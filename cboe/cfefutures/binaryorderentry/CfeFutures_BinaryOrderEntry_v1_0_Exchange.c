// cboe/cfefutures/binaryorderentry/CfeFutures_BinaryOrderEntry_v1_0_Exchange.c
/*
 * Chicago Board Options Exchange Futures Binary Order Entry
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

/* ---- Prevent Match: 3 bytes -------------------------------------------------- */

typedef struct {
  uint8_t mtp_modifier;      /* byte 0 */
  uint8_t unique_id_level;   /* byte 1 */
  uint8_t trading_group_id;  /* byte 2 */
} PreventMatch;

/* any Prevent Match at all: every byte one the checker chooses */
static void any_prevent_match(PreventMatch *record) {
  record->mtp_modifier = arbitrary();
  record->unique_id_level = arbitrary();
  record->trading_group_id = arbitrary();
}

/* Prevent Match to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_prevent_match(const PreventMatch *record, uint8_t *wire, size_t at) {
  wire[at++] = record->mtp_modifier;
  wire[at++] = record->unique_id_level;
  wire[at++] = record->trading_group_id;

  return at;
}

/* Prevent Match off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_prevent_match(PreventMatch *record, const uint8_t *wire, size_t at) {
  record->mtp_modifier = wire[at++];
  record->unique_id_level = wire[at++];
  record->trading_group_id = wire[at++];

  return at;
}

/* what was read of Prevent Match is what was written, byte for byte */
static void equal_prevent_match(const PreventMatch *read, const PreventMatch *written) {
  assert(read->mtp_modifier == written->mtp_modifier);
  assert(read->unique_id_level == written->unique_id_level);
  assert(read->trading_group_id == written->trading_group_id);
}

