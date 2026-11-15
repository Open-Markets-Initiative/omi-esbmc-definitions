// cboe/bzxequities/binaryorderentry/BzxEquities_BinaryOrderEntry_v1_0_14_Firm.c
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

/* ---- New Order Us Equities V 1: 141 bytes ------------------------------------ */

/* Submission of a new order to Cboe */
typedef struct {
  uint8_t cl_ord_id[20];             /* bytes 0 to 19 */
  uint8_t side;                      /* byte 20 */
  uint8_t order_qty[4];              /* bytes 21 to 24 */
  uint8_t clearing_firm[4];          /* bytes 25 to 28 */
  uint8_t clearing_account[4];       /* bytes 29 to 32 */
  uint8_t price[8];                  /* bytes 33 to 40 */
  uint8_t exec_inst;                 /* byte 41 */
  uint8_t ord_type;                  /* byte 42 */
  uint8_t time_in_force;             /* byte 43 */
  uint8_t min_qty[4];                /* bytes 44 to 47 */
  uint8_t max_floor[4];              /* bytes 48 to 51 */
  uint8_t symbol[8];                 /* bytes 52 to 59 */
  uint8_t capacity;                  /* byte 60 */
  uint8_t routing_inst[4];           /* bytes 61 to 64 */
  uint8_t account[16];               /* bytes 65 to 80 */
  uint8_t display_indicator;         /* byte 81 */
  uint8_t discretion_amount[2];      /* bytes 82 to 83 */
  uint8_t peg_difference[8];         /* bytes 84 to 91 */
  uint8_t prevent_match[3];          /* bytes 92 to 94 */
  uint8_t locate_reqd;               /* byte 95 */
  uint8_t expire_time[8];            /* bytes 96 to 103 */
  uint8_t attributed_quote;          /* byte 104 */
  uint8_t ext_exec_inst;             /* byte 105 */
  uint8_t display_range[4];          /* bytes 106 to 109 */
  uint8_t stop_px[8];                /* bytes 110 to 117 */
  uint8_t rout_strategy[6];          /* bytes 118 to 123 */
  uint8_t route_delivery_method[3];  /* bytes 124 to 126 */
  uint8_t ex_destination;            /* byte 127 */
  uint8_t risk_group_id[2];          /* bytes 128 to 129 */
  uint8_t cross_trade_flag;          /* byte 130 */
  uint8_t locate_broker[4];          /* bytes 131 to 134 */
  uint8_t step_up_amount[4];         /* bytes 135 to 138 */
  uint8_t cmc_sessions[2];           /* bytes 139 to 140 */
} NewOrderUsEquitiesV1;

