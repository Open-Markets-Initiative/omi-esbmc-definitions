// cboe/neoequities/orderentry/NeoEquities_OrderEntry_v1_0_19_Exchange.c
/*
 * Chicago Board Options Exchange Order Entry
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

/* ---- Order Acknowledgement Ca Equities V 1: 130 bytes ------------------------ */

/* Order Acknowledgement sent in response to a New Order message */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t account[16];               /* bytes 8 to 23 */
  uint8_t cl_ord_id[20];             /* bytes 24 to 43 */
  uint8_t broker_id[2];              /* bytes 44 to 45 */
  uint8_t order_id[8];               /* bytes 46 to 53 */
  uint8_t exec_inst;                 /* byte 54 */
  uint8_t order_qty[4];              /* bytes 55 to 58 */
  uint8_t ord_type;                  /* byte 59 */
  uint8_t price[8];                  /* bytes 60 to 67 */
  uint8_t stop_px[8];                /* bytes 68 to 75 */
  uint8_t working_price[8];          /* bytes 76 to 83 */
  uint8_t side;                      /* byte 84 */
  uint8_t short_marking_exempt;      /* byte 85 */
  uint8_t symbol[14];                /* bytes 86 to 99 */
  uint8_t time_in_force;             /* byte 100 */
  uint8_t max_floor[4];              /* bytes 101 to 104 */
  uint8_t expire_time[8];            /* bytes 105 to 112 */
  uint8_t ex_destination;            /* byte 113 */
  uint8_t no_trade_feat;             /* byte 114 */
  uint8_t no_trade_key[6];           /* bytes 115 to 120 */
  uint8_t base_liquidity_indicator;  /* byte 121 */
  uint8_t true_min_qty[4];           /* bytes 122 to 125 */
  uint8_t expire_date[4];            /* bytes 126 to 129 */
} OrderAcknowledgementCaEquitiesV1;

/* any Order Acknowledgement Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_acknowledgement_ca_equities_v1(OrderAcknowledgementCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->side = arbitrary();
  record->short_marking_exempt = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* Order Acknowledgement Ca Equities V 1 to the wire: 130 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_ca_equities_v1(const OrderAcknowledgementCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->side;
  wire[at++] = record->short_marking_exempt;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  wire[at++] = record->ex_destination;
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* Order Acknowledgement Ca Equities V 1 off the wire: 130 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_ca_equities_v1(OrderAcknowledgementCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->side = wire[at++];
  record->short_marking_exempt = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement Ca Equities V 1 is what was written, byte for byte */
static void equal_order_acknowledgement_ca_equities_v1(const OrderAcknowledgementCaEquitiesV1 *read, const OrderAcknowledgementCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->side == written->side);
  assert(read->short_marking_exempt == written->short_marking_exempt);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  assert(read->ex_destination == written->ex_destination);
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 6; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* Order Acknowledgement Ca Equities V 1: written and read back, then read and written back */
static void check_order_acknowledgement_ca_equities_v1(void) {
  OrderAcknowledgementCaEquitiesV1 sent;
  OrderAcknowledgementCaEquitiesV1 got;
  uint8_t wire[130];
  uint8_t again[130];

  any_order_acknowledgement_ca_equities_v1(&sent);
  assert(encode_order_acknowledgement_ca_equities_v1(&sent, wire, 0) == 130);
  assert(decode_order_acknowledgement_ca_equities_v1(&got, wire, 0) == 130);
  equal_order_acknowledgement_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 130; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_ca_equities_v1(&got, wire, 0) == 130);
  assert(encode_order_acknowledgement_ca_equities_v1(&got, again, 0) == 130);
  for (size_t i = 0; i < 130; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Ca Equities V 1: 91 bytes -------------------------------- */

/* Order Rejected message sent in response to a New Order or New Order Cross that must be rejected */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t broker_id[2];         /* bytes 28 to 29 */
  uint8_t order_reject_reason;  /* byte 30 */
  uint8_t text[60];             /* bytes 31 to 90 */
} OrderRejectedCaEquitiesV1;

