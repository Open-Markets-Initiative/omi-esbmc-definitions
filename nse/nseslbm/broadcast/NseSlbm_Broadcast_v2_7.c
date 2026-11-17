// nse/nseslbm/broadcast/NseSlbm_Broadcast_v2_7.c
/*
 * National Stock Exchange of India Ltd
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
 *   - a run counted by a field
 *   - a Conversion rule
 *   - a field read in bits
 *   - a Composite rule
 *   - a run of a stated number of entries
 *   - the dispatch that chooses a message by its type
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

/* ---- Bcast Header: 40 bytes -------------------------------------------------- */

/* BCAST_HEADER */
typedef struct {
  uint8_t reserved_0[2];        /* bytes 0 to 1 */
  uint8_t reserved_2[2];        /* bytes 2 to 3 */
  uint8_t log_time[4];          /* bytes 4 to 7 */
  uint8_t alpha_char[2];        /* bytes 8 to 9 */
  uint8_t transaction_code[2];  /* bytes 10 to 11 */
  uint8_t error_code[2];        /* bytes 12 to 13 */
  uint8_t bc_seq_no[4];         /* bytes 14 to 17 */
  uint8_t reserved_18;          /* byte 18 */
  uint8_t reserved_19[3];       /* bytes 19 to 21 */
  uint8_t time_stamp_2[8];      /* bytes 22 to 29 */
  uint8_t filler_2[8];          /* bytes 30 to 37 */
  uint8_t message_length[2];    /* bytes 38 to 39 */
} BcastHeader;

