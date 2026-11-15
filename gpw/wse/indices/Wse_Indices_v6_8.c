// gpw/wse/indices/Wse_Indices_v6_8.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Indices
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
 *   - a run of a stated number of entries
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

/* All messages are preceded by a common packet header format, which section 1.1 states for every Market Information message */
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

/* ---- Real Time Index Message: 108 bytes -------------------------------------- */

/* The real time index message handles the real-time characteristics of an index */
typedef struct {
  uint8_t symbol_index[4];                       /* bytes 0 to 3 */
  uint8_t source_time[4];                        /* bytes 4 to 7 */
  uint8_t source_seq_num[4];                     /* bytes 8 to 11 */
  uint8_t system_id[4];                          /* bytes 12 to 15 */
  uint8_t index_level[4];                        /* bytes 16 to 19 */
  uint8_t session_high[4];                       /* bytes 20 to 23 */
  uint8_t session_low[4];                        /* bytes 24 to 27 */
  uint8_t ind_index_opening_portfolio[4];        /* bytes 28 to 31 */
  uint8_t percent_change_toi[4];                 /* bytes 32 to 35 */
  uint8_t pct_change_index_val_prev_session[4];  /* bytes 36 to 39 */
  uint8_t pct_change_index_val_prev_year[4];     /* bytes 40 to 43 */
  uint8_t toi[4];                                /* bytes 44 to 47 */
  uint8_t point_change[4];                       /* bytes 48 to 51 */
  uint8_t value_trading[8];                      /* bytes 52 to 59 */
  uint8_t index_value_bid[4];                    /* bytes 60 to 63 */
  uint8_t index_value_ask[4];                    /* bytes 64 to 67 */
  uint8_t mid_spread_index[4];                   /* bytes 68 to 71 */
  uint8_t difference_central_spread[4];          /* bytes 72 to 75 */
  uint8_t num_of_active_instruments[2];          /* bytes 76 to 77 */
  uint8_t num_of_instr_of_decreasing_qt[2];      /* bytes 78 to 79 */
  uint8_t num_of_instr_of_increasing_qt[2];      /* bytes 80 to 81 */
  uint8_t num_of_instr_of_unchanged_qt[2];       /* bytes 82 to 83 */
  uint8_t source_time_micro_secs[2];             /* bytes 84 to 85 */
  uint8_t level_scale_code;                      /* byte 86 */
  uint8_t time_first_high[6];                    /* bytes 87 to 92 */
  uint8_t time_first_low[6];                     /* bytes 93 to 98 */
  uint8_t index_status_indicator[2];             /* bytes 99 to 100 */
  uint8_t index_level_code;                      /* byte 101 */
  uint8_t marker_percent_change_toi;             /* byte 102 */
  uint8_t marker_pct_chg_index_val_prev_sess;    /* byte 103 */
  uint8_t marker_pct_chg_index_val_prev_year;    /* byte 104 */
  uint8_t marker_point_change;                   /* byte 105 */
  uint8_t marker_difference_central_spread;      /* byte 106 */
  uint8_t dissemination_frequency_marker;        /* byte 107 */
} RealTimeIndexMessage;