/* any Order Rejected Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_rejected_ca_equities_v1(OrderRejectedCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Ca Equities V 1 to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_ca_equities_v1(const OrderRejectedCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Ca Equities V 1 off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_ca_equities_v1(OrderRejectedCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Ca Equities V 1 is what was written, byte for byte */
static void equal_order_rejected_ca_equities_v1(const OrderRejectedCaEquitiesV1 *read, const OrderRejectedCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Ca Equities V 1: written and read back, then read and written back */
static void check_order_rejected_ca_equities_v1(void) {
  OrderRejectedCaEquitiesV1 sent;
  OrderRejectedCaEquitiesV1 got;
  uint8_t wire[91];
  uint8_t again[91];

  any_order_rejected_ca_equities_v1(&sent);
  assert(encode_order_rejected_ca_equities_v1(&sent, wire, 0) == 91);
  assert(decode_order_rejected_ca_equities_v1(&got, wire, 0) == 91);
  equal_order_rejected_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_ca_equities_v1(&got, wire, 0) == 91);
  assert(encode_order_rejected_ca_equities_v1(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Ca Equities V 1: 242 bytes ------------------------------- */

/* Order Modified message sent in response to a Modify Order indicating successful modification */
typedef struct {
  uint8_t transaction_time[8];                /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];                      /* bytes 8 to 27 */
  uint8_t broker_id[2];                       /* bytes 28 to 29 */
  uint8_t order_id[8];                        /* bytes 30 to 37 */
  uint8_t account[16];                        /* bytes 38 to 53 */
  uint8_t time_in_force;                      /* byte 54 */
  uint8_t max_floor[4];                       /* bytes 55 to 58 */
  uint8_t expire_date[4];                     /* bytes 59 to 62 */
  uint8_t lei_order_origin;                   /* byte 63 */
  uint8_t lei_routing_arrangement_indicator;  /* byte 64 */
  uint8_t umir_account_type;                  /* byte 65 */
  uint8_t lei_customer_account[20];           /* bytes 66 to 85 */
  uint8_t lei_algorithm_id[20];               /* bytes 86 to 105 */
  uint8_t customer_lei[52];                   /* bytes 106 to 157 */
  uint8_t broker_lei[20];                     /* bytes 158 to 177 */
  uint8_t order_qty[4];                       /* bytes 178 to 181 */
  uint8_t orig_cl_ord_id[20];                 /* bytes 182 to 201 */
  uint8_t leaves_qty[4];                      /* bytes 202 to 205 */
  uint8_t price[8];                           /* bytes 206 to 213 */
  uint8_t stop_px[8];                         /* bytes 214 to 221 */
  uint8_t true_min_qty[4];                    /* bytes 222 to 225 */
  uint8_t secondary_order_id[8];              /* bytes 226 to 233 */
  uint8_t expire_time[8];                     /* bytes 234 to 241 */
} OrderModifiedCaEquitiesV1;

/* any Order Modified Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_modified_ca_equities_v1(OrderModifiedCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
  record->lei_order_origin = arbitrary();
  record->lei_routing_arrangement_indicator = arbitrary();
  record->umir_account_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
}

/* Order Modified Ca Equities V 1 to the wire: 242 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_ca_equities_v1(const OrderModifiedCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }
  wire[at++] = record->lei_order_origin;
  wire[at++] = record->lei_routing_arrangement_indicator;
  wire[at++] = record->umir_account_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->broker_lei[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }

  return at;
}

/* Order Modified Ca Equities V 1 off the wire: 242 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_ca_equities_v1(OrderModifiedCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }
  record->lei_order_origin = wire[at++];
  record->lei_routing_arrangement_indicator = wire[at++];
  record->umir_account_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Ca Equities V 1 is what was written, byte for byte */
static void equal_order_modified_ca_equities_v1(const OrderModifiedCaEquitiesV1 *read, const OrderModifiedCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  assert(read->lei_order_origin == written->lei_order_origin);
  assert(read->lei_routing_arrangement_indicator == written->lei_routing_arrangement_indicator);
  assert(read->umir_account_type == written->umir_account_type);
  for (size_t i = 0; i < 20; i++) { assert(read->lei_customer_account[i] == written->lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->lei_algorithm_id[i] == written->lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->customer_lei[i] == written->customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->broker_lei[i] == written->broker_lei[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
}

/* Order Modified Ca Equities V 1: written and read back, then read and written back */
static void check_order_modified_ca_equities_v1(void) {
  OrderModifiedCaEquitiesV1 sent;
  OrderModifiedCaEquitiesV1 got;
  uint8_t wire[242];
  uint8_t again[242];

  any_order_modified_ca_equities_v1(&sent);
  assert(encode_order_modified_ca_equities_v1(&sent, wire, 0) == 242);
  assert(decode_order_modified_ca_equities_v1(&got, wire, 0) == 242);
  equal_order_modified_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 242; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_ca_equities_v1(&got, wire, 0) == 242);
  assert(encode_order_modified_ca_equities_v1(&got, again, 0) == 242);
  for (size_t i = 0; i < 242; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Ca Equities V 1: 111 bytes ------------------------------ */

/* Modify Rejected message sent in response to a Modify Order that cannot be modified */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t broker_id[2];          /* bytes 28 to 29 */
  uint8_t orig_cl_ord_id[20];    /* bytes 30 to 49 */
  uint8_t text[60];              /* bytes 50 to 109 */
  uint8_t modify_reject_reason;  /* byte 110 */
} ModifyRejectedCaEquitiesV1;

/* any Modify Rejected Ca Equities V 1 at all: every byte one the checker chooses */
static void any_modify_rejected_ca_equities_v1(ModifyRejectedCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
}

/* Modify Rejected Ca Equities V 1 to the wire: 111 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_ca_equities_v1(const ModifyRejectedCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }
  wire[at++] = record->modify_reject_reason;

  return at;
}

/* Modify Rejected Ca Equities V 1 off the wire: 111 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_ca_equities_v1(ModifyRejectedCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];

  return at;
}

/* what was read of Modify Rejected Ca Equities V 1 is what was written, byte for byte */
static void equal_modify_rejected_ca_equities_v1(const ModifyRejectedCaEquitiesV1 *read, const ModifyRejectedCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
}

/* Modify Rejected Ca Equities V 1: written and read back, then read and written back */
static void check_modify_rejected_ca_equities_v1(void) {
  ModifyRejectedCaEquitiesV1 sent;
  ModifyRejectedCaEquitiesV1 got;
  uint8_t wire[111];
  uint8_t again[111];

  any_modify_rejected_ca_equities_v1(&sent);
  assert(encode_modify_rejected_ca_equities_v1(&sent, wire, 0) == 111);
  assert(decode_modify_rejected_ca_equities_v1(&got, wire, 0) == 111);
  equal_modify_rejected_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 111; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_ca_equities_v1(&got, wire, 0) == 111);
  assert(encode_modify_rejected_ca_equities_v1(&got, again, 0) == 111);
  for (size_t i = 0; i < 111; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Restated Ca Equities V 1: 80 bytes -------------------------------- */

/* Order Restated message sent when iceberg order reloads or when self-trade protection reduces an order */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t broker_id[2];              /* bytes 28 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t order_qty[4];              /* bytes 38 to 41 */
  uint8_t leaves_qty[4];             /* bytes 42 to 45 */
  uint8_t secondary_order_id[8];     /* bytes 46 to 53 */
  uint8_t last_px[8];                /* bytes 54 to 61 */
  uint8_t last_shares[4];            /* bytes 62 to 65 */
  uint8_t base_liquidity_indicator;  /* byte 66 */
  uint8_t price[8];                  /* bytes 67 to 74 */
  uint8_t true_min_qty[4];           /* bytes 75 to 78 */
  uint8_t restatement_reason;        /* byte 79 */
} OrderRestatedCaEquitiesV1;

/* any Order Restated Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_restated_ca_equities_v1(OrderRestatedCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
  record->restatement_reason = arbitrary();
}

/* Order Restated Ca Equities V 1 to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_order_restated_ca_equities_v1(const OrderRestatedCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }
  wire[at++] = record->restatement_reason;

  return at;
}

/* Order Restated Ca Equities V 1 off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_order_restated_ca_equities_v1(OrderRestatedCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }
  record->restatement_reason = wire[at++];

  return at;
}

/* what was read of Order Restated Ca Equities V 1 is what was written, byte for byte */
static void equal_order_restated_ca_equities_v1(const OrderRestatedCaEquitiesV1 *read, const OrderRestatedCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
  assert(read->restatement_reason == written->restatement_reason);
}

/* Order Restated Ca Equities V 1: written and read back, then read and written back */
static void check_order_restated_ca_equities_v1(void) {
  OrderRestatedCaEquitiesV1 sent;
  OrderRestatedCaEquitiesV1 got;
  uint8_t wire[80];
  uint8_t again[80];

  any_order_restated_ca_equities_v1(&sent);
  assert(encode_order_restated_ca_equities_v1(&sent, wire, 0) == 80);
  assert(decode_order_restated_ca_equities_v1(&got, wire, 0) == 80);
  equal_order_restated_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_order_restated_ca_equities_v1(&got, wire, 0) == 80);
  assert(encode_order_restated_ca_equities_v1(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Ca Equities V 1: 99 bytes ------------------------------- */

/* Order Execution message sent for each fill on an order */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];             /* bytes 8 to 27 */
  uint8_t exec_id[8];                /* bytes 28 to 35 */
  uint8_t last_px[8];                /* bytes 36 to 43 */
  uint8_t last_shares[4];            /* bytes 44 to 47 */
  uint8_t order_id[8];               /* bytes 48 to 55 */
  uint8_t side;                      /* byte 56 */
  uint8_t symbol[14];                /* bytes 57 to 70 */
  uint8_t trade_date[4];             /* bytes 71 to 74 */
  uint8_t leaves_qty[4];             /* bytes 75 to 78 */
  uint8_t contra_broker[2];          /* bytes 79 to 80 */
  uint8_t base_liquidity_indicator;  /* byte 81 */
  uint8_t broker_id[2];              /* bytes 82 to 83 */
  uint8_t principal_trade;           /* byte 84 */
  uint8_t wash_trade;                /* byte 85 */
  uint8_t no_trade_feat;             /* byte 86 */
  uint8_t no_trade_key[6];           /* bytes 87 to 92 */
  uint8_t short_marking_exempt;      /* byte 93 */
  uint8_t matching_priority;         /* byte 94 */
  uint8_t is_self_trade;             /* byte 95 */
  uint8_t fee_code[2];               /* bytes 96 to 97 */
  uint8_t ex_destination;            /* byte 98 */
} OrderExecutionCaEquitiesV1;

/* any Order Execution Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_execution_ca_equities_v1(OrderExecutionCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->contra_broker[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->principal_trade = arbitrary();
  record->wash_trade = arbitrary();
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = arbitrary(); }
  record->short_marking_exempt = arbitrary();
  record->matching_priority = arbitrary();
  record->is_self_trade = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  record->ex_destination = arbitrary();
}

/* Order Execution Ca Equities V 1 to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_ca_equities_v1(const OrderExecutionCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->contra_broker[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->principal_trade;
  wire[at++] = record->wash_trade;
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->short_marking_exempt;
  wire[at++] = record->matching_priority;
  wire[at++] = record->is_self_trade;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  wire[at++] = record->ex_destination;

  return at;
}

/* Order Execution Ca Equities V 1 off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_ca_equities_v1(OrderExecutionCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->contra_broker[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->principal_trade = wire[at++];
  record->wash_trade = wire[at++];
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = wire[at++]; }
  record->short_marking_exempt = wire[at++];
  record->matching_priority = wire[at++];
  record->is_self_trade = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  record->ex_destination = wire[at++];

  return at;
}

/* what was read of Order Execution Ca Equities V 1 is what was written, byte for byte */
static void equal_order_execution_ca_equities_v1(const OrderExecutionCaEquitiesV1 *read, const OrderExecutionCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->principal_trade == written->principal_trade);
  assert(read->wash_trade == written->wash_trade);
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 6; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->short_marking_exempt == written->short_marking_exempt);
  assert(read->matching_priority == written->matching_priority);
  assert(read->is_self_trade == written->is_self_trade);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  assert(read->ex_destination == written->ex_destination);
}

/* Order Execution Ca Equities V 1: written and read back, then read and written back */
static void check_order_execution_ca_equities_v1(void) {
  OrderExecutionCaEquitiesV1 sent;
  OrderExecutionCaEquitiesV1 got;
  uint8_t wire[99];
  uint8_t again[99];

  any_order_execution_ca_equities_v1(&sent);
  assert(encode_order_execution_ca_equities_v1(&sent, wire, 0) == 99);
  assert(decode_order_execution_ca_equities_v1(&got, wire, 0) == 99);
  equal_order_execution_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_ca_equities_v1(&got, wire, 0) == 99);
  assert(encode_order_execution_ca_equities_v1(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Ca Equities V 1: 31 bytes ------------------------------- */

/* Order Cancelled message */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t broker_id[2];         /* bytes 28 to 29 */
  uint8_t cancel_reason;        /* byte 30 */
} OrderCancelledCaEquitiesV1;

/* any Order Cancelled Ca Equities V 1 at all: every byte one the checker chooses */
static void any_order_cancelled_ca_equities_v1(OrderCancelledCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Cancelled Ca Equities V 1 to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_ca_equities_v1(const OrderCancelledCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Cancelled Ca Equities V 1 off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_ca_equities_v1(OrderCancelledCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Cancelled Ca Equities V 1 is what was written, byte for byte */
static void equal_order_cancelled_ca_equities_v1(const OrderCancelledCaEquitiesV1 *read, const OrderCancelledCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Cancelled Ca Equities V 1: written and read back, then read and written back */
static void check_order_cancelled_ca_equities_v1(void) {
  OrderCancelledCaEquitiesV1 sent;
  OrderCancelledCaEquitiesV1 got;
  uint8_t wire[31];
  uint8_t again[31];

  any_order_cancelled_ca_equities_v1(&sent);
  assert(encode_order_cancelled_ca_equities_v1(&sent, wire, 0) == 31);
  assert(decode_order_cancelled_ca_equities_v1(&got, wire, 0) == 31);
  equal_order_cancelled_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_ca_equities_v1(&got, wire, 0) == 31);
  assert(encode_order_cancelled_ca_equities_v1(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Ca Equities V 1: 91 bytes ------------------------------- */

/* Cancel Rejected message sent when a Cancel Order cancellation cannot occur */
typedef struct {
  uint8_t transaction_time[8];   /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];         /* bytes 8 to 27 */
  uint8_t broker_id[2];          /* bytes 28 to 29 */
  uint8_t text[60];              /* bytes 30 to 89 */
  uint8_t cancel_reject_reason;  /* byte 90 */
} CancelRejectedCaEquitiesV1;

/* any Cancel Rejected Ca Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_rejected_ca_equities_v1(CancelRejectedCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
}

/* Cancel Rejected Ca Equities V 1 to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_ca_equities_v1(const CancelRejectedCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }
  wire[at++] = record->cancel_reject_reason;

  return at;
}

/* Cancel Rejected Ca Equities V 1 off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_ca_equities_v1(CancelRejectedCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];

  return at;
}

/* what was read of Cancel Rejected Ca Equities V 1 is what was written, byte for byte */
static void equal_cancel_rejected_ca_equities_v1(const CancelRejectedCaEquitiesV1 *read, const CancelRejectedCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
}

/* Cancel Rejected Ca Equities V 1: written and read back, then read and written back */
static void check_cancel_rejected_ca_equities_v1(void) {
  CancelRejectedCaEquitiesV1 sent;
  CancelRejectedCaEquitiesV1 got;
  uint8_t wire[91];
  uint8_t again[91];

  any_cancel_rejected_ca_equities_v1(&sent);
  assert(encode_cancel_rejected_ca_equities_v1(&sent, wire, 0) == 91);
  assert(decode_cancel_rejected_ca_equities_v1(&got, wire, 0) == 91);
  equal_cancel_rejected_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_ca_equities_v1(&got, wire, 0) == 91);
  assert(encode_cancel_rejected_ca_equities_v1(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Carried Restatement Ca Equities V 1: 262 bytes -------------------------- */

/* Carried Restatement message used to indicate restoration of a multi-day GTC or GTD order at the start of a new business day */
typedef struct {
  uint8_t transaction_time[8];                /* bytes 0 to 7 */
  uint8_t order_id[8];                        /* bytes 8 to 15 */
  uint8_t account[16];                        /* bytes 16 to 31 */
  uint8_t cl_ord_id[20];                      /* bytes 32 to 51 */
  uint8_t broker_id[2];                       /* bytes 52 to 53 */
  uint8_t exec_inst;                          /* byte 54 */
  uint8_t handling_inst;                      /* byte 55 */
  uint8_t order_qty[4];                       /* bytes 56 to 59 */
  uint8_t cum_qty[4];                         /* bytes 60 to 63 */
  uint8_t leaves_qty[4];                      /* bytes 64 to 67 */
  uint8_t ord_type;                           /* byte 68 */
  uint8_t price[8];                           /* bytes 69 to 76 */
  uint8_t stop_px[8];                         /* bytes 77 to 84 */
  uint8_t side;                               /* byte 85 */
  uint8_t symbol[14];                         /* bytes 86 to 99 */
  uint8_t time_in_force;                      /* byte 100 */
  uint8_t settlement_type;                    /* byte 101 */
  uint8_t fut_settl_date[4];                  /* bytes 102 to 105 */
  uint8_t ex_destination;                     /* byte 106 */
  uint8_t max_floor[4];                       /* bytes 107 to 110 */
  uint8_t expire_date[4];                     /* bytes 111 to 114 */
  uint8_t lei_order_origin;                   /* byte 115 */
  uint8_t lei_routing_arrangement_indicator;  /* byte 116 */
  uint8_t umir_account_type;                  /* byte 117 */
  uint8_t umir_user_id[12];                   /* bytes 118 to 129 */
  uint8_t basket_trade[4];                    /* bytes 130 to 133 */
  uint8_t program_trade;                      /* byte 134 */
  uint8_t jitney[2];                          /* bytes 135 to 136 */
  uint8_t anonymous;                          /* byte 137 */
  uint8_t umir_regulation_id;                 /* byte 138 */
  uint8_t non_resident;                       /* byte 139 */
  uint8_t bypass;                             /* byte 140 */
  uint8_t ncib;                               /* byte 141 */
  uint8_t short_marking_exempt;               /* byte 142 */
  uint8_t lei_customer_account[20];           /* bytes 143 to 162 */
  uint8_t lei_algorithm_id[20];               /* bytes 163 to 182 */
  uint8_t customer_lei[52];                   /* bytes 183 to 234 */
  uint8_t broker_lei[20];                     /* bytes 235 to 254 */
  uint8_t routing_inst;                       /* byte 255 */
  uint8_t display_indicator;                  /* byte 256 */
  uint8_t matching_state_participation;       /* byte 257 */
  uint8_t true_min_qty[4];                    /* bytes 258 to 261 */
} CarriedRestatementCaEquitiesV1;

/* any Carried Restatement Ca Equities V 1 at all: every byte one the checker chooses */
static void any_carried_restatement_ca_equities_v1(CarriedRestatementCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->handling_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
  record->lei_order_origin = arbitrary();
  record->lei_routing_arrangement_indicator = arbitrary();
  record->umir_account_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = arbitrary(); }
  record->program_trade = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->jitney[i] = arbitrary(); }
  record->anonymous = arbitrary();
  record->umir_regulation_id = arbitrary();
  record->non_resident = arbitrary();
  record->bypass = arbitrary();
  record->ncib = arbitrary();
  record->short_marking_exempt = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = arbitrary(); }
  record->routing_inst = arbitrary();
  record->display_indicator = arbitrary();
  record->matching_state_participation = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
}

/* Carried Restatement Ca Equities V 1 to the wire: 262 bytes from at, returning where the next byte goes */
static size_t encode_carried_restatement_ca_equities_v1(const CarriedRestatementCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->handling_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fut_settl_date[i]; }
  wire[at++] = record->ex_destination;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }
  wire[at++] = record->lei_order_origin;
  wire[at++] = record->lei_routing_arrangement_indicator;
  wire[at++] = record->umir_account_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->umir_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->basket_trade[i]; }
  wire[at++] = record->program_trade;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->jitney[i]; }
  wire[at++] = record->anonymous;
  wire[at++] = record->umir_regulation_id;
  wire[at++] = record->non_resident;
  wire[at++] = record->bypass;
  wire[at++] = record->ncib;
  wire[at++] = record->short_marking_exempt;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->broker_lei[i]; }
  wire[at++] = record->routing_inst;
  wire[at++] = record->display_indicator;
  wire[at++] = record->matching_state_participation;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }

  return at;
}

/* Carried Restatement Ca Equities V 1 off the wire: 262 bytes from at, returning where the next byte lies */
static size_t decode_carried_restatement_ca_equities_v1(CarriedRestatementCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->handling_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }
  record->lei_order_origin = wire[at++];
  record->lei_routing_arrangement_indicator = wire[at++];
  record->umir_account_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = wire[at++]; }
  record->program_trade = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->jitney[i] = wire[at++]; }
  record->anonymous = wire[at++];
  record->umir_regulation_id = wire[at++];
  record->non_resident = wire[at++];
  record->bypass = wire[at++];
  record->ncib = wire[at++];
  record->short_marking_exempt = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = wire[at++]; }
  record->routing_inst = wire[at++];
  record->display_indicator = wire[at++];
  record->matching_state_participation = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Carried Restatement Ca Equities V 1 is what was written, byte for byte */
