// tmx/mx/solaorderentry/Mx_SolaOrderEntry_v1_21_Firm.c
/*
 * TMX Group Sola Order Entry
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

/* ---- Heartbeat Response: 20 bytes -------------------------------------------- */

typedef struct {
  uint8_t user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[8];  /* bytes 0 to 7 */
  uint8_t last_exchange_message_id_sent_to_participant[6];                              /* bytes 8 to 13 */
  uint8_t user_message_timestamp_local_hhmmss[6];                                       /* bytes 14 to 19 */
} HeartbeatResponse;

/* any Heartbeat Response at all: every byte one the checker chooses */
static void any_heartbeat_response(HeartbeatResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->user_message_timestamp_local_hhmmss[i] = arbitrary(); }
}

/* Heartbeat Response to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_response(const HeartbeatResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_exchange_message_id_sent_to_participant[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_message_timestamp_local_hhmmss[i]; }

  return at;
}

/* Heartbeat Response off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_response(HeartbeatResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->user_message_timestamp_local_hhmmss[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Response is what was written, byte for byte */
static void equal_heartbeat_response(const HeartbeatResponse *read, const HeartbeatResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] == written->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_exchange_message_id_sent_to_participant[i] == written->last_exchange_message_id_sent_to_participant[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->user_message_timestamp_local_hhmmss[i] == written->user_message_timestamp_local_hhmmss[i]); }
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

/* ---- Incoming Messages Header: 22 bytes -------------------------------------- */

/* The guide states these fields once, as the Incoming Messages Header, for every business message a Participant sends. Message Type is read by the packet before the branch, so it is not repeated here. */
typedef struct {
  uint8_t user_timestamp_local_hhmmss[6];  /* bytes 0 to 5 */
  uint8_t trader_id[8];                    /* bytes 6 to 13 */
  uint8_t user_sequence_id[8];             /* bytes 14 to 21 */
} IncomingMessagesHeader;

/* any Incoming Messages Header at all: every byte one the checker chooses */
static void any_incoming_messages_header(IncomingMessagesHeader *record) {
  for (size_t i = 0; i < 6; i++) { record->user_timestamp_local_hhmmss[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id[i] = arbitrary(); }
}

/* Incoming Messages Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_incoming_messages_header(const IncomingMessagesHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_timestamp_local_hhmmss[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_id[i]; }

  return at;
}

/* Incoming Messages Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_incoming_messages_header(IncomingMessagesHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->user_timestamp_local_hhmmss[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id[i] = wire[at++]; }

  return at;
}

/* what was read of Incoming Messages Header is what was written, byte for byte */
static void equal_incoming_messages_header(const IncomingMessagesHeader *read, const IncomingMessagesHeader *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->user_timestamp_local_hhmmss[i] == written->user_timestamp_local_hhmmss[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_id[i] == written->user_sequence_id[i]); }
}

/* Incoming Messages Header: written and read back, then read and written back */
static void check_incoming_messages_header(void) {
  IncomingMessagesHeader sent;
  IncomingMessagesHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_incoming_messages_header(&sent);
  assert(encode_incoming_messages_header(&sent, wire, 0) == 22);
  assert(decode_incoming_messages_header(&got, wire, 0) == 22);
  equal_incoming_messages_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_incoming_messages_header(&got, wire, 0) == 22);
  assert(encode_incoming_messages_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Request: 22 bytes ------------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
} OrderRequest;

/* any Order Request at all: every byte one the checker chooses */
static void any_order_request(OrderRequest *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
}

/* Order Request to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_order_request(const OrderRequest *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);

  return at;
}

/* Order Request off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_order_request(OrderRequest *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);

  return at;
}

/* what was read of Order Request is what was written, byte for byte */
static void equal_order_request(const OrderRequest *read, const OrderRequest *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
}

