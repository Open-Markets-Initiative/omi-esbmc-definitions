// cboe/edgaequities/binaryorderentry/EdgaEquities_BinaryOrderEntry_v1_0_14_Exchange.c
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

/* ---- Order Acknowledgement Us Equities V 1: 82 bytes ------------------------- */

/* Order Acknowledgment messages are sent in response to New Order messages */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t side;                      /* byte 38 */
  uint8_t price[8];                  /* bytes 39 to 46 */
  uint8_t ord_type;                  /* byte 47 */
  uint8_t symbol[8];                 /* bytes 48 to 55 */
  uint8_t clearing_firm[4];          /* bytes 56 to 59 */
  uint8_t leaves_qty[4];             /* bytes 60 to 63 */
  uint8_t display_price[8];          /* bytes 64 to 71 */
  uint8_t working_price[8];          /* bytes 72 to 79 */
  uint8_t base_liquidity_indicator;  /* byte 80 */
  uint8_t sub_liquidity_indicator;   /* byte 81 */
} OrderAcknowledgementUsEquitiesV1;

/* any Order Acknowledgement Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_acknowledgement_us_equities_v1(OrderAcknowledgementUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  record->sub_liquidity_indicator = arbitrary();
}

/* Order Acknowledgement Us Equities V 1 to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement_us_equities_v1(const OrderAcknowledgementUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  wire[at++] = record->sub_liquidity_indicator;

  return at;
}

/* Order Acknowledgement Us Equities V 1 off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement_us_equities_v1(OrderAcknowledgementUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  record->sub_liquidity_indicator = wire[at++];

  return at;
}

/* what was read of Order Acknowledgement Us Equities V 1 is what was written, byte for byte */
static void equal_order_acknowledgement_us_equities_v1(const OrderAcknowledgementUsEquitiesV1 *read, const OrderAcknowledgementUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  assert(read->sub_liquidity_indicator == written->sub_liquidity_indicator);
}

/* Order Acknowledgement Us Equities V 1: written and read back, then read and written back */
static void check_order_acknowledgement_us_equities_v1(void) {
  OrderAcknowledgementUsEquitiesV1 sent;
  OrderAcknowledgementUsEquitiesV1 got;
  uint8_t wire[82];
  uint8_t again[82];

  any_order_acknowledgement_us_equities_v1(&sent);
  assert(encode_order_acknowledgement_us_equities_v1(&sent, wire, 0) == 82);
  assert(decode_order_acknowledgement_us_equities_v1(&got, wire, 0) == 82);
  equal_order_acknowledgement_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement_us_equities_v1(&got, wire, 0) == 82);
  assert(encode_order_acknowledgement_us_equities_v1(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Rejected Us Equities V 1: 95 bytes -------------------------------- */

/* Order Rejected messages are sent in response to a New Order message which must be rejected */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];        /* bytes 10 to 29 */
  uint8_t clearing_firm[4];     /* bytes 30 to 33 */
  uint8_t order_reject_reason;  /* byte 34 */
  uint8_t text[60];             /* bytes 35 to 94 */
} OrderRejectedUsEquitiesV1;

