// qse/qsecash/marketdata/QseCash_MarketData_v2_6.c
/*
 * Qatar Stock Exchange Qse Cash Market Data
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
 *   - a field filling what is left of what holds it
 *   - a run filling what frames it
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

/* ---- Packet Header: 16 bytes ------------------------------------------------- */

/* All messages contain a common packet header, so that a client implements line level protocol processing once and then develops parsing algorithms only for its choice of message */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_type[2];             /* bytes 2 to 3 */
  uint8_t packet_sequence_number[4];  /* bytes 4 to 7 */
  uint8_t send_time[4];               /* bytes 8 to 11 */
  uint8_t service_id[2];              /* bytes 12 to 13 */
  uint8_t delivery_flag;              /* byte 14 */
  uint8_t number_msg_entries;         /* byte 15 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->packet_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->service_id[i] = arbitrary(); }
  record->delivery_flag = arbitrary();
  record->number_msg_entries = arbitrary();
}

/* Packet Header to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->send_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->service_id[i]; }
  wire[at++] = record->delivery_flag;
  wire[at++] = record->number_msg_entries;

  return at;
}

/* Packet Header off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->packet_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->service_id[i] = wire[at++]; }
  record->delivery_flag = wire[at++];
  record->number_msg_entries = wire[at++];

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->packet_type[i] == written->packet_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->send_time[i] == written->send_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->service_id[i] == written->service_id[i]); }
  assert(read->delivery_flag == written->delivery_flag);
  assert(read->number_msg_entries == written->number_msg_entries);
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[16];
  uint8_t again[16];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 16);
  assert(decode_packet_header(&got, wire, 0) == 16);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 16);
  assert(encode_packet_header(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 4 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type[2];  /* bytes 2 to 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock State Change Message: 48 bytes ------------------------------------ */

/* A Stock State Change message is generated by the trading engines to announce a change in the state of an instrument. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t system_id[4];               /* bytes 12 to 15 */
  uint8_t source_time_micro_secs[2];  /* bytes 16 to 17 */
  uint8_t filler_binary_int_2[2];     /* bytes 18 to 19 */
  uint8_t start_date_halting[8];      /* bytes 20 to 27 */
  uint8_t start_time_halting[6];      /* bytes 28 to 33 */
  uint8_t prog_opening_time[6];       /* bytes 34 to 39 */
  uint8_t order_entry_rejection;      /* byte 40 */
  uint8_t instrument_state;           /* byte 41 */
  uint8_t instrument_trading_status;  /* byte 42 */
  uint8_t halt_reason;                /* byte 43 */
  uint8_t action_affecting_state;     /* byte 44 */
  uint8_t instrument_state_tcs;       /* byte 45 */
  uint8_t period_side;                /* byte 46 */
  uint8_t filler_binary_int_1;        /* byte 47 */
} StockStateChangeMessage;

/* any Stock State Change Message at all: every byte one the checker chooses */
static void any_stock_state_change_message(StockStateChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->start_date_halting[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->start_time_halting[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->prog_opening_time[i] = arbitrary(); }
  record->order_entry_rejection = arbitrary();
  record->instrument_state = arbitrary();
  record->instrument_trading_status = arbitrary();
  record->halt_reason = arbitrary();
  record->action_affecting_state = arbitrary();
  record->instrument_state_tcs = arbitrary();
  record->period_side = arbitrary();
  record->filler_binary_int_1 = arbitrary();
}

/* Stock State Change Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_stock_state_change_message(const StockStateChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_binary_int_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_date_halting[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->start_time_halting[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->prog_opening_time[i]; }
  wire[at++] = record->order_entry_rejection;
  wire[at++] = record->instrument_state;
  wire[at++] = record->instrument_trading_status;
  wire[at++] = record->halt_reason;
  wire[at++] = record->action_affecting_state;
  wire[at++] = record->instrument_state_tcs;
  wire[at++] = record->period_side;
  wire[at++] = record->filler_binary_int_1;

  return at;
}

/* Stock State Change Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_stock_state_change_message(StockStateChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->start_date_halting[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->start_time_halting[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->prog_opening_time[i] = wire[at++]; }
  record->order_entry_rejection = wire[at++];
  record->instrument_state = wire[at++];
  record->instrument_trading_status = wire[at++];
  record->halt_reason = wire[at++];
  record->action_affecting_state = wire[at++];
  record->instrument_state_tcs = wire[at++];
  record->period_side = wire[at++];
  record->filler_binary_int_1 = wire[at++];

  return at;
}

/* what was read of Stock State Change Message is what was written, byte for byte */
static void equal_stock_state_change_message(const StockStateChangeMessage *read, const StockStateChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_binary_int_2[i] == written->filler_binary_int_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->start_date_halting[i] == written->start_date_halting[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->start_time_halting[i] == written->start_time_halting[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->prog_opening_time[i] == written->prog_opening_time[i]); }
  assert(read->order_entry_rejection == written->order_entry_rejection);
  assert(read->instrument_state == written->instrument_state);
  assert(read->instrument_trading_status == written->instrument_trading_status);
  assert(read->halt_reason == written->halt_reason);
  assert(read->action_affecting_state == written->action_affecting_state);
  assert(read->instrument_state_tcs == written->instrument_state_tcs);
  assert(read->period_side == written->period_side);
  assert(read->filler_binary_int_1 == written->filler_binary_int_1);
}

/* Stock State Change Message: written and read back, then read and written back */
static void check_stock_state_change_message(void) {
  StockStateChangeMessage sent;
  StockStateChangeMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_stock_state_change_message(&sent);
  assert(encode_stock_state_change_message(&sent, wire, 0) == 48);
  assert(decode_stock_state_change_message(&got, wire, 0) == 48);
  equal_stock_state_change_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_state_change_message(&got, wire, 0) == 48);
  assert(encode_stock_state_change_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Class State Change Message: 24 bytes ------------------------------------ */

/* A Class State Change message announces a change in the trading market phase of a class or instrument group, which instruments belonging to it inherit. */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t instrument_group_code[3];   /* bytes 14 to 16 */
  uint8_t instrument_group_state;     /* byte 17 */
  uint8_t session_type;               /* byte 18 */
  uint8_t filler_binary_int_1;        /* byte 19 */
  uint8_t class_state[4];             /* bytes 20 to 23 */
} ClassStateChangeMessage;

/* any Class State Change Message at all: every byte one the checker chooses */
static void any_class_state_change_message(ClassStateChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = arbitrary(); }
  record->instrument_group_state = arbitrary();
  record->session_type = arbitrary();
  record->filler_binary_int_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->class_state[i] = arbitrary(); }
}

/* Class State Change Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_class_state_change_message(const ClassStateChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->instrument_group_code[i]; }
  wire[at++] = record->instrument_group_state;
  wire[at++] = record->session_type;
  wire[at++] = record->filler_binary_int_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->class_state[i]; }

  return at;
}

/* Class State Change Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_class_state_change_message(ClassStateChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = wire[at++]; }
  record->instrument_group_state = wire[at++];
  record->session_type = wire[at++];
  record->filler_binary_int_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->class_state[i] = wire[at++]; }

  return at;
}

/* what was read of Class State Change Message is what was written, byte for byte */
static void equal_class_state_change_message(const ClassStateChangeMessage *read, const ClassStateChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->instrument_group_code[i] == written->instrument_group_code[i]); }
  assert(read->instrument_group_state == written->instrument_group_state);
  assert(read->session_type == written->session_type);
  assert(read->filler_binary_int_1 == written->filler_binary_int_1);
  for (size_t i = 0; i < 4; i++) { assert(read->class_state[i] == written->class_state[i]); }
}

/* Class State Change Message: written and read back, then read and written back */
static void check_class_state_change_message(void) {
  ClassStateChangeMessage sent;
  ClassStateChangeMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_class_state_change_message(&sent);
  assert(encode_class_state_change_message(&sent, wire, 0) == 24);
  assert(decode_class_state_change_message(&got, wire, 0) == 24);
  equal_class_state_change_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_class_state_change_message(&got, wire, 0) == 24);
  assert(encode_class_state_change_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mail Message: 964 bytes ------------------------------------------------- */

/* A Mail message carries a free text notice broadcast to market participants. */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t e_mail_msg_number[2];       /* bytes 14 to 15 */
  uint8_t number_of_message[2];       /* bytes 16 to 17 */
  uint8_t sequence_number[2];         /* bytes 18 to 19 */
  uint8_t instrument_group_code[3];   /* bytes 20 to 22 */
  uint8_t filler_ascii_str_1;         /* byte 23 */
  uint8_t priority_indicator;         /* byte 24 */
  uint8_t type_of_message;            /* byte 25 */
  uint8_t address_type[2];            /* bytes 26 to 27 */
  uint8_t title[80];                  /* bytes 28 to 107 */
  uint8_t text[854];                  /* bytes 108 to 961 */
  uint8_t filler_ascii_str_2[2];      /* bytes 962 to 963 */
} MailMessage;

/* any Mail Message at all: every byte one the checker chooses */
static void any_mail_message(MailMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->e_mail_msg_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_message[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = arbitrary(); }
  record->filler_ascii_str_1 = arbitrary();
  record->priority_indicator = arbitrary();
  record->type_of_message = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->address_type[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->title[i] = arbitrary(); }
  for (size_t i = 0; i < 854; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = arbitrary(); }
}

/* Mail Message to the wire: 964 bytes from at, returning where the next byte goes */
static size_t encode_mail_message(const MailMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->e_mail_msg_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_message[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->instrument_group_code[i]; }
  wire[at++] = record->filler_ascii_str_1;
  wire[at++] = record->priority_indicator;
  wire[at++] = record->type_of_message;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->address_type[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->title[i]; }
  for (size_t i = 0; i < 854; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_str_2[i]; }

  return at;
}

/* Mail Message off the wire: 964 bytes from at, returning where the next byte lies */
static size_t decode_mail_message(MailMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->e_mail_msg_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_message[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = wire[at++]; }
  record->filler_ascii_str_1 = wire[at++];
  record->priority_indicator = wire[at++];
  record->type_of_message = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->address_type[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->title[i] = wire[at++]; }
  for (size_t i = 0; i < 854; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = wire[at++]; }

  return at;
}

