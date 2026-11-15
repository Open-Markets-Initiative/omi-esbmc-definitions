// nse/nsefo/broadcast/NseFo_Broadcast_v9_50.c
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

/* ---- Security Open Price Message: 20 bytes ----------------------------------- */

/* Carries the open price of a security once it opens */
typedef struct {
  uint8_t symbol[10];        /* bytes 0 to 9 */
  uint8_t series[2];         /* bytes 10 to 11 */
  uint8_t token[4];          /* bytes 12 to 15 */
  uint8_t opening_price[4];  /* bytes 16 to 19 */
} SecurityOpenPriceMessage;

/* any Security Open Price Message at all: every byte one the checker chooses */
static void any_security_open_price_message(SecurityOpenPriceMessage *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = arbitrary(); }
}

/* Security Open Price Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_security_open_price_message(const SecurityOpenPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_price[i]; }

  return at;
}

/* Security Open Price Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_security_open_price_message(SecurityOpenPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = wire[at++]; }

  return at;
}

/* what was read of Security Open Price Message is what was written, byte for byte */
static void equal_security_open_price_message(const SecurityOpenPriceMessage *read, const SecurityOpenPriceMessage *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
}

/* Security Open Price Message: written and read back, then read and written back */
static void check_security_open_price_message(void) {
  SecurityOpenPriceMessage sent;
  SecurityOpenPriceMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_security_open_price_message(&sent);
  assert(encode_security_open_price_message(&sent, wire, 0) == 20);
  assert(decode_security_open_price_message(&got, wire, 0) == 20);
  equal_security_open_price_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_security_open_price_message(&got, wire, 0) == 20);
  assert(encode_security_open_price_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sec Info: 30 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t instrument_name[6];  /* bytes 0 to 5 */
  uint8_t symbol[10];          /* bytes 6 to 15 */
  uint8_t series[2];           /* bytes 16 to 17 */
  uint8_t expiry_date[4];      /* bytes 18 to 21 */
  uint8_t strike_price[4];     /* bytes 22 to 25 */
  uint8_t option_type[2];      /* bytes 26 to 27 */
  uint8_t ca_level[2];         /* bytes 28 to 29 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = arbitrary(); }
}

/* Sec Info to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ca_level[i]; }

  return at;
}

/* Sec Info off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ca_level[i] == written->ca_level[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[30];
  uint8_t again[30];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 30);
  assert(decode_sec_info(&got, wire, 0) == 30);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 30);
  assert(encode_sec_info(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Master Change Message: 38 bytes ------------------------------ */

/* Broadcasts a change to the instrument master */
typedef struct {
  uint8_t instrument_id[2];            /* bytes 0 to 1 */
  uint8_t instrument_name[6];          /* bytes 2 to 7 */
  uint8_t instrument_description[25];  /* bytes 8 to 32 */
  uint8_t instrument_update_time[4];   /* bytes 33 to 36 */
  uint8_t delete_flag;                 /* byte 37 */
} InstrumentMasterChangeMessage;

/* any Instrument Master Change Message at all: every byte one the checker chooses */
static void any_instrument_master_change_message(InstrumentMasterChangeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->instrument_description[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_update_time[i] = arbitrary(); }
  record->delete_flag = arbitrary();
}

/* Instrument Master Change Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_instrument_master_change_message(const InstrumentMasterChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->instrument_description[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_update_time[i]; }
  wire[at++] = record->delete_flag;

  return at;
}

/* Instrument Master Change Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_instrument_master_change_message(InstrumentMasterChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->instrument_description[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_update_time[i] = wire[at++]; }
  record->delete_flag = wire[at++];

  return at;
}

/* what was read of Instrument Master Change Message is what was written, byte for byte */
static void equal_instrument_master_change_message(const InstrumentMasterChangeMessage *read, const InstrumentMasterChangeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->instrument_description[i] == written->instrument_description[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_update_time[i] == written->instrument_update_time[i]); }
  assert(read->delete_flag == written->delete_flag);
}

/* Instrument Master Change Message: written and read back, then read and written back */
static void check_instrument_master_change_message(void) {
  InstrumentMasterChangeMessage sent;
  InstrumentMasterChangeMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_instrument_master_change_message(&sent);
  assert(encode_instrument_master_change_message(&sent, wire, 0) == 38);
  assert(decode_instrument_master_change_message(&got, wire, 0) == 38);
  equal_instrument_master_change_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_master_change_message(&got, wire, 0) == 38);
  assert(encode_instrument_master_change_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Participant Master Change Message: 43 bytes ----------------------------- */

/* Broadcasts a change to the participant master */
typedef struct {
  uint8_t participant_id[12];               /* bytes 0 to 11 */
  uint8_t participant_name[25];             /* bytes 12 to 36 */
  uint8_t participant_status;               /* byte 37 */
  uint8_t participant_update_date_time[4];  /* bytes 38 to 41 */
  uint8_t delete_flag;                      /* byte 42 */
} ParticipantMasterChangeMessage;

/* any Participant Master Change Message at all: every byte one the checker chooses */
static void any_participant_master_change_message(ParticipantMasterChangeMessage *record) {
  for (size_t i = 0; i < 12; i++) { record->participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->participant_name[i] = arbitrary(); }
  record->participant_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->participant_update_date_time[i] = arbitrary(); }
  record->delete_flag = arbitrary();
}

