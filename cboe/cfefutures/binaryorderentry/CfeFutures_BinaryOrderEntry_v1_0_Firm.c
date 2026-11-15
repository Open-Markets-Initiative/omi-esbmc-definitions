// cboe/cfefutures/binaryorderentry/CfeFutures_BinaryOrderEntry_v1_0_Firm.c
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

/* ---- New Order Message: 129 bytes -------------------------------------------- */

/* New order futures message */
typedef struct {
  uint8_t cl_ord_id[20];             /* bytes 0 to 19 */
  uint8_t side;                      /* byte 20 */
  uint8_t order_qty[4];              /* bytes 21 to 24 */
  uint8_t clearing_firm[4];          /* bytes 25 to 28 */
  uint8_t clearing_account[4];       /* bytes 29 to 32 */
  uint8_t price[8];                  /* bytes 33 to 40 */
  uint8_t ord_type;                  /* byte 41 */
  uint8_t time_in_force;             /* byte 42 */
  uint8_t min_qty[4];                /* bytes 43 to 46 */
  uint8_t symbol[8];                 /* bytes 47 to 54 */
  uint8_t capacity;                  /* byte 55 */
  uint8_t account[16];               /* bytes 56 to 71 */
  PreventMatch prevent_match;        /* bytes 72 to 74 */
  uint8_t expire_time[8];            /* bytes 75 to 82 */
  uint8_t maturity_date[4];          /* bytes 83 to 86 */
  uint8_t open_close;                /* byte 87 */
  uint8_t cmta_number[4];            /* bytes 88 to 91 */
  uint8_t stop_px[8];                /* bytes 92 to 99 */
  uint8_t custom_group_id[2];        /* bytes 100 to 101 */
  uint8_t cti_code;                  /* byte 102 */
  uint8_t manual_order_indicator;    /* byte 103 */
  uint8_t oeo_id[18];                /* bytes 104 to 121 */
  uint8_t frequent_trader_id[6];     /* bytes 122 to 127 */
  uint8_t cust_order_handling_inst;  /* byte 128 */
} NewOrderMessage;

/* any New Order Message at all: every byte one the checker chooses */
static void any_new_order_message(NewOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  any_prevent_match(&record->prevent_match);
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = arbitrary(); }
  record->cti_code = arbitrary();
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->cust_order_handling_inst = arbitrary();
}

/* New Order Message to the wire: 129 bytes from at, returning where the next byte goes */
static size_t encode_new_order_message(const NewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  at = encode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id[i]; }
  wire[at++] = record->cti_code;
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->oeo_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->cust_order_handling_inst;

  return at;
}

/* New Order Message off the wire: 129 bytes from at, returning where the next byte lies */
static size_t decode_new_order_message(NewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  at = decode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = wire[at++]; }
  record->cti_code = wire[at++];
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->cust_order_handling_inst = wire[at++];

  return at;
}