/* what was read of Mail Message is what was written, byte for byte */
static void equal_mail_message(const MailMessage *read, const MailMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->e_mail_msg_number[i] == written->e_mail_msg_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_message[i] == written->number_of_message[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->instrument_group_code[i] == written->instrument_group_code[i]); }
  assert(read->filler_ascii_str_1 == written->filler_ascii_str_1);
  assert(read->priority_indicator == written->priority_indicator);
  assert(read->type_of_message == written->type_of_message);
  for (size_t i = 0; i < 2; i++) { assert(read->address_type[i] == written->address_type[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->title[i] == written->title[i]); }
  for (size_t i = 0; i < 854; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_str_2[i] == written->filler_ascii_str_2[i]); }
}

/* Mail Message: written and read back, then read and written back */
static void check_mail_message(void) {
  MailMessage sent;
  MailMessage got;
  uint8_t wire[964];
  uint8_t again[964];

  any_mail_message(&sent);
  assert(encode_mail_message(&sent, wire, 0) == 964);
  assert(decode_mail_message(&got, wire, 0) == 964);
  equal_mail_message(&got, &sent);

  for (size_t i = 0; i < 964; i++) { wire[i] = arbitrary(); }
  assert(decode_mail_message(&got, wire, 0) == 964);
  assert(encode_mail_message(&got, again, 0) == 964);
  for (size_t i = 0; i < 964; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Matching Price Message: 32 bytes ----------------------------- */

/* An Indicative Matching Price message gives the price at which the instrument would open, were the opening to occur at this moment. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t im_price[4];                /* bytes 12 to 15 */
  uint8_t variation[4];               /* bytes 16 to 19 */
  uint8_t system_id[4];               /* bytes 20 to 23 */
  uint8_t source_time_micro_secs[2];  /* bytes 24 to 25 */
  uint8_t price_scale_code;           /* byte 26 */
  uint8_t variation_scale_code;       /* byte 27 */
  uint8_t im_volume[4];               /* bytes 28 to 31 */
} IndicativeMatchingPriceMessage;

/* any Indicative Matching Price Message at all: every byte one the checker chooses */
static void any_indicative_matching_price_message(IndicativeMatchingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->im_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->im_volume[i] = arbitrary(); }
}

/* Indicative Matching Price Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_indicative_matching_price_message(const IndicativeMatchingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->im_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->variation_scale_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->im_volume[i]; }

  return at;
}

/* Indicative Matching Price Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_indicative_matching_price_message(IndicativeMatchingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->im_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->im_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Indicative Matching Price Message is what was written, byte for byte */
static void equal_indicative_matching_price_message(const IndicativeMatchingPriceMessage *read, const IndicativeMatchingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->im_price[i] == written->im_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation[i] == written->variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
  for (size_t i = 0; i < 4; i++) { assert(read->im_volume[i] == written->im_volume[i]); }
}

/* Indicative Matching Price Message: written and read back, then read and written back */
static void check_indicative_matching_price_message(void) {
  IndicativeMatchingPriceMessage sent;
  IndicativeMatchingPriceMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_indicative_matching_price_message(&sent);
  assert(encode_indicative_matching_price_message(&sent, wire, 0) == 32);
  assert(decode_indicative_matching_price_message(&got, wire, 0) == 32);
  equal_indicative_matching_price_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_indicative_matching_price_message(&got, wire, 0) == 32);
  assert(encode_indicative_matching_price_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collars Message: 32 bytes ----------------------------------------------- */

/* A Collars message gives the upper and lower price thresholds beyond which an instrument is reserved. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t high_collar[4];             /* bytes 12 to 15 */
  uint8_t low_collar[4];              /* bytes 16 to 19 */
  uint8_t system_id[4];               /* bytes 20 to 23 */
  uint8_t source_time_micro_secs[2];  /* bytes 24 to 25 */
  uint8_t high_scale_code;            /* byte 26 */
  uint8_t low_scale_code;             /* byte 27 */
  uint8_t collar_type;                /* byte 28 */
  uint8_t filler_ascii_str_3[3];      /* bytes 29 to 31 */
} CollarsMessage;

