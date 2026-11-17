// miax/miaxoptions/clearingtradedrop/MiaxOptions_ClearingTradeDrop_v2_4_a.c
/*
 * Miami International Holdings Clearing Trade Drop
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

/* ---- Sesm Packet Header: 3 bytes --------------------------------------------- */

/* SesM packet header */
typedef struct {
  uint8_t sesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t sesm_packet_type;       /* byte 2 */
} SesmPacketHeader;

/* any Sesm Packet Header at all: every byte one the checker chooses */
static void any_sesm_packet_header(SesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = arbitrary(); }
  record->sesm_packet_type = arbitrary();
}

/* Sesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_sesm_packet_header(const SesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sesm_packet_length[i]; }
  wire[at++] = record->sesm_packet_type;

  return at;
}

/* Sesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_sesm_packet_header(SesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = wire[at++]; }
  record->sesm_packet_type = wire[at++];

  return at;
}

/* what was read of Sesm Packet Header is what was written, byte for byte */
static void equal_sesm_packet_header(const SesmPacketHeader *read, const SesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->sesm_packet_length[i] == written->sesm_packet_length[i]); }
  assert(read->sesm_packet_type == written->sesm_packet_type);
}

/* Sesm Packet Header: written and read back, then read and written back */
static void check_sesm_packet_header(void) {
  SesmPacketHeader sent;
  SesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_sesm_packet_header(&sent);
  assert(encode_sesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  equal_sesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  assert(encode_sesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State: 21 bytes -------------------------------------------------- */

/* This message format is used to notify firms of the state changes of the system. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems. */
typedef struct {
  uint8_t notification_time[8];   /* bytes 0 to 7 */
  uint8_t ctd_version[8];         /* bytes 8 to 15 */
  uint8_t trading_session_id[4];  /* bytes 16 to 19 */
  uint8_t system_status;          /* byte 20 */
} SystemState;

/* any System State at all: every byte one the checker chooses */
static void any_system_state(SystemState *record) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ctd_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = arbitrary(); }
  record->system_status = arbitrary();
}

/* System State to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_system_state(const SystemState *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->notification_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ctd_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_id[i]; }
  wire[at++] = record->system_status;

  return at;
}

/* System State off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_system_state(SystemState *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->notification_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ctd_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = wire[at++]; }
  record->system_status = wire[at++];

  return at;
}

/* what was read of System State is what was written, byte for byte */
static void equal_system_state(const SystemState *read, const SystemState *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->notification_time[i] == written->notification_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ctd_version[i] == written->ctd_version[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_id[i] == written->trading_session_id[i]); }
  assert(read->system_status == written->system_status);
}