/* any Bcast Header at all: every byte one the checker chooses */
static void any_bcast_header(BcastHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_0[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bc_seq_no[i] = arbitrary(); }
  record->reserved_18 = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_19[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->filler_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Bcast Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_bcast_header(const BcastHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_0[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->alpha_char[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bc_seq_no[i]; }
  wire[at++] = record->reserved_18;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_19[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->filler_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Bcast Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_bcast_header(BcastHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_0[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bc_seq_no[i] = wire[at++]; }
  record->reserved_18 = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_19[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->filler_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Bcast Header is what was written, byte for byte */
static void equal_bcast_header(const BcastHeader *read, const BcastHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_0[i] == written->reserved_0[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->log_time[i] == written->log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->alpha_char[i] == written->alpha_char[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bc_seq_no[i] == written->bc_seq_no[i]); }
  assert(read->reserved_18 == written->reserved_18);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_19[i] == written->reserved_19[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_2[i] == written->time_stamp_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->filler_2[i] == written->filler_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Bcast Header: written and read back, then read and written back */
static void check_bcast_header(void) {
  BcastHeader sent;
  BcastHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_bcast_header(&sent);
  assert(encode_bcast_header(&sent, wire, 0) == 40);
  assert(decode_bcast_header(&got, wire, 0) == 40);
  equal_bcast_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_bcast_header(&got, wire, 0) == 40);
  assert(encode_bcast_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sec Info: 12 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t symbol[10];  /* bytes 0 to 9 */
  uint8_t series[2];   /* bytes 10 to 11 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
}

/* Sec Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }

  return at;
}

/* Sec Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 12);
  assert(decode_sec_info(&got, wire, 0) == 12);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 12);
  assert(encode_sec_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Change Participant Status Message: 43 bytes ----------------------------- */

/* Sent as BCAST_PART_MSTR_CHG whenever there is a participant change */
typedef struct {
  uint8_t participant_id[12];               /* bytes 0 to 11 */
  uint8_t participant_name[25];             /* bytes 12 to 36 */
  uint8_t participant_status;               /* byte 37 */
  uint8_t participant_update_date_time[4];  /* bytes 38 to 41 */
  uint8_t delete_flag;                      /* byte 42 */
} ChangeParticipantStatusMessage;

/* any Change Participant Status Message at all: every byte one the checker chooses */
static void any_change_participant_status_message(ChangeParticipantStatusMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->participant_name[i] = arbitrary(); }
  record->participant_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_update_date_time[i] = arbitrary(); }
  record->delete_flag = arbitrary();
}

/* Change Participant Status Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_change_participant_status_message(const ChangeParticipantStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->participant_name[i]; }
  wire[at++] = record->participant_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_update_date_time[i]; }
  wire[at++] = record->delete_flag;

  return at;
}

/* Change Participant Status Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_change_participant_status_message(ChangeParticipantStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->participant_name[i] = wire[at++]; }
  record->participant_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_update_date_time[i] = wire[at++]; }
  record->delete_flag = wire[at++];

  return at;
}

/* what was read of Change Participant Status Message is what was written, byte for byte */
static void equal_change_participant_status_message(const ChangeParticipantStatusMessage *read, const ChangeParticipantStatusMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->participant_name[i] == written->participant_name[i]); }
  assert(read->participant_status == written->participant_status);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_update_date_time[i] == written->participant_update_date_time[i]); }
  assert(read->delete_flag == written->delete_flag);
}

/* Change Participant Status Message: written and read back, then read and written back */
static void check_change_participant_status_message(void) {
  ChangeParticipantStatusMessage sent;
  ChangeParticipantStatusMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_change_participant_status_message(&sent);
  assert(encode_change_participant_status_message(&sent, wire, 0) == 43);
  assert(decode_change_participant_status_message(&got, wire, 0) == 43);
  equal_change_participant_status_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_change_participant_status_message(&got, wire, 0) == 43);
  assert(encode_change_participant_status_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover Limit Exceeded Message: 37 bytes ------------------------------- */

/* Sent as BCAST_TURNOVER_EXCEEDED when a broker's turnover is about to exceed or has exceeded its limit */
typedef struct {
  uint8_t broker_code[5];          /* bytes 0 to 4 */
  uint8_t counter_broker_code[5];  /* bytes 5 to 9 */
  uint8_t warning_type[2];         /* bytes 10 to 11 */
  SecInfo sec_info;                /* bytes 12 to 23 */
  uint8_t trade_number[4];         /* bytes 24 to 27 */
  uint8_t trade_price[4];          /* bytes 28 to 31 */
  uint8_t trade_volume[4];         /* bytes 32 to 35 */
  uint8_t final;                   /* byte 36 */
} TurnoverLimitExceededMessage;

/* any Turnover Limit Exceeded Message at all: every byte one the checker chooses */
static void any_turnover_limit_exceeded_message(TurnoverLimitExceededMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = arbitrary(); }
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->final = arbitrary();
}

/* Turnover Limit Exceeded Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_turnover_limit_exceeded_message(const TurnoverLimitExceededMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counter_broker_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->warning_type[i]; }
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->final;

  return at;
}

/* Turnover Limit Exceeded Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_turnover_limit_exceeded_message(TurnoverLimitExceededMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = wire[at++]; }
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->final = wire[at++];

  return at;
}

/* what was read of Turnover Limit Exceeded Message is what was written, byte for byte */
static void equal_turnover_limit_exceeded_message(const TurnoverLimitExceededMessage *read, const TurnoverLimitExceededMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->broker_code[i] == written->broker_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counter_broker_code[i] == written->counter_broker_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->warning_type[i] == written->warning_type[i]); }
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->final == written->final);
}

/* Turnover Limit Exceeded Message: written and read back, then read and written back */
static void check_turnover_limit_exceeded_message(void) {
  TurnoverLimitExceededMessage sent;
  TurnoverLimitExceededMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_turnover_limit_exceeded_message(&sent);
  assert(encode_turnover_limit_exceeded_message(&sent, wire, 0) == 37);
  assert(decode_turnover_limit_exceeded_message(&got, wire, 0) == 37);
  equal_turnover_limit_exceeded_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover_limit_exceeded_message(&got, wire, 0) == 37);
  assert(encode_turnover_limit_exceeded_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Broker Reactivated Message: 37 bytes ------------------------------------ */

/* Sent as BROADCAST_BROKER_ACTIVATED when a deactivated broker is reactivated */
typedef struct {
  uint8_t broker_code[5];          /* bytes 0 to 4 */
  uint8_t counter_broker_code[5];  /* bytes 5 to 9 */
  uint8_t warning_type[2];         /* bytes 10 to 11 */
  SecInfo sec_info;                /* bytes 12 to 23 */
  uint8_t trade_number[4];         /* bytes 24 to 27 */
  uint8_t trade_price[4];          /* bytes 28 to 31 */
  uint8_t trade_volume[4];         /* bytes 32 to 35 */
  uint8_t final;                   /* byte 36 */
} BrokerReactivatedMessage;

/* any Broker Reactivated Message at all: every byte one the checker chooses */
static void any_broker_reactivated_message(BrokerReactivatedMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = arbitrary(); }
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->final = arbitrary();
}

/* Broker Reactivated Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_broker_reactivated_message(const BrokerReactivatedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counter_broker_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->warning_type[i]; }
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->final;

  return at;
}

/* Broker Reactivated Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_broker_reactivated_message(BrokerReactivatedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = wire[at++]; }
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->final = wire[at++];

  return at;
}

/* what was read of Broker Reactivated Message is what was written, byte for byte */
static void equal_broker_reactivated_message(const BrokerReactivatedMessage *read, const BrokerReactivatedMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->broker_code[i] == written->broker_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counter_broker_code[i] == written->counter_broker_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->warning_type[i] == written->warning_type[i]); }
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->final == written->final);
}

