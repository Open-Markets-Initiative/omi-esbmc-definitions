// cboe/neoequities/orderentry/NeoEquities_OrderEntry_v1_0_19_Firm.c
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

/* ---- New Order Ca Equities V 1: 253 bytes ------------------------------------ */

/* New order message for Cboe Canada Equities */
typedef struct {
  uint8_t account[16];                        /* bytes 0 to 15 */
  uint8_t cl_ord_id[20];                      /* bytes 16 to 35 */
  uint8_t broker_id[2];                       /* bytes 36 to 37 */
  uint8_t exec_inst;                          /* byte 38 */
  uint8_t handling_inst;                      /* byte 39 */
  uint8_t order_qty[4];                       /* bytes 40 to 43 */
  uint8_t ord_type;                           /* byte 44 */
  uint8_t price[8];                           /* bytes 45 to 52 */
  uint8_t stop_px[8];                         /* bytes 53 to 60 */
  uint8_t side;                               /* byte 61 */
  uint8_t symbol[14];                         /* bytes 62 to 75 */
  uint8_t time_in_force;                      /* byte 76 */
  uint8_t settlement_type;                    /* byte 77 */
  uint8_t fut_settl_date[4];                  /* bytes 78 to 81 */
  uint8_t ex_destination;                     /* byte 82 */
  uint8_t max_floor[4];                       /* bytes 83 to 86 */
  uint8_t expire_time[8];                     /* bytes 87 to 94 */
  uint8_t expire_date[4];                     /* bytes 95 to 98 */
  uint8_t lei_order_origin;                   /* byte 99 */
  uint8_t lei_routing_arrangement_indicator;  /* byte 100 */
  uint8_t umir_account_type;                  /* byte 101 */
  uint8_t umir_user_id[12];                   /* bytes 102 to 113 */
  uint8_t basket_trade[4];                    /* bytes 114 to 117 */
  uint8_t program_trade;                      /* byte 118 */
  uint8_t jitney[2];                          /* bytes 119 to 120 */
  uint8_t anonymous;                          /* byte 121 */
  uint8_t umir_regulation_id;                 /* byte 122 */
  uint8_t non_resident;                       /* byte 123 */
  uint8_t bypass;                             /* byte 124 */
  uint8_t ncib;                               /* byte 125 */
  uint8_t no_trade_feat;                      /* byte 126 */
  uint8_t no_trade_key[6];                    /* bytes 127 to 132 */
  uint8_t short_marking_exempt;               /* byte 133 */
  uint8_t lei_customer_account[20];           /* bytes 134 to 153 */
  uint8_t lei_algorithm_id[20];               /* bytes 154 to 173 */
  uint8_t customer_lei[52];                   /* bytes 174 to 225 */
  uint8_t broker_lei[20];                     /* bytes 226 to 245 */
  uint8_t routing_inst;                       /* byte 246 */
  uint8_t display_indicator;                  /* byte 247 */
  uint8_t matching_state_participation;       /* byte 248 */
  uint8_t true_min_qty[4];                    /* bytes 249 to 252 */
} NewOrderCaEquitiesV1;

/* any New Order Ca Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_ca_equities_v1(NewOrderCaEquitiesV1 *record) {
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->handling_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
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
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
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
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = arbitrary(); }
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

/* New Order Ca Equities V 1 to the wire: 253 bytes from at, returning where the next byte goes */
static size_t encode_new_order_ca_equities_v1(const NewOrderCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->handling_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
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
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->no_trade_key[i]; }
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

/* New Order Ca Equities V 1 off the wire: 253 bytes from at, returning where the next byte lies */
static size_t decode_new_order_ca_equities_v1(NewOrderCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->handling_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
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
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = wire[at++]; }
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