/* System State: written and read back, then read and written back */
static void check_system_state(void) {
  SystemState sent;
  SystemState got;
  uint8_t wire[21];
  uint8_t again[21];

  any_system_state(&sent);
  assert(encode_system_state(&sent, wire, 0) == 21);
  assert(decode_system_state(&got, wire, 0) == 21);
  equal_system_state(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state(&got, wire, 0) == 21);
  assert(encode_system_state(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Message: 310 bytes ------------------------------------------------ */

/* This is the message format that will be used to disseminate all MIAX trade related content for entitled parties. MIAX sends trades, trade corrections and trade cancels using this message. This is a sequenced message. */
typedef struct {
  uint8_t processing_time[8];                    /* bytes 0 to 7 */
  uint8_t trade_time[8];                         /* bytes 8 to 15 */
  uint8_t trade_as_of_date[4];                   /* bytes 16 to 19 */
  uint8_t trade_action;                          /* byte 20 */
  uint8_t trade_type;                            /* byte 21 */
  uint8_t trade_id[4];                           /* bytes 22 to 25 */
  uint8_t execution_id[8];                       /* bytes 26 to 33 */
  uint8_t correction_number;                     /* byte 34 */
  uint8_t transaction_id[4];                     /* bytes 35 to 38 */
  uint8_t reference_trade_time[8];               /* bytes 39 to 46 */
  uint8_t reference_trade_id[4];                 /* bytes 47 to 50 */
  uint8_t reference_correction_number;           /* byte 51 */
  uint8_t correction_type;                       /* byte 52 */
  uint8_t event_id[4];                           /* bytes 53 to 56 */
  uint8_t strategy_id[4];                        /* bytes 57 to 60 */
  uint8_t reserved_12[12];                       /* bytes 61 to 72 */
  uint8_t product_id[4];                         /* bytes 73 to 76 */
  uint8_t underlying_symbol[11];                 /* bytes 77 to 87 */
  uint8_t underlying_type;                       /* byte 88 */
  uint8_t security_symbol[6];                    /* bytes 89 to 94 */
  uint8_t expiration_date[4];                    /* bytes 95 to 98 */
  uint8_t strike_price[4];                       /* bytes 99 to 102 */
  uint8_t call_or_put;                           /* byte 103 */
  uint8_t reserved_8[8];                         /* bytes 104 to 111 */
  uint8_t side;                                  /* byte 112 */
  uint8_t price[4];                              /* bytes 113 to 116 */
  uint8_t size[4];                               /* bytes 117 to 120 */
  uint8_t trade_condition;                       /* byte 121 */
  uint8_t second_reserved_8[8];                  /* bytes 122 to 129 */
  uint8_t class_fee_type;                        /* byte 130 */
  uint8_t miax_bbo_posting_increment_indicator;  /* byte 131 */
  uint8_t execution_exchange;                    /* byte 132 */
  uint8_t routed_order_quantity[4];              /* bytes 133 to 136 */
  uint8_t market_maker_role;                     /* byte 137 */
  uint8_t traded_with_directed_mm;               /* byte 138 */
  uint8_t market_state;                          /* byte 139 */
  uint8_t auction_type;                          /* byte 140 */
  uint8_t directed_status;                       /* byte 141 */
  uint8_t strategy_state;                        /* byte 142 */
  uint8_t strategy_auction_type;                 /* byte 143 */
  uint8_t stock_execution_destination;           /* byte 144 */
  uint8_t reserved_13[13];                       /* bytes 145 to 157 */
  uint8_t executing_mpid[4];                     /* bytes 158 to 161 */
  uint8_t order_date[4];                         /* bytes 162 to 165 */
  uint8_t fix_order_id[30];                      /* bytes 166 to 195 */
  uint8_t client_message_id[4];                  /* bytes 196 to 199 */
  uint8_t bulk_quote_index;                      /* byte 200 */
  uint8_t open_close_indicator;                  /* byte 201 */
  uint8_t liquidity_type;                        /* byte 202 */
  uint8_t mm_priority_indicator;                 /* byte 203 */
  uint8_t liquidity_indicator;                   /* byte 204 */
  uint8_t liquidity_timer_role;                  /* byte 205 */
  uint8_t time_in_force;                         /* byte 206 */
  uint8_t billing_mpid[4];                       /* bytes 207 to 210 */
  uint8_t leg_reference_id[5];                   /* bytes 211 to 215 */
  uint8_t strategy_timer_role;                   /* byte 216 */
  uint8_t stock_short_sell_indicator;            /* byte 217 */
  uint8_t reserved_4[4];                         /* bytes 218 to 221 */
  uint8_t clearing_mpid[4];                      /* bytes 222 to 225 */
  uint8_t member_type;                           /* byte 226 */
  uint8_t origin;                                /* byte 227 */
  uint8_t clearing_number[4];                    /* bytes 228 to 231 */
  uint8_t cmta[4];                               /* bytes 232 to 235 */
  uint8_t multi_account[5];                      /* bytes 236 to 240 */
  uint8_t account_id[10];                        /* bytes 241 to 250 */
  uint8_t supplementary_id[13];                  /* bytes 251 to 263 */
  uint8_t allocation_id[4];                      /* bytes 264 to 267 */
  uint8_t billing_clearing_number[4];            /* bytes 268 to 271 */
  uint8_t order_capacity;                        /* byte 272 */
  uint8_t reserved_7[7];                         /* bytes 273 to 279 */
  uint8_t mpid[4];                               /* bytes 280 to 283 */
  uint8_t contra_member_type;                    /* byte 284 */
  uint8_t contra_origin;                         /* byte 285 */
  uint8_t contra_clearing_number[4];             /* bytes 286 to 289 */
  uint8_t contra_cmta[4];                        /* bytes 290 to 293 */
  uint8_t contra_time_in_force;                  /* byte 294 */
  uint8_t contra_liquidity_timer_role;           /* byte 295 */
  uint8_t contra_strategy_timer_role;            /* byte 296 */
  uint8_t contra_order_capacity;                 /* byte 297 */
  uint8_t second_reserved_12[12];                /* bytes 298 to 309 */
} TradeMessage;

/* any Trade Message at all: every byte one the checker chooses */
static void any_trade_message(TradeMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->processing_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_as_of_date[i] = arbitrary(); }
  record->trade_action = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  record->correction_number = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_trade_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_trade_id[i] = arbitrary(); }
  record->reference_correction_number = arbitrary();
  record->correction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = arbitrary(); }
  record->underlying_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->call_or_put = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = arbitrary(); }
  record->class_fee_type = arbitrary();
  record->miax_bbo_posting_increment_indicator = arbitrary();
  record->execution_exchange = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->routed_order_quantity[i] = arbitrary(); }
  record->market_maker_role = arbitrary();
  record->traded_with_directed_mm = arbitrary();
  record->market_state = arbitrary();
  record->auction_type = arbitrary();
  record->directed_status = arbitrary();
  record->strategy_state = arbitrary();
  record->strategy_auction_type = arbitrary();
  record->stock_execution_destination = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->reserved_13[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executing_mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->fix_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = arbitrary(); }
  record->bulk_quote_index = arbitrary();
  record->open_close_indicator = arbitrary();
  record->liquidity_type = arbitrary();
  record->mm_priority_indicator = arbitrary();
  record->liquidity_indicator = arbitrary();
  record->liquidity_timer_role = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->billing_mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->leg_reference_id[i] = arbitrary(); }
  record->strategy_timer_role = arbitrary();
  record->stock_short_sell_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_mpid[i] = arbitrary(); }
  record->member_type = arbitrary();
  record->origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->multi_account[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 13; i++) { record->supplementary_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->allocation_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->billing_clearing_number[i] = arbitrary(); }
  record->order_capacity = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  record->contra_member_type = arbitrary();
  record->contra_origin = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_cmta[i] = arbitrary(); }
  record->contra_time_in_force = arbitrary();
  record->contra_liquidity_timer_role = arbitrary();
  record->contra_strategy_timer_role = arbitrary();
  record->contra_order_capacity = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->second_reserved_12[i] = arbitrary(); }
}

