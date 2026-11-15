// cboe/cxaequities/binaryorderentry/CxaEquities_BinaryOrderEntry_v1_0_20_Exchange.c
/*
 * Chicago Board Options Exchange Binary Order Entry
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
 *   - a Reassemble rule
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

/* ---- Exchange Message Header: 12 bytes --------------------------------------- */

/* Message header of a packet sent by the exchange */
typedef struct {
  uint8_t start_of_message[2];       /* bytes 0 to 1 */
  uint8_t message_length[2];         /* bytes 2 to 3 */
  uint8_t exchange_message_type[2];  /* bytes 4 to 5 */
  uint8_t matching_unit;             /* byte 6 */
  uint8_t reserved_field;            /* byte 7 */
  uint8_t sequence_number[4];        /* bytes 8 to 11 */
} ExchangeMessageHeader;

/* any Exchange Message Header at all: every byte one the checker chooses */
static void any_exchange_message_header(ExchangeMessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->exchange_message_type[i] = arbitrary(); }
  record->matching_unit = arbitrary();
  record->reserved_field = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Exchange Message Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_exchange_message_header(const ExchangeMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->start_of_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->exchange_message_type[i]; }
  wire[at++] = record->matching_unit;
  wire[at++] = record->reserved_field;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Exchange Message Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_exchange_message_header(ExchangeMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->exchange_message_type[i] = wire[at++]; }
  record->matching_unit = wire[at++];
  record->reserved_field = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Exchange Message Header is what was written, byte for byte */
static void equal_exchange_message_header(const ExchangeMessageHeader *read, const ExchangeMessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->start_of_message[i] == written->start_of_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->exchange_message_type[i] == written->exchange_message_type[i]); }
  assert(read->matching_unit == written->matching_unit);
  assert(read->reserved_field == written->reserved_field);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Exchange Message Header: written and read back, then read and written back */
static void check_exchange_message_header(void) {
  ExchangeMessageHeader sent;
  ExchangeMessageHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_exchange_message_header(&sent);
  assert(encode_exchange_message_header(&sent, wire, 0) == 12);
  assert(decode_exchange_message_header(&got, wire, 0) == 12);
  equal_exchange_message_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_exchange_message_header(&got, wire, 0) == 12);
  assert(encode_exchange_message_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Response Message: 61 bytes --------------------------------------- */

/* A Logout Response is usually sent in response to a Logout Request */
typedef struct {
  uint8_t logout_reason;           /* byte 0 */
  uint8_t logout_reason_text[60];  /* bytes 1 to 60 */
} LogoutResponseMessage;

/* any Logout Response Message at all: every byte one the checker chooses */
static void any_logout_response_message(LogoutResponseMessage *record) {
  record->logout_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->logout_reason_text[i] = arbitrary(); }
}

/* Logout Response Message to the wire: 61 bytes from at, returning where the next byte goes */
static size_t encode_logout_response_message(const LogoutResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->logout_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->logout_reason_text[i]; }

  return at;
}

/* Logout Response Message off the wire: 61 bytes from at, returning where the next byte lies */
static size_t decode_logout_response_message(LogoutResponseMessage *record, const uint8_t *wire, size_t at) {
  record->logout_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->logout_reason_text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Response Message is what was written, byte for byte */
static void equal_logout_response_message(const LogoutResponseMessage *read, const LogoutResponseMessage *written) {
  assert(read->logout_reason == written->logout_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->logout_reason_text[i] == written->logout_reason_text[i]); }
}