/* what was read of New Order Ca Equities V 1 is what was written, byte for byte */
static void equal_new_order_ca_equities_v1(const NewOrderCaEquitiesV1 *read, const NewOrderCaEquitiesV1 *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->handling_inst == written->handling_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
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
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
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
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 6; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
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

/* New Order Ca Equities V 1: written and read back, then read and written back */
static void check_new_order_ca_equities_v1(void) {
  NewOrderCaEquitiesV1 sent;
  NewOrderCaEquitiesV1 got;
  uint8_t wire[253];
  uint8_t again[253];

  any_new_order_ca_equities_v1(&sent);
  assert(encode_new_order_ca_equities_v1(&sent, wire, 0) == 253);
  assert(decode_new_order_ca_equities_v1(&got, wire, 0) == 253);
  equal_new_order_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 253; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_ca_equities_v1(&got, wire, 0) == 253);
  assert(encode_new_order_ca_equities_v1(&got, again, 0) == 253);
  for (size_t i = 0; i < 253; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Ca Equities V 2: 261 bytes ------------------------------------ */

/* New order V2 message for Cboe Canada Equities, adds PegDifference */
typedef struct {
  uint8_t account[16];                        /* bytes 0 to 15 */
  uint8_t cl_ord_id[20];                      /* bytes 16 to 35 */
  uint8_t broker_id[2];                       /* bytes 36 to 37 */
  uint8_t exec_inst;                          /* byte 38 */
  uint8_t handling_inst;                      /* byte 39 */
  uint8_t order_qty[4];                       /* bytes 40 to 43 */
  uint8_t ord_type;                           /* byte 44 */
  uint8_t price[8];                           /* bytes 45 to 52 */
  uint8_t stop_px[8];                         /* bytes 53 to 60 */
  uint8_t side;                               /* byte 61 */
  uint8_t symbol[14];                         /* bytes 62 to 75 */
  uint8_t time_in_force;                      /* byte 76 */
  uint8_t settlement_type;                    /* byte 77 */
  uint8_t fut_settl_date[4];                  /* bytes 78 to 81 */
  uint8_t ex_destination;                     /* byte 82 */
  uint8_t max_floor[4];                       /* bytes 83 to 86 */
  uint8_t expire_time[8];                     /* bytes 87 to 94 */
  uint8_t expire_date[4];                     /* bytes 95 to 98 */
  uint8_t lei_order_origin;                   /* byte 99 */
  uint8_t lei_routing_arrangement_indicator;  /* byte 100 */
  uint8_t umir_account_type;                  /* byte 101 */
  uint8_t umir_user_id[12];                   /* bytes 102 to 113 */
  uint8_t basket_trade[4];                    /* bytes 114 to 117 */
  uint8_t program_trade;                      /* byte 118 */
  uint8_t jitney[2];                          /* bytes 119 to 120 */
  uint8_t anonymous;                          /* byte 121 */
  uint8_t umir_regulation_id;                 /* byte 122 */
  uint8_t non_resident;                       /* byte 123 */
  uint8_t bypass;                             /* byte 124 */
  uint8_t ncib;                               /* byte 125 */
  uint8_t no_trade_feat;                      /* byte 126 */
  uint8_t no_trade_key[6];                    /* bytes 127 to 132 */
  uint8_t short_marking_exempt;               /* byte 133 */
  uint8_t lei_customer_account[20];           /* bytes 134 to 153 */
  uint8_t lei_algorithm_id[20];               /* bytes 154 to 173 */
  uint8_t customer_lei[52];                   /* bytes 174 to 225 */
  uint8_t broker_lei[20];                     /* bytes 226 to 245 */
  uint8_t routing_inst;                       /* byte 246 */
  uint8_t display_indicator;                  /* byte 247 */
  uint8_t matching_state_participation;       /* byte 248 */
  uint8_t true_min_qty[4];                    /* bytes 249 to 252 */
  uint8_t peg_difference[8];                  /* bytes 253 to 260 */
} NewOrderCaEquitiesV2;

/* any New Order Ca Equities V 2 at all: every byte one the checker chooses */
static void any_new_order_ca_equities_v2(NewOrderCaEquitiesV2 *record) {
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  record->handling_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
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
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
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
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = arbitrary(); }
  record->short_marking_exempt = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = arbitrary(); }
  record->routing_inst = arbitrary();
  record->display_indicator = arbitrary();
  record->matching_state_participation = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->peg_difference[i] = arbitrary(); }
}

/* New Order Ca Equities V 2 to the wire: 261 bytes from at, returning where the next byte goes */
static size_t encode_new_order_ca_equities_v2(const NewOrderCaEquitiesV2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->exec_inst;
  wire[at++] = record->handling_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
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
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
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
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->short_marking_exempt;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->broker_lei[i]; }
  wire[at++] = record->routing_inst;
  wire[at++] = record->display_indicator;
  wire[at++] = record->matching_state_participation;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->peg_difference[i]; }

  return at;
}