static void equal_carried_restatement_ca_equities_v1(const CarriedRestatementCaEquitiesV1 *read, const CarriedRestatementCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->handling_inst == written->handling_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->fut_settl_date[i] == written->fut_settl_date[i]); }
  assert(read->ex_destination == written->ex_destination);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  assert(read->lei_order_origin == written->lei_order_origin);
  assert(read->lei_routing_arrangement_indicator == written->lei_routing_arrangement_indicator);
  assert(read->umir_account_type == written->umir_account_type);
  for (size_t i = 0; i < 12; i++) { assert(read->umir_user_id[i] == written->umir_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->basket_trade[i] == written->basket_trade[i]); }
  assert(read->program_trade == written->program_trade);
  for (size_t i = 0; i < 2; i++) { assert(read->jitney[i] == written->jitney[i]); }
  assert(read->anonymous == written->anonymous);
  assert(read->umir_regulation_id == written->umir_regulation_id);
  assert(read->non_resident == written->non_resident);
  assert(read->bypass == written->bypass);
  assert(read->ncib == written->ncib);
  assert(read->short_marking_exempt == written->short_marking_exempt);
  for (size_t i = 0; i < 20; i++) { assert(read->lei_customer_account[i] == written->lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->lei_algorithm_id[i] == written->lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->customer_lei[i] == written->customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->broker_lei[i] == written->broker_lei[i]); }
  assert(read->routing_inst == written->routing_inst);
  assert(read->display_indicator == written->display_indicator);
  assert(read->matching_state_participation == written->matching_state_participation);
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
}

