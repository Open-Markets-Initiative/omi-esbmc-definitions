// cboe/cfefutures/binaryorderentry/CfeFutures_BinaryOrderEntry_v1_1_20_Exchange.c
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

/* ---- Order Acknowledgement: 161 bytes ---------------------------------------- */

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
} OrderAcknowledgement;

/* any Order Acknowledgement at all: every byte one the checker chooses */
static void any_order_acknowledgement(OrderAcknowledgement *record) {
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

/* Order Acknowledgement to the wire: 161 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement(const OrderAcknowledgement *record, uint8_t *wire, size_t at) {
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

/* Order Acknowledgement off the wire: 161 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement(OrderAcknowledgement *record, const uint8_t *wire, size_t at) {
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

/* what was read of Order Acknowledgement is what was written, byte for byte */
static void equal_order_acknowledgement(const OrderAcknowledgement *read, const OrderAcknowledgement *written) {
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

/* Order Acknowledgement: written and read back, then read and written back */
static void check_order_acknowledgement(void) {
  OrderAcknowledgement sent;
  OrderAcknowledgement got;
  uint8_t wire[161];
  uint8_t again[161];

  any_order_acknowledgement(&sent);
  assert(encode_order_acknowledgement(&sent, wire, 0) == 161);
  assert(decode_order_acknowledgement(&got, wire, 0) == 161);
  equal_order_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 161; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement(&got, wire, 0) == 161);
  assert(encode_order_acknowledgement(&got, again, 0) == 161);
  for (size_t i = 0; i < 161; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected: 93 bytes ------------------------------------------------ */

/* Order Rejected messages are sent in response to a New Order which must be rejected */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t clearing_firm[4];     /* bytes 28 to 31 */
  uint8_t order_reject_reason;  /* byte 32 */
  uint8_t text[60];             /* bytes 33 to 92 */
} OrderRejected;

/* any Order Rejected at all: every byte one the checker chooses */
static void any_order_rejected(OrderRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected(const OrderRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected(OrderRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected is what was written, byte for byte */
static void equal_order_rejected(const OrderRejected *read, const OrderRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected: written and read back, then read and written back */
static void check_order_rejected(void) {
  OrderRejected sent;
  OrderRejected got;
  uint8_t wire[93];
  uint8_t again[93];

  any_order_rejected(&sent);
  assert(encode_order_rejected(&sent, wire, 0) == 93);
  assert(decode_order_rejected(&got, wire, 0) == 93);
  equal_order_rejected(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected(&got, wire, 0) == 93);
  assert(encode_order_rejected(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified: 101 bytes ----------------------------------------------- */

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
} OrderModified;

/* any Order Modified at all: every byte one the checker chooses */
static void any_order_modified(OrderModified *record) {
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

/* Order Modified to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_order_modified(const OrderModified *record, uint8_t *wire, size_t at) {
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

/* Order Modified off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_order_modified(OrderModified *record, const uint8_t *wire, size_t at) {
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

/* what was read of Order Modified is what was written, byte for byte */
static void equal_order_modified(const OrderModified *read, const OrderModified *written) {
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

/* Order Modified: written and read back, then read and written back */
static void check_order_modified(void) {
  OrderModified sent;
  OrderModified got;
  uint8_t wire[101];
  uint8_t again[101];

  any_order_modified(&sent);
  assert(encode_order_modified(&sent, wire, 0) == 101);
  assert(decode_order_modified(&got, wire, 0) == 101);
  equal_order_modified(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified(&got, wire, 0) == 101);
  assert(encode_order_modified(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected: 113 bytes ---------------------------------------------- */

/* Modify Rejected messages are sent in response to a Modify Order for an order which cannot be modified */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t orig_cl_ord_id[20];    /* bytes 28 to 47 */
  uint8_t clearing_firm[4];      /* bytes 48 to 51 */
  uint8_t modify_reject_reason;  /* byte 52 */
  uint8_t text[60];              /* bytes 53 to 112 */
} ModifyRejected;

/* any Modify Rejected at all: every byte one the checker chooses */
static void any_modify_rejected(ModifyRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected(const ModifyRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected(ModifyRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected is what was written, byte for byte */
static void equal_modify_rejected(const ModifyRejected *read, const ModifyRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected: written and read back, then read and written back */
static void check_modify_rejected(void) {
  ModifyRejected sent;
  ModifyRejected got;
  uint8_t wire[113];
  uint8_t again[113];

  any_modify_rejected(&sent);
  assert(encode_modify_rejected(&sent, wire, 0) == 113);
  assert(decode_modify_rejected(&got, wire, 0) == 113);
  equal_modify_rejected(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected(&got, wire, 0) == 113);
  assert(encode_modify_rejected(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution: 91 bytes ----------------------------------------------- */

/* AnOrder Executionis sent for each fill on an order */
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
} OrderExecution;

/* any Order Execution at all: every byte one the checker chooses */
static void any_order_execution(OrderExecution *record) {
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

/* Order Execution to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_order_execution(const OrderExecution *record, uint8_t *wire, size_t at) {
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

/* Order Execution off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_order_execution(OrderExecution *record, const uint8_t *wire, size_t at) {
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

/* what was read of Order Execution is what was written, byte for byte */
static void equal_order_execution(const OrderExecution *read, const OrderExecution *written) {
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

/* Order Execution: written and read back, then read and written back */
static void check_order_execution(void) {
  OrderExecution sent;
  OrderExecution got;
  uint8_t wire[91];
  uint8_t again[91];

  any_order_execution(&sent);
  assert(encode_order_execution(&sent, wire, 0) == 91);
  assert(decode_order_execution(&got, wire, 0) == 91);
  equal_order_execution(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution(&got, wire, 0) == 91);
  assert(encode_order_execution(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Option: 103 bytes --------------------------------------- */

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
  uint8_t security_desc[16];         /* bytes 67 to 82 */
  uint8_t fee_code[2];               /* bytes 83 to 84 */
  uint8_t trade_date[4];             /* bytes 85 to 88 */
  uint8_t clearing_size[4];          /* bytes 89 to 92 */
  uint8_t pending_status;            /* byte 93 */
  uint8_t multileg_reporting_type;   /* byte 94 */
  uint8_t secondary_exec_id[8];      /* bytes 95 to 102 */
} OrderExecutionOption;

/* any Order Execution Option at all: every byte one the checker chooses */
static void any_order_execution_option(OrderExecutionOption *record) {
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
  for (size_t i = 0; i < 16; i++) { record->security_desc[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = arbitrary(); }
  record->pending_status = arbitrary();
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
}

/* Order Execution Option to the wire: 103 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_option(const OrderExecutionOption *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->security_desc[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_size[i]; }
  wire[at++] = record->pending_status;
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }

  return at;
}

/* Order Execution Option off the wire: 103 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_option(OrderExecutionOption *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 16; i++) { record->security_desc[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_size[i] = wire[at++]; }
  record->pending_status = wire[at++];
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Option is what was written, byte for byte */
static void equal_order_execution_option(const OrderExecutionOption *read, const OrderExecutionOption *written) {
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
  for (size_t i = 0; i < 16; i++) { assert(read->security_desc[i] == written->security_desc[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_size[i] == written->clearing_size[i]); }
  assert(read->pending_status == written->pending_status);
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
}

/* Order Execution Option: written and read back, then read and written back */
static void check_order_execution_option(void) {
  OrderExecutionOption sent;
  OrderExecutionOption got;
  uint8_t wire[103];
  uint8_t again[103];

  any_order_execution_option(&sent);
  assert(encode_order_execution_option(&sent, wire, 0) == 103);
  assert(decode_order_execution_option(&got, wire, 0) == 103);
  equal_order_execution_option(&got, &sent);

  for (size_t i = 0; i < 103; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_option(&got, wire, 0) == 103);
  assert(encode_order_execution_option(&got, again, 0) == 103);
  for (size_t i = 0; i < 103; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled: 41 bytes ----------------------------------------------- */

/* Order Cancelled message */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t clearing_firm[4];          /* bytes 28 to 31 */
  uint8_t cancel_reason;             /* byte 32 */
  uint8_t request_received_time[8];  /* bytes 33 to 40 */
} OrderCancelled;

/* any Order Cancelled at all: every byte one the checker chooses */
static void any_order_cancelled(OrderCancelled *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Cancelled to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled(const OrderCancelled *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Cancelled off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled(OrderCancelled *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancelled is what was written, byte for byte */
static void equal_order_cancelled(const OrderCancelled *read, const OrderCancelled *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Cancelled: written and read back, then read and written back */
static void check_order_cancelled(void) {
  OrderCancelled sent;
  OrderCancelled got;
  uint8_t wire[41];
  uint8_t again[41];

  any_order_cancelled(&sent);
  assert(encode_order_cancelled(&sent, wire, 0) == 41);
  assert(decode_order_cancelled(&got, wire, 0) == 41);
  equal_order_cancelled(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled(&got, wire, 0) == 41);
  assert(encode_order_cancelled(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected: 93 bytes ----------------------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t clearing_firm[4];      /* bytes 28 to 31 */
  uint8_t cancel_reject_reason;  /* byte 32 */
  uint8_t text[60];              /* bytes 33 to 92 */
} CancelRejected;

/* any Cancel Rejected at all: every byte one the checker chooses */
static void any_cancel_rejected(CancelRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected(const CancelRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected(CancelRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected is what was written, byte for byte */
static void equal_cancel_rejected(const CancelRejected *read, const CancelRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected: written and read back, then read and written back */
static void check_cancel_rejected(void) {
  CancelRejected sent;
  CancelRejected got;
  uint8_t wire[93];
  uint8_t again[93];

  any_cancel_rejected(&sent);
  assert(encode_cancel_rejected(&sent, wire, 0) == 93);
  assert(decode_cancel_rejected(&got, wire, 0) == 93);
  equal_cancel_rejected(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected(&got, wire, 0) == 93);
  assert(encode_cancel_rejected(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Acknowledgement: 40 bytes ----------------------------------- */

/* A Mass Cancel Acknowledgment is an unsequenced message sent when a Cancel Order or Purge Orders message requesting a mass cancellation has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
  uint8_t request_received_time[8];  /* bytes 32 to 39 */
} MassCancelAcknowledgement;

/* any Mass Cancel Acknowledgement at all: every byte one the checker chooses */
static void any_mass_cancel_acknowledgement(MassCancelAcknowledgement *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Mass Cancel Acknowledgement to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_acknowledgement(const MassCancelAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Mass Cancel Acknowledgement off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_acknowledgement(MassCancelAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Acknowledgement is what was written, byte for byte */
static void equal_mass_cancel_acknowledgement(const MassCancelAcknowledgement *read, const MassCancelAcknowledgement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Mass Cancel Acknowledgement: written and read back, then read and written back */
static void check_mass_cancel_acknowledgement(void) {
  MassCancelAcknowledgement sent;
  MassCancelAcknowledgement got;
  uint8_t wire[40];
  uint8_t again[40];

  any_mass_cancel_acknowledgement(&sent);
  assert(encode_mass_cancel_acknowledgement(&sent, wire, 0) == 40);
  assert(decode_mass_cancel_acknowledgement(&got, wire, 0) == 40);
  equal_mass_cancel_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_acknowledgement(&got, wire, 0) == 40);
  assert(encode_mass_cancel_acknowledgement(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Rejected: 89 bytes ------------------------------------------ */

/* A Mass Cancel Rejected message is sent in response to a Mass Cancel Order message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];        /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];         /* bytes 8 to 27 */
  uint8_t mass_cancel_reject_reason;  /* byte 28 */
  uint8_t text[60];                   /* bytes 29 to 88 */
} MassCancelRejected;

/* any Mass Cancel Rejected at all: every byte one the checker chooses */
static void any_mass_cancel_rejected(MassCancelRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->mass_cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Mass Cancel Rejected to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_rejected(const MassCancelRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->mass_cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Mass Cancel Rejected off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_rejected(MassCancelRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->mass_cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Rejected is what was written, byte for byte */
static void equal_mass_cancel_rejected(const MassCancelRejected *read, const MassCancelRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Mass Cancel Rejected: written and read back, then read and written back */
static void check_mass_cancel_rejected(void) {
  MassCancelRejected sent;
  MassCancelRejected got;
  uint8_t wire[89];
  uint8_t again[89];

  any_mass_cancel_rejected(&sent);
  assert(encode_mass_cancel_rejected(&sent, wire, 0) == 89);
  assert(decode_mass_cancel_rejected(&got, wire, 0) == 89);
  equal_mass_cancel_rejected(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_rejected(&got, wire, 0) == 89);
  assert(encode_mass_cancel_rejected(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement: 40 bytes ----------------------------------------- */

/* A Purge Acknowledgment is an unsequenced message sent when a Purge Orders message requesting an order purge has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
  uint8_t request_received_time[8];  /* bytes 32 to 39 */
} PurgeAcknowledgement;

/* any Purge Acknowledgement at all: every byte one the checker chooses */
static void any_purge_acknowledgement(PurgeAcknowledgement *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Purge Acknowledgement to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement(const PurgeAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Purge Acknowledgement off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement(PurgeAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement is what was written, byte for byte */
static void equal_purge_acknowledgement(const PurgeAcknowledgement *read, const PurgeAcknowledgement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Purge Acknowledgement: written and read back, then read and written back */
static void check_purge_acknowledgement(void) {
  PurgeAcknowledgement sent;
  PurgeAcknowledgement got;
  uint8_t wire[40];
  uint8_t again[40];

  any_purge_acknowledgement(&sent);
  assert(encode_purge_acknowledgement(&sent, wire, 0) == 40);
  assert(decode_purge_acknowledgement(&got, wire, 0) == 40);
  equal_purge_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement(&got, wire, 0) == 40);
  assert(encode_purge_acknowledgement(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected: 89 bytes ------------------------------------------------ */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];   /* bytes 8 to 27 */
  uint8_t purge_reject_reason;  /* byte 28 */
  uint8_t text[60];             /* bytes 29 to 88 */
} PurgeRejected;

/* any Purge Rejected at all: every byte one the checker chooses */
static void any_purge_rejected(PurgeRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected(const PurgeRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected(PurgeRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected is what was written, byte for byte */
static void equal_purge_rejected(const PurgeRejected *read, const PurgeRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected: written and read back, then read and written back */
static void check_purge_rejected(void) {
  PurgeRejected sent;
  PurgeRejected got;
  uint8_t wire[89];
  uint8_t again[89];

  any_purge_rejected(&sent);
  assert(encode_purge_rejected(&sent, wire, 0) == 89);
  assert(decode_purge_rejected(&got, wire, 0) == 89);
  equal_purge_rejected(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected(&got, wire, 0) == 89);
  assert(encode_purge_rejected(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct: 92 bytes ------------------------------------------ */

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
} TradeCancelCorrect;

/* any Trade Cancel Correct at all: every byte one the checker chooses */
static void any_trade_cancel_correct(TradeCancelCorrect *record) {
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

/* Trade Cancel Correct to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct(const TradeCancelCorrect *record, uint8_t *wire, size_t at) {
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

/* Trade Cancel Correct off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct(TradeCancelCorrect *record, const uint8_t *wire, size_t at) {
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

/* what was read of Trade Cancel Correct is what was written, byte for byte */
static void equal_trade_cancel_correct(const TradeCancelCorrect *read, const TradeCancelCorrect *written) {
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

/* Trade Cancel Correct: written and read back, then read and written back */
static void check_trade_cancel_correct(void) {
  TradeCancelCorrect sent;
  TradeCancelCorrect got;
  uint8_t wire[92];
  uint8_t again[92];

  any_trade_cancel_correct(&sent);
  assert(encode_trade_cancel_correct(&sent, wire, 0) == 92);
  assert(decode_trade_cancel_correct(&got, wire, 0) == 92);
  equal_trade_cancel_correct(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct(&got, wire, 0) == 92);
  assert(encode_trade_cancel_correct(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct Option: 104 bytes ---------------------------------- */

/* Used to provide notification that an option trade has been cancelled or corrected */
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
  uint8_t security_desc[16];         /* bytes 83 to 98 */
  uint8_t open_close;                /* byte 99 */
  uint8_t cmta_number[4];            /* bytes 100 to 103 */
} TradeCancelCorrectOption;

/* any Trade Cancel Correct Option at all: every byte one the checker chooses */
static void any_trade_cancel_correct_option(TradeCancelCorrectOption *record) {
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
  for (size_t i = 0; i < 16; i++) { record->security_desc[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
}

/* Trade Cancel Correct Option to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct_option(const TradeCancelCorrectOption *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->security_desc[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }

  return at;
}

/* Trade Cancel Correct Option off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct_option(TradeCancelCorrectOption *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 16; i++) { record->security_desc[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Correct Option is what was written, byte for byte */
static void equal_trade_cancel_correct_option(const TradeCancelCorrectOption *read, const TradeCancelCorrectOption *written) {
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
  for (size_t i = 0; i < 16; i++) { assert(read->security_desc[i] == written->security_desc[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
}

/* Trade Cancel Correct Option: written and read back, then read and written back */
static void check_trade_cancel_correct_option(void) {
  TradeCancelCorrectOption sent;
  TradeCancelCorrectOption got;
  uint8_t wire[104];
  uint8_t again[104];

  any_trade_cancel_correct_option(&sent);
  assert(encode_trade_cancel_correct_option(&sent, wire, 0) == 104);
  assert(decode_trade_cancel_correct_option(&got, wire, 0) == 104);
  equal_trade_cancel_correct_option(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct_option(&got, wire, 0) == 104);
  assert(encode_trade_cancel_correct_option(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tas Restatement: 104 bytes ---------------------------------------------- */

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
} TasRestatement;

/* any Tas Restatement at all: every byte one the checker chooses */
static void any_tas_restatement(TasRestatement *record) {
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

/* Tas Restatement to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_tas_restatement(const TasRestatement *record, uint8_t *wire, size_t at) {
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

/* Tas Restatement off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_tas_restatement(TasRestatement *record, const uint8_t *wire, size_t at) {
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

/* what was read of Tas Restatement is what was written, byte for byte */
static void equal_tas_restatement(const TasRestatement *read, const TasRestatement *written) {
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

/* Tas Restatement: written and read back, then read and written back */
static void check_tas_restatement(void) {
  TasRestatement sent;
  TasRestatement got;
  uint8_t wire[104];
  uint8_t again[104];

  any_tas_restatement(&sent);
  assert(encode_tas_restatement(&sent, wire, 0) == 104);
  assert(decode_tas_restatement(&got, wire, 0) == 104);
  equal_tas_restatement(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_tas_restatement(&got, wire, 0) == 104);
  assert(encode_tas_restatement(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Update Rejected: 25 bytes ----------------------------------------- */

/* Quote Update Rejected messages are sent in response to a Quote Update or Quote Update Option message when the entire quote block is rejected by the order handler */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t quote_reject_reason;  /* byte 24 */
} QuoteUpdateRejected;

/* any Quote Update Rejected at all: every byte one the checker chooses */
static void any_quote_update_rejected(QuoteUpdateRejected *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  record->quote_reject_reason = arbitrary();
}

/* Quote Update Rejected to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_quote_update_rejected(const QuoteUpdateRejected *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  wire[at++] = record->quote_reject_reason;

  return at;
}

/* Quote Update Rejected off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_quote_update_rejected(QuoteUpdateRejected *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  record->quote_reject_reason = wire[at++];

  return at;
}

/* what was read of Quote Update Rejected is what was written, byte for byte */
static void equal_quote_update_rejected(const QuoteUpdateRejected *read, const QuoteUpdateRejected *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  assert(read->quote_reject_reason == written->quote_reject_reason);
}

/* Quote Update Rejected: written and read back, then read and written back */
static void check_quote_update_rejected(void) {
  QuoteUpdateRejected sent;
  QuoteUpdateRejected got;
  uint8_t wire[25];
  uint8_t again[25];

  any_quote_update_rejected(&sent);
  assert(encode_quote_update_rejected(&sent, wire, 0) == 25);
  assert(decode_quote_update_rejected(&got, wire, 0) == 25);
  equal_quote_update_rejected(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_update_rejected(&got, wire, 0) == 25);
  assert(encode_quote_update_rejected(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Restated: 52 bytes ------------------------------------------------ */

/* Quote Restatedmessages are sent to inform the TPH that an order has been asynchronously modified for some reason by CFE */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t order_id[8];          /* bytes 24 to 31 */
  uint8_t leaves_qty[4];        /* bytes 32 to 35 */
  uint8_t working_price[8];     /* bytes 36 to 43 */
  uint8_t quote_symbol[6];      /* bytes 44 to 49 */
  uint8_t side;                 /* byte 50 */
  uint8_t restatement_reason;   /* byte 51 */
} QuoteRestated;

/* any Quote Restated at all: every byte one the checker chooses */
static void any_quote_restated(QuoteRestated *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->restatement_reason = arbitrary();
}

/* Quote Restated to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_quote_restated(const QuoteRestated *record, uint8_t *wire, size_t at) {
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

/* Quote Restated off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_quote_restated(QuoteRestated *record, const uint8_t *wire, size_t at) {
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

/* what was read of Quote Restated is what was written, byte for byte */
static void equal_quote_restated(const QuoteRestated *read, const QuoteRestated *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  assert(read->side == written->side);
  assert(read->restatement_reason == written->restatement_reason);
}

/* Quote Restated: written and read back, then read and written back */
static void check_quote_restated(void) {
  QuoteRestated sent;
  QuoteRestated got;
  uint8_t wire[52];
  uint8_t again[52];

  any_quote_restated(&sent);
  assert(encode_quote_restated(&sent, wire, 0) == 52);
  assert(decode_quote_restated(&got, wire, 0) == 52);
  equal_quote_restated(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_restated(&got, wire, 0) == 52);
  assert(encode_quote_restated(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Execution: 71 bytes ----------------------------------------------- */

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
} QuoteExecution;

/* any Quote Execution at all: every byte one the checker chooses */
static void any_quote_execution(QuoteExecution *record) {
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

/* Quote Execution to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_quote_execution(const QuoteExecution *record, uint8_t *wire, size_t at) {
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

/* Quote Execution off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_quote_execution(QuoteExecution *record, const uint8_t *wire, size_t at) {
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

/* what was read of Quote Execution is what was written, byte for byte */
static void equal_quote_execution(const QuoteExecution *read, const QuoteExecution *written) {
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

/* Quote Execution: written and read back, then read and written back */
static void check_quote_execution(void) {
  QuoteExecution sent;
  QuoteExecution got;
  uint8_t wire[71];
  uint8_t again[71];

  any_quote_execution(&sent);
  assert(encode_quote_execution(&sent, wire, 0) == 71);
  assert(decode_quote_execution(&got, wire, 0) == 71);
  equal_quote_execution(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_execution(&got, wire, 0) == 71);
  assert(encode_quote_execution(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancelled: 40 bytes ----------------------------------------------- */

/* A Quote Cancelled message will be sent to indicate an unsolicited cancellation of a quote entered with a Quote Update message */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t order_id[8];          /* bytes 24 to 31 */
  uint8_t quote_symbol[6];      /* bytes 32 to 37 */
  uint8_t side;                 /* byte 38 */
  uint8_t cancel_reason;        /* byte 39 */
} QuoteCancelled;

/* any Quote Cancelled at all: every byte one the checker chooses */
static void any_quote_cancelled(QuoteCancelled *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->cancel_reason = arbitrary();
}

/* Quote Cancelled to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancelled(const QuoteCancelled *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  wire[at++] = record->side;
  wire[at++] = record->cancel_reason;

  return at;
}

/* Quote Cancelled off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancelled(QuoteCancelled *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  record->side = wire[at++];
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Quote Cancelled is what was written, byte for byte */
static void equal_quote_cancelled(const QuoteCancelled *read, const QuoteCancelled *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  assert(read->side == written->side);
  assert(read->cancel_reason == written->cancel_reason);
}

/* Quote Cancelled: written and read back, then read and written back */
static void check_quote_cancelled(void) {
  QuoteCancelled sent;
  QuoteCancelled got;
  uint8_t wire[40];
  uint8_t again[40];

  any_quote_cancelled(&sent);
  assert(encode_quote_cancelled(&sent, wire, 0) == 40);
  assert(decode_quote_cancelled(&got, wire, 0) == 40);
  equal_quote_cancelled(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancelled(&got, wire, 0) == 40);
  assert(encode_quote_cancelled(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tas Quote Restatement: 54 bytes ----------------------------------------- */

/* A TAS Quote Restatement is sent post-settlement time for each TAS quote execution during the associated business day to communicate the updated Price and Symbol associated with the cleared execution */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t quote_update_id[16];  /* bytes 8 to 23 */
  uint8_t exec_id[8];           /* bytes 24 to 31 */
  uint8_t quote_symbol[6];      /* bytes 32 to 37 */
  uint8_t clearing_symbol[8];   /* bytes 38 to 45 */
  uint8_t clearing_price[8];    /* bytes 46 to 53 */
} TasQuoteRestatement;

/* any Tas Quote Restatement at all: every byte one the checker chooses */
static void any_tas_quote_restatement(TasQuoteRestatement *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = arbitrary(); }
}

/* Tas Quote Restatement to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_tas_quote_restatement(const TasQuoteRestatement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->clearing_price[i]; }

  return at;
}

/* Tas Quote Restatement off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_tas_quote_restatement(TasQuoteRestatement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->clearing_price[i] = wire[at++]; }

  return at;
}

/* what was read of Tas Quote Restatement is what was written, byte for byte */
static void equal_tas_quote_restatement(const TasQuoteRestatement *read, const TasQuoteRestatement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_symbol[i] == written->clearing_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->clearing_price[i] == written->clearing_price[i]); }
}

/* Tas Quote Restatement: written and read back, then read and written back */
static void check_tas_quote_restatement(void) {
  TasQuoteRestatement sent;
  TasQuoteRestatement got;
  uint8_t wire[54];
  uint8_t again[54];

  any_tas_quote_restatement(&sent);
  assert(encode_tas_quote_restatement(&sent, wire, 0) == 54);
  assert(decode_tas_quote_restatement(&got, wire, 0) == 54);
  equal_tas_quote_restatement(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_tas_quote_restatement(&got, wire, 0) == 54);
  assert(encode_tas_quote_restatement(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Acknowledgement: 25 bytes ------------------------------------ */

/* Response to a Reset Risk request */
typedef struct {
  uint8_t risk_status_id[16];        /* bytes 0 to 15 */
  uint8_t risk_reset_result;         /* byte 16 */
  uint8_t request_received_time[8];  /* bytes 17 to 24 */
} ResetRiskAcknowledgement;

/* any Reset Risk Acknowledgement at all: every byte one the checker chooses */
static void any_reset_risk_acknowledgement(ResetRiskAcknowledgement *record) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  record->risk_reset_result = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Reset Risk Acknowledgement to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_acknowledgement(const ResetRiskAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  wire[at++] = record->risk_reset_result;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Reset Risk Acknowledgement off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_acknowledgement(ResetRiskAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  record->risk_reset_result = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Acknowledgement is what was written, byte for byte */
static void equal_reset_risk_acknowledgement(const ResetRiskAcknowledgement *read, const ResetRiskAcknowledgement *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  assert(read->risk_reset_result == written->risk_reset_result);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Reset Risk Acknowledgement: written and read back, then read and written back */
static void check_reset_risk_acknowledgement(void) {
  ResetRiskAcknowledgement sent;
  ResetRiskAcknowledgement got;
  uint8_t wire[25];
  uint8_t again[25];

  any_reset_risk_acknowledgement(&sent);
  assert(encode_reset_risk_acknowledgement(&sent, wire, 0) == 25);
  assert(decode_reset_risk_acknowledgement(&got, wire, 0) == 25);
  equal_reset_risk_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_acknowledgement(&got, wire, 0) == 25);
  assert(encode_reset_risk_acknowledgement(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Complex Instrument Rejected Option: 93 bytes ------------------------ */

/* The New Complex Instrument Rejected indicates that a requested complex strategy has been rejected */
typedef struct {
  uint8_t transaction_time[8];               /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];                     /* bytes 8 to 27 */
  uint8_t clearing_firm[4];                  /* bytes 28 to 31 */
  uint8_t complex_instrument_reject_reason;  /* byte 32 */
  uint8_t text[60];                          /* bytes 33 to 92 */
} NewComplexInstrumentRejectedOption;

/* any New Complex Instrument Rejected Option at all: every byte one the checker chooses */
static void any_new_complex_instrument_rejected_option(NewComplexInstrumentRejectedOption *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->complex_instrument_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* New Complex Instrument Rejected Option to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_new_complex_instrument_rejected_option(const NewComplexInstrumentRejectedOption *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->complex_instrument_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* New Complex Instrument Rejected Option off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_new_complex_instrument_rejected_option(NewComplexInstrumentRejectedOption *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->complex_instrument_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of New Complex Instrument Rejected Option is what was written, byte for byte */
static void equal_new_complex_instrument_rejected_option(const NewComplexInstrumentRejectedOption *read, const NewComplexInstrumentRejectedOption *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->complex_instrument_reject_reason == written->complex_instrument_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* New Complex Instrument Rejected Option: written and read back, then read and written back */
static void check_new_complex_instrument_rejected_option(void) {
  NewComplexInstrumentRejectedOption sent;
  NewComplexInstrumentRejectedOption got;
  uint8_t wire[93];
  uint8_t again[93];

  any_new_complex_instrument_rejected_option(&sent);
  assert(encode_new_complex_instrument_rejected_option(&sent, wire, 0) == 93);
  assert(decode_new_complex_instrument_rejected_option(&got, wire, 0) == 93);
  equal_new_complex_instrument_rejected_option(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_new_complex_instrument_rejected_option(&got, wire, 0) == 93);
  assert(encode_new_complex_instrument_rejected_option(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_prevent_match();
  check_order_acknowledgement();
  check_order_rejected();
  check_order_modified();
  check_modify_rejected();
  check_order_execution();
  check_order_execution_option();
  check_order_cancelled();
  check_cancel_rejected();
  check_mass_cancel_acknowledgement();
  check_mass_cancel_rejected();
  check_purge_acknowledgement();
  check_purge_rejected();
  check_trade_cancel_correct();
  check_trade_cancel_correct_option();
  check_tas_restatement();
  check_quote_update_rejected();
  check_quote_restated();
  check_quote_execution();
  check_quote_cancelled();
  check_tas_quote_restatement();
  check_reset_risk_acknowledgement();
  check_new_complex_instrument_rejected_option();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