/* New Order Ca Equities V 2 off the wire: 261 bytes from at, returning where the next byte lies */
static size_t decode_new_order_ca_equities_v2(NewOrderCaEquitiesV2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  record->handling_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
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
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->no_trade_key[i] = wire[at++]; }
  record->short_marking_exempt = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->broker_lei[i] = wire[at++]; }
  record->routing_inst = wire[at++];
  record->display_indicator = wire[at++];
  record->matching_state_participation = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->peg_difference[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Ca Equities V 2 is what was written, byte for byte */
static void equal_new_order_ca_equities_v2(const NewOrderCaEquitiesV2 *read, const NewOrderCaEquitiesV2 *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  assert(read->handling_inst == written->handling_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
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
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
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
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 6; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->short_marking_exempt == written->short_marking_exempt);
  for (size_t i = 0; i < 20; i++) { assert(read->lei_customer_account[i] == written->lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->lei_algorithm_id[i] == written->lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->customer_lei[i] == written->customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->broker_lei[i] == written->broker_lei[i]); }
  assert(read->routing_inst == written->routing_inst);
  assert(read->display_indicator == written->display_indicator);
  assert(read->matching_state_participation == written->matching_state_participation);
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->peg_difference[i] == written->peg_difference[i]); }
}

/* New Order Ca Equities V 2: written and read back, then read and written back */
static void check_new_order_ca_equities_v2(void) {
  NewOrderCaEquitiesV2 sent;
  NewOrderCaEquitiesV2 got;
  uint8_t wire[261];
  uint8_t again[261];

  any_new_order_ca_equities_v2(&sent);
  assert(encode_new_order_ca_equities_v2(&sent, wire, 0) == 261);
  assert(decode_new_order_ca_equities_v2(&got, wire, 0) == 261);
  equal_new_order_ca_equities_v2(&got, &sent);

  for (size_t i = 0; i < 261; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_ca_equities_v2(&got, wire, 0) == 261);
  assert(encode_new_order_ca_equities_v2(&got, again, 0) == 261);
  for (size_t i = 0; i < 261; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Ca Equities V 1: 215 bytes --------------------------------- */

/* Request to modify an existing order */
typedef struct {
  uint8_t cl_ord_id[20];                      /* bytes 0 to 19 */
  uint8_t orig_cl_ord_id[20];                 /* bytes 20 to 39 */
  uint8_t broker_id[2];                       /* bytes 40 to 41 */
  uint8_t account[16];                        /* bytes 42 to 57 */
  uint8_t order_qty[4];                       /* bytes 58 to 61 */
  uint8_t price[8];                           /* bytes 62 to 69 */
  uint8_t stop_px[8];                         /* bytes 70 to 77 */
  uint8_t time_in_force;                      /* byte 78 */
  uint8_t max_floor[4];                       /* bytes 79 to 82 */
  uint8_t expire_date[4];                     /* bytes 83 to 86 */
  uint8_t lei_order_origin;                   /* byte 87 */
  uint8_t lei_routing_arrangement_indicator;  /* byte 88 */
  uint8_t umir_account_type;                  /* byte 89 */
  uint8_t lei_customer_account[20];           /* bytes 90 to 109 */
  uint8_t lei_algorithm_id[20];               /* bytes 110 to 129 */
  uint8_t customer_lei[52];                   /* bytes 130 to 181 */
  uint8_t broker_lei[20];                     /* bytes 182 to 201 */
  uint8_t cancel_orig_on_reject;              /* byte 202 */
  uint8_t true_min_qty[4];                    /* bytes 203 to 206 */
  uint8_t expire_time[8];                     /* bytes 207 to 214 */
} ModifyOrderCaEquitiesV1;

/* any Modify Order Ca Equities V 1 at all: every byte one the checker chooses */
static void any_modify_order_ca_equities_v1(ModifyOrderCaEquitiesV1 *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
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
  record->cancel_orig_on_reject = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
}

/* Modify Order Ca Equities V 1 to the wire: 215 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_ca_equities_v1(const ModifyOrderCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
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
  wire[at++] = record->cancel_orig_on_reject;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->true_min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }

  return at;
}

/* Modify Order Ca Equities V 1 off the wire: 215 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_ca_equities_v1(ModifyOrderCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
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
  record->cancel_orig_on_reject = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->true_min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Ca Equities V 1 is what was written, byte for byte */
static void equal_modify_order_ca_equities_v1(const ModifyOrderCaEquitiesV1 *read, const ModifyOrderCaEquitiesV1 *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
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
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
  for (size_t i = 0; i < 4; i++) { assert(read->true_min_qty[i] == written->true_min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
}

/* Modify Order Ca Equities V 1: written and read back, then read and written back */
static void check_modify_order_ca_equities_v1(void) {
  ModifyOrderCaEquitiesV1 sent;
  ModifyOrderCaEquitiesV1 got;
  uint8_t wire[215];
  uint8_t again[215];

  any_modify_order_ca_equities_v1(&sent);
  assert(encode_modify_order_ca_equities_v1(&sent, wire, 0) == 215);
  assert(decode_modify_order_ca_equities_v1(&got, wire, 0) == 215);
  equal_modify_order_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 215; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_ca_equities_v1(&got, wire, 0) == 215);
  assert(encode_modify_order_ca_equities_v1(&got, again, 0) == 215);
  for (size_t i = 0; i < 215; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Ca Equities V 1: 22 bytes ---------------------------------- */

/* Request to cancel a single order */
typedef struct {
  uint8_t broker_id[2];        /* bytes 0 to 1 */
  uint8_t orig_cl_ord_id[20];  /* bytes 2 to 21 */
} CancelOrderCaEquitiesV1;

/* any Cancel Order Ca Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_order_ca_equities_v1(CancelOrderCaEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
}

/* Cancel Order Ca Equities V 1 to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_ca_equities_v1(const CancelOrderCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }

  return at;
}

/* Cancel Order Ca Equities V 1 off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_ca_equities_v1(CancelOrderCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Ca Equities V 1 is what was written, byte for byte */
static void equal_cancel_order_ca_equities_v1(const CancelOrderCaEquitiesV1 *read, const CancelOrderCaEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
}

/* Cancel Order Ca Equities V 1: written and read back, then read and written back */
static void check_cancel_order_ca_equities_v1(void) {
  CancelOrderCaEquitiesV1 sent;
  CancelOrderCaEquitiesV1 got;
  uint8_t wire[22];
  uint8_t again[22];

  any_cancel_order_ca_equities_v1(&sent);
  assert(encode_cancel_order_ca_equities_v1(&sent, wire, 0) == 22);
  assert(decode_cancel_order_ca_equities_v1(&got, wire, 0) == 22);
  equal_cancel_order_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_ca_equities_v1(&got, wire, 0) == 22);
  assert(encode_cancel_order_ca_equities_v1(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Cross Ca Equities V 1: 342 bytes ------------------------------ */

/* New Order Cross message for pre-arranged two-sided trades */
typedef struct {
  uint8_t broker_id[2];                            /* bytes 0 to 1 */
  uint8_t cross_cl_ord_id[18];                     /* bytes 2 to 19 */
  uint8_t cross_type;                              /* byte 20 */
  uint8_t price[8];                                /* bytes 21 to 28 */
  uint8_t order_qty[4];                            /* bytes 29 to 32 */
  uint8_t symbol[14];                              /* bytes 33 to 46 */
  uint8_t settlement_type;                         /* byte 47 */
  uint8_t fut_settl_date[4];                       /* bytes 48 to 51 */
  uint8_t umir_user_id[12];                        /* bytes 52 to 63 */
  uint8_t basket_trade[4];                         /* bytes 64 to 67 */
  uint8_t program_trade;                           /* byte 68 */
  uint8_t non_resident;                            /* byte 69 */
  uint8_t bypass;                                  /* byte 70 */
  uint8_t ncib;                                    /* byte 71 */
  uint8_t cross_side;                              /* byte 72 */
  uint8_t short_marking_exempt;                    /* byte 73 */
  uint8_t buy_umir_account_type;                   /* byte 74 */
  uint8_t buy_account[16];                         /* bytes 75 to 90 */
  uint8_t buy_umir_regulation_id;                  /* byte 91 */
  uint8_t buy_jitney[2];                           /* bytes 92 to 93 */
  uint8_t buy_lei_customer_account[20];            /* bytes 94 to 113 */
  uint8_t buy_lei_algorithm_id[20];                /* bytes 114 to 133 */
  uint8_t buy_customer_lei[52];                    /* bytes 134 to 185 */
  uint8_t buy_broker_lei[20];                      /* bytes 186 to 205 */
  uint8_t buy_lei_order_origin;                    /* byte 206 */
  uint8_t buy_lei_routing_arrangemeant_indicator;  /* byte 207 */
  uint8_t sell_umir_account_type;                  /* byte 208 */
  uint8_t sell_account[16];                        /* bytes 209 to 224 */
  uint8_t sell_umir_regulation_id;                 /* byte 225 */
  uint8_t sell_jitney[2];                          /* bytes 226 to 227 */
  uint8_t sell_lei_customer_account[20];           /* bytes 228 to 247 */
  uint8_t sell_lei_algorithm_id[20];               /* bytes 248 to 267 */
  uint8_t sell_customer_lei[52];                   /* bytes 268 to 319 */
  uint8_t sell_broker_lei[20];                     /* bytes 320 to 339 */
  uint8_t sell_lei_order_origin;                   /* byte 340 */
  uint8_t sell_lei_routing_arrangement_indicator;  /* byte 341 */
} NewOrderCrossCaEquitiesV1;

/* any New Order Cross Ca Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_cross_ca_equities_v1(NewOrderCrossCaEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->cross_cl_ord_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = arbitrary(); }
  record->program_trade = arbitrary();
  record->non_resident = arbitrary();
  record->bypass = arbitrary();
  record->ncib = arbitrary();
  record->cross_side = arbitrary();
  record->short_marking_exempt = arbitrary();
  record->buy_umir_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->buy_account[i] = arbitrary(); }
  record->buy_umir_regulation_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->buy_jitney[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->buy_customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_broker_lei[i] = arbitrary(); }
  record->buy_lei_order_origin = arbitrary();
  record->buy_lei_routing_arrangemeant_indicator = arbitrary();
  record->sell_umir_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->sell_account[i] = arbitrary(); }
  record->sell_umir_regulation_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sell_jitney[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->sell_customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_broker_lei[i] = arbitrary(); }
  record->sell_lei_order_origin = arbitrary();
  record->sell_lei_routing_arrangement_indicator = arbitrary();
}

/* New Order Cross Ca Equities V 1 to the wire: 342 bytes from at, returning where the next byte goes */
static size_t encode_new_order_cross_ca_equities_v1(const NewOrderCrossCaEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->cross_cl_ord_id[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fut_settl_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->umir_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->basket_trade[i]; }
  wire[at++] = record->program_trade;
  wire[at++] = record->non_resident;
  wire[at++] = record->bypass;
  wire[at++] = record->ncib;
  wire[at++] = record->cross_side;
  wire[at++] = record->short_marking_exempt;
  wire[at++] = record->buy_umir_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->buy_account[i]; }
  wire[at++] = record->buy_umir_regulation_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_jitney[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->buy_customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_broker_lei[i]; }
  wire[at++] = record->buy_lei_order_origin;
  wire[at++] = record->buy_lei_routing_arrangemeant_indicator;
  wire[at++] = record->sell_umir_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->sell_account[i]; }
  wire[at++] = record->sell_umir_regulation_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_jitney[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->sell_customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_broker_lei[i]; }
  wire[at++] = record->sell_lei_order_origin;
  wire[at++] = record->sell_lei_routing_arrangement_indicator;

  return at;
}

/* New Order Cross Ca Equities V 1 off the wire: 342 bytes from at, returning where the next byte lies */
static size_t decode_new_order_cross_ca_equities_v1(NewOrderCrossCaEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->cross_cl_ord_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = wire[at++]; }
  record->program_trade = wire[at++];
  record->non_resident = wire[at++];
  record->bypass = wire[at++];
  record->ncib = wire[at++];
  record->cross_side = wire[at++];
  record->short_marking_exempt = wire[at++];
  record->buy_umir_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->buy_account[i] = wire[at++]; }
  record->buy_umir_regulation_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->buy_jitney[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->buy_customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_broker_lei[i] = wire[at++]; }
  record->buy_lei_order_origin = wire[at++];
  record->buy_lei_routing_arrangemeant_indicator = wire[at++];
  record->sell_umir_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->sell_account[i] = wire[at++]; }
  record->sell_umir_regulation_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sell_jitney[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->sell_customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_broker_lei[i] = wire[at++]; }
  record->sell_lei_order_origin = wire[at++];
  record->sell_lei_routing_arrangement_indicator = wire[at++];

  return at;
}

/* what was read of New Order Cross Ca Equities V 1 is what was written, byte for byte */
static void equal_new_order_cross_ca_equities_v1(const NewOrderCrossCaEquitiesV1 *read, const NewOrderCrossCaEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->cross_cl_ord_id[i] == written->cross_cl_ord_id[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->fut_settl_date[i] == written->fut_settl_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->umir_user_id[i] == written->umir_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->basket_trade[i] == written->basket_trade[i]); }
  assert(read->program_trade == written->program_trade);
  assert(read->non_resident == written->non_resident);
  assert(read->bypass == written->bypass);
  assert(read->ncib == written->ncib);
  assert(read->cross_side == written->cross_side);
  assert(read->short_marking_exempt == written->short_marking_exempt);
  assert(read->buy_umir_account_type == written->buy_umir_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->buy_account[i] == written->buy_account[i]); }
  assert(read->buy_umir_regulation_id == written->buy_umir_regulation_id);
  for (size_t i = 0; i < 2; i++) { assert(read->buy_jitney[i] == written->buy_jitney[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_lei_customer_account[i] == written->buy_lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_lei_algorithm_id[i] == written->buy_lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->buy_customer_lei[i] == written->buy_customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_broker_lei[i] == written->buy_broker_lei[i]); }
  assert(read->buy_lei_order_origin == written->buy_lei_order_origin);
  assert(read->buy_lei_routing_arrangemeant_indicator == written->buy_lei_routing_arrangemeant_indicator);
  assert(read->sell_umir_account_type == written->sell_umir_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->sell_account[i] == written->sell_account[i]); }
  assert(read->sell_umir_regulation_id == written->sell_umir_regulation_id);
  for (size_t i = 0; i < 2; i++) { assert(read->sell_jitney[i] == written->sell_jitney[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_lei_customer_account[i] == written->sell_lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_lei_algorithm_id[i] == written->sell_lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->sell_customer_lei[i] == written->sell_customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_broker_lei[i] == written->sell_broker_lei[i]); }
  assert(read->sell_lei_order_origin == written->sell_lei_order_origin);
  assert(read->sell_lei_routing_arrangement_indicator == written->sell_lei_routing_arrangement_indicator);
}

/* New Order Cross Ca Equities V 1: written and read back, then read and written back */
static void check_new_order_cross_ca_equities_v1(void) {
  NewOrderCrossCaEquitiesV1 sent;
  NewOrderCrossCaEquitiesV1 got;
  uint8_t wire[342];
  uint8_t again[342];

  any_new_order_cross_ca_equities_v1(&sent);
  assert(encode_new_order_cross_ca_equities_v1(&sent, wire, 0) == 342);
  assert(decode_new_order_cross_ca_equities_v1(&got, wire, 0) == 342);
  equal_new_order_cross_ca_equities_v1(&got, &sent);

  for (size_t i = 0; i < 342; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_cross_ca_equities_v1(&got, wire, 0) == 342);
  assert(encode_new_order_cross_ca_equities_v1(&got, again, 0) == 342);
  for (size_t i = 0; i < 342; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Cross Ca Equities V 2: 347 bytes ------------------------------ */

/* New Order Cross V2 message with Anonymous flag */
typedef struct {
  uint8_t broker_id[2];                            /* bytes 0 to 1 */
  uint8_t cross_cl_ord_id[18];                     /* bytes 2 to 19 */
  uint8_t cross_type;                              /* byte 20 */
  uint8_t price[8];                                /* bytes 21 to 28 */
  uint8_t order_qty[4];                            /* bytes 29 to 32 */
  uint8_t symbol[14];                              /* bytes 33 to 46 */
  uint8_t settlement_type;                         /* byte 47 */
  uint8_t fut_settl_date[4];                       /* bytes 48 to 51 */
  uint8_t umir_user_id[12];                        /* bytes 52 to 63 */
  uint8_t basket_trade[4];                         /* bytes 64 to 67 */
  uint8_t program_trade;                           /* byte 68 */
  uint8_t non_resident;                            /* byte 69 */
  uint8_t bypass;                                  /* byte 70 */
  uint8_t ncib;                                    /* byte 71 */
  uint8_t cross_side;                              /* byte 72 */
  uint8_t short_marking_exempt;                    /* byte 73 */
  uint8_t buy_umir_account_type;                   /* byte 74 */
  uint8_t buy_account[16];                         /* bytes 75 to 90 */
  uint8_t buy_umir_regulation_id;                  /* byte 91 */
  uint8_t buy_jitney[2];                           /* bytes 92 to 93 */
  uint8_t buy_lei_customer_account[20];            /* bytes 94 to 113 */
  uint8_t buy_lei_algorithm_id[20];                /* bytes 114 to 133 */
  uint8_t buy_customer_lei[52];                    /* bytes 134 to 185 */
  uint8_t buy_broker_lei[20];                      /* bytes 186 to 205 */
  uint8_t buy_lei_order_origin;                    /* byte 206 */
  uint8_t buy_lei_routing_arrangement_indicator;   /* byte 207 */
  uint8_t sell_umir_account_type;                  /* byte 208 */
  uint8_t sell_account[16];                        /* bytes 209 to 224 */
  uint8_t sell_umir_regulation_id;                 /* byte 225 */
  uint8_t sell_jitney[2];                          /* bytes 226 to 227 */
  uint8_t sell_lei_customer_account[20];           /* bytes 228 to 247 */
  uint8_t sell_lei_algorithm_id[20];               /* bytes 248 to 267 */
  uint8_t sell_customer_lei[52];                   /* bytes 268 to 319 */
  uint8_t sell_broker_lei[20];                     /* bytes 320 to 339 */
  uint8_t sell_lei_order_origin;                   /* byte 340 */
  uint8_t sell_lei_routing_arrangement_indicator;  /* byte 341 */
  uint8_t anonymous;                               /* byte 342 */
  uint8_t reserved[4];                             /* bytes 343 to 346 */
} NewOrderCrossCaEquitiesV2;

/* any New Order Cross Ca Equities V 2 at all: every byte one the checker chooses */
static void any_new_order_cross_ca_equities_v2(NewOrderCrossCaEquitiesV2 *record) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->cross_cl_ord_id[i] = arbitrary(); }
  record->cross_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = arbitrary(); }
  record->settlement_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = arbitrary(); }
  record->program_trade = arbitrary();
  record->non_resident = arbitrary();
  record->bypass = arbitrary();
  record->ncib = arbitrary();
  record->cross_side = arbitrary();
  record->short_marking_exempt = arbitrary();
  record->buy_umir_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->buy_account[i] = arbitrary(); }
  record->buy_umir_regulation_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->buy_jitney[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->buy_customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->buy_broker_lei[i] = arbitrary(); }
  record->buy_lei_order_origin = arbitrary();
  record->buy_lei_routing_arrangement_indicator = arbitrary();
  record->sell_umir_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->sell_account[i] = arbitrary(); }
  record->sell_umir_regulation_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->sell_jitney[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_customer_account[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_algorithm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 52; i++) { record->sell_customer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sell_broker_lei[i] = arbitrary(); }
  record->sell_lei_order_origin = arbitrary();
  record->sell_lei_routing_arrangement_indicator = arbitrary();
  record->anonymous = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved[i] = arbitrary(); }
}