/* Trade Message to the wire: 310 bytes from at, returning where the next byte goes */
static size_t encode_trade_message(const TradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->processing_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_as_of_date[i]; }
  wire[at++] = record->trade_action;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  wire[at++] = record->correction_number;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_trade_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_trade_id[i]; }
  wire[at++] = record->reference_correction_number;
  wire[at++] = record->correction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->underlying_symbol[i]; }
  wire[at++] = record->underlying_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->call_or_put;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_reserved_8[i]; }
  wire[at++] = record->class_fee_type;
  wire[at++] = record->miax_bbo_posting_increment_indicator;
  wire[at++] = record->execution_exchange;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routed_order_quantity[i]; }
  wire[at++] = record->market_maker_role;
  wire[at++] = record->traded_with_directed_mm;
  wire[at++] = record->market_state;
  wire[at++] = record->auction_type;
  wire[at++] = record->directed_status;
  wire[at++] = record->strategy_state;
  wire[at++] = record->strategy_auction_type;
  wire[at++] = record->stock_execution_destination;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->reserved_13[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_date[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->fix_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_message_id[i]; }
  wire[at++] = record->bulk_quote_index;
  wire[at++] = record->open_close_indicator;
  wire[at++] = record->liquidity_type;
  wire[at++] = record->mm_priority_indicator;
  wire[at++] = record->liquidity_indicator;
  wire[at++] = record->liquidity_timer_role;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->billing_mpid[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->leg_reference_id[i]; }
  wire[at++] = record->strategy_timer_role;
  wire[at++] = record->stock_short_sell_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_mpid[i]; }
  wire[at++] = record->member_type;
  wire[at++] = record->origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->multi_account[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->supplementary_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->allocation_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->billing_clearing_number[i]; }
  wire[at++] = record->order_capacity;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  wire[at++] = record->contra_member_type;
  wire[at++] = record->contra_origin;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_clearing_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_cmta[i]; }
  wire[at++] = record->contra_time_in_force;
  wire[at++] = record->contra_liquidity_timer_role;
  wire[at++] = record->contra_strategy_timer_role;
  wire[at++] = record->contra_order_capacity;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->second_reserved_12[i]; }

  return at;
}