/* Broker Reactivated Message: written and read back, then read and written back */
static void check_broker_reactivated_message(void) {
  BrokerReactivatedMessage sent;
  BrokerReactivatedMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_broker_reactivated_message(&sent);
  assert(encode_broker_reactivated_message(&sent, wire, 0) == 37);
  assert(decode_broker_reactivated_message(&got, wire, 0) == 37);
  equal_broker_reactivated_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_broker_reactivated_message(&got, wire, 0) == 37);
  assert(encode_broker_reactivated_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- St Auction Inq Info: 36 bytes ------------------------------------------- */

/* ST_AUCTION_INQ_INFO */
typedef struct {
  uint8_t token[4];              /* bytes 0 to 3 */
  uint8_t auction_number[2];     /* bytes 4 to 5 */
  uint8_t auction_status[2];     /* bytes 6 to 7 */
  uint8_t initiator_type[2];     /* bytes 8 to 9 */
  uint8_t total_buy_qty[4];      /* bytes 10 to 13 */
  uint8_t best_buy_price[4];     /* bytes 14 to 17 */
  uint8_t total_sell_qty[4];     /* bytes 18 to 21 */
  uint8_t best_sell_price[4];    /* bytes 22 to 25 */
  uint8_t auction_price[4];      /* bytes 26 to 29 */
  uint8_t auction_qty[4];        /* bytes 30 to 33 */
  uint8_t settlement_period[2];  /* bytes 34 to 35 */
} StAuctionInqInfo;

/* any St Auction Inq Info at all: every byte one the checker chooses */
static void any_st_auction_inq_info(StAuctionInqInfo *record) {
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->initiator_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_buy_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_buy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_sell_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->best_sell_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->settlement_period[i] = arbitrary(); }
}

/* St Auction Inq Info to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_st_auction_inq_info(const StAuctionInqInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->initiator_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_buy_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_buy_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_sell_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->best_sell_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settlement_period[i]; }

  return at;
}

/* St Auction Inq Info off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_st_auction_inq_info(StAuctionInqInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->initiator_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_buy_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_buy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_sell_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->best_sell_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->settlement_period[i] = wire[at++]; }

  return at;
}

/* what was read of St Auction Inq Info is what was written, byte for byte */
static void equal_st_auction_inq_info(const StAuctionInqInfo *read, const StAuctionInqInfo *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_number[i] == written->auction_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_status[i] == written->auction_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->initiator_type[i] == written->initiator_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_buy_qty[i] == written->total_buy_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_buy_price[i] == written->best_buy_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_sell_qty[i] == written->total_sell_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->best_sell_price[i] == written->best_sell_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_price[i] == written->auction_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_qty[i] == written->auction_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->settlement_period[i] == written->settlement_period[i]); }
}