/* Carried Restatement Ca Equities V 1: written and read back, then read and written back */
static void check_carried_restatement_ca_equities_v1(void) {
  CarriedRestatementCaEquitiesV1 sent;
  CarriedRestatementCaEquitiesV1 got;
  uint8_t wire[262];
  uint8_t again[262];

  any_carried_restatement_ca_equities_v1(&sent);
  assert(encode_carried_restatement_ca_equities_v1(&sent, wire, 0) == 262);
  assert(decode_carried_restatement_ca_equities_v1(&got, wire, 0) == 262);
  equal_carried_restatement_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 262; i++) { wire[i] = arbitrary(); }
  assert(decode_carried_restatement_ca_equities_v1(&got, wire, 0) == 262);
  assert(encode_carried_restatement_ca_equities_v1(&got, again, 0) == 262);
  for (size_t i = 0; i < 262; i++) { assert(again[i] == wire[i]); }
}

/* ---- Done For Day Ca Equities V 1: 38 bytes ---------------------------------- */

/* Done For Day message representing orders persisted during the current day session to carry over to the next session */
typedef struct {
  uint8_t transaction_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];        /* bytes 8 to 27 */
  uint8_t broker_id[2];         /* bytes 28 to 29 */
  uint8_t symbol_short[8];      /* bytes 30 to 37 */
} DoneForDayCaEquitiesV1;