/* Trade Message off the wire: 310 bytes from at, returning where the next byte lies */
static size_t decode_trade_message(TradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->processing_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_as_of_date[i] = wire[at++]; }
  record->trade_action = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  record->correction_number = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_trade_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_trade_id[i] = wire[at++]; }
  record->reference_correction_number = wire[at++];
  record->correction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->underlying_symbol[i] = wire[at++]; }
  record->underlying_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->security_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->call_or_put = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->second_reserved_8[i] = wire[at++]; }
  record->class_fee_type = wire[at++];
  record->miax_bbo_posting_increment_indicator = wire[at++];
  record->execution_exchange = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->routed_order_quantity[i] = wire[at++]; }
  record->market_maker_role = wire[at++];
  record->traded_with_directed_mm = wire[at++];
  record->market_state = wire[at++];
  record->auction_type = wire[at++];
  record->directed_status = wire[at++];
  record->strategy_state = wire[at++];
  record->strategy_auction_type = wire[at++];
  record->stock_execution_destination = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->reserved_13[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executing_mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->fix_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_message_id[i] = wire[at++]; }
  record->bulk_quote_index = wire[at++];
  record->open_close_indicator = wire[at++];
  record->liquidity_type = wire[at++];
  record->mm_priority_indicator = wire[at++];
  record->liquidity_indicator = wire[at++];
  record->liquidity_timer_role = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->billing_mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->leg_reference_id[i] = wire[at++]; }
  record->strategy_timer_role = wire[at++];
  record->stock_short_sell_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_mpid[i] = wire[at++]; }
  record->member_type = wire[at++];
  record->origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->multi_account[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 13; i++) { record->supplementary_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->allocation_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->billing_clearing_number[i] = wire[at++]; }
  record->order_capacity = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  record->contra_member_type = wire[at++];
  record->contra_origin = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_cmta[i] = wire[at++]; }
  record->contra_time_in_force = wire[at++];
  record->contra_liquidity_timer_role = wire[at++];
  record->contra_strategy_timer_role = wire[at++];
  record->contra_order_capacity = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->second_reserved_12[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Message is what was written, byte for byte */
static void equal_trade_message(const TradeMessage *read, const TradeMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->processing_time[i] == written->processing_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_time[i] == written->trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_as_of_date[i] == written->trade_as_of_date[i]); }
  assert(read->trade_action == written->trade_action);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  assert(read->correction_number == written->correction_number);
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_id[i] == written->transaction_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_trade_time[i] == written->reference_trade_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_trade_id[i] == written->reference_trade_id[i]); }
  assert(read->reference_correction_number == written->reference_correction_number);
  assert(read->correction_type == written->correction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_id[i] == written->strategy_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_id[i] == written->product_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  assert(read->underlying_type == written->underlying_type);
  for (size_t i = 0; i < 6; i++) { assert(read->security_symbol[i] == written->security_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->call_or_put == written->call_or_put);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->second_reserved_8[i] == written->second_reserved_8[i]); }
  assert(read->class_fee_type == written->class_fee_type);
  assert(read->miax_bbo_posting_increment_indicator == written->miax_bbo_posting_increment_indicator);
  assert(read->execution_exchange == written->execution_exchange);
  for (size_t i = 0; i < 4; i++) { assert(read->routed_order_quantity[i] == written->routed_order_quantity[i]); }
  assert(read->market_maker_role == written->market_maker_role);
  assert(read->traded_with_directed_mm == written->traded_with_directed_mm);
  assert(read->market_state == written->market_state);
  assert(read->auction_type == written->auction_type);
  assert(read->directed_status == written->directed_status);
  assert(read->strategy_state == written->strategy_state);
  assert(read->strategy_auction_type == written->strategy_auction_type);
  assert(read->stock_execution_destination == written->stock_execution_destination);
  for (size_t i = 0; i < 13; i++) { assert(read->reserved_13[i] == written->reserved_13[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executing_mpid[i] == written->executing_mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_date[i] == written->order_date[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->fix_order_id[i] == written->fix_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_message_id[i] == written->client_message_id[i]); }
  assert(read->bulk_quote_index == written->bulk_quote_index);
  assert(read->open_close_indicator == written->open_close_indicator);
  assert(read->liquidity_type == written->liquidity_type);
  assert(read->mm_priority_indicator == written->mm_priority_indicator);
  assert(read->liquidity_indicator == written->liquidity_indicator);
  assert(read->liquidity_timer_role == written->liquidity_timer_role);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->billing_mpid[i] == written->billing_mpid[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->leg_reference_id[i] == written->leg_reference_id[i]); }
  assert(read->strategy_timer_role == written->strategy_timer_role);
  assert(read->stock_short_sell_indicator == written->stock_short_sell_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_mpid[i] == written->clearing_mpid[i]); }
  assert(read->member_type == written->member_type);
  assert(read->origin == written->origin);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_number[i] == written->clearing_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta[i] == written->cmta[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->multi_account[i] == written->multi_account[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 13; i++) { assert(read->supplementary_id[i] == written->supplementary_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->allocation_id[i] == written->allocation_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->billing_clearing_number[i] == written->billing_clearing_number[i]); }
  assert(read->order_capacity == written->order_capacity);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  assert(read->contra_member_type == written->contra_member_type);
  assert(read->contra_origin == written->contra_origin);
  for (size_t i = 0; i < 4; i++) { assert(read->contra_clearing_number[i] == written->contra_clearing_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_cmta[i] == written->contra_cmta[i]); }
  assert(read->contra_time_in_force == written->contra_time_in_force);
  assert(read->contra_liquidity_timer_role == written->contra_liquidity_timer_role);
  assert(read->contra_strategy_timer_role == written->contra_strategy_timer_role);
  assert(read->contra_order_capacity == written->contra_order_capacity);
  for (size_t i = 0; i < 12; i++) { assert(read->second_reserved_12[i] == written->second_reserved_12[i]); }
}

