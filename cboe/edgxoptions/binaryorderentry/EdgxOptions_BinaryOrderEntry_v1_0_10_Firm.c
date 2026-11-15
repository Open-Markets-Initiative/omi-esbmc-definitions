// cboe/edgxoptions/binaryorderentry/EdgxOptions_BinaryOrderEntry_v1_0_10_Firm.c
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

/* ---- New Order Message: 193 bytes -------------------------------------------- */

/* Submission of a new simple (single leg) order to Cboe */
typedef struct {
  uint8_t cl_ord_id[20];               /* bytes 0 to 19 */
  uint8_t side;                        /* byte 20 */
  uint8_t order_qty[4];                /* bytes 21 to 24 */
  uint8_t clearing_firm[4];            /* bytes 25 to 28 */
  uint8_t clearing_account[4];         /* bytes 29 to 32 */
  uint8_t price[8];                    /* bytes 33 to 40 */
  uint8_t exec_inst;                   /* byte 41 */
  uint8_t ord_type;                    /* byte 42 */
  uint8_t time_in_force;               /* byte 43 */
  uint8_t min_qty[4];                  /* bytes 44 to 47 */
  uint8_t max_floor[4];                /* bytes 48 to 51 */
  uint8_t symbol[8];                   /* bytes 52 to 59 */
  uint8_t capacity;                    /* byte 60 */
  uint8_t routing_inst[4];             /* bytes 61 to 64 */
  uint8_t account[16];                 /* bytes 65 to 80 */
  uint8_t display_indicator;           /* byte 81 */
  PreventMatch prevent_match;          /* bytes 82 to 84 */
  uint8_t expire_time[8];              /* bytes 85 to 92 */
  uint8_t maturity_date[4];            /* bytes 93 to 96 */
  uint8_t strike_price[8];             /* bytes 97 to 104 */
  uint8_t put_or_call;                 /* byte 105 */
  uint8_t open_close;                  /* byte 106 */
  uint8_t cmta_number[4];              /* bytes 107 to 110 */
  uint8_t target_party_id[4];          /* bytes 111 to 114 */
  uint8_t session_eligibility;         /* byte 115 */
  uint8_t attributed_quote;            /* byte 116 */
  uint8_t display_range[4];            /* bytes 117 to 120 */
  uint8_t stop_px[8];                  /* bytes 121 to 128 */
  uint8_t rout_strategy[6];            /* bytes 129 to 134 */
  uint8_t route_delivery_method[3];    /* bytes 135 to 137 */
  uint8_t ex_destination;              /* byte 138 */
  uint8_t auction_id[8];               /* bytes 139 to 146 */
  uint8_t routing_firm_id[4];          /* bytes 147 to 150 */
  uint8_t custom_group_id[2];          /* bytes 151 to 152 */
  uint8_t clearing_optional_data[16];  /* bytes 153 to 168 */
  uint8_t client_id_attr[4];           /* bytes 169 to 172 */
  uint8_t frequent_trader_id[6];       /* bytes 173 to 178 */
  uint8_t compression;                 /* byte 179 */
  uint8_t floor_destination[4];        /* bytes 180 to 183 */
  uint8_t floor_routing_inst;          /* byte 184 */
  uint8_t order_origin[3];             /* bytes 185 to 187 */
  uint8_t order_router_subsidy;        /* byte 188 */
  uint8_t price_type;                  /* byte 189 */
  uint8_t held;                        /* byte 190 */
  uint8_t scratch_pad[2];              /* bytes 191 to 192 */
} NewOrderMessage;

