// cboe/cxjequities/binaryorderentry/CxjEquities_BinaryOrderEntry_v1_0_12_Exchange.c
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

/* ---- Order Acknowledgement Jp Equities V 1: 104 bytes ------------------------ */

/* Order Acknowledgement messages are sent in response to a New Order message */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t account[10];               /* bytes 8 to 17 */
  uint8_t trading_firm[4];           /* bytes 18 to 21 */
  uint8_t cl_ord_id[20];             /* bytes 22 to 41 */
  uint8_t order_id[8];               /* bytes 42 to 49 */
  uint8_t order_qty[4];              /* bytes 50 to 53 */
  uint8_t ord_type;                  /* byte 54 */
  uint8_t price[8];                  /* bytes 55 to 62 */
  uint8_t capacity;                  /* byte 63 */
  uint8_t side;                      /* byte 64 */
  uint8_t symbol[8];                 /* bytes 65 to 72 */
  uint8_t time_in_force;             /* byte 73 */
  uint8_t expire_time[8];            /* bytes 74 to 81 */
  uint8_t cash_margin;               /* byte 82 */
  uint8_t risk_group_id[2];          /* bytes 83 to 84 */
  uint8_t no_trade_feat;             /* byte 85 */
  uint8_t no_trade_key[10];          /* bytes 86 to 95 */
  uint8_t posting_instruction;       /* byte 96 */
  uint8_t order_classification;      /* byte 97 */
  uint8_t margin_transaction_type;   /* byte 98 */
  uint8_t base_liquidity_indicator;  /* byte 99 */
  uint8_t company_id[4];             /* bytes 100 to 103 */
} OrderAcknowledgementJpEquitiesV1;

/* any Order Acknowledgement Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_acknowledgement_jp_equities_v1(OrderAcknowledgementJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  record->cash_margin = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = arbitrary(); }
  record->posting_instruction = arbitrary();
  record->order_classification = arbitrary();
  record->margin_transaction_type = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = arbitrary(); }
}

/* Order Acknowledgement Jp Equities V 1 to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_jp_equities_v1(const OrderAcknowledgementJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  wire[at++] = record->cash_margin;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->posting_instruction;
  wire[at++] = record->order_classification;
  wire[at++] = record->margin_transaction_type;
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->company_id[i]; }

  return at;
}

/* Order Acknowledgement Jp Equities V 1 off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_jp_equities_v1(OrderAcknowledgementJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  record->cash_margin = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = wire[at++]; }
  record->posting_instruction = wire[at++];
  record->order_classification = wire[at++];
  record->margin_transaction_type = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement Jp Equities V 1 is what was written, byte for byte */
static void equal_order_acknowledgement_jp_equities_v1(const OrderAcknowledgementJpEquitiesV1 *read, const OrderAcknowledgementJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->capacity == written->capacity);
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  assert(read->cash_margin == written->cash_margin);
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 10; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->posting_instruction == written->posting_instruction);
  assert(read->order_classification == written->order_classification);
  assert(read->margin_transaction_type == written->margin_transaction_type);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->company_id[i] == written->company_id[i]); }
}

/* Order Acknowledgement Jp Equities V 1: written and read back, then read and written back */
static void check_order_acknowledgement_jp_equities_v1(void) {
  OrderAcknowledgementJpEquitiesV1 sent;
  OrderAcknowledgementJpEquitiesV1 got;
  uint8_t wire[104];
  uint8_t again[104];

  any_order_acknowledgement_jp_equities_v1(&sent);
  assert(encode_order_acknowledgement_jp_equities_v1(&sent, wire, 0) == 104);
  assert(decode_order_acknowledgement_jp_equities_v1(&got, wire, 0) == 104);
  equal_order_acknowledgement_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_jp_equities_v1(&got, wire, 0) == 104);
  assert(encode_order_acknowledgement_jp_equities_v1(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Jp Equities V 1: 93 bytes -------------------------------- */

/* Order Rejected messages are sent in response to a New Order which must be rejected */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t trading_firm[4];      /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];        /* bytes 12 to 31 */
  uint8_t order_reject_reason;  /* byte 32 */
  uint8_t text[60];             /* bytes 33 to 92 */
} OrderRejectedJpEquitiesV1;