/* any Done For Day Ca Equities V 1 at all: every byte one the checker chooses */
static void any_done_for_day_ca_equities_v1(DoneForDayCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_short[i] = arbitrary(); }
}

/* Done For Day Ca Equities V 1 to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_done_for_day_ca_equities_v1(const DoneForDayCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_short[i]; }

  return at;
}

/* Done For Day Ca Equities V 1 off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_done_for_day_ca_equities_v1(DoneForDayCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_short[i] = wire[at++]; }

  return at;
}

/* what was read of Done For Day Ca Equities V 1 is what was written, byte for byte */
static void equal_done_for_day_ca_equities_v1(const DoneForDayCaEquitiesV1 *read, const DoneForDayCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
}

/* Done For Day Ca Equities V 1: written and read back, then read and written back */
static void check_done_for_day_ca_equities_v1(void) {
  DoneForDayCaEquitiesV1 sent;
  DoneForDayCaEquitiesV1 got;
  uint8_t wire[38];
  uint8_t again[38];

  any_done_for_day_ca_equities_v1(&sent);
  assert(encode_done_for_day_ca_equities_v1(&sent, wire, 0) == 38);
  assert(decode_done_for_day_ca_equities_v1(&got, wire, 0) == 38);
  equal_done_for_day_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_done_for_day_ca_equities_v1(&got, wire, 0) == 38);
  assert(encode_done_for_day_ca_equities_v1(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct Ca Equities V 1: 119 bytes ------------------------- */

/* Trade Cancel or Correct notification that a trade has been busted or corrected */
typedef struct {
  uint8_t transaction_time[8];       /* bytes 0 to 7 */
  uint8_t account[16];               /* bytes 8 to 23 */
  uint8_t cl_ord_id[20];             /* bytes 24 to 43 */
  uint8_t exec_id[8];                /* bytes 44 to 51 */
  uint8_t exec_ref_id[8];            /* bytes 52 to 59 */
  uint8_t last_px[8];                /* bytes 60 to 67 */
  uint8_t last_shares[4];            /* bytes 68 to 71 */
  uint8_t side;                      /* byte 72 */
  uint8_t symbol[14];                /* bytes 73 to 86 */
  uint8_t base_liquidity_indicator;  /* byte 87 */
  uint8_t corrected_size[4];         /* bytes 88 to 91 */
  uint8_t umir_user_id[12];          /* bytes 92 to 103 */
  uint8_t corrected_price[8];        /* bytes 104 to 111 */
  uint8_t fee_code[2];               /* bytes 112 to 113 */
  uint8_t settlement_type;           /* byte 114 */
  uint8_t fut_settl_date[4];         /* bytes 115 to 118 */
} TradeCancelCorrectCaEquitiesV1;

/* any Trade Cancel Correct Ca Equities V 1 at all: every byte one the checker chooses */
static void any_trade_cancel_correct_ca_equities_v1(TradeCancelCorrectCaEquitiesV1 *record) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->corrected_size[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = arbitrary(); }
}

/* Trade Cancel Correct Ca Equities V 1 to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct_ca_equities_v1(const TradeCancelCorrectCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_size[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->umir_user_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fut_settl_date[i]; }

  return at;
}

/* Trade Cancel Correct Ca Equities V 1 off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct_ca_equities_v1(TradeCancelCorrectCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->corrected_size[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Correct Ca Equities V 1 is what was written, byte for byte */
static void equal_trade_cancel_correct_ca_equities_v1(const TradeCancelCorrectCaEquitiesV1 *read, const TradeCancelCorrectCaEquitiesV1 *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_size[i] == written->corrected_size[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->umir_user_id[i] == written->umir_user_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->fut_settl_date[i] == written->fut_settl_date[i]); }
}