/* any New Order Message at all: every byte one the checker chooses */
static void any_new_order_message(NewOrderMessage *record) {
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
  any_prevent_match(&record->prevent_match);
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->put_or_call = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  record->session_eligibility = arbitrary();
  record->attributed_quote = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->display_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->clearing_optional_data[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id_attr[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  record->compression = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->floor_destination[i] = arbitrary(); }
  record->floor_routing_inst = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->order_origin[i] = arbitrary(); }
  record->order_router_subsidy = arbitrary();
  record->price_type = arbitrary();
  record->held = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* New Order Message to the wire: 193 bytes from at, returning where the next byte goes */
static size_t encode_new_order_message(const NewOrderMessage *record, uint8_t *wire, size_t at) {
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
  at = encode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->put_or_call;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  wire[at++] = record->session_eligibility;
  wire[at++] = record->attributed_quote;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->rout_strategy[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->route_delivery_method[i]; }
  wire[at++] = record->ex_destination;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->clearing_optional_data[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id_attr[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  wire[at++] = record->compression;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->floor_destination[i]; }
  wire[at++] = record->floor_routing_inst;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->order_origin[i]; }
  wire[at++] = record->order_router_subsidy;
  wire[at++] = record->price_type;
  wire[at++] = record->held;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* New Order Message off the wire: 193 bytes from at, returning where the next byte lies */
static size_t decode_new_order_message(NewOrderMessage *record, const uint8_t *wire, size_t at) {
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
  at = decode_prevent_match(&record->prevent_match, wire, at);
  for (size_t i = 0; i < 8; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->put_or_call = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  record->session_eligibility = wire[at++];
  record->attributed_quote = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->display_range[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->route_delivery_method[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->clearing_optional_data[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id_attr[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  record->compression = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->floor_destination[i] = wire[at++]; }
  record->floor_routing_inst = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->order_origin[i] = wire[at++]; }
  record->order_router_subsidy = wire[at++];
  record->price_type = wire[at++];
  record->held = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

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
  equal_prevent_match(&read->prevent_match, &written->prevent_match);
  for (size_t i = 0; i < 8; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->put_or_call == written->put_or_call);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  assert(read->session_eligibility == written->session_eligibility);
  assert(read->attributed_quote == written->attributed_quote);
  for (size_t i = 0; i < 4; i++) { assert(read->display_range[i] == written->display_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->rout_strategy[i] == written->rout_strategy[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->route_delivery_method[i] == written->route_delivery_method[i]); }
  assert(read->ex_destination == written->ex_destination);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id[i] == written->custom_group_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->clearing_optional_data[i] == written->clearing_optional_data[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id_attr[i] == written->client_id_attr[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  assert(read->compression == written->compression);
  for (size_t i = 0; i < 4; i++) { assert(read->floor_destination[i] == written->floor_destination[i]); }
  assert(read->floor_routing_inst == written->floor_routing_inst);
  for (size_t i = 0; i < 3; i++) { assert(read->order_origin[i] == written->order_origin[i]); }
  assert(read->order_router_subsidy == written->order_router_subsidy);
  assert(read->price_type == written->price_type);
  assert(read->held == written->held);
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* New Order Message: written and read back, then read and written back */
static void check_new_order_message(void) {
  NewOrderMessage sent;
  NewOrderMessage got;
  uint8_t wire[193];
  uint8_t again[193];

  any_new_order_message(&sent);
  assert(encode_new_order_message(&sent, wire, 0) == 193);
  assert(decode_new_order_message(&got, wire, 0) == 193);
  equal_new_order_message(&got, &sent);

  for (size_t i = 0; i < 193; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_message(&got, wire, 0) == 193);
  assert(encode_new_order_message(&got, again, 0) == 193);
  for (size_t i = 0; i < 193; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Short Message: 117 bytes -------------------------------------- */

/* Submission of a new simple (single leg) order to Cboe */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t side;                   /* byte 20 */
  uint8_t order_qty[4];           /* bytes 21 to 24 */
  uint8_t clearing_firm[4];       /* bytes 25 to 28 */
  uint8_t clearing_account[4];    /* bytes 29 to 32 */
  uint8_t price[8];               /* bytes 33 to 40 */
  uint8_t exec_inst;              /* byte 41 */
  uint8_t ord_type;               /* byte 42 */
  uint8_t time_in_force;          /* byte 43 */
  uint8_t min_qty[4];             /* bytes 44 to 47 */
  uint8_t max_floor[4];           /* bytes 48 to 51 */
  uint8_t symbol[8];              /* bytes 52 to 59 */
  uint8_t capacity;               /* byte 60 */
  uint8_t routing_inst[4];        /* bytes 61 to 64 */
  uint8_t account[16];            /* bytes 65 to 80 */
  uint8_t display_indicator;      /* byte 81 */
  PreventMatch prevent_match;     /* bytes 82 to 84 */
  uint8_t open_close;             /* byte 85 */
  uint8_t cmta_number[4];         /* bytes 86 to 89 */
  uint8_t session_eligibility;    /* byte 90 */
  uint8_t attributed_quote;       /* byte 91 */
  uint8_t rout_strategy[6];       /* bytes 92 to 97 */
  uint8_t ex_destination;         /* byte 98 */
  uint8_t auction_id[8];          /* bytes 99 to 106 */
  uint8_t custom_group_id[2];     /* bytes 107 to 108 */
  uint8_t frequent_trader_id[6];  /* bytes 109 to 114 */
  uint8_t scratch_pad[2];         /* bytes 115 to 116 */
} NewOrderShortMessage;

/* any New Order Short Message at all: every byte one the checker chooses */
static void any_new_order_short_message(NewOrderShortMessage *record) {
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
  any_prevent_match(&record->prevent_match);
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = arbitrary(); }
  record->session_eligibility = arbitrary();
  record->attributed_quote = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = arbitrary(); }
  record->ex_destination = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* New Order Short Message to the wire: 117 bytes from at, returning where the next byte goes */
static size_t encode_new_order_short_message(const NewOrderShortMessage *record, uint8_t *wire, size_t at) {
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
  at = encode_prevent_match(&record->prevent_match, wire, at);
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_number[i]; }
  wire[at++] = record->session_eligibility;
  wire[at++] = record->attributed_quote;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->rout_strategy[i]; }
  wire[at++] = record->ex_destination;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->frequent_trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* New Order Short Message off the wire: 117 bytes from at, returning where the next byte lies */
static size_t decode_new_order_short_message(NewOrderShortMessage *record, const uint8_t *wire, size_t at) {
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
  at = decode_prevent_match(&record->prevent_match, wire, at);
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cmta_number[i] = wire[at++]; }
  record->session_eligibility = wire[at++];
  record->attributed_quote = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->rout_strategy[i] = wire[at++]; }
  record->ex_destination = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->frequent_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Short Message is what was written, byte for byte */
static void equal_new_order_short_message(const NewOrderShortMessage *read, const NewOrderShortMessage *written) {
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
  equal_prevent_match(&read->prevent_match, &written->prevent_match);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_number[i] == written->cmta_number[i]); }
  assert(read->session_eligibility == written->session_eligibility);
  assert(read->attributed_quote == written->attributed_quote);
  for (size_t i = 0; i < 6; i++) { assert(read->rout_strategy[i] == written->rout_strategy[i]); }
  assert(read->ex_destination == written->ex_destination);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id[i] == written->custom_group_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->frequent_trader_id[i] == written->frequent_trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* New Order Short Message: written and read back, then read and written back */
static void check_new_order_short_message(void) {
  NewOrderShortMessage sent;
  NewOrderShortMessage got;
  uint8_t wire[117];
  uint8_t again[117];

  any_new_order_short_message(&sent);
  assert(encode_new_order_short_message(&sent, wire, 0) == 117);
  assert(decode_new_order_short_message(&got, wire, 0) == 117);
  equal_new_order_short_message(&got, &sent);

  for (size_t i = 0; i < 117; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_short_message(&got, wire, 0) == 117);
  assert(encode_new_order_short_message(&got, again, 0) == 117);
  for (size_t i = 0; i < 117; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Message: 30 bytes ------------------------------------------ */

/* Request to cancel a single order */
typedef struct {
  uint8_t orig_cl_ord_id[20];  /* bytes 0 to 19 */
  uint8_t clearing_firm[4];    /* bytes 20 to 23 */
  uint8_t routing_firm_id[4];  /* bytes 24 to 27 */
  uint8_t scratch_pad[2];      /* bytes 28 to 29 */
} CancelOrderMessage;

/* any Cancel Order Message at all: every byte one the checker chooses */
static void any_cancel_order_message(CancelOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* Cancel Order Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_message(const CancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* Cancel Order Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_message(CancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Message is what was written, byte for byte */
static void equal_cancel_order_message(const CancelOrderMessage *read, const CancelOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* Cancel Order Message: written and read back, then read and written back */
static void check_cancel_order_message(void) {
  CancelOrderMessage sent;
  CancelOrderMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_cancel_order_message(&sent);
  assert(encode_cancel_order_message(&sent, wire, 0) == 30);
  assert(decode_cancel_order_message(&got, wire, 0) == 30);
  equal_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_message(&got, wire, 0) == 30);
  assert(encode_cancel_order_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Inst: 8 bytes ----------------------------------------------- */

typedef struct {
  uint8_t clearing_firm_filter;    /* byte 0 */
  uint8_t acknowledgement_style;   /* byte 1 */
  uint8_t lockout_instruction;     /* byte 2 */
  uint8_t instrument_type_filter;  /* byte 3 */
  uint8_t gtc_order_filter;        /* byte 4 */
  uint8_t instruction_details[3];  /* bytes 5 to 7 */
} MassCancelInst;

/* any Mass Cancel Inst at all: every byte one the checker chooses */
static void any_mass_cancel_inst(MassCancelInst *record) {
  record->clearing_firm_filter = arbitrary();
  record->acknowledgement_style = arbitrary();
  record->lockout_instruction = arbitrary();
  record->instrument_type_filter = arbitrary();
  record->gtc_order_filter = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->instruction_details[i] = arbitrary(); }
}

/* Mass Cancel Inst to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_inst(const MassCancelInst *record, uint8_t *wire, size_t at) {
  wire[at++] = record->clearing_firm_filter;
  wire[at++] = record->acknowledgement_style;
  wire[at++] = record->lockout_instruction;
  wire[at++] = record->instrument_type_filter;
  wire[at++] = record->gtc_order_filter;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->instruction_details[i]; }

  return at;
}

/* Mass Cancel Inst off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_inst(MassCancelInst *record, const uint8_t *wire, size_t at) {
  record->clearing_firm_filter = wire[at++];
  record->acknowledgement_style = wire[at++];
  record->lockout_instruction = wire[at++];
  record->instrument_type_filter = wire[at++];
  record->gtc_order_filter = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->instruction_details[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Inst is what was written, byte for byte */
static void equal_mass_cancel_inst(const MassCancelInst *read, const MassCancelInst *written) {
  assert(read->clearing_firm_filter == written->clearing_firm_filter);
  assert(read->acknowledgement_style == written->acknowledgement_style);
  assert(read->lockout_instruction == written->lockout_instruction);
  assert(read->instrument_type_filter == written->instrument_type_filter);
  assert(read->gtc_order_filter == written->gtc_order_filter);
  for (size_t i = 0; i < 3; i++) { assert(read->instruction_details[i] == written->instruction_details[i]); }
}

/* Mass Cancel Inst: written and read back, then read and written back */
static void check_mass_cancel_inst(void) {
  MassCancelInst sent;
  MassCancelInst got;
  uint8_t wire[8];
  uint8_t again[8];

  any_mass_cancel_inst(&sent);
  assert(encode_mass_cancel_inst(&sent, wire, 0) == 8);
  assert(decode_mass_cancel_inst(&got, wire, 0) == 8);
  equal_mass_cancel_inst(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_inst(&got, wire, 0) == 8);
  assert(encode_mass_cancel_inst(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Order Message: 52 bytes ------------------------------------- */

/* MassCancelOrderMessage */
typedef struct {
  uint8_t mass_cancel_id[20];       /* bytes 0 to 19 */
  uint8_t clearing_firm[4];         /* bytes 20 to 23 */
  uint8_t routing_firm_id[4];       /* bytes 24 to 27 */
  uint8_t risk_root[6];             /* bytes 28 to 33 */
  MassCancelInst mass_cancel_inst;  /* bytes 34 to 41 */
  uint8_t send_time[8];             /* bytes 42 to 49 */
  uint8_t scratch_pad[2];           /* bytes 50 to 51 */
} MassCancelOrderMessage;

/* any Mass Cancel Order Message at all: every byte one the checker chooses */
static void any_mass_cancel_order_message(MassCancelOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = arbitrary(); }
  any_mass_cancel_inst(&record->mass_cancel_inst);
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* Mass Cancel Order Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_order_message(const MassCancelOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->risk_root[i]; }
  at = encode_mass_cancel_inst(&record->mass_cancel_inst, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* Mass Cancel Order Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_order_message(MassCancelOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = wire[at++]; }
  at = decode_mass_cancel_inst(&record->mass_cancel_inst, wire, at);
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Order Message is what was written, byte for byte */
static void equal_mass_cancel_order_message(const MassCancelOrderMessage *read, const MassCancelOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->risk_root[i] == written->risk_root[i]); }
  equal_mass_cancel_inst(&read->mass_cancel_inst, &written->mass_cancel_inst);
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* Mass Cancel Order Message: written and read back, then read and written back */
static void check_mass_cancel_order_message(void) {
  MassCancelOrderMessage sent;
  MassCancelOrderMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_mass_cancel_order_message(&sent);
  assert(encode_mass_cancel_order_message(&sent, wire, 0) == 52);
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 52);
  equal_mass_cancel_order_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_order_message(&got, wire, 0) == 52);
  assert(encode_mass_cancel_order_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 117 bytes ----------------------------------------- */

/* Request to modify an order */
typedef struct {
  uint8_t cl_ord_id[20];          /* bytes 0 to 19 */
  uint8_t orig_cl_ord_id[20];     /* bytes 20 to 39 */
  uint8_t clearing_firm[4];       /* bytes 40 to 43 */
  uint8_t routing_firm_id[4];     /* bytes 44 to 47 */
  uint8_t order_qty[4];           /* bytes 48 to 51 */
  uint8_t price[8];               /* bytes 52 to 59 */
  uint8_t ord_type;               /* byte 60 */
  uint8_t max_floor[4];           /* bytes 61 to 64 */
  uint8_t stop_px[8];             /* bytes 65 to 72 */
  uint8_t cancel_orig_on_reject;  /* byte 73 */
  uint8_t reserved[41];           /* bytes 74 to 114 */
  uint8_t scratch_pad[2];         /* bytes 115 to 116 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  record->cancel_orig_on_reject = arbitrary();
  for (size_t i = 0; i < 41; i++) { record->reserved[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* Modify Order Message to the wire: 117 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_floor[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  wire[at++] = record->cancel_orig_on_reject;
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->reserved[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* Modify Order Message off the wire: 117 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_floor[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  record->cancel_orig_on_reject = wire[at++];
  for (size_t i = 0; i < 41; i++) { record->reserved[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 4; i++) { assert(read->max_floor[i] == written->max_floor[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  assert(read->cancel_orig_on_reject == written->cancel_orig_on_reject);
  for (size_t i = 0; i < 41; i++) { assert(read->reserved[i] == written->reserved[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[117];
  uint8_t again[117];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 117);
  assert(decode_modify_order_message(&got, wire, 0) == 117);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 117; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 117);
  assert(encode_modify_order_message(&got, again, 0) == 117);
  for (size_t i = 0; i < 117; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reset Risk Message: 39 bytes -------------------------------------------- */

/* Reset or release Firm, Risk Root, or Custom Group ID level lockout conditions resulting from risk profile trips or self-imposed lockouts issued via Cancel Order or Purge Orders messages */
typedef struct {
  uint8_t risk_status_id[16];    /* bytes 0 to 15 */
  uint8_t risk_reset[8];         /* bytes 16 to 23 */
  uint8_t clearing_firm[4];      /* bytes 24 to 27 */
  uint8_t risk_root[6];          /* bytes 28 to 33 */
  uint8_t target_matching_unit;  /* byte 34 */
  uint8_t custom_group_id[2];    /* bytes 35 to 36 */
  uint8_t scratch_pad[2];        /* bytes 37 to 38 */
} ResetRiskMessage;

/* any Reset Risk Message at all: every byte one the checker chooses */
static void any_reset_risk_message(ResetRiskMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = arbitrary(); }
  record->target_matching_unit = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = arbitrary(); }
}

/* Reset Risk Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_reset_risk_message(const ResetRiskMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->risk_status_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->risk_reset[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->risk_root[i]; }
  wire[at++] = record->target_matching_unit;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->scratch_pad[i]; }

  return at;
}

/* Reset Risk Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_reset_risk_message(ResetRiskMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->risk_status_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->risk_reset[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->risk_root[i] = wire[at++]; }
  record->target_matching_unit = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->custom_group_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->scratch_pad[i] = wire[at++]; }

  return at;
}

/* what was read of Reset Risk Message is what was written, byte for byte */
static void equal_reset_risk_message(const ResetRiskMessage *read, const ResetRiskMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->risk_status_id[i] == written->risk_status_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->risk_reset[i] == written->risk_reset[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->risk_root[i] == written->risk_root[i]); }
  assert(read->target_matching_unit == written->target_matching_unit);
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id[i] == written->custom_group_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->scratch_pad[i] == written->scratch_pad[i]); }
}

/* Reset Risk Message: written and read back, then read and written back */
static void check_reset_risk_message(void) {
  ResetRiskMessage sent;
  ResetRiskMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_reset_risk_message(&sent);
  assert(encode_reset_risk_message(&sent, wire, 0) == 39);
  assert(decode_reset_risk_message(&got, wire, 0) == 39);
  equal_reset_risk_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_reset_risk_message(&got, wire, 0) == 39);
  assert(encode_reset_risk_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_firm_message_header();
  check_prevent_match();
  check_new_order_message();
  check_new_order_short_message();
  check_cancel_order_message();
  check_mass_cancel_inst();
  check_mass_cancel_order_message();
  check_modify_order_message();
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