/* Trade Message: written and read back, then read and written back */
static void check_trade_message(void) {
  TradeMessage sent;
  TradeMessage got;
  uint8_t wire[310];
  uint8_t again[310];

  any_trade_message(&sent);
  assert(encode_trade_message(&sent, wire, 0) == 310);
  assert(decode_trade_message(&got, wire, 0) == 310);
  equal_trade_message(&got, &sent);

  for (size_t i = 0; i < 310; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_message(&got, wire, 0) == 310);
  assert(encode_trade_message(&got, again, 0) == 310);
  for (size_t i = 0; i < 310; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Notification Message: 160 bytes ------------------------------------ */

/* Firms configured to use Risk Protection Monitoring will receive User Notification communicating the status of Risk checks. Field Event Type is used to determine the reason for the notification. The following message will be used to disseminate all MIAX Risk Protection Monitor (RPM) related notifications. Sequenced and UnSequenced Pkt based on Event Type: solicited event types (T, R, W, D, A, P, U) are Sequenced messages at the SesM protocol level and recoverable; unsolicited (S) are Unsequenced and not recoverable. */
typedef struct {
  uint8_t processing_time[8];                  /* bytes 0 to 7 */
  uint8_t mpid_group_id[32];                   /* bytes 8 to 39 */
  uint8_t metric_id[32];                       /* bytes 40 to 71 */
  uint8_t route_id[32];                        /* bytes 72 to 103 */
  uint8_t metric_type;                         /* byte 104 */
  uint8_t protection_type;                     /* byte 105 */
  uint8_t event_type;                          /* byte 106 */
  uint8_t event_id[4];                         /* bytes 107 to 110 */
  uint8_t configured_counting_time_period[4];  /* bytes 111 to 114 */
  uint8_t configured_max_quantity[4];          /* bytes 115 to 118 */
  uint8_t current_quantity[4];                 /* bytes 119 to 122 */
  uint8_t max_peak_quantity[4];                /* bytes 123 to 126 */
  uint8_t percentage_level;                    /* byte 127 */
  uint8_t reserved_32[32];                     /* bytes 128 to 159 */
} RiskNotificationMessage;

/* any Risk Notification Message at all: every byte one the checker chooses */
static void any_risk_notification_message(RiskNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->processing_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->mpid_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->metric_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->route_id[i] = arbitrary(); }
  record->metric_type = arbitrary();
  record->protection_type = arbitrary();
  record->event_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->configured_counting_time_period[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->configured_max_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->current_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_peak_quantity[i] = arbitrary(); }
  record->percentage_level = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = arbitrary(); }
}