/* Logout Response Message: written and read back, then read and written back */
static void check_logout_response_message(void) {
  LogoutResponseMessage sent;
  LogoutResponseMessage got;
  uint8_t wire[61];
  uint8_t again[61];

  any_logout_response_message(&sent);
  assert(encode_logout_response_message(&sent, wire, 0) == 61);
  assert(decode_logout_response_message(&got, wire, 0) == 61);
  equal_logout_response_message(&got, &sent);

  for (size_t i = 0; i < 61; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_response_message(&got, wire, 0) == 61);
  assert(encode_logout_response_message(&got, again, 0) == 61);
  for (size_t i = 0; i < 61; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Acknowledgement Au Equities V 1: 192 bytes ------------------------ */

/* Order Acknowledgement messages are sent in response to a New Order message */
typedef struct {
  uint8_t transaction_time[8];            /* bytes 0 to 7 */
  uint8_t account[10];                    /* bytes 8 to 17 */
  uint8_t trading_participant_id[2];      /* bytes 18 to 19 */
  uint8_t cl_ord_id[20];                  /* bytes 20 to 39 */
  uint8_t exec_inst;                      /* byte 40 */
  uint8_t order_id[8];                    /* bytes 41 to 48 */
  uint8_t order_qty[4];                   /* bytes 49 to 52 */
  uint8_t ord_type;                       /* byte 53 */
  uint8_t price[8];                       /* bytes 54 to 61 */
  uint8_t capacity;                       /* byte 62 */
  uint8_t side;                           /* byte 63 */
  uint8_t symbol[6];                      /* bytes 64 to 69 */
  uint8_t time_in_force;                  /* byte 70 */
  uint8_t min_qty[4];                     /* bytes 71 to 74 */
  uint8_t max_floor[4];                   /* bytes 75 to 78 */
  uint8_t expire_time[8];                 /* bytes 79 to 86 */
  uint8_t clearing_participant_id[4];     /* bytes 87 to 90 */
  uint8_t clearing_account[10];           /* bytes 91 to 100 */
  uint8_t undisclosed;                    /* byte 101 */
  uint8_t client_cross_ref[15];           /* bytes 102 to 116 */
  uint8_t short_sell_naked_qty[4];        /* bytes 117 to 120 */
  uint8_t short_sell_covered_qty[4];      /* bytes 121 to 124 */
  uint8_t short_sell_long_qty[4];         /* bytes 125 to 128 */
  uint8_t risk_group_id[2];               /* bytes 129 to 130 */
  uint8_t no_trade_feat;                  /* byte 131 */
  uint8_t no_trade_key[10];               /* bytes 132 to 141 */
  uint8_t meqse;                          /* byte 142 */
  uint8_t origin_of_trans[20];            /* bytes 143 to 162 */
  uint8_t intermediary_id[10];            /* bytes 163 to 172 */
  uint8_t directed_wholesale_indicator;   /* byte 173 */
  uint8_t remove_crossing_from_clearing;  /* byte 174 */
  uint8_t broker_preferencing;            /* byte 175 */
  uint8_t working_price[8];               /* bytes 176 to 183 */
  uint8_t base_liquidity_indicator;       /* byte 184 */
  uint8_t sub_liquidity_indicator;        /* byte 185 */
  uint8_t routing_inst;                   /* byte 186 */
  uint8_t display_indicator;              /* byte 187 */
  uint8_t expire_date[4];                 /* bytes 188 to 191 */
} OrderAcknowledgementAuEquitiesV1;

/* any Order Acknowledgement Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_acknowledgement_au_equities_v1(OrderAcknowledgementAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = arbitrary(); }
  record->undisclosed = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = arbitrary(); }
  record->meqse = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  record->directed_wholesale_indicator = arbitrary();
  record->remove_crossing_from_clearing = arbitrary();
  record->broker_preferencing = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  record->routing_inst = arbitrary();
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* Order Acknowledgement Au Equities V 1 to the wire: 192 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_au_equities_v1(const OrderAcknowledgementAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->undisclosed;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_cross_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->meqse;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->origin_of_trans[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  wire[at++] = record->directed_wholesale_indicator;
  wire[at++] = record->remove_crossing_from_clearing;
  wire[at++] = record->broker_preferencing;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  wire[at++] = record->routing_inst;
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* Order Acknowledgement Au Equities V 1 off the wire: 192 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_au_equities_v1(OrderAcknowledgementAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = wire[at++]; }
  record->undisclosed = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = wire[at++]; }
  record->meqse = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  record->directed_wholesale_indicator = wire[at++];
  record->remove_crossing_from_clearing = wire[at++];
  record->broker_preferencing = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  record->routing_inst = wire[at++];
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement Au Equities V 1 is what was written, byte for byte */
static void equal_order_acknowledgement_au_equities_v1(const OrderAcknowledgementAuEquitiesV1 *read, const OrderAcknowledgementAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->capacity == written->capacity);
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->undisclosed == written->undisclosed);
  for (size_t i = 0; i < 15; i++) { assert(read->client_cross_ref[i] == written->client_cross_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 10; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->meqse == written->meqse);
  for (size_t i = 0; i < 20; i++) { assert(read->origin_of_trans[i] == written->origin_of_trans[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  assert(read->directed_wholesale_indicator == written->directed_wholesale_indicator);
  assert(read->remove_crossing_from_clearing == written->remove_crossing_from_clearing);
  assert(read->broker_preferencing == written->broker_preferencing);
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  assert(read->routing_inst == written->routing_inst);
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* Order Acknowledgement Au Equities V 1: written and read back, then read and written back */
static void check_order_acknowledgement_au_equities_v1(void) {
  OrderAcknowledgementAuEquitiesV1 sent;
  OrderAcknowledgementAuEquitiesV1 got;
  uint8_t wire[192];
  uint8_t again[192];

  any_order_acknowledgement_au_equities_v1(&sent);
  assert(encode_order_acknowledgement_au_equities_v1(&sent, wire, 0) == 192);
  assert(decode_order_acknowledgement_au_equities_v1(&got, wire, 0) == 192);
  equal_order_acknowledgement_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 192; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_au_equities_v1(&got, wire, 0) == 192);
  assert(encode_order_acknowledgement_au_equities_v1(&got, again, 0) == 192);
  for (size_t i = 0; i < 192; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Au Equities V 1: 91 bytes -------------------------------- */

/* Order Rejected messages are sent in response to a New Order which must be rejected */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t order_reject_reason;        /* byte 30 */
  uint8_t text[60];                   /* bytes 31 to 90 */
} OrderRejectedAuEquitiesV1;

/* any Order Rejected Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_rejected_au_equities_v1(OrderRejectedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Au Equities V 1 to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_au_equities_v1(const OrderRejectedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Au Equities V 1 off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_au_equities_v1(OrderRejectedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Au Equities V 1 is what was written, byte for byte */
static void equal_order_rejected_au_equities_v1(const OrderRejectedAuEquitiesV1 *read, const OrderRejectedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Au Equities V 1: written and read back, then read and written back */
static void check_order_rejected_au_equities_v1(void) {
  OrderRejectedAuEquitiesV1 sent;
  OrderRejectedAuEquitiesV1 got;
  uint8_t wire[91];
  uint8_t again[91];

  any_order_rejected_au_equities_v1(&sent);
  assert(encode_order_rejected_au_equities_v1(&sent, wire, 0) == 91);
  assert(decode_order_rejected_au_equities_v1(&got, wire, 0) == 91);
  equal_order_rejected_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_au_equities_v1(&got, wire, 0) == 91);
  assert(encode_order_rejected_au_equities_v1(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Au Equities V 1: 105 bytes ------------------------------- */

/* Order Modified messages are sent in response to a Modify Order to indicate that the order has been successfully modified */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t exec_inst;                  /* byte 30 */
  uint8_t order_qty[4];               /* bytes 31 to 34 */
  uint8_t orig_cl_ord_id[20];         /* bytes 35 to 54 */
  uint8_t price[8];                   /* bytes 55 to 62 */
  uint8_t min_qty[4];                 /* bytes 63 to 66 */
  uint8_t max_floor[4];               /* bytes 67 to 70 */
  uint8_t leaves_qty[4];              /* bytes 71 to 74 */
  uint8_t secondary_order_id[8];      /* bytes 75 to 82 */
  uint8_t short_sell_naked_qty[4];    /* bytes 83 to 86 */
  uint8_t short_sell_covered_qty[4];  /* bytes 87 to 90 */
  uint8_t short_sell_long_qty[4];     /* bytes 91 to 94 */
  uint8_t working_price[8];           /* bytes 95 to 102 */
  uint8_t base_liquidity_indicator;   /* byte 103 */
  uint8_t sub_liquidity_indicator;    /* byte 104 */
} OrderModifiedAuEquitiesV1;

/* any Order Modified Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_modified_au_equities_v1(OrderModifiedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
}

/* Order Modified Au Equities V 1 to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_au_equities_v1(const OrderModifiedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;

  return at;
}

/* Order Modified Au Equities V 1 off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_au_equities_v1(OrderModifiedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];

  return at;
}

/* what was read of Order Modified Au Equities V 1 is what was written, byte for byte */
static void equal_order_modified_au_equities_v1(const OrderModifiedAuEquitiesV1 *read, const OrderModifiedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
}

/* Order Modified Au Equities V 1: written and read back, then read and written back */
static void check_order_modified_au_equities_v1(void) {
  OrderModifiedAuEquitiesV1 sent;
  OrderModifiedAuEquitiesV1 got;
  uint8_t wire[105];
  uint8_t again[105];

  any_order_modified_au_equities_v1(&sent);
  assert(encode_order_modified_au_equities_v1(&sent, wire, 0) == 105);
  assert(decode_order_modified_au_equities_v1(&got, wire, 0) == 105);
  equal_order_modified_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_au_equities_v1(&got, wire, 0) == 105);
  assert(encode_order_modified_au_equities_v1(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Au Equities V 1: 111 bytes ------------------------------ */

/* Modify Rejected messages are sent in response to a Modify Order for an order which cannot be modified */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t orig_cl_ord_id[20];         /* bytes 30 to 49 */
  uint8_t modify_reject_reason;       /* byte 50 */
  uint8_t text[60];                   /* bytes 51 to 110 */
} ModifyRejectedAuEquitiesV1;

/* any Modify Rejected Au Equities V 1 at all: every byte one the checker chooses */
static void any_modify_rejected_au_equities_v1(ModifyRejectedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected Au Equities V 1 to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_au_equities_v1(const ModifyRejectedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected Au Equities V 1 off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_au_equities_v1(ModifyRejectedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected Au Equities V 1 is what was written, byte for byte */
static void equal_modify_rejected_au_equities_v1(const ModifyRejectedAuEquitiesV1 *read, const ModifyRejectedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected Au Equities V 1: written and read back, then read and written back */
static void check_modify_rejected_au_equities_v1(void) {
  ModifyRejectedAuEquitiesV1 sent;
  ModifyRejectedAuEquitiesV1 got;
  uint8_t wire[111];
  uint8_t again[111];

  any_modify_rejected_au_equities_v1(&sent);
  assert(encode_modify_rejected_au_equities_v1(&sent, wire, 0) == 111);
  assert(decode_modify_rejected_au_equities_v1(&got, wire, 0) == 111);
  equal_modify_rejected_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_au_equities_v1(&got, wire, 0) == 111);
  assert(encode_modify_rejected_au_equities_v1(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Restated Au Equities V 1: 76 bytes -------------------------------- */

/* Order restatement for an iceberg reload or a Self-Trade Protection reduction or cancellation */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t order_id[8];                /* bytes 30 to 37 */
  uint8_t order_qty[4];               /* bytes 38 to 41 */
  uint8_t price[8];                   /* bytes 42 to 49 */
  uint8_t leaves_qty[4];              /* bytes 50 to 53 */
  uint8_t secondary_order_id[8];      /* bytes 54 to 61 */
  uint8_t last_px[8];                 /* bytes 62 to 69 */
  uint8_t last_shares[4];             /* bytes 70 to 73 */
  uint8_t base_liquidity_indicator;   /* byte 74 */
  uint8_t restatement_reason;         /* byte 75 */
} OrderRestatedAuEquitiesV1;

/* any Order Restated Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_restated_au_equities_v1(OrderRestatedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->restatement_reason = arbitrary();
}

/* Order Restated Au Equities V 1 to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_order_restated_au_equities_v1(const OrderRestatedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->restatement_reason;

  return at;
}

/* Order Restated Au Equities V 1 off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_order_restated_au_equities_v1(OrderRestatedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->restatement_reason = wire[at++];

  return at;
}

/* what was read of Order Restated Au Equities V 1 is what was written, byte for byte */
static void equal_order_restated_au_equities_v1(const OrderRestatedAuEquitiesV1 *read, const OrderRestatedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->restatement_reason == written->restatement_reason);
}

/* Order Restated Au Equities V 1: written and read back, then read and written back */
static void check_order_restated_au_equities_v1(void) {
  OrderRestatedAuEquitiesV1 sent;
  OrderRestatedAuEquitiesV1 got;
  uint8_t wire[76];
  uint8_t again[76];

  any_order_restated_au_equities_v1(&sent);
  assert(encode_order_restated_au_equities_v1(&sent, wire, 0) == 76);
  assert(decode_order_restated_au_equities_v1(&got, wire, 0) == 76);
  equal_order_restated_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_order_restated_au_equities_v1(&got, wire, 0) == 76);
  assert(encode_order_restated_au_equities_v1(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Au Equities V 1: 104 bytes ------------------------------ */

/* An Order Execution is sent for each fill on an order */
typedef struct {
  uint8_t transaction_time[8];         /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];   /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];               /* bytes 10 to 29 */
  uint8_t exec_id[8];                  /* bytes 30 to 37 */
  uint8_t last_capacity;               /* byte 38 */
  uint8_t last_mkt[4];                 /* bytes 39 to 42 */
  uint8_t last_px[8];                  /* bytes 43 to 50 */
  uint8_t last_shares[4];              /* bytes 51 to 54 */
  uint8_t side;                        /* byte 55 */
  uint8_t symbol[6];                   /* bytes 56 to 61 */
  uint8_t leaves_qty[4];               /* bytes 62 to 65 */
  uint8_t secondary_order_id[8];       /* bytes 66 to 73 */
  uint8_t clearing_participant_id[4];  /* bytes 74 to 77 */
  uint8_t price_improvement[8];        /* bytes 78 to 85 */
  uint8_t transact_id[10];             /* bytes 86 to 95 */
  uint8_t on_market_cross_type;        /* byte 96 */
  uint8_t trade_report_type;           /* byte 97 */
  uint8_t base_liquidity_indicator;    /* byte 98 */
  uint8_t sub_liquidity_indicator;     /* byte 99 */
  uint8_t contra_participant_id[2];    /* bytes 100 to 101 */
  uint8_t fee_code[2];                 /* bytes 102 to 103 */
} OrderExecutionAuEquitiesV1;

/* any Order Execution Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_execution_au_equities_v1(OrderExecutionAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_mkt[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_improvement[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = arbitrary(); }
  record->on_market_cross_type = arbitrary();
  record->trade_report_type = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contra_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
}

/* Order Execution Au Equities V 1 to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_au_equities_v1(const OrderExecutionAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_mkt[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_improvement[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->transact_id[i]; }
  wire[at++] = record->on_market_cross_type;
  wire[at++] = record->trade_report_type;
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_participant_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }

  return at;
}

/* Order Execution Au Equities V 1 off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_au_equities_v1(OrderExecutionAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_mkt[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_improvement[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = wire[at++]; }
  record->on_market_cross_type = wire[at++];
  record->trade_report_type = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contra_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Au Equities V 1 is what was written, byte for byte */
static void equal_order_execution_au_equities_v1(const OrderExecutionAuEquitiesV1 *read, const OrderExecutionAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->last_mkt[i] == written->last_mkt[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_improvement[i] == written->price_improvement[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->transact_id[i] == written->transact_id[i]); }
  assert(read->on_market_cross_type == written->on_market_cross_type);
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->contra_participant_id[i] == written->contra_participant_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
}

/* Order Execution Au Equities V 1: written and read back, then read and written back */
static void check_order_execution_au_equities_v1(void) {
  OrderExecutionAuEquitiesV1 sent;
  OrderExecutionAuEquitiesV1 got;
  uint8_t wire[104];
  uint8_t again[104];

  any_order_execution_au_equities_v1(&sent);
  assert(encode_order_execution_au_equities_v1(&sent, wire, 0) == 104);
  assert(decode_order_execution_au_equities_v1(&got, wire, 0) == 104);
  equal_order_execution_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_au_equities_v1(&got, wire, 0) == 104);
  assert(encode_order_execution_au_equities_v1(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Au Equities V 1: 31 bytes ------------------------------- */

/* Order Cancelled message */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t cancel_reason;              /* byte 30 */
} OrderCancelledAuEquitiesV1;

/* any Order Cancelled Au Equities V 1 at all: every byte one the checker chooses */
static void any_order_cancelled_au_equities_v1(OrderCancelledAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Cancelled Au Equities V 1 to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_au_equities_v1(const OrderCancelledAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Cancelled Au Equities V 1 off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_au_equities_v1(OrderCancelledAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Cancelled Au Equities V 1 is what was written, byte for byte */
static void equal_order_cancelled_au_equities_v1(const OrderCancelledAuEquitiesV1 *read, const OrderCancelledAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Cancelled Au Equities V 1: written and read back, then read and written back */
static void check_order_cancelled_au_equities_v1(void) {
  OrderCancelledAuEquitiesV1 sent;
  OrderCancelledAuEquitiesV1 got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_cancelled_au_equities_v1(&sent);
  assert(encode_order_cancelled_au_equities_v1(&sent, wire, 0) == 31);
  assert(decode_order_cancelled_au_equities_v1(&got, wire, 0) == 31);
  equal_order_cancelled_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_au_equities_v1(&got, wire, 0) == 31);
  assert(encode_order_cancelled_au_equities_v1(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Au Equities V 1: 91 bytes ------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t cancel_reject_reason;       /* byte 30 */
  uint8_t text[60];                   /* bytes 31 to 90 */
} CancelRejectedAuEquitiesV1;

/* any Cancel Rejected Au Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_rejected_au_equities_v1(CancelRejectedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected Au Equities V 1 to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_au_equities_v1(const CancelRejectedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected Au Equities V 1 off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_au_equities_v1(CancelRejectedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected Au Equities V 1 is what was written, byte for byte */
static void equal_cancel_rejected_au_equities_v1(const CancelRejectedAuEquitiesV1 *read, const CancelRejectedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected Au Equities V 1: written and read back, then read and written back */
static void check_cancel_rejected_au_equities_v1(void) {
  CancelRejectedAuEquitiesV1 sent;
  CancelRejectedAuEquitiesV1 got;
  uint8_t wire[91];
  uint8_t again[91];

  any_cancel_rejected_au_equities_v1(&sent);
  assert(encode_cancel_rejected_au_equities_v1(&sent, wire, 0) == 91);
  assert(decode_cancel_rejected_au_equities_v1(&got, wire, 0) == 91);
  equal_cancel_rejected_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_au_equities_v1(&got, wire, 0) == 91);
  assert(encode_cancel_rejected_au_equities_v1(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Restatement Au Equities V 1: 73 bytes ------------------------- */

/* Order Execution Restated messages will be issued for all (unbroken) fills of MOC orders after the closing price has been determined */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t exec_id[8];                 /* bytes 30 to 37 */
  uint8_t last_px[8];                 /* bytes 38 to 45 */
  uint8_t last_shares[4];             /* bytes 46 to 49 */
  uint8_t side;                       /* byte 50 */
  uint8_t symbol[6];                  /* bytes 51 to 56 */
  uint8_t transact_id[10];            /* bytes 57 to 66 */
  uint8_t base_liquidity_indicator;   /* byte 67 */
  uint8_t contra_participant_id[2];   /* bytes 68 to 69 */
  uint8_t fee_code[2];                /* bytes 70 to 71 */
  uint8_t exec_restatement_reason;    /* byte 72 */
} ExecutionRestatementAuEquitiesV1;

/* any Execution Restatement Au Equities V 1 at all: every byte one the checker chooses */
static void any_execution_restatement_au_equities_v1(ExecutionRestatementAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->contra_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  record->exec_restatement_reason = arbitrary();
}

/* Execution Restatement Au Equities V 1 to the wire: 73 bytes from at, returning where the next byte goes */
static size_t encode_execution_restatement_au_equities_v1(const ExecutionRestatementAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->transact_id[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_participant_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  wire[at++] = record->exec_restatement_reason;

  return at;
}

/* Execution Restatement Au Equities V 1 off the wire: 73 bytes from at, returning where the next byte lies */
static size_t decode_execution_restatement_au_equities_v1(ExecutionRestatementAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->contra_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  record->exec_restatement_reason = wire[at++];

  return at;
}

/* what was read of Execution Restatement Au Equities V 1 is what was written, byte for byte */
static void equal_execution_restatement_au_equities_v1(const ExecutionRestatementAuEquitiesV1 *read, const ExecutionRestatementAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->transact_id[i] == written->transact_id[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->contra_participant_id[i] == written->contra_participant_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  assert(read->exec_restatement_reason == written->exec_restatement_reason);
}

/* Execution Restatement Au Equities V 1: written and read back, then read and written back */
static void check_execution_restatement_au_equities_v1(void) {
  ExecutionRestatementAuEquitiesV1 sent;
  ExecutionRestatementAuEquitiesV1 got;
  uint8_t wire[73];
  uint8_t again[73];

  any_execution_restatement_au_equities_v1(&sent);
  assert(encode_execution_restatement_au_equities_v1(&sent, wire, 0) == 73);
  assert(decode_execution_restatement_au_equities_v1(&got, wire, 0) == 73);
  equal_execution_restatement_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 73; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_restatement_au_equities_v1(&got, wire, 0) == 73);
  assert(encode_execution_restatement_au_equities_v1(&got, again, 0) == 73);
  for (size_t i = 0; i < 73; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement Au Equities V 1: 32 bytes ------------------------- */

/* A Purge Acknowledgment is an unsequenced message sent when a Purge Orders message requesting an order purge has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
} PurgeAcknowledgementAuEquitiesV1;

/* any Purge Acknowledgement Au Equities V 1 at all: every byte one the checker chooses */
static void any_purge_acknowledgement_au_equities_v1(PurgeAcknowledgementAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
}

/* Purge Acknowledgement Au Equities V 1 to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement_au_equities_v1(const PurgeAcknowledgementAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }

  return at;
}

/* Purge Acknowledgement Au Equities V 1 off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement_au_equities_v1(PurgeAcknowledgementAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement Au Equities V 1 is what was written, byte for byte */
static void equal_purge_acknowledgement_au_equities_v1(const PurgeAcknowledgementAuEquitiesV1 *read, const PurgeAcknowledgementAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
}

/* Purge Acknowledgement Au Equities V 1: written and read back, then read and written back */
static void check_purge_acknowledgement_au_equities_v1(void) {
  PurgeAcknowledgementAuEquitiesV1 sent;
  PurgeAcknowledgementAuEquitiesV1 got;
  uint8_t wire[32];
  uint8_t again[32];

  any_purge_acknowledgement_au_equities_v1(&sent);
  assert(encode_purge_acknowledgement_au_equities_v1(&sent, wire, 0) == 32);
  assert(decode_purge_acknowledgement_au_equities_v1(&got, wire, 0) == 32);
  equal_purge_acknowledgement_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement_au_equities_v1(&got, wire, 0) == 32);
  assert(encode_purge_acknowledgement_au_equities_v1(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected Au Equities V 1: 89 bytes -------------------------------- */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];   /* bytes 8 to 27 */
  uint8_t purge_reject_reason;  /* byte 28 */
  uint8_t text[60];             /* bytes 29 to 88 */
} PurgeRejectedAuEquitiesV1;

/* any Purge Rejected Au Equities V 1 at all: every byte one the checker chooses */
static void any_purge_rejected_au_equities_v1(PurgeRejectedAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected Au Equities V 1 to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected_au_equities_v1(const PurgeRejectedAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected Au Equities V 1 off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected_au_equities_v1(PurgeRejectedAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected Au Equities V 1 is what was written, byte for byte */
static void equal_purge_rejected_au_equities_v1(const PurgeRejectedAuEquitiesV1 *read, const PurgeRejectedAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected Au Equities V 1: written and read back, then read and written back */
static void check_purge_rejected_au_equities_v1(void) {
  PurgeRejectedAuEquitiesV1 sent;
  PurgeRejectedAuEquitiesV1 got;
  uint8_t wire[89];
  uint8_t again[89];

  any_purge_rejected_au_equities_v1(&sent);
  assert(encode_purge_rejected_au_equities_v1(&sent, wire, 0) == 89);
  assert(decode_purge_rejected_au_equities_v1(&got, wire, 0) == 89);
  equal_purge_rejected_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected_au_equities_v1(&got, wire, 0) == 89);
  assert(encode_purge_rejected_au_equities_v1(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct Au Equities V 1: 88 bytes -------------------------- */

/* Used to provide notification that a trade has been cancelled (busted) or corrected (price change only) */
typedef struct {
  uint8_t transaction_time[8];         /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];   /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];               /* bytes 10 to 29 */
  uint8_t exec_ref_id[8];              /* bytes 30 to 37 */
  uint8_t last_px[8];                  /* bytes 38 to 45 */
  uint8_t last_shares[4];              /* bytes 46 to 49 */
  uint8_t orig_time[8];                /* bytes 50 to 57 */
  uint8_t side;                        /* byte 58 */
  uint8_t symbol[6];                   /* bytes 59 to 64 */
  uint8_t clearing_participant_id[4];  /* bytes 65 to 68 */
  uint8_t transact_id[10];             /* bytes 69 to 78 */
  uint8_t corrected_price[8];          /* bytes 79 to 86 */
  uint8_t base_liquidity_indicator;    /* byte 87 */
} TradeCancelCorrectAuEquitiesV1;

/* any Trade Cancel Correct Au Equities V 1 at all: every byte one the checker chooses */
static void any_trade_cancel_correct_au_equities_v1(TradeCancelCorrectAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
}

/* Trade Cancel Correct Au Equities V 1 to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct_au_equities_v1(const TradeCancelCorrectAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->transact_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }
  wire[at++] = record->base_liquidity_indicator;

  return at;
}

/* Trade Cancel Correct Au Equities V 1 off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct_au_equities_v1(TradeCancelCorrectAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->transact_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];

  return at;
}

/* what was read of Trade Cancel Correct Au Equities V 1 is what was written, byte for byte */
static void equal_trade_cancel_correct_au_equities_v1(const TradeCancelCorrectAuEquitiesV1 *read, const TradeCancelCorrectAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->transact_id[i] == written->transact_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
}

/* Trade Cancel Correct Au Equities V 1: written and read back, then read and written back */
static void check_trade_cancel_correct_au_equities_v1(void) {
  TradeCancelCorrectAuEquitiesV1 sent;
  TradeCancelCorrectAuEquitiesV1 got;
  uint8_t wire[88];
  uint8_t again[88];

  any_trade_cancel_correct_au_equities_v1(&sent);
  assert(encode_trade_cancel_correct_au_equities_v1(&sent, wire, 0) == 88);
  assert(decode_trade_cancel_correct_au_equities_v1(&got, wire, 0) == 88);
  equal_trade_cancel_correct_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct_au_equities_v1(&got, wire, 0) == 88);
  assert(encode_trade_cancel_correct_au_equities_v1(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Au Equities V 2: 109 bytes ------------------------------- */

/* Order Modified messages are sent in response to a Modify Order, with ExpireDate for multi-day orders */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t trading_participant_id[2];  /* bytes 8 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t exec_inst;                  /* byte 30 */
  uint8_t order_qty[4];               /* bytes 31 to 34 */
  uint8_t orig_cl_ord_id[20];         /* bytes 35 to 54 */
  uint8_t price[8];                   /* bytes 55 to 62 */
  uint8_t min_qty[4];                 /* bytes 63 to 66 */
  uint8_t max_floor[4];               /* bytes 67 to 70 */
  uint8_t leaves_qty[4];              /* bytes 71 to 74 */
  uint8_t secondary_order_id[8];      /* bytes 75 to 82 */
  uint8_t short_sell_naked_qty[4];    /* bytes 83 to 86 */
  uint8_t short_sell_covered_qty[4];  /* bytes 87 to 90 */
  uint8_t short_sell_long_qty[4];     /* bytes 91 to 94 */
  uint8_t working_price[8];           /* bytes 95 to 102 */
  uint8_t base_liquidity_indicator;   /* byte 103 */
  uint8_t sub_liquidity_indicator;    /* byte 104 */
  uint8_t expire_date[4];             /* bytes 105 to 108 */
} OrderModifiedAuEquitiesV2;

/* any Order Modified Au Equities V 2 at all: every byte one the checker chooses */
static void any_order_modified_au_equities_v2(OrderModifiedAuEquitiesV2 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* Order Modified Au Equities V 2 to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_au_equities_v2(const OrderModifiedAuEquitiesV2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* Order Modified Au Equities V 2 off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_au_equities_v2(OrderModifiedAuEquitiesV2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Au Equities V 2 is what was written, byte for byte */
static void equal_order_modified_au_equities_v2(const OrderModifiedAuEquitiesV2 *read, const OrderModifiedAuEquitiesV2 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* Order Modified Au Equities V 2: written and read back, then read and written back */
static void check_order_modified_au_equities_v2(void) {
  OrderModifiedAuEquitiesV2 sent;
  OrderModifiedAuEquitiesV2 got;
  uint8_t wire[109];
  uint8_t again[109];

  any_order_modified_au_equities_v2(&sent);
  assert(encode_order_modified_au_equities_v2(&sent, wire, 0) == 109);
  assert(decode_order_modified_au_equities_v2(&got, wire, 0) == 109);
  equal_order_modified_au_equities_v2(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_au_equities_v2(&got, wire, 0) == 109);
  assert(encode_order_modified_au_equities_v2(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Carried Restatement Au Equities V 1: 182 bytes -------------------------- */

/* The Carried Restatement message is used to indicate the restoration of a multi-day GTC or GTD orders at the start of a new business day */
typedef struct {
  uint8_t transaction_time[8];            /* bytes 0 to 7 */
  uint8_t account[10];                    /* bytes 8 to 17 */
  uint8_t trading_participant_id[2];      /* bytes 18 to 19 */
  uint8_t cl_ord_id[20];                  /* bytes 20 to 39 */
  uint8_t exec_inst;                      /* byte 40 */
  uint8_t order_id[8];                    /* bytes 41 to 48 */
  uint8_t order_qty[4];                   /* bytes 49 to 52 */
  uint8_t ord_type;                       /* byte 53 */
  uint8_t price[8];                       /* bytes 54 to 61 */
  uint8_t capacity;                       /* byte 62 */
  uint8_t side;                           /* byte 63 */
  uint8_t symbol[6];                      /* bytes 64 to 69 */
  uint8_t time_in_force;                  /* byte 70 */
  uint8_t min_qty[4];                     /* bytes 71 to 74 */
  uint8_t max_floor[4];                   /* bytes 75 to 78 */
  uint8_t expire_time[8];                 /* bytes 79 to 86 */
  uint8_t clearing_participant_id[4];     /* bytes 87 to 90 */
  uint8_t clearing_account[10];           /* bytes 91 to 100 */
  uint8_t undisclosed;                    /* byte 101 */
  uint8_t client_cross_ref[15];           /* bytes 102 to 116 */
  uint8_t short_sell_naked_qty[4];        /* bytes 117 to 120 */
  uint8_t short_sell_covered_qty[4];      /* bytes 121 to 124 */
  uint8_t short_sell_long_qty[4];         /* bytes 125 to 128 */
  uint8_t risk_group_id[2];               /* bytes 129 to 130 */
  uint8_t no_trade_feat;                  /* byte 131 */
  uint8_t no_trade_key[10];               /* bytes 132 to 141 */
  uint8_t meqse;                          /* byte 142 */
  uint8_t origin_of_trans[20];            /* bytes 143 to 162 */
  uint8_t intermediary_id[10];            /* bytes 163 to 172 */
  uint8_t directed_wholesale_indicator;   /* byte 173 */
  uint8_t remove_crossing_from_clearing;  /* byte 174 */
  uint8_t broker_preferencing;            /* byte 175 */
  uint8_t routing_inst;                   /* byte 176 */
  uint8_t display_indicator;              /* byte 177 */
  uint8_t expire_date[4];                 /* bytes 178 to 181 */
} CarriedRestatementAuEquitiesV1;

/* any Carried Restatement Au Equities V 1 at all: every byte one the checker chooses */
static void any_carried_restatement_au_equities_v1(CarriedRestatementAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = arbitrary(); }
  record->undisclosed = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = arbitrary(); }
  record->meqse = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  record->directed_wholesale_indicator = arbitrary();
  record->remove_crossing_from_clearing = arbitrary();
  record->broker_preferencing = arbitrary();
  record->routing_inst = arbitrary();
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* Carried Restatement Au Equities V 1 to the wire: 182 bytes from at, returning where the next byte goes */
static size_t encode_carried_restatement_au_equities_v1(const CarriedRestatementAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->undisclosed;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_cross_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->meqse;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->origin_of_trans[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  wire[at++] = record->directed_wholesale_indicator;
  wire[at++] = record->remove_crossing_from_clearing;
  wire[at++] = record->broker_preferencing;
  wire[at++] = record->routing_inst;
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* Carried Restatement Au Equities V 1 off the wire: 182 bytes from at, returning where the next byte lies */
static size_t decode_carried_restatement_au_equities_v1(CarriedRestatementAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = wire[at++]; }
  record->undisclosed = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = wire[at++]; }
  record->meqse = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  record->directed_wholesale_indicator = wire[at++];
  record->remove_crossing_from_clearing = wire[at++];
  record->broker_preferencing = wire[at++];
  record->routing_inst = wire[at++];
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of Carried Restatement Au Equities V 1 is what was written, byte for byte */
static void equal_carried_restatement_au_equities_v1(const CarriedRestatementAuEquitiesV1 *read, const CarriedRestatementAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->capacity == written->capacity);
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->undisclosed == written->undisclosed);
  for (size_t i = 0; i < 15; i++) { assert(read->client_cross_ref[i] == written->client_cross_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 10; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->meqse == written->meqse);
  for (size_t i = 0; i < 20; i++) { assert(read->origin_of_trans[i] == written->origin_of_trans[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  assert(read->directed_wholesale_indicator == written->directed_wholesale_indicator);
  assert(read->remove_crossing_from_clearing == written->remove_crossing_from_clearing);
  assert(read->broker_preferencing == written->broker_preferencing);
  assert(read->routing_inst == written->routing_inst);
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* Carried Restatement Au Equities V 1: written and read back, then read and written back */
static void check_carried_restatement_au_equities_v1(void) {
  CarriedRestatementAuEquitiesV1 sent;
  CarriedRestatementAuEquitiesV1 got;
  uint8_t wire[182];
  uint8_t again[182];

  any_carried_restatement_au_equities_v1(&sent);
  assert(encode_carried_restatement_au_equities_v1(&sent, wire, 0) == 182);
  assert(decode_carried_restatement_au_equities_v1(&got, wire, 0) == 182);
  equal_carried_restatement_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 182; i++) { wire[i] = arbitrary(); }
  assert(decode_carried_restatement_au_equities_v1(&got, wire, 0) == 182);
  assert(encode_carried_restatement_au_equities_v1(&got, again, 0) == 182);
  for (size_t i = 0; i < 182; i++) { assert(again[i] == wire[i]); }
}

/* ---- Done For Day Au Equities V 1: 34 bytes ---------------------------------- */

/* Done For Day messages represent orders persisted during the current day session to carry over to the next session */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t symbol[6];            /* bytes 28 to 33 */
} DoneForDayAuEquitiesV1;

/* any Done For Day Au Equities V 1 at all: every byte one the checker chooses */
static void any_done_for_day_au_equities_v1(DoneForDayAuEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
}

/* Done For Day Au Equities V 1 to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_done_for_day_au_equities_v1(const DoneForDayAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Done For Day Au Equities V 1 off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_done_for_day_au_equities_v1(DoneForDayAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Done For Day Au Equities V 1 is what was written, byte for byte */
static void equal_done_for_day_au_equities_v1(const DoneForDayAuEquitiesV1 *read, const DoneForDayAuEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Done For Day Au Equities V 1: written and read back, then read and written back */
static void check_done_for_day_au_equities_v1(void) {
  DoneForDayAuEquitiesV1 sent;
  DoneForDayAuEquitiesV1 got;
  uint8_t wire[34];
  uint8_t again[34];

  any_done_for_day_au_equities_v1(&sent);
  assert(encode_done_for_day_au_equities_v1(&sent, wire, 0) == 34);
  assert(decode_done_for_day_au_equities_v1(&got, wire, 0) == 34);
  equal_done_for_day_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_done_for_day_au_equities_v1(&got, wire, 0) == 34);
  assert(encode_done_for_day_au_equities_v1(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_order_acknowledgement_au_equities_v1();
  check_order_rejected_au_equities_v1();
  check_order_modified_au_equities_v1();
  check_modify_rejected_au_equities_v1();
  check_order_restated_au_equities_v1();
  check_order_execution_au_equities_v1();
  check_order_cancelled_au_equities_v1();
  check_cancel_rejected_au_equities_v1();
  check_execution_restatement_au_equities_v1();
  check_purge_acknowledgement_au_equities_v1();
  check_purge_rejected_au_equities_v1();
  check_trade_cancel_correct_au_equities_v1();
  check_order_modified_au_equities_v2();
  check_carried_restatement_au_equities_v1();
  check_done_for_day_au_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