/* Order Request: written and read back, then read and written back */
static void check_order_request(void) {
  OrderRequest sent;
  OrderRequest got;
  uint8_t wire[22];
  uint8_t again[22];

  any_order_request(&sent);
  assert(encode_order_request(&sent, wire, 0) == 22);
  assert(decode_order_request(&got, wire, 0) == 22);
  equal_order_request(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_order_request(&got, wire, 0) == 22);
  assert(encode_order_request(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Data: 20 bytes ------------------------------------------------- */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t filler_5[5];               /* bytes 15 to 19 */
} ClearingData;

/* any Clearing Data at all: every byte one the checker chooses */
static void any_clearing_data(ClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = arbitrary(); }
}

/* Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_clearing_data(const ClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->filler_5[i]; }

  return at;
}

/* Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_clearing_data(ClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Data is what was written, byte for byte */
static void equal_clearing_data(const ClearingData *read, const ClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  for (size_t i = 0; i < 5; i++) { assert(read->filler_5[i] == written->filler_5[i]); }
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

/* ---- Owner Data: 50 bytes ---------------------------------------------------- */

/* The guide states this field once, as Owner Data, for every message that carries it. */
typedef struct {
  uint8_t memo[50];  /* bytes 0 to 49 */
} OwnerData;

/* any Owner Data at all: every byte one the checker chooses */
static void any_owner_data(OwnerData *record) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Owner Data to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_owner_data(const OwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Owner Data off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_owner_data(OwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Owner Data is what was written, byte for byte */
static void equal_owner_data(const OwnerData *read, const OwnerData *written) {
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Owner Data: written and read back, then read and written back */
static void check_owner_data(void) {
  OwnerData sent;
  OwnerData got;
  uint8_t wire[50];
  uint8_t again[50];

  any_owner_data(&sent);
  assert(encode_owner_data(&sent, wire, 0) == 50);
  assert(decode_owner_data(&got, wire, 0) == 50);
  equal_owner_data(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_owner_data(&got, wire, 0) == 50);
  assert(encode_owner_data(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulk Quote Data: 174 bytes ---------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  ClearingData clearing_data;                       /* bytes 24 to 43 */
  OwnerData owner_data;                             /* bytes 44 to 93 */
  uint8_t maximum_number_trades[2];                 /* bytes 94 to 95 */
  uint8_t minimum_volume[8];                        /* bytes 96 to 103 */
  uint8_t filler_2[2];                              /* bytes 104 to 105 */
  uint8_t calculation_time_interval[8];             /* bytes 106 to 113 */
  uint8_t maximum_total_volume[8];                  /* bytes 114 to 121 */
  uint8_t maximum_total_value[8];                   /* bytes 122 to 129 */
  uint8_t delta_maximum_volume[8];                  /* bytes 130 to 137 */
  uint8_t delta_maximum_value[8];                   /* bytes 138 to 145 */
  uint8_t anti_wash_id[8];                          /* bytes 146 to 153 */
  uint8_t filler_20[20];                            /* bytes 154 to 173 */
} BulkQuoteData;

/* any Bulk Quote Data at all: every byte one the checker chooses */
static void any_bulk_quote_data(BulkQuoteData *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 2; i++) { record->maximum_number_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->calculation_time_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta_maximum_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->delta_maximum_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = arbitrary(); }
}

/* Bulk Quote Data to the wire: 174 bytes from at, returning where the next byte goes */
static size_t encode_bulk_quote_data(const BulkQuoteData *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maximum_number_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculation_time_interval[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_total_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_total_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta_maximum_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->delta_maximum_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->anti_wash_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler_20[i]; }

  return at;
}

/* Bulk Quote Data off the wire: 174 bytes from at, returning where the next byte lies */
static size_t decode_bulk_quote_data(BulkQuoteData *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 2; i++) { record->maximum_number_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->calculation_time_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maximum_total_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta_maximum_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->delta_maximum_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = wire[at++]; }

  return at;
}

/* what was read of Bulk Quote Data is what was written, byte for byte */
static void equal_bulk_quote_data(const BulkQuoteData *read, const BulkQuoteData *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 2; i++) { assert(read->maximum_number_trades[i] == written->maximum_number_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_volume[i] == written->minimum_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->calculation_time_interval[i] == written->calculation_time_interval[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_total_volume[i] == written->maximum_total_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_total_value[i] == written->maximum_total_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta_maximum_volume[i] == written->delta_maximum_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->delta_maximum_value[i] == written->delta_maximum_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->anti_wash_id[i] == written->anti_wash_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->filler_20[i] == written->filler_20[i]); }
}

/* Bulk Quote Data: written and read back, then read and written back */
static void check_bulk_quote_data(void) {
  BulkQuoteData sent;
  BulkQuoteData got;
  uint8_t wire[174];
  uint8_t again[174];

  any_bulk_quote_data(&sent);
  assert(encode_bulk_quote_data(&sent, wire, 0) == 174);
  assert(decode_bulk_quote_data(&got, wire, 0) == 174);
  equal_bulk_quote_data(&got, &sent);

  for (size_t i = 0; i < 174; i++) { wire[i] = arbitrary(); }
  assert(decode_bulk_quote_data(&got, wire, 0) == 174);
  assert(encode_bulk_quote_data(&got, again, 0) == 174);
  for (size_t i = 0; i < 174; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Cancellation: 25 bytes ------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t type_of_cancellation_q_quotes_only;       /* byte 24 */
} GlobalCancellation;

/* any Global Cancellation at all: every byte one the checker chooses */
static void any_global_cancellation(GlobalCancellation *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->type_of_cancellation_q_quotes_only = arbitrary();
}

/* Global Cancellation to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_global_cancellation(const GlobalCancellation *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->type_of_cancellation_q_quotes_only;

  return at;
}

/* Global Cancellation off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_global_cancellation(GlobalCancellation *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->type_of_cancellation_q_quotes_only = wire[at++];

  return at;
}

/* what was read of Global Cancellation is what was written, byte for byte */
static void equal_global_cancellation(const GlobalCancellation *read, const GlobalCancellation *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->type_of_cancellation_q_quotes_only == written->type_of_cancellation_q_quotes_only);
}

/* Global Cancellation: written and read back, then read and written back */
static void check_global_cancellation(void) {
  GlobalCancellation sent;
  GlobalCancellation got;
  uint8_t wire[25];
  uint8_t again[25];

  any_global_cancellation(&sent);
  assert(encode_global_cancellation(&sent, wire, 0) == 25);
  assert(decode_global_cancellation(&got, wire, 0) == 25);
  equal_global_cancellation(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_global_cancellation(&got, wire, 0) == 25);
  assert(encode_global_cancellation(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Global Cancellation: 37 bytes -------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group_filter[2];                          /* bytes 22 to 23 */
  uint8_t instrument_filter[4];                     /* bytes 24 to 27 */
  uint8_t type_of_cancellation;                     /* byte 28 */
  uint8_t account_type_filter[8];                   /* bytes 29 to 36 */
} UserGlobalCancellation;

/* any User Global Cancellation at all: every byte one the checker chooses */
static void any_user_global_cancellation(UserGlobalCancellation *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group_filter[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_filter[i] = arbitrary(); }
  record->type_of_cancellation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->account_type_filter[i] = arbitrary(); }
}

/* User Global Cancellation to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_user_global_cancellation(const UserGlobalCancellation *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group_filter[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_filter[i]; }
  wire[at++] = record->type_of_cancellation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->account_type_filter[i]; }

  return at;
}

/* User Global Cancellation off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_user_global_cancellation(UserGlobalCancellation *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group_filter[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_filter[i] = wire[at++]; }
  record->type_of_cancellation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->account_type_filter[i] = wire[at++]; }

  return at;
}

/* what was read of User Global Cancellation is what was written, byte for byte */
static void equal_user_global_cancellation(const UserGlobalCancellation *read, const UserGlobalCancellation *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group_filter[i] == written->group_filter[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_filter[i] == written->instrument_filter[i]); }
  assert(read->type_of_cancellation == written->type_of_cancellation);
  for (size_t i = 0; i < 8; i++) { assert(read->account_type_filter[i] == written->account_type_filter[i]); }
}

/* User Global Cancellation: written and read back, then read and written back */
static void check_user_global_cancellation(void) {
  UserGlobalCancellation sent;
  UserGlobalCancellation got;
  uint8_t wire[37];
  uint8_t again[37];

  any_user_global_cancellation(&sent);
  assert(encode_user_global_cancellation(&sent, wire, 0) == 37);
  assert(decode_user_global_cancellation(&got, wire, 0) == 37);
  equal_user_global_cancellation(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_user_global_cancellation(&got, wire, 0) == 37);
  assert(encode_user_global_cancellation(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Set Global Risk Limits: 101 bytes --------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t global_net_exposure_action;               /* byte 22 */
  uint8_t default_net_exposure_action;              /* byte 23 */
  uint8_t default_long_exposure_action;             /* byte 24 */
  uint8_t default_short_exposure_action;            /* byte 25 */
  uint8_t default_net_position_action;              /* byte 26 */
  uint8_t default_long_position_action;             /* byte 27 */
  uint8_t default_short_position_action;            /* byte 28 */
  uint8_t global_net_exposure_limit[10];            /* bytes 29 to 38 */
  uint8_t default_maximum_order_quantity[8];        /* bytes 39 to 46 */
  uint8_t default_net_exposure_limit[10];           /* bytes 47 to 56 */
  uint8_t default_long_exposure_limit[10];          /* bytes 57 to 66 */
  uint8_t default_short_exposure_limit[10];         /* bytes 67 to 76 */
  uint8_t default_net_position_limit[8];            /* bytes 77 to 84 */
  uint8_t default_long_position_limit[8];           /* bytes 85 to 92 */
  uint8_t default_short_position_limit[8];          /* bytes 93 to 100 */
} SetGlobalRiskLimits;

/* any Set Global Risk Limits at all: every byte one the checker chooses */
static void any_set_global_risk_limits(SetGlobalRiskLimits *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  record->global_net_exposure_action = arbitrary();
  record->default_net_exposure_action = arbitrary();
  record->default_long_exposure_action = arbitrary();
  record->default_short_exposure_action = arbitrary();
  record->default_net_position_action = arbitrary();
  record->default_long_position_action = arbitrary();
  record->default_short_position_action = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->global_net_exposure_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->default_maximum_order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->default_net_exposure_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->default_long_exposure_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->default_short_exposure_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->default_net_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->default_long_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->default_short_position_limit[i] = arbitrary(); }
}

/* Set Global Risk Limits to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_set_global_risk_limits(const SetGlobalRiskLimits *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  wire[at++] = record->global_net_exposure_action;
  wire[at++] = record->default_net_exposure_action;
  wire[at++] = record->default_long_exposure_action;
  wire[at++] = record->default_short_exposure_action;
  wire[at++] = record->default_net_position_action;
  wire[at++] = record->default_long_position_action;
  wire[at++] = record->default_short_position_action;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->global_net_exposure_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->default_maximum_order_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->default_net_exposure_limit[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->default_long_exposure_limit[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->default_short_exposure_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->default_net_position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->default_long_position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->default_short_position_limit[i]; }

  return at;
}

/* Set Global Risk Limits off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_set_global_risk_limits(SetGlobalRiskLimits *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  record->global_net_exposure_action = wire[at++];
  record->default_net_exposure_action = wire[at++];
  record->default_long_exposure_action = wire[at++];
  record->default_short_exposure_action = wire[at++];
  record->default_net_position_action = wire[at++];
  record->default_long_position_action = wire[at++];
  record->default_short_position_action = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->global_net_exposure_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->default_maximum_order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->default_net_exposure_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->default_long_exposure_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->default_short_exposure_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->default_net_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->default_long_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->default_short_position_limit[i] = wire[at++]; }

  return at;
}

/* what was read of Set Global Risk Limits is what was written, byte for byte */
static void equal_set_global_risk_limits(const SetGlobalRiskLimits *read, const SetGlobalRiskLimits *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  assert(read->global_net_exposure_action == written->global_net_exposure_action);
  assert(read->default_net_exposure_action == written->default_net_exposure_action);
  assert(read->default_long_exposure_action == written->default_long_exposure_action);
  assert(read->default_short_exposure_action == written->default_short_exposure_action);
  assert(read->default_net_position_action == written->default_net_position_action);
  assert(read->default_long_position_action == written->default_long_position_action);
  assert(read->default_short_position_action == written->default_short_position_action);
  for (size_t i = 0; i < 10; i++) { assert(read->global_net_exposure_limit[i] == written->global_net_exposure_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->default_maximum_order_quantity[i] == written->default_maximum_order_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->default_net_exposure_limit[i] == written->default_net_exposure_limit[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->default_long_exposure_limit[i] == written->default_long_exposure_limit[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->default_short_exposure_limit[i] == written->default_short_exposure_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->default_net_position_limit[i] == written->default_net_position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->default_long_position_limit[i] == written->default_long_position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->default_short_position_limit[i] == written->default_short_position_limit[i]); }
}

/* Set Global Risk Limits: written and read back, then read and written back */
static void check_set_global_risk_limits(void) {
  SetGlobalRiskLimits sent;
  SetGlobalRiskLimits got;
  uint8_t wire[101];
  uint8_t again[101];

  any_set_global_risk_limits(&sent);
  assert(encode_set_global_risk_limits(&sent, wire, 0) == 101);
  assert(decode_set_global_risk_limits(&got, wire, 0) == 101);
  equal_set_global_risk_limits(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_set_global_risk_limits(&got, wire, 0) == 101);
  assert(encode_set_global_risk_limits(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Entry: 181 bytes -------------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t price_type;                               /* byte 28 */
  uint8_t verb_side;                                /* byte 29 */
  uint8_t quantity[8];                              /* bytes 30 to 37 */
  uint8_t price[10];                                /* bytes 38 to 47 */
  uint8_t special_price_term;                       /* byte 48 */
  uint8_t additional_price[10];                     /* bytes 49 to 58 */
  uint8_t quantity_term;                            /* byte 59 */
  uint8_t additional_quantity[8];                   /* bytes 60 to 67 */
  uint8_t duration_type;                            /* byte 68 */
  uint8_t gtd_date[8];                              /* bytes 69 to 76 */
  uint8_t executing_participant[4];                 /* bytes 77 to 80 */
  uint8_t filler_1;                                 /* byte 81 */
  ClearingData clearing_data;                       /* bytes 82 to 101 */
  OwnerData owner_data;                             /* bytes 102 to 151 */
  uint8_t anti_wash_id[8];                          /* bytes 152 to 159 */
  uint8_t anti_wash_instruction;                    /* byte 160 */
  uint8_t filler_20[20];                            /* bytes 161 to 180 */
} OrderEntry;

/* any Order Entry at all: every byte one the checker chooses */
static void any_order_entry(OrderEntry *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->special_price_term = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = arbitrary(); }
  record->quantity_term = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = arbitrary(); }
  record->duration_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executing_participant[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = arbitrary(); }
  record->anti_wash_instruction = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = arbitrary(); }
}

/* Order Entry to the wire: 181 bytes from at, returning where the next byte goes */
static size_t encode_order_entry(const OrderEntry *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->special_price_term;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->additional_price[i]; }
  wire[at++] = record->quantity_term;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_quantity[i]; }
  wire[at++] = record->duration_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gtd_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_participant[i]; }
  wire[at++] = record->filler_1;
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->anti_wash_id[i]; }
  wire[at++] = record->anti_wash_instruction;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler_20[i]; }

  return at;
}

/* Order Entry off the wire: 181 bytes from at, returning where the next byte lies */
static size_t decode_order_entry(OrderEntry *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->special_price_term = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = wire[at++]; }
  record->quantity_term = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = wire[at++]; }
  record->duration_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executing_participant[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = wire[at++]; }
  record->anti_wash_instruction = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = wire[at++]; }

  return at;
}

