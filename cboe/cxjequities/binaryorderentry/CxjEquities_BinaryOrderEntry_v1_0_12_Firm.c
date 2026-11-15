// cboe/cxjequities/binaryorderentry/CxjEquities_BinaryOrderEntry_v1_0_12_Firm.c
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

/* ---- Firm Message Header: 12 bytes ------------------------------------------- */

/* Message header of a packet sent by the firm */
typedef struct {
  uint8_t start_of_message[2];   /* bytes 0 to 1 */
  uint8_t message_length[2];     /* bytes 2 to 3 */
  uint8_t firm_message_type[2];  /* bytes 4 to 5 */
  uint8_t matching_unit;         /* byte 6 */
  uint8_t reserved_field;        /* byte 7 */
  uint8_t sequence_number[4];    /* bytes 8 to 11 */
} FirmMessageHeader;

/* any Firm Message Header at all: every byte one the checker chooses */
static void any_firm_message_header(FirmMessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->firm_message_type[i] = arbitrary(); }
  record->matching_unit = arbitrary();
  record->reserved_field = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Firm Message Header to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_firm_message_header(const FirmMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->start_of_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->firm_message_type[i]; }
  wire[at++] = record->matching_unit;
  wire[at++] = record->reserved_field;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Firm Message Header off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_firm_message_header(FirmMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->start_of_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->firm_message_type[i] = wire[at++]; }
  record->matching_unit = wire[at++];
  record->reserved_field = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Firm Message Header is what was written, byte for byte */
static void equal_firm_message_header(const FirmMessageHeader *read, const FirmMessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->start_of_message[i] == written->start_of_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->firm_message_type[i] == written->firm_message_type[i]); }
  assert(read->matching_unit == written->matching_unit);
  assert(read->reserved_field == written->reserved_field);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Firm Message Header: written and read back, then read and written back */
