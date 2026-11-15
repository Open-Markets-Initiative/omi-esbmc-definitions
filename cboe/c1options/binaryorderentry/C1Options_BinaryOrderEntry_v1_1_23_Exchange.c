// cboe/c1options/binaryorderentry/C1Options_BinaryOrderEntry_v1_1_23_Exchange.c
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

/* ---- Order Acknowledgement Message: 93 bytes --------------------------------- */

/* OrderAcknowledgementMessage */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t side;                      /* byte 38 */
  uint8_t price[8];                  /* bytes 39 to 46 */
  uint8_t symbol[8];                 /* bytes 47 to 54 */
  uint8_t clearing_firm[4];          /* bytes 55 to 58 */
  uint8_t leaves_qty[4];             /* bytes 59 to 62 */
  uint8_t display_price[8];          /* bytes 63 to 70 */
  uint8_t working_price[8];          /* bytes 71 to 78 */
  uint8_t base_liquidity_indicator;  /* byte 79 */
  uint8_t sub_liquidity_indicator;   /* byte 80 */
  uint8_t routing_firm_id[4];        /* bytes 81 to 84 */
  uint8_t request_received_time[8];  /* bytes 85 to 92 */
} OrderAcknowledgementMessage;

/* any Order Acknowledgement Message at all: every byte one the checker chooses */
static void any_order_acknowledgement_message(OrderAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Acknowledgement Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_message(const OrderAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Acknowledgement Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_message(OrderAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement Message is what was written, byte for byte */
static void equal_order_acknowledgement_message(const OrderAcknowledgementMessage *read, const OrderAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Acknowledgement Message: written and read back, then read and written back */
static void check_order_acknowledgement_message(void) {
  OrderAcknowledgementMessage sent;
  OrderAcknowledgementMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_order_acknowledgement_message(&sent);
  assert(encode_order_acknowledgement_message(&sent, wire, 0) == 93);
  assert(decode_order_acknowledgement_message(&got, wire, 0) == 93);
  equal_order_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_message(&got, wire, 0) == 93);
  assert(encode_order_acknowledgement_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Message: 99 bytes ---------------------------------------- */

/* Order Rejected messages are sent in response to a New Order message which must be rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t clearing_firm[4];     /* bytes 30 to 33 */
  uint8_t routing_firm_id[4];   /* bytes 34 to 37 */
  uint8_t order_reject_reason;  /* byte 38 */
  uint8_t text[60];             /* bytes 39 to 98 */
} OrderRejectedMessage;

/* any Order Rejected Message at all: every byte one the checker chooses */
static void any_order_rejected_message(OrderRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_message(const OrderRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_message(OrderRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Message is what was written, byte for byte */
static void equal_order_rejected_message(const OrderRejectedMessage *read, const OrderRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Message: written and read back, then read and written back */
static void check_order_rejected_message(void) {
  OrderRejectedMessage sent;
  OrderRejectedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_order_rejected_message(&sent);
  assert(encode_order_rejected_message(&sent, wire, 0) == 99);
  assert(decode_order_rejected_message(&got, wire, 0) == 99);
  equal_order_rejected_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_message(&got, wire, 0) == 99);
  assert(encode_order_rejected_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Order Rejected Message: 95 bytes ---------------------------------- */

/* Cross Order Rejected messages are sent in response to a New Order Cross and New Order Cross Multileg message which must be rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cross_id[20];         /* bytes 10 to 29 */
  uint8_t routing_firm_id[4];   /* bytes 30 to 33 */
  uint8_t order_reject_reason;  /* byte 34 */
  uint8_t text[60];             /* bytes 35 to 94 */
} CrossOrderRejectedMessage;

/* any Cross Order Rejected Message at all: every byte one the checker chooses */
static void any_cross_order_rejected_message(CrossOrderRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cross Order Rejected Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_cross_order_rejected_message(const CrossOrderRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cross Order Rejected Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_cross_order_rejected_message(CrossOrderRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Order Rejected Message is what was written, byte for byte */
static void equal_cross_order_rejected_message(const CrossOrderRejectedMessage *read, const CrossOrderRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cross Order Rejected Message: written and read back, then read and written back */
static void check_cross_order_rejected_message(void) {
  CrossOrderRejectedMessage sent;
  CrossOrderRejectedMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_cross_order_rejected_message(&sent);
  assert(encode_cross_order_rejected_message(&sent, wire, 0) == 95);
  assert(decode_cross_order_rejected_message(&got, wire, 0) == 95);
  equal_cross_order_rejected_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_order_rejected_message(&got, wire, 0) == 95);
  assert(encode_cross_order_rejected_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Update Rejected Message: 27 bytes --------------------------------- */

/* Quote Update Rejected messages are sent in response to a Quote Update message when the entire quote block is rejected by the order handler */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t quote_update_id[16];  /* bytes 10 to 25 */
  uint8_t quote_reject_reason;  /* byte 26 */
} QuoteUpdateRejectedMessage;

/* any Quote Update Rejected Message at all: every byte one the checker chooses */
static void any_quote_update_rejected_message(QuoteUpdateRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  record->quote_reject_reason = arbitrary();
}

/* Quote Update Rejected Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_quote_update_rejected_message(const QuoteUpdateRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  wire[at++] = record->quote_reject_reason;

  return at;
}

/* Quote Update Rejected Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_quote_update_rejected_message(QuoteUpdateRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  record->quote_reject_reason = wire[at++];

  return at;
}

/* what was read of Quote Update Rejected Message is what was written, byte for byte */
static void equal_quote_update_rejected_message(const QuoteUpdateRejectedMessage *read, const QuoteUpdateRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  assert(read->quote_reject_reason == written->quote_reject_reason);
}

/* Quote Update Rejected Message: written and read back, then read and written back */
static void check_quote_update_rejected_message(void) {
  QuoteUpdateRejectedMessage sent;
  QuoteUpdateRejectedMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_quote_update_rejected_message(&sent);
  assert(encode_quote_update_rejected_message(&sent, wire, 0) == 27);
  assert(decode_quote_update_rejected_message(&got, wire, 0) == 27);
  equal_quote_update_rejected_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_update_rejected_message(&got, wire, 0) == 27);
  assert(encode_quote_update_rejected_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Message: 136 bytes --------------------------------------- */

/* Order Modified messages are sent in response to a Modify Request message to indicate that the order has been successfully modified */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t orig_cl_ord_id[20];        /* bytes 30 to 49 */
  uint8_t order_id[8];               /* bytes 50 to 57 */
  uint8_t clearing_firm[4];          /* bytes 58 to 61 */
  uint8_t routing_firm_id[4];        /* bytes 62 to 65 */
  uint8_t symbol[8];                 /* bytes 66 to 73 */
  uint8_t order_qty[4];              /* bytes 74 to 77 */
  uint8_t price[8];                  /* bytes 78 to 85 */
  uint8_t ord_type;                  /* byte 86 */
  uint8_t max_floor[4];              /* bytes 87 to 90 */
  uint8_t stop_px[8];                /* bytes 91 to 98 */
  uint8_t leaves_qty[4];             /* bytes 99 to 102 */
  uint8_t display_price[8];          /* bytes 103 to 110 */
  uint8_t working_price[8];          /* bytes 111 to 118 */
  uint8_t base_liquidity_indicator;  /* byte 119 */
  uint8_t secondary_order_id[8];     /* bytes 120 to 127 */
  uint8_t request_received_time[8];  /* bytes 128 to 135 */
} OrderModifiedMessage;

/* any Order Modified Message at all: every byte one the checker chooses */
static void any_order_modified_message(OrderModifiedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Modified Message to the wire: 136 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_message(const OrderModifiedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Modified Message off the wire: 136 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_message(OrderModifiedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Message is what was written, byte for byte */
static void equal_order_modified_message(const OrderModifiedMessage *read, const OrderModifiedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Modified Message: written and read back, then read and written back */
static void check_order_modified_message(void) {
  OrderModifiedMessage sent;
  OrderModifiedMessage got;
  uint8_t wire[136];
  uint8_t again[136];

  any_order_modified_message(&sent);
  assert(encode_order_modified_message(&sent, wire, 0) == 136);
  assert(decode_order_modified_message(&got, wire, 0) == 136);
  equal_order_modified_message(&got, &sent);

  for (size_t i = 0; i < 136; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_message(&got, wire, 0) == 136);
  assert(encode_order_modified_message(&got, again, 0) == 136);
  for (size_t i = 0; i < 136; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Restated Message: 108 bytes --------------------------------------- */

/* Order Restated messages are sent to inform the Member that an order has been asynchronously modified */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t clearing_firm[4];          /* bytes 38 to 41 */
  uint8_t routing_firm_id[4];        /* bytes 42 to 45 */
  uint8_t symbol[8];                 /* bytes 46 to 53 */
  uint8_t order_restatement_reason;  /* byte 54 */
  uint8_t order_qty[4];              /* bytes 55 to 58 */
  uint8_t price[8];                  /* bytes 59 to 66 */
  uint8_t leaves_qty[4];             /* bytes 67 to 70 */
  uint8_t display_price[8];          /* bytes 71 to 78 */
  uint8_t working_price[8];          /* bytes 79 to 86 */
  uint8_t base_liquidity_indicator;  /* byte 87 */
  uint8_t secondary_order_id[8];     /* bytes 88 to 95 */
  uint8_t last_shares[4];            /* bytes 96 to 99 */
  uint8_t last_px[8];                /* bytes 100 to 107 */
} OrderRestatedMessage;

/* any Order Restated Message at all: every byte one the checker chooses */
static void any_order_restated_message(OrderRestatedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->order_restatement_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
}

/* Order Restated Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_order_restated_message(const OrderRestatedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->order_restatement_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }

  return at;
}

/* Order Restated Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_order_restated_message(OrderRestatedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->order_restatement_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }

  return at;
}

/* what was read of Order Restated Message is what was written, byte for byte */
static void equal_order_restated_message(const OrderRestatedMessage *read, const OrderRestatedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->order_restatement_reason == written->order_restatement_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
}

/* Order Restated Message: written and read back, then read and written back */
static void check_order_restated_message(void) {
  OrderRestatedMessage sent;
  OrderRestatedMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_order_restated_message(&sent);
  assert(encode_order_restated_message(&sent, wire, 0) == 108);
  assert(decode_order_restated_message(&got, wire, 0) == 108);
  equal_order_restated_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_order_restated_message(&got, wire, 0) == 108);
  assert(encode_order_restated_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Restated Message: 54 bytes ---------------------------------------- */

/* Quote Restated messages are sent to inform the Member that an order has been asynchronously modified for some reason by the Exchange */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t quote_update_id[16];  /* bytes 10 to 25 */
  uint8_t order_id[8];          /* bytes 26 to 33 */
  uint8_t leaves_qty[4];        /* bytes 34 to 37 */
  uint8_t working_price[8];     /* bytes 38 to 45 */
  uint8_t quote_symbol[6];      /* bytes 46 to 51 */
  uint8_t side;                 /* byte 52 */
  uint8_t restatement_reason;   /* byte 53 */
} QuoteRestatedMessage;

/* any Quote Restated Message at all: every byte one the checker chooses */
static void any_quote_restated_message(QuoteRestatedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->restatement_reason = arbitrary();
}

/* Quote Restated Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_quote_restated_message(const QuoteRestatedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
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

/* Quote Restated Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_quote_restated_message(QuoteRestatedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
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
  uint8_t wire[54];
  uint8_t again[54];

  any_quote_restated_message(&sent);
  assert(encode_quote_restated_message(&sent, wire, 0) == 54);
  assert(decode_quote_restated_message(&got, wire, 0) == 54);
  equal_quote_restated_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_restated_message(&got, wire, 0) == 54);
  assert(encode_quote_restated_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Message: 119 bytes -------------------------------------- */

/* User Modify Rejected messages are sent in response to a Modify Order message for an order which cannot be modified */
typedef struct {
  uint8_t in_flight[2];          /* bytes 0 to 1 */
  uint8_t transaction_time[8];   /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];         /* bytes 10 to 29 */
  uint8_t clearing_firm[4];      /* bytes 30 to 33 */
  uint8_t routing_firm_id[4];    /* bytes 34 to 37 */
  uint8_t orig_cl_ord_id[20];    /* bytes 38 to 57 */
  uint8_t modify_reject_reason;  /* byte 58 */
  uint8_t text[60];              /* bytes 59 to 118 */
} ModifyRejectedMessage;

/* any Modify Rejected Message at all: every byte one the checker chooses */
static void any_modify_rejected_message(ModifyRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected Message to the wire: 119 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_message(const ModifyRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected Message off the wire: 119 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_message(ModifyRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected Message is what was written, byte for byte */
static void equal_modify_rejected_message(const ModifyRejectedMessage *read, const ModifyRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected Message: written and read back, then read and written back */
static void check_modify_rejected_message(void) {
  ModifyRejectedMessage sent;
  ModifyRejectedMessage got;
  uint8_t wire[119];
  uint8_t again[119];

  any_modify_rejected_message(&sent);
  assert(encode_modify_rejected_message(&sent, wire, 0) == 119);
  assert(decode_modify_rejected_message(&got, wire, 0) == 119);
  equal_modify_rejected_message(&got, &sent);

  for (size_t i = 0; i < 119; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_message(&got, wire, 0) == 119);
  assert(encode_modify_rejected_message(&got, again, 0) == 119);
  for (size_t i = 0; i < 119; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Message: 56 bytes --------------------------------------- */

/* This message indicates an order has been cancelled */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t cancel_reason;             /* byte 30 */
  uint8_t cancel_sub_reason;         /* byte 31 */
  uint8_t clearing_firm[4];          /* bytes 32 to 35 */
  uint8_t routing_firm_id[4];        /* bytes 36 to 39 */
  uint8_t symbol[8];                 /* bytes 40 to 47 */
  uint8_t request_received_time[8];  /* bytes 48 to 55 */
} OrderCancelledMessage;

/* any Order Cancelled Message at all: every byte one the checker chooses */
static void any_order_cancelled_message(OrderCancelledMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  record->cancel_sub_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Order Cancelled Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_message(const OrderCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;
  wire[at++] = record->cancel_sub_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Order Cancelled Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_message(OrderCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  record->cancel_sub_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancelled Message is what was written, byte for byte */
static void equal_order_cancelled_message(const OrderCancelledMessage *read, const OrderCancelledMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  assert(read->cancel_sub_reason == written->cancel_sub_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Order Cancelled Message: written and read back, then read and written back */
static void check_order_cancelled_message(void) {
  OrderCancelledMessage sent;
  OrderCancelledMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_order_cancelled_message(&sent);
  assert(encode_order_cancelled_message(&sent, wire, 0) == 56);
  assert(decode_order_cancelled_message(&got, wire, 0) == 56);
  equal_order_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_message(&got, wire, 0) == 56);
  assert(encode_order_cancelled_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancelled Message: 43 bytes --------------------------------------- */

/* A Quote Cancelled message will be sent to indicate an unsolicited cancellation of a quote entered with a Quote Update message */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t quote_update_id[16];  /* bytes 10 to 25 */
  uint8_t order_id[8];          /* bytes 26 to 33 */
  uint8_t quote_symbol[6];      /* bytes 34 to 39 */
  uint8_t side;                 /* byte 40 */
  uint8_t cancel_reason;        /* byte 41 */
  uint8_t cancel_sub_reason;    /* byte 42 */
} QuoteCancelledMessage;

/* any Quote Cancelled Message at all: every byte one the checker chooses */
static void any_quote_cancelled_message(QuoteCancelledMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  record->cancel_reason = arbitrary();
  record->cancel_sub_reason = arbitrary();
}

/* Quote Cancelled Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancelled_message(const QuoteCancelledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  wire[at++] = record->side;
  wire[at++] = record->cancel_reason;
  wire[at++] = record->cancel_sub_reason;

  return at;
}

/* Quote Cancelled Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancelled_message(QuoteCancelledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  record->side = wire[at++];
  record->cancel_reason = wire[at++];
  record->cancel_sub_reason = wire[at++];

  return at;
}

/* what was read of Quote Cancelled Message is what was written, byte for byte */
static void equal_quote_cancelled_message(const QuoteCancelledMessage *read, const QuoteCancelledMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  assert(read->side == written->side);
  assert(read->cancel_reason == written->cancel_reason);
  assert(read->cancel_sub_reason == written->cancel_sub_reason);
}

/* Quote Cancelled Message: written and read back, then read and written back */
static void check_quote_cancelled_message(void) {
  QuoteCancelledMessage sent;
  QuoteCancelledMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_quote_cancelled_message(&sent);
  assert(encode_quote_cancelled_message(&sent, wire, 0) == 43);
  assert(decode_quote_cancelled_message(&got, wire, 0) == 43);
  equal_quote_cancelled_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancelled_message(&got, wire, 0) == 43);
  assert(encode_quote_cancelled_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Message: 99 bytes --------------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t in_flight[2];          /* bytes 0 to 1 */
  uint8_t transaction_time[8];   /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];         /* bytes 10 to 29 */
  uint8_t clearing_firm[4];      /* bytes 30 to 33 */
  uint8_t routing_firm_id[4];    /* bytes 34 to 37 */
  uint8_t cancel_reject_reason;  /* byte 38 */
  uint8_t text[60];              /* bytes 39 to 98 */
} CancelRejectedMessage;

/* any Cancel Rejected Message at all: every byte one the checker chooses */
static void any_cancel_rejected_message(CancelRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_message(const CancelRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_message(CancelRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected Message is what was written, byte for byte */
static void equal_cancel_rejected_message(const CancelRejectedMessage *read, const CancelRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected Message: written and read back, then read and written back */
static void check_cancel_rejected_message(void) {
  CancelRejectedMessage sent;
  CancelRejectedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_cancel_rejected_message(&sent);
  assert(encode_cancel_rejected_message(&sent, wire, 0) == 99);
  assert(decode_cancel_rejected_message(&got, wire, 0) == 99);
  equal_cancel_rejected_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_message(&got, wire, 0) == 99);
  assert(encode_cancel_rejected_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Message: 116 bytes -------------------------------------- */

/* An Order Execution message is sent for each fill on an order */
typedef struct {
  uint8_t in_flight[2];               /* bytes 0 to 1 */
  uint8_t transaction_time[8];        /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];              /* bytes 10 to 29 */
  uint8_t exec_id[8];                 /* bytes 30 to 37 */
  uint8_t last_shares[4];             /* bytes 38 to 41 */
  uint8_t last_px[8];                 /* bytes 42 to 49 */
  uint8_t leaves_qty[4];              /* bytes 50 to 53 */
  uint8_t base_liquidity_indicator;   /* byte 54 */
  uint8_t sub_liquidity_indicator;    /* byte 55 */
  uint8_t contra_broker[4];           /* bytes 56 to 59 */
  uint8_t side;                       /* byte 60 */
  uint8_t symbol[8];                  /* bytes 61 to 68 */
  uint8_t contra_trader[4];           /* bytes 69 to 72 */
  uint8_t clearing_firm[4];           /* bytes 73 to 76 */
  uint8_t contra_capacity;            /* byte 77 */
  uint8_t fee_code[2];                /* bytes 78 to 79 */
  uint8_t marketing_fee_code[2];      /* bytes 80 to 81 */
  uint8_t routing_firm_id[4];         /* bytes 82 to 85 */
  uint8_t cross_exclusion_indicator;  /* byte 86 */
  uint8_t trade_date[4];              /* bytes 87 to 90 */
  uint8_t multileg_reporting_type;    /* byte 91 */
  uint8_t secondary_exec_id[8];       /* bytes 92 to 99 */
  uint8_t price_type;                 /* byte 100 */
  uint8_t trade_through_alert_type;   /* byte 101 */
  uint8_t sender_location_id;         /* byte 102 */
  uint8_t floor_trader_acronym[3];    /* bytes 103 to 105 */
  uint8_t floor_trade_time[8];        /* bytes 106 to 113 */
  uint8_t ex_destination;             /* byte 114 */
  uint8_t equity_ex_destination;      /* byte 115 */
} OrderExecutionMessage;

/* any Order Execution Message at all: every byte one the checker chooses */
static void any_order_execution_message(OrderExecutionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contra_broker[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->contra_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  record->cross_exclusion_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->trade_through_alert_type = arbitrary();
  record->sender_location_id = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->floor_trade_time[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  record->equity_ex_destination = arbitrary();
}

/* Order Execution Message to the wire: 116 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_message(const OrderExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_broker[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_trader[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->contra_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->marketing_fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  wire[at++] = record->cross_exclusion_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->trade_through_alert_type;
  wire[at++] = record->sender_location_id;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->floor_trader_acronym[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->floor_trade_time[i]; }
  wire[at++] = record->ex_destination;
  wire[at++] = record->equity_ex_destination;

  return at;
}

/* Order Execution Message off the wire: 116 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_message(OrderExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contra_broker[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->contra_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  record->cross_exclusion_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->trade_through_alert_type = wire[at++];
  record->sender_location_id = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->floor_trade_time[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  record->equity_ex_destination = wire[at++];

  return at;
}

/* what was read of Order Execution Message is what was written, byte for byte */
static void equal_order_execution_message(const OrderExecutionMessage *read, const OrderExecutionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->contra_broker[i] == written->contra_broker[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_trader[i] == written->contra_trader[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->contra_capacity == written->contra_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->marketing_fee_code[i] == written->marketing_fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  assert(read->cross_exclusion_indicator == written->cross_exclusion_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  assert(read->price_type == written->price_type);
  assert(read->trade_through_alert_type == written->trade_through_alert_type);
  assert(read->sender_location_id == written->sender_location_id);
  for (size_t i = 0; i < 3; i++) { assert(read->floor_trader_acronym[i] == written->floor_trader_acronym[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->floor_trade_time[i] == written->floor_trade_time[i]); }
  assert(read->ex_destination == written->ex_destination);
  assert(read->equity_ex_destination == written->equity_ex_destination);
}

/* Order Execution Message: written and read back, then read and written back */
static void check_order_execution_message(void) {
  OrderExecutionMessage sent;
  OrderExecutionMessage got;
  uint8_t wire[116];
  uint8_t again[116];

  any_order_execution_message(&sent);
  assert(encode_order_execution_message(&sent, wire, 0) == 116);
  assert(decode_order_execution_message(&got, wire, 0) == 116);
  equal_order_execution_message(&got, &sent);

  for (size_t i = 0; i < 116; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_message(&got, wire, 0) == 116);
  assert(encode_order_execution_message(&got, again, 0) == 116);
  for (size_t i = 0; i < 116; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Execution Message: 84 bytes --------------------------------------- */

/* A Quote Execution message is used to indicate an execution has occurred on a resting quote */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t quote_update_id[16];       /* bytes 10 to 25 */
  uint8_t order_id[8];               /* bytes 26 to 33 */
  uint8_t exec_id[8];                /* bytes 34 to 41 */
  uint8_t quote_symbol[6];           /* bytes 42 to 47 */
  uint8_t clearing_firm[4];          /* bytes 48 to 51 */
  uint8_t last_shares[4];            /* bytes 52 to 55 */
  uint8_t last_px[8];                /* bytes 56 to 63 */
  uint8_t leaves_qty[4];             /* bytes 64 to 67 */
  uint8_t contra_trader[4];          /* bytes 68 to 71 */
  uint8_t contra_capacity;           /* byte 72 */
  uint8_t side;                      /* byte 73 */
  uint8_t base_liquidity_indicator;  /* byte 74 */
  uint8_t sub_liquidity_indicator;   /* byte 75 */
  uint8_t fee_code[2];               /* bytes 76 to 77 */
  uint8_t marketing_fee_code[2];     /* bytes 78 to 79 */
  uint8_t trade_date[4];             /* bytes 80 to 83 */
} QuoteExecutionMessage;

/* any Quote Execution Message at all: every byte one the checker chooses */
static void any_quote_execution_message(QuoteExecutionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = arbitrary(); }
  record->contra_capacity = arbitrary();
  record->side = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Quote Execution Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_quote_execution_message(const QuoteExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_trader[i]; }
  wire[at++] = record->contra_capacity;
  wire[at++] = record->side;
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->marketing_fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Quote Execution Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_quote_execution_message(QuoteExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = wire[at++]; }
  record->contra_capacity = wire[at++];
  record->side = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Execution Message is what was written, byte for byte */
static void equal_quote_execution_message(const QuoteExecutionMessage *read, const QuoteExecutionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_trader[i] == written->contra_trader[i]); }
  assert(read->contra_capacity == written->contra_capacity);
  assert(read->side == written->side);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->marketing_fee_code[i] == written->marketing_fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
}

/* Quote Execution Message: written and read back, then read and written back */
static void check_quote_execution_message(void) {
  QuoteExecutionMessage sent;
  QuoteExecutionMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_quote_execution_message(&sent);
  assert(encode_quote_execution_message(&sent, wire, 0) == 84);
  assert(decode_quote_execution_message(&got, wire, 0) == 84);
  equal_quote_execution_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_execution_message(&got, wire, 0) == 84);
  assert(encode_quote_execution_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Quote Execution Message: 93 bytes ------------------------------- */

/* A Complex Quote Execution message is used to indicate an execution has occurred on a resting complex quote */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t quote_update_id[16];       /* bytes 10 to 25 */
  uint8_t order_id[8];               /* bytes 26 to 33 */
  uint8_t exec_id[8];                /* bytes 34 to 41 */
  uint8_t quote_symbol[6];           /* bytes 42 to 47 */
  uint8_t clearing_firm[4];          /* bytes 48 to 51 */
  uint8_t last_shares[4];            /* bytes 52 to 55 */
  uint8_t last_px[8];                /* bytes 56 to 63 */
  uint8_t leaves_qty[4];             /* bytes 64 to 67 */
  uint8_t contra_trader[4];          /* bytes 68 to 71 */
  uint8_t contra_capacity;           /* byte 72 */
  uint8_t side;                      /* byte 73 */
  uint8_t base_liquidity_indicator;  /* byte 74 */
  uint8_t sub_liquidity_indicator;   /* byte 75 */
  uint8_t fee_code[2];               /* bytes 76 to 77 */
  uint8_t marketing_fee_code[2];     /* bytes 78 to 79 */
  uint8_t trade_date[4];             /* bytes 80 to 83 */
  uint8_t multileg_reporting_type;   /* byte 84 */
  uint8_t secondary_exec_id[8];      /* bytes 85 to 92 */
} ComplexQuoteExecutionMessage;

/* any Complex Quote Execution Message at all: every byte one the checker chooses */
static void any_complex_quote_execution_message(ComplexQuoteExecutionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = arbitrary(); }
  record->contra_capacity = arbitrary();
  record->side = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
  record->multileg_reporting_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = arbitrary(); }
}

/* Complex Quote Execution Message to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_complex_quote_execution_message(const ComplexQuoteExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->quote_update_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->quote_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_trader[i]; }
  wire[at++] = record->contra_capacity;
  wire[at++] = record->side;
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->marketing_fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }
  wire[at++] = record->multileg_reporting_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_exec_id[i]; }

  return at;
}

/* Complex Quote Execution Message off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_complex_quote_execution_message(ComplexQuoteExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->quote_update_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->quote_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = wire[at++]; }
  record->contra_capacity = wire[at++];
  record->side = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }
  record->multileg_reporting_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Quote Execution Message is what was written, byte for byte */
static void equal_complex_quote_execution_message(const ComplexQuoteExecutionMessage *read, const ComplexQuoteExecutionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->quote_update_id[i] == written->quote_update_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->quote_symbol[i] == written->quote_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_trader[i] == written->contra_trader[i]); }
  assert(read->contra_capacity == written->contra_capacity);
  assert(read->side == written->side);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->marketing_fee_code[i] == written->marketing_fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  assert(read->multileg_reporting_type == written->multileg_reporting_type);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
}

/* Complex Quote Execution Message: written and read back, then read and written back */
static void check_complex_quote_execution_message(void) {
  ComplexQuoteExecutionMessage sent;
  ComplexQuoteExecutionMessage got;
  uint8_t wire[93];
  uint8_t again[93];

  any_complex_quote_execution_message(&sent);
  assert(encode_complex_quote_execution_message(&sent, wire, 0) == 93);
  assert(decode_complex_quote_execution_message(&got, wire, 0) == 93);
  equal_complex_quote_execution_message(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_quote_execution_message(&got, wire, 0) == 93);
  assert(encode_complex_quote_execution_message(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct Message: 122 bytes --------------------------------- */

/* Used to relay a trade which has been cancelled (busted) or corrected */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t exec_ref_id[8];            /* bytes 38 to 45 */
  uint8_t side;                      /* byte 46 */
  uint8_t base_liquidity_indicator;  /* byte 47 */
  uint8_t sub_liquidity_indicator;   /* byte 48 */
  uint8_t clearing_firm[4];          /* bytes 49 to 52 */
  uint8_t clearing_account[4];       /* bytes 53 to 56 */
  uint8_t last_shares[4];            /* bytes 57 to 60 */
  uint8_t last_px[8];                /* bytes 61 to 68 */
  uint8_t corrected_price[8];        /* bytes 69 to 76 */
  uint8_t corrected_size[4];         /* bytes 77 to 80 */
  uint8_t orig_time[8];              /* bytes 81 to 88 */
  uint8_t symbol[8];                 /* bytes 89 to 96 */
  uint8_t maturity_date[4];          /* bytes 97 to 100 */
  uint8_t strike_price[8];           /* bytes 101 to 108 */
  uint8_t put_or_call;               /* byte 109 */
  uint8_t capacity;                  /* byte 110 */
  uint8_t open_close;                /* byte 111 */
  uint8_t marketing_fee_code[2];     /* bytes 112 to 113 */
  uint8_t target_party_id[4];        /* bytes 114 to 117 */
  uint8_t cmta_number[4];            /* bytes 118 to 121 */
} TradeCancelCorrectMessage;

/* any Trade Cancel Correct Message at all: every byte one the checker chooses */
static void any_trade_cancel_correct_message(TradeCancelCorrectMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->corrected_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  record->capacity = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
}

/* Trade Cancel Correct Message to the wire: 122 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct_message(const TradeCancelCorrectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_ref_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->corrected_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->corrected_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->put_or_call;
  wire[at++] = record->capacity;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->marketing_fee_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }

  return at;
}

/* Trade Cancel Correct Message off the wire: 122 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct_message(TradeCancelCorrectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_ref_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->corrected_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->corrected_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  record->capacity = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->marketing_fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel Correct Message is what was written, byte for byte */
static void equal_trade_cancel_correct_message(const TradeCancelCorrectMessage *read, const TradeCancelCorrectMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  assert(read->side == written->side);
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->corrected_price[i] == written->corrected_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->corrected_size[i] == written->corrected_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
  assert(read->capacity == written->capacity);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 2; i++) { assert(read->marketing_fee_code[i] == written->marketing_fee_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
}

/* Trade Cancel Correct Message: written and read back, then read and written back */
static void check_trade_cancel_correct_message(void) {
  TradeCancelCorrectMessage sent;
  TradeCancelCorrectMessage got;
  uint8_t wire[122];
  uint8_t again[122];

  any_trade_cancel_correct_message(&sent);
  assert(encode_trade_cancel_correct_message(&sent, wire, 0) == 122);
  assert(decode_trade_cancel_correct_message(&got, wire, 0) == 122);
  equal_trade_cancel_correct_message(&got, &sent);

  for (size_t i = 0; i < 122; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct_message(&got, wire, 0) == 122);
  assert(encode_trade_cancel_correct_message(&got, again, 0) == 122);
  for (size_t i = 0; i < 122; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected Message: 91 bytes ---------------------------------------- */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];   /* bytes 10 to 29 */
  uint8_t purge_reject_reason;  /* byte 30 */
  uint8_t text[60];             /* bytes 31 to 90 */
} PurgeRejectedMessage;

/* any Purge Rejected Message at all: every byte one the checker chooses */
static void any_purge_rejected_message(PurgeRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected_message(const PurgeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected_message(PurgeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected Message is what was written, byte for byte */
static void equal_purge_rejected_message(const PurgeRejectedMessage *read, const PurgeRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected Message: written and read back, then read and written back */
static void check_purge_rejected_message(void) {
  PurgeRejectedMessage sent;
  PurgeRejectedMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_purge_rejected_message(&sent);
  assert(encode_purge_rejected_message(&sent, wire, 0) == 91);
  assert(decode_purge_rejected_message(&got, wire, 0) == 91);
  equal_purge_rejected_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected_message(&got, wire, 0) == 91);
  assert(encode_purge_rejected_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Acknowledgement Message: 27 bytes ---------------------------- */

/* Response to a Reset Risk message request */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t risk_status_id[16];        /* bytes 2 to 17 */
  uint8_t risk_reset_result;         /* byte 18 */
  uint8_t request_received_time[8];  /* bytes 19 to 26 */
} ResetRiskAcknowledgementMessage;

/* any Reset Risk Acknowledgement Message at all: every byte one the checker chooses */
static void any_reset_risk_acknowledgement_message(ResetRiskAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  record->risk_reset_result = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Reset Risk Acknowledgement Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_acknowledgement_message(const ResetRiskAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  wire[at++] = record->risk_reset_result;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Reset Risk Acknowledgement Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_acknowledgement_message(ResetRiskAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  record->risk_reset_result = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Acknowledgement Message is what was written, byte for byte */
static void equal_reset_risk_acknowledgement_message(const ResetRiskAcknowledgementMessage *read, const ResetRiskAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  assert(read->risk_reset_result == written->risk_reset_result);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Reset Risk Acknowledgement Message: written and read back, then read and written back */
static void check_reset_risk_acknowledgement_message(void) {
  ResetRiskAcknowledgementMessage sent;
  ResetRiskAcknowledgementMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_reset_risk_acknowledgement_message(&sent);
  assert(encode_reset_risk_acknowledgement_message(&sent, wire, 0) == 27);
  assert(decode_reset_risk_acknowledgement_message(&got, wire, 0) == 27);
  equal_reset_risk_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_acknowledgement_message(&got, wire, 0) == 27);
  assert(encode_reset_risk_acknowledgement_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Acknowledgment Message: 42 bytes ---------------------------- */

/* A Mass Cancel Acknowledgment message is an unsequenced message sent when a Mass Cancel Order message requesting a mass cancellation has completed canceling all individual orders */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];        /* bytes 10 to 29 */
  uint8_t cancelled_order_count[4];  /* bytes 30 to 33 */
  uint8_t request_received_time[8];  /* bytes 34 to 41 */
} MassCancelAcknowledgmentMessage;

/* any Mass Cancel Acknowledgment Message at all: every byte one the checker chooses */
static void any_mass_cancel_acknowledgment_message(MassCancelAcknowledgmentMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Mass Cancel Acknowledgment Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_acknowledgment_message(const MassCancelAcknowledgmentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Mass Cancel Acknowledgment Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_acknowledgment_message(MassCancelAcknowledgmentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Acknowledgment Message is what was written, byte for byte */
static void equal_mass_cancel_acknowledgment_message(const MassCancelAcknowledgmentMessage *read, const MassCancelAcknowledgmentMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Mass Cancel Acknowledgment Message: written and read back, then read and written back */
static void check_mass_cancel_acknowledgment_message(void) {
  MassCancelAcknowledgmentMessage sent;
  MassCancelAcknowledgmentMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_mass_cancel_acknowledgment_message(&sent);
  assert(encode_mass_cancel_acknowledgment_message(&sent, wire, 0) == 42);
  assert(decode_mass_cancel_acknowledgment_message(&got, wire, 0) == 42);
  equal_mass_cancel_acknowledgment_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_acknowledgment_message(&got, wire, 0) == 42);
  assert(encode_mass_cancel_acknowledgment_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Rejected Message: 91 bytes ---------------------------------- */

/* A Mass Cancel Rejected message is sent in response to a Mass Cancel message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t in_flight[2];               /* bytes 0 to 1 */
  uint8_t transaction_time[8];        /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];         /* bytes 10 to 29 */
  uint8_t mass_cancel_reject_reason;  /* byte 30 */
  uint8_t text[60];                   /* bytes 31 to 90 */
} MassCancelRejectedMessage;

/* any Mass Cancel Rejected Message at all: every byte one the checker chooses */
static void any_mass_cancel_rejected_message(MassCancelRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->mass_cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Mass Cancel Rejected Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_rejected_message(const MassCancelRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->mass_cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Mass Cancel Rejected Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_rejected_message(MassCancelRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->mass_cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Rejected Message is what was written, byte for byte */
static void equal_mass_cancel_rejected_message(const MassCancelRejectedMessage *read, const MassCancelRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Mass Cancel Rejected Message: written and read back, then read and written back */
static void check_mass_cancel_rejected_message(void) {
  MassCancelRejectedMessage sent;
  MassCancelRejectedMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_mass_cancel_rejected_message(&sent);
  assert(encode_mass_cancel_rejected_message(&sent, wire, 0) == 91);
  assert(decode_mass_cancel_rejected_message(&got, wire, 0) == 91);
  equal_mass_cancel_rejected_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_rejected_message(&got, wire, 0) == 91);
  assert(encode_mass_cancel_rejected_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement Message: 43 bytes --------------------------------- */

/* A Purge Acknowledgment message is an unsequenced message sent when a Purge Orders message requesting an order purge has completed canceling all individual orders */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];        /* bytes 10 to 29 */
  uint8_t cancelled_order_count[4];  /* bytes 30 to 33 */
  uint8_t source_matching_unit;      /* byte 34 */
  uint8_t request_received_time[8];  /* bytes 35 to 42 */
} PurgeAcknowledgementMessage;

/* any Purge Acknowledgement Message at all: every byte one the checker chooses */
static void any_purge_acknowledgement_message(PurgeAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  record->source_matching_unit = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = arbitrary(); }
}

/* Purge Acknowledgement Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement_message(const PurgeAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  wire[at++] = record->source_matching_unit;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_received_time[i]; }

  return at;
}

/* Purge Acknowledgement Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement_message(PurgeAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  record->source_matching_unit = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->request_received_time[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement Message is what was written, byte for byte */
static void equal_purge_acknowledgement_message(const PurgeAcknowledgementMessage *read, const PurgeAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  assert(read->source_matching_unit == written->source_matching_unit);
  for (size_t i = 0; i < 8; i++) { assert(read->request_received_time[i] == written->request_received_time[i]); }
}

/* Purge Acknowledgement Message: written and read back, then read and written back */
static void check_purge_acknowledgement_message(void) {
  PurgeAcknowledgementMessage sent;
  PurgeAcknowledgementMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_purge_acknowledgement_message(&sent);
  assert(encode_purge_acknowledgement_message(&sent, wire, 0) == 43);
  assert(decode_purge_acknowledgement_message(&got, wire, 0) == 43);
  equal_purge_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement_message(&got, wire, 0) == 43);
  assert(encode_purge_acknowledgement_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Notification Message: 46 bytes ------------------------------------ */

/* One Purge Notification message is sent for each matching unit that cancelled orders for that order entry port */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];        /* bytes 10 to 29 */
  uint8_t cancelled_order_count[4];  /* bytes 30 to 33 */
  uint8_t source_matching_unit;      /* byte 34 */
  uint8_t clearing_firm[4];          /* bytes 35 to 38 */
  uint8_t risk_root[6];              /* bytes 39 to 44 */
  uint8_t mass_cancel_lockout;       /* byte 45 */
} PurgeNotificationMessage;

/* any Purge Notification Message at all: every byte one the checker chooses */
static void any_purge_notification_message(PurgeNotificationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
  record->source_matching_unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = arbitrary(); }
  record->mass_cancel_lockout = arbitrary();
}

/* Purge Notification Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_purge_notification_message(const PurgeNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }
  wire[at++] = record->source_matching_unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->risk_root[i]; }
  wire[at++] = record->mass_cancel_lockout;

  return at;
}

/* Purge Notification Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_purge_notification_message(PurgeNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }
  record->source_matching_unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = wire[at++]; }
  record->mass_cancel_lockout = wire[at++];

  return at;
}

/* what was read of Purge Notification Message is what was written, byte for byte */
static void equal_purge_notification_message(const PurgeNotificationMessage *read, const PurgeNotificationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
  assert(read->source_matching_unit == written->source_matching_unit);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->risk_root[i] == written->risk_root[i]); }
  assert(read->mass_cancel_lockout == written->mass_cancel_lockout);
}

/* Purge Notification Message: written and read back, then read and written back */
static void check_purge_notification_message(void) {
  PurgeNotificationMessage sent;
  PurgeNotificationMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_purge_notification_message(&sent);
  assert(encode_purge_notification_message(&sent, wire, 0) == 46);
  assert(decode_purge_notification_message(&got, wire, 0) == 46);
  equal_purge_notification_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_notification_message(&got, wire, 0) == 46);
  assert(encode_purge_notification_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Complex Instrument Rejected Message: 95 bytes ----------------------- */

/* The New Complex Instrument Rejected message is used to indicate that a requested complex strategy has been rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t no_of_securities[4];  /* bytes 30 to 33 */
  uint8_t order_reject_reason;  /* byte 34 */
  uint8_t text[60];             /* bytes 35 to 94 */
} NewComplexInstrumentRejectedMessage;

/* any New Complex Instrument Rejected Message at all: every byte one the checker chooses */
static void any_new_complex_instrument_rejected_message(NewComplexInstrumentRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->no_of_securities[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* New Complex Instrument Rejected Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_new_complex_instrument_rejected_message(const NewComplexInstrumentRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->no_of_securities[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* New Complex Instrument Rejected Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_new_complex_instrument_rejected_message(NewComplexInstrumentRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->no_of_securities[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of New Complex Instrument Rejected Message is what was written, byte for byte */
static void equal_new_complex_instrument_rejected_message(const NewComplexInstrumentRejectedMessage *read, const NewComplexInstrumentRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->no_of_securities[i] == written->no_of_securities[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* New Complex Instrument Rejected Message: written and read back, then read and written back */
static void check_new_complex_instrument_rejected_message(void) {
  NewComplexInstrumentRejectedMessage sent;
  NewComplexInstrumentRejectedMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_new_complex_instrument_rejected_message(&sent);
  assert(encode_new_complex_instrument_rejected_message(&sent, wire, 0) == 95);
  assert(decode_new_complex_instrument_rejected_message(&got, wire, 0) == 95);
  equal_new_complex_instrument_rejected_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_new_complex_instrument_rejected_message(&got, wire, 0) == 95);
  assert(encode_new_complex_instrument_rejected_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
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

/* ---- Carried Restatement Message: 240 bytes ---------------------------------- */

/* The Carried Restatement message is used to indicate the restoration of a multi-day GTC or GTD order at the start of a new business day */
typedef struct {
  uint8_t in_flight[2];                /* bytes 0 to 1 */
  uint8_t transaction_time[8];         /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];               /* bytes 10 to 29 */
  uint8_t order_id[8];                 /* bytes 30 to 37 */
  uint8_t side;                        /* byte 38 */
  uint8_t price[8];                    /* bytes 39 to 46 */
  uint8_t exec_inst;                   /* byte 47 */
  uint8_t ord_type;                    /* byte 48 */
  uint8_t time_in_force;               /* byte 49 */
  uint8_t min_qty[4];                  /* bytes 50 to 53 */
  uint8_t symbol[8];                   /* bytes 54 to 61 */
  uint8_t capacity;                    /* byte 62 */
  uint8_t account[16];                 /* bytes 63 to 78 */
  uint8_t clearing_firm[4];            /* bytes 79 to 82 */
  uint8_t clearing_account[4];         /* bytes 83 to 86 */
  uint8_t display_indicator;           /* byte 87 */
  uint8_t max_floor[4];                /* bytes 88 to 91 */
  uint8_t order_qty[4];                /* bytes 92 to 95 */
  PreventMatch prevent_match;          /* bytes 96 to 98 */
  uint8_t maturity_date[4];            /* bytes 99 to 102 */
  uint8_t strike_price[8];             /* bytes 103 to 110 */
  uint8_t put_or_call;                 /* byte 111 */
  uint8_t open_close;                  /* byte 112 */
  uint8_t leaves_qty[4];               /* bytes 113 to 116 */
  uint8_t display_price[8];            /* bytes 117 to 124 */
  uint8_t working_price[8];            /* bytes 125 to 132 */
  uint8_t expire_time[8];              /* bytes 133 to 140 */
  uint8_t attributed_quote;            /* byte 141 */
  uint8_t stop_px[8];                  /* bytes 142 to 149 */
  uint8_t routing_inst[4];             /* bytes 150 to 153 */
  uint8_t rout_strategy[6];            /* bytes 154 to 159 */
  uint8_t route_delivery_method[3];    /* bytes 160 to 162 */
  uint8_t ex_destination;              /* byte 163 */
  uint8_t target_party_id[4];          /* bytes 164 to 167 */
  uint8_t auction_id[8];               /* bytes 168 to 175 */
  uint8_t cmta_number[4];              /* bytes 176 to 179 */
  uint8_t routing_firm_id[4];          /* bytes 180 to 183 */
  uint8_t clearing_optional_data[16];  /* bytes 184 to 199 */
  uint8_t cum_qty[4];                  /* bytes 200 to 203 */
  uint8_t drill_thru_protection[8];    /* bytes 204 to 211 */
  uint8_t equity_party_id[4];          /* bytes 212 to 215 */
  uint8_t client_id_attr[4];           /* bytes 216 to 219 */
  uint8_t frequent_trader_id[6];       /* bytes 220 to 225 */
  uint8_t session_eligibility;         /* byte 226 */
  uint8_t combo_order;                 /* byte 227 */
  uint8_t compression;                 /* byte 228 */
  uint8_t floor_destination[4];        /* bytes 229 to 232 */
  uint8_t floor_routing_inst;          /* byte 233 */
  uint8_t order_origin[3];             /* bytes 234 to 236 */
  uint8_t price_type;                  /* byte 237 */
  uint8_t strategy_id;                 /* byte 238 */
  uint8_t held;                        /* byte 239 */
} CarriedRestatementMessage;

/* any Carried Restatement Message at all: every byte one the checker chooses */
static void any_carried_restatement_message(CarriedRestatementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->ord_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  any_prevent_match(&record->prevent_match);
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  record->attributed_quote = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_inst[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clearing_optional_data[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->drill_thru_protection[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->equity_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id_attr[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->session_eligibility = arbitrary();
  record->combo_order = arbitrary();
  record->compression = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->floor_destination[i] = arbitrary(); }
  record->floor_routing_inst = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->order_origin[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->strategy_id = arbitrary();
  record->held = arbitrary();
}

/* Carried Restatement Message to the wire: 240 bytes from at, returning where the next byte goes */
static size_t encode_carried_restatement_message(const CarriedRestatementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->ord_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  at = encode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->put_or_call;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  wire[at++] = record->attributed_quote;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_inst[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->rout_strategy[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->route_delivery_method[i]; }
  wire[at++] = record->ex_destination;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clearing_optional_data[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->drill_thru_protection[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->equity_party_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id_attr[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->session_eligibility;
  wire[at++] = record->combo_order;
  wire[at++] = record->compression;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->floor_destination[i]; }
  wire[at++] = record->floor_routing_inst;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->order_origin[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->strategy_id;
  wire[at++] = record->held;

  return at;
}

/* Carried Restatement Message off the wire: 240 bytes from at, returning where the next byte lies */
static size_t decode_carried_restatement_message(CarriedRestatementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->ord_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  at = decode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  record->attributed_quote = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_inst[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clearing_optional_data[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->drill_thru_protection[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->equity_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id_attr[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->session_eligibility = wire[at++];
  record->combo_order = wire[at++];
  record->compression = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->floor_destination[i] = wire[at++]; }
  record->floor_routing_inst = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->order_origin[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->strategy_id = wire[at++];
  record->held = wire[at++];

  return at;
}

/* what was read of Carried Restatement Message is what was written, byte for byte */
static void equal_carried_restatement_message(const CarriedRestatementMessage *read, const CarriedRestatementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->ord_type == written->ord_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  equal_prevent_match(&read->prevent_match, &written->prevent_match);
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  assert(read->attributed_quote == written->attributed_quote);
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_inst[i] == written->routing_inst[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->rout_strategy[i] == written->rout_strategy[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->route_delivery_method[i] == written->route_delivery_method[i]); }
  assert(read->ex_destination == written->ex_destination);
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clearing_optional_data[i] == written->clearing_optional_data[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->drill_thru_protection[i] == written->drill_thru_protection[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->equity_party_id[i] == written->equity_party_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id_attr[i] == written->client_id_attr[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->session_eligibility == written->session_eligibility);
  assert(read->combo_order == written->combo_order);
  assert(read->compression == written->compression);
  for (size_t i = 0; i < 4; i++) { assert(read->floor_destination[i] == written->floor_destination[i]); }
  assert(read->floor_routing_inst == written->floor_routing_inst);
  for (size_t i = 0; i < 3; i++) { assert(read->order_origin[i] == written->order_origin[i]); }
  assert(read->price_type == written->price_type);
  assert(read->strategy_id == written->strategy_id);
  assert(read->held == written->held);
}

/* Carried Restatement Message: written and read back, then read and written back */
static void check_carried_restatement_message(void) {
  CarriedRestatementMessage sent;
  CarriedRestatementMessage got;
  uint8_t wire[240];
  uint8_t again[240];

  any_carried_restatement_message(&sent);
  assert(encode_carried_restatement_message(&sent, wire, 0) == 240);
  assert(decode_carried_restatement_message(&got, wire, 0) == 240);
  equal_carried_restatement_message(&got, &sent);

  for (size_t i = 0; i < 240; i++) { wire[i] = arbitrary(); }
  assert(decode_carried_restatement_message(&got, wire, 0) == 240);
  assert(encode_carried_restatement_message(&got, again, 0) == 240);
  for (size_t i = 0; i < 240; i++) { assert(again[i] == wire[i]); }
}

/* ---- Done For Day Message: 46 bytes ------------------------------------------ */

/* The Done For Day messages represent orders persisted during the current day session to carry over to the next session */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t clearing_firm[4];     /* bytes 30 to 33 */
  uint8_t routing_firm_id[4];   /* bytes 34 to 37 */
  uint8_t symbol[8];            /* bytes 38 to 45 */
} DoneForDayMessage;

/* any Done For Day Message at all: every byte one the checker chooses */
static void any_done_for_day_message(DoneForDayMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
}

/* Done For Day Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_done_for_day_message(const DoneForDayMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Done For Day Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_done_for_day_message(DoneForDayMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Done For Day Message is what was written, byte for byte */
static void equal_done_for_day_message(const DoneForDayMessage *read, const DoneForDayMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Done For Day Message: written and read back, then read and written back */
static void check_done_for_day_message(void) {
  DoneForDayMessage sent;
  DoneForDayMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_done_for_day_message(&sent);
  assert(encode_done_for_day_message(&sent, wire, 0) == 46);
  assert(decode_done_for_day_message(&got, wire, 0) == 46);
  equal_done_for_day_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_done_for_day_message(&got, wire, 0) == 46);
  assert(encode_done_for_day_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Floor Trade Notification Message: 69 bytes ------------------------------ */

/* TPHs with Market Makers on the Cboe trading floor may optionally receive Floor Trade Notification messages */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t exec_id[8];                /* bytes 10 to 17 */
  uint8_t symbol[8];                 /* bytes 18 to 25 */
  uint8_t put_or_call;               /* byte 26 */
  uint8_t strike_price[8];           /* bytes 27 to 34 */
  uint8_t maturity_date[4];          /* bytes 35 to 38 */
  uint8_t order_qty[4];              /* bytes 39 to 42 */
  uint8_t price[8];                  /* bytes 43 to 50 */
  uint8_t side;                      /* byte 51 */
  uint8_t contra_trader[4];          /* bytes 52 to 55 */
  uint8_t floor_trader_acronym[3];   /* bytes 56 to 58 */
  uint8_t floor_trade_time[8];       /* bytes 59 to 66 */
  uint8_t trade_through_alert_type;  /* byte 67 */
  uint8_t price_type;                /* byte 68 */
} FloorTradeNotificationMessage;

/* any Floor Trade Notification Message at all: every byte one the checker chooses */
static void any_floor_trade_notification_message(FloorTradeNotificationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->floor_trade_time[i] = arbitrary(); }
  record->trade_through_alert_type = arbitrary();
  record->price_type = arbitrary();
}

/* Floor Trade Notification Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_floor_trade_notification_message(const FloorTradeNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_trader[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->floor_trader_acronym[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->floor_trade_time[i]; }
  wire[at++] = record->trade_through_alert_type;
  wire[at++] = record->price_type;

  return at;
}

/* Floor Trade Notification Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_floor_trade_notification_message(FloorTradeNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->contra_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->floor_trade_time[i] = wire[at++]; }
  record->trade_through_alert_type = wire[at++];
  record->price_type = wire[at++];

  return at;
}

/* what was read of Floor Trade Notification Message is what was written, byte for byte */
static void equal_floor_trade_notification_message(const FloorTradeNotificationMessage *read, const FloorTradeNotificationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->contra_trader[i] == written->contra_trader[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->floor_trader_acronym[i] == written->floor_trader_acronym[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->floor_trade_time[i] == written->floor_trade_time[i]); }
  assert(read->trade_through_alert_type == written->trade_through_alert_type);
  assert(read->price_type == written->price_type);
}

/* Floor Trade Notification Message: written and read back, then read and written back */
static void check_floor_trade_notification_message(void) {
  FloorTradeNotificationMessage sent;
  FloorTradeNotificationMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_floor_trade_notification_message(&sent);
  assert(encode_floor_trade_notification_message(&sent, wire, 0) == 69);
  assert(decode_floor_trade_notification_message(&got, wire, 0) == 69);
  equal_floor_trade_notification_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_floor_trade_notification_message(&got, wire, 0) == 69);
  assert(encode_floor_trade_notification_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Floor Trade Confirmation Rejected Message: 99 bytes --------------------- */

/* The Add Floor Trade Rejected message is used to indicate that a requested Add Floor Trade message has been rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t exec_id[8];           /* bytes 30 to 37 */
  uint8_t order_reject_reason;  /* byte 38 */
  uint8_t text[60];             /* bytes 39 to 98 */
} FloorTradeConfirmationRejectedMessage;

/* any Floor Trade Confirmation Rejected Message at all: every byte one the checker chooses */
static void any_floor_trade_confirmation_rejected_message(FloorTradeConfirmationRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Floor Trade Confirmation Rejected Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_floor_trade_confirmation_rejected_message(const FloorTradeConfirmationRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Floor Trade Confirmation Rejected Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_floor_trade_confirmation_rejected_message(FloorTradeConfirmationRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Floor Trade Confirmation Rejected Message is what was written, byte for byte */
static void equal_floor_trade_confirmation_rejected_message(const FloorTradeConfirmationRejectedMessage *read, const FloorTradeConfirmationRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Floor Trade Confirmation Rejected Message: written and read back, then read and written back */
static void check_floor_trade_confirmation_rejected_message(void) {
  FloorTradeConfirmationRejectedMessage sent;
  FloorTradeConfirmationRejectedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_floor_trade_confirmation_rejected_message(&sent);
  assert(encode_floor_trade_confirmation_rejected_message(&sent, wire, 0) == 99);
  assert(decode_floor_trade_confirmation_rejected_message(&got, wire, 0) == 99);
  equal_floor_trade_confirmation_rejected_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_floor_trade_confirmation_rejected_message(&got, wire, 0) == 99);
  assert(encode_floor_trade_confirmation_rejected_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Floor Trade Rejected Message: 91 bytes ------------------------------ */

/* The Add Floor Trade Rejected message is used to indicate that a requested Add Floor Trade message has been rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t order_reject_reason;  /* byte 30 */
  uint8_t text[60];             /* bytes 31 to 90 */
} AddFloorTradeRejectedMessage;

/* any Add Floor Trade Rejected Message at all: every byte one the checker chooses */
static void any_add_floor_trade_rejected_message(AddFloorTradeRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Add Floor Trade Rejected Message to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_add_floor_trade_rejected_message(const AddFloorTradeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Add Floor Trade Rejected Message off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_add_floor_trade_rejected_message(AddFloorTradeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Add Floor Trade Rejected Message is what was written, byte for byte */
static void equal_add_floor_trade_rejected_message(const AddFloorTradeRejectedMessage *read, const AddFloorTradeRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Add Floor Trade Rejected Message: written and read back, then read and written back */
static void check_add_floor_trade_rejected_message(void) {
  AddFloorTradeRejectedMessage sent;
  AddFloorTradeRejectedMessage got;
  uint8_t wire[91];
  uint8_t again[91];

  any_add_floor_trade_rejected_message(&sent);
  assert(encode_add_floor_trade_rejected_message(&sent, wire, 0) == 91);
  assert(decode_add_floor_trade_rejected_message(&got, wire, 0) == 91);
  equal_add_floor_trade_rejected_message(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_add_floor_trade_rejected_message(&got, wire, 0) == 91);
  assert(encode_add_floor_trade_rejected_message(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Floor Trade Rejected Message: 99 bytes --------------------------- */

/* The Delete Floor Trade Rejected message is used to indicate that a requested Delete Floor Trade message has been rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t exec_id[8];           /* bytes 30 to 37 */
  uint8_t order_reject_reason;  /* byte 38 */
  uint8_t text[60];             /* bytes 39 to 98 */
} DeleteFloorTradeRejectedMessage;

/* any Delete Floor Trade Rejected Message at all: every byte one the checker chooses */
static void any_delete_floor_trade_rejected_message(DeleteFloorTradeRejectedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Delete Floor Trade Rejected Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_delete_floor_trade_rejected_message(const DeleteFloorTradeRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Delete Floor Trade Rejected Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_delete_floor_trade_rejected_message(DeleteFloorTradeRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Floor Trade Rejected Message is what was written, byte for byte */
static void equal_delete_floor_trade_rejected_message(const DeleteFloorTradeRejectedMessage *read, const DeleteFloorTradeRejectedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Delete Floor Trade Rejected Message: written and read back, then read and written back */
static void check_delete_floor_trade_rejected_message(void) {
  DeleteFloorTradeRejectedMessage sent;
  DeleteFloorTradeRejectedMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_delete_floor_trade_rejected_message(&sent);
  assert(encode_delete_floor_trade_rejected_message(&sent, wire, 0) == 99);
  assert(decode_delete_floor_trade_rejected_message(&got, wire, 0) == 99);
  equal_delete_floor_trade_rejected_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_floor_trade_rejected_message(&got, wire, 0) == 99);
  assert(encode_delete_floor_trade_rejected_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Floor Order Represented Message: 50 bytes ------------------------------- */

/* Orders routed to the trading floor will be represented before being traded in open outcry */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t clearing_firm[4];          /* bytes 38 to 41 */
  uint8_t routing_firm_id[4];        /* bytes 42 to 45 */
  uint8_t floor_trader_acronym[3];   /* bytes 46 to 48 */
  uint8_t order_restatement_reason;  /* byte 49 */
} FloorOrderRepresentedMessage;

/* any Floor Order Represented Message at all: every byte one the checker chooses */
static void any_floor_order_represented_message(FloorOrderRepresentedMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = arbitrary(); }
  record->order_restatement_reason = arbitrary();
}

/* Floor Order Represented Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_floor_order_represented_message(const FloorOrderRepresentedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->floor_trader_acronym[i]; }
  wire[at++] = record->order_restatement_reason;

  return at;
}

/* Floor Order Represented Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_floor_order_represented_message(FloorOrderRepresentedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->floor_trader_acronym[i] = wire[at++]; }
  record->order_restatement_reason = wire[at++];

  return at;
}

/* what was read of Floor Order Represented Message is what was written, byte for byte */
static void equal_floor_order_represented_message(const FloorOrderRepresentedMessage *read, const FloorOrderRepresentedMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->floor_trader_acronym[i] == written->floor_trader_acronym[i]); }
  assert(read->order_restatement_reason == written->order_restatement_reason);
}

/* Floor Order Represented Message: written and read back, then read and written back */
static void check_floor_order_represented_message(void) {
  FloorOrderRepresentedMessage sent;
  FloorOrderRepresentedMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_floor_order_represented_message(&sent);
  assert(encode_floor_order_represented_message(&sent, wire, 0) == 50);
  assert(decode_floor_order_represented_message(&got, wire, 0) == 50);
  equal_floor_order_represented_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_floor_order_represented_message(&got, wire, 0) == 50);
  assert(encode_floor_order_represented_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Floor Trade Acknowledgement Message: 38 bytes -------------------- */

/* A Delete Floor Trade Acknowledgment message is an unsequenced message sent when a Delete Floor Trade message has been accepted */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t exec_id[8];           /* bytes 30 to 37 */
} DeleteFloorTradeAcknowledgementMessage;

/* any Delete Floor Trade Acknowledgement Message at all: every byte one the checker chooses */
static void any_delete_floor_trade_acknowledgement_message(DeleteFloorTradeAcknowledgementMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
}

/* Delete Floor Trade Acknowledgement Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_delete_floor_trade_acknowledgement_message(const DeleteFloorTradeAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }

  return at;
}

/* Delete Floor Trade Acknowledgement Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_delete_floor_trade_acknowledgement_message(DeleteFloorTradeAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Floor Trade Acknowledgement Message is what was written, byte for byte */
static void equal_delete_floor_trade_acknowledgement_message(const DeleteFloorTradeAcknowledgementMessage *read, const DeleteFloorTradeAcknowledgementMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
}

/* Delete Floor Trade Acknowledgement Message: written and read back, then read and written back */
static void check_delete_floor_trade_acknowledgement_message(void) {
  DeleteFloorTradeAcknowledgementMessage sent;
  DeleteFloorTradeAcknowledgementMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_delete_floor_trade_acknowledgement_message(&sent);
  assert(encode_delete_floor_trade_acknowledgement_message(&sent, wire, 0) == 38);
  assert(decode_delete_floor_trade_acknowledgement_message(&got, wire, 0) == 38);
  equal_delete_floor_trade_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_floor_trade_acknowledgement_message(&got, wire, 0) == 38);
  assert(encode_delete_floor_trade_acknowledgement_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_order_acknowledgement_message();
  check_order_rejected_message();
  check_cross_order_rejected_message();
  check_quote_update_rejected_message();
  check_order_modified_message();
  check_order_restated_message();
  check_quote_restated_message();
  check_modify_rejected_message();
  check_order_cancelled_message();
  check_quote_cancelled_message();
  check_cancel_rejected_message();
  check_order_execution_message();
  check_quote_execution_message();
  check_complex_quote_execution_message();
  check_trade_cancel_correct_message();
  check_purge_rejected_message();
  check_reset_risk_acknowledgement_message();
  check_mass_cancel_acknowledgment_message();
  check_mass_cancel_rejected_message();
  check_purge_acknowledgement_message();
  check_purge_notification_message();
  check_new_complex_instrument_rejected_message();
  check_prevent_match();
  check_carried_restatement_message();
  check_done_for_day_message();
  check_floor_trade_notification_message();
  check_floor_trade_confirmation_rejected_message();
  check_add_floor_trade_rejected_message();
  check_delete_floor_trade_rejected_message();
  check_floor_order_represented_message();
  check_delete_floor_trade_acknowledgement_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
