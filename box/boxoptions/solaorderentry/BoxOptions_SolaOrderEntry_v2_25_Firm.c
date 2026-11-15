// box/boxoptions/solaorderentry/BoxOptions_SolaOrderEntry_v2_25_Firm.c
/*
 * Box Options Market Sola Order Entry
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

/* ---- Incoming Header: 24 bytes ----------------------------------------------- */

/* The header on all incoming participant business messages */
typedef struct {
  uint8_t message_type[2];       /* bytes 0 to 1 */
  uint8_t user_time[6];          /* bytes 2 to 7 */
  uint8_t trader_id[8];          /* bytes 8 to 15 */
  uint8_t user_sequence_i_d[8];  /* bytes 16 to 23 */
} IncomingHeader;

/* any Incoming Header at all: every byte one the checker chooses */
static void any_incoming_header(IncomingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->user_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_i_d[i] = arbitrary(); }
}

/* Incoming Header to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_incoming_header(const IncomingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_i_d[i]; }

  return at;
}

/* Incoming Header off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_incoming_header(IncomingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->user_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_i_d[i] = wire[at++]; }

  return at;
}

/* what was read of Incoming Header is what was written, byte for byte */
static void equal_incoming_header(const IncomingHeader *read, const IncomingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->user_time[i] == written->user_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_i_d[i] == written->user_sequence_i_d[i]); }
}