/* any Collars Message at all: every byte one the checker chooses */
static void any_collars_message(CollarsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_collar[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->high_scale_code = arbitrary();
  record->low_scale_code = arbitrary();
  record->collar_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* Collars Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_collars_message(const CollarsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_collar[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_collar[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->high_scale_code;
  wire[at++] = record->low_scale_code;
  wire[at++] = record->collar_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* Collars Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_collars_message(CollarsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_collar[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->high_scale_code = wire[at++];
  record->low_scale_code = wire[at++];
  record->collar_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of Collars Message is what was written, byte for byte */
static void equal_collars_message(const CollarsMessage *read, const CollarsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_collar[i] == written->high_collar[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_collar[i] == written->low_collar[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->high_scale_code == written->high_scale_code);
  assert(read->low_scale_code == written->low_scale_code);
  assert(read->collar_type == written->collar_type);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* Collars Message: written and read back, then read and written back */
static void check_collars_message(void) {
  CollarsMessage sent;
  CollarsMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_collars_message(&sent);
  assert(encode_collars_message(&sent, wire, 0) == 32);
  assert(decode_collars_message(&got, wire, 0) == 32);
  equal_collars_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_collars_message(&got, wire, 0) == 32);
  assert(encode_collars_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Timetable Message: 80 bytes ------------------------------------- */

/* A Session Timetable message gives the timetable of the trading session for a group of instruments. */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t instrument_group_code[3];   /* bytes 14 to 16 */
  uint8_t session_type;               /* byte 17 */
  uint8_t time_pre_opening_1[6];      /* bytes 18 to 23 */
  uint8_t time_opening_1[6];          /* bytes 24 to 29 */
  uint8_t time_closing_1[6];          /* bytes 30 to 35 */
  uint8_t time_pre_opening_2[6];      /* bytes 36 to 41 */
  uint8_t time_opening_2[6];          /* bytes 42 to 47 */
  uint8_t time_closing_2[6];          /* bytes 48 to 53 */
  uint8_t time_pre_opening_3[6];      /* bytes 54 to 59 */
  uint8_t time_opening_3[6];          /* bytes 60 to 65 */
  uint8_t time_closing_3[6];          /* bytes 66 to 71 */
  uint8_t eod_time[6];                /* bytes 72 to 77 */
  uint8_t filler_ascii_str_2[2];      /* bytes 78 to 79 */
} SessionTimetableMessage;

/* any Session Timetable Message at all: every byte one the checker chooses */
static void any_session_timetable_message(SessionTimetableMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = arbitrary(); }
  record->session_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_opening_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_closing_1[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_opening_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_closing_2[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_3[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_opening_3[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_closing_3[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->eod_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = arbitrary(); }
}

/* Session Timetable Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_session_timetable_message(const SessionTimetableMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->instrument_group_code[i]; }
  wire[at++] = record->session_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_pre_opening_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_opening_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_closing_1[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_pre_opening_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_opening_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_closing_2[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_pre_opening_3[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_opening_3[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_closing_3[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->eod_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_str_2[i]; }

  return at;
}

/* Session Timetable Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_session_timetable_message(SessionTimetableMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = wire[at++]; }
  record->session_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_opening_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_closing_1[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_opening_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_closing_2[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_pre_opening_3[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_opening_3[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_closing_3[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->eod_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = wire[at++]; }

  return at;
}

/* what was read of Session Timetable Message is what was written, byte for byte */
static void equal_session_timetable_message(const SessionTimetableMessage *read, const SessionTimetableMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->instrument_group_code[i] == written->instrument_group_code[i]); }
  assert(read->session_type == written->session_type);
  for (size_t i = 0; i < 6; i++) { assert(read->time_pre_opening_1[i] == written->time_pre_opening_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_opening_1[i] == written->time_opening_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_closing_1[i] == written->time_closing_1[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_pre_opening_2[i] == written->time_pre_opening_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_opening_2[i] == written->time_opening_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_closing_2[i] == written->time_closing_2[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_pre_opening_3[i] == written->time_pre_opening_3[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_opening_3[i] == written->time_opening_3[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_closing_3[i] == written->time_closing_3[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->eod_time[i] == written->eod_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_str_2[i] == written->filler_ascii_str_2[i]); }
}

/* Session Timetable Message: written and read back, then read and written back */
static void check_session_timetable_message(void) {
  SessionTimetableMessage sent;
  SessionTimetableMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_session_timetable_message(&sent);
  assert(encode_session_timetable_message(&sent, wire, 0) == 80);
  assert(decode_session_timetable_message(&got, wire, 0) == 80);
  equal_session_timetable_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_session_timetable_message(&got, wire, 0) == 80);
  assert(encode_session_timetable_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Market Activity Summary Message: 30 bytes ------------------------ */

/* A Global Market Activity Summary message provides an overall summary of the global market activity. This message is used only at Qatar Exchange. */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t nb_trades[4];               /* bytes 14 to 17 */
  uint8_t qty_shares[4];              /* bytes 18 to 21 */
  uint8_t amount_traded[4];           /* bytes 22 to 25 */
  uint8_t price_scale_code;           /* byte 26 */
  uint8_t filler_ascii_str_3[3];      /* bytes 27 to 29 */
} GlobalMarketActivitySummaryMessage;

/* any Global Market Activity Summary Message at all: every byte one the checker chooses */
static void any_global_market_activity_summary_message(GlobalMarketActivitySummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amount_traded[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* Global Market Activity Summary Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_global_market_activity_summary_message(const GlobalMarketActivitySummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nb_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amount_traded[i]; }
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* Global Market Activity Summary Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_global_market_activity_summary_message(GlobalMarketActivitySummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amount_traded[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of Global Market Activity Summary Message is what was written, byte for byte */
static void equal_global_market_activity_summary_message(const GlobalMarketActivitySummaryMessage *read, const GlobalMarketActivitySummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nb_trades[i] == written->nb_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty_shares[i] == written->qty_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amount_traded[i] == written->amount_traded[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* Global Market Activity Summary Message: written and read back, then read and written back */
static void check_global_market_activity_summary_message(void) {
  GlobalMarketActivitySummaryMessage sent;
  GlobalMarketActivitySummaryMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_global_market_activity_summary_message(&sent);
  assert(encode_global_market_activity_summary_message(&sent, wire, 0) == 30);
  assert(decode_global_market_activity_summary_message(&got, wire, 0) == 30);
  equal_global_market_activity_summary_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_global_market_activity_summary_message(&got, wire, 0) == 30);
  assert(encode_global_market_activity_summary_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Referential Message: 4 bytes -------------------------------------- */

/* A Start Referential message marks the beginning of the broadcast of the reference data. */
typedef struct {
  uint8_t indicator;              /* byte 0 */
  uint8_t filler_ascii_str_3[3];  /* bytes 1 to 3 */
} StartReferentialMessage;

/* any Start Referential Message at all: every byte one the checker chooses */
static void any_start_referential_message(StartReferentialMessage *record) {
  record->indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* Start Referential Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_start_referential_message(const StartReferentialMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* Start Referential Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_start_referential_message(StartReferentialMessage *record, const uint8_t *wire, size_t at) {
  record->indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of Start Referential Message is what was written, byte for byte */
static void equal_start_referential_message(const StartReferentialMessage *read, const StartReferentialMessage *written) {
  assert(read->indicator == written->indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* Start Referential Message: written and read back, then read and written back */
static void check_start_referential_message(void) {
  StartReferentialMessage sent;
  StartReferentialMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_start_referential_message(&sent);
  assert(encode_start_referential_message(&sent, wire, 0) == 4);
  assert(decode_start_referential_message(&got, wire, 0) == 4);
  equal_start_referential_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_start_referential_message(&got, wire, 0) == 4);
  assert(encode_start_referential_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Referential Message: 4 bytes ---------------------------------------- */

/* An End Referential message marks the end of the broadcast of the reference data. */
typedef struct {
  uint8_t indicator;              /* byte 0 */
  uint8_t filler_ascii_str_3[3];  /* bytes 1 to 3 */
} EndReferentialMessage;

/* any End Referential Message at all: every byte one the checker chooses */
static void any_end_referential_message(EndReferentialMessage *record) {
  record->indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* End Referential Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_referential_message(const EndReferentialMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* End Referential Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_referential_message(EndReferentialMessage *record, const uint8_t *wire, size_t at) {
  record->indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of End Referential Message is what was written, byte for byte */
static void equal_end_referential_message(const EndReferentialMessage *read, const EndReferentialMessage *written) {
  assert(read->indicator == written->indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* End Referential Message: written and read back, then read and written back */
static void check_end_referential_message(void) {
  EndReferentialMessage sent;
  EndReferentialMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_referential_message(&sent);
  assert(encode_end_referential_message(&sent, wire, 0) == 4);
  assert(decode_end_referential_message(&got, wire, 0) == 4);
  equal_end_referential_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_referential_message(&got, wire, 0) == 4);
  assert(encode_end_referential_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Referential Message: 492 bytes ------------------------------------------ */

/* A Referential message carries the characteristics of an instrument, including its standard identifiers, trading parameters and reference prices. */
typedef struct {
  uint8_t symbol_index[4];                     /* bytes 0 to 3 */
  uint8_t source_seq_num[4];                   /* bytes 4 to 7 */
  uint8_t source_time[4];                      /* bytes 8 to 11 */
  uint8_t last_adj_price[4];                   /* bytes 12 to 15 */
  uint8_t system_id[4];                        /* bytes 16 to 19 */
  uint8_t prev_volume_traded[4];               /* bytes 20 to 23 */
  uint8_t fix_price_tick[4];                   /* bytes 24 to 27 */
  uint8_t source_time_micro_secs[2];           /* bytes 28 to 29 */
  uint8_t stock_exchange_code[2];              /* bytes 30 to 31 */
  uint8_t type_of_instrument[2];               /* bytes 32 to 33 */
  uint8_t event_date[8];                       /* bytes 34 to 41 */
  uint8_t instrument_name[18];                 /* bytes 42 to 59 */
  uint8_t period_indicator;                    /* byte 60 */
  uint8_t type_of_market_admission;            /* byte 61 */
  uint8_t issuing_country_code[3];             /* bytes 62 to 64 */
  uint8_t trading_currency[3];                 /* bytes 65 to 67 */
  uint8_t instrument_group_code[3];            /* bytes 68 to 70 */
  uint8_t instrument_category;                 /* byte 71 */
  uint8_t instrument_code[12];                 /* bytes 72 to 83 */
  uint8_t date_of_last_trade[8];               /* bytes 84 to 91 */
  uint8_t underlying_repo_isin_code[12];       /* bytes 92 to 103 */
  uint8_t repo_expiry_date[8];                 /* bytes 104 to 111 */
  uint8_t first_settlement_date[8];            /* bytes 112 to 119 */
  uint8_t type_of_derivatives;                 /* byte 120 */
  uint8_t bic_depositary[11];                  /* bytes 121 to 131 */
  uint8_t icb[4];                              /* bytes 132 to 135 */
  uint8_t mic[4];                              /* bytes 136 to 139 */
  uint8_t underlying_wisin_code[12];           /* bytes 140 to 151 */
  uint8_t depositary_list[25];                 /* bytes 152 to 176 */
  uint8_t main_depositary[5];                  /* bytes 177 to 181 */
  uint8_t type_of_corporate_event[2];          /* bytes 182 to 183 */
  uint8_t time_lag_euronext_utc[5];            /* bytes 184 to 188 */
  uint8_t time_lag_mi_fid_reg_utc[5];          /* bytes 189 to 193 */
  uint8_t cfi[6];                              /* bytes 194 to 199 */
  uint8_t quantity_notation[4];                /* bytes 200 to 203 */
  uint8_t index_set_of_var_price_tick[2];      /* bytes 204 to 205 */
  uint8_t market_feed_code[2];                 /* bytes 206 to 207 */
  uint8_t mic_list[24];                        /* bytes 208 to 231 */
  uint8_t industry_code[4];                    /* bytes 232 to 235 */
  uint8_t industry_text[100];                  /* bytes 236 to 335 */
  uint8_t financial_market_code[3];            /* bytes 336 to 338 */
  uint8_t us_indicators[7];                    /* bytes 339 to 345 */
  uint8_t filler_ascii_str_2[2];               /* bytes 346 to 347 */
  uint8_t prev_day_capital_traded[8];          /* bytes 348 to 355 */
  uint8_t nom_mkt_price[8];                    /* bytes 356 to 363 */
  uint8_t lot_size[8];                         /* bytes 364 to 371 */
  uint8_t number_instrument_circ[8];           /* bytes 372 to 379 */
  uint8_t shares_out[8];                       /* bytes 380 to 387 */
  uint8_t auth_shares[8];                      /* bytes 388 to 395 */
  uint8_t heading_number[2];                   /* bytes 396 to 397 */
  uint8_t section_number;                      /* byte 398 */
  uint8_t repo_indicator;                      /* byte 399 */
  uint8_t last_adj_price_scale_code;           /* byte 400 */
  uint8_t type_of_unit_exp;                    /* byte 401 */
  uint8_t market_indicator;                    /* byte 402 */
  uint8_t prev_day_capital_traded_scale_code;  /* byte 403 */
  uint8_t tax_code;                            /* byte 404 */
  uint8_t nom_mkdt_price_scale_code;           /* byte 405 */
  uint8_t lot_size_scale_code;                 /* byte 406 */
  uint8_t fix_price_tick_scale_code;           /* byte 407 */
  uint8_t mnemo[5];                            /* bytes 408 to 412 */
  uint8_t trading_code[12];                    /* bytes 413 to 424 */
  uint8_t filler_ascii_str_3[3];               /* bytes 425 to 427 */
  uint8_t strike_price[4];                     /* bytes 428 to 431 */
  uint8_t strike_currency[3];                  /* bytes 432 to 434 */
  uint8_t strike_scale_code;                   /* byte 435 */
  uint8_t currency_coef[4];                    /* bytes 436 to 439 */
  uint8_t currency_coef_scale_code;            /* byte 440 */
  uint8_t trading_currency_indicator;          /* byte 441 */
  uint8_t strike_currency_indicator;           /* byte 442 */
  uint8_t market_segment[2];                   /* bytes 443 to 444 */
  uint8_t algo;                                /* byte 445 */
  uint8_t local_name[30];                      /* bytes 446 to 475 */
  uint8_t small_trade[4];                      /* bytes 476 to 479 */
  uint8_t filler_binary_int_12[12];            /* bytes 480 to 491 */
} ReferentialMessage;

/* any Referential Message at all: every byte one the checker chooses */
static void any_referential_message(ReferentialMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_adj_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_volume_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fix_price_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->stock_exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->event_date[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->instrument_name[i] = arbitrary(); }
  record->period_indicator = arbitrary();
  record->type_of_market_admission = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->issuing_country_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = arbitrary(); }
  record->instrument_category = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->instrument_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_last_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_repo_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->repo_expiry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->first_settlement_date[i] = arbitrary(); }
  record->type_of_derivatives = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->bic_depositary[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->icb[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_wisin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->depositary_list[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->main_depositary[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_corporate_event[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_lag_euronext_utc[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->time_lag_mi_fid_reg_utc[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity_notation[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->index_set_of_var_price_tick[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_feed_code[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->mic_list[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->industry_text[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->financial_market_code[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->us_indicators[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prev_day_capital_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nom_mkt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->number_instrument_circ[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auth_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->heading_number[i] = arbitrary(); }
  record->section_number = arbitrary();
  record->repo_indicator = arbitrary();
  record->last_adj_price_scale_code = arbitrary();
  record->type_of_unit_exp = arbitrary();
  record->market_indicator = arbitrary();
  record->prev_day_capital_traded_scale_code = arbitrary();
  record->tax_code = arbitrary();
  record->nom_mkdt_price_scale_code = arbitrary();
  record->lot_size_scale_code = arbitrary();
  record->fix_price_tick_scale_code = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->mnemo[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->trading_code[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->strike_currency[i] = arbitrary(); }
  record->strike_scale_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->currency_coef[i] = arbitrary(); }
  record->currency_coef_scale_code = arbitrary();
  record->trading_currency_indicator = arbitrary();
  record->strike_currency_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = arbitrary(); }
  record->algo = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->local_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->small_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->filler_binary_int_12[i] = arbitrary(); }
}

/* Referential Message to the wire: 492 bytes from at, returning where the next byte goes */
static size_t encode_referential_message(const ReferentialMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_adj_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_volume_traded[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fix_price_tick[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->stock_exchange_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->event_date[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->instrument_name[i]; }
  wire[at++] = record->period_indicator;
  wire[at++] = record->type_of_market_admission;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->issuing_country_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trading_currency[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->instrument_group_code[i]; }
  wire[at++] = record->instrument_category;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_last_trade[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_repo_isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->repo_expiry_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_settlement_date[i]; }
  wire[at++] = record->type_of_derivatives;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->bic_depositary[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->icb[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_wisin_code[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->depositary_list[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->main_depositary[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_corporate_event[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_lag_euronext_utc[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->time_lag_mi_fid_reg_utc[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_notation[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->index_set_of_var_price_tick[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_feed_code[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->mic_list[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->industry_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->industry_text[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->financial_market_code[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->us_indicators[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_str_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prev_day_capital_traded[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nom_mkt_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->number_instrument_circ[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auth_shares[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->heading_number[i]; }
  wire[at++] = record->section_number;
  wire[at++] = record->repo_indicator;
  wire[at++] = record->last_adj_price_scale_code;
  wire[at++] = record->type_of_unit_exp;
  wire[at++] = record->market_indicator;
  wire[at++] = record->prev_day_capital_traded_scale_code;
  wire[at++] = record->tax_code;
  wire[at++] = record->nom_mkdt_price_scale_code;
  wire[at++] = record->lot_size_scale_code;
  wire[at++] = record->fix_price_tick_scale_code;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mnemo[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->trading_code[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->strike_currency[i]; }
  wire[at++] = record->strike_scale_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->currency_coef[i]; }
  wire[at++] = record->currency_coef_scale_code;
  wire[at++] = record->trading_currency_indicator;
  wire[at++] = record->strike_currency_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_segment[i]; }
  wire[at++] = record->algo;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->local_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->small_trade[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->filler_binary_int_12[i]; }

  return at;
}

/* Referential Message off the wire: 492 bytes from at, returning where the next byte lies */
static size_t decode_referential_message(ReferentialMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_adj_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_volume_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fix_price_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->stock_exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->event_date[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->instrument_name[i] = wire[at++]; }
  record->period_indicator = wire[at++];
  record->type_of_market_admission = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->issuing_country_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trading_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->instrument_group_code[i] = wire[at++]; }
  record->instrument_category = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->instrument_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_last_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_repo_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->repo_expiry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->first_settlement_date[i] = wire[at++]; }
  record->type_of_derivatives = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->bic_depositary[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->icb[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_wisin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->depositary_list[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->main_depositary[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_corporate_event[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_lag_euronext_utc[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->time_lag_mi_fid_reg_utc[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity_notation[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->index_set_of_var_price_tick[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_feed_code[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->mic_list[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->industry_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->industry_text[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->financial_market_code[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->us_indicators[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prev_day_capital_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nom_mkt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->number_instrument_circ[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auth_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->heading_number[i] = wire[at++]; }
  record->section_number = wire[at++];
  record->repo_indicator = wire[at++];
  record->last_adj_price_scale_code = wire[at++];
  record->type_of_unit_exp = wire[at++];
  record->market_indicator = wire[at++];
  record->prev_day_capital_traded_scale_code = wire[at++];
  record->tax_code = wire[at++];
  record->nom_mkdt_price_scale_code = wire[at++];
  record->lot_size_scale_code = wire[at++];
  record->fix_price_tick_scale_code = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->mnemo[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->trading_code[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->strike_currency[i] = wire[at++]; }
  record->strike_scale_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->currency_coef[i] = wire[at++]; }
  record->currency_coef_scale_code = wire[at++];
  record->trading_currency_indicator = wire[at++];
  record->strike_currency_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->market_segment[i] = wire[at++]; }
  record->algo = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->local_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->small_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->filler_binary_int_12[i] = wire[at++]; }

  return at;
}

/* what was read of Referential Message is what was written, byte for byte */
static void equal_referential_message(const ReferentialMessage *read, const ReferentialMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_adj_price[i] == written->last_adj_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_volume_traded[i] == written->prev_volume_traded[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fix_price_tick[i] == written->fix_price_tick[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->stock_exchange_code[i] == written->stock_exchange_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_instrument[i] == written->type_of_instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->event_date[i] == written->event_date[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->instrument_name[i] == written->instrument_name[i]); }
  assert(read->period_indicator == written->period_indicator);
  assert(read->type_of_market_admission == written->type_of_market_admission);
  for (size_t i = 0; i < 3; i++) { assert(read->issuing_country_code[i] == written->issuing_country_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trading_currency[i] == written->trading_currency[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->instrument_group_code[i] == written->instrument_group_code[i]); }
  assert(read->instrument_category == written->instrument_category);
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_code[i] == written->instrument_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_last_trade[i] == written->date_of_last_trade[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_repo_isin_code[i] == written->underlying_repo_isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->repo_expiry_date[i] == written->repo_expiry_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->first_settlement_date[i] == written->first_settlement_date[i]); }
  assert(read->type_of_derivatives == written->type_of_derivatives);
  for (size_t i = 0; i < 11; i++) { assert(read->bic_depositary[i] == written->bic_depositary[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->icb[i] == written->icb[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_wisin_code[i] == written->underlying_wisin_code[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->depositary_list[i] == written->depositary_list[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->main_depositary[i] == written->main_depositary[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_corporate_event[i] == written->type_of_corporate_event[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_lag_euronext_utc[i] == written->time_lag_euronext_utc[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->time_lag_mi_fid_reg_utc[i] == written->time_lag_mi_fid_reg_utc[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi[i] == written->cfi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_notation[i] == written->quantity_notation[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->index_set_of_var_price_tick[i] == written->index_set_of_var_price_tick[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_feed_code[i] == written->market_feed_code[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->mic_list[i] == written->mic_list[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->industry_code[i] == written->industry_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->industry_text[i] == written->industry_text[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->financial_market_code[i] == written->financial_market_code[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->us_indicators[i] == written->us_indicators[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_str_2[i] == written->filler_ascii_str_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prev_day_capital_traded[i] == written->prev_day_capital_traded[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nom_mkt_price[i] == written->nom_mkt_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->number_instrument_circ[i] == written->number_instrument_circ[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_out[i] == written->shares_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auth_shares[i] == written->auth_shares[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->heading_number[i] == written->heading_number[i]); }
  assert(read->section_number == written->section_number);
  assert(read->repo_indicator == written->repo_indicator);
  assert(read->last_adj_price_scale_code == written->last_adj_price_scale_code);
  assert(read->type_of_unit_exp == written->type_of_unit_exp);
  assert(read->market_indicator == written->market_indicator);
  assert(read->prev_day_capital_traded_scale_code == written->prev_day_capital_traded_scale_code);
  assert(read->tax_code == written->tax_code);
  assert(read->nom_mkdt_price_scale_code == written->nom_mkdt_price_scale_code);
  assert(read->lot_size_scale_code == written->lot_size_scale_code);
  assert(read->fix_price_tick_scale_code == written->fix_price_tick_scale_code);
  for (size_t i = 0; i < 5; i++) { assert(read->mnemo[i] == written->mnemo[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->trading_code[i] == written->trading_code[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->strike_currency[i] == written->strike_currency[i]); }
  assert(read->strike_scale_code == written->strike_scale_code);
  for (size_t i = 0; i < 4; i++) { assert(read->currency_coef[i] == written->currency_coef[i]); }
  assert(read->currency_coef_scale_code == written->currency_coef_scale_code);
  assert(read->trading_currency_indicator == written->trading_currency_indicator);
  assert(read->strike_currency_indicator == written->strike_currency_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->market_segment[i] == written->market_segment[i]); }
  assert(read->algo == written->algo);
  for (size_t i = 0; i < 30; i++) { assert(read->local_name[i] == written->local_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->small_trade[i] == written->small_trade[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->filler_binary_int_12[i] == written->filler_binary_int_12[i]); }
}

/* Referential Message: written and read back, then read and written back */
static void check_referential_message(void) {
  ReferentialMessage sent;
  ReferentialMessage got;
  uint8_t wire[492];
  uint8_t again[492];

  any_referential_message(&sent);
  assert(encode_referential_message(&sent, wire, 0) == 492);
  assert(decode_referential_message(&got, wire, 0) == 492);
  equal_referential_message(&got, &sent);

  for (size_t i = 0; i < 492; i++) { wire[i] = arbitrary(); }
  assert(decode_referential_message(&got, wire, 0) == 492);
  assert(encode_referential_message(&got, again, 0) == 492);
  for (size_t i = 0; i < 492; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Creation Message: 40 bytes ---------------------------------------- */

/* A Trade Creation message announces a trade that has just been created in the trading engine. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t trade_id_number[4];         /* bytes 8 to 11 */
  uint8_t quote_link_id[4];           /* bytes 12 to 15 */
  uint8_t source_seq_num[4];          /* bytes 16 to 19 */
  uint8_t price[4];                   /* bytes 20 to 23 */
  uint8_t volume[4];                  /* bytes 24 to 27 */
  uint8_t system_id[4];               /* bytes 28 to 31 */
  uint8_t source_time_micro_secs[2];  /* bytes 32 to 33 */
  uint8_t small_trade_indicator;      /* byte 34 */
  uint8_t trad_cond_2;                /* byte 35 */
  uint8_t trad_cond_3;                /* byte 36 */
  uint8_t trade_origin;               /* byte 37 */
  uint8_t opening_trade_indicator;    /* byte 38 */
  uint8_t price_scale_code;           /* byte 39 */
} TradeCreationMessage;

/* any Trade Creation Message at all: every byte one the checker chooses */
static void any_trade_creation_message(TradeCreationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->small_trade_indicator = arbitrary();
  record->trad_cond_2 = arbitrary();
  record->trad_cond_3 = arbitrary();
  record->trade_origin = arbitrary();
  record->opening_trade_indicator = arbitrary();
  record->price_scale_code = arbitrary();
}

/* Trade Creation Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_creation_message(const TradeCreationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->small_trade_indicator;
  wire[at++] = record->trad_cond_2;
  wire[at++] = record->trad_cond_3;
  wire[at++] = record->trade_origin;
  wire[at++] = record->opening_trade_indicator;
  wire[at++] = record->price_scale_code;

  return at;
}

/* Trade Creation Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_creation_message(TradeCreationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->small_trade_indicator = wire[at++];
  record->trad_cond_2 = wire[at++];
  record->trad_cond_3 = wire[at++];
  record->trade_origin = wire[at++];
  record->opening_trade_indicator = wire[at++];
  record->price_scale_code = wire[at++];

  return at;
}

/* what was read of Trade Creation Message is what was written, byte for byte */
static void equal_trade_creation_message(const TradeCreationMessage *read, const TradeCreationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id_number[i] == written->trade_id_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_link_id[i] == written->quote_link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->small_trade_indicator == written->small_trade_indicator);
  assert(read->trad_cond_2 == written->trad_cond_2);
  assert(read->trad_cond_3 == written->trad_cond_3);
  assert(read->trade_origin == written->trade_origin);
  assert(read->opening_trade_indicator == written->opening_trade_indicator);
  assert(read->price_scale_code == written->price_scale_code);
}

/* Trade Creation Message: written and read back, then read and written back */
static void check_trade_creation_message(void) {
  TradeCreationMessage sent;
  TradeCreationMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_creation_message(&sent);
  assert(encode_trade_creation_message(&sent, wire, 0) == 40);
  assert(decode_trade_creation_message(&got, wire, 0) == 40);
  equal_trade_creation_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_creation_message(&got, wire, 0) == 40);
  assert(encode_trade_creation_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancellation Message: 24 bytes ------------------------------------ */

/* A Trade Cancellation message announces the cancellation of a trade previously published. */
typedef struct {
  uint8_t symbol_index[4];              /* bytes 0 to 3 */
  uint8_t source_time[4];               /* bytes 4 to 7 */
  uint8_t source_seq_num[4];            /* bytes 8 to 11 */
  uint8_t original_trade_id_number[4];  /* bytes 12 to 15 */
  uint8_t system_id[4];                 /* bytes 16 to 19 */
  uint8_t source_time_micro_secs[2];    /* bytes 20 to 21 */
  uint8_t filler_binary_int_2[2];       /* bytes 22 to 23 */
} TradeCancellationMessage;

/* any Trade Cancellation Message at all: every byte one the checker chooses */
static void any_trade_cancellation_message(TradeCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = arbitrary(); }
}

/* Trade Cancellation Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancellation_message(const TradeCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->original_trade_id_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_binary_int_2[i]; }

  return at;
}

/* Trade Cancellation Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancellation_message(TradeCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->original_trade_id_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancellation Message is what was written, byte for byte */
static void equal_trade_cancellation_message(const TradeCancellationMessage *read, const TradeCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->original_trade_id_number[i] == written->original_trade_id_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_binary_int_2[i] == written->filler_binary_int_2[i]); }
}

/* Trade Cancellation Message: written and read back, then read and written back */
static void check_trade_cancellation_message(void) {
  TradeCancellationMessage sent;
  TradeCancellationMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_trade_cancellation_message(&sent);
  assert(encode_trade_cancellation_message(&sent, wire, 0) == 24);
  assert(decode_trade_cancellation_message(&got, wire, 0) == 24);
  equal_trade_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancellation_message(&got, wire, 0) == 24);
  assert(encode_trade_cancellation_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Full Information Message: 60 bytes -------------------------------- */

/* A Trade Full Information message carries a trade along with the cumulated statistics of the instrument for the trading day. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t trade_id_number[4];         /* bytes 8 to 11 */
  uint8_t quote_link_id[4];           /* bytes 12 to 15 */
  uint8_t source_seq_num[4];          /* bytes 16 to 19 */
  uint8_t price[4];                   /* bytes 20 to 23 */
  uint8_t volume[4];                  /* bytes 24 to 27 */
  uint8_t cumulative_quantity[4];     /* bytes 28 to 31 */
  uint8_t highest_price[4];           /* bytes 32 to 35 */
  uint8_t lowest_price[4];            /* bytes 36 to 39 */
  uint8_t variation_last_price[4];    /* bytes 40 to 43 */
  uint8_t system_id[4];               /* bytes 44 to 47 */
  uint8_t source_time_micro_secs[2];  /* bytes 48 to 49 */
  uint8_t filler_binary_int_2[2];     /* bytes 50 to 51 */
  uint8_t small_trade_indicator;      /* byte 52 */
  uint8_t trad_cond_2;                /* byte 53 */
  uint8_t trad_cond_3;                /* byte 54 */
  uint8_t trade_origin;               /* byte 55 */
  uint8_t tick_direction;             /* byte 56 */
  uint8_t opening_trade_indicator;    /* byte 57 */
  uint8_t variation_scale_code;       /* byte 58 */
  uint8_t price_scale_code;           /* byte 59 */
} TradeFullInformationMessage;

/* any Trade Full Information Message at all: every byte one the checker chooses */
static void any_trade_full_information_message(TradeFullInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = arbitrary(); }
  record->small_trade_indicator = arbitrary();
  record->trad_cond_2 = arbitrary();
  record->trad_cond_3 = arbitrary();
  record->trade_origin = arbitrary();
  record->tick_direction = arbitrary();
  record->opening_trade_indicator = arbitrary();
  record->variation_scale_code = arbitrary();
  record->price_scale_code = arbitrary();
}

/* Trade Full Information Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_trade_full_information_message(const TradeFullInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation_last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_binary_int_2[i]; }
  wire[at++] = record->small_trade_indicator;
  wire[at++] = record->trad_cond_2;
  wire[at++] = record->trad_cond_3;
  wire[at++] = record->trade_origin;
  wire[at++] = record->tick_direction;
  wire[at++] = record->opening_trade_indicator;
  wire[at++] = record->variation_scale_code;
  wire[at++] = record->price_scale_code;

  return at;
}

/* Trade Full Information Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_trade_full_information_message(TradeFullInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_id_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = wire[at++]; }
  record->small_trade_indicator = wire[at++];
  record->trad_cond_2 = wire[at++];
  record->trad_cond_3 = wire[at++];
  record->trade_origin = wire[at++];
  record->tick_direction = wire[at++];
  record->opening_trade_indicator = wire[at++];
  record->variation_scale_code = wire[at++];
  record->price_scale_code = wire[at++];

  return at;
}

/* what was read of Trade Full Information Message is what was written, byte for byte */
static void equal_trade_full_information_message(const TradeFullInformationMessage *read, const TradeFullInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id_number[i] == written->trade_id_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_link_id[i] == written->quote_link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_quantity[i] == written->cumulative_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation_last_price[i] == written->variation_last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_binary_int_2[i] == written->filler_binary_int_2[i]); }
  assert(read->small_trade_indicator == written->small_trade_indicator);
  assert(read->trad_cond_2 == written->trad_cond_2);
  assert(read->trad_cond_3 == written->trad_cond_3);
  assert(read->trade_origin == written->trade_origin);
  assert(read->tick_direction == written->tick_direction);
  assert(read->opening_trade_indicator == written->opening_trade_indicator);
  assert(read->variation_scale_code == written->variation_scale_code);
  assert(read->price_scale_code == written->price_scale_code);
}

/* Trade Full Information Message: written and read back, then read and written back */
static void check_trade_full_information_message(void) {
  TradeFullInformationMessage sent;
  TradeFullInformationMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_trade_full_information_message(&sent);
  assert(encode_trade_full_information_message(&sent, wire, 0) == 60);
  assert(decode_trade_full_information_message(&got, wire, 0) == 60);
  equal_trade_full_information_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_full_information_message(&got, wire, 0) == 60);
  assert(encode_trade_full_information_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Update Message: 40 bytes ------------------------------------------ */

/* A Price Update message updates the statistics of an instrument without carrying a new trade. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t source_seq_num[4];          /* bytes 8 to 11 */
  uint8_t price[4];                   /* bytes 12 to 15 */
  uint8_t highest_price[4];           /* bytes 16 to 19 */
  uint8_t lowest_price[4];            /* bytes 20 to 23 */
  uint8_t variation_last_price[4];    /* bytes 24 to 27 */
  uint8_t system_id[4];               /* bytes 28 to 31 */
  uint8_t source_time_micro_secs[2];  /* bytes 32 to 33 */
  uint8_t type_of_price[2];           /* bytes 34 to 35 */
  uint8_t filler_binary_int_2[2];     /* bytes 36 to 37 */
  uint8_t price_scale_code;           /* byte 38 */
  uint8_t variation_scale_code;       /* byte 39 */
} PriceUpdateMessage;

/* any Price Update Message at all: every byte one the checker chooses */
static void any_price_update_message(PriceUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
}

/* Price Update Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_price_update_message(const PriceUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation_last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_binary_int_2[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->variation_scale_code;

  return at;
}

/* Price Update Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_price_update_message(PriceUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation_last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler_binary_int_2[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];

  return at;
}

/* what was read of Price Update Message is what was written, byte for byte */
static void equal_price_update_message(const PriceUpdateMessage *read, const PriceUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation_last_price[i] == written->variation_last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_price[i] == written->type_of_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler_binary_int_2[i] == written->filler_binary_int_2[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
}

/* Price Update Message: written and read back, then read and written back */
static void check_price_update_message(void) {
  PriceUpdateMessage sent;
  PriceUpdateMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_price_update_message(&sent);
  assert(encode_price_update_message(&sent, wire, 0) == 40);
  assert(decode_price_update_message(&got, wire, 0) == 40);
  equal_price_update_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_price_update_message(&got, wire, 0) == 40);
  assert(encode_price_update_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 48 bytes --------------------------------------- */

/* An Auction Summary message summarises the trades resulting from an auction. */
typedef struct {
  uint8_t symbol_index[4];             /* bytes 0 to 3 */
  uint8_t source_time[4];              /* bytes 4 to 7 */
  uint8_t source_seq_num[4];           /* bytes 8 to 11 */
  uint8_t first_price[4];              /* bytes 12 to 15 */
  uint8_t last_price[4];               /* bytes 16 to 19 */
  uint8_t highest_price[4];            /* bytes 20 to 23 */
  uint8_t lowest_price[4];             /* bytes 24 to 27 */
  uint8_t cumulative_quantity[4];      /* bytes 28 to 31 */
  uint8_t variation[4];                /* bytes 32 to 35 */
  uint8_t system_id[4];                /* bytes 36 to 39 */
  uint8_t source_time_micro_secs[2];   /* bytes 40 to 41 */
  uint8_t type_of_last_price[2];       /* bytes 42 to 43 */
  uint8_t tick_direction;              /* byte 44 */
  uint8_t instrument_valuation_price;  /* byte 45 */
  uint8_t price_scale_code;            /* byte 46 */
  uint8_t variation_scale_code;        /* byte 47 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_last_price[i] = arbitrary(); }
  record->tick_direction = arbitrary();
  record->instrument_valuation_price = arbitrary();
  record->price_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
}

/* Auction Summary Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->highest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lowest_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cumulative_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_last_price[i]; }
  wire[at++] = record->tick_direction;
  wire[at++] = record->instrument_valuation_price;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->variation_scale_code;

  return at;
}

/* Auction Summary Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->highest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lowest_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cumulative_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_last_price[i] = wire[at++]; }
  record->tick_direction = wire[at++];
  record->instrument_valuation_price = wire[at++];
  record->price_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_price[i] == written->first_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->highest_price[i] == written->highest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lowest_price[i] == written->lowest_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cumulative_quantity[i] == written->cumulative_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation[i] == written->variation[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_last_price[i] == written->type_of_last_price[i]); }
  assert(read->tick_direction == written->tick_direction);
  assert(read->instrument_valuation_price == written->instrument_valuation_price);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 48);
  assert(decode_auction_summary_message(&got, wire, 0) == 48);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 48);
  assert(encode_auction_summary_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vwap Closing Price Message: 44 bytes ------------------------------------ */

/* A VWAP - Closing Price message contains the real time Volume-Weighted Average Price for an instrument together with the current closing price. This message is used exclusively at Qatar Exchange. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t source_seq_num[4];          /* bytes 8 to 11 */
  uint8_t sending_indicator[2];       /* bytes 12 to 13 */
  uint8_t closing_price_rule[2];      /* bytes 14 to 15 */
  uint8_t closing_price[4];           /* bytes 16 to 19 */
  uint8_t adjusted_closing_price[4];  /* bytes 20 to 23 */
  uint8_t nb_trades[4];               /* bytes 24 to 27 */
  uint8_t qty_shares[4];              /* bytes 28 to 31 */
  uint8_t amount_traded[4];           /* bytes 32 to 35 */
  uint8_t system_id[4];               /* bytes 36 to 39 */
  uint8_t price_scale_code;           /* byte 40 */
  uint8_t filler_ascii_str_3[3];      /* bytes 41 to 43 */
} VwapClosingPriceMessage;

/* any Vwap Closing Price Message at all: every byte one the checker chooses */
static void any_vwap_closing_price_message(VwapClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sending_indicator[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->closing_price_rule[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amount_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* Vwap Closing Price Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_vwap_closing_price_message(const VwapClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sending_indicator[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->closing_price_rule[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->adjusted_closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nb_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->qty_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amount_traded[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* Vwap Closing Price Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_vwap_closing_price_message(VwapClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sending_indicator[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->closing_price_rule[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->adjusted_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nb_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->qty_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amount_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of Vwap Closing Price Message is what was written, byte for byte */
static void equal_vwap_closing_price_message(const VwapClosingPriceMessage *read, const VwapClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sending_indicator[i] == written->sending_indicator[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->closing_price_rule[i] == written->closing_price_rule[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->adjusted_closing_price[i] == written->adjusted_closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nb_trades[i] == written->nb_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->qty_shares[i] == written->qty_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amount_traded[i] == written->amount_traded[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* Vwap Closing Price Message: written and read back, then read and written back */
static void check_vwap_closing_price_message(void) {
  VwapClosingPriceMessage sent;
  VwapClosingPriceMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_vwap_closing_price_message(&sent);
  assert(encode_vwap_closing_price_message(&sent, wire, 0) == 44);
  assert(decode_vwap_closing_price_message(&got, wire, 0) == 44);
  equal_vwap_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_vwap_closing_price_message(&got, wire, 0) == 44);
  assert(encode_vwap_closing_price_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quotes Message: 48 bytes ------------------------------------------------ */

/* A Quotes message carries the best limits of the order book for an instrument. */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t quote_link_id[4];           /* bytes 12 to 15 */
  uint8_t ask_price[4];               /* bytes 16 to 19 */
  uint8_t ask_size[4];                /* bytes 20 to 23 */
  uint8_t bid_price[4];               /* bytes 24 to 27 */
  uint8_t bid_size[4];                /* bytes 28 to 31 */
  uint8_t system_id[4];               /* bytes 32 to 35 */
  uint8_t number_ask_orders[2];       /* bytes 36 to 37 */
  uint8_t number_bid_orders[2];       /* bytes 38 to 39 */
  uint8_t source_time_micro_secs[2];  /* bytes 40 to 41 */
  uint8_t type_of_ask_price;          /* byte 42 */
  uint8_t type_of_bid_price;          /* byte 43 */
  uint8_t quote_condition;            /* byte 44 */
  uint8_t quote_number;               /* byte 45 */
  uint8_t price_scale_code;           /* byte 46 */
  uint8_t filler_ascii_str_1;         /* byte 47 */
} QuotesMessage;

/* any Quotes Message at all: every byte one the checker chooses */
static void any_quotes_message(QuotesMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_ask_orders[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_bid_orders[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->type_of_ask_price = arbitrary();
  record->type_of_bid_price = arbitrary();
  record->quote_condition = arbitrary();
  record->quote_number = arbitrary();
  record->price_scale_code = arbitrary();
  record->filler_ascii_str_1 = arbitrary();
}

/* Quotes Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_quotes_message(const QuotesMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_ask_orders[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_bid_orders[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->type_of_ask_price;
  wire[at++] = record->type_of_bid_price;
  wire[at++] = record->quote_condition;
  wire[at++] = record->quote_number;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->filler_ascii_str_1;

  return at;
}

/* Quotes Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_quotes_message(QuotesMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_ask_orders[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_bid_orders[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->type_of_ask_price = wire[at++];
  record->type_of_bid_price = wire[at++];
  record->quote_condition = wire[at++];
  record->quote_number = wire[at++];
  record->price_scale_code = wire[at++];
  record->filler_ascii_str_1 = wire[at++];

  return at;
}

/* what was read of Quotes Message is what was written, byte for byte */
static void equal_quotes_message(const QuotesMessage *read, const QuotesMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_link_id[i] == written->quote_link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_price[i] == written->ask_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size[i] == written->ask_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size[i] == written->bid_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_ask_orders[i] == written->number_ask_orders[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_bid_orders[i] == written->number_bid_orders[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->type_of_ask_price == written->type_of_ask_price);
  assert(read->type_of_bid_price == written->type_of_bid_price);
  assert(read->quote_condition == written->quote_condition);
  assert(read->quote_number == written->quote_number);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->filler_ascii_str_1 == written->filler_ascii_str_1);
}

/* Quotes Message: written and read back, then read and written back */
static void check_quotes_message(void) {
  QuotesMessage sent;
  QuotesMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_quotes_message(&sent);
  assert(encode_quotes_message(&sent, wire, 0) == 48);
  assert(decode_quotes_message(&got, wire, 0) == 48);
  equal_quotes_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_quotes_message(&got, wire, 0) == 48);
  assert(encode_quotes_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Update Market Sheet Message: 60 bytes ----------------------------- */

/* An Order Update message carries a single order of the market sheet, so that the order book of an instrument may be rebuilt and maintained. */
typedef struct {
  uint8_t symbol_index[4];               /* bytes 0 to 3 */
  uint8_t source_time[4];                /* bytes 4 to 7 */
  uint8_t source_seq_num[4];             /* bytes 8 to 11 */
  uint8_t price[4];                      /* bytes 12 to 15 */
  uint8_t aggregated_volume[4];          /* bytes 16 to 19 */
  uint8_t volume[4];                     /* bytes 20 to 23 */
  uint8_t link_id[4];                    /* bytes 24 to 27 */
  uint8_t order_id[4];                   /* bytes 28 to 31 */
  uint8_t system_id[4];                  /* bytes 32 to 35 */
  uint8_t source_time_micro_secs[2];     /* bytes 36 to 37 */
  uint8_t number_orders[2];              /* bytes 38 to 39 */
  uint8_t side;                          /* byte 40 */
  uint8_t order_type;                    /* byte 41 */
  uint8_t action_type;                   /* byte 42 */
  uint8_t price_scale_code;              /* byte 43 */
  uint8_t order_date[4];                 /* bytes 44 to 47 */
  uint8_t order_priority_date[4];        /* bytes 48 to 51 */
  uint8_t order_priority_time[4];        /* bytes 52 to 55 */
  uint8_t order_priority_micro_secs[2];  /* bytes 56 to 57 */
  uint8_t order_origin;                  /* byte 58 */
  uint8_t filler_binary_int_1;           /* byte 59 */
} OrderUpdateMarketSheetMessage;

/* any Order Update Market Sheet Message at all: every byte one the checker chooses */
static void any_order_update_market_sheet_message(OrderUpdateMarketSheetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->aggregated_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->link_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_orders[i] = arbitrary(); }
  record->side = arbitrary();
  record->order_type = arbitrary();
  record->action_type = arbitrary();
  record->price_scale_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_priority_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_priority_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->order_priority_micro_secs[i] = arbitrary(); }
  record->order_origin = arbitrary();
  record->filler_binary_int_1 = arbitrary();
}

/* Order Update Market Sheet Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_order_update_market_sheet_message(const OrderUpdateMarketSheetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->aggregated_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->link_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_orders[i]; }
  wire[at++] = record->side;
  wire[at++] = record->order_type;
  wire[at++] = record->action_type;
  wire[at++] = record->price_scale_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_priority_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_priority_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->order_priority_micro_secs[i]; }
  wire[at++] = record->order_origin;
  wire[at++] = record->filler_binary_int_1;

  return at;
}

/* Order Update Market Sheet Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_order_update_market_sheet_message(OrderUpdateMarketSheetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->aggregated_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->link_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_orders[i] = wire[at++]; }
  record->side = wire[at++];
  record->order_type = wire[at++];
  record->action_type = wire[at++];
  record->price_scale_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_priority_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_priority_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->order_priority_micro_secs[i] = wire[at++]; }
  record->order_origin = wire[at++];
  record->filler_binary_int_1 = wire[at++];

  return at;
}

/* what was read of Order Update Market Sheet Message is what was written, byte for byte */
static void equal_order_update_market_sheet_message(const OrderUpdateMarketSheetMessage *read, const OrderUpdateMarketSheetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->aggregated_volume[i] == written->aggregated_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->link_id[i] == written->link_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_orders[i] == written->number_orders[i]); }
  assert(read->side == written->side);
  assert(read->order_type == written->order_type);
  assert(read->action_type == written->action_type);
  assert(read->price_scale_code == written->price_scale_code);
  for (size_t i = 0; i < 4; i++) { assert(read->order_date[i] == written->order_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_priority_date[i] == written->order_priority_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_priority_time[i] == written->order_priority_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->order_priority_micro_secs[i] == written->order_priority_micro_secs[i]); }
  assert(read->order_origin == written->order_origin);
  assert(read->filler_binary_int_1 == written->filler_binary_int_1);
}

/* Order Update Market Sheet Message: written and read back, then read and written back */
static void check_order_update_market_sheet_message(void) {
  OrderUpdateMarketSheetMessage sent;
  OrderUpdateMarketSheetMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_order_update_market_sheet_message(&sent);
  assert(encode_order_update_market_sheet_message(&sent, wire, 0) == 60);
  assert(decode_order_update_market_sheet_message(&got, wire, 0) == 60);
  equal_order_update_market_sheet_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_order_update_market_sheet_message(&got, wire, 0) == 60);
  assert(encode_order_update_market_sheet_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orderbook Retransmission Delimiter Message: 12 bytes -------------------- */

/* An Orderbook Retransmission Delimiter message delimits the retransmission of a market sheet, so that the order book is cleaned before the orders that follow are applied. */
typedef struct {
  uint8_t source_time[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];         /* bytes 4 to 7 */
  uint8_t trading_engine_id[2];      /* bytes 8 to 9 */
  uint8_t instance_id;               /* byte 10 */
  uint8_t retransmission_indicator;  /* byte 11 */
} OrderbookRetransmissionDelimiterMessage;

/* any Orderbook Retransmission Delimiter Message at all: every byte one the checker chooses */
static void any_orderbook_retransmission_delimiter_message(OrderbookRetransmissionDelimiterMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trading_engine_id[i] = arbitrary(); }
  record->instance_id = arbitrary();
  record->retransmission_indicator = arbitrary();
}

/* Orderbook Retransmission Delimiter Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_orderbook_retransmission_delimiter_message(const OrderbookRetransmissionDelimiterMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trading_engine_id[i]; }
  wire[at++] = record->instance_id;
  wire[at++] = record->retransmission_indicator;

  return at;
}

/* Orderbook Retransmission Delimiter Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_orderbook_retransmission_delimiter_message(OrderbookRetransmissionDelimiterMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trading_engine_id[i] = wire[at++]; }
  record->instance_id = wire[at++];
  record->retransmission_indicator = wire[at++];

  return at;
}

/* what was read of Orderbook Retransmission Delimiter Message is what was written, byte for byte */
static void equal_orderbook_retransmission_delimiter_message(const OrderbookRetransmissionDelimiterMessage *read, const OrderbookRetransmissionDelimiterMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trading_engine_id[i] == written->trading_engine_id[i]); }
  assert(read->instance_id == written->instance_id);
  assert(read->retransmission_indicator == written->retransmission_indicator);
}

/* Orderbook Retransmission Delimiter Message: written and read back, then read and written back */
static void check_orderbook_retransmission_delimiter_message(void) {
  OrderbookRetransmissionDelimiterMessage sent;
  OrderbookRetransmissionDelimiterMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_orderbook_retransmission_delimiter_message(&sent);
  assert(encode_orderbook_retransmission_delimiter_message(&sent, wire, 0) == 12);
  assert(decode_orderbook_retransmission_delimiter_message(&got, wire, 0) == 12);
  equal_orderbook_retransmission_delimiter_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_orderbook_retransmission_delimiter_message(&got, wire, 0) == 12);
  assert(encode_orderbook_retransmission_delimiter_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Real Time Index Message: 48 bytes --------------------------------------- */

/* A Real Time Index message carries the current level of an index. */
typedef struct {
  uint8_t symbol_index[4];                        /* bytes 0 to 3 */
  uint8_t source_time[4];                         /* bytes 4 to 7 */
  uint8_t index_level[4];                         /* bytes 8 to 11 */
  uint8_t forerunner_level[4];                    /* bytes 12 to 15 */
  uint8_t session_high[4];                        /* bytes 16 to 19 */
  uint8_t session_low[4];                         /* bytes 20 to 23 */
  uint8_t percentage_of_capitalization[4];        /* bytes 24 to 27 */
  uint8_t variation_from_previous_days_price[4];  /* bytes 28 to 31 */
  uint8_t system_id[4];                           /* bytes 32 to 35 */
  uint8_t source_time_micro_secs[2];              /* bytes 36 to 37 */
  uint8_t num_of_securities_quoted[2];            /* bytes 38 to 39 */
  uint8_t index_level_code;                       /* byte 40 */
  uint8_t type_of_level;                          /* byte 41 */
  uint8_t level_scale_code;                       /* byte 42 */
  uint8_t percentage_scale_code;                  /* byte 43 */
  uint8_t variation_scale_code;                   /* byte 44 */
  uint8_t rebroadcast_indicator;                  /* byte 45 */
  uint8_t filler_ascii_str_2[2];                  /* bytes 46 to 47 */
} RealTimeIndexMessage;

/* any Real Time Index Message at all: every byte one the checker chooses */
static void any_real_time_index_message(RealTimeIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->forerunner_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage_of_capitalization[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->variation_from_previous_days_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_of_securities_quoted[i] = arbitrary(); }
  record->index_level_code = arbitrary();
  record->type_of_level = arbitrary();
  record->level_scale_code = arbitrary();
  record->percentage_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
  record->rebroadcast_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = arbitrary(); }
}

/* Real Time Index Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_real_time_index_message(const RealTimeIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->forerunner_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage_of_capitalization[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->variation_from_previous_days_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_of_securities_quoted[i]; }
  wire[at++] = record->index_level_code;
  wire[at++] = record->type_of_level;
  wire[at++] = record->level_scale_code;
  wire[at++] = record->percentage_scale_code;
  wire[at++] = record->variation_scale_code;
  wire[at++] = record->rebroadcast_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler_ascii_str_2[i]; }

  return at;
}

/* Real Time Index Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_real_time_index_message(RealTimeIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->forerunner_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage_of_capitalization[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->variation_from_previous_days_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_of_securities_quoted[i] = wire[at++]; }
  record->index_level_code = wire[at++];
  record->type_of_level = wire[at++];
  record->level_scale_code = wire[at++];
  record->percentage_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];
  record->rebroadcast_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->filler_ascii_str_2[i] = wire[at++]; }

  return at;
}

/* what was read of Real Time Index Message is what was written, byte for byte */
static void equal_real_time_index_message(const RealTimeIndexMessage *read, const RealTimeIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_level[i] == written->index_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->forerunner_level[i] == written->forerunner_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_high[i] == written->session_high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_low[i] == written->session_low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage_of_capitalization[i] == written->percentage_of_capitalization[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->variation_from_previous_days_price[i] == written->variation_from_previous_days_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_of_securities_quoted[i] == written->num_of_securities_quoted[i]); }
  assert(read->index_level_code == written->index_level_code);
  assert(read->type_of_level == written->type_of_level);
  assert(read->level_scale_code == written->level_scale_code);
  assert(read->percentage_scale_code == written->percentage_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
  assert(read->rebroadcast_indicator == written->rebroadcast_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->filler_ascii_str_2[i] == written->filler_ascii_str_2[i]); }
}

/* Real Time Index Message: written and read back, then read and written back */
static void check_real_time_index_message(void) {
  RealTimeIndexMessage sent;
  RealTimeIndexMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_real_time_index_message(&sent);
  assert(encode_real_time_index_message(&sent, wire, 0) == 48);
  assert(decode_real_time_index_message(&got, wire, 0) == 48);
  equal_real_time_index_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_real_time_index_message(&got, wire, 0) == 48);
  assert(encode_real_time_index_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Summary Message: 88 bytes ----------------------------------------- */

/* An Index Summary message gives the summary of an index for the trading day. */
typedef struct {
  uint8_t symbol_index[4];                 /* bytes 0 to 3 */
  uint8_t source_time[4];                  /* bytes 4 to 7 */
  uint8_t preliminary_opening_level[4];    /* bytes 8 to 11 */
  uint8_t preliminary_opening_time[4];     /* bytes 12 to 15 */
  uint8_t first_level[4];                  /* bytes 16 to 19 */
  uint8_t first_time[4];                   /* bytes 20 to 23 */
  uint8_t opening_reference_level[4];      /* bytes 24 to 27 */
  uint8_t opening_reference_time[4];       /* bytes 28 to 31 */
  uint8_t closing_reference_level[4];      /* bytes 32 to 35 */
  uint8_t closing_reference_time[4];       /* bytes 36 to 39 */
  uint8_t percent_variation_prev_clos[4];  /* bytes 40 to 43 */
  uint8_t high_level[4];                   /* bytes 44 to 47 */
  uint8_t high_time[4];                    /* bytes 48 to 51 */
  uint8_t low_level[4];                    /* bytes 52 to 55 */
  uint8_t low_time[4];                     /* bytes 56 to 59 */
  uint8_t clearing_level[4];               /* bytes 60 to 63 */
  uint8_t clearing_time[4];                /* bytes 64 to 67 */
  uint8_t liquidation_level[4];            /* bytes 68 to 71 */
  uint8_t liquidation_time[4];             /* bytes 72 to 75 */
  uint8_t system_id[4];                    /* bytes 76 to 79 */
  uint8_t source_time_micro_secs[2];       /* bytes 80 to 81 */
  uint8_t type_of_level;                   /* byte 82 */
  uint8_t level_scale_code;                /* byte 83 */
  uint8_t variation_scale_code;            /* byte 84 */
  uint8_t filler_ascii_str_3[3];           /* bytes 85 to 87 */
} IndexSummaryMessage;

/* any Index Summary Message at all: every byte one the checker chooses */
static void any_index_summary_message(IndexSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->preliminary_opening_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->preliminary_opening_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_reference_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_reference_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_reference_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_reference_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percent_variation_prev_clos[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->high_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->low_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->liquidation_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->liquidation_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->type_of_level = arbitrary();
  record->level_scale_code = arbitrary();
  record->variation_scale_code = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = arbitrary(); }
}

/* Index Summary Message to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_index_summary_message(const IndexSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->preliminary_opening_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->preliminary_opening_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_reference_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_reference_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_reference_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_reference_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percent_variation_prev_clos[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->high_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->low_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->liquidation_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->liquidation_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->type_of_level;
  wire[at++] = record->level_scale_code;
  wire[at++] = record->variation_scale_code;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->filler_ascii_str_3[i]; }

  return at;
}

/* Index Summary Message off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_index_summary_message(IndexSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->preliminary_opening_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->preliminary_opening_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_reference_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_reference_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_reference_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_reference_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percent_variation_prev_clos[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->high_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->low_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->liquidation_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->liquidation_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->type_of_level = wire[at++];
  record->level_scale_code = wire[at++];
  record->variation_scale_code = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->filler_ascii_str_3[i] = wire[at++]; }

  return at;
}

/* what was read of Index Summary Message is what was written, byte for byte */
static void equal_index_summary_message(const IndexSummaryMessage *read, const IndexSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->preliminary_opening_level[i] == written->preliminary_opening_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->preliminary_opening_time[i] == written->preliminary_opening_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_level[i] == written->first_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_time[i] == written->first_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_reference_level[i] == written->opening_reference_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_reference_time[i] == written->opening_reference_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_reference_level[i] == written->closing_reference_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_reference_time[i] == written->closing_reference_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percent_variation_prev_clos[i] == written->percent_variation_prev_clos[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_level[i] == written->high_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->high_time[i] == written->high_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_level[i] == written->low_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->low_time[i] == written->low_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_level[i] == written->clearing_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_time[i] == written->clearing_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->liquidation_level[i] == written->liquidation_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->liquidation_time[i] == written->liquidation_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->type_of_level == written->type_of_level);
  assert(read->level_scale_code == written->level_scale_code);
  assert(read->variation_scale_code == written->variation_scale_code);
  for (size_t i = 0; i < 3; i++) { assert(read->filler_ascii_str_3[i] == written->filler_ascii_str_3[i]); }
}

/* Index Summary Message: written and read back, then read and written back */
static void check_index_summary_message(void) {
  IndexSummaryMessage sent;
  IndexSummaryMessage got;
  uint8_t wire[88];
  uint8_t again[88];

  any_index_summary_message(&sent);
  assert(encode_index_summary_message(&sent, wire, 0) == 88);
  assert(decode_index_summary_message(&got, wire, 0) == 88);
  equal_index_summary_message(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_index_summary_message(&got, wire, 0) == 88);
  assert(encode_index_summary_message(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Composition Message: 48 bytes ------------------------------------- */

/* An Index Composition message transmits one instrument making up an index, its weight and its adjustment coefficient. */
typedef struct {
  uint8_t symbol_index[4];                 /* bytes 0 to 3 */
  uint8_t source_time[4];                  /* bytes 4 to 7 */
  uint8_t instrument_weight[4];            /* bytes 8 to 11 */
  uint8_t instrument_factor[4];            /* bytes 12 to 15 */
  uint8_t previous_close[4];               /* bytes 16 to 19 */
  uint8_t system_id[4];                    /* bytes 20 to 23 */
  uint8_t source_time_micro_secs[2];       /* bytes 24 to 25 */
  uint8_t number_of_conponents[2];         /* bytes 26 to 27 */
  uint8_t instrument_id_of_component[12];  /* bytes 28 to 39 */
  uint8_t mnemo[5];                        /* bytes 40 to 44 */
  uint8_t index_frequency;                 /* byte 45 */
  uint8_t price_scale_code;                /* byte 46 */
  uint8_t level_scale_code;                /* byte 47 */
} IndexCompositionMessage;

/* any Index Composition Message at all: every byte one the checker chooses */
static void any_index_composition_message(IndexCompositionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_weight[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_factor[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->previous_close[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->number_of_conponents[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_of_component[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mnemo[i] = arbitrary(); }
  record->index_frequency = arbitrary();
  record->price_scale_code = arbitrary();
  record->level_scale_code = arbitrary();
}

/* Index Composition Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_index_composition_message(const IndexCompositionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_weight[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_factor[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->previous_close[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->number_of_conponents[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->instrument_id_of_component[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mnemo[i]; }
  wire[at++] = record->index_frequency;
  wire[at++] = record->price_scale_code;
  wire[at++] = record->level_scale_code;

  return at;
}

/* Index Composition Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_index_composition_message(IndexCompositionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_weight[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_factor[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->previous_close[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->number_of_conponents[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->instrument_id_of_component[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mnemo[i] = wire[at++]; }
  record->index_frequency = wire[at++];
  record->price_scale_code = wire[at++];
  record->level_scale_code = wire[at++];

  return at;
}

/* what was read of Index Composition Message is what was written, byte for byte */
static void equal_index_composition_message(const IndexCompositionMessage *read, const IndexCompositionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_weight[i] == written->instrument_weight[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_factor[i] == written->instrument_factor[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->previous_close[i] == written->previous_close[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->number_of_conponents[i] == written->number_of_conponents[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->instrument_id_of_component[i] == written->instrument_id_of_component[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mnemo[i] == written->mnemo[i]); }
  assert(read->index_frequency == written->index_frequency);
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->level_scale_code == written->level_scale_code);
}

/* Index Composition Message: written and read back, then read and written back */
static void check_index_composition_message(void) {
  IndexCompositionMessage sent;
  IndexCompositionMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_index_composition_message(&sent);
  assert(encode_index_composition_message(&sent, wire, 0) == 48);
  assert(decode_index_composition_message(&got, wire, 0) == 48);
  equal_index_composition_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_index_composition_message(&got, wire, 0) == 48);
  assert(encode_index_composition_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Start Refresh Message: 4 bytes ------------------------------------------ */

/* A refresh cycle begins with a Start Refresh message on the multicast channels. */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} StartRefreshMessage;

/* any Start Refresh Message at all: every byte one the checker chooses */
static void any_start_refresh_message(StartRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* Start Refresh Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_start_refresh_message(const StartRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* Start Refresh Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_start_refresh_message(StartRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Start Refresh Message is what was written, byte for byte */
static void equal_start_refresh_message(const StartRefreshMessage *read, const StartRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* Start Refresh Message: written and read back, then read and written back */
static void check_start_refresh_message(void) {
  StartRefreshMessage sent;
  StartRefreshMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_start_refresh_message(&sent);
  assert(encode_start_refresh_message(&sent, wire, 0) == 4);
  assert(decode_start_refresh_message(&got, wire, 0) == 4);
  equal_start_refresh_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_start_refresh_message(&got, wire, 0) == 4);
  assert(encode_start_refresh_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Refresh Message: 4 bytes -------------------------------------------- */

/* A refresh cycle ends with an End Refresh message on the multicast channels. */
typedef struct {
  uint8_t last_seq_num[4];  /* bytes 0 to 3 */
} EndRefreshMessage;

/* any End Refresh Message at all: every byte one the checker chooses */
static void any_end_refresh_message(EndRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = arbitrary(); }
}

/* End Refresh Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_refresh_message(const EndRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_seq_num[i]; }

  return at;
}

/* End Refresh Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_refresh_message(EndRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of End Refresh Message is what was written, byte for byte */
static void equal_end_refresh_message(const EndRefreshMessage *read, const EndRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_seq_num[i] == written->last_seq_num[i]); }
}

/* End Refresh Message: written and read back, then read and written back */
static void check_end_refresh_message(void) {
  EndRefreshMessage sent;
  EndRefreshMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_refresh_message(&sent);
  assert(encode_end_refresh_message(&sent, wire, 0) == 4);
  assert(decode_end_refresh_message(&got, wire, 0) == 4);
  equal_end_refresh_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_refresh_message(&got, wire, 0) == 4);
  assert(encode_end_refresh_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_stock_state_change_message();
  check_class_state_change_message();
  check_mail_message();
  check_indicative_matching_price_message();
  check_collars_message();
  check_session_timetable_message();
  check_global_market_activity_summary_message();
  check_start_referential_message();
  check_end_referential_message();
  check_referential_message();
  check_trade_creation_message();
  check_trade_cancellation_message();
  check_trade_full_information_message();
  check_price_update_message();
  check_auction_summary_message();
  check_vwap_closing_price_message();
  check_quotes_message();
  check_order_update_market_sheet_message();
  check_orderbook_retransmission_delimiter_message();
  check_real_time_index_message();
  check_index_summary_message();
  check_index_composition_message();
  check_start_refresh_message();
  check_end_refresh_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