/* Risk Notification Message to the wire: 160 bytes from at, returning where the next byte goes */
static size_t encode_risk_notification_message(const RiskNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->processing_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->mpid_group_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->metric_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->route_id[i]; }
  wire[at++] = record->metric_type;
  wire[at++] = record->protection_type;
  wire[at++] = record->event_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->event_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->configured_counting_time_period[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->configured_max_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_peak_quantity[i]; }
  wire[at++] = record->percentage_level;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reserved_32[i]; }

  return at;
}

/* Risk Notification Message off the wire: 160 bytes from at, returning where the next byte lies */
static size_t decode_risk_notification_message(RiskNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->processing_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->mpid_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->metric_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->route_id[i] = wire[at++]; }
  record->metric_type = wire[at++];
  record->protection_type = wire[at++];
  record->event_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->event_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->configured_counting_time_period[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->configured_max_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->current_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_peak_quantity[i] = wire[at++]; }
  record->percentage_level = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->reserved_32[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Notification Message is what was written, byte for byte */
static void equal_risk_notification_message(const RiskNotificationMessage *read, const RiskNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->processing_time[i] == written->processing_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->mpid_group_id[i] == written->mpid_group_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->metric_id[i] == written->metric_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->route_id[i] == written->route_id[i]); }
  assert(read->metric_type == written->metric_type);
  assert(read->protection_type == written->protection_type);
  assert(read->event_type == written->event_type);
  for (size_t i = 0; i < 4; i++) { assert(read->event_id[i] == written->event_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->configured_counting_time_period[i] == written->configured_counting_time_period[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->configured_max_quantity[i] == written->configured_max_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->current_quantity[i] == written->current_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_peak_quantity[i] == written->max_peak_quantity[i]); }
  assert(read->percentage_level == written->percentage_level);
  for (size_t i = 0; i < 32; i++) { assert(read->reserved_32[i] == written->reserved_32[i]); }
}