static void check_firm_message_header(void) {
  FirmMessageHeader sent;
  FirmMessageHeader got;
  uint8_t wire[12];
  uint8_t again[12];

  any_firm_message_header(&sent);
  assert(encode_firm_message_header(&sent, wire, 0) == 12);
  assert(decode_firm_message_header(&got, wire, 0) == 12);
  equal_firm_message_header(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_firm_message_header(&got, wire, 0) == 12);
  assert(encode_firm_message_header(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Jp Equities V 1: 87 bytes ------------------------------------- */

/* Submission of a new order to Cboe Japan */
typedef struct {
  uint8_t account[10];              /* bytes 0 to 9 */
  uint8_t trading_firm[4];          /* bytes 10 to 13 */
  uint8_t cl_ord_id[20];            /* bytes 14 to 33 */
  uint8_t order_qty[4];             /* bytes 34 to 37 */
  uint8_t ord_type;                 /* byte 38 */
  uint8_t price[8];                 /* bytes 39 to 46 */
  uint8_t capacity;                 /* byte 47 */
  uint8_t side;                     /* byte 48 */
  uint8_t symbol[8];                /* bytes 49 to 56 */
  uint8_t time_in_force;            /* byte 57 */
  uint8_t expire_time[8];           /* bytes 58 to 65 */
  uint8_t cash_margin;              /* byte 66 */
  uint8_t risk_group_id[2];         /* bytes 67 to 68 */
  uint8_t no_trade_feat;            /* byte 69 */
  uint8_t no_trade_key[10];         /* bytes 70 to 79 */
  uint8_t posting_instruction;      /* byte 80 */
  uint8_t order_classification;     /* byte 81 */
  uint8_t margin_transaction_type;  /* byte 82 */
  uint8_t company_id[4];            /* bytes 83 to 86 */
} NewOrderJpEquitiesV1;

/* any New Order Jp Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_jp_equities_v1(NewOrderJpEquitiesV1 *record) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = arbitrary(); }
}

/* New Order Jp Equities V 1 to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_new_order_jp_equities_v1(const NewOrderJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->company_id[i]; }

  return at;
}

/* New Order Jp Equities V 1 off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_new_order_jp_equities_v1(NewOrderJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { record->company_id[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Jp Equities V 1 is what was written, byte for byte */
static void equal_new_order_jp_equities_v1(const NewOrderJpEquitiesV1 *read, const NewOrderJpEquitiesV1 *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
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
  for (size_t i = 0; i < 4; i++) { assert(read->company_id[i] == written->company_id[i]); }
}

/* New Order Jp Equities V 1: written and read back, then read and written back */
static void check_new_order_jp_equities_v1(void) {
  NewOrderJpEquitiesV1 sent;
  NewOrderJpEquitiesV1 got;
  uint8_t wire[87];
  uint8_t again[87];

  any_new_order_jp_equities_v1(&sent);
  assert(encode_new_order_jp_equities_v1(&sent, wire, 0) == 87);
  assert(decode_new_order_jp_equities_v1(&got, wire, 0) == 87);
  equal_new_order_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_jp_equities_v1(&got, wire, 0) == 87);
  assert(encode_new_order_jp_equities_v1(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Jp Equities V 1: 57 bytes ---------------------------------- */

/* Request to modify an order. Only Price and OrderQty may be adjusted */
typedef struct {
  uint8_t trading_firm[4];        /* bytes 0 to 3 */
  uint8_t cl_ord_id[20];          /* bytes 4 to 23 */
  uint8_t order_qty[4];           /* bytes 24 to 27 */
  uint8_t orig_cl_ord_id[20];     /* bytes 28 to 47 */
  uint8_t price[8];               /* bytes 48 to 55 */
  uint8_t cancel_orig_on_reject;  /* byte 56 */
} ModifyOrderJpEquitiesV1;

/* any Modify Order Jp Equities V 1 at all: every byte one the checker chooses */
static void any_modify_order_jp_equities_v1(ModifyOrderJpEquitiesV1 *record) {
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->cancel_orig_on_reject = arbitrary();
}

/* Modify Order Jp Equities V 1 to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_jp_equities_v1(const ModifyOrderJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->cancel_orig_on_reject;

  return at;
}

/* Modify Order Jp Equities V 1 off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_jp_equities_v1(ModifyOrderJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->cancel_orig_on_reject = wire[at++];

  return at;
}

/* what was read of Modify Order Jp Equities V 1 is what was written, byte for byte */
static void equal_modify_order_jp_equities_v1(const ModifyOrderJpEquitiesV1 *read, const ModifyOrderJpEquitiesV1 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
}

/* Modify Order Jp Equities V 1: written and read back, then read and written back */
static void check_modify_order_jp_equities_v1(void) {
  ModifyOrderJpEquitiesV1 sent;
  ModifyOrderJpEquitiesV1 got;
  uint8_t wire[57];
  uint8_t again[57];

  any_modify_order_jp_equities_v1(&sent);
  assert(encode_modify_order_jp_equities_v1(&sent, wire, 0) == 57);
  assert(decode_modify_order_jp_equities_v1(&got, wire, 0) == 57);
  equal_modify_order_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_jp_equities_v1(&got, wire, 0) == 57);
  assert(encode_modify_order_jp_equities_v1(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Jp Equities V 1: 24 bytes ---------------------------------- */

/* Request to cancel a single order */
typedef struct {
  uint8_t trading_firm[4];     /* bytes 0 to 3 */
  uint8_t orig_cl_ord_id[20];  /* bytes 4 to 23 */
} CancelOrderJpEquitiesV1;

/* any Cancel Order Jp Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_order_jp_equities_v1(CancelOrderJpEquitiesV1 *record) {
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
}

/* Cancel Order Jp Equities V 1 to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_jp_equities_v1(const CancelOrderJpEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_firm[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }

  return at;
}

/* Cancel Order Jp Equities V 1 off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_jp_equities_v1(CancelOrderJpEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trading_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Jp Equities V 1 is what was written, byte for byte */
static void equal_cancel_order_jp_equities_v1(const CancelOrderJpEquitiesV1 *read, const CancelOrderJpEquitiesV1 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trading_firm[i] == written->trading_firm[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
}

/* Cancel Order Jp Equities V 1: written and read back, then read and written back */
static void check_cancel_order_jp_equities_v1(void) {
  CancelOrderJpEquitiesV1 sent;
  CancelOrderJpEquitiesV1 got;
  uint8_t wire[24];
  uint8_t again[24];

  any_cancel_order_jp_equities_v1(&sent);
  assert(encode_cancel_order_jp_equities_v1(&sent, wire, 0) == 24);
  assert(decode_cancel_order_jp_equities_v1(&got, wire, 0) == 24);
  equal_cancel_order_jp_equities_v1(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_jp_equities_v1(&got, wire, 0) == 24);
  assert(encode_cancel_order_jp_equities_v1(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_new_order_jp_equities_v1();
  check_modify_order_jp_equities_v1();
  check_cancel_order_jp_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