/* what was read of Order Entry is what was written, byte for byte */
static void equal_order_entry(const OrderEntry *read, const OrderEntry *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->price_type == written->price_type);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->special_price_term == written->special_price_term);
  for (size_t i = 0; i < 10; i++) { assert(read->additional_price[i] == written->additional_price[i]); }
  assert(read->quantity_term == written->quantity_term);
  for (size_t i = 0; i < 8; i++) { assert(read->additional_quantity[i] == written->additional_quantity[i]); }
  assert(read->duration_type == written->duration_type);
  for (size_t i = 0; i < 8; i++) { assert(read->gtd_date[i] == written->gtd_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executing_participant[i] == written->executing_participant[i]); }
  assert(read->filler_1 == written->filler_1);
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->anti_wash_id[i] == written->anti_wash_id[i]); }
  assert(read->anti_wash_instruction == written->anti_wash_instruction);
  for (size_t i = 0; i < 20; i++) { assert(read->filler_20[i] == written->filler_20[i]); }
}

/* Order Entry: written and read back, then read and written back */
static void check_order_entry(void) {
  OrderEntry sent;
  OrderEntry got;
  uint8_t wire[181];
  uint8_t again[181];

  any_order_entry(&sent);
  assert(encode_order_entry(&sent, wire, 0) == 181);
  assert(decode_order_entry(&got, wire, 0) == 181);
  equal_order_entry(&got, &sent);

  for (size_t i = 0; i < 181; i++) { wire[i] = arbitrary(); }
  assert(decode_order_entry(&got, wire, 0) == 181);
  assert(encode_order_entry(&got, again, 0) == 181);
  for (size_t i = 0; i < 181; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modification: 190 bytes ------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t price_type;                               /* byte 28 */
  uint8_t verb_side;                                /* byte 29 */
  uint8_t quantity_sign;                            /* byte 30 */
  uint8_t quantity[8];                              /* bytes 31 to 38 */
  uint8_t price[10];                                /* bytes 39 to 48 */
  uint8_t special_price_term;                       /* byte 49 */
  uint8_t additional_price[10];                     /* bytes 50 to 59 */
  uint8_t quantity_term;                            /* byte 60 */
  uint8_t additional_quantity[8];                   /* bytes 61 to 68 */
  uint8_t duration_type;                            /* byte 69 */
  uint8_t gtd_date[8];                              /* bytes 70 to 77 */
  uint8_t filler_4[4];                              /* bytes 78 to 81 */
  uint8_t filler_1;                                 /* byte 82 */
  uint8_t modified_order_id[8];                     /* bytes 83 to 90 */
  ClearingData clearing_data;                       /* bytes 91 to 110 */
  OwnerData owner_data;                             /* bytes 111 to 160 */
  uint8_t anti_wash_id[8];                          /* bytes 161 to 168 */
  uint8_t anti_wash_instruction;                    /* byte 169 */
  uint8_t filler_20[20];                            /* bytes 170 to 189 */
} OrderModification;

/* any Order Modification at all: every byte one the checker chooses */
static void any_order_modification(OrderModification *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  record->price_type = arbitrary();
  record->verb_side = arbitrary();
  record->quantity_sign = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  record->special_price_term = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = arbitrary(); }
  record->quantity_term = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = arbitrary(); }
  record->duration_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->modified_order_id[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = arbitrary(); }
  record->anti_wash_instruction = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = arbitrary(); }
}