/* Risk Notification Message: written and read back, then read and written back */
static void check_risk_notification_message(void) {
  RiskNotificationMessage sent;
  RiskNotificationMessage got;
  uint8_t wire[160];
  uint8_t again[160];

  any_risk_notification_message(&sent);
  assert(encode_risk_notification_message(&sent, wire, 0) == 160);
  assert(decode_risk_notification_message(&got, wire, 0) == 160);
  equal_risk_notification_message(&got, &sent);

  for (size_t i = 0; i < 160; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_notification_message(&got, wire, 0) == 160);
  assert(encode_risk_notification_message(&got, again, 0) == 160);
  for (size_t i = 0; i < 160; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client uses this packet to allow the server to authenticate the client and to convey to the server the last sequenced packet that the client received */
typedef struct {
  uint8_t sesm_version[5];               /* bytes 0 to 4 */
  uint8_t username[5];                   /* bytes 5 to 9 */
  uint8_t computer_id[8];                /* bytes 10 to 17 */
  uint8_t application_protocol[8];       /* bytes 18 to 25 */
  uint8_t requested_session;             /* byte 26 */
  uint8_t requested_sequence_number[8];  /* bytes 27 to 34 */
} LoginRequest;

/* any Login Request at all: every byte one the checker chooses */
static void any_login_request(LoginRequest *record) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = arbitrary(); }
  record->requested_session = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_login_request(const LoginRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sesm_version[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->computer_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_protocol[i]; }
  wire[at++] = record->requested_session;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_login_request(LoginRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = wire[at++]; }
  record->requested_session = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request is what was written, byte for byte */
static void equal_login_request(const LoginRequest *read, const LoginRequest *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->sesm_version[i] == written->sesm_version[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->computer_id[i] == written->computer_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_protocol[i] == written->application_protocol[i]); }
  assert(read->requested_session == written->requested_session);
  for (size_t i = 0; i < 8; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request: written and read back, then read and written back */
static void check_login_request(void) {
  LoginRequest sent;
  LoginRequest got;
  uint8_t wire[35];
  uint8_t again[35];

  any_login_request(&sent);
  assert(encode_login_request(&sent, wire, 0) == 35);
  assert(decode_login_request(&got, wire, 0) == 35);
  equal_login_request(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request(&got, wire, 0) == 35);
  assert(encode_login_request(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 10 bytes ------------------------------------------------ */

/* The SesM server sends a Login response packet in response to a Login request packet from the client */
typedef struct {
  uint8_t login_status;                /* byte 0 */
  uint8_t session_id;                  /* byte 1 */
  uint8_t highest_sequence_number[8];  /* bytes 2 to 9 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->login_status = arbitrary();
  record->session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = arbitrary(); }
}

/* Login Response to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_status;
  wire[at++] = record->session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_sequence_number[i]; }

  return at;
}

/* Login Response off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->login_status = wire[at++];
  record->session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->login_status == written->login_status);
  assert(read->session_id == written->session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->highest_sequence_number[i] == written->highest_sequence_number[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[10];
  uint8_t again[10];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 10);
  assert(decode_login_response(&got, wire, 0) == 10);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 10);
  assert(encode_login_response(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The SesM client uses this packet to request the server to retransmit a range of packets */
typedef struct {
  uint8_t start_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t end_sequence_number[8];    /* bytes 8 to 15 */
} RetransmissionRequest;

/* any Retransmission Request at all: every byte one the checker chooses */
static void any_retransmission_request(RetransmissionRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = arbitrary(); }
}

/* Retransmission Request to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request(const RetransmissionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_sequence_number[i]; }

  return at;
}

/* Retransmission Request off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request(RetransmissionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request is what was written, byte for byte */
static void equal_retransmission_request(const RetransmissionRequest *read, const RetransmissionRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->start_sequence_number[i] == written->start_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_sequence_number[i] == written->end_sequence_number[i]); }
}

/* Retransmission Request: written and read back, then read and written back */
static void check_retransmission_request(void) {
  RetransmissionRequest sent;
  RetransmissionRequest got;
  uint8_t wire[16];
  uint8_t again[16];

  any_retransmission_request(&sent);
  assert(encode_retransmission_request(&sent, wire, 0) == 16);
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  equal_retransmission_request(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  assert(encode_retransmission_request(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sesm_packet_header();
  check_system_state();
  check_trade_message();
  check_risk_notification_message();
  check_login_request();
  check_login_response();
  check_retransmission_request();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