/* what was read of New Order Message is what was written, byte for byte */
static void equal_new_order_message(const NewOrderMessage *read, const NewOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  equal_prevent_match(&read->prevent_match, &written->prevent_match);
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id[i] == written->custom_group_id[i]); }
  assert(read->cti_code == written->cti_code);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 18; i++) { assert(read->oeo_id[i] == written->oeo_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
}

/* New Order Message: written and read back, then read and written back */
static void check_new_order_message(void) {
  NewOrderMessage sent;
  NewOrderMessage got;
  uint8_t wire[129];
  uint8_t again[129];

  any_new_order_message(&sent);
  assert(encode_new_order_message(&sent, wire, 0) == 129);
  assert(decode_new_order_message(&got, wire, 0) == 129);
  equal_new_order_message(&got, &sent);

  for (size_t i = 0; i < 129; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_message(&got, wire, 0) == 129);
  assert(encode_new_order_message(&got, again, 0) == 129);
  for (size_t i = 0; i < 129; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 92 bytes ------------------------------------------ */

/* Request to modify an order */
typedef struct {
  uint8_t cl_ord_id[20];             /* bytes 0 to 19 */
  uint8_t orig_cl_ord_id[20];        /* bytes 20 to 39 */
  uint8_t clearing_firm[4];          /* bytes 40 to 43 */
  uint8_t order_qty[4];              /* bytes 44 to 47 */
  uint8_t price[8];                  /* bytes 48 to 55 */
  uint8_t ord_type;                  /* byte 56 */
  uint8_t cancel_orig_on_reject;     /* byte 57 */
  uint8_t stop_px[8];                /* bytes 58 to 65 */
  uint8_t manual_order_indicator;    /* byte 66 */
  uint8_t oeo_id[18];                /* bytes 67 to 84 */
  uint8_t frequent_trader_id[6];     /* bytes 85 to 90 */
  uint8_t cust_order_handling_inst;  /* byte 91 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->cancel_orig_on_reject = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->cust_order_handling_inst = arbitrary();
}

/* Modify Order Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->cancel_orig_on_reject;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->oeo_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->cust_order_handling_inst;

  return at;
}

/* Modify Order Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->cancel_orig_on_reject = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->cust_order_handling_inst = wire[at++];

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 18; i++) { assert(read->oeo_id[i] == written->oeo_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 92);
  assert(decode_modify_order_message(&got, wire, 0) == 92);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 92);
  assert(encode_modify_order_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 43 bytes ------------------------------------------ */

/* Request to cancel a single order or quote */
typedef struct {
  uint8_t orig_cl_ord_id[20];      /* bytes 0 to 19 */
  uint8_t clearing_firm[4];        /* bytes 20 to 23 */
  uint8_t manual_order_indicator;  /* byte 24 */
  uint8_t oeo_id[18];              /* bytes 25 to 42 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->oeo_id[i]; }

  return at;
}

/* Cancel Order Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 18; i++) { assert(read->oeo_id[i] == written->oeo_id[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 43);
  assert(decode_cancel_order_message(&got, wire, 0) == 43);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 43);
  assert(encode_cancel_order_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Inst: 16 bytes ---------------------------------------------- */

typedef struct {
  uint8_t clearing_firm_filter;     /* byte 0 */
  uint8_t acknowledgement_style;    /* byte 1 */
  uint8_t lockout_instruction;      /* byte 2 */
  uint8_t instrument_type_filter;   /* byte 3 */
  uint8_t gtc_order_filter;         /* byte 4 */
  uint8_t instruction_details[11];  /* bytes 5 to 15 */
} MassCancelInst;

/* any Mass Cancel Inst at all: every byte one the checker chooses */
static void any_mass_cancel_inst(MassCancelInst *record) {
  record->clearing_firm_filter = arbitrary();
  record->acknowledgement_style = arbitrary();
  record->lockout_instruction = arbitrary();
  record->instrument_type_filter = arbitrary();
  record->gtc_order_filter = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->instruction_details[i] = arbitrary(); }
}

/* Mass Cancel Inst to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_inst(const MassCancelInst *record, uint8_t *wire, size_t at) {
  wire[at++] = record->clearing_firm_filter;
  wire[at++] = record->acknowledgement_style;
  wire[at++] = record->lockout_instruction;
  wire[at++] = record->instrument_type_filter;
  wire[at++] = record->gtc_order_filter;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->instruction_details[i]; }

  return at;
}

/* Mass Cancel Inst off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_inst(MassCancelInst *record, const uint8_t *wire, size_t at) {
  record->clearing_firm_filter = wire[at++];
  record->acknowledgement_style = wire[at++];
  record->lockout_instruction = wire[at++];
  record->instrument_type_filter = wire[at++];
  record->gtc_order_filter = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->instruction_details[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Inst is what was written, byte for byte */
static void equal_mass_cancel_inst(const MassCancelInst *read, const MassCancelInst *written) {
  assert(read->clearing_firm_filter == written->clearing_firm_filter);
  assert(read->acknowledgement_style == written->acknowledgement_style);
  assert(read->lockout_instruction == written->lockout_instruction);
  assert(read->instrument_type_filter == written->instrument_type_filter);
  assert(read->gtc_order_filter == written->gtc_order_filter);
  for (size_t i = 0; i < 11; i++) { assert(read->instruction_details[i] == written->instruction_details[i]); }
}

/* Mass Cancel Inst: written and read back, then read and written back */
static void check_mass_cancel_inst(void) {
  MassCancelInst sent;
  MassCancelInst got;
  uint8_t wire[16];
  uint8_t again[16];

  any_mass_cancel_inst(&sent);
  assert(encode_mass_cancel_inst(&sent, wire, 0) == 16);
  assert(decode_mass_cancel_inst(&got, wire, 0) == 16);
  equal_mass_cancel_inst(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_inst(&got, wire, 0) == 16);
  assert(encode_mass_cancel_inst(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Order Message: 65 bytes ------------------------------------- */

/* A Mass Cancel Order message is a request to cancel a group of orders or quotes */
typedef struct {
  uint8_t mass_cancel_id[20];       /* bytes 0 to 19 */
  uint8_t clearing_firm[4];         /* bytes 20 to 23 */
  uint8_t product_name[6];          /* bytes 24 to 29 */
  MassCancelInst mass_cancel_inst;  /* bytes 30 to 45 */
  uint8_t manual_order_indicator;   /* byte 46 */
  uint8_t oeo_id[18];               /* bytes 47 to 64 */
} MassCancelOrderMessage;

/* any Mass Cancel Order Message at all: every byte one the checker chooses */
static void any_mass_cancel_order_message(MassCancelOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->product_name[i] = arbitrary(); }
  any_mass_cancel_inst(&record->mass_cancel_inst);
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = arbitrary(); }
}

/* Mass Cancel Order Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_order_message(const MassCancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->product_name[i]; }
  at = encode_mass_cancel_inst(&record->mass_cancel_inst, wire, at);
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->oeo_id[i]; }

  return at;
}

/* Mass Cancel Order Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_order_message(MassCancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->product_name[i] = wire[at++]; }
  at = decode_mass_cancel_inst(&record->mass_cancel_inst, wire, at);
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 18; i++) { record->oeo_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Order Message is what was written, byte for byte */
static void equal_mass_cancel_order_message(const MassCancelOrderMessage *read, const MassCancelOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->product_name[i] == written->product_name[i]); }
  equal_mass_cancel_inst(&read->mass_cancel_inst, &written->mass_cancel_inst);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 18; i++) { assert(read->oeo_id[i] == written->oeo_id[i]); }
}

/* Mass Cancel Order Message: written and read back, then read and written back */
static void check_mass_cancel_order_message(void) {
  MassCancelOrderMessage sent;
  MassCancelOrderMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_mass_cancel_order_message(&sent);
  assert(encode_mass_cancel_order_message(&sent, wire, 0) == 65);
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 65);
  equal_mass_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 65);
  assert(encode_mass_cancel_order_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Message: 36 bytes -------------------------------------------- */

/* Reset or release Firm/EFID, Product, or Custom Group Id level lockout conditions resulting from risk profile trips or self-imposed lockouts issued viaMass Cancel Order or Purge Orders messages */
typedef struct {
  uint8_t risk_status_id[16];  /* bytes 0 to 15 */
  uint8_t risk_reset[8];       /* bytes 16 to 23 */
  uint8_t clearing_firm[4];    /* bytes 24 to 27 */
  uint8_t product_name[6];     /* bytes 28 to 33 */
  uint8_t custom_group_id[2];  /* bytes 34 to 35 */
} ResetRiskMessage;

/* any Reset Risk Message at all: every byte one the checker chooses */
static void any_reset_risk_message(ResetRiskMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->product_name[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = arbitrary(); }
}

/* Reset Risk Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_message(const ResetRiskMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->risk_reset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->product_name[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id[i]; }

  return at;
}

/* Reset Risk Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_message(ResetRiskMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->product_name[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Message is what was written, byte for byte */
static void equal_reset_risk_message(const ResetRiskMessage *read, const ResetRiskMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->risk_reset[i] == written->risk_reset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->product_name[i] == written->product_name[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id[i] == written->custom_group_id[i]); }
}

/* Reset Risk Message: written and read back, then read and written back */
static void check_reset_risk_message(void) {
  ResetRiskMessage sent;
  ResetRiskMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_reset_risk_message(&sent);
  assert(encode_reset_risk_message(&sent, wire, 0) == 36);
  assert(decode_reset_risk_message(&got, wire, 0) == 36);
  equal_reset_risk_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_message(&got, wire, 0) == 36);
  assert(encode_reset_risk_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_prevent_match();
  check_new_order_message();
  check_modify_order_message();
  check_cancel_order_message();
  check_mass_cancel_inst();
  check_mass_cancel_order_message();
  check_reset_risk_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