/* Incoming Header: written and read back, then read and written back */
static void check_incoming_header(void) {
  IncomingHeader sent;
  IncomingHeader got;
  uint8_t wire[24];
  uint8_t again[24];

  any_incoming_header(&sent);
  assert(encode_incoming_header(&sent, wire, 0) == 24);
  assert(decode_incoming_header(&got, wire, 0) == 24);
  equal_incoming_header(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_incoming_header(&got, wire, 0) == 24);
  assert(encode_incoming_header(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Disconnection: 12 bytes -------------------------------------------- */

typedef struct {
  uint8_t user_id[8];     /* bytes 0 to 7 */
  uint8_t session_id[4];  /* bytes 8 to 11 */
} UserDisconnection;

/* any User Disconnection at all: every byte one the checker chooses */
static void any_user_disconnection(UserDisconnection *record) {
  for (size_t i = 0; i < 8; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* User Disconnection to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_user_disconnection(const UserDisconnection *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* User Disconnection off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_user_disconnection(UserDisconnection *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of User Disconnection is what was written, byte for byte */
static void equal_user_disconnection(const UserDisconnection *read, const UserDisconnection *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* User Disconnection: written and read back, then read and written back */
static void check_user_disconnection(void) {
  UserDisconnection sent;
  UserDisconnection got;
  uint8_t wire[12];
  uint8_t again[12];

  any_user_disconnection(&sent);
  assert(encode_user_disconnection(&sent, wire, 0) == 12);
  assert(decode_user_disconnection(&got, wire, 0) == 12);
  equal_user_disconnection(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_user_disconnection(&got, wire, 0) == 12);
  assert(encode_user_disconnection(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Response: 20 bytes -------------------------------------------- */

/* Stated by the guide as having the same number of bytes and format as TH, whose fields are written out here. */
typedef struct {
  uint8_t first_user_sequence_i_d[8];                       /* bytes 0 to 7 */
  uint8_t last_exchange_message_id_sent_to_participant[6];  /* bytes 8 to 13 */
  uint8_t time_local[6];                                    /* bytes 14 to 19 */
} HeartbeatResponse;

/* any Heartbeat Response at all: every byte one the checker chooses */
static void any_heartbeat_response(HeartbeatResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->first_user_sequence_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_local[i] = arbitrary(); }
}

/* Heartbeat Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_response(const HeartbeatResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_user_sequence_i_d[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_exchange_message_id_sent_to_participant[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_local[i]; }

  return at;
}

/* Heartbeat Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_response(HeartbeatResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->first_user_sequence_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_local[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Response is what was written, byte for byte */
static void equal_heartbeat_response(const HeartbeatResponse *read, const HeartbeatResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->first_user_sequence_i_d[i] == written->first_user_sequence_i_d[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_exchange_message_id_sent_to_participant[i] == written->last_exchange_message_id_sent_to_participant[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_local[i] == written->time_local[i]); }
}

/* Heartbeat Response: written and read back, then read and written back */
static void check_heartbeat_response(void) {
  HeartbeatResponse sent;
  HeartbeatResponse got;
  uint8_t wire[20];
  uint8_t again[20];

  any_heartbeat_response(&sent);
  assert(encode_heartbeat_response(&sent, wire, 0) == 20);
  assert(decode_heartbeat_response(&got, wire, 0) == 20);
  equal_heartbeat_response(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_response(&got, wire, 0) == 20);
  assert(encode_heartbeat_response(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Data: 20 bytes ------------------------------------------------- */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t clearing_operation_mode;   /* byte 15 */
  uint8_t clearing_destination[4];   /* bytes 16 to 19 */
} ClearingData;

/* any Clearing Data at all: every byte one the checker chooses */
static void any_clearing_data(ClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  record->clearing_operation_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = arbitrary(); }
}

/* Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_clearing_data(const ClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  wire[at++] = record->clearing_operation_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_destination[i]; }

  return at;
}

/* Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_clearing_data(ClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  record->clearing_operation_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Data is what was written, byte for byte */
static void equal_clearing_data(const ClearingData *read, const ClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  assert(read->clearing_operation_mode == written->clearing_operation_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_destination[i] == written->clearing_destination[i]); }
}

/* Clearing Data: written and read back, then read and written back */
static void check_clearing_data(void) {
  ClearingData sent;
  ClearingData got;
  uint8_t wire[20];
  uint8_t again[20];

  any_clearing_data(&sent);
  assert(encode_clearing_data(&sent, wire, 0) == 20);
  assert(decode_clearing_data(&got, wire, 0) == 20);
  equal_clearing_data(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_data(&got, wire, 0) == 20);
  assert(encode_clearing_data(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Owner Data: 71 bytes ---------------------------------------------------- */

/* The guide states these fields once, as Owner Data, for every message that carries them. */
typedef struct {
  uint8_t client_order_id[20];  /* bytes 0 to 19 */
  uint8_t pound_sign;           /* byte 20 */
  uint8_t memo[50];             /* bytes 21 to 70 */
} OwnerData;

/* any Owner Data at all: every byte one the checker chooses */
static void any_owner_data(OwnerData *record) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->pound_sign = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Owner Data to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_owner_data(const OwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->pound_sign;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Owner Data off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_owner_data(OwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->pound_sign = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Owner Data is what was written, byte for byte */
static void equal_owner_data(const OwnerData *read, const OwnerData *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->pound_sign == written->pound_sign);
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Owner Data: written and read back, then read and written back */
static void check_owner_data(void) {
  OwnerData sent;
  OwnerData got;
  uint8_t wire[71];
  uint8_t again[71];

  any_owner_data(&sent);
  assert(encode_owner_data(&sent, wire, 0) == 71);
  assert(decode_owner_data(&got, wire, 0) == 71);
  equal_owner_data(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_owner_data(&got, wire, 0) == 71);
  assert(encode_owner_data(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulk Quote Data: 203 bytes ---------------------------------------------- */

typedef struct {
  uint8_t group[2];                       /* bytes 0 to 1 */
  ClearingData clearing_data;             /* bytes 2 to 21 */
  OwnerData owner_data;                   /* bytes 22 to 92 */
  uint8_t reserved_2[2];                  /* bytes 93 to 94 */
  uint8_t reserved_8[8];                  /* bytes 95 to 102 */
  uint8_t second_reserved_2[2];           /* bytes 103 to 104 */
  uint8_t calculation_time_interval[8];   /* bytes 105 to 112 */
  uint8_t maximum_total_volume[8];        /* bytes 113 to 120 */
  uint8_t maximum_total_value[8];         /* bytes 121 to 128 */
  uint8_t maximum_delta_volume[8];        /* bytes 129 to 136 */
  uint8_t maximum_delta_value[8];         /* bytes 137 to 144 */
  uint8_t percent_of_quote[8];            /* bytes 145 to 152 */
  uint8_t post_trading_instructions[50];  /* bytes 153 to 202 */
} BulkQuoteData;

/* any Bulk Quote Data at all: every byte one the checker chooses */
static void any_bulk_quote_data(BulkQuoteData *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculation_time_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_delta_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_delta_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->percent_of_quote[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = arbitrary(); }
}

/* Bulk Quote Data to the wire: 203 bytes from at, returning where the next byte goes */
static size_t encode_bulk_quote_data(const BulkQuoteData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second_reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculation_time_interval[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_delta_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_delta_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->percent_of_quote[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->post_trading_instructions[i]; }

  return at;
}

/* Bulk Quote Data off the wire: 203 bytes from at, returning where the next byte lies */
static size_t decode_bulk_quote_data(BulkQuoteData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculation_time_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_delta_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_delta_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->percent_of_quote[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = wire[at++]; }

  return at;
}

/* what was read of Bulk Quote Data is what was written, byte for byte */
static void equal_bulk_quote_data(const BulkQuoteData *read, const BulkQuoteData *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second_reserved_2[i] == written->second_reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculation_time_interval[i] == written->calculation_time_interval[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_total_volume[i] == written->maximum_total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_total_value[i] == written->maximum_total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_delta_volume[i] == written->maximum_delta_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_delta_value[i] == written->maximum_delta_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->percent_of_quote[i] == written->percent_of_quote[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->post_trading_instructions[i] == written->post_trading_instructions[i]); }
}

/* Bulk Quote Data: written and read back, then read and written back */
static void check_bulk_quote_data(void) {
  BulkQuoteData sent;
  BulkQuoteData got;
  uint8_t wire[203];
  uint8_t again[203];

  any_bulk_quote_data(&sent);
  assert(encode_bulk_quote_data(&sent, wire, 0) == 203);
  assert(decode_bulk_quote_data(&got, wire, 0) == 203);
  equal_bulk_quote_data(&got, &sent);

  for (size_t i = 0; i < 203; i++) { wire[i] = arbitrary(); }
  assert(decode_bulk_quote_data(&got, wire, 0) == 203);
  assert(encode_bulk_quote_data(&got, again, 0) == 203);
  for (size_t i = 0; i < 203; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Cancellation: 11 bytes ------------------------------------------- */

typedef struct {
  uint8_t group[2];              /* bytes 0 to 1 */
  uint8_t type_of_cancellation;  /* byte 2 */
  uint8_t mm_cat_user_time[8];   /* bytes 3 to 10 */
} GlobalCancellation;

/* any Global Cancellation at all: every byte one the checker chooses */
static void any_global_cancellation(GlobalCancellation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->type_of_cancellation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->mm_cat_user_time[i] = arbitrary(); }
}

/* Global Cancellation to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_global_cancellation(const GlobalCancellation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->type_of_cancellation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mm_cat_user_time[i]; }

  return at;
}

/* Global Cancellation off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_global_cancellation(GlobalCancellation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->type_of_cancellation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->mm_cat_user_time[i] = wire[at++]; }

  return at;
}

/* what was read of Global Cancellation is what was written, byte for byte */
static void equal_global_cancellation(const GlobalCancellation *read, const GlobalCancellation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->type_of_cancellation == written->type_of_cancellation);
  for (size_t i = 0; i < 8; i++) { assert(read->mm_cat_user_time[i] == written->mm_cat_user_time[i]); }
}

/* Global Cancellation: written and read back, then read and written back */
static void check_global_cancellation(void) {
  GlobalCancellation sent;
  GlobalCancellation got;
  uint8_t wire[11];
  uint8_t again[11];

  any_global_cancellation(&sent);
  assert(encode_global_cancellation(&sent, wire, 0) == 11);
  assert(decode_global_cancellation(&got, wire, 0) == 11);
  equal_global_cancellation(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_global_cancellation(&got, wire, 0) == 11);
  assert(encode_global_cancellation(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Global Cancellation: 23 bytes -------------------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t type_of_cancellation;    /* byte 6 */
  uint8_t account_type_filter[8];  /* bytes 7 to 14 */
  uint8_t mm_cat_user_time[8];     /* bytes 15 to 22 */
} UserGlobalCancellation;

/* any User Global Cancellation at all: every byte one the checker chooses */
static void any_user_global_cancellation(UserGlobalCancellation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  record->type_of_cancellation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->account_type_filter[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mm_cat_user_time[i] = arbitrary(); }
}

/* User Global Cancellation to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_user_global_cancellation(const UserGlobalCancellation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  wire[at++] = record->type_of_cancellation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->account_type_filter[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mm_cat_user_time[i]; }

  return at;
}

/* User Global Cancellation off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_user_global_cancellation(UserGlobalCancellation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  record->type_of_cancellation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->account_type_filter[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mm_cat_user_time[i] = wire[at++]; }

  return at;
}

/* what was read of User Global Cancellation is what was written, byte for byte */
static void equal_user_global_cancellation(const UserGlobalCancellation *read, const UserGlobalCancellation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  assert(read->type_of_cancellation == written->type_of_cancellation);
  for (size_t i = 0; i < 8; i++) { assert(read->account_type_filter[i] == written->account_type_filter[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mm_cat_user_time[i] == written->mm_cat_user_time[i]); }
}

/* User Global Cancellation: written and read back, then read and written back */
static void check_user_global_cancellation(void) {
  UserGlobalCancellation sent;
  UserGlobalCancellation got;
  uint8_t wire[23];
  uint8_t again[23];

  any_user_global_cancellation(&sent);
  assert(encode_user_global_cancellation(&sent, wire, 0) == 23);
  assert(decode_user_global_cancellation(&got, wire, 0) == 23);
  equal_user_global_cancellation(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_user_global_cancellation(&got, wire, 0) == 23);
  assert(encode_user_global_cancellation(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Directed Routed Order Rejection And Quote: 44 bytes --------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t trader_id[8];            /* bytes 6 to 13 */
  uint8_t order_id[8];             /* bytes 14 to 21 */
  uint8_t rejection_code[4];       /* bytes 22 to 25 */
  uint8_t quote_quantity[8];       /* bytes 26 to 33 */
  uint8_t quote_price[10];         /* bytes 34 to 43 */
} DirectedRoutedOrderRejectionAndQuote;

/* any Directed Routed Order Rejection And Quote at all: every byte one the checker chooses */
static void any_directed_routed_order_rejection_and_quote(DirectedRoutedOrderRejectionAndQuote *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rejection_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quote_price[i] = arbitrary(); }
}

/* Directed Routed Order Rejection And Quote to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_directed_routed_order_rejection_and_quote(const DirectedRoutedOrderRejectionAndQuote *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rejection_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quote_price[i]; }

  return at;
}

/* Directed Routed Order Rejection And Quote off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_directed_routed_order_rejection_and_quote(DirectedRoutedOrderRejectionAndQuote *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rejection_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quote_price[i] = wire[at++]; }

  return at;
}

/* what was read of Directed Routed Order Rejection And Quote is what was written, byte for byte */
static void equal_directed_routed_order_rejection_and_quote(const DirectedRoutedOrderRejectionAndQuote *read, const DirectedRoutedOrderRejectionAndQuote *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rejection_code[i] == written->rejection_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_quantity[i] == written->quote_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quote_price[i] == written->quote_price[i]); }
}

/* Directed Routed Order Rejection And Quote: written and read back, then read and written back */
static void check_directed_routed_order_rejection_and_quote(void) {
  DirectedRoutedOrderRejectionAndQuote sent;
  DirectedRoutedOrderRejectionAndQuote got;
  uint8_t wire[44];
  uint8_t again[44];

  any_directed_routed_order_rejection_and_quote(&sent);
  assert(encode_directed_routed_order_rejection_and_quote(&sent, wire, 0) == 44);
  assert(decode_directed_routed_order_rejection_and_quote(&got, wire, 0) == 44);
  equal_directed_routed_order_rejection_and_quote(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_directed_routed_order_rejection_and_quote(&got, wire, 0) == 44);
  assert(encode_directed_routed_order_rejection_and_quote(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buying Clearing Data: 20 bytes ------------------------------------------ */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t clearing_operation_mode;   /* byte 15 */
  uint8_t clearing_destination[4];   /* bytes 16 to 19 */
} BuyingClearingData;

/* any Buying Clearing Data at all: every byte one the checker chooses */
static void any_buying_clearing_data(BuyingClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  record->clearing_operation_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = arbitrary(); }
}

/* Buying Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_buying_clearing_data(const BuyingClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  wire[at++] = record->clearing_operation_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_destination[i]; }

  return at;
}

/* Buying Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_buying_clearing_data(BuyingClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  record->clearing_operation_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = wire[at++]; }

  return at;
}

/* what was read of Buying Clearing Data is what was written, byte for byte */
static void equal_buying_clearing_data(const BuyingClearingData *read, const BuyingClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  assert(read->clearing_operation_mode == written->clearing_operation_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_destination[i] == written->clearing_destination[i]); }
}

/* Buying Clearing Data: written and read back, then read and written back */
static void check_buying_clearing_data(void) {
  BuyingClearingData sent;
  BuyingClearingData got;
  uint8_t wire[20];
  uint8_t again[20];

  any_buying_clearing_data(&sent);
  assert(encode_buying_clearing_data(&sent, wire, 0) == 20);
  assert(decode_buying_clearing_data(&got, wire, 0) == 20);
  equal_buying_clearing_data(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_buying_clearing_data(&got, wire, 0) == 20);
  assert(encode_buying_clearing_data(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Selling Clearing Data: 20 bytes ----------------------------------------- */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t clearing_operation_mode;   /* byte 15 */
  uint8_t clearing_destination[4];   /* bytes 16 to 19 */
} SellingClearingData;

/* any Selling Clearing Data at all: every byte one the checker chooses */
static void any_selling_clearing_data(SellingClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  record->clearing_operation_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = arbitrary(); }
}

/* Selling Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_selling_clearing_data(const SellingClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  wire[at++] = record->clearing_operation_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_destination[i]; }

  return at;
}

/* Selling Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_selling_clearing_data(SellingClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  record->clearing_operation_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = wire[at++]; }

  return at;
}

/* what was read of Selling Clearing Data is what was written, byte for byte */
static void equal_selling_clearing_data(const SellingClearingData *read, const SellingClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  assert(read->clearing_operation_mode == written->clearing_operation_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_destination[i] == written->clearing_destination[i]); }
}

/* Selling Clearing Data: written and read back, then read and written back */
static void check_selling_clearing_data(void) {
  SellingClearingData sent;
  SellingClearingData got;
  uint8_t wire[20];
  uint8_t again[20];

  any_selling_clearing_data(&sent);
  assert(encode_selling_clearing_data(&sent, wire, 0) == 20);
  assert(decode_selling_clearing_data(&got, wire, 0) == 20);
  equal_selling_clearing_data(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_selling_clearing_data(&got, wire, 0) == 20);
  assert(encode_selling_clearing_data(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buying Owner Data: 71 bytes --------------------------------------------- */

/* The guide states these fields once, as Owner Data, for every message that carries them. */
typedef struct {
  uint8_t client_order_id[20];  /* bytes 0 to 19 */
  uint8_t pound_sign;           /* byte 20 */
  uint8_t memo[50];             /* bytes 21 to 70 */
} BuyingOwnerData;

/* any Buying Owner Data at all: every byte one the checker chooses */
static void any_buying_owner_data(BuyingOwnerData *record) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->pound_sign = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Buying Owner Data to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_buying_owner_data(const BuyingOwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->pound_sign;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Buying Owner Data off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_buying_owner_data(BuyingOwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->pound_sign = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Buying Owner Data is what was written, byte for byte */
static void equal_buying_owner_data(const BuyingOwnerData *read, const BuyingOwnerData *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->pound_sign == written->pound_sign);
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Buying Owner Data: written and read back, then read and written back */
static void check_buying_owner_data(void) {
  BuyingOwnerData sent;
  BuyingOwnerData got;
  uint8_t wire[71];
  uint8_t again[71];

  any_buying_owner_data(&sent);
  assert(encode_buying_owner_data(&sent, wire, 0) == 71);
  assert(decode_buying_owner_data(&got, wire, 0) == 71);
  equal_buying_owner_data(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_buying_owner_data(&got, wire, 0) == 71);
  assert(encode_buying_owner_data(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Selling Owner Data: 71 bytes -------------------------------------------- */

/* The guide states these fields once, as Owner Data, for every message that carries them. */
typedef struct {
  uint8_t client_order_id[20];  /* bytes 0 to 19 */
  uint8_t pound_sign;           /* byte 20 */
  uint8_t memo[50];             /* bytes 21 to 70 */
} SellingOwnerData;

/* any Selling Owner Data at all: every byte one the checker chooses */
static void any_selling_owner_data(SellingOwnerData *record) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->pound_sign = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Selling Owner Data to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_selling_owner_data(const SellingOwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->pound_sign;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Selling Owner Data off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_selling_owner_data(SellingOwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->pound_sign = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Selling Owner Data is what was written, byte for byte */
static void equal_selling_owner_data(const SellingOwnerData *read, const SellingOwnerData *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->pound_sign == written->pound_sign);
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Selling Owner Data: written and read back, then read and written back */
static void check_selling_owner_data(void) {
  SellingOwnerData sent;
  SellingOwnerData got;
  uint8_t wire[71];
  uint8_t again[71];

  any_selling_owner_data(&sent);
  assert(encode_selling_owner_data(&sent, wire, 0) == 71);
  assert(decode_selling_owner_data(&got, wire, 0) == 71);
  equal_selling_owner_data(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_selling_owner_data(&got, wire, 0) == 71);
  assert(encode_selling_owner_data(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Entry: 364 bytes ------------------------------------------------ */

typedef struct {
  uint8_t group[2];                              /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                /* bytes 2 to 5 */
  uint8_t verb_side;                             /* byte 6 */
  uint8_t quantity[8];                           /* bytes 7 to 14 */
  uint8_t price[10];                             /* bytes 15 to 24 */
  BuyingClearingData buying_clearing_data;       /* bytes 25 to 44 */
  SellingClearingData selling_clearing_data;     /* bytes 45 to 64 */
  BuyingOwnerData buying_owner_data;             /* bytes 65 to 135 */
  SellingOwnerData selling_owner_data;           /* bytes 136 to 206 */
  uint8_t iml_handling;                          /* byte 207 */
  uint8_t special_price_term;                    /* byte 208 */
  uint8_t additional_price[10];                  /* bytes 209 to 218 */
  uint8_t quantity_term;                         /* byte 219 */
  uint8_t additional_quantity[8];                /* bytes 220 to 227 */
  uint8_t buying_post_trading_instruction[50];   /* bytes 228 to 277 */
  uint8_t selling_post_trading_instruction[50];  /* bytes 278 to 327 */
  uint8_t buying_additional_client_memo[16];     /* bytes 328 to 343 */
  uint8_t selling_additional_client_memo[16];    /* bytes 344 to 359 */
  uint8_t reserved_4[4];                         /* bytes 360 to 363 */
} AuctionEntry;

/* any Auction Entry at all: every byte one the checker chooses */
static void any_auction_entry(AuctionEntry *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  any_buying_clearing_data(&record->buying_clearing_data);
  any_selling_clearing_data(&record->selling_clearing_data);
  any_buying_owner_data(&record->buying_owner_data);
  any_selling_owner_data(&record->selling_owner_data);
  record->iml_handling = arbitrary();
  record->special_price_term = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = arbitrary(); }
  record->quantity_term = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->buying_post_trading_instruction[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->selling_post_trading_instruction[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->buying_additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->selling_additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Auction Entry to the wire: 364 bytes from at, returning where the next byte goes */
static size_t encode_auction_entry(const AuctionEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  at = encode_buying_clearing_data(&record->buying_clearing_data, wire, at);
  at = encode_selling_clearing_data(&record->selling_clearing_data, wire, at);
  at = encode_buying_owner_data(&record->buying_owner_data, wire, at);
  at = encode_selling_owner_data(&record->selling_owner_data, wire, at);
  wire[at++] = record->iml_handling;
  wire[at++] = record->special_price_term;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->additional_price[i]; }
  wire[at++] = record->quantity_term;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_quantity[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->buying_post_trading_instruction[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->selling_post_trading_instruction[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->buying_additional_client_memo[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->selling_additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Auction Entry off the wire: 364 bytes from at, returning where the next byte lies */
static size_t decode_auction_entry(AuctionEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  at = decode_buying_clearing_data(&record->buying_clearing_data, wire, at);
  at = decode_selling_clearing_data(&record->selling_clearing_data, wire, at);
  at = decode_buying_owner_data(&record->buying_owner_data, wire, at);
  at = decode_selling_owner_data(&record->selling_owner_data, wire, at);
  record->iml_handling = wire[at++];
  record->special_price_term = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = wire[at++]; }
  record->quantity_term = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->buying_post_trading_instruction[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->selling_post_trading_instruction[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->buying_additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->selling_additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Entry is what was written, byte for byte */
static void equal_auction_entry(const AuctionEntry *read, const AuctionEntry *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  equal_buying_clearing_data(&read->buying_clearing_data, &written->buying_clearing_data);
  equal_selling_clearing_data(&read->selling_clearing_data, &written->selling_clearing_data);
  equal_buying_owner_data(&read->buying_owner_data, &written->buying_owner_data);
  equal_selling_owner_data(&read->selling_owner_data, &written->selling_owner_data);
  assert(read->iml_handling == written->iml_handling);
  assert(read->special_price_term == written->special_price_term);
  for (size_t i = 0; i < 10; i++) { assert(read->additional_price[i] == written->additional_price[i]); }
  assert(read->quantity_term == written->quantity_term);
  for (size_t i = 0; i < 8; i++) { assert(read->additional_quantity[i] == written->additional_quantity[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->buying_post_trading_instruction[i] == written->buying_post_trading_instruction[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->selling_post_trading_instruction[i] == written->selling_post_trading_instruction[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->buying_additional_client_memo[i] == written->buying_additional_client_memo[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->selling_additional_client_memo[i] == written->selling_additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Auction Entry: written and read back, then read and written back */
static void check_auction_entry(void) {
  AuctionEntry sent;
  AuctionEntry got;
  uint8_t wire[364];
  uint8_t again[364];

  any_auction_entry(&sent);
  assert(encode_auction_entry(&sent, wire, 0) == 364);
  assert(decode_auction_entry(&got, wire, 0) == 364);
  equal_auction_entry(&got, &sent);

  for (size_t i = 0; i < 364; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_entry(&got, wire, 0) == 364);
  assert(encode_auction_entry(&got, again, 0) == 364);
  for (size_t i = 0; i < 364; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Data Dealer: 20 bytes ------------------------------------------ */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t clearing_operation_mode;   /* byte 15 */
  uint8_t clearing_destination[4];   /* bytes 16 to 19 */
} ClearingDataDealer;

/* any Clearing Data Dealer at all: every byte one the checker chooses */
static void any_clearing_data_dealer(ClearingDataDealer *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  record->clearing_operation_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = arbitrary(); }
}

/* Clearing Data Dealer to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_clearing_data_dealer(const ClearingDataDealer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  wire[at++] = record->clearing_operation_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_destination[i]; }

  return at;
}

/* Clearing Data Dealer off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_clearing_data_dealer(ClearingDataDealer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  record->clearing_operation_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Data Dealer is what was written, byte for byte */
static void equal_clearing_data_dealer(const ClearingDataDealer *read, const ClearingDataDealer *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  assert(read->clearing_operation_mode == written->clearing_operation_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_destination[i] == written->clearing_destination[i]); }
}

/* Clearing Data Dealer: written and read back, then read and written back */
static void check_clearing_data_dealer(void) {
  ClearingDataDealer sent;
  ClearingDataDealer got;
  uint8_t wire[20];
  uint8_t again[20];

  any_clearing_data_dealer(&sent);
  assert(encode_clearing_data_dealer(&sent, wire, 0) == 20);
  assert(decode_clearing_data_dealer(&got, wire, 0) == 20);
  equal_clearing_data_dealer(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_data_dealer(&got, wire, 0) == 20);
  assert(encode_clearing_data_dealer(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Owner Data Dealer: 71 bytes --------------------------------------------- */

/* The guide states these fields once, as Owner Data, for every message that carries them. */
typedef struct {
  uint8_t client_order_id[20];  /* bytes 0 to 19 */
  uint8_t pound_sign;           /* byte 20 */
  uint8_t memo[50];             /* bytes 21 to 70 */
} OwnerDataDealer;

/* any Owner Data Dealer at all: every byte one the checker chooses */
static void any_owner_data_dealer(OwnerDataDealer *record) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->pound_sign = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Owner Data Dealer to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_owner_data_dealer(const OwnerDataDealer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->pound_sign;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Owner Data Dealer off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_owner_data_dealer(OwnerDataDealer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->pound_sign = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Owner Data Dealer is what was written, byte for byte */
static void equal_owner_data_dealer(const OwnerDataDealer *read, const OwnerDataDealer *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->pound_sign == written->pound_sign);
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Owner Data Dealer: written and read back, then read and written back */
static void check_owner_data_dealer(void) {
  OwnerDataDealer sent;
  OwnerDataDealer got;
  uint8_t wire[71];
  uint8_t again[71];

  any_owner_data_dealer(&sent);
  assert(encode_owner_data_dealer(&sent, wire, 0) == 71);
  assert(decode_owner_data_dealer(&got, wire, 0) == 71);
  equal_owner_data_dealer(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_owner_data_dealer(&got, wire, 0) == 71);
  assert(encode_owner_data_dealer(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Directed Order Acceptation: 200 bytes ----------------------------------- */

typedef struct {
  uint8_t group[2];                         /* bytes 0 to 1 */
  uint8_t instrument_optional[4];           /* bytes 2 to 5 */
  uint8_t referenced_order_id[8];           /* bytes 6 to 13 */
  uint8_t auction_starting_price[10];       /* bytes 14 to 23 */
  ClearingDataDealer clearing_data_dealer;  /* bytes 24 to 43 */
  OwnerDataDealer owner_data_dealer;        /* bytes 44 to 114 */
  uint8_t additional_price[10];             /* bytes 115 to 124 */
  uint8_t quantity_term;                    /* byte 125 */
  uint8_t post_trading_instruction[50];     /* bytes 126 to 175 */
  uint8_t additional_quantity[8];           /* bytes 176 to 183 */
  uint8_t additional_client_memo[16];       /* bytes 184 to 199 */
} DirectedOrderAcceptation;

/* any Directed Order Acceptation at all: every byte one the checker chooses */
static void any_directed_order_acceptation(DirectedOrderAcceptation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->auction_starting_price[i] = arbitrary(); }
  any_clearing_data_dealer(&record->clearing_data_dealer);
  any_owner_data_dealer(&record->owner_data_dealer);
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = arbitrary(); }
  record->quantity_term = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->post_trading_instruction[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Directed Order Acceptation to the wire: 200 bytes from at, returning where the next byte goes */
static size_t encode_directed_order_acceptation(const DirectedOrderAcceptation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->referenced_order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->auction_starting_price[i]; }
  at = encode_clearing_data_dealer(&record->clearing_data_dealer, wire, at);
  at = encode_owner_data_dealer(&record->owner_data_dealer, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->additional_price[i]; }
  wire[at++] = record->quantity_term;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->post_trading_instruction[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_quantity[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Directed Order Acceptation off the wire: 200 bytes from at, returning where the next byte lies */
static size_t decode_directed_order_acceptation(DirectedOrderAcceptation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->auction_starting_price[i] = wire[at++]; }
  at = decode_clearing_data_dealer(&record->clearing_data_dealer, wire, at);
  at = decode_owner_data_dealer(&record->owner_data_dealer, wire, at);
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = wire[at++]; }
  record->quantity_term = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->post_trading_instruction[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Directed Order Acceptation is what was written, byte for byte */
static void equal_directed_order_acceptation(const DirectedOrderAcceptation *read, const DirectedOrderAcceptation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->referenced_order_id[i] == written->referenced_order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->auction_starting_price[i] == written->auction_starting_price[i]); }
  equal_clearing_data_dealer(&read->clearing_data_dealer, &written->clearing_data_dealer);
  equal_owner_data_dealer(&read->owner_data_dealer, &written->owner_data_dealer);
  for (size_t i = 0; i < 10; i++) { assert(read->additional_price[i] == written->additional_price[i]); }
  assert(read->quantity_term == written->quantity_term);
  for (size_t i = 0; i < 50; i++) { assert(read->post_trading_instruction[i] == written->post_trading_instruction[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->additional_quantity[i] == written->additional_quantity[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Directed Order Acceptation: written and read back, then read and written back */
static void check_directed_order_acceptation(void) {
  DirectedOrderAcceptation sent;
  DirectedOrderAcceptation got;
  uint8_t wire[200];
  uint8_t again[200];

  any_directed_order_acceptation(&sent);
  assert(encode_directed_order_acceptation(&sent, wire, 0) == 200);
  assert(decode_directed_order_acceptation(&got, wire, 0) == 200);
  equal_directed_order_acceptation(&got, &sent);

  for (size_t i = 0; i < 200; i++) { wire[i] = arbitrary(); }
  assert(decode_directed_order_acceptation(&got, wire, 0) == 200);
  assert(encode_directed_order_acceptation(&got, again, 0) == 200);
  for (size_t i = 0; i < 200; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Entry: 221 bytes -------------------------------------------------- */

typedef struct {
  uint8_t group[2];                       /* bytes 0 to 1 */
  uint8_t instrument_optional[4];         /* bytes 2 to 5 */
  uint8_t price_type;                     /* byte 6 */
  uint8_t verb_side;                      /* byte 7 */
  uint8_t quantity[8];                    /* bytes 8 to 15 */
  uint8_t price[10];                      /* bytes 16 to 25 */
  uint8_t special_price_term;             /* byte 26 */
  uint8_t reserved_10[10];                /* bytes 27 to 36 */
  uint8_t quantity_term;                  /* byte 37 */
  uint8_t additional_quantity[8];         /* bytes 38 to 45 */
  uint8_t duration_type;                  /* byte 46 */
  uint8_t gtd_date[8];                    /* bytes 47 to 54 */
  uint8_t executing_participant[4];       /* bytes 55 to 58 */
  uint8_t iml_handling;                   /* byte 59 */
  ClearingData clearing_data;             /* bytes 60 to 79 */
  OwnerData owner_data;                   /* bytes 80 to 150 */
  uint8_t post_trading_instructions[50];  /* bytes 151 to 200 */
  uint8_t additional_client_memo[16];     /* bytes 201 to 216 */
  uint8_t reserved_4[4];                  /* bytes 217 to 220 */
} OrderEntry;

/* any Order Entry at all: every byte one the checker chooses */
static void any_order_entry(OrderEntry *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->special_price_term = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
  record->quantity_term = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = arbitrary(); }
  record->duration_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executing_participant[i] = arbitrary(); }
  record->iml_handling = arbitrary();
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Entry to the wire: 221 bytes from at, returning where the next byte goes */
static size_t encode_order_entry(const OrderEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->special_price_term;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }
  wire[at++] = record->quantity_term;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_quantity[i]; }
  wire[at++] = record->duration_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gtd_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_participant[i]; }
  wire[at++] = record->iml_handling;
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->post_trading_instructions[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Entry off the wire: 221 bytes from at, returning where the next byte lies */
static size_t decode_order_entry(OrderEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->special_price_term = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }
  record->quantity_term = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = wire[at++]; }
  record->duration_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executing_participant[i] = wire[at++]; }
  record->iml_handling = wire[at++];
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Entry is what was written, byte for byte */
static void equal_order_entry(const OrderEntry *read, const OrderEntry *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  assert(read->price_type == written->price_type);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->special_price_term == written->special_price_term);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
  assert(read->quantity_term == written->quantity_term);
  for (size_t i = 0; i < 8; i++) { assert(read->additional_quantity[i] == written->additional_quantity[i]); }
  assert(read->duration_type == written->duration_type);
  for (size_t i = 0; i < 8; i++) { assert(read->gtd_date[i] == written->gtd_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executing_participant[i] == written->executing_participant[i]); }
  assert(read->iml_handling == written->iml_handling);
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 50; i++) { assert(read->post_trading_instructions[i] == written->post_trading_instructions[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Entry: written and read back, then read and written back */
static void check_order_entry(void) {
  OrderEntry sent;
  OrderEntry got;
  uint8_t wire[221];
  uint8_t again[221];

  any_order_entry(&sent);
  assert(encode_order_entry(&sent, wire, 0) == 221);
  assert(decode_order_entry(&got, wire, 0) == 221);
  equal_order_entry(&got, &sent);

  for (size_t i = 0; i < 221; i++) { wire[i] = arbitrary(); }
  assert(decode_order_entry(&got, wire, 0) == 221);
  assert(encode_order_entry(&got, again, 0) == 221);
  for (size_t i = 0; i < 221; i++) { assert(again[i] == wire[i]); }
}

/* ---- Improvement Order Entry: 210 bytes -------------------------------------- */

typedef struct {
  uint8_t group[2];                       /* bytes 0 to 1 */
  uint8_t instrument_optional[4];         /* bytes 2 to 5 */
  uint8_t verb_side;                      /* byte 6 */
  uint8_t quantity_sign;                  /* byte 7 */
  uint8_t quantity[8];                    /* bytes 8 to 15 */
  uint8_t price[10];                      /* bytes 16 to 25 */
  uint8_t auction_i_d_optional[6];        /* bytes 26 to 31 */
  uint8_t reserved_17[17];                /* bytes 32 to 48 */
  ClearingData clearing_data;             /* bytes 49 to 68 */
  OwnerData owner_data;                   /* bytes 69 to 139 */
  uint8_t post_trading_instructions[50];  /* bytes 140 to 189 */
  uint8_t additional_client_memo[16];     /* bytes 190 to 205 */
  uint8_t reserved_4[4];                  /* bytes 206 to 209 */
} ImprovementOrderEntry;

/* any Improvement Order Entry at all: every byte one the checker chooses */
static void any_improvement_order_entry(ImprovementOrderEntry *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  record->verb_side = arbitrary();
  record->quantity_sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 17; i++) { record->reserved_17[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Improvement Order Entry to the wire: 210 bytes from at, returning where the next byte goes */
static size_t encode_improvement_order_entry(const ImprovementOrderEntry *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  wire[at++] = record->verb_side;
  wire[at++] = record->quantity_sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->reserved_17[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->post_trading_instructions[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Improvement Order Entry off the wire: 210 bytes from at, returning where the next byte lies */
static size_t decode_improvement_order_entry(ImprovementOrderEntry *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  record->verb_side = wire[at++];
  record->quantity_sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 17; i++) { record->reserved_17[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instructions[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Improvement Order Entry is what was written, byte for byte */
static void equal_improvement_order_entry(const ImprovementOrderEntry *read, const ImprovementOrderEntry *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  assert(read->verb_side == written->verb_side);
  assert(read->quantity_sign == written->quantity_sign);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 17; i++) { assert(read->reserved_17[i] == written->reserved_17[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 50; i++) { assert(read->post_trading_instructions[i] == written->post_trading_instructions[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Improvement Order Entry: written and read back, then read and written back */
static void check_improvement_order_entry(void) {
  ImprovementOrderEntry sent;
  ImprovementOrderEntry got;
  uint8_t wire[210];
  uint8_t again[210];

  any_improvement_order_entry(&sent);
  assert(encode_improvement_order_entry(&sent, wire, 0) == 210);
  assert(decode_improvement_order_entry(&got, wire, 0) == 210);
  equal_improvement_order_entry(&got, &sent);

  for (size_t i = 0; i < 210; i++) { wire[i] = arbitrary(); }
  assert(decode_improvement_order_entry(&got, wire, 0) == 210);
  assert(encode_improvement_order_entry(&got, again, 0) == 210);
  for (size_t i = 0; i < 210; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modification: 230 bytes ------------------------------------------- */

typedef struct {
  uint8_t group[2];                      /* bytes 0 to 1 */
  uint8_t instrument_optional[4];        /* bytes 2 to 5 */
  uint8_t price_type;                    /* byte 6 */
  uint8_t verb_side;                     /* byte 7 */
  uint8_t quantity_sign;                 /* byte 8 */
  uint8_t quantity[8];                   /* bytes 9 to 16 */
  uint8_t price[10];                     /* bytes 17 to 26 */
  uint8_t special_price_term;            /* byte 27 */
  uint8_t reserved_10[10];               /* bytes 28 to 37 */
  uint8_t reserved_1;                    /* byte 38 */
  uint8_t reserved_8[8];                 /* bytes 39 to 46 */
  uint8_t duration_type;                 /* byte 47 */
  uint8_t gtd_date[8];                   /* bytes 48 to 55 */
  uint8_t firm_id[4];                    /* bytes 56 to 59 */
  uint8_t iml_handling;                  /* byte 60 */
  uint8_t modified_order_id[8];          /* bytes 61 to 68 */
  ClearingData clearing_data;            /* bytes 69 to 88 */
  OwnerData owner_data;                  /* bytes 89 to 159 */
  uint8_t post_trading_instruction[50];  /* bytes 160 to 209 */
  uint8_t additional_client_memo[16];    /* bytes 210 to 225 */
  uint8_t reserved_4[4];                 /* bytes 226 to 229 */
} OrderModification;

/* any Order Modification at all: every byte one the checker chooses */
static void any_order_modification(OrderModification *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->verb_side = arbitrary();
  record->quantity_sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->special_price_term = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  record->duration_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = arbitrary(); }
  record->iml_handling = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->modified_order_id[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instruction[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Modification to the wire: 230 bytes from at, returning where the next byte goes */
static size_t encode_order_modification(const OrderModification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->verb_side;
  wire[at++] = record->quantity_sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->special_price_term;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  wire[at++] = record->duration_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gtd_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->firm_id[i]; }
  wire[at++] = record->iml_handling;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->modified_order_id[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->post_trading_instruction[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Modification off the wire: 230 bytes from at, returning where the next byte lies */
static size_t decode_order_modification(OrderModification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->verb_side = wire[at++];
  record->quantity_sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->special_price_term = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  record->duration_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->firm_id[i] = wire[at++]; }
  record->iml_handling = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->modified_order_id[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 50; i++) { record->post_trading_instruction[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modification is what was written, byte for byte */
static void equal_order_modification(const OrderModification *read, const OrderModification *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  assert(read->price_type == written->price_type);
  assert(read->verb_side == written->verb_side);
  assert(read->quantity_sign == written->quantity_sign);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->special_price_term == written->special_price_term);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  assert(read->duration_type == written->duration_type);
  for (size_t i = 0; i < 8; i++) { assert(read->gtd_date[i] == written->gtd_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  assert(read->iml_handling == written->iml_handling);
  for (size_t i = 0; i < 8; i++) { assert(read->modified_order_id[i] == written->modified_order_id[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 50; i++) { assert(read->post_trading_instruction[i] == written->post_trading_instruction[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Modification: written and read back, then read and written back */
static void check_order_modification(void) {
  OrderModification sent;
  OrderModification got;
  uint8_t wire[230];
  uint8_t again[230];

  any_order_modification(&sent);
  assert(encode_order_modification(&sent, wire, 0) == 230);
  assert(decode_order_modification(&got, wire, 0) == 230);
  equal_order_modification(&got, &sent);

  for (size_t i = 0; i < 230; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modification(&got, wire, 0) == 230);
  assert(encode_order_modification(&got, again, 0) == 230);
  for (size_t i = 0; i < 230; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Maker Protection Subscription: 3 bytes --------------------------- */

typedef struct {
  uint8_t group[2];                         /* bytes 0 to 1 */
  uint8_t protection_type_advanced_normal;  /* byte 2 */
} MarketMakerProtectionSubscription;

/* any Market Maker Protection Subscription at all: every byte one the checker chooses */
static void any_market_maker_protection_subscription(MarketMakerProtectionSubscription *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->protection_type_advanced_normal = arbitrary();
}

/* Market Maker Protection Subscription to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_market_maker_protection_subscription(const MarketMakerProtectionSubscription *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->protection_type_advanced_normal;

  return at;
}

/* Market Maker Protection Subscription off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_market_maker_protection_subscription(MarketMakerProtectionSubscription *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->protection_type_advanced_normal = wire[at++];

  return at;
}

/* what was read of Market Maker Protection Subscription is what was written, byte for byte */
static void equal_market_maker_protection_subscription(const MarketMakerProtectionSubscription *read, const MarketMakerProtectionSubscription *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->protection_type_advanced_normal == written->protection_type_advanced_normal);
}

/* Market Maker Protection Subscription: written and read back, then read and written back */
static void check_market_maker_protection_subscription(void) {
  MarketMakerProtectionSubscription sent;
  MarketMakerProtectionSubscription got;
  uint8_t wire[3];
  uint8_t again[3];

  any_market_maker_protection_subscription(&sent);
  assert(encode_market_maker_protection_subscription(&sent, wire, 0) == 3);
  assert(decode_market_maker_protection_subscription(&got, wire, 0) == 3);
  equal_market_maker_protection_subscription(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_market_maker_protection_subscription(&got, wire, 0) == 3);
  assert(encode_market_maker_protection_subscription(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote: 14 bytes --------------------------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t quantity_1[8];           /* bytes 6 to 13 */
} RequestForQuote;

/* any Request For Quote at all: every byte one the checker chooses */
static void any_request_for_quote(RequestForQuote *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_1[i] = arbitrary(); }
}

/* Request For Quote to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote(const RequestForQuote *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_1[i]; }

  return at;
}

/* Request For Quote off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote(RequestForQuote *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_1[i] = wire[at++]; }

  return at;
}

/* what was read of Request For Quote is what was written, byte for byte */
static void equal_request_for_quote(const RequestForQuote *read, const RequestForQuote *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_1[i] == written->quantity_1[i]); }
}

/* Request For Quote: written and read back, then read and written back */
static void check_request_for_quote(void) {
  RequestForQuote sent;
  RequestForQuote got;
  uint8_t wire[14];
  uint8_t again[14];

  any_request_for_quote(&sent);
  assert(encode_request_for_quote(&sent, wire, 0) == 14);
  assert(decode_request_for_quote(&got, wire, 0) == 14);
  equal_request_for_quote(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote(&got, wire, 0) == 14);
  assert(encode_request_for_quote(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation: 14 bytes -------------------------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t cancelled_order_id[8];   /* bytes 6 to 13 */
} OrderCancellation;

/* any Order Cancellation at all: every byte one the checker chooses */
static void any_order_cancellation(OrderCancellation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = arbitrary(); }
}

/* Order Cancellation to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation(const OrderCancellation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cancelled_order_id[i]; }

  return at;
}

/* Order Cancellation off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation(OrderCancellation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation is what was written, byte for byte */
static void equal_order_cancellation(const OrderCancellation *read, const OrderCancellation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cancelled_order_id[i] == written->cancelled_order_id[i]); }
}

/* Order Cancellation: written and read back, then read and written back */
static void check_order_cancellation(void) {
  OrderCancellation sent;
  OrderCancellation got;
  uint8_t wire[14];
  uint8_t again[14];

  any_order_cancellation(&sent);
  assert(encode_order_cancellation(&sent, wire, 0) == 14);
  assert(decode_order_cancellation(&got, wire, 0) == 14);
  equal_order_cancellation(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation(&got, wire, 0) == 14);
  assert(encode_order_cancellation(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Improvement Order Cancellation: 14 bytes -------------------------------- */

/* Stated by the guide as having the same number of bytes and format as XE, whose fields are written out here. */
typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t cancelled_order_id[8];   /* bytes 6 to 13 */
} ImprovementOrderCancellation;

/* any Improvement Order Cancellation at all: every byte one the checker chooses */
static void any_improvement_order_cancellation(ImprovementOrderCancellation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = arbitrary(); }
}

/* Improvement Order Cancellation to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_improvement_order_cancellation(const ImprovementOrderCancellation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cancelled_order_id[i]; }

  return at;
}

/* Improvement Order Cancellation off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_improvement_order_cancellation(ImprovementOrderCancellation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Improvement Order Cancellation is what was written, byte for byte */
static void equal_improvement_order_cancellation(const ImprovementOrderCancellation *read, const ImprovementOrderCancellation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cancelled_order_id[i] == written->cancelled_order_id[i]); }
}

/* Improvement Order Cancellation: written and read back, then read and written back */
static void check_improvement_order_cancellation(void) {
  ImprovementOrderCancellation sent;
  ImprovementOrderCancellation got;
  uint8_t wire[14];
  uint8_t again[14];

  any_improvement_order_cancellation(&sent);
  assert(encode_improvement_order_cancellation(&sent, wire, 0) == 14);
  assert(decode_improvement_order_cancellation(&got, wire, 0) == 14);
  equal_improvement_order_cancellation(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_improvement_order_cancellation(&got, wire, 0) == 14);
  assert(encode_improvement_order_cancellation(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_incoming_header();
  check_user_disconnection();
  check_heartbeat_response();
  check_clearing_data();
  check_owner_data();
  check_bulk_quote_data();
  check_global_cancellation();
  check_user_global_cancellation();
  check_directed_routed_order_rejection_and_quote();
  check_buying_clearing_data();
  check_selling_clearing_data();
  check_buying_owner_data();
  check_selling_owner_data();
  check_auction_entry();
  check_clearing_data_dealer();
  check_owner_data_dealer();
  check_directed_order_acceptation();
  check_order_entry();
  check_improvement_order_entry();
  check_order_modification();
  check_market_maker_protection_subscription();
  check_request_for_quote();
  check_order_cancellation();
  check_improvement_order_cancellation();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
