// cboe/cxaequities/binaryorderentry/CxaEquities_BinaryOrderEntry_v1_0_20_Firm.c
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

/* ---- New Order Au Equities V 1: 160 bytes ------------------------------------ */

/* Submission of a new order to Cboe Australia */
typedef struct {
  uint8_t account[10];                    /* bytes 0 to 9 */
  uint8_t trading_participant_id[2];      /* bytes 10 to 11 */
  uint8_t cl_ord_id[20];                  /* bytes 12 to 31 */
  uint8_t exec_inst;                      /* byte 32 */
  uint8_t order_qty[4];                   /* bytes 33 to 36 */
  uint8_t ord_type;                       /* byte 37 */
  uint8_t price[8];                       /* bytes 38 to 45 */
  uint8_t capacity;                       /* byte 46 */
  uint8_t side;                           /* byte 47 */
  uint8_t symbol[6];                      /* bytes 48 to 53 */
  uint8_t time_in_force;                  /* byte 54 */
  uint8_t min_qty[4];                     /* bytes 55 to 58 */
  uint8_t max_floor[4];                   /* bytes 59 to 62 */
  uint8_t expire_time[8];                 /* bytes 63 to 70 */
  uint8_t clearing_participant_id[4];     /* bytes 71 to 74 */
  uint8_t clearing_account[10];           /* bytes 75 to 84 */
  uint8_t undisclosed;                    /* byte 85 */
  uint8_t client_cross_ref[15];           /* bytes 86 to 100 */
  uint8_t short_sell_naked_qty[4];        /* bytes 101 to 104 */
  uint8_t short_sell_covered_qty[4];      /* bytes 105 to 108 */
  uint8_t short_sell_long_qty[4];         /* bytes 109 to 112 */
  uint8_t risk_group_id[2];               /* bytes 113 to 114 */
  uint8_t no_trade_feat;                  /* byte 115 */
  uint8_t no_trade_key[10];               /* bytes 116 to 125 */
  uint8_t meqse;                          /* byte 126 */
  uint8_t origin_of_trans[20];            /* bytes 127 to 146 */
  uint8_t intermediary_id[10];            /* bytes 147 to 156 */
  uint8_t directed_wholesale_indicator;   /* byte 157 */
  uint8_t remove_crossing_from_clearing;  /* byte 158 */
  uint8_t broker_preferencing;            /* byte 159 */
} NewOrderAuEquitiesV1;

/* any New Order Au Equities V 1 at all: every byte one the checker chooses */
static void any_new_order_au_equities_v1(NewOrderAuEquitiesV1 *record) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = arbitrary(); }
  record->undisclosed = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = arbitrary(); }
  record->meqse = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  record->directed_wholesale_indicator = arbitrary();
  record->remove_crossing_from_clearing = arbitrary();
  record->broker_preferencing = arbitrary();
}

/* New Order Au Equities V 1 to the wire: 160 bytes from at, returning where the next byte goes */
static size_t encode_new_order_au_equities_v1(const NewOrderAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->undisclosed;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_cross_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->meqse;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->origin_of_trans[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  wire[at++] = record->directed_wholesale_indicator;
  wire[at++] = record->remove_crossing_from_clearing;
  wire[at++] = record->broker_preferencing;

  return at;
}

/* New Order Au Equities V 1 off the wire: 160 bytes from at, returning where the next byte lies */
static size_t decode_new_order_au_equities_v1(NewOrderAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = wire[at++]; }
  record->undisclosed = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = wire[at++]; }
  record->meqse = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  record->directed_wholesale_indicator = wire[at++];
  record->remove_crossing_from_clearing = wire[at++];
  record->broker_preferencing = wire[at++];

  return at;
}