/* New Order Cross Ca Equities V 2 to the wire: 347 bytes from at, returning where the next byte goes */
static size_t encode_new_order_cross_ca_equities_v2(const NewOrderCrossCaEquitiesV2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->cross_cl_ord_id[i]; }
  wire[at++] = record->cross_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->settlement_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fut_settl_date[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->umir_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->basket_trade[i]; }
  wire[at++] = record->program_trade;
  wire[at++] = record->non_resident;
  wire[at++] = record->bypass;
  wire[at++] = record->ncib;
  wire[at++] = record->cross_side;
  wire[at++] = record->short_marking_exempt;
  wire[at++] = record->buy_umir_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->buy_account[i]; }
  wire[at++] = record->buy_umir_regulation_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_jitney[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->buy_customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->buy_broker_lei[i]; }
  wire[at++] = record->buy_lei_order_origin;
  wire[at++] = record->buy_lei_routing_arrangement_indicator;
  wire[at++] = record->sell_umir_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->sell_account[i]; }
  wire[at++] = record->sell_umir_regulation_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_jitney[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_lei_customer_account[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_lei_algorithm_id[i]; }
  for (size_t i = 0; i < 52; i++) { wire[at++] = record->sell_customer_lei[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sell_broker_lei[i]; }
  wire[at++] = record->sell_lei_order_origin;
  wire[at++] = record->sell_lei_routing_arrangement_indicator;
  wire[at++] = record->anonymous;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved[i]; }

  return at;
}