/* Participant Master Change Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_participant_master_change_message(const ParticipantMasterChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->participant_name[i]; }
  wire[at++] = record->participant_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->participant_update_date_time[i]; }
  wire[at++] = record->delete_flag;

  return at;
}

/* Participant Master Change Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_participant_master_change_message(ParticipantMasterChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->participant_name[i] = wire[at++]; }
  record->participant_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->participant_update_date_time[i] = wire[at++]; }
  record->delete_flag = wire[at++];

  return at;
}

/* what was read of Participant Master Change Message is what was written, byte for byte */
static void equal_participant_master_change_message(const ParticipantMasterChangeMessage *read, const ParticipantMasterChangeMessage *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->participant_id[i] == written->participant_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->participant_name[i] == written->participant_name[i]); }
  assert(read->participant_status == written->participant_status);
  for (size_t i = 0; i < 4; i++) { assert(read->participant_update_date_time[i] == written->participant_update_date_time[i]); }
  assert(read->delete_flag == written->delete_flag);
}

/* Participant Master Change Message: written and read back, then read and written back */
static void check_participant_master_change_message(void) {
  ParticipantMasterChangeMessage sent;
  ParticipantMasterChangeMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_participant_master_change_message(&sent);
  assert(encode_participant_master_change_message(&sent, wire, 0) == 43);
  assert(decode_participant_master_change_message(&got, wire, 0) == 43);
  equal_participant_master_change_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_participant_master_change_message(&got, wire, 0) == 43);
  assert(encode_participant_master_change_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover Limit Exceeded Body: 58 bytes ---------------------------------- */

/* Turnover Limit Exceeded Body */
typedef struct {
  uint8_t broker_code[5];          /* bytes 0 to 4 */
  uint8_t counter_broker_code[5];  /* bytes 5 to 9 */
  uint8_t warning_type[2];         /* bytes 10 to 11 */
  uint8_t token[4];                /* bytes 12 to 15 */
  uint8_t instrument_name[6];      /* bytes 16 to 21 */
  uint8_t symbol[10];              /* bytes 22 to 31 */
  uint8_t expiry_date[4];          /* bytes 32 to 35 */
  uint8_t strike_price[4];         /* bytes 36 to 39 */
  uint8_t option_type[2];          /* bytes 40 to 41 */
  uint8_t ca_level[2];             /* bytes 42 to 43 */
  uint8_t trade_number[4];         /* bytes 44 to 47 */
  uint8_t trade_price[4];          /* bytes 48 to 51 */
  uint8_t trade_volume[4];         /* bytes 52 to 55 */
  uint8_t final;                   /* byte 56 */
  uint8_t filler;                  /* byte 57 */
} TurnoverLimitExceededBody;

/* any Turnover Limit Exceeded Body at all: every byte one the checker chooses */
static void any_turnover_limit_exceeded_body(TurnoverLimitExceededBody *record) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = arbitrary(); }
  record->final = arbitrary();
  record->filler = arbitrary();
}

/* Turnover Limit Exceeded Body to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_turnover_limit_exceeded_body(const TurnoverLimitExceededBody *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_code[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counter_broker_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->warning_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->instrument_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expiry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->option_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ca_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_volume[i]; }
  wire[at++] = record->final;
  wire[at++] = record->filler;

  return at;
}

/* Turnover Limit Exceeded Body off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_turnover_limit_exceeded_body(TurnoverLimitExceededBody *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counter_broker_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->warning_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->instrument_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->option_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ca_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_volume[i] = wire[at++]; }
  record->final = wire[at++];
  record->filler = wire[at++];

  return at;
}

/* what was read of Turnover Limit Exceeded Body is what was written, byte for byte */
static void equal_turnover_limit_exceeded_body(const TurnoverLimitExceededBody *read, const TurnoverLimitExceededBody *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->broker_code[i] == written->broker_code[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counter_broker_code[i] == written->counter_broker_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->warning_type[i] == written->warning_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expiry_date[i] == written->expiry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->option_type[i] == written->option_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ca_level[i] == written->ca_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_volume[i] == written->trade_volume[i]); }
  assert(read->final == written->final);
  assert(read->filler == written->filler);
}

/* Turnover Limit Exceeded Body: written and read back, then read and written back */
static void check_turnover_limit_exceeded_body(void) {
  TurnoverLimitExceededBody sent;
  TurnoverLimitExceededBody got;
  uint8_t wire[58];
  uint8_t again[58];

  any_turnover_limit_exceeded_body(&sent);
  assert(encode_turnover_limit_exceeded_body(&sent, wire, 0) == 58);
  assert(decode_turnover_limit_exceeded_body(&got, wire, 0) == 58);
  equal_turnover_limit_exceeded_body(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover_limit_exceeded_body(&got, wire, 0) == 58);
  assert(encode_turnover_limit_exceeded_body(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_bcast_header();
  check_security_open_price_message();
  check_sec_info();
  check_instrument_master_change_message();
  check_participant_master_change_message();
  check_turnover_limit_exceeded_body();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