/* what was read of New Order Au Equities V 1 is what was written, byte for byte */
static void equal_new_order_au_equities_v1(const NewOrderAuEquitiesV1 *read, const NewOrderAuEquitiesV1 *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->capacity == written->capacity);
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->undisclosed == written->undisclosed);
  for (size_t i = 0; i < 15; i++) { assert(read->client_cross_ref[i] == written->client_cross_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 10; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->meqse == written->meqse);
  for (size_t i = 0; i < 20; i++) { assert(read->origin_of_trans[i] == written->origin_of_trans[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  assert(read->directed_wholesale_indicator == written->directed_wholesale_indicator);
  assert(read->remove_crossing_from_clearing == written->remove_crossing_from_clearing);
  assert(read->broker_preferencing == written->broker_preferencing);
}

/* New Order Au Equities V 1: written and read back, then read and written back */
static void check_new_order_au_equities_v1(void) {
  NewOrderAuEquitiesV1 sent;
  NewOrderAuEquitiesV1 got;
  uint8_t wire[160];
  uint8_t again[160];

  any_new_order_au_equities_v1(&sent);
  assert(encode_new_order_au_equities_v1(&sent, wire, 0) == 160);
  assert(decode_new_order_au_equities_v1(&got, wire, 0) == 160);
  equal_new_order_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 160; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_au_equities_v1(&got, wire, 0) == 160);
  assert(encode_new_order_au_equities_v1(&got, again, 0) == 160);
  for (size_t i = 0; i < 160; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Au Equities V 2: 166 bytes ------------------------------------ */

/* Submission of a new order to Cboe Australia, with Post Only and multi-day order fields */
typedef struct {
  uint8_t account[10];                    /* bytes 0 to 9 */
  uint8_t trading_participant_id[2];      /* bytes 10 to 11 */
  uint8_t cl_ord_id[20];                  /* bytes 12 to 31 */
  uint8_t exec_inst;                      /* byte 32 */
  uint8_t order_qty[4];                   /* bytes 33 to 36 */
  uint8_t ord_type;                       /* byte 37 */
  uint8_t price[8];                       /* bytes 38 to 45 */
  uint8_t capacity;                       /* byte 46 */
  uint8_t side;                           /* byte 47 */
  uint8_t symbol[6];                      /* bytes 48 to 53 */
  uint8_t time_in_force;                  /* byte 54 */
  uint8_t min_qty[4];                     /* bytes 55 to 58 */
  uint8_t max_floor[4];                   /* bytes 59 to 62 */
  uint8_t expire_time[8];                 /* bytes 63 to 70 */
  uint8_t clearing_participant_id[4];     /* bytes 71 to 74 */
  uint8_t clearing_account[10];           /* bytes 75 to 84 */
  uint8_t undisclosed;                    /* byte 85 */
  uint8_t client_cross_ref[15];           /* bytes 86 to 100 */
  uint8_t short_sell_naked_qty[4];        /* bytes 101 to 104 */
  uint8_t short_sell_covered_qty[4];      /* bytes 105 to 108 */
  uint8_t short_sell_long_qty[4];         /* bytes 109 to 112 */
  uint8_t risk_group_id[2];               /* bytes 113 to 114 */
  uint8_t no_trade_feat;                  /* byte 115 */
  uint8_t no_trade_key[10];               /* bytes 116 to 125 */
  uint8_t meqse;                          /* byte 126 */
  uint8_t origin_of_trans[20];            /* bytes 127 to 146 */
  uint8_t intermediary_id[10];            /* bytes 147 to 156 */
  uint8_t directed_wholesale_indicator;   /* byte 157 */
  uint8_t remove_crossing_from_clearing;  /* byte 158 */
  uint8_t broker_preferencing;            /* byte 159 */
  uint8_t routing_inst;                   /* byte 160 */
  uint8_t display_indicator;              /* byte 161 */
  uint8_t expire_date[4];                 /* bytes 162 to 165 */
} NewOrderAuEquitiesV2;

/* any New Order Au Equities V 2 at all: every byte one the checker chooses */
static void any_new_order_au_equities_v2(NewOrderAuEquitiesV2 *record) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = arbitrary(); }
  record->undisclosed = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = arbitrary(); }
  record->no_trade_feat = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = arbitrary(); }
  record->meqse = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = arbitrary(); }
  record->directed_wholesale_indicator = arbitrary();
  record->remove_crossing_from_clearing = arbitrary();
  record->broker_preferencing = arbitrary();
  record->routing_inst = arbitrary();
  record->display_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* New Order Au Equities V 2 to the wire: 166 bytes from at, returning where the next byte goes */
static size_t encode_new_order_au_equities_v2(const NewOrderAuEquitiesV2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_participant_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->undisclosed;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_cross_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->risk_group_id[i]; }
  wire[at++] = record->no_trade_feat;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->no_trade_key[i]; }
  wire[at++] = record->meqse;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->origin_of_trans[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->intermediary_id[i]; }
  wire[at++] = record->directed_wholesale_indicator;
  wire[at++] = record->remove_crossing_from_clearing;
  wire[at++] = record->broker_preferencing;
  wire[at++] = record->routing_inst;
  wire[at++] = record->display_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* New Order Au Equities V 2 off the wire: 166 bytes from at, returning where the next byte lies */
static size_t decode_new_order_au_equities_v2(NewOrderAuEquitiesV2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->clearing_account[i] = wire[at++]; }
  record->undisclosed = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_cross_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->risk_group_id[i] = wire[at++]; }
  record->no_trade_feat = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->no_trade_key[i] = wire[at++]; }
  record->meqse = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->origin_of_trans[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->intermediary_id[i] = wire[at++]; }
  record->directed_wholesale_indicator = wire[at++];
  record->remove_crossing_from_clearing = wire[at++];
  record->broker_preferencing = wire[at++];
  record->routing_inst = wire[at++];
  record->display_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Au Equities V 2 is what was written, byte for byte */