/* St Auction Inq Info: written and read back, then read and written back */
static void check_st_auction_inq_info(void) {
  StAuctionInqInfo sent;
  StAuctionInqInfo got;
  uint8_t wire[36];
  uint8_t again[36];

  any_st_auction_inq_info(&sent);
  assert(encode_st_auction_inq_info(&sent, wire, 0) == 36);
  assert(decode_st_auction_inq_info(&got, wire, 0) == 36);
  equal_st_auction_inq_info(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_st_auction_inq_info(&got, wire, 0) == 36);
  assert(encode_st_auction_inq_info(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Activity Message: 36 bytes -------------------------------------- */

/* Sent as BCAST_AUCTION_INQUIRY_OUT for any auction related activity in CM */
typedef struct {
  StAuctionInqInfo st_auction_inq_info;  /* bytes 0 to 35 */
} AuctionActivityMessage;

/* any Auction Activity Message at all: every byte one the checker chooses */
static void any_auction_activity_message(AuctionActivityMessage *record) {
  any_st_auction_inq_info(&record->st_auction_inq_info);
}

/* Auction Activity Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_auction_activity_message(const AuctionActivityMessage *record, uint8_t *wire, size_t at) {
  at = encode_st_auction_inq_info(&record->st_auction_inq_info, wire, at);

  return at;
}

/* Auction Activity Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_auction_activity_message(AuctionActivityMessage *record, const uint8_t *wire, size_t at) {
  at = decode_st_auction_inq_info(&record->st_auction_inq_info, wire, at);

  return at;
}

/* what was read of Auction Activity Message is what was written, byte for byte */
static void equal_auction_activity_message(const AuctionActivityMessage *read, const AuctionActivityMessage *written) {
  equal_st_auction_inq_info(&read->st_auction_inq_info, &written->st_auction_inq_info);
}

/* Auction Activity Message: written and read back, then read and written back */
static void check_auction_activity_message(void) {
  AuctionActivityMessage sent;
  AuctionActivityMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_auction_activity_message(&sent);
  assert(encode_auction_activity_message(&sent, wire, 0) == 36);
  assert(decode_auction_activity_message(&got, wire, 0) == 36);
  equal_auction_activity_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_activity_message(&got, wire, 0) == 36);
  assert(encode_auction_activity_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Open Message: 20 bytes ----------------------------------------- */

/* Sent as SECURITY_OPEN_PRICE with the open price of a security when the market opens */
typedef struct {
  SecInfo sec_info;          /* bytes 0 to 11 */
  uint8_t token[4];          /* bytes 12 to 15 */
  uint8_t opening_price[4];  /* bytes 16 to 19 */
} SecurityOpenMessage;

/* any Security Open Message at all: every byte one the checker chooses */
static void any_security_open_message(SecurityOpenMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = arbitrary(); }
}

/* Security Open Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_security_open_message(const SecurityOpenMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_price[i]; }

  return at;
}

/* Security Open Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_security_open_message(SecurityOpenMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = wire[at++]; }

  return at;
}

/* what was read of Security Open Message is what was written, byte for byte */
static void equal_security_open_message(const SecurityOpenMessage *read, const SecurityOpenMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
}

/* Security Open Message: written and read back, then read and written back */
static void check_security_open_message(void) {
  SecurityOpenMessage sent;
  SecurityOpenMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_security_open_message(&sent);
  assert(encode_security_open_message(&sent, wire, 0) == 20);
  assert(decode_security_open_message(&got, wire, 0) == 20);
  equal_security_open_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_message(&got, wire, 0) == 20);
  assert(encode_security_open_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Report Header Body: 67 bytes -------------------------------------------- */

/* Report Header Body */
typedef struct {
  uint8_t reserved_1;        /* byte 0 */
  uint8_t report_date[4];    /* bytes 1 to 4 */
  uint8_t user_type[2];      /* bytes 5 to 6 */
  uint8_t broker_id[5];      /* bytes 7 to 11 */
  uint8_t broker_name[25];   /* bytes 12 to 36 */
  uint8_t trader_number[4];  /* bytes 37 to 40 */
  uint8_t trader_name[26];   /* bytes 41 to 66 */
} ReportHeaderBody;

/* any Report Header Body at all: every byte one the checker chooses */
static void any_report_header_body(ReportHeaderBody *record) {
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->broker_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = arbitrary(); }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = arbitrary(); }
}

/* Report Header Body to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_report_header_body(const ReportHeaderBody *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->report_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_type[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->broker_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_number[i]; }
  for (size_t i = 0; i < 26; i++) { wire[at++] = record->trader_name[i]; }

  return at;
}

/* Report Header Body off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_report_header_body(ReportHeaderBody *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->report_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_type[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->broker_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_number[i] = wire[at++]; }
  for (size_t i = 0; i < 26; i++) { record->trader_name[i] = wire[at++]; }

  return at;
}

/* what was read of Report Header Body is what was written, byte for byte */
static void equal_report_header_body(const ReportHeaderBody *read, const ReportHeaderBody *written) {
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->report_date[i] == written->report_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_type[i] == written->user_type[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->broker_name[i] == written->broker_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_number[i] == written->trader_number[i]); }
  for (size_t i = 0; i < 26; i++) { assert(read->trader_name[i] == written->trader_name[i]); }
}

/* Report Header Body: written and read back, then read and written back */
static void check_report_header_body(void) {
  ReportHeaderBody sent;
  ReportHeaderBody got;
  uint8_t wire[67];
  uint8_t again[67];

  any_report_header_body(&sent);
  assert(encode_report_header_body(&sent, wire, 0) == 67);
  assert(decode_report_header_body(&got, wire, 0) == 67);
  equal_report_header_body(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_report_header_body(&got, wire, 0) == 67);
  assert(encode_report_header_body(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Report Trailer Body: 5 bytes -------------------------------------------- */

/* Report Trailer Body */
typedef struct {
  uint8_t number_of_records_long[4];  /* bytes 0 to 3 */
  uint8_t reserved_1;                 /* byte 4 */
} ReportTrailerBody;

/* any Report Trailer Body at all: every byte one the checker chooses */
static void any_report_trailer_body(ReportTrailerBody *record) {
  for (size_t i = 0; i < 4; i++) { record->number_of_records_long[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Report Trailer Body to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_report_trailer_body(const ReportTrailerBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_records_long[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Report Trailer Body off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_report_trailer_body(ReportTrailerBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->number_of_records_long[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Report Trailer Body is what was written, byte for byte */
static void equal_report_trailer_body(const ReportTrailerBody *read, const ReportTrailerBody *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_records_long[i] == written->number_of_records_long[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Report Trailer Body: written and read back, then read and written back */
static void check_report_trailer_body(void) {
  ReportTrailerBody sent;
  ReportTrailerBody got;
  uint8_t wire[5];
  uint8_t again[5];

  any_report_trailer_body(&sent);
  assert(encode_report_trailer_body(&sent, wire, 0) == 5);
  assert(decode_report_trailer_body(&got, wire, 0) == 5);
  equal_report_trailer_body(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_report_trailer_body(&got, wire, 0) == 5);
  assert(encode_report_trailer_body(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contingency Broadcast Message: 204 bytes -------------------------------- */

/* Sent as BCAST_CONTI_MSG at the start and the end of an outage of one or more streams */
typedef struct {
  uint8_t stream_number[2];   /* bytes 0 to 1 */
  uint8_t outage_status[2];   /* bytes 2 to 3 */
  uint8_t reserved_200[200];  /* bytes 4 to 203 */
} ContingencyBroadcastMessage;

/* any Contingency Broadcast Message at all: every byte one the checker chooses */
static void any_contingency_broadcast_message(ContingencyBroadcastMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->stream_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->outage_status[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->reserved_200[i] = arbitrary(); }
}

/* Contingency Broadcast Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_contingency_broadcast_message(const ContingencyBroadcastMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stream_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->outage_status[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->reserved_200[i]; }

  return at;
}

/* Contingency Broadcast Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_contingency_broadcast_message(ContingencyBroadcastMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->stream_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->outage_status[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->reserved_200[i] = wire[at++]; }

  return at;
}

/* what was read of Contingency Broadcast Message is what was written, byte for byte */
static void equal_contingency_broadcast_message(const ContingencyBroadcastMessage *read, const ContingencyBroadcastMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->stream_number[i] == written->stream_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->outage_status[i] == written->outage_status[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->reserved_200[i] == written->reserved_200[i]); }
}

/* Contingency Broadcast Message: written and read back, then read and written back */
static void check_contingency_broadcast_message(void) {
  ContingencyBroadcastMessage sent;
  ContingencyBroadcastMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_contingency_broadcast_message(&sent);
  assert(encode_contingency_broadcast_message(&sent, wire, 0) == 204);
  assert(decode_contingency_broadcast_message(&got, wire, 0) == 204);
  equal_contingency_broadcast_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_contingency_broadcast_message(&got, wire, 0) == 204);
  assert(encode_contingency_broadcast_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_bcast_header();
  check_sec_info();
  check_change_participant_status_message();
  check_turnover_limit_exceeded_message();
  check_broker_reactivated_message();
  check_st_auction_inq_info();
  check_auction_activity_message();
  check_security_open_message();
  check_report_header_body();
  check_report_trailer_body();
  check_contingency_broadcast_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