/* Order Modification to the wire: 190 bytes from at, returning where the next byte goes */
static size_t encode_order_modification(const OrderModification *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->price_type;
  wire[at++] = record->verb_side;
  wire[at++] = record->quantity_sign;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->special_price_term;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->additional_price[i]; }
  wire[at++] = record->quantity_term;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->additional_quantity[i]; }
  wire[at++] = record->duration_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gtd_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->filler_4[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->modified_order_id[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->anti_wash_id[i]; }
  wire[at++] = record->anti_wash_instruction;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler_20[i]; }

  return at;
}

/* Order Modification off the wire: 190 bytes from at, returning where the next byte lies */
static size_t decode_order_modification(OrderModification *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  record->price_type = wire[at++];
  record->verb_side = wire[at++];
  record->quantity_sign = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  record->special_price_term = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->additional_price[i] = wire[at++]; }
  record->quantity_term = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->additional_quantity[i] = wire[at++]; }
  record->duration_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->gtd_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->filler_4[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->modified_order_id[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->anti_wash_id[i] = wire[at++]; }
  record->anti_wash_instruction = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modification is what was written, byte for byte */
static void equal_order_modification(const OrderModification *read, const OrderModification *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->price_type == written->price_type);
  assert(read->verb_side == written->verb_side);
  assert(read->quantity_sign == written->quantity_sign);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->special_price_term == written->special_price_term);
  for (size_t i = 0; i < 10; i++) { assert(read->additional_price[i] == written->additional_price[i]); }
  assert(read->quantity_term == written->quantity_term);
  for (size_t i = 0; i < 8; i++) { assert(read->additional_quantity[i] == written->additional_quantity[i]); }
  assert(read->duration_type == written->duration_type);
  for (size_t i = 0; i < 8; i++) { assert(read->gtd_date[i] == written->gtd_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->filler_4[i] == written->filler_4[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->modified_order_id[i] == written->modified_order_id[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->anti_wash_id[i] == written->anti_wash_id[i]); }
  assert(read->anti_wash_instruction == written->anti_wash_instruction);
  for (size_t i = 0; i < 20; i++) { assert(read->filler_20[i] == written->filler_20[i]); }
}

/* Order Modification: written and read back, then read and written back */
static void check_order_modification(void) {
  OrderModification sent;
  OrderModification got;
  uint8_t wire[190];
  uint8_t again[190];

  any_order_modification(&sent);
  assert(encode_order_modification(&sent, wire, 0) == 190);
  assert(decode_order_modification(&got, wire, 0) == 190);
  equal_order_modification(&got, &sent);

  for (size_t i = 0; i < 190; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modification(&got, wire, 0) == 190);
  assert(encode_order_modification(&got, again, 0) == 190);
  for (size_t i = 0; i < 190; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buying Clearing Data: 20 bytes ------------------------------------------ */

/* Clearing Data for the buying side, which OX: Cross Entry carries alongside the other side. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t filler_5[5];               /* bytes 15 to 19 */
} BuyingClearingData;

/* any Buying Clearing Data at all: every byte one the checker chooses */
static void any_buying_clearing_data(BuyingClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = arbitrary(); }
}

/* Buying Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_buying_clearing_data(const BuyingClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->filler_5[i]; }

  return at;
}

/* Buying Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_buying_clearing_data(BuyingClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = wire[at++]; }

  return at;
}

/* what was read of Buying Clearing Data is what was written, byte for byte */
static void equal_buying_clearing_data(const BuyingClearingData *read, const BuyingClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  for (size_t i = 0; i < 5; i++) { assert(read->filler_5[i] == written->filler_5[i]); }
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

/* Clearing Data for the selling side, which OX: Cross Entry carries alongside the other side. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t filler_5[5];               /* bytes 15 to 19 */
} SellingClearingData;

/* any Selling Clearing Data at all: every byte one the checker chooses */
static void any_selling_clearing_data(SellingClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = arbitrary(); }
}