/* any Order Rejected Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_rejected_jp_equities_v1(OrderRejectedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Jp Equities V 1 to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_jp_equities_v1(const OrderRejectedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Jp Equities V 1 off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_jp_equities_v1(OrderRejectedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Jp Equities V 1 is what was written, byte for byte */
static void equal_order_rejected_jp_equities_v1(const OrderRejectedJpEquitiesV1 *read, const OrderRejectedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Jp Equities V 1: written and read back, then read and written back */
static void check_order_rejected_jp_equities_v1(void) {
  OrderRejectedJpEquitiesV1 sent;
  OrderRejectedJpEquitiesV1 got;
  uint8_t wire[93];
  uint8_t again[93];

  any_order_rejected_jp_equities_v1(&sent);
  assert(encode_order_rejected_jp_equities_v1(&sent, wire, 0) == 93);
  assert(decode_order_rejected_jp_equities_v1(&got, wire, 0) == 93);
  equal_order_rejected_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_jp_equities_v1(&got, wire, 0) == 93);
  assert(encode_order_rejected_jp_equities_v1(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Jp Equities V 1: 81 bytes -------------------------------- */

/* Order Modified messages are sent in response to a Modify Order to indicate that the order has been successfully modified */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t trading_firm[4];           /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];             /* bytes 12 to 31 */
  uint8_t order_qty[4];              /* bytes 32 to 35 */
  uint8_t orig_cl_ord_id[20];        /* bytes 36 to 55 */
  uint8_t order_id[8];               /* bytes 56 to 63 */
  uint8_t price[8];                  /* bytes 64 to 71 */
  uint8_t leaves_qty[4];             /* bytes 72 to 75 */
  uint8_t base_liquidity_indicator;  /* byte 76 */
  uint8_t company_id[4];             /* bytes 77 to 80 */
} OrderModifiedJpEquitiesV1;

/* any Order Modified Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_modified_jp_equities_v1(OrderModifiedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = arbitrary(); }
}

/* Order Modified Jp Equities V 1 to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_jp_equities_v1(const OrderModifiedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->company_id[i]; }

  return at;
}

/* Order Modified Jp Equities V 1 off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_jp_equities_v1(OrderModifiedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Jp Equities V 1 is what was written, byte for byte */
static void equal_order_modified_jp_equities_v1(const OrderModifiedJpEquitiesV1 *read, const OrderModifiedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->company_id[i] == written->company_id[i]); }
}

/* Order Modified Jp Equities V 1: written and read back, then read and written back */
static void check_order_modified_jp_equities_v1(void) {
  OrderModifiedJpEquitiesV1 sent;
  OrderModifiedJpEquitiesV1 got;
  uint8_t wire[81];
  uint8_t again[81];

  any_order_modified_jp_equities_v1(&sent);
  assert(encode_order_modified_jp_equities_v1(&sent, wire, 0) == 81);
  assert(decode_order_modified_jp_equities_v1(&got, wire, 0) == 81);
  equal_order_modified_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_jp_equities_v1(&got, wire, 0) == 81);
  assert(encode_order_modified_jp_equities_v1(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Jp Equities V 1: 113 bytes ------------------------------ */

/* Modify Rejected messages are sent in response to a Modify Order for an order which cannot be modified */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t trading_firm[4];       /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];         /* bytes 12 to 31 */
  uint8_t orig_cl_ord_id[20];    /* bytes 32 to 51 */
  uint8_t modify_reject_reason;  /* byte 52 */
  uint8_t text[60];              /* bytes 53 to 112 */
} ModifyRejectedJpEquitiesV1;