/* New Order Cross Ca Equities V 2 off the wire: 347 bytes from at, returning where the next byte lies */
static size_t decode_new_order_cross_ca_equities_v2(NewOrderCrossCaEquitiesV2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->cross_cl_ord_id[i] = wire[at++]; }
  record->cross_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->symbol[i] = wire[at++]; }
  record->settlement_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->fut_settl_date[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->umir_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->basket_trade[i] = wire[at++]; }
  record->program_trade = wire[at++];
  record->non_resident = wire[at++];
  record->bypass = wire[at++];
  record->ncib = wire[at++];
  record->cross_side = wire[at++];
  record->short_marking_exempt = wire[at++];
  record->buy_umir_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->buy_account[i] = wire[at++]; }
  record->buy_umir_regulation_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->buy_jitney[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->buy_customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->buy_broker_lei[i] = wire[at++]; }
  record->buy_lei_order_origin = wire[at++];
  record->buy_lei_routing_arrangement_indicator = wire[at++];
  record->sell_umir_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->sell_account[i] = wire[at++]; }
  record->sell_umir_regulation_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->sell_jitney[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_customer_account[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_lei_algorithm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 52; i++) { record->sell_customer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sell_broker_lei[i] = wire[at++]; }
  record->sell_lei_order_origin = wire[at++];
  record->sell_lei_routing_arrangement_indicator = wire[at++];
  record->anonymous = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Cross Ca Equities V 2 is what was written, byte for byte */
static void equal_new_order_cross_ca_equities_v2(const NewOrderCrossCaEquitiesV2 *read, const NewOrderCrossCaEquitiesV2 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->cross_cl_ord_id[i] == written->cross_cl_ord_id[i]); }
  assert(read->cross_type == written->cross_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->settlement_type == written->settlement_type);
  for (size_t i = 0; i < 4; i++) { assert(read->fut_settl_date[i] == written->fut_settl_date[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->umir_user_id[i] == written->umir_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->basket_trade[i] == written->basket_trade[i]); }
  assert(read->program_trade == written->program_trade);
  assert(read->non_resident == written->non_resident);
  assert(read->bypass == written->bypass);
  assert(read->ncib == written->ncib);
  assert(read->cross_side == written->cross_side);
  assert(read->short_marking_exempt == written->short_marking_exempt);
  assert(read->buy_umir_account_type == written->buy_umir_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->buy_account[i] == written->buy_account[i]); }
  assert(read->buy_umir_regulation_id == written->buy_umir_regulation_id);
  for (size_t i = 0; i < 2; i++) { assert(read->buy_jitney[i] == written->buy_jitney[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_lei_customer_account[i] == written->buy_lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_lei_algorithm_id[i] == written->buy_lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->buy_customer_lei[i] == written->buy_customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->buy_broker_lei[i] == written->buy_broker_lei[i]); }
  assert(read->buy_lei_order_origin == written->buy_lei_order_origin);
  assert(read->buy_lei_routing_arrangement_indicator == written->buy_lei_routing_arrangement_indicator);
  assert(read->sell_umir_account_type == written->sell_umir_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->sell_account[i] == written->sell_account[i]); }
  assert(read->sell_umir_regulation_id == written->sell_umir_regulation_id);
  for (size_t i = 0; i < 2; i++) { assert(read->sell_jitney[i] == written->sell_jitney[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_lei_customer_account[i] == written->sell_lei_customer_account[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_lei_algorithm_id[i] == written->sell_lei_algorithm_id[i]); }
  for (size_t i = 0; i < 52; i++) { assert(read->sell_customer_lei[i] == written->sell_customer_lei[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sell_broker_lei[i] == written->sell_broker_lei[i]); }
  assert(read->sell_lei_order_origin == written->sell_lei_order_origin);
  assert(read->sell_lei_routing_arrangement_indicator == written->sell_lei_routing_arrangement_indicator);
  assert(read->anonymous == written->anonymous);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved[i] == written->reserved[i]); }
}

/* New Order Cross Ca Equities V 2: written and read back, then read and written back */
static void check_new_order_cross_ca_equities_v2(void) {
  NewOrderCrossCaEquitiesV2 sent;
  NewOrderCrossCaEquitiesV2 got;
  uint8_t wire[347];
  uint8_t again[347];

  any_new_order_cross_ca_equities_v2(&sent);
  assert(encode_new_order_cross_ca_equities_v2(&sent, wire, 0) == 347);
  assert(decode_new_order_cross_ca_equities_v2(&got, wire, 0) == 347);
  equal_new_order_cross_ca_equities_v2(&got, &sent);

  for (size_t i = 0; i < 347; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_cross_ca_equities_v2(&got, wire, 0) == 347);
  assert(encode_new_order_cross_ca_equities_v2(&got, again, 0) == 347);
  for (size_t i = 0; i < 347; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_new_order_ca_equities_v1();
  check_new_order_ca_equities_v2();
  check_modify_order_ca_equities_v1();
  check_cancel_order_ca_equities_v1();
  check_new_order_cross_ca_equities_v1();
  check_new_order_cross_ca_equities_v2();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