/* Trade Cancel Correct Ca Equities V 1: written and read back, then read and written back */
static void check_trade_cancel_correct_ca_equities_v1(void) {
  TradeCancelCorrectCaEquitiesV1 sent;
  TradeCancelCorrectCaEquitiesV1 got;
  uint8_t wire[119];
  uint8_t again[119];

  any_trade_cancel_correct_ca_equities_v1(&sent);
  assert(encode_trade_cancel_correct_ca_equities_v1(&sent, wire, 0) == 119);
  assert(decode_trade_cancel_correct_ca_equities_v1(&got, wire, 0) == 119);
  equal_trade_cancel_correct_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct_ca_equities_v1(&got, wire, 0) == 119);
  assert(encode_trade_cancel_correct_ca_equities_v1(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_order_acknowledgement_ca_equities_v1();
  check_order_rejected_ca_equities_v1();
  check_order_modified_ca_equities_v1();
  check_modify_rejected_ca_equities_v1();
  check_order_restated_ca_equities_v1();
  check_order_execution_ca_equities_v1();
  check_order_cancelled_ca_equities_v1();
  check_cancel_rejected_ca_equities_v1();
  check_carried_restatement_ca_equities_v1();
  check_done_for_day_ca_equities_v1();
  check_trade_cancel_correct_ca_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