static void equal_new_order_au_equities_v2(const NewOrderAuEquitiesV2 *read, const NewOrderAuEquitiesV2 *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->capacity == written->capacity);
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_participant_id[i] == written->clearing_participant_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->undisclosed == written->undisclosed);
  for (size_t i = 0; i < 15; i++) { assert(read->client_cross_ref[i] == written->client_cross_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->risk_group_id[i] == written->risk_group_id[i]); }
  assert(read->no_trade_feat == written->no_trade_feat);
  for (size_t i = 0; i < 10; i++) { assert(read->no_trade_key[i] == written->no_trade_key[i]); }
  assert(read->meqse == written->meqse);
  for (size_t i = 0; i < 20; i++) { assert(read->origin_of_trans[i] == written->origin_of_trans[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->intermediary_id[i] == written->intermediary_id[i]); }
  assert(read->directed_wholesale_indicator == written->directed_wholesale_indicator);
  assert(read->remove_crossing_from_clearing == written->remove_crossing_from_clearing);
  assert(read->broker_preferencing == written->broker_preferencing);
  assert(read->routing_inst == written->routing_inst);
  assert(read->display_indicator == written->display_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* New Order Au Equities V 2: written and read back, then read and written back */
static void check_new_order_au_equities_v2(void) {
  NewOrderAuEquitiesV2 sent;
  NewOrderAuEquitiesV2 got;
  uint8_t wire[166];
  uint8_t again[166];

  any_new_order_au_equities_v2(&sent);
  assert(encode_new_order_au_equities_v2(&sent, wire, 0) == 166);
  assert(decode_new_order_au_equities_v2(&got, wire, 0) == 166);
  equal_new_order_au_equities_v2(&got, &sent);

  for (size_t i = 0; i < 166; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_au_equities_v2(&got, wire, 0) == 166);
  assert(encode_new_order_au_equities_v2(&got, again, 0) == 166);
  for (size_t i = 0; i < 166; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Au Equities V 1: 76 bytes ---------------------------------- */

/* Request to modify an order */
typedef struct {
  uint8_t trading_participant_id[2];  /* bytes 0 to 1 */
  uint8_t cl_ord_id[20];              /* bytes 2 to 21 */
  uint8_t exec_inst;                  /* byte 22 */
  uint8_t order_qty[4];               /* bytes 23 to 26 */
  uint8_t orig_cl_ord_id[20];         /* bytes 27 to 46 */
  uint8_t price[8];                   /* bytes 47 to 54 */
  uint8_t min_qty[4];                 /* bytes 55 to 58 */
  uint8_t max_floor[4];               /* bytes 59 to 62 */
  uint8_t short_sell_naked_qty[4];    /* bytes 63 to 66 */
  uint8_t short_sell_covered_qty[4];  /* bytes 67 to 70 */
  uint8_t short_sell_long_qty[4];     /* bytes 71 to 74 */
  uint8_t cancel_orig_on_reject;      /* byte 75 */
} ModifyOrderAuEquitiesV1;

/* any Modify Order Au Equities V 1 at all: every byte one the checker chooses */
static void any_modify_order_au_equities_v1(ModifyOrderAuEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  record->cancel_orig_on_reject = arbitrary();
}

/* Modify Order Au Equities V 1 to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_au_equities_v1(const ModifyOrderAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  wire[at++] = record->cancel_orig_on_reject;

  return at;
}

/* Modify Order Au Equities V 1 off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_au_equities_v1(ModifyOrderAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  record->cancel_orig_on_reject = wire[at++];

  return at;
}

/* what was read of Modify Order Au Equities V 1 is what was written, byte for byte */
static void equal_modify_order_au_equities_v1(const ModifyOrderAuEquitiesV1 *read, const ModifyOrderAuEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
}

/* Modify Order Au Equities V 1: written and read back, then read and written back */
static void check_modify_order_au_equities_v1(void) {
  ModifyOrderAuEquitiesV1 sent;
  ModifyOrderAuEquitiesV1 got;
  uint8_t wire[76];
  uint8_t again[76];

  any_modify_order_au_equities_v1(&sent);
  assert(encode_modify_order_au_equities_v1(&sent, wire, 0) == 76);
  assert(decode_modify_order_au_equities_v1(&got, wire, 0) == 76);
  equal_modify_order_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_au_equities_v1(&got, wire, 0) == 76);
  assert(encode_modify_order_au_equities_v1(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Au Equities V 2: 80 bytes ---------------------------------- */

/* Request to modify an order, with ExpireDate for multi-day orders */
typedef struct {
  uint8_t trading_participant_id[2];  /* bytes 0 to 1 */
  uint8_t cl_ord_id[20];              /* bytes 2 to 21 */
  uint8_t exec_inst;                  /* byte 22 */
  uint8_t order_qty[4];               /* bytes 23 to 26 */
  uint8_t orig_cl_ord_id[20];         /* bytes 27 to 46 */
  uint8_t price[8];                   /* bytes 47 to 54 */
  uint8_t min_qty[4];                 /* bytes 55 to 58 */
  uint8_t max_floor[4];               /* bytes 59 to 62 */
  uint8_t short_sell_naked_qty[4];    /* bytes 63 to 66 */
  uint8_t short_sell_covered_qty[4];  /* bytes 67 to 70 */
  uint8_t short_sell_long_qty[4];     /* bytes 71 to 74 */
  uint8_t cancel_orig_on_reject;      /* byte 75 */
  uint8_t expire_date[4];             /* bytes 76 to 79 */
} ModifyOrderAuEquitiesV2;

/* any Modify Order Au Equities V 2 at all: every byte one the checker chooses */
static void any_modify_order_au_equities_v2(ModifyOrderAuEquitiesV2 *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->exec_inst = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = arbitrary(); }
  record->cancel_orig_on_reject = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = arbitrary(); }
}

/* Modify Order Au Equities V 2 to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_au_equities_v2(const ModifyOrderAuEquitiesV2 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->exec_inst;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_naked_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_covered_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_sell_long_qty[i]; }
  wire[at++] = record->cancel_orig_on_reject;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_date[i]; }

  return at;
}

/* Modify Order Au Equities V 2 off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_au_equities_v2(ModifyOrderAuEquitiesV2 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->exec_inst = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_naked_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_covered_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_sell_long_qty[i] = wire[at++]; }
  record->cancel_orig_on_reject = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->expire_date[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Au Equities V 2 is what was written, byte for byte */
static void equal_modify_order_au_equities_v2(const ModifyOrderAuEquitiesV2 *read, const ModifyOrderAuEquitiesV2 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->exec_inst == written->exec_inst);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_naked_qty[i] == written->short_sell_naked_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_covered_qty[i] == written->short_sell_covered_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_sell_long_qty[i] == written->short_sell_long_qty[i]); }
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
  for (size_t i = 0; i < 4; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
}

/* Modify Order Au Equities V 2: written and read back, then read and written back */
static void check_modify_order_au_equities_v2(void) {
  ModifyOrderAuEquitiesV2 sent;
  ModifyOrderAuEquitiesV2 got;
  uint8_t wire[80];
  uint8_t again[80];

  any_modify_order_au_equities_v2(&sent);
  assert(encode_modify_order_au_equities_v2(&sent, wire, 0) == 80);
  assert(decode_modify_order_au_equities_v2(&got, wire, 0) == 80);
  equal_modify_order_au_equities_v2(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_au_equities_v2(&got, wire, 0) == 80);
  assert(encode_modify_order_au_equities_v2(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Au Equities V 1: 22 bytes ---------------------------------- */

/* Request to cancel a single order */
typedef struct {
  uint8_t trading_participant_id[2];  /* bytes 0 to 1 */
  uint8_t orig_cl_ord_id[20];         /* bytes 2 to 21 */
} CancelOrderAuEquitiesV1;

/* any Cancel Order Au Equities V 1 at all: every byte one the checker chooses */
static void any_cancel_order_au_equities_v1(CancelOrderAuEquitiesV1 *record) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
}

/* Cancel Order Au Equities V 1 to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_au_equities_v1(const CancelOrderAuEquitiesV1 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_participant_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }

  return at;
}

/* Cancel Order Au Equities V 1 off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_au_equities_v1(CancelOrderAuEquitiesV1 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->trading_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Au Equities V 1 is what was written, byte for byte */
static void equal_cancel_order_au_equities_v1(const CancelOrderAuEquitiesV1 *read, const CancelOrderAuEquitiesV1 *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->trading_participant_id[i] == written->trading_participant_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
}

/* Cancel Order Au Equities V 1: written and read back, then read and written back */
static void check_cancel_order_au_equities_v1(void) {
  CancelOrderAuEquitiesV1 sent;
  CancelOrderAuEquitiesV1 got;
  uint8_t wire[22];
  uint8_t again[22];

  any_cancel_order_au_equities_v1(&sent);
  assert(encode_cancel_order_au_equities_v1(&sent, wire, 0) == 22);
  assert(decode_cancel_order_au_equities_v1(&got, wire, 0) == 22);
  equal_cancel_order_au_equities_v1(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_au_equities_v1(&got, wire, 0) == 22);
  assert(encode_cancel_order_au_equities_v1(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_new_order_au_equities_v1();
  check_new_order_au_equities_v2();
  check_modify_order_au_equities_v1();
  check_modify_order_au_equities_v2();
  check_cancel_order_au_equities_v1();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