/* any New Order Us Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_us_equities_v1(NewOrderUsEquitiesV1 *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->ord_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->routing_inst[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->discretion_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->peg_difference[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->prevent_match[i] = arbitrary(); }
  record->locate_reqd = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  record->attributed_quote = arbitrary();
  record->ext_exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->display_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->cross_trade_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->step_up_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->cmc_sessions[i] = arbitrary(); }
}

/* New Order Us Equities V 1 to the wire: 141 bytes from at, returning where the next byte goes */
static size_t encode_new_order_us_equities_v1(const NewOrderUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->ord_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_inst[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->discretion_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->peg_difference[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->prevent_match[i]; }
  wire[at++] = record->locate_reqd;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  wire[at++] = record->attributed_quote;
  wire[at++] = record->ext_exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->rout_strategy[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->route_delivery_method[i]; }
  wire[at++] = record->ex_destination;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->cross_trade_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->locate_broker[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->step_up_amount[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cmc_sessions[i]; }

  return at;
}

/* New Order Us Equities V 1 off the wire: 141 bytes from at, returning where the next byte lies */
static size_t decode_new_order_us_equities_v1(NewOrderUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->ord_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->routing_inst[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->discretion_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->peg_difference[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->prevent_match[i] = wire[at++]; }
  record->locate_reqd = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  record->attributed_quote = wire[at++];
  record->ext_exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->display_range[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->cross_trade_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->step_up_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->cmc_sessions[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Us Equities V 1 is what was written, byte for byte */
static void equal_new_order_us_equities_v1(const NewOrderUsEquitiesV1 *read, const NewOrderUsEquitiesV1 *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->ord_type == written->ord_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  for (size_t i = 0; i < 4; i++) { assert(read->routing_inst[i] == written->routing_inst[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->discretion_amount[i] == written->discretion_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->peg_difference[i] == written->peg_difference[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->prevent_match[i] == written->prevent_match[i]); }
  assert(read->locate_reqd == written->locate_reqd);
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  assert(read->attributed_quote == written->attributed_quote);
  assert(read->ext_exec_inst == written->ext_exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->display_range[i] == written->display_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->rout_strategy[i] == written->rout_strategy[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->route_delivery_method[i] == written->route_delivery_method[i]); }
  assert(read->ex_destination == written->ex_destination);
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->cross_trade_flag == written->cross_trade_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->locate_broker[i] == written->locate_broker[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->step_up_amount[i] == written->step_up_amount[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->cmc_sessions[i] == written->cmc_sessions[i]); }
}

/* New Order Us Equities V 1: written and read back, then read and written back */
static void check_new_order_us_equities_v1(void) {
  NewOrderUsEquitiesV1 sent;
  NewOrderUsEquitiesV1 got;
  uint8_t wire[141];
  uint8_t again[141];

  any_new_order_us_equities_v1(&sent);
  assert(encode_new_order_us_equities_v1(&sent, wire, 0) == 141);
  assert(decode_new_order_us_equities_v1(&got, wire, 0) == 141);
  equal_new_order_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 141; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_us_equities_v1(&got, wire, 0) == 141);
  assert(encode_new_order_us_equities_v1(&got, again, 0) == 141);
  for (size_t i = 0; i < 141; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Short Us Equities V 1: 71 bytes ------------------------------- */

/* Submission of a new order to Cboe */
typedef struct {
  uint8_t cl_ord_id[20];        /* bytes 0 to 19 */
  uint8_t side;                 /* byte 20 */
  uint8_t order_qty[4];         /* bytes 21 to 24 */
  uint8_t clearing_firm[4];     /* bytes 25 to 28 */
  uint8_t clearing_account[4];  /* bytes 29 to 32 */
  uint8_t price[8];             /* bytes 33 to 40 */
  uint8_t exec_inst;            /* byte 41 */
  uint8_t ord_type;             /* byte 42 */
  uint8_t time_in_force;        /* byte 43 */
  uint8_t symbol[8];            /* bytes 44 to 51 */
  uint8_t capacity;             /* byte 52 */
  uint8_t short_routing_inst;   /* byte 53 */
  uint8_t short_account[10];    /* bytes 54 to 63 */
  uint8_t display_indicator;    /* byte 64 */
  uint8_t risk_group_id[2];     /* bytes 65 to 66 */
  uint8_t locate_broker[4];     /* bytes 67 to 70 */
} NewOrderShortUsEquitiesV1;

/* any New Order Short Us Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_short_us_equities_v1(NewOrderShortUsEquitiesV1 *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->ord_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->short_routing_inst = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->short_account[i] = arbitrary(); }
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = arbitrary(); }
}

/* New Order Short Us Equities V 1 to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_new_order_short_us_equities_v1(const NewOrderShortUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->ord_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->short_routing_inst;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->short_account[i]; }
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->locate_broker[i]; }

  return at;
}

/* New Order Short Us Equities V 1 off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_new_order_short_us_equities_v1(NewOrderShortUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->ord_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->short_routing_inst = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->short_account[i] = wire[at++]; }
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Short Us Equities V 1 is what was written, byte for byte */
static void equal_new_order_short_us_equities_v1(const NewOrderShortUsEquitiesV1 *read, const NewOrderShortUsEquitiesV1 *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->ord_type == written->ord_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->capacity == written->capacity);
  assert(read->short_routing_inst == written->short_routing_inst);
  for (size_t i = 0; i < 10; i++) { assert(read->short_account[i] == written->short_account[i]); }
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->locate_broker[i] == written->locate_broker[i]); }
}

/* New Order Short Us Equities V 1: written and read back, then read and written back */
static void check_new_order_short_us_equities_v1(void) {
  NewOrderShortUsEquitiesV1 sent;
  NewOrderShortUsEquitiesV1 got;
  uint8_t wire[71];
  uint8_t again[71];

  any_new_order_short_us_equities_v1(&sent);
  assert(encode_new_order_short_us_equities_v1(&sent, wire, 0) == 71);
  assert(decode_new_order_short_us_equities_v1(&got, wire, 0) == 71);
  equal_new_order_short_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_short_us_equities_v1(&got, wire, 0) == 71);
  assert(encode_new_order_short_us_equities_v1(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Us Equities V 1: 24 bytes ---------------------------------- */

/* Request to cancel a single order */
typedef struct {
  uint8_t orig_cl_ord_id[20];  /* bytes 0 to 19 */
  uint8_t clearing_firm[4];    /* bytes 20 to 23 */
} CancelOrderUsEquitiesV1;

/* any Cancel Order Us Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_order_us_equities_v1(CancelOrderUsEquitiesV1 *record) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
}

/* Cancel Order Us Equities V 1 to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_us_equities_v1(const CancelOrderUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }

  return at;
}

/* Cancel Order Us Equities V 1 off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_us_equities_v1(CancelOrderUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Us Equities V 1 is what was written, byte for byte */
static void equal_cancel_order_us_equities_v1(const CancelOrderUsEquitiesV1 *read, const CancelOrderUsEquitiesV1 *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
}

/* Cancel Order Us Equities V 1: written and read back, then read and written back */
static void check_cancel_order_us_equities_v1(void) {
  CancelOrderUsEquitiesV1 sent;
  CancelOrderUsEquitiesV1 got;
  uint8_t wire[24];
  uint8_t again[24];

  any_cancel_order_us_equities_v1(&sent);
  assert(encode_cancel_order_us_equities_v1(&sent, wire, 0) == 24);
  assert(decode_cancel_order_us_equities_v1(&got, wire, 0) == 24);
  equal_cancel_order_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_us_equities_v1(&got, wire, 0) == 24);
  assert(encode_cancel_order_us_equities_v1(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Us Equities V 1: 83 bytes ---------------------------------- */

/* Request to modify an order */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t orig_cl_ord_id[20];     /* bytes 20 to 39 */
  uint8_t clearing_firm[4];       /* bytes 40 to 43 */
  uint8_t symbol[8];              /* bytes 44 to 51 */
  uint8_t order_qty[4];           /* bytes 52 to 55 */
  uint8_t price[8];               /* bytes 56 to 63 */
  uint8_t ord_type;               /* byte 64 */
  uint8_t side;                   /* byte 65 */
  uint8_t max_floor[4];           /* bytes 66 to 69 */
  uint8_t stop_px[8];             /* bytes 70 to 77 */
  uint8_t cancel_orig_on_reject;  /* byte 78 */
  uint8_t locate_broker[4];       /* bytes 79 to 82 */
} ModifyOrderUsEquitiesV1;

/* any Modify Order Us Equities V 1 at all: every byte one the checker chooses */
static void any_modify_order_us_equities_v1(ModifyOrderUsEquitiesV1 *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  record->cancel_orig_on_reject = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = arbitrary(); }
}

/* Modify Order Us Equities V 1 to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_us_equities_v1(const ModifyOrderUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  wire[at++] = record->cancel_orig_on_reject;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->locate_broker[i]; }

  return at;
}

/* Modify Order Us Equities V 1 off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_us_equities_v1(ModifyOrderUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  record->cancel_orig_on_reject = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->locate_broker[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Us Equities V 1 is what was written, byte for byte */
static void equal_modify_order_us_equities_v1(const ModifyOrderUsEquitiesV1 *read, const ModifyOrderUsEquitiesV1 *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
  for (size_t i = 0; i < 4; i++) { assert(read->locate_broker[i] == written->locate_broker[i]); }
}

/* Modify Order Us Equities V 1: written and read back, then read and written back */
static void check_modify_order_us_equities_v1(void) {
  ModifyOrderUsEquitiesV1 sent;
  ModifyOrderUsEquitiesV1 got;
  uint8_t wire[83];
  uint8_t again[83];

  any_modify_order_us_equities_v1(&sent);
  assert(encode_modify_order_us_equities_v1(&sent, wire, 0) == 83);
  assert(decode_modify_order_us_equities_v1(&got, wire, 0) == 83);
  equal_modify_order_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_us_equities_v1(&got, wire, 0) == 83);
  assert(encode_modify_order_us_equities_v1(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Us Equities V 1: 39 bytes ------------------------------------ */

/* Reset or release Firm, Symbol, or Risk Group ID level lockout conditions resulting from risk profile trips or self-imposed lockouts issued via Purge Orders messages */
typedef struct {
  uint8_t risk_status_id[16];    /* bytes 0 to 15 */
  uint8_t risk_reset[8];         /* bytes 16 to 23 */
  uint8_t clearing_firm[4];      /* bytes 24 to 27 */
  uint8_t symbol[8];             /* bytes 28 to 35 */
  uint8_t target_matching_unit;  /* byte 36 */
  uint8_t risk_group_id[2];      /* bytes 37 to 38 */
} ResetRiskUsEquitiesV1;

/* any Reset Risk Us Equities V 1 at all: every byte one the checker chooses */
static void any_reset_risk_us_equities_v1(ResetRiskUsEquitiesV1 *record) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = arbitrary(); }
  record->target_matching_unit = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
}

/* Reset Risk Us Equities V 1 to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_us_equities_v1(const ResetRiskUsEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->risk_reset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->target_matching_unit;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }

  return at;
}

/* Reset Risk Us Equities V 1 off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_us_equities_v1(ResetRiskUsEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol[i] = wire[at++]; }
  record->target_matching_unit = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Us Equities V 1 is what was written, byte for byte */
static void equal_reset_risk_us_equities_v1(const ResetRiskUsEquitiesV1 *read, const ResetRiskUsEquitiesV1 *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->risk_reset[i] == written->risk_reset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->target_matching_unit == written->target_matching_unit);
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
}

/* Reset Risk Us Equities V 1: written and read back, then read and written back */
static void check_reset_risk_us_equities_v1(void) {
  ResetRiskUsEquitiesV1 sent;
  ResetRiskUsEquitiesV1 got;
  uint8_t wire[39];
  uint8_t again[39];

  any_reset_risk_us_equities_v1(&sent);
  assert(encode_reset_risk_us_equities_v1(&sent, wire, 0) == 39);
  assert(decode_reset_risk_us_equities_v1(&got, wire, 0) == 39);
  equal_reset_risk_us_equities_v1(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_us_equities_v1(&got, wire, 0) == 39);
  assert(encode_reset_risk_us_equities_v1(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_new_order_us_equities_v1();
  check_new_order_short_us_equities_v1();
  check_cancel_order_us_equities_v1();
  check_modify_order_us_equities_v1();
  check_reset_risk_us_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