/* any Real Time Index Message at all: every byte one the checker chooses */
static void any_real_time_index_message(RealTimeIndexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_level[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ind_index_opening_portfolio[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percent_change_toi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->toi[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->point_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->value_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_value_bid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_value_ask[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_spread_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->difference_central_spread[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_of_active_instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_decreasing_qt[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_increasing_qt[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_unchanged_qt[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->level_scale_code = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_first_high[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_first_low[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->index_status_indicator[i] = arbitrary(); }
  record->index_level_code = arbitrary();
  record->marker_percent_change_toi = arbitrary();
  record->marker_pct_chg_index_val_prev_sess = arbitrary();
  record->marker_pct_chg_index_val_prev_year = arbitrary();
  record->marker_point_change = arbitrary();
  record->marker_difference_central_spread = arbitrary();
  record->dissemination_frequency_marker = arbitrary();
}

/* Real Time Index Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_real_time_index_message(const RealTimeIndexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_level[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ind_index_opening_portfolio[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percent_change_toi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_change_index_val_prev_session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_change_index_val_prev_year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->toi[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->point_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value_trading[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_value_bid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_value_ask[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_spread_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->difference_central_spread[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_of_active_instruments[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_of_instr_of_decreasing_qt[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_of_instr_of_increasing_qt[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_of_instr_of_unchanged_qt[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->level_scale_code;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_first_high[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_first_low[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->index_status_indicator[i]; }
  wire[at++] = record->index_level_code;
  wire[at++] = record->marker_percent_change_toi;
  wire[at++] = record->marker_pct_chg_index_val_prev_sess;
  wire[at++] = record->marker_pct_chg_index_val_prev_year;
  wire[at++] = record->marker_point_change;
  wire[at++] = record->marker_difference_central_spread;
  wire[at++] = record->dissemination_frequency_marker;

  return at;
}

/* Real Time Index Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_real_time_index_message(RealTimeIndexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_level[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ind_index_opening_portfolio[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percent_change_toi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->toi[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->point_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->value_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_value_bid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_value_ask[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_spread_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->difference_central_spread[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_of_active_instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_decreasing_qt[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_increasing_qt[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_of_instr_of_unchanged_qt[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->level_scale_code = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_first_high[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_first_low[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->index_status_indicator[i] = wire[at++]; }
  record->index_level_code = wire[at++];
  record->marker_percent_change_toi = wire[at++];
  record->marker_pct_chg_index_val_prev_sess = wire[at++];
  record->marker_pct_chg_index_val_prev_year = wire[at++];
  record->marker_point_change = wire[at++];
  record->marker_difference_central_spread = wire[at++];
  record->dissemination_frequency_marker = wire[at++];

  return at;
}

/* what was read of Real Time Index Message is what was written, byte for byte */
static void equal_real_time_index_message(const RealTimeIndexMessage *read, const RealTimeIndexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_level[i] == written->index_level[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_high[i] == written->session_high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_low[i] == written->session_low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ind_index_opening_portfolio[i] == written->ind_index_opening_portfolio[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percent_change_toi[i] == written->percent_change_toi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_change_index_val_prev_session[i] == written->pct_change_index_val_prev_session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_change_index_val_prev_year[i] == written->pct_change_index_val_prev_year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->toi[i] == written->toi[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->point_change[i] == written->point_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->value_trading[i] == written->value_trading[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_value_bid[i] == written->index_value_bid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_value_ask[i] == written->index_value_ask[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_spread_index[i] == written->mid_spread_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->difference_central_spread[i] == written->difference_central_spread[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_of_active_instruments[i] == written->num_of_active_instruments[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_of_instr_of_decreasing_qt[i] == written->num_of_instr_of_decreasing_qt[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_of_instr_of_increasing_qt[i] == written->num_of_instr_of_increasing_qt[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_of_instr_of_unchanged_qt[i] == written->num_of_instr_of_unchanged_qt[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->level_scale_code == written->level_scale_code);
  for (size_t i = 0; i < 6; i++) { assert(read->time_first_high[i] == written->time_first_high[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_first_low[i] == written->time_first_low[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->index_status_indicator[i] == written->index_status_indicator[i]); }
  assert(read->index_level_code == written->index_level_code);
  assert(read->marker_percent_change_toi == written->marker_percent_change_toi);
  assert(read->marker_pct_chg_index_val_prev_sess == written->marker_pct_chg_index_val_prev_sess);
  assert(read->marker_pct_chg_index_val_prev_year == written->marker_pct_chg_index_val_prev_year);
  assert(read->marker_point_change == written->marker_point_change);
  assert(read->marker_difference_central_spread == written->marker_difference_central_spread);
  assert(read->dissemination_frequency_marker == written->dissemination_frequency_marker);
}

/* Real Time Index Message: written and read back, then read and written back */
static void check_real_time_index_message(void) {
  RealTimeIndexMessage sent;
  RealTimeIndexMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_real_time_index_message(&sent);
  assert(encode_real_time_index_message(&sent, wire, 0) == 108);
  assert(decode_real_time_index_message(&got, wire, 0) == 108);
  equal_real_time_index_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_real_time_index_message(&got, wire, 0) == 108);
  assert(encode_real_time_index_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Summary Message: 100 bytes ---------------------------------------- */

/* The index summary message provides a summary of the data calculated in a stock index for a given day */
typedef struct {
  uint8_t symbol_index[4];                         /* bytes 0 to 3 */
  uint8_t source_time[4];                          /* bytes 4 to 7 */
  uint8_t source_seq_num[4];                       /* bytes 8 to 11 */
  uint8_t system_id[4];                            /* bytes 12 to 15 */
  uint8_t closing_index_value[4];                  /* bytes 16 to 19 */
  uint8_t ind_opening_portfolio[4];                /* bytes 20 to 23 */
  uint8_t opening_index_value[4];                  /* bytes 24 to 27 */
  uint8_t session_high[4];                         /* bytes 28 to 31 */
  uint8_t session_low[4];                          /* bytes 32 to 35 */
  uint8_t pct_chg_high_index_val_prev_session[4];  /* bytes 36 to 39 */
  uint8_t pct_chg_low_index_val_prev_session[4];   /* bytes 40 to 43 */
  uint8_t pct_change_index_val_prev_session[4];    /* bytes 44 to 47 */
  uint8_t pct_change_index_val_prev_year[4];       /* bytes 48 to 51 */
  uint8_t capitalisation_portfolio[4];             /* bytes 52 to 55 */
  uint8_t index_adjustment_coefficient[4];         /* bytes 56 to 59 */
  uint8_t source_time_micro_secs[2];               /* bytes 60 to 61 */
  uint8_t level_scale_code;                        /* byte 62 */
  uint8_t capitalisation_scale_code;               /* byte 63 */
  uint8_t index_adjustment_scale_code;             /* byte 64 */
  uint8_t time_closing[6];                         /* bytes 65 to 70 */
  uint8_t time_opening[6];                         /* bytes 71 to 76 */
  uint8_t time_full_opening[6];                    /* bytes 77 to 82 */
  uint8_t time_high[6];                            /* bytes 83 to 88 */
  uint8_t time_low[6];                             /* bytes 89 to 94 */
  uint8_t marker_high;                             /* byte 95 */
  uint8_t marker_low;                              /* byte 96 */
  uint8_t marker_closing_prev_session;             /* byte 97 */
  uint8_t marker_closing_prev_year;                /* byte 98 */
  uint8_t reserved_1;                              /* byte 99 */
} IndexSummaryMessage;

/* any Index Summary Message at all: every byte one the checker chooses */
static void any_index_summary_message(IndexSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ind_opening_portfolio[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_chg_high_index_val_prev_session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_chg_low_index_val_prev_session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_session[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->capitalisation_portfolio[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->index_adjustment_coefficient[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->level_scale_code = arbitrary();
  record->capitalisation_scale_code = arbitrary();
  record->index_adjustment_scale_code = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_closing[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_opening[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_full_opening[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_high[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_low[i] = arbitrary(); }
  record->marker_high = arbitrary();
  record->marker_low = arbitrary();
  record->marker_closing_prev_session = arbitrary();
  record->marker_closing_prev_year = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Index Summary Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_index_summary_message(const IndexSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_index_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ind_opening_portfolio[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_index_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_high[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_low[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_chg_high_index_val_prev_session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_chg_low_index_val_prev_session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_change_index_val_prev_session[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_change_index_val_prev_year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->capitalisation_portfolio[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_adjustment_coefficient[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->level_scale_code;
  wire[at++] = record->capitalisation_scale_code;
  wire[at++] = record->index_adjustment_scale_code;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_closing[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_opening[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_full_opening[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_high[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_low[i]; }
  wire[at++] = record->marker_high;
  wire[at++] = record->marker_low;
  wire[at++] = record->marker_closing_prev_session;
  wire[at++] = record->marker_closing_prev_year;
  wire[at++] = record->reserved_1;

  return at;
}

/* Index Summary Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_index_summary_message(IndexSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ind_opening_portfolio[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_high[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_low[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_chg_high_index_val_prev_session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_chg_low_index_val_prev_session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_session[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_change_index_val_prev_year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->capitalisation_portfolio[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->index_adjustment_coefficient[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->level_scale_code = wire[at++];
  record->capitalisation_scale_code = wire[at++];
  record->index_adjustment_scale_code = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_closing[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_opening[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_full_opening[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_high[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_low[i] = wire[at++]; }
  record->marker_high = wire[at++];
  record->marker_low = wire[at++];
  record->marker_closing_prev_session = wire[at++];
  record->marker_closing_prev_year = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Index Summary Message is what was written, byte for byte */
static void equal_index_summary_message(const IndexSummaryMessage *read, const IndexSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_index_value[i] == written->closing_index_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ind_opening_portfolio[i] == written->ind_opening_portfolio[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_index_value[i] == written->opening_index_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_high[i] == written->session_high[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_low[i] == written->session_low[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_chg_high_index_val_prev_session[i] == written->pct_chg_high_index_val_prev_session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_chg_low_index_val_prev_session[i] == written->pct_chg_low_index_val_prev_session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_change_index_val_prev_session[i] == written->pct_change_index_val_prev_session[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_change_index_val_prev_year[i] == written->pct_change_index_val_prev_year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->capitalisation_portfolio[i] == written->capitalisation_portfolio[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->index_adjustment_coefficient[i] == written->index_adjustment_coefficient[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->level_scale_code == written->level_scale_code);
  assert(read->capitalisation_scale_code == written->capitalisation_scale_code);
  assert(read->index_adjustment_scale_code == written->index_adjustment_scale_code);
  for (size_t i = 0; i < 6; i++) { assert(read->time_closing[i] == written->time_closing[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_opening[i] == written->time_opening[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_full_opening[i] == written->time_full_opening[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_high[i] == written->time_high[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_low[i] == written->time_low[i]); }
  assert(read->marker_high == written->marker_high);
  assert(read->marker_low == written->marker_low);
  assert(read->marker_closing_prev_session == written->marker_closing_prev_session);
  assert(read->marker_closing_prev_year == written->marker_closing_prev_year);
  assert(read->reserved_1 == written->reserved_1);
}

/* Index Summary Message: written and read back, then read and written back */
static void check_index_summary_message(void) {
  IndexSummaryMessage sent;
  IndexSummaryMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_index_summary_message(&sent);
  assert(encode_index_summary_message(&sent, wire, 0) == 100);
  assert(decode_index_summary_message(&got, wire, 0) == 100);
  equal_index_summary_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_index_summary_message(&got, wire, 0) == 100);
  assert(encode_index_summary_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_real_time_index_message();
  check_index_summary_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