/* any Order Rejected Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_rejected_us_equities_v1(OrderRejectedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->order_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Order Rejected Us Equities V 1 to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_order_rejected_us_equities_v1(const OrderRejectedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->order_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Rejected Us Equities V 1 off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_order_rejected_us_equities_v1(OrderRejectedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->order_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Rejected Us Equities V 1 is what was written, byte for byte */
static void equal_order_rejected_us_equities_v1(const OrderRejectedUsEquitiesV1 *read, const OrderRejectedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->order_reject_reason == written->order_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Rejected Us Equities V 1: written and read back, then read and written back */
static void check_order_rejected_us_equities_v1(void) {
  OrderRejectedUsEquitiesV1 sent;
  OrderRejectedUsEquitiesV1 got;
  uint8_t wire[95];
  uint8_t again[95];

  any_order_rejected_us_equities_v1(&sent);
  assert(encode_order_rejected_us_equities_v1(&sent, wire, 0) == 95);
  assert(decode_order_rejected_us_equities_v1(&got, wire, 0) == 95);
  equal_order_rejected_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_order_rejected_us_equities_v1(&got, wire, 0) == 95);
  assert(encode_order_rejected_us_equities_v1(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modified Us Equities V 1: 125 bytes ------------------------------- */

/* Order Modified messages are sent in response to a Modify Request message to indicate that the order has been successfully modified */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t orig_cl_ord_id[20];        /* bytes 30 to 49 */
  uint8_t order_id[8];               /* bytes 50 to 57 */
  uint8_t clearing_firm[4];          /* bytes 58 to 61 */
  uint8_t symbol[8];                 /* bytes 62 to 69 */
  uint8_t side;                      /* byte 70 */
  uint8_t price[8];                  /* bytes 71 to 78 */
  uint8_t ord_type;                  /* byte 79 */
  uint8_t max_floor[4];              /* bytes 80 to 83 */
  uint8_t order_qty[4];              /* bytes 84 to 87 */
  uint8_t stop_px[8];                /* bytes 88 to 95 */
  uint8_t leaves_qty[4];             /* bytes 96 to 99 */
  uint8_t display_price[8];          /* bytes 100 to 107 */
  uint8_t working_price[8];          /* bytes 108 to 115 */
  uint8_t base_liquidity_indicator;  /* byte 116 */
  uint8_t secondary_order_id[8];     /* bytes 117 to 124 */
} OrderModifiedUsEquitiesV1;

/* any Order Modified Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_modified_us_equities_v1(OrderModifiedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->base_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
}

/* Order Modified Us Equities V 1 to the wire: 125 bytes from at, returning where the next byte goes */
static size_t encode_order_modified_us_equities_v1(const OrderModifiedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->base_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }

  return at;
}

/* Order Modified Us Equities V 1 off the wire: 125 bytes from at, returning where the next byte lies */
static size_t decode_order_modified_us_equities_v1(OrderModifiedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->base_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modified Us Equities V 1 is what was written, byte for byte */
static void equal_order_modified_us_equities_v1(const OrderModifiedUsEquitiesV1 *read, const OrderModifiedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->base_liquidity_indicator == written->base_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
}

/* Order Modified Us Equities V 1: written and read back, then read and written back */
static void check_order_modified_us_equities_v1(void) {
  OrderModifiedUsEquitiesV1 sent;
  OrderModifiedUsEquitiesV1 got;
  uint8_t wire[125];
  uint8_t again[125];

  any_order_modified_us_equities_v1(&sent);
  assert(encode_order_modified_us_equities_v1(&sent, wire, 0) == 125);
  assert(decode_order_modified_us_equities_v1(&got, wire, 0) == 125);
  equal_order_modified_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 125; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modified_us_equities_v1(&got, wire, 0) == 125);
  assert(encode_order_modified_us_equities_v1(&got, again, 0) == 125);
  for (size_t i = 0; i < 125; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Restated Us Equities V 1: 108 bytes ------------------------------- */

/* Order Restated messages are sent to inform the Member that an order has been asynchronously modified for some reason without an explicit Modify Order message request having been sent */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t cl_ord_id[20];             /* bytes 10 to 29 */
  uint8_t order_id[8];               /* bytes 30 to 37 */
  uint8_t clearing_firm[4];          /* bytes 38 to 41 */
  uint8_t symbol[8];                 /* bytes 42 to 49 */
  uint8_t order_restatement_reason;  /* byte 50 */
  uint8_t order_qty[4];              /* bytes 51 to 54 */
  uint8_t price[8];                  /* bytes 55 to 62 */
  uint8_t leaves_qty[4];             /* bytes 63 to 66 */
  uint8_t display_price[8];          /* bytes 67 to 74 */
  uint8_t working_price[8];          /* bytes 75 to 82 */
  uint8_t base_liquidity_indicator;  /* byte 83 */
  uint8_t secondary_order_id[8];     /* bytes 84 to 91 */
  uint8_t last_shares[4];            /* bytes 92 to 95 */
  uint8_t last_px[8];                /* bytes 96 to 103 */
  uint8_t cmc_match_qty[4];          /* bytes 104 to 107 */
} OrderRestatedUsEquitiesV1;

/* any Order Restated Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_restated_us_equities_v1(OrderRestatedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { record->cmc_match_qty[i] = arbitrary(); }
}

/* Order Restated Us Equities V 1 to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_order_restated_us_equities_v1(const OrderRestatedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmc_match_qty[i]; }

  return at;
}

/* Order Restated Us Equities V 1 off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_order_restated_us_equities_v1(OrderRestatedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { record->cmc_match_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Restated Us Equities V 1 is what was written, byte for byte */
static void equal_order_restated_us_equities_v1(const OrderRestatedUsEquitiesV1 *read, const OrderRestatedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
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
  for (size_t i = 0; i < 4; i++) { assert(read->cmc_match_qty[i] == written->cmc_match_qty[i]); }
}

/* Order Restated Us Equities V 1: written and read back, then read and written back */
static void check_order_restated_us_equities_v1(void) {
  OrderRestatedUsEquitiesV1 sent;
  OrderRestatedUsEquitiesV1 got;
  uint8_t wire[108];
  uint8_t again[108];

  any_order_restated_us_equities_v1(&sent);
  assert(encode_order_restated_us_equities_v1(&sent, wire, 0) == 108);
  assert(decode_order_restated_us_equities_v1(&got, wire, 0) == 108);
  equal_order_restated_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_order_restated_us_equities_v1(&got, wire, 0) == 108);
  assert(encode_order_restated_us_equities_v1(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Rejected Us Equities V 1: 115 bytes ------------------------------ */

/* User Modify Rejected messages are sent in response to a Modify Order message for an order which cannot be modified */
typedef struct {
  uint8_t in_flight[2];          /* bytes 0 to 1 */
  uint8_t transaction_time[8];   /* bytes 2 to 9 */
  uint8_t clearing_firm[4];      /* bytes 10 to 13 */
  uint8_t cl_ord_id[20];         /* bytes 14 to 33 */
  uint8_t orig_cl_ord_id[20];    /* bytes 34 to 53 */
  uint8_t modify_reject_reason;  /* byte 54 */
  uint8_t text[60];              /* bytes 55 to 114 */
} ModifyRejectedUsEquitiesV1;

/* any Modify Rejected Us Equities V 1 at all: every byte one the checker chooses */
static void any_modify_rejected_us_equities_v1(ModifyRejectedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->modify_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Modify Rejected Us Equities V 1 to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_modify_rejected_us_equities_v1(const ModifyRejectedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->modify_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Modify Rejected Us Equities V 1 off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_modify_rejected_us_equities_v1(ModifyRejectedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->modify_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Rejected Us Equities V 1 is what was written, byte for byte */
static void equal_modify_rejected_us_equities_v1(const ModifyRejectedUsEquitiesV1 *read, const ModifyRejectedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->modify_reject_reason == written->modify_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Modify Rejected Us Equities V 1: written and read back, then read and written back */
static void check_modify_rejected_us_equities_v1(void) {
  ModifyRejectedUsEquitiesV1 sent;
  ModifyRejectedUsEquitiesV1 got;
  uint8_t wire[115];
  uint8_t again[115];

  any_modify_rejected_us_equities_v1(&sent);
  assert(encode_modify_rejected_us_equities_v1(&sent, wire, 0) == 115);
  assert(decode_modify_rejected_us_equities_v1(&got, wire, 0) == 115);
  equal_modify_rejected_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_rejected_us_equities_v1(&got, wire, 0) == 115);
  assert(encode_modify_rejected_us_equities_v1(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancelled Us Equities V 1: 35 bytes ------------------------------- */

/* This message indicates an order has been cancelled */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t clearing_firm[4];     /* bytes 10 to 13 */
  uint8_t cl_ord_id[20];        /* bytes 14 to 33 */
  uint8_t cancel_reason;        /* byte 34 */
} OrderCancelledUsEquitiesV1;

/* any Order Cancelled Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_cancelled_us_equities_v1(OrderCancelledUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Cancelled Us Equities V 1 to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_order_cancelled_us_equities_v1(const OrderCancelledUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Cancelled Us Equities V 1 off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_order_cancelled_us_equities_v1(OrderCancelledUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Cancelled Us Equities V 1 is what was written, byte for byte */
static void equal_order_cancelled_us_equities_v1(const OrderCancelledUsEquitiesV1 *read, const OrderCancelledUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Cancelled Us Equities V 1: written and read back, then read and written back */
static void check_order_cancelled_us_equities_v1(void) {
  OrderCancelledUsEquitiesV1 sent;
  OrderCancelledUsEquitiesV1 got;
  uint8_t wire[35];
  uint8_t again[35];

  any_order_cancelled_us_equities_v1(&sent);
  assert(encode_order_cancelled_us_equities_v1(&sent, wire, 0) == 35);
  assert(decode_order_cancelled_us_equities_v1(&got, wire, 0) == 35);
  equal_order_cancelled_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancelled_us_equities_v1(&got, wire, 0) == 35);
  assert(encode_order_cancelled_us_equities_v1(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Us Equities V 1: 95 bytes ------------------------------- */

/* A Cancel Rejected message is sent in response to a Cancel Order message to indicate that the cancellation cannot occur */
typedef struct {
  uint8_t in_flight[2];          /* bytes 0 to 1 */
  uint8_t transaction_time[8];   /* bytes 2 to 9 */
  uint8_t clearing_firm[4];      /* bytes 10 to 13 */
  uint8_t cl_ord_id[20];         /* bytes 14 to 33 */
  uint8_t cancel_reject_reason;  /* byte 34 */
  uint8_t text[60];              /* bytes 35 to 94 */
} CancelRejectedUsEquitiesV1;

/* any Cancel Rejected Us Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_rejected_us_equities_v1(CancelRejectedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Cancel Rejected Us Equities V 1 to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_us_equities_v1(const CancelRejectedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->cancel_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Cancel Rejected Us Equities V 1 off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_us_equities_v1(CancelRejectedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Rejected Us Equities V 1 is what was written, byte for byte */
static void equal_cancel_rejected_us_equities_v1(const CancelRejectedUsEquitiesV1 *read, const CancelRejectedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->cancel_reject_reason == written->cancel_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Cancel Rejected Us Equities V 1: written and read back, then read and written back */
static void check_cancel_rejected_us_equities_v1(void) {
  CancelRejectedUsEquitiesV1 sent;
  CancelRejectedUsEquitiesV1 got;
  uint8_t wire[95];
  uint8_t again[95];

  any_cancel_rejected_us_equities_v1(&sent);
  assert(encode_cancel_rejected_us_equities_v1(&sent, wire, 0) == 95);
  assert(decode_cancel_rejected_us_equities_v1(&got, wire, 0) == 95);
  equal_cancel_rejected_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_us_equities_v1(&got, wire, 0) == 95);
  assert(encode_cancel_rejected_us_equities_v1(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Execution Us Equities V 1: 83 bytes ------------------------------- */

/* An Order Execution message is sent for each fill on an order */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t clearing_firm[4];          /* bytes 10 to 13 */
  uint8_t cl_ord_id[20];             /* bytes 14 to 33 */
  uint8_t exec_id[8];                /* bytes 34 to 41 */
  uint8_t last_shares[4];            /* bytes 42 to 45 */
  uint8_t last_px[8];                /* bytes 46 to 53 */
  uint8_t leaves_qty[4];             /* bytes 54 to 57 */
  uint8_t base_liquidity_indicator;  /* byte 58 */
  uint8_t sub_liquidity_indicator;   /* byte 59 */
  uint8_t contra_broker[4];          /* bytes 60 to 63 */
  uint8_t side;                      /* byte 64 */
  uint8_t symbol[8];                 /* bytes 65 to 72 */
  uint8_t fee_code[2];               /* bytes 73 to 74 */
  uint8_t access_fee[8];             /* bytes 75 to 82 */
} OrderExecutionUsEquitiesV1;

/* any Order Execution Us Equities V 1 at all: every byte one the checker chooses */
static void any_order_execution_us_equities_v1(OrderExecutionUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
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
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->access_fee[i] = arbitrary(); }
}

/* Order Execution Us Equities V 1 to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_order_execution_us_equities_v1(const OrderExecutionUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
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
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->access_fee[i]; }

  return at;
}

/* Order Execution Us Equities V 1 off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_order_execution_us_equities_v1(OrderExecutionUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
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
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->access_fee[i] = wire[at++]; }

  return at;
}

/* what was read of Order Execution Us Equities V 1 is what was written, byte for byte */
static void equal_order_execution_us_equities_v1(const OrderExecutionUsEquitiesV1 *read, const OrderExecutionUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
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
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->access_fee[i] == written->access_fee[i]); }
}

/* Order Execution Us Equities V 1: written and read back, then read and written back */
static void check_order_execution_us_equities_v1(void) {
  OrderExecutionUsEquitiesV1 sent;
  OrderExecutionUsEquitiesV1 got;
  uint8_t wire[83];
  uint8_t again[83];

  any_order_execution_us_equities_v1(&sent);
  assert(encode_order_execution_us_equities_v1(&sent, wire, 0) == 83);
  assert(decode_order_execution_us_equities_v1(&got, wire, 0) == 83);
  equal_order_execution_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_order_execution_us_equities_v1(&got, wire, 0) == 83);
  assert(encode_order_execution_us_equities_v1(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel Correct Us Equities V 1: 94 bytes -------------------------- */

/* Used to relay a trade which has been cancelled (busted) or corrected (price change only) */
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
  uint8_t orig_time[8];              /* bytes 77 to 84 */
  uint8_t symbol[8];                 /* bytes 85 to 92 */
  uint8_t capacity;                  /* byte 93 */
} TradeCancelCorrectUsEquitiesV1;

/* any Trade Cancel Correct Us Equities V 1 at all: every byte one the checker chooses */
static void any_trade_cancel_correct_us_equities_v1(TradeCancelCorrectUsEquitiesV1 *record) {
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
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
}

/* Trade Cancel Correct Us Equities V 1 to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel_correct_us_equities_v1(const TradeCancelCorrectUsEquitiesV1 *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;

  return at;
}

/* Trade Cancel Correct Us Equities V 1 off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel_correct_us_equities_v1(TradeCancelCorrectUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];

  return at;
}

/* what was read of Trade Cancel Correct Us Equities V 1 is what was written, byte for byte */
static void equal_trade_cancel_correct_us_equities_v1(const TradeCancelCorrectUsEquitiesV1 *read, const TradeCancelCorrectUsEquitiesV1 *written) {
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
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
}

/* Trade Cancel Correct Us Equities V 1: written and read back, then read and written back */
static void check_trade_cancel_correct_us_equities_v1(void) {
  TradeCancelCorrectUsEquitiesV1 sent;
  TradeCancelCorrectUsEquitiesV1 got;
  uint8_t wire[94];
  uint8_t again[94];

  any_trade_cancel_correct_us_equities_v1(&sent);
  assert(encode_trade_cancel_correct_us_equities_v1(&sent, wire, 0) == 94);
  assert(decode_trade_cancel_correct_us_equities_v1(&got, wire, 0) == 94);
  equal_trade_cancel_correct_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel_correct_us_equities_v1(&got, wire, 0) == 94);
  assert(encode_trade_cancel_correct_us_equities_v1(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Rejected Us Equities V 1: 91 bytes -------------------------------- */

/* A Purge Rejected message is sent in response to a Purge Orders message to indicate that the mass cancellation cannot occur */
typedef struct {
  uint8_t in_flight[2];         /* bytes 0 to 1 */
  uint8_t transaction_time[8];  /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];   /* bytes 10 to 29 */
  uint8_t purge_reject_reason;  /* byte 30 */
  uint8_t text[60];             /* bytes 31 to 90 */
} PurgeRejectedUsEquitiesV1;

/* any Purge Rejected Us Equities V 1 at all: every byte one the checker chooses */
static void any_purge_rejected_us_equities_v1(PurgeRejectedUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  record->purge_reject_reason = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->text[i] = arbitrary(); }
}

/* Purge Rejected Us Equities V 1 to the wire: 91 bytes from at, returning where the next byte goes */
static size_t encode_purge_rejected_us_equities_v1(const PurgeRejectedUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  wire[at++] = record->purge_reject_reason;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Purge Rejected Us Equities V 1 off the wire: 91 bytes from at, returning where the next byte lies */
static size_t decode_purge_rejected_us_equities_v1(PurgeRejectedUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  record->purge_reject_reason = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Rejected Us Equities V 1 is what was written, byte for byte */
static void equal_purge_rejected_us_equities_v1(const PurgeRejectedUsEquitiesV1 *read, const PurgeRejectedUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  assert(read->purge_reject_reason == written->purge_reject_reason);
  for (size_t i = 0; i < 60; i++) { assert(read->text[i] == written->text[i]); }
}

/* Purge Rejected Us Equities V 1: written and read back, then read and written back */
static void check_purge_rejected_us_equities_v1(void) {
  PurgeRejectedUsEquitiesV1 sent;
  PurgeRejectedUsEquitiesV1 got;
  uint8_t wire[91];
  uint8_t again[91];

  any_purge_rejected_us_equities_v1(&sent);
  assert(encode_purge_rejected_us_equities_v1(&sent, wire, 0) == 91);
  assert(decode_purge_rejected_us_equities_v1(&got, wire, 0) == 91);
  equal_purge_rejected_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 91; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_rejected_us_equities_v1(&got, wire, 0) == 91);
  assert(encode_purge_rejected_us_equities_v1(&got, again, 0) == 91);
  for (size_t i = 0; i < 91; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Acknowledgement Us Equities V 1: 19 bytes -------------------- */

/* Response to a Reset Risk message request */
typedef struct {
  uint8_t in_flight[2];        /* bytes 0 to 1 */
  uint8_t risk_status_id[16];  /* bytes 2 to 17 */
  uint8_t risk_reset_result;   /* byte 18 */
} ResetRiskAcknowledgementUsEquitiesV1;

/* any Reset Risk Acknowledgement Us Equities V 1 at all: every byte one the checker chooses */
static void any_reset_risk_acknowledgement_us_equities_v1(ResetRiskAcknowledgementUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  record->risk_reset_result = arbitrary();
}

/* Reset Risk Acknowledgement Us Equities V 1 to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_acknowledgement_us_equities_v1(const ResetRiskAcknowledgementUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  wire[at++] = record->risk_reset_result;

  return at;
}

/* Reset Risk Acknowledgement Us Equities V 1 off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_acknowledgement_us_equities_v1(ResetRiskAcknowledgementUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  record->risk_reset_result = wire[at++];

  return at;
}

/* what was read of Reset Risk Acknowledgement Us Equities V 1 is what was written, byte for byte */
static void equal_reset_risk_acknowledgement_us_equities_v1(const ResetRiskAcknowledgementUsEquitiesV1 *read, const ResetRiskAcknowledgementUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  assert(read->risk_reset_result == written->risk_reset_result);
}

/* Reset Risk Acknowledgement Us Equities V 1: written and read back, then read and written back */
static void check_reset_risk_acknowledgement_us_equities_v1(void) {
  ResetRiskAcknowledgementUsEquitiesV1 sent;
  ResetRiskAcknowledgementUsEquitiesV1 got;
  uint8_t wire[19];
  uint8_t again[19];

  any_reset_risk_acknowledgement_us_equities_v1(&sent);
  assert(encode_reset_risk_acknowledgement_us_equities_v1(&sent, wire, 0) == 19);
  assert(decode_reset_risk_acknowledgement_us_equities_v1(&got, wire, 0) == 19);
  equal_reset_risk_acknowledgement_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_acknowledgement_us_equities_v1(&got, wire, 0) == 19);
  assert(encode_reset_risk_acknowledgement_us_equities_v1(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Purge Acknowledgement Us Equities V 1: 34 bytes ------------------------- */

/* A Purge Acknowledgment message is an unsequenced message sent when a Purge Orders message requesting an order purge has completed canceling all individual orders */
typedef struct {
  uint8_t in_flight[2];              /* bytes 0 to 1 */
  uint8_t transaction_time[8];       /* bytes 2 to 9 */
  uint8_t mass_cancel_id[20];        /* bytes 10 to 29 */
  uint8_t cancelled_order_count[4];  /* bytes 30 to 33 */
} PurgeAcknowledgementUsEquitiesV1;

/* any Purge Acknowledgement Us Equities V 1 at all: every byte one the checker chooses */
static void any_purge_acknowledgement_us_equities_v1(PurgeAcknowledgementUsEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = arbitrary(); }
}

/* Purge Acknowledgement Us Equities V 1 to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_purge_acknowledgement_us_equities_v1(const PurgeAcknowledgementUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->in_flight[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancelled_order_count[i]; }

  return at;
}

/* Purge Acknowledgement Us Equities V 1 off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_purge_acknowledgement_us_equities_v1(PurgeAcknowledgementUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->in_flight[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancelled_order_count[i] = wire[at++]; }

  return at;
}

/* what was read of Purge Acknowledgement Us Equities V 1 is what was written, byte for byte */
static void equal_purge_acknowledgement_us_equities_v1(const PurgeAcknowledgementUsEquitiesV1 *read, const PurgeAcknowledgementUsEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->in_flight[i] == written->in_flight[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_time[i] == written->transaction_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancelled_order_count[i] == written->cancelled_order_count[i]); }
}

/* Purge Acknowledgement Us Equities V 1: written and read back, then read and written back */
static void check_purge_acknowledgement_us_equities_v1(void) {
  PurgeAcknowledgementUsEquitiesV1 sent;
  PurgeAcknowledgementUsEquitiesV1 got;
  uint8_t wire[34];
  uint8_t again[34];

  any_purge_acknowledgement_us_equities_v1(&sent);
  assert(encode_purge_acknowledgement_us_equities_v1(&sent, wire, 0) == 34);
  assert(decode_purge_acknowledgement_us_equities_v1(&got, wire, 0) == 34);
  equal_purge_acknowledgement_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_purge_acknowledgement_us_equities_v1(&got, wire, 0) == 34);
  assert(encode_purge_acknowledgement_us_equities_v1(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_exchange_message_header();
  check_logout_response_message();
  check_order_acknowledgement_us_equities_v1();
  check_order_rejected_us_equities_v1();
  check_order_modified_us_equities_v1();
  check_order_restated_us_equities_v1();
  check_modify_rejected_us_equities_v1();
  check_order_cancelled_us_equities_v1();
  check_cancel_rejected_us_equities_v1();
  check_order_execution_us_equities_v1();
  check_trade_cancel_correct_us_equities_v1();
  check_purge_rejected_us_equities_v1();
  check_reset_risk_acknowledgement_us_equities_v1();
  check_purge_acknowledgement_us_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