/* Prevent Match: written and read back, then read and written back */
static void check_prevent_match(void) {
  PreventMatch sent;
  PreventMatch got;
  uint8_t wire[3];
  uint8_t again[3];

  any_prevent_match(&sent);
  assert(encode_prevent_match(&sent, wire, 0) == 3);
  assert(decode_prevent_match(&got, wire, 0) == 3);
  equal_prevent_match(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_prevent_match(&got, wire, 0) == 3);
  assert(encode_prevent_match(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Acknowledgement Message: 161 bytes -------------------------------- */

/* Order Acknowledgement messages are sent in response to a new order message */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t order_id[8];               /* bytes 28 to 35 */
  uint8_t side;                      /* byte 36 */
  uint8_t price[8];                  /* bytes 37 to 44 */
  uint8_t ord_type;                  /* byte 45 */
  uint8_t time_in_force;             /* byte 46 */
  uint8_t min_qty[4];                /* bytes 47 to 50 */
  uint8_t symbol[8];                 /* bytes 51 to 58 */
  uint8_t capacity;                  /* byte 59 */
  uint8_t account[16];               /* bytes 60 to 75 */
  uint8_t clearing_firm[4];          /* bytes 76 to 79 */
  uint8_t clearing_account[4];       /* bytes 80 to 83 */
  uint8_t order_qty[4];              /* bytes 84 to 87 */
  PreventMatch prevent_match;        /* bytes 88 to 90 */
  uint8_t maturity_date[4];          /* bytes 91 to 94 */
  uint8_t open_close;                /* byte 95 */
  uint8_t leaves_qty[4];             /* bytes 96 to 99 */
  uint8_t base_liquidity_indicator;  /* byte 100 */
  uint8_t expire_time[8];            /* bytes 101 to 108 */
  uint8_t sub_liquidity_indicator;   /* byte 109 */
  uint8_t stop_px[8];                /* bytes 110 to 117 */
  uint8_t cmta_number[4];            /* bytes 118 to 121 */
  uint8_t cti_code;                  /* byte 122 */
  uint8_t manual_order_indicator;    /* byte 123 */
  uint8_t oeo_id[18];                /* bytes 124 to 141 */
  uint8_t cum_qty[4];                /* bytes 142 to 145 */
  uint8_t frequent_trader_id[6];     /* bytes 146 to 151 */
  uint8_t cust_order_handling_inst;  /* byte 152 */
  uint8_t request_received_time[8];  /* bytes 153 to 160 */
} OrderAcknowledgementMessage;

/* any Order Acknowledgement Message at all: every byte one the checker chooses */
static void any_order_acknowledgement_message(OrderAcknowledgementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  any_prevent_match(&record->prevent_match);
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
  record->cti_code = arbitrary();
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->cust_order_handling_inst = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Acknowledgement Message to the wire: 161 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_message(const OrderAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  at = encode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }
  wire[at++] = record->cti_code;
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->oeo_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->cust_order_handling_inst;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Acknowledgement Message off the wire: 161 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_message(OrderAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  at = decode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }
  record->cti_code = wire[at++];
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->cust_order_handling_inst = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement Message is what was written, byte for byte */
static void equal_order_acknowledgement_message(const OrderAcknowledgementMessage *read, const OrderAcknowledgementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  equal_prevent_match(&read->prevent_match, &written->prevent_match);
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
  assert(read->cti_code == written->cti_code);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 18; i++) { assert(read->oeo_id[i] == written->oeo_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Acknowledgement Message: written and read back, then read and written back */
static void check_order_acknowledgement_message(void) {
  OrderAcknowledgementMessage sent;
  OrderAcknowledgementMessage got;
  uint8_t wire[161];
  uint8_t again[161];

  any_order_acknowledgement_message(&sent);
  assert(encode_order_acknowledgement_message(&sent, wire, 0) == 161);
  assert(decode_order_acknowledgement_message(&got, wire, 0) == 161);
  equal_order_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 161; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_message(&got, wire, 0) == 161);
  assert(encode_order_acknowledgement_message(&got, again, 0) == 161);
  for (size_t i = 0; i < 161; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Message: 93 bytes ---------------------------------------- */

/* Order Rejected messages are sent in response to a New Order which must be rejected */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t clearing_firm[4];     /* bytes 28 to 31 */
  uint8_t order_reject_reason;  /* byte 32 */
  uint8_t text[60];             /* bytes 33 to 92 */
} OrderRejectedMessage;

/* any Order Rejected Message at all: every byte one the checker chooses */
static void any_order_rejected_message(OrderRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_message(const OrderRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_message(OrderRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Message is what was written, byte for byte */
static void equal_order_rejected_message(const OrderRejectedMessage *read, const OrderRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Message: written and read back, then read and written back */
static void check_order_rejected_message(void) {
  OrderRejectedMessage sent;
  OrderRejectedMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_order_rejected_message(&sent);
  assert(encode_order_rejected_message(&sent, wire, 0) == 93);
  assert(decode_order_rejected_message(&got, wire, 0) == 93);
  equal_order_rejected_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_message(&got, wire, 0) == 93);
  assert(encode_order_rejected_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Message: 101 bytes --------------------------------------- */

/* Order Modified messages are sent in response to a Modify Order to indicate that the orderhas been successfully modified */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t orig_cl_ord_id[20];        /* bytes 28 to 47 */
  uint8_t order_id[8];               /* bytes 48 to 55 */
  uint8_t clearing_firm[4];          /* bytes 56 to 59 */
  uint8_t price[8];                  /* bytes 60 to 67 */
  uint8_t ord_type;                  /* byte 68 */
  uint8_t order_qty[4];              /* bytes 69 to 72 */
  uint8_t leaves_qty[4];             /* bytes 73 to 76 */
  uint8_t base_liquidity_indicator;  /* byte 77 */
  uint8_t stop_px[8];                /* bytes 78 to 85 */
  uint8_t frequent_trader_id[6];     /* bytes 86 to 91 */
  uint8_t cust_order_handling_inst;  /* byte 92 */
  uint8_t request_received_time[8];  /* bytes 93 to 100 */
} OrderModifiedMessage;

/* any Order Modified Message at all: every byte one the checker chooses */
static void any_order_modified_message(OrderModifiedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->cust_order_handling_inst = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Modified Message to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_message(const OrderModifiedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->cust_order_handling_inst;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Modified Message off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_message(OrderModifiedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->cust_order_handling_inst = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Message is what was written, byte for byte */
static void equal_order_modified_message(const OrderModifiedMessage *read, const OrderModifiedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Modified Message: written and read back, then read and written back */
static void check_order_modified_message(void) {
  OrderModifiedMessage sent;
  OrderModifiedMessage got;
  uint8_t wire[101];
  uint8_t again[101];

  any_order_modified_message(&sent);
  assert(encode_order_modified_message(&sent, wire, 0) == 101);
  assert(decode_order_modified_message(&got, wire, 0) == 101);
  equal_order_modified_message(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_message(&got, wire, 0) == 101);
  assert(encode_order_modified_message(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Message: 113 bytes -------------------------------------- */

/* Modify Rejected messages are sent in response to a Modify Order for an order which cannot be modified */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t orig_cl_ord_id[20];    /* bytes 28 to 47 */
  uint8_t clearing_firm[4];      /* bytes 48 to 51 */
  uint8_t modify_reject_reason;  /* byte 52 */
  uint8_t text[60];              /* bytes 53 to 112 */
} ModifyRejectedMessage;

/* any Modify Rejected Message at all: every byte one the checker chooses */
static void any_modify_rejected_message(ModifyRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected Message to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_message(const ModifyRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected Message off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_message(ModifyRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected Message is what was written, byte for byte */
static void equal_modify_rejected_message(const ModifyRejectedMessage *read, const ModifyRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected Message: written and read back, then read and written back */
static void check_modify_rejected_message(void) {
  ModifyRejectedMessage sent;
  ModifyRejectedMessage got;
  uint8_t wire[113];
  uint8_t again[113];

  any_modify_rejected_message(&sent);
  assert(encode_modify_rejected_message(&sent, wire, 0) == 113);
  assert(decode_modify_rejected_message(&got, wire, 0) == 113);
  equal_modify_rejected_message(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_message(&got, wire, 0) == 113);
  assert(encode_modify_rejected_message(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Message: 91 bytes --------------------------------------- */

/* An Order Execution is sent for each fill on an order */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t exec_id[8];                /* bytes 28 to 35 */
  uint8_t last_shares[4];            /* bytes 36 to 39 */
  uint8_t last_px[8];                /* bytes 40 to 47 */
  uint8_t leaves_qty[4];             /* bytes 48 to 51 */
  uint8_t base_liquidity_indicator;  /* byte 52 */
  uint8_t sub_liquidity_indicator;   /* byte 53 */
  uint8_t side;                      /* byte 54 */
  uint8_t symbol[8];                 /* bytes 55 to 62 */
  uint8_t clearing_firm[4];          /* bytes 63 to 66 */
  uint8_t maturity_date[4];          /* bytes 67 to 70 */
  uint8_t fee_code[2];               /* bytes 71 to 72 */
  uint8_t trade_date[4];             /* bytes 73 to 76 */
  uint8_t clearing_size[4];          /* bytes 77 to 80 */
  uint8_t pending_status;            /* byte 81 */
  uint8_t multileg_reporting_type;   /* byte 82 */
  uint8_t secondary_exec_id[8];      /* bytes 83 to 90 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = arbitrary(); }
  record->pending_status = arbitrary();
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
}

/* Order Execution Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_size[i]; }
  wire[at++] = record->pending_status;
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }

  return at;
}

/* Order Execution Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = wire[at++]; }
  record->pending_status = wire[at++];
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_size[i] == written->clearing_size[i]); }
  assert(read->pending_status == written->pending_status);
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 91);
  assert(decode_order_execution_message(&got, wire, 0) == 91);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 91);
  assert(encode_order_execution_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Message: 41 bytes --------------------------------------- */

/* Order Cancelled message */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t clearing_firm[4];          /* bytes 28 to 31 */
  uint8_t cancel_reason;             /* byte 32 */
  uint8_t request_received_time[8];  /* bytes 33 to 40 */
} OrderCancelledMessage;

/* any Order Cancelled Message at all: every byte one the checker chooses */
static void any_order_cancelled_message(OrderCancelledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Cancelled Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_message(const OrderCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Cancelled Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_message(OrderCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancelled Message is what was written, byte for byte */
static void equal_order_cancelled_message(const OrderCancelledMessage *read, const OrderCancelledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Cancelled Message: written and read back, then read and written back */
static void check_order_cancelled_message(void) {
  OrderCancelledMessage sent;
  OrderCancelledMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_cancelled_message(&sent);
  assert(encode_order_cancelled_message(&sent, wire, 0) == 41);
  assert(decode_order_cancelled_message(&got, wire, 0) == 41);
  equal_order_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_message(&got, wire, 0) == 41);
  assert(encode_order_cancelled_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Message: 93 bytes --------------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t clearing_firm[4];      /* bytes 28 to 31 */
  uint8_t cancel_reject_reason;  /* byte 32 */
  uint8_t text[60];              /* bytes 33 to 92 */
} CancelRejectedMessage;

/* any Cancel Rejected Message at all: every byte one the checker chooses */
static void any_cancel_rejected_message(CancelRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_message(const CancelRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_message(CancelRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected Message is what was written, byte for byte */
static void equal_cancel_rejected_message(const CancelRejectedMessage *read, const CancelRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected Message: written and read back, then read and written back */
static void check_cancel_rejected_message(void) {
  CancelRejectedMessage sent;
  CancelRejectedMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_cancel_rejected_message(&sent);
  assert(encode_cancel_rejected_message(&sent, wire, 0) == 93);
  assert(decode_cancel_rejected_message(&got, wire, 0) == 93);
  equal_cancel_rejected_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_message(&got, wire, 0) == 93);
  assert(encode_cancel_rejected_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Acknowledgement Message: 40 bytes --------------------------- */

/* A Mass Cancel Acknowledgment is an unsequenced message sent when a Cancel Order or Purge Orders message requesting a mass cancellation has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
  uint8_t request_received_time[8];  /* bytes 32 to 39 */
} MassCancelAcknowledgementMessage;

/* any Mass Cancel Acknowledgement Message at all: every byte one the checker chooses */
static void any_mass_cancel_acknowledgement_message(MassCancelAcknowledgementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Mass Cancel Acknowledgement Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_acknowledgement_message(const MassCancelAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Mass Cancel Acknowledgement Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_acknowledgement_message(MassCancelAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Acknowledgement Message is what was written, byte for byte */
static void equal_mass_cancel_acknowledgement_message(const MassCancelAcknowledgementMessage *read, const MassCancelAcknowledgementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Mass Cancel Acknowledgement Message: written and read back, then read and written back */
static void check_mass_cancel_acknowledgement_message(void) {
  MassCancelAcknowledgementMessage sent;
  MassCancelAcknowledgementMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_mass_cancel_acknowledgement_message(&sent);
  assert(encode_mass_cancel_acknowledgement_message(&sent, wire, 0) == 40);
  assert(decode_mass_cancel_acknowledgement_message(&got, wire, 0) == 40);
  equal_mass_cancel_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_acknowledgement_message(&got, wire, 0) == 40);
  assert(encode_mass_cancel_acknowledgement_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Rejected Message: 89 bytes ---------------------------------- */

/* A Mass Cancel Rejected message is sent in response to a Mass Cancel Order message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];         /* bytes 8 to 27 */
  uint8_t mass_cancel_reject_reason;  /* byte 28 */
  uint8_t text[60];                   /* bytes 29 to 88 */
} MassCancelRejectedMessage;

/* any Mass Cancel Rejected Message at all: every byte one the checker chooses */
static void any_mass_cancel_rejected_message(MassCancelRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->mass_cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Mass Cancel Rejected Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_rejected_message(const MassCancelRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->mass_cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Mass Cancel Rejected Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_rejected_message(MassCancelRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->mass_cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Rejected Message is what was written, byte for byte */
static void equal_mass_cancel_rejected_message(const MassCancelRejectedMessage *read, const MassCancelRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Mass Cancel Rejected Message: written and read back, then read and written back */
static void check_mass_cancel_rejected_message(void) {
  MassCancelRejectedMessage sent;
  MassCancelRejectedMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_mass_cancel_rejected_message(&sent);
  assert(encode_mass_cancel_rejected_message(&sent, wire, 0) == 89);
  assert(decode_mass_cancel_rejected_message(&got, wire, 0) == 89);
  equal_mass_cancel_rejected_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_rejected_message(&got, wire, 0) == 89);
  assert(encode_mass_cancel_rejected_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement Message: 40 bytes --------------------------------- */

/* A Purge Acknowledgment is an unsequenced message sent when a Purge Orders message requesting an order purge has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
  uint8_t request_received_time[8];  /* bytes 32 to 39 */
} PurgeAcknowledgementMessage;

/* any Purge Acknowledgement Message at all: every byte one the checker chooses */
static void any_purge_acknowledgement_message(PurgeAcknowledgementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Purge Acknowledgement Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement_message(const PurgeAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Purge Acknowledgement Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement_message(PurgeAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement Message is what was written, byte for byte */
static void equal_purge_acknowledgement_message(const PurgeAcknowledgementMessage *read, const PurgeAcknowledgementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Purge Acknowledgement Message: written and read back, then read and written back */
static void check_purge_acknowledgement_message(void) {
  PurgeAcknowledgementMessage sent;
  PurgeAcknowledgementMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_purge_acknowledgement_message(&sent);
  assert(encode_purge_acknowledgement_message(&sent, wire, 0) == 40);
  assert(decode_purge_acknowledgement_message(&got, wire, 0) == 40);
  equal_purge_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement_message(&got, wire, 0) == 40);
  assert(encode_purge_acknowledgement_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected Message: 89 bytes ---------------------------------------- */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];   /* bytes 8 to 27 */
  uint8_t purge_reject_reason;  /* byte 28 */
  uint8_t text[60];             /* bytes 29 to 88 */
} PurgeRejectedMessage;

/* any Purge Rejected Message at all: every byte one the checker chooses */
static void any_purge_rejected_message(PurgeRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected_message(const PurgeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected_message(PurgeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected Message is what was written, byte for byte */
static void equal_purge_rejected_message(const PurgeRejectedMessage *read, const PurgeRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected Message: written and read back, then read and written back */
static void check_purge_rejected_message(void) {
  PurgeRejectedMessage sent;
  PurgeRejectedMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_purge_rejected_message(&sent);
  assert(encode_purge_rejected_message(&sent, wire, 0) == 89);
  assert(decode_purge_rejected_message(&got, wire, 0) == 89);
  equal_purge_rejected_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected_message(&got, wire, 0) == 89);
  assert(encode_purge_rejected_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Or Correct Message: 92 bytes ------------------------------- */

/* Used to provide notification that a trade has been cancelled or corrected */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t exec_ref_id[8];            /* bytes 28 to 35 */
  uint8_t side;                      /* byte 36 */
  uint8_t base_liquidity_indicator;  /* byte 37 */
  uint8_t clearing_firm[4];          /* bytes 38 to 41 */
  uint8_t clearing_account[4];       /* bytes 42 to 45 */
  uint8_t last_shares[4];            /* bytes 46 to 49 */
  uint8_t last_px[8];                /* bytes 50 to 57 */
  uint8_t corrected_price[8];        /* bytes 58 to 65 */
  uint8_t orig_time[8];              /* bytes 66 to 73 */
  uint8_t symbol[8];                 /* bytes 74 to 81 */
  uint8_t capacity;                  /* byte 82 */
  uint8_t maturity_date[4];          /* bytes 83 to 86 */
  uint8_t open_close;                /* byte 87 */
  uint8_t cmta_number[4];            /* bytes 88 to 91 */
} TradeCancelOrCorrectMessage;

/* any Trade Cancel Or Correct Message at all: every byte one the checker chooses */
static void any_trade_cancel_or_correct_message(TradeCancelOrCorrectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
}

/* Trade Cancel Or Correct Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_or_correct_message(const TradeCancelOrCorrectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }

  return at;
}

/* Trade Cancel Or Correct Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_or_correct_message(TradeCancelOrCorrectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Or Correct Message is what was written, byte for byte */
static void equal_trade_cancel_or_correct_message(const TradeCancelOrCorrectMessage *read, const TradeCancelOrCorrectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  assert(read->side == written->side);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
}

/* Trade Cancel Or Correct Message: written and read back, then read and written back */
static void check_trade_cancel_or_correct_message(void) {
  TradeCancelOrCorrectMessage sent;
  TradeCancelOrCorrectMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_trade_cancel_or_correct_message(&sent);
  assert(encode_trade_cancel_or_correct_message(&sent, wire, 0) == 92);
  assert(decode_trade_cancel_or_correct_message(&got, wire, 0) == 92);
  equal_trade_cancel_or_correct_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_or_correct_message(&got, wire, 0) == 92);
  assert(encode_trade_cancel_or_correct_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tas Restatement Message: 104 bytes -------------------------------------- */

/* A Tas Restatement is sent post-settlement time for each TAS execution during the associated business day to communicate the updated Price and Symbol associated with the cleared execution */
typedef struct {
  uint8_t transaction_time[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];            /* bytes 8 to 27 */
  uint8_t clearing_firm[4];         /* bytes 28 to 31 */
  uint8_t exec_id[8];               /* bytes 32 to 39 */
  uint8_t side;                     /* byte 40 */
  uint8_t price[8];                 /* bytes 41 to 48 */
  uint8_t symbol[8];                /* bytes 49 to 56 */
  uint8_t maturity_date[4];         /* bytes 57 to 60 */
  uint8_t last_shares[4];           /* bytes 61 to 64 */
  uint8_t last_px[8];               /* bytes 65 to 72 */
  uint8_t fee_code[2];              /* bytes 73 to 74 */
  uint8_t trade_date[4];            /* bytes 75 to 78 */
  uint8_t clearing_price[8];        /* bytes 79 to 86 */
  uint8_t clearing_symbol[8];       /* bytes 87 to 94 */
  uint8_t multileg_reporting_type;  /* byte 95 */
  uint8_t secondary_exec_id[8];     /* bytes 96 to 103 */
} TasRestatementMessage;

/* any Tas Restatement Message at all: every byte one the checker chooses */
static void any_tas_restatement_message(TasRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = arbitrary(); }
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
}

/* Tas Restatement Message to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_tas_restatement_message(const TasRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_symbol[i]; }
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }

  return at;
}

/* Tas Restatement Message off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_tas_restatement_message(TasRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = wire[at++]; }
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Tas Restatement Message is what was written, byte for byte */
static void equal_tas_restatement_message(const TasRestatementMessage *read, const TasRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_price[i] == written->clearing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_symbol[i] == written->clearing_symbol[i]); }
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
}

/* Tas Restatement Message: written and read back, then read and written back */
static void check_tas_restatement_message(void) {
  TasRestatementMessage sent;
  TasRestatementMessage got;
  uint8_t wire[104];
  uint8_t again[104];

  any_tas_restatement_message(&sent);
  assert(encode_tas_restatement_message(&sent, wire, 0) == 104);
  assert(decode_tas_restatement_message(&got, wire, 0) == 104);
  equal_tas_restatement_message(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_tas_restatement_message(&got, wire, 0) == 104);
  assert(encode_tas_restatement_message(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Variance Restatement Message: 108 bytes --------------------------------- */

/* A Variance Restatement is sent post-settlement time for each VA and VAO execution during the associated business day to communicate updated Price, Size and Symbol associated with the cleared execution */
typedef struct {
  uint8_t transaction_time[8];      /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];            /* bytes 8 to 27 */
  uint8_t clearing_firm[4];         /* bytes 28 to 31 */
  uint8_t exec_id[8];               /* bytes 32 to 39 */
  uint8_t side;                     /* byte 40 */
  uint8_t price[8];                 /* bytes 41 to 48 */
  uint8_t symbol[8];                /* bytes 49 to 56 */
  uint8_t maturity_date[4];         /* bytes 57 to 60 */
  uint8_t last_shares[4];           /* bytes 61 to 64 */
  uint8_t last_px[8];               /* bytes 65 to 72 */
  uint8_t fee_code[2];              /* bytes 73 to 74 */
  uint8_t trade_date[4];            /* bytes 75 to 78 */
  uint8_t clearing_price[8];        /* bytes 79 to 86 */
  uint8_t clearing_size[4];         /* bytes 87 to 90 */
  uint8_t clearing_symbol[8];       /* bytes 91 to 98 */
  uint8_t multileg_reporting_type;  /* byte 99 */
  uint8_t secondary_exec_id[8];     /* bytes 100 to 107 */
} VarianceRestatementMessage;

/* any Variance Restatement Message at all: every byte one the checker chooses */
static void any_variance_restatement_message(VarianceRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = arbitrary(); }
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
}

/* Variance Restatement Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_variance_restatement_message(const VarianceRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_symbol[i]; }
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }

  return at;
}

/* Variance Restatement Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_variance_restatement_message(VarianceRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = wire[at++]; }
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Variance Restatement Message is what was written, byte for byte */
static void equal_variance_restatement_message(const VarianceRestatementMessage *read, const VarianceRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_price[i] == written->clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_size[i] == written->clearing_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_symbol[i] == written->clearing_symbol[i]); }
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
}

/* Variance Restatement Message: written and read back, then read and written back */
static void check_variance_restatement_message(void) {
  VarianceRestatementMessage sent;
  VarianceRestatementMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_variance_restatement_message(&sent);
  assert(encode_variance_restatement_message(&sent, wire, 0) == 108);
  assert(decode_variance_restatement_message(&got, wire, 0) == 108);
  equal_variance_restatement_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_variance_restatement_message(&got, wire, 0) == 108);
  assert(encode_variance_restatement_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Update Rejected Message: 25 bytes --------------------------------- */

/* Quote Update Rejected messages are sent in response to a Quote Update or Quote Update Option message when the entire quote block is rejected by the order handler */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t quote_reject_reason;  /* byte 24 */
} QuoteUpdateRejectedMessage;

/* any Quote Update Rejected Message at all: every byte one the checker chooses */
static void any_quote_update_rejected_message(QuoteUpdateRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  record->quote_reject_reason = arbitrary();
}

/* Quote Update Rejected Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_quote_update_rejected_message(const QuoteUpdateRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  wire[at++] = record->quote_reject_reason;

  return at;
}

/* Quote Update Rejected Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_quote_update_rejected_message(QuoteUpdateRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  record->quote_reject_reason = wire[at++];

  return at;
}

/* what was read of Quote Update Rejected Message is what was written, byte for byte */
static void equal_quote_update_rejected_message(const QuoteUpdateRejectedMessage *read, const QuoteUpdateRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  assert(read->quote_reject_reason == written->quote_reject_reason);
}

/* Quote Update Rejected Message: written and read back, then read and written back */
static void check_quote_update_rejected_message(void) {
  QuoteUpdateRejectedMessage sent;
  QuoteUpdateRejectedMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_quote_update_rejected_message(&sent);
  assert(encode_quote_update_rejected_message(&sent, wire, 0) == 25);
  assert(decode_quote_update_rejected_message(&got, wire, 0) == 25);
  equal_quote_update_rejected_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_update_rejected_message(&got, wire, 0) == 25);
  assert(encode_quote_update_rejected_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Restated Message: 52 bytes ---------------------------------------- */

/* Quote Restated messages are sent to inform the TPH that an order has been asynchronously modified for some reason by CFE */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t order_id[8];          /* bytes 24 to 31 */
  uint8_t leaves_qty[4];        /* bytes 32 to 35 */
  uint8_t working_price[8];     /* bytes 36 to 43 */
  uint8_t quote_symbol[6];      /* bytes 44 to 49 */
  uint8_t side;                 /* byte 50 */
  uint8_t restatement_reason;   /* byte 51 */
} QuoteRestatedMessage;

/* any Quote Restated Message at all: every byte one the checker chooses */
static void any_quote_restated_message(QuoteRestatedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->restatement_reason = arbitrary();
}

/* Quote Restated Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_quote_restated_message(const QuoteRestatedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  wire[at++] = record->side;
  wire[at++] = record->restatement_reason;

  return at;
}

/* Quote Restated Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_quote_restated_message(QuoteRestatedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  record->side = wire[at++];
  record->restatement_reason = wire[at++];

  return at;
}

/* what was read of Quote Restated Message is what was written, byte for byte */
static void equal_quote_restated_message(const QuoteRestatedMessage *read, const QuoteRestatedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  assert(read->side == written->side);
  assert(read->restatement_reason == written->restatement_reason);
}

/* Quote Restated Message: written and read back, then read and written back */
static void check_quote_restated_message(void) {
  QuoteRestatedMessage sent;
  QuoteRestatedMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_quote_restated_message(&sent);
  assert(encode_quote_restated_message(&sent, wire, 0) == 52);
  assert(decode_quote_restated_message(&got, wire, 0) == 52);
  equal_quote_restated_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_restated_message(&got, wire, 0) == 52);
  assert(encode_quote_restated_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Execution Message: 71 bytes --------------------------------------- */

/* A Quote Execution message is used to indicate an execution has occurred on a resting quote */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t quote_update_id[16];       /* bytes 8 to 23 */
  uint8_t order_id[8];               /* bytes 24 to 31 */
  uint8_t exec_id[8];                /* bytes 32 to 39 */
  uint8_t quote_symbol[6];           /* bytes 40 to 45 */
  uint8_t clearing_firm[4];          /* bytes 46 to 49 */
  uint8_t last_shares[4];            /* bytes 50 to 53 */
  uint8_t last_px[8];                /* bytes 54 to 61 */
  uint8_t leaves_qty[4];             /* bytes 62 to 65 */
  uint8_t side;                      /* byte 66 */
  uint8_t base_liquidity_indicator;  /* byte 67 */
  uint8_t sub_liquidity_indicator;   /* byte 68 */
  uint8_t fee_code[2];               /* bytes 69 to 70 */
} QuoteExecutionMessage;

/* any Quote Execution Message at all: every byte one the checker chooses */
static void any_quote_execution_message(QuoteExecutionMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
}

/* Quote Execution Message to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_quote_execution_message(const QuoteExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }

  return at;
}

/* Quote Execution Message off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_quote_execution_message(QuoteExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Execution Message is what was written, byte for byte */
static void equal_quote_execution_message(const QuoteExecutionMessage *read, const QuoteExecutionMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->side == written->side);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
}

/* Quote Execution Message: written and read back, then read and written back */
static void check_quote_execution_message(void) {
  QuoteExecutionMessage sent;
  QuoteExecutionMessage got;
  uint8_t wire[71];
  uint8_t again[71];

  any_quote_execution_message(&sent);
  assert(encode_quote_execution_message(&sent, wire, 0) == 71);
  assert(decode_quote_execution_message(&got, wire, 0) == 71);
  equal_quote_execution_message(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_execution_message(&got, wire, 0) == 71);
  assert(encode_quote_execution_message(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancelled Message: 40 bytes --------------------------------------- */

/* A Quote Cancelled message will be sent to indicate an unsolicited cancellation of a quote entered with a Quote Update message */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t order_id[8];          /* bytes 24 to 31 */
  uint8_t quote_symbol[6];      /* bytes 32 to 37 */
  uint8_t side;                 /* byte 38 */
  uint8_t cancel_reason;        /* byte 39 */
} QuoteCancelledMessage;

/* any Quote Cancelled Message at all: every byte one the checker chooses */
static void any_quote_cancelled_message(QuoteCancelledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->cancel_reason = arbitrary();
}

/* Quote Cancelled Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancelled_message(const QuoteCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  wire[at++] = record->side;
  wire[at++] = record->cancel_reason;

  return at;
}

/* Quote Cancelled Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancelled_message(QuoteCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  record->side = wire[at++];
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Quote Cancelled Message is what was written, byte for byte */
static void equal_quote_cancelled_message(const QuoteCancelledMessage *read, const QuoteCancelledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  assert(read->side == written->side);
  assert(read->cancel_reason == written->cancel_reason);
}

/* Quote Cancelled Message: written and read back, then read and written back */
static void check_quote_cancelled_message(void) {
  QuoteCancelledMessage sent;
  QuoteCancelledMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_quote_cancelled_message(&sent);
  assert(encode_quote_cancelled_message(&sent, wire, 0) == 40);
  assert(decode_quote_cancelled_message(&got, wire, 0) == 40);
  equal_quote_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancelled_message(&got, wire, 0) == 40);
  assert(encode_quote_cancelled_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tas Quote Restatement Message: 54 bytes --------------------------------- */

/* A TAS Quote Restatement is sent post-settlement time for each TAS quote execution during the associated business day to communicate the updated Price and Symbol associated with the cleared execution */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t exec_id[8];           /* bytes 24 to 31 */
  uint8_t quote_symbol[6];      /* bytes 32 to 37 */
  uint8_t clearing_symbol[8];   /* bytes 38 to 45 */
  uint8_t clearing_price[8];    /* bytes 46 to 53 */
} TasQuoteRestatementMessage;

/* any Tas Quote Restatement Message at all: every byte one the checker chooses */
static void any_tas_quote_restatement_message(TasQuoteRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = arbitrary(); }
}

/* Tas Quote Restatement Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_tas_quote_restatement_message(const TasQuoteRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_price[i]; }

  return at;
}

/* Tas Quote Restatement Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_tas_quote_restatement_message(TasQuoteRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Tas Quote Restatement Message is what was written, byte for byte */
static void equal_tas_quote_restatement_message(const TasQuoteRestatementMessage *read, const TasQuoteRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_symbol[i] == written->clearing_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_price[i] == written->clearing_price[i]); }
}

/* Tas Quote Restatement Message: written and read back, then read and written back */
static void check_tas_quote_restatement_message(void) {
  TasQuoteRestatementMessage sent;
  TasQuoteRestatementMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_tas_quote_restatement_message(&sent);
  assert(encode_tas_quote_restatement_message(&sent, wire, 0) == 54);
  assert(decode_tas_quote_restatement_message(&got, wire, 0) == 54);
  equal_tas_quote_restatement_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_tas_quote_restatement_message(&got, wire, 0) == 54);
  assert(encode_tas_quote_restatement_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Variance Quote Restatement Message: 58 bytes ---------------------------- */

/* A Variance Quote Restatement is sent post-settlement time for each VA and VAO execution during the associated business day to communicate updated Price, Size, and Symbol values associated with the cleared execution */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t exec_id[8];           /* bytes 24 to 31 */
  uint8_t quote_symbol[6];      /* bytes 32 to 37 */
  uint8_t clearing_symbol[8];   /* bytes 38 to 45 */
  uint8_t clearing_price[8];    /* bytes 46 to 53 */
  uint8_t clearing_size[4];     /* bytes 54 to 57 */
} VarianceQuoteRestatementMessage;

/* any Variance Quote Restatement Message at all: every byte one the checker chooses */
static void any_variance_quote_restatement_message(VarianceQuoteRestatementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = arbitrary(); }
}

/* Variance Quote Restatement Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_variance_quote_restatement_message(const VarianceQuoteRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_size[i]; }

  return at;
}

/* Variance Quote Restatement Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_variance_quote_restatement_message(VarianceQuoteRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = wire[at++]; }

  return at;
}

/* what was read of Variance Quote Restatement Message is what was written, byte for byte */
static void equal_variance_quote_restatement_message(const VarianceQuoteRestatementMessage *read, const VarianceQuoteRestatementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_symbol[i] == written->clearing_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_price[i] == written->clearing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_size[i] == written->clearing_size[i]); }
}

/* Variance Quote Restatement Message: written and read back, then read and written back */
static void check_variance_quote_restatement_message(void) {
  VarianceQuoteRestatementMessage sent;
  VarianceQuoteRestatementMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_variance_quote_restatement_message(&sent);
  assert(encode_variance_quote_restatement_message(&sent, wire, 0) == 58);
  assert(decode_variance_quote_restatement_message(&got, wire, 0) == 58);
  equal_variance_quote_restatement_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_variance_quote_restatement_message(&got, wire, 0) == 58);
  assert(encode_variance_quote_restatement_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Acknowledgement Message: 25 bytes ---------------------------- */

/* Response to a Reset Risk request */
typedef struct {
  uint8_t risk_status_id[16];        /* bytes 0 to 15 */
  uint8_t risk_reset_result;         /* byte 16 */
  uint8_t request_received_time[8];  /* bytes 17 to 24 */
} ResetRiskAcknowledgementMessage;

/* any Reset Risk Acknowledgement Message at all: every byte one the checker chooses */
static void any_reset_risk_acknowledgement_message(ResetRiskAcknowledgementMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  record->risk_reset_result = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Reset Risk Acknowledgement Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_acknowledgement_message(const ResetRiskAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  wire[at++] = record->risk_reset_result;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Reset Risk Acknowledgement Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_acknowledgement_message(ResetRiskAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  record->risk_reset_result = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Acknowledgement Message is what was written, byte for byte */
static void equal_reset_risk_acknowledgement_message(const ResetRiskAcknowledgementMessage *read, const ResetRiskAcknowledgementMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  assert(read->risk_reset_result == written->risk_reset_result);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Reset Risk Acknowledgement Message: written and read back, then read and written back */
static void check_reset_risk_acknowledgement_message(void) {
  ResetRiskAcknowledgementMessage sent;
  ResetRiskAcknowledgementMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_reset_risk_acknowledgement_message(&sent);
  assert(encode_reset_risk_acknowledgement_message(&sent, wire, 0) == 25);
  assert(decode_reset_risk_acknowledgement_message(&got, wire, 0) == 25);
  equal_reset_risk_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_acknowledgement_message(&got, wire, 0) == 25);
  assert(encode_reset_risk_acknowledgement_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_prevent_match();
  check_order_acknowledgement_message();
  check_order_rejected_message();
  check_order_modified_message();
  check_modify_rejected_message();
  check_order_execution_message();
  check_order_cancelled_message();
  check_cancel_rejected_message();
  check_mass_cancel_acknowledgement_message();
  check_mass_cancel_rejected_message();
  check_purge_acknowledgement_message();
  check_purge_rejected_message();
  check_trade_cancel_or_correct_message();
  check_tas_restatement_message();
  check_variance_restatement_message();
  check_quote_update_rejected_message();
  check_quote_restated_message();
  check_quote_execution_message();
  check_quote_cancelled_message();
  check_tas_quote_restatement_message();
  check_variance_quote_restatement_message();
  check_reset_risk_acknowledgement_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