/* Selling Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_selling_clearing_data(const SellingClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->filler_5[i]; }

  return at;
}

/* Selling Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_selling_clearing_data(SellingClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = wire[at++]; }

  return at;
}

/* what was read of Selling Clearing Data is what was written, byte for byte */
static void equal_selling_clearing_data(const SellingClearingData *read, const SellingClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  for (size_t i = 0; i < 5; i++) { assert(read->filler_5[i] == written->filler_5[i]); }
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

/* ---- Buying Owner Data: 50 bytes --------------------------------------------- */

/* Owner Data for the buying side, which OX: Cross Entry carries alongside the other side. */
typedef struct {
  uint8_t memo[50];  /* bytes 0 to 49 */
} BuyingOwnerData;

/* any Buying Owner Data at all: every byte one the checker chooses */
static void any_buying_owner_data(BuyingOwnerData *record) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Buying Owner Data to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_buying_owner_data(const BuyingOwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Buying Owner Data off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_buying_owner_data(BuyingOwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Buying Owner Data is what was written, byte for byte */
static void equal_buying_owner_data(const BuyingOwnerData *read, const BuyingOwnerData *written) {
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Buying Owner Data: written and read back, then read and written back */
static void check_buying_owner_data(void) {
  BuyingOwnerData sent;
  BuyingOwnerData got;
  uint8_t wire[50];
  uint8_t again[50];

  any_buying_owner_data(&sent);
  assert(encode_buying_owner_data(&sent, wire, 0) == 50);
  assert(decode_buying_owner_data(&got, wire, 0) == 50);
  equal_buying_owner_data(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_buying_owner_data(&got, wire, 0) == 50);
  assert(encode_buying_owner_data(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Selling Owner Data: 50 bytes -------------------------------------------- */

/* Owner Data for the selling side, which OX: Cross Entry carries alongside the other side. */
typedef struct {
  uint8_t memo[50];  /* bytes 0 to 49 */
} SellingOwnerData;

/* any Selling Owner Data at all: every byte one the checker chooses */
static void any_selling_owner_data(SellingOwnerData *record) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Selling Owner Data to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_selling_owner_data(const SellingOwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Selling Owner Data off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_selling_owner_data(SellingOwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Selling Owner Data is what was written, byte for byte */
static void equal_selling_owner_data(const SellingOwnerData *read, const SellingOwnerData *written) {
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Selling Owner Data: written and read back, then read and written back */
static void check_selling_owner_data(void) {
  SellingOwnerData sent;
  SellingOwnerData got;
  uint8_t wire[50];
  uint8_t again[50];

  any_selling_owner_data(&sent);
  assert(encode_selling_owner_data(&sent, wire, 0) == 50);
  assert(decode_selling_owner_data(&got, wire, 0) == 50);
  equal_selling_owner_data(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_selling_owner_data(&got, wire, 0) == 50);
  assert(encode_selling_owner_data(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Entry: 207 bytes -------------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t filler_1;                                 /* byte 28 */
  uint8_t quantity[8];                              /* bytes 29 to 36 */
  uint8_t price[10];                                /* bytes 37 to 46 */
  BuyingClearingData buying_clearing_data;          /* bytes 47 to 66 */
  SellingClearingData selling_clearing_data;        /* bytes 67 to 86 */
  BuyingOwnerData buying_owner_data;                /* bytes 87 to 136 */
  SellingOwnerData selling_owner_data;              /* bytes 137 to 186 */
  uint8_t filler_20[20];                            /* bytes 187 to 206 */
} CrossEntry;

/* any Cross Entry at all: every byte one the checker chooses */
static void any_cross_entry(CrossEntry *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  record->filler_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  any_buying_clearing_data(&record->buying_clearing_data);
  any_selling_clearing_data(&record->selling_clearing_data);
  any_buying_owner_data(&record->buying_owner_data);
  any_selling_owner_data(&record->selling_owner_data);
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = arbitrary(); }
}

/* Cross Entry to the wire: 207 bytes from at, returning where the next byte goes */
static size_t encode_cross_entry(const CrossEntry *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->filler_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  at = encode_buying_clearing_data(&record->buying_clearing_data, wire, at);
  at = encode_selling_clearing_data(&record->selling_clearing_data, wire, at);
  at = encode_buying_owner_data(&record->buying_owner_data, wire, at);
  at = encode_selling_owner_data(&record->selling_owner_data, wire, at);
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->filler_20[i]; }

  return at;
}

/* Cross Entry off the wire: 207 bytes from at, returning where the next byte lies */
static size_t decode_cross_entry(CrossEntry *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  record->filler_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  at = decode_buying_clearing_data(&record->buying_clearing_data, wire, at);
  at = decode_selling_clearing_data(&record->selling_clearing_data, wire, at);
  at = decode_buying_owner_data(&record->buying_owner_data, wire, at);
  at = decode_selling_owner_data(&record->selling_owner_data, wire, at);
  for (size_t i = 0; i < 20; i++) { record->filler_20[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Entry is what was written, byte for byte */
static void equal_cross_entry(const CrossEntry *read, const CrossEntry *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->filler_1 == written->filler_1);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  equal_buying_clearing_data(&read->buying_clearing_data, &written->buying_clearing_data);
  equal_selling_clearing_data(&read->selling_clearing_data, &written->selling_clearing_data);
  equal_buying_owner_data(&read->buying_owner_data, &written->buying_owner_data);
  equal_selling_owner_data(&read->selling_owner_data, &written->selling_owner_data);
  for (size_t i = 0; i < 20; i++) { assert(read->filler_20[i] == written->filler_20[i]); }
}

/* Cross Entry: written and read back, then read and written back */
static void check_cross_entry(void) {
  CrossEntry sent;
  CrossEntry got;
  uint8_t wire[207];
  uint8_t again[207];

  any_cross_entry(&sent);
  assert(encode_cross_entry(&sent, wire, 0) == 207);
  assert(decode_cross_entry(&got, wire, 0) == 207);
  equal_cross_entry(&got, &sent);

  for (size_t i = 0; i < 207; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_entry(&got, wire, 0) == 207);
  assert(encode_cross_entry(&got, again, 0) == 207);
  for (size_t i = 0; i < 207; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sail Request For Quote With Side: 37 bytes ------------------------------ */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t quantity[8];                              /* bytes 28 to 35 */
  uint8_t market_side;                              /* byte 36 */
} SailRequestForQuoteWithSide;

/* any Sail Request For Quote With Side at all: every byte one the checker chooses */
static void any_sail_request_for_quote_with_side(SailRequestForQuoteWithSide *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->market_side = arbitrary();
}

/* Sail Request For Quote With Side to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_sail_request_for_quote_with_side(const SailRequestForQuoteWithSide *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->market_side;

  return at;
}

/* Sail Request For Quote With Side off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_sail_request_for_quote_with_side(SailRequestForQuoteWithSide *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->market_side = wire[at++];

  return at;
}

/* what was read of Sail Request For Quote With Side is what was written, byte for byte */
static void equal_sail_request_for_quote_with_side(const SailRequestForQuoteWithSide *read, const SailRequestForQuoteWithSide *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->market_side == written->market_side);
}

/* Sail Request For Quote With Side: written and read back, then read and written back */
static void check_sail_request_for_quote_with_side(void) {
  SailRequestForQuoteWithSide sent;
  SailRequestForQuoteWithSide got;
  uint8_t wire[37];
  uint8_t again[37];

  any_sail_request_for_quote_with_side(&sent);
  assert(encode_sail_request_for_quote_with_side(&sent, wire, 0) == 37);
  assert(decode_sail_request_for_quote_with_side(&got, wire, 0) == 37);
  equal_sail_request_for_quote_with_side(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_sail_request_for_quote_with_side(&got, wire, 0) == 37);
  assert(encode_sail_request_for_quote_with_side(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulk Quote Participant Bqp Protection Subscription: 25 bytes ------------ */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;                           /* bytes 0 to 21 */
  uint8_t group[2];                                                          /* bytes 22 to 23 */
  uint8_t protection_type_advanced_protection_advanced_protection_disabled;  /* byte 24 */
} BulkQuoteParticipantBqpProtectionSubscription;

/* any Bulk Quote Participant Bqp Protection Subscription at all: every byte one the checker chooses */
static void any_bulk_quote_participant_bqp_protection_subscription(BulkQuoteParticipantBqpProtectionSubscription *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->protection_type_advanced_protection_advanced_protection_disabled = arbitrary();
}

/* Bulk Quote Participant Bqp Protection Subscription to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_bulk_quote_participant_bqp_protection_subscription(const BulkQuoteParticipantBqpProtectionSubscription *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->protection_type_advanced_protection_advanced_protection_disabled;

  return at;
}

/* Bulk Quote Participant Bqp Protection Subscription off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_bulk_quote_participant_bqp_protection_subscription(BulkQuoteParticipantBqpProtectionSubscription *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->protection_type_advanced_protection_advanced_protection_disabled = wire[at++];

  return at;
}

/* what was read of Bulk Quote Participant Bqp Protection Subscription is what was written, byte for byte */
static void equal_bulk_quote_participant_bqp_protection_subscription(const BulkQuoteParticipantBqpProtectionSubscription *read, const BulkQuoteParticipantBqpProtectionSubscription *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->protection_type_advanced_protection_advanced_protection_disabled == written->protection_type_advanced_protection_advanced_protection_disabled);
}

/* Bulk Quote Participant Bqp Protection Subscription: written and read back, then read and written back */
static void check_bulk_quote_participant_bqp_protection_subscription(void) {
  BulkQuoteParticipantBqpProtectionSubscription sent;
  BulkQuoteParticipantBqpProtectionSubscription got;
  uint8_t wire[25];
  uint8_t again[25];

  any_bulk_quote_participant_bqp_protection_subscription(&sent);
  assert(encode_bulk_quote_participant_bqp_protection_subscription(&sent, wire, 0) == 25);
  assert(decode_bulk_quote_participant_bqp_protection_subscription(&got, wire, 0) == 25);
  equal_bulk_quote_participant_bqp_protection_subscription(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_bulk_quote_participant_bqp_protection_subscription(&got, wire, 0) == 25);
  assert(encode_bulk_quote_participant_bqp_protection_subscription(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote: 36 bytes --------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t quantity[8];                              /* bytes 28 to 35 */
} RequestForQuote;

/* any Request For Quote at all: every byte one the checker chooses */
static void any_request_for_quote(RequestForQuote *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Request For Quote to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote(const RequestForQuote *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Request For Quote off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote(RequestForQuote *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Request For Quote is what was written, byte for byte */
static void equal_request_for_quote(const RequestForQuote *read, const RequestForQuote *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Request For Quote: written and read back, then read and written back */
static void check_request_for_quote(void) {
  RequestForQuote sent;
  RequestForQuote got;
  uint8_t wire[36];
  uint8_t again[36];

  any_request_for_quote(&sent);
  assert(encode_request_for_quote(&sent, wire, 0) == 36);
  assert(decode_request_for_quote(&got, wire, 0) == 36);
  equal_request_for_quote(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote(&got, wire, 0) == 36);
  assert(encode_request_for_quote(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation: 36 bytes -------------------------------------------- */

typedef struct {
  IncomingMessagesHeader incoming_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t cancelled_order_id[8];                    /* bytes 28 to 35 */
} OrderCancellation;

/* any Order Cancellation at all: every byte one the checker chooses */
static void any_order_cancellation(OrderCancellation *record) {
  any_incoming_messages_header(&record->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = arbitrary(); }
}

/* Order Cancellation to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation(const OrderCancellation *record, uint8_t *wire, size_t at) {
  at = encode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cancelled_order_id[i]; }

  return at;
}

/* Order Cancellation off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation(OrderCancellation *record, const uint8_t *wire, size_t at) {
  at = decode_incoming_messages_header(&record->incoming_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cancelled_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation is what was written, byte for byte */
static void equal_order_cancellation(const OrderCancellation *read, const OrderCancellation *written) {
  equal_incoming_messages_header(&read->incoming_messages_header, &written->incoming_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cancelled_order_id[i] == written->cancelled_order_id[i]); }
}

/* Order Cancellation: written and read back, then read and written back */
static void check_order_cancellation(void) {
  OrderCancellation sent;
  OrderCancellation got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_cancellation(&sent);
  assert(encode_order_cancellation(&sent, wire, 0) == 36);
  assert(decode_order_cancellation(&got, wire, 0) == 36);
  equal_order_cancellation(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation(&got, wire, 0) == 36);
  assert(encode_order_cancellation(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_heartbeat_response();
  check_user_disconnection();
  check_incoming_messages_header();
  check_order_request();
  check_clearing_data();
  check_owner_data();
  check_bulk_quote_data();
  check_global_cancellation();
  check_user_global_cancellation();
  check_set_global_risk_limits();
  check_order_entry();
  check_order_modification();
  check_buying_clearing_data();
  check_selling_clearing_data();
  check_buying_owner_data();
  check_selling_owner_data();
  check_cross_entry();
  check_sail_request_for_quote_with_side();
  check_bulk_quote_participant_bqp_protection_subscription();
  check_request_for_quote();
  check_order_cancellation();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