/* any Modify Rejected Jp Equities V 1 at all: every byte one the checker chooses */
static void any_modify_rejected_jp_equities_v1(ModifyRejectedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected Jp Equities V 1 to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_jp_equities_v1(const ModifyRejectedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected Jp Equities V 1 off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_jp_equities_v1(ModifyRejectedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected Jp Equities V 1 is what was written, byte for byte */
static void equal_modify_rejected_jp_equities_v1(const ModifyRejectedJpEquitiesV1 *read, const ModifyRejectedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected Jp Equities V 1: written and read back, then read and written back */
static void check_modify_rejected_jp_equities_v1(void) {
  ModifyRejectedJpEquitiesV1 sent;
  ModifyRejectedJpEquitiesV1 got;
  uint8_t wire[113];
  uint8_t again[113];

  any_modify_rejected_jp_equities_v1(&sent);
  assert(encode_modify_rejected_jp_equities_v1(&sent, wire, 0) == 113);
  assert(decode_modify_rejected_jp_equities_v1(&got, wire, 0) == 113);
  equal_modify_rejected_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_jp_equities_v1(&got, wire, 0) == 113);
  assert(encode_modify_rejected_jp_equities_v1(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Restated Jp Equities V 1: 78 bytes -------------------------------- */

/* If an order is cancelled or reduced due to Self-Trade Protection instructions, the order will be restated with reductions to OrderQty and/or LeavesQty */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t trading_firm[4];           /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];             /* bytes 12 to 31 */
  uint8_t order_id[8];               /* bytes 32 to 39 */
  uint8_t order_qty[4];              /* bytes 40 to 43 */
  uint8_t price[8];                  /* bytes 44 to 51 */
  uint8_t leaves_qty[4];             /* bytes 52 to 55 */
  uint8_t secondary_order_id[8];     /* bytes 56 to 63 */
  uint8_t last_px[8];                /* bytes 64 to 71 */
  uint8_t last_shares[4];            /* bytes 72 to 75 */
  uint8_t base_liquidity_indicator;  /* byte 76 */
  uint8_t restatement_reason;        /* byte 77 */
} OrderRestatedJpEquitiesV1;

/* any Order Restated Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_restated_jp_equities_v1(OrderRestatedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
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

/* Order Restated Jp Equities V 1 to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_order_restated_jp_equities_v1(const OrderRestatedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
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

/* Order Restated Jp Equities V 1 off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_order_restated_jp_equities_v1(OrderRestatedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
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

/* what was read of Order Restated Jp Equities V 1 is what was written, byte for byte */
static void equal_order_restated_jp_equities_v1(const OrderRestatedJpEquitiesV1 *read, const OrderRestatedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
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

/* Order Restated Jp Equities V 1: written and read back, then read and written back */
static void check_order_restated_jp_equities_v1(void) {
  OrderRestatedJpEquitiesV1 sent;
  OrderRestatedJpEquitiesV1 got;
  uint8_t wire[78];
  uint8_t again[78];

  any_order_restated_jp_equities_v1(&sent);
  assert(encode_order_restated_jp_equities_v1(&sent, wire, 0) == 78);
  assert(decode_order_restated_jp_equities_v1(&got, wire, 0) == 78);
  equal_order_restated_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_order_restated_jp_equities_v1(&got, wire, 0) == 78);
  assert(encode_order_restated_jp_equities_v1(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Jp Equities V 1: 67 bytes ------------------------------- */

/* An Order Execution is sent for each fill on an order */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t trading_firm[4];           /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];             /* bytes 12 to 31 */
  uint8_t exec_id[8];                /* bytes 32 to 39 */
  uint8_t last_capacity;             /* byte 40 */
  uint8_t last_px[8];                /* bytes 41 to 48 */
  uint8_t last_shares[4];            /* bytes 49 to 52 */
  uint8_t side;                      /* byte 53 */
  uint8_t symbol[8];                 /* bytes 54 to 61 */
  uint8_t leaves_qty[4];             /* bytes 62 to 65 */
  uint8_t base_liquidity_indicator;  /* byte 66 */
} OrderExecutionJpEquitiesV1;

/* any Order Execution Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_execution_jp_equities_v1(OrderExecutionJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
}

/* Order Execution Jp Equities V 1 to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_jp_equities_v1(const OrderExecutionJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;

  return at;
}

/* Order Execution Jp Equities V 1 off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_jp_equities_v1(OrderExecutionJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];

  return at;
}

/* what was read of Order Execution Jp Equities V 1 is what was written, byte for byte */
static void equal_order_execution_jp_equities_v1(const OrderExecutionJpEquitiesV1 *read, const OrderExecutionJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
}

/* Order Execution Jp Equities V 1: written and read back, then read and written back */
static void check_order_execution_jp_equities_v1(void) {
  OrderExecutionJpEquitiesV1 sent;
  OrderExecutionJpEquitiesV1 got;
  uint8_t wire[67];
  uint8_t again[67];

  any_order_execution_jp_equities_v1(&sent);
  assert(encode_order_execution_jp_equities_v1(&sent, wire, 0) == 67);
  assert(decode_order_execution_jp_equities_v1(&got, wire, 0) == 67);
  equal_order_execution_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_jp_equities_v1(&got, wire, 0) == 67);
  assert(encode_order_execution_jp_equities_v1(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Jp Equities V 1: 33 bytes ------------------------------- */

/* Order Cancelled message */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t trading_firm[4];      /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];        /* bytes 12 to 31 */
  uint8_t cancel_reason;        /* byte 32 */
} OrderCancelledJpEquitiesV1;

/* any Order Cancelled Jp Equities V 1 at all: every byte one the checker chooses */
static void any_order_cancelled_jp_equities_v1(OrderCancelledJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Cancelled Jp Equities V 1 to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_jp_equities_v1(const OrderCancelledJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Cancelled Jp Equities V 1 off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_jp_equities_v1(OrderCancelledJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Cancelled Jp Equities V 1 is what was written, byte for byte */
static void equal_order_cancelled_jp_equities_v1(const OrderCancelledJpEquitiesV1 *read, const OrderCancelledJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Cancelled Jp Equities V 1: written and read back, then read and written back */
static void check_order_cancelled_jp_equities_v1(void) {
  OrderCancelledJpEquitiesV1 sent;
  OrderCancelledJpEquitiesV1 got;
  uint8_t wire[33];
  uint8_t again[33];

  any_order_cancelled_jp_equities_v1(&sent);
  assert(encode_order_cancelled_jp_equities_v1(&sent, wire, 0) == 33);
  assert(decode_order_cancelled_jp_equities_v1(&got, wire, 0) == 33);
  equal_order_cancelled_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_jp_equities_v1(&got, wire, 0) == 33);
  assert(encode_order_cancelled_jp_equities_v1(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Jp Equities V 1: 93 bytes ------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t trading_firm[4];       /* bytes 8 to 11 */
  uint8_t cl_ord_id[20];         /* bytes 12 to 31 */
  uint8_t cancel_reject_reason;  /* byte 32 */
  uint8_t text[60];              /* bytes 33 to 92 */
} CancelRejectedJpEquitiesV1;

/* any Cancel Rejected Jp Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_rejected_jp_equities_v1(CancelRejectedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected Jp Equities V 1 to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_jp_equities_v1(const CancelRejectedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected Jp Equities V 1 off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_jp_equities_v1(CancelRejectedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected Jp Equities V 1 is what was written, byte for byte */
static void equal_cancel_rejected_jp_equities_v1(const CancelRejectedJpEquitiesV1 *read, const CancelRejectedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected Jp Equities V 1: written and read back, then read and written back */
static void check_cancel_rejected_jp_equities_v1(void) {
  CancelRejectedJpEquitiesV1 sent;
  CancelRejectedJpEquitiesV1 got;
  uint8_t wire[93];
  uint8_t again[93];

  any_cancel_rejected_jp_equities_v1(&sent);
  assert(encode_cancel_rejected_jp_equities_v1(&sent, wire, 0) == 93);
  assert(decode_cancel_rejected_jp_equities_v1(&got, wire, 0) == 93);
  equal_cancel_rejected_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_jp_equities_v1(&got, wire, 0) == 93);
  assert(encode_cancel_rejected_jp_equities_v1(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement Jp Equities V 1: 32 bytes ------------------------- */

/* A Purge Acknowledgment is an unsequenced message sent when a Purge Orders message requesting an order purge has completed cancelling all individual orders */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];        /* bytes 8 to 27 */
  uint8_t cancelled_order_count[4];  /* bytes 28 to 31 */
} PurgeAcknowledgementJpEquitiesV1;

/* any Purge Acknowledgement Jp Equities V 1 at all: every byte one the checker chooses */
static void any_purge_acknowledgement_jp_equities_v1(PurgeAcknowledgementJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
}

/* Purge Acknowledgement Jp Equities V 1 to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement_jp_equities_v1(const PurgeAcknowledgementJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }

  return at;
}

/* Purge Acknowledgement Jp Equities V 1 off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement_jp_equities_v1(PurgeAcknowledgementJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement Jp Equities V 1 is what was written, byte for byte */
static void equal_purge_acknowledgement_jp_equities_v1(const PurgeAcknowledgementJpEquitiesV1 *read, const PurgeAcknowledgementJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
}

/* Purge Acknowledgement Jp Equities V 1: written and read back, then read and written back */
static void check_purge_acknowledgement_jp_equities_v1(void) {
  PurgeAcknowledgementJpEquitiesV1 sent;
  PurgeAcknowledgementJpEquitiesV1 got;
  uint8_t wire[32];
  uint8_t again[32];

  any_purge_acknowledgement_jp_equities_v1(&sent);
  assert(encode_purge_acknowledgement_jp_equities_v1(&sent, wire, 0) == 32);
  assert(decode_purge_acknowledgement_jp_equities_v1(&got, wire, 0) == 32);
  equal_purge_acknowledgement_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement_jp_equities_v1(&got, wire, 0) == 32);
  assert(encode_purge_acknowledgement_jp_equities_v1(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected Jp Equities V 1: 89 bytes -------------------------------- */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t mass_cancel_id[20];   /* bytes 8 to 27 */
  uint8_t purge_reject_reason;  /* byte 28 */
  uint8_t text[60];             /* bytes 29 to 88 */
} PurgeRejectedJpEquitiesV1;

/* any Purge Rejected Jp Equities V 1 at all: every byte one the checker chooses */
static void any_purge_rejected_jp_equities_v1(PurgeRejectedJpEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected Jp Equities V 1 to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected_jp_equities_v1(const PurgeRejectedJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected Jp Equities V 1 off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected_jp_equities_v1(PurgeRejectedJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected Jp Equities V 1 is what was written, byte for byte */
static void equal_purge_rejected_jp_equities_v1(const PurgeRejectedJpEquitiesV1 *read, const PurgeRejectedJpEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected Jp Equities V 1: written and read back, then read and written back */
static void check_purge_rejected_jp_equities_v1(void) {
  PurgeRejectedJpEquitiesV1 sent;
  PurgeRejectedJpEquitiesV1 got;
  uint8_t wire[89];
  uint8_t again[89];

  any_purge_rejected_jp_equities_v1(&sent);
  assert(encode_purge_rejected_jp_equities_v1(&sent, wire, 0) == 89);
  assert(decode_purge_rejected_jp_equities_v1(&got, wire, 0) == 89);
  equal_purge_rejected_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected_jp_equities_v1(&got, wire, 0) == 89);
  assert(encode_purge_rejected_jp_equities_v1(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_order_acknowledgement_jp_equities_v1();
  check_order_rejected_jp_equities_v1();
  check_order_modified_jp_equities_v1();
  check_modify_rejected_jp_equities_v1();
  check_order_restated_jp_equities_v1();
  check_order_execution_jp_equities_v1();
  check_order_cancelled_jp_equities_v1();
  check_cancel_rejected_jp_equities_v1();
  check_purge_acknowledgement_jp_equities_v1();
  check_purge_rejected_jp_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
