// gpw/wse/marketinformation/Wse_MarketInformation_v6_8.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Market Information
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

/* ---- Class State Change Message: 24 bytes ------------------------------------ */

/* The Class State Change message indicates a change in the state of a class */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t instrument_group_code[3];   /* bytes 14 to 16 */
  uint8_t instrument_group_state;     /* byte 17 */
  uint8_t session_type;               /* byte 18 */
  uint8_t reserved_1;                 /* byte 19 */
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
  record->reserved_1 = arbitrary();
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
  wire[at++] = record->reserved_1;
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
  record->reserved_1 = wire[at++];
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
  assert(read->reserved_1 == written->reserved_1);
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

/* ---- Mail Message: 1098 bytes ------------------------------------------------ */

/* This message supplies a part or a complete electronic message (E-mail), in order to inform members and rebroadcasting members about quotation conditions on a given listed instrument or a set of listed instruments or otherwise about a technical problem */
typedef struct {
  uint8_t source_seq_num[4];          /* bytes 0 to 3 */
  uint8_t source_time[4];             /* bytes 4 to 7 */
  uint8_t system_id[4];               /* bytes 8 to 11 */
  uint8_t source_time_micro_secs[2];  /* bytes 12 to 13 */
  uint8_t scope;                      /* byte 14 */
  uint8_t title[80];                  /* bytes 15 to 94 */
  uint8_t text_ascii_str_1000[1000];  /* bytes 95 to 1094 */
  uint8_t reserved_3[3];              /* bytes 1095 to 1097 */
} MailMessage;

/* any Mail Message at all: every byte one the checker chooses */
static void any_mail_message(MailMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->scope = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->title[i] = arbitrary(); }
  for (size_t i = 0; i < 1000; i++) { record->text_ascii_str_1000[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Mail Message to the wire: 1098 bytes from at, returning where the next byte goes */
static size_t encode_mail_message(const MailMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->scope;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->title[i]; }
  for (size_t i = 0; i < 1000; i++) { wire[at++] = record->text_ascii_str_1000[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Mail Message off the wire: 1098 bytes from at, returning where the next byte lies */
static size_t decode_mail_message(MailMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->scope = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->title[i] = wire[at++]; }
  for (size_t i = 0; i < 1000; i++) { record->text_ascii_str_1000[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Mail Message is what was written, byte for byte */
static void equal_mail_message(const MailMessage *read, const MailMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->scope == written->scope);
  for (size_t i = 0; i < 80; i++) { assert(read->title[i] == written->title[i]); }
  for (size_t i = 0; i < 1000; i++) { assert(read->text_ascii_str_1000[i] == written->text_ascii_str_1000[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Mail Message: written and read back, then read and written back */
static void check_mail_message(void) {
  MailMessage sent;
  MailMessage got;
  uint8_t wire[1098];
  uint8_t again[1098];

  any_mail_message(&sent);
  assert(encode_mail_message(&sent, wire, 0) == 1098);
  assert(decode_mail_message(&got, wire, 0) == 1098);
  equal_mail_message(&got, &sent);

  for (size_t i = 0; i < 1098; i++) { wire[i] = arbitrary(); }
  assert(decode_mail_message(&got, wire, 0) == 1098);
  assert(encode_mail_message(&got, again, 0) == 1098);
  for (size_t i = 0; i < 1098; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collars Message: 32 bytes ----------------------------------------------- */

/* A Collars message informs Clients of modifications in authorized price fluctuations for an instrument */
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
  uint8_t reserved_3[3];              /* bytes 29 to 31 */
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
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
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
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

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
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

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
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
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

/* ---- Start Referential Message: 4 bytes -------------------------------------- */

/* The Start referential message is sent to signal the start of transmission of the Instrument Reference Data Flow */
typedef struct {
  uint8_t indicator;      /* byte 0 */
  uint8_t reserved_3[3];  /* bytes 1 to 3 */
} StartReferentialMessage;

/* any Start Referential Message at all: every byte one the checker chooses */
static void any_start_referential_message(StartReferentialMessage *record) {
  record->indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Start Referential Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_start_referential_message(const StartReferentialMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Start Referential Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_start_referential_message(StartReferentialMessage *record, const uint8_t *wire, size_t at) {
  record->indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Start Referential Message is what was written, byte for byte */
static void equal_start_referential_message(const StartReferentialMessage *read, const StartReferentialMessage *written) {
  assert(read->indicator == written->indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
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

/* The End referential message is sent to signal the end of transmission of the Instrument Reference Data Flow */
typedef struct {
  uint8_t indicator;      /* byte 0 */
  uint8_t reserved_3[3];  /* bytes 1 to 3 */
} EndReferentialMessage;

/* any End Referential Message at all: every byte one the checker chooses */
static void any_end_referential_message(EndReferentialMessage *record) {
  record->indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* End Referential Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_referential_message(const EndReferentialMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* End Referential Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_referential_message(EndReferentialMessage *record, const uint8_t *wire, size_t at) {
  record->indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of End Referential Message is what was written, byte for byte */
static void equal_end_referential_message(const EndReferentialMessage *read, const EndReferentialMessage *written) {
  assert(read->indicator == written->indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
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

/* ---- Session Summary Message: 260 bytes -------------------------------------- */

/* This message contains statistical data */
typedef struct {
  uint8_t symbol_index[4];                        /* bytes 0 to 3 */
  uint8_t source_time[4];                         /* bytes 4 to 7 */
  uint8_t source_seq_num[4];                      /* bytes 8 to 11 */
  uint8_t date_binary_int_4[4];                   /* bytes 12 to 15 */
  uint8_t multiplier[4];                          /* bytes 16 to 19 */
  uint8_t accumulated_interest[4];                /* bytes 20 to 23 */
  uint8_t opening_price[4];                       /* bytes 24 to 27 */
  uint8_t maximum_price[4];                       /* bytes 28 to 31 */
  uint8_t minimum_price[4];                       /* bytes 32 to 35 */
  uint8_t closing_price[4];                       /* bytes 36 to 39 */
  uint8_t implied_volatility[4];                  /* bytes 40 to 43 */
  uint8_t average_weighted_price[4];              /* bytes 44 to 47 */
  uint8_t reference_price[4];                     /* bytes 48 to 51 */
  uint8_t pct_change_price[4];                    /* bytes 52 to 55 */
  uint8_t dividend_rate[4];                       /* bytes 56 to 59 */
  uint8_t settlement_price[4];                    /* bytes 60 to 63 */
  uint8_t settlement_value[4];                    /* bytes 64 to 67 */
  uint8_t reserved_4[4];                          /* bytes 68 to 71 */
  uint8_t open_positions[4];                      /* bytes 72 to 75 */
  uint8_t trading_volume[4];                      /* bytes 76 to 79 */
  uint8_t transactions_number[4];                 /* bytes 80 to 83 */
  uint8_t trading_value[8];                       /* bytes 84 to 91 */
  uint8_t currency_price[4];                      /* bytes 92 to 95 */
  uint8_t delta[4];                               /* bytes 96 to 99 */
  uint8_t gamma[4];                               /* bytes 100 to 103 */
  uint8_t rho[4];                                 /* bytes 104 to 107 */
  uint8_t theta[4];                               /* bytes 108 to 111 */
  uint8_t vega[4];                                /* bytes 112 to 115 */
  uint8_t end_trading[4];                         /* bytes 116 to 119 */
  uint8_t number_of_instruments[4];               /* bytes 120 to 123 */
  uint8_t trading_value_currency[8];              /* bytes 124 to 131 */
  uint8_t interest_rate[4];                       /* bytes 132 to 135 */
  uint8_t volatility[4];                          /* bytes 136 to 139 */
  uint8_t strike_price[4];                        /* bytes 140 to 143 */
  uint8_t short_selling_trades_number[4];         /* bytes 144 to 147 */
  uint8_t volume_short_selling_trades[4];         /* bytes 148 to 151 */
  uint8_t value_short_selling_trades[4];          /* bytes 152 to 155 */
  uint8_t last_trade_date[4];                     /* bytes 156 to 159 */
  uint8_t last_trade_price[4];                    /* bytes 160 to 163 */
  uint8_t block_trades_number[4];                 /* bytes 164 to 167 */
  uint8_t volume_block_trades[4];                 /* bytes 168 to 171 */
  uint8_t value_block_trades[4];                  /* bytes 172 to 175 */
  uint8_t vwap_blocktrade[4];                     /* bytes 176 to 179 */
  uint8_t maximum_block_price[4];                 /* bytes 180 to 183 */
  uint8_t minimum_block_price[4];                 /* bytes 184 to 187 */
  uint8_t system_id[4];                           /* bytes 188 to 191 */
  uint8_t source_time_micro_secs[2];              /* bytes 192 to 193 */
  uint8_t multiplier_scale_code;                  /* byte 194 */
  uint8_t accumulated_interest_scale_code;        /* byte 195 */
  uint8_t opening_price_scale_code;               /* byte 196 */
  uint8_t maximum_price_scale_code;               /* byte 197 */
  uint8_t minimum_price_scale_code;               /* byte 198 */
  uint8_t closing_price_scale_code;               /* byte 199 */
  uint8_t implied_volatility_scale_code;          /* byte 200 */
  uint8_t average_weighted_price_scale_code;      /* byte 201 */
  uint8_t reference_price_scale_code;             /* byte 202 */
  uint8_t pct_change_price_scale_code;            /* byte 203 */
  uint8_t dividend_rate_scale_code;               /* byte 204 */
  uint8_t settlement_price_scale_code;            /* byte 205 */
  uint8_t settlement_value_scale_code;            /* byte 206 */
  uint8_t reserved_1;                             /* byte 207 */
  uint8_t trading_value_scale_code;               /* byte 208 */
  uint8_t currency_price_scale_code;              /* byte 209 */
  uint8_t delta_scale_code;                       /* byte 210 */
  uint8_t gamma_scale_code;                       /* byte 211 */
  uint8_t rho_scale_code;                         /* byte 212 */
  uint8_t theta_scale_code;                       /* byte 213 */
  uint8_t vega_scale_code;                        /* byte 214 */
  uint8_t trading_value_currency_scale_code;      /* byte 215 */
  uint8_t interest_rate_scale_code;               /* byte 216 */
  uint8_t volatility_scale_code;                  /* byte 217 */
  uint8_t strike_price_scale_code;                /* byte 218 */
  uint8_t value_short_selling_trades_scale_code;  /* byte 219 */
  uint8_t last_trade_price_scale_code;            /* byte 220 */
  uint8_t value_block_trades_scale_code;          /* byte 221 */
  uint8_t vwap_blocktrade_scale_code;             /* byte 222 */
  uint8_t maximum_block_price_scale_code;         /* byte 223 */
  uint8_t minimum_block_price_scale_code;         /* byte 224 */
  uint8_t status_indicator;                       /* byte 225 */
  uint8_t sector[3];                              /* bytes 226 to 228 */
  uint8_t market;                                 /* byte 229 */
  uint8_t second_reserved_1;                      /* byte 230 */
  uint8_t short_sale;                             /* byte 231 */
  uint8_t marker_pct_change_price;                /* byte 232 */
  uint8_t symbol_delta;                           /* byte 233 */
  uint8_t symbol_gamma;                           /* byte 234 */
  uint8_t symbol_rho;                             /* byte 235 */
  uint8_t symbol_theta;                           /* byte 236 */
  uint8_t symbol_vega;                            /* byte 237 */
  uint8_t third_reserved_1;                       /* byte 238 */
  uint8_t fourth_reserved_1;                      /* byte 239 */
  uint8_t fifth_reserved_1;                       /* byte 240 */
  uint8_t sixth_reserved_1;                       /* byte 241 */
  uint8_t seventh_reserved_1;                     /* byte 242 */
  uint8_t eighth_reserved_1;                      /* byte 243 */
  uint8_t segment[2];                             /* bytes 244 to 245 */
  uint8_t lower_liquidity;                        /* byte 246 */
  uint8_t dividend[2];                            /* bytes 247 to 248 */
  uint8_t subscription_right[2];                  /* bytes 249 to 250 */
  uint8_t split[2];                               /* bytes 251 to 252 */
  uint8_t interim_dividend_right[2];              /* bytes 253 to 254 */
  uint8_t quotation_system[2];                    /* bytes 255 to 256 */
  uint8_t liquidity_support_pge[2];               /* bytes 257 to 258 */
  uint8_t ninth_reserved_1;                       /* byte 259 */
} SessionSummaryMessage;

/* any Session Summary Message at all: every byte one the checker chooses */
static void any_session_summary_message(SessionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date_binary_int_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->accumulated_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maximum_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->implied_volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->average_weighted_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pct_change_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->dividend_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settlement_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_positions[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transactions_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_value[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->currency_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->gamma[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rho[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->theta[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_trading[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->number_of_instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_value_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->interest_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->short_selling_trades_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_short_selling_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->value_short_selling_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->block_trades_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volume_block_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->value_block_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->vwap_blocktrade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maximum_block_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_block_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->multiplier_scale_code = arbitrary();
  record->accumulated_interest_scale_code = arbitrary();
  record->opening_price_scale_code = arbitrary();
  record->maximum_price_scale_code = arbitrary();
  record->minimum_price_scale_code = arbitrary();
  record->closing_price_scale_code = arbitrary();
  record->implied_volatility_scale_code = arbitrary();
  record->average_weighted_price_scale_code = arbitrary();
  record->reference_price_scale_code = arbitrary();
  record->pct_change_price_scale_code = arbitrary();
  record->dividend_rate_scale_code = arbitrary();
  record->settlement_price_scale_code = arbitrary();
  record->settlement_value_scale_code = arbitrary();
  record->reserved_1 = arbitrary();
  record->trading_value_scale_code = arbitrary();
  record->currency_price_scale_code = arbitrary();
  record->delta_scale_code = arbitrary();
  record->gamma_scale_code = arbitrary();
  record->rho_scale_code = arbitrary();
  record->theta_scale_code = arbitrary();
  record->vega_scale_code = arbitrary();
  record->trading_value_currency_scale_code = arbitrary();
  record->interest_rate_scale_code = arbitrary();
  record->volatility_scale_code = arbitrary();
  record->strike_price_scale_code = arbitrary();
  record->value_short_selling_trades_scale_code = arbitrary();
  record->last_trade_price_scale_code = arbitrary();
  record->value_block_trades_scale_code = arbitrary();
  record->vwap_blocktrade_scale_code = arbitrary();
  record->maximum_block_price_scale_code = arbitrary();
  record->minimum_block_price_scale_code = arbitrary();
  record->status_indicator = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sector[i] = arbitrary(); }
  record->market = arbitrary();
  record->second_reserved_1 = arbitrary();
  record->short_sale = arbitrary();
  record->marker_pct_change_price = arbitrary();
  record->symbol_delta = arbitrary();
  record->symbol_gamma = arbitrary();
  record->symbol_rho = arbitrary();
  record->symbol_theta = arbitrary();
  record->symbol_vega = arbitrary();
  record->third_reserved_1 = arbitrary();
  record->fourth_reserved_1 = arbitrary();
  record->fifth_reserved_1 = arbitrary();
  record->sixth_reserved_1 = arbitrary();
  record->seventh_reserved_1 = arbitrary();
  record->eighth_reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->segment[i] = arbitrary(); }
  record->lower_liquidity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->subscription_right[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->split[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->interim_dividend_right[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quotation_system[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->liquidity_support_pge[i] = arbitrary(); }
  record->ninth_reserved_1 = arbitrary();
}

/* Session Summary Message to the wire: 260 bytes from at, returning where the next byte goes */
static size_t encode_session_summary_message(const SessionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_binary_int_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->multiplier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->accumulated_interest[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maximum_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->implied_volatility[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->average_weighted_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pct_change_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->dividend_rate[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_positions[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_volume[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transactions_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_value[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->currency_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->gamma[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rho[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->theta[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vega[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_trading[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_instruments[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_value_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->interest_rate[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_selling_trades_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_short_selling_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value_short_selling_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trade_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->block_trades_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volume_block_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->value_block_trades[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->vwap_blocktrade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maximum_block_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_block_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->multiplier_scale_code;
  wire[at++] = record->accumulated_interest_scale_code;
  wire[at++] = record->opening_price_scale_code;
  wire[at++] = record->maximum_price_scale_code;
  wire[at++] = record->minimum_price_scale_code;
  wire[at++] = record->closing_price_scale_code;
  wire[at++] = record->implied_volatility_scale_code;
  wire[at++] = record->average_weighted_price_scale_code;
  wire[at++] = record->reference_price_scale_code;
  wire[at++] = record->pct_change_price_scale_code;
  wire[at++] = record->dividend_rate_scale_code;
  wire[at++] = record->settlement_price_scale_code;
  wire[at++] = record->settlement_value_scale_code;
  wire[at++] = record->reserved_1;
  wire[at++] = record->trading_value_scale_code;
  wire[at++] = record->currency_price_scale_code;
  wire[at++] = record->delta_scale_code;
  wire[at++] = record->gamma_scale_code;
  wire[at++] = record->rho_scale_code;
  wire[at++] = record->theta_scale_code;
  wire[at++] = record->vega_scale_code;
  wire[at++] = record->trading_value_currency_scale_code;
  wire[at++] = record->interest_rate_scale_code;
  wire[at++] = record->volatility_scale_code;
  wire[at++] = record->strike_price_scale_code;
  wire[at++] = record->value_short_selling_trades_scale_code;
  wire[at++] = record->last_trade_price_scale_code;
  wire[at++] = record->value_block_trades_scale_code;
  wire[at++] = record->vwap_blocktrade_scale_code;
  wire[at++] = record->maximum_block_price_scale_code;
  wire[at++] = record->minimum_block_price_scale_code;
  wire[at++] = record->status_indicator;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sector[i]; }
  wire[at++] = record->market;
  wire[at++] = record->second_reserved_1;
  wire[at++] = record->short_sale;
  wire[at++] = record->marker_pct_change_price;
  wire[at++] = record->symbol_delta;
  wire[at++] = record->symbol_gamma;
  wire[at++] = record->symbol_rho;
  wire[at++] = record->symbol_theta;
  wire[at++] = record->symbol_vega;
  wire[at++] = record->third_reserved_1;
  wire[at++] = record->fourth_reserved_1;
  wire[at++] = record->fifth_reserved_1;
  wire[at++] = record->sixth_reserved_1;
  wire[at++] = record->seventh_reserved_1;
  wire[at++] = record->eighth_reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->segment[i]; }
  wire[at++] = record->lower_liquidity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->dividend[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->subscription_right[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->split[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->interim_dividend_right[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quotation_system[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->liquidity_support_pge[i]; }
  wire[at++] = record->ninth_reserved_1;

  return at;
}

/* Session Summary Message off the wire: 260 bytes from at, returning where the next byte lies */
static size_t decode_session_summary_message(SessionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date_binary_int_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->accumulated_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maximum_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->implied_volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->average_weighted_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pct_change_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->dividend_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settlement_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_positions[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transactions_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_value[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->currency_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->gamma[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rho[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->theta[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vega[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_trading[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->number_of_instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_value_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->interest_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->short_selling_trades_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_short_selling_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->value_short_selling_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->block_trades_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volume_block_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->value_block_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->vwap_blocktrade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maximum_block_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_block_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->multiplier_scale_code = wire[at++];
  record->accumulated_interest_scale_code = wire[at++];
  record->opening_price_scale_code = wire[at++];
  record->maximum_price_scale_code = wire[at++];
  record->minimum_price_scale_code = wire[at++];
  record->closing_price_scale_code = wire[at++];
  record->implied_volatility_scale_code = wire[at++];
  record->average_weighted_price_scale_code = wire[at++];
  record->reference_price_scale_code = wire[at++];
  record->pct_change_price_scale_code = wire[at++];
  record->dividend_rate_scale_code = wire[at++];
  record->settlement_price_scale_code = wire[at++];
  record->settlement_value_scale_code = wire[at++];
  record->reserved_1 = wire[at++];
  record->trading_value_scale_code = wire[at++];
  record->currency_price_scale_code = wire[at++];
  record->delta_scale_code = wire[at++];
  record->gamma_scale_code = wire[at++];
  record->rho_scale_code = wire[at++];
  record->theta_scale_code = wire[at++];
  record->vega_scale_code = wire[at++];
  record->trading_value_currency_scale_code = wire[at++];
  record->interest_rate_scale_code = wire[at++];
  record->volatility_scale_code = wire[at++];
  record->strike_price_scale_code = wire[at++];
  record->value_short_selling_trades_scale_code = wire[at++];
  record->last_trade_price_scale_code = wire[at++];
  record->value_block_trades_scale_code = wire[at++];
  record->vwap_blocktrade_scale_code = wire[at++];
  record->maximum_block_price_scale_code = wire[at++];
  record->minimum_block_price_scale_code = wire[at++];
  record->status_indicator = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sector[i] = wire[at++]; }
  record->market = wire[at++];
  record->second_reserved_1 = wire[at++];
  record->short_sale = wire[at++];
  record->marker_pct_change_price = wire[at++];
  record->symbol_delta = wire[at++];
  record->symbol_gamma = wire[at++];
  record->symbol_rho = wire[at++];
  record->symbol_theta = wire[at++];
  record->symbol_vega = wire[at++];
  record->third_reserved_1 = wire[at++];
  record->fourth_reserved_1 = wire[at++];
  record->fifth_reserved_1 = wire[at++];
  record->sixth_reserved_1 = wire[at++];
  record->seventh_reserved_1 = wire[at++];
  record->eighth_reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->segment[i] = wire[at++]; }
  record->lower_liquidity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->subscription_right[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->split[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->interim_dividend_right[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quotation_system[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->liquidity_support_pge[i] = wire[at++]; }
  record->ninth_reserved_1 = wire[at++];

  return at;
}

/* what was read of Session Summary Message is what was written, byte for byte */
static void equal_session_summary_message(const SessionSummaryMessage *read, const SessionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date_binary_int_4[i] == written->date_binary_int_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->multiplier[i] == written->multiplier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->accumulated_interest[i] == written->accumulated_interest[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maximum_price[i] == written->maximum_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_price[i] == written->minimum_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->implied_volatility[i] == written->implied_volatility[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->average_weighted_price[i] == written->average_weighted_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pct_change_price[i] == written->pct_change_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->dividend_rate[i] == written->dividend_rate[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_price[i] == written->settlement_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_value[i] == written->settlement_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_positions[i] == written->open_positions[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_volume[i] == written->trading_volume[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transactions_number[i] == written->transactions_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_value[i] == written->trading_value[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->currency_price[i] == written->currency_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delta[i] == written->delta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->gamma[i] == written->gamma[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rho[i] == written->rho[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->theta[i] == written->theta[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vega[i] == written->vega[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_trading[i] == written->end_trading[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_instruments[i] == written->number_of_instruments[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_value_currency[i] == written->trading_value_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->interest_rate[i] == written->interest_rate[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->short_selling_trades_number[i] == written->short_selling_trades_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_short_selling_trades[i] == written->volume_short_selling_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->value_short_selling_trades[i] == written->value_short_selling_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_date[i] == written->last_trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trade_price[i] == written->last_trade_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->block_trades_number[i] == written->block_trades_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volume_block_trades[i] == written->volume_block_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->value_block_trades[i] == written->value_block_trades[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->vwap_blocktrade[i] == written->vwap_blocktrade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maximum_block_price[i] == written->maximum_block_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_block_price[i] == written->minimum_block_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->multiplier_scale_code == written->multiplier_scale_code);
  assert(read->accumulated_interest_scale_code == written->accumulated_interest_scale_code);
  assert(read->opening_price_scale_code == written->opening_price_scale_code);
  assert(read->maximum_price_scale_code == written->maximum_price_scale_code);
  assert(read->minimum_price_scale_code == written->minimum_price_scale_code);
  assert(read->closing_price_scale_code == written->closing_price_scale_code);
  assert(read->implied_volatility_scale_code == written->implied_volatility_scale_code);
  assert(read->average_weighted_price_scale_code == written->average_weighted_price_scale_code);
  assert(read->reference_price_scale_code == written->reference_price_scale_code);
  assert(read->pct_change_price_scale_code == written->pct_change_price_scale_code);
  assert(read->dividend_rate_scale_code == written->dividend_rate_scale_code);
  assert(read->settlement_price_scale_code == written->settlement_price_scale_code);
  assert(read->settlement_value_scale_code == written->settlement_value_scale_code);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->trading_value_scale_code == written->trading_value_scale_code);
  assert(read->currency_price_scale_code == written->currency_price_scale_code);
  assert(read->delta_scale_code == written->delta_scale_code);
  assert(read->gamma_scale_code == written->gamma_scale_code);
  assert(read->rho_scale_code == written->rho_scale_code);
  assert(read->theta_scale_code == written->theta_scale_code);
  assert(read->vega_scale_code == written->vega_scale_code);
  assert(read->trading_value_currency_scale_code == written->trading_value_currency_scale_code);
  assert(read->interest_rate_scale_code == written->interest_rate_scale_code);
  assert(read->volatility_scale_code == written->volatility_scale_code);
  assert(read->strike_price_scale_code == written->strike_price_scale_code);
  assert(read->value_short_selling_trades_scale_code == written->value_short_selling_trades_scale_code);
  assert(read->last_trade_price_scale_code == written->last_trade_price_scale_code);
  assert(read->value_block_trades_scale_code == written->value_block_trades_scale_code);
  assert(read->vwap_blocktrade_scale_code == written->vwap_blocktrade_scale_code);
  assert(read->maximum_block_price_scale_code == written->maximum_block_price_scale_code);
  assert(read->minimum_block_price_scale_code == written->minimum_block_price_scale_code);
  assert(read->status_indicator == written->status_indicator);
  for (size_t i = 0; i < 3; i++) { assert(read->sector[i] == written->sector[i]); }
  assert(read->market == written->market);
  assert(read->second_reserved_1 == written->second_reserved_1);
  assert(read->short_sale == written->short_sale);
  assert(read->marker_pct_change_price == written->marker_pct_change_price);
  assert(read->symbol_delta == written->symbol_delta);
  assert(read->symbol_gamma == written->symbol_gamma);
  assert(read->symbol_rho == written->symbol_rho);
  assert(read->symbol_theta == written->symbol_theta);
  assert(read->symbol_vega == written->symbol_vega);
  assert(read->third_reserved_1 == written->third_reserved_1);
  assert(read->fourth_reserved_1 == written->fourth_reserved_1);
  assert(read->fifth_reserved_1 == written->fifth_reserved_1);
  assert(read->sixth_reserved_1 == written->sixth_reserved_1);
  assert(read->seventh_reserved_1 == written->seventh_reserved_1);
  assert(read->eighth_reserved_1 == written->eighth_reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->segment[i] == written->segment[i]); }
  assert(read->lower_liquidity == written->lower_liquidity);
  for (size_t i = 0; i < 2; i++) { assert(read->dividend[i] == written->dividend[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->subscription_right[i] == written->subscription_right[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->split[i] == written->split[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->interim_dividend_right[i] == written->interim_dividend_right[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quotation_system[i] == written->quotation_system[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->liquidity_support_pge[i] == written->liquidity_support_pge[i]); }
  assert(read->ninth_reserved_1 == written->ninth_reserved_1);
}

/* Session Summary Message: written and read back, then read and written back */
static void check_session_summary_message(void) {
  SessionSummaryMessage sent;
  SessionSummaryMessage got;
  uint8_t wire[260];
  uint8_t again[260];

  any_session_summary_message(&sent);
  assert(encode_session_summary_message(&sent, wire, 0) == 260);
  assert(decode_session_summary_message(&got, wire, 0) == 260);
  equal_session_summary_message(&got, &sent);

  for (size_t i = 0; i < 260; i++) { wire[i] = arbitrary(); }
  assert(decode_session_summary_message(&got, wire, 0) == 260);
  assert(encode_session_summary_message(&got, again, 0) == 260);
  for (size_t i = 0; i < 260; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument State Change Message: 48 bytes ------------------------------- */

/* An 'Instrument State Change' message is generated by the trading engines to announce a change in the state of an instrument */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t system_id[4];               /* bytes 12 to 15 */
  uint8_t source_time_micro_secs[2];  /* bytes 16 to 17 */
  uint8_t reserved_2[2];              /* bytes 18 to 19 */
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
  uint8_t reserved_1;                 /* byte 47 */
} InstrumentStateChangeMessage;

/* any Instrument State Change Message at all: every byte one the checker chooses */
static void any_instrument_state_change_message(InstrumentStateChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
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
  record->reserved_1 = arbitrary();
}

/* Instrument State Change Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_instrument_state_change_message(const InstrumentStateChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
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
  wire[at++] = record->reserved_1;

  return at;
}

/* Instrument State Change Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_instrument_state_change_message(InstrumentStateChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
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
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Instrument State Change Message is what was written, byte for byte */
static void equal_instrument_state_change_message(const InstrumentStateChangeMessage *read, const InstrumentStateChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
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
  assert(read->reserved_1 == written->reserved_1);
}

/* Instrument State Change Message: written and read back, then read and written back */
static void check_instrument_state_change_message(void) {
  InstrumentStateChangeMessage sent;
  InstrumentStateChangeMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_instrument_state_change_message(&sent);
  assert(encode_instrument_state_change_message(&sent, wire, 0) == 48);
  assert(decode_instrument_state_change_message(&got, wire, 0) == 48);
  equal_instrument_state_change_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_state_change_message(&got, wire, 0) == 48);
  assert(encode_instrument_state_change_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indicative Matching Price Message: 32 bytes ----------------------------- */

/* The Indicative matching price message indicates an instrument's theoretical opening price (also known as an indicative opening price):  An IMP-message is sent if the indicative matching price or – volume varies */
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

/* ---- Short Sale Change Message: 124 bytes ------------------------------------ */

/* The Short Sale Change message indicates whether an instrument short sale is suspended or re-authorized */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t system_id[4];               /* bytes 12 to 15 */
  uint8_t source_time_micro_secs[2];  /* bytes 16 to 17 */
  uint8_t text_ascii_ch_100[100];     /* bytes 18 to 117 */
  uint8_t authority;                  /* byte 118 */
  uint8_t ss_market_maker;            /* byte 119 */
  uint8_t ss_non_market_maker;        /* byte 120 */
  uint8_t reserved_3[3];              /* bytes 121 to 123 */
} ShortSaleChangeMessage;

/* any Short Sale Change Message at all: every byte one the checker chooses */
static void any_short_sale_change_message(ShortSaleChangeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text_ascii_ch_100[i] = arbitrary(); }
  record->authority = arbitrary();
  record->ss_market_maker = arbitrary();
  record->ss_non_market_maker = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = arbitrary(); }
}

/* Short Sale Change Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_short_sale_change_message(const ShortSaleChangeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text_ascii_ch_100[i]; }
  wire[at++] = record->authority;
  wire[at++] = record->ss_market_maker;
  wire[at++] = record->ss_non_market_maker;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reserved_3[i]; }

  return at;
}

/* Short Sale Change Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_short_sale_change_message(ShortSaleChangeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text_ascii_ch_100[i] = wire[at++]; }
  record->authority = wire[at++];
  record->ss_market_maker = wire[at++];
  record->ss_non_market_maker = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->reserved_3[i] = wire[at++]; }

  return at;
}

/* what was read of Short Sale Change Message is what was written, byte for byte */
static void equal_short_sale_change_message(const ShortSaleChangeMessage *read, const ShortSaleChangeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text_ascii_ch_100[i] == written->text_ascii_ch_100[i]); }
  assert(read->authority == written->authority);
  assert(read->ss_market_maker == written->ss_market_maker);
  assert(read->ss_non_market_maker == written->ss_non_market_maker);
  for (size_t i = 0; i < 3; i++) { assert(read->reserved_3[i] == written->reserved_3[i]); }
}

/* Short Sale Change Message: written and read back, then read and written back */
static void check_short_sale_change_message(void) {
  ShortSaleChangeMessage sent;
  ShortSaleChangeMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_short_sale_change_message(&sent);
  assert(encode_short_sale_change_message(&sent, wire, 0) == 124);
  assert(decode_short_sale_change_message(&got, wire, 0) == 124);
  equal_short_sale_change_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_short_sale_change_message(&got, wire, 0) == 124);
  assert(encode_short_sale_change_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Treasury Bond Futures Data: 220 bytes ----------------------------------- */

/* Body Message for InternalMsgType = 02, which informs about the structure of the basket of treasury bonds for a given bond future for the next trading day */
typedef struct {
  uint8_t isin_code[12];                       /* bytes 0 to 11 */
  uint8_t date_of_first_quotation[8];          /* bytes 12 to 19 */
  uint8_t short_name[16];                      /* bytes 20 to 35 */
  uint8_t date_ascii_str_8[8];                 /* bytes 36 to 43 */
  uint8_t underlying_isin_code[12];            /* bytes 44 to 55 */
  uint8_t treasury_bond_1_isin_code[12];       /* bytes 56 to 67 */
  uint8_t conversion_coefficient_factor_1[9];  /* bytes 68 to 76 */
  uint8_t treasury_bond_2_isin_code[12];       /* bytes 77 to 88 */
  uint8_t conversion_coefficient_factor_2[9];  /* bytes 89 to 97 */
  uint8_t treasury_bond_3_isin_code[12];       /* bytes 98 to 109 */
  uint8_t conversion_coefficient_factor_3[9];  /* bytes 110 to 118 */
  uint8_t treasury_bond_4_isin_code[12];       /* bytes 119 to 130 */
  uint8_t conversion_coefficient_factor_4[9];  /* bytes 131 to 139 */
  uint8_t treasury_bond_5_isin_code[12];       /* bytes 140 to 151 */
  uint8_t conversion_coefficient_factor_5[9];  /* bytes 152 to 160 */
  uint8_t reserved_59[59];                     /* bytes 161 to 219 */
} TreasuryBondFuturesData;

/* any Treasury Bond Futures Data at all: every byte one the checker chooses */
static void any_treasury_bond_futures_data(TreasuryBondFuturesData *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_of_first_quotation[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->short_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->date_ascii_str_8[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_1_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_1[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_2_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_2[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_3_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_3[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_4_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_4[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_5_isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_5[i] = arbitrary(); }
  for (size_t i = 0; i < 59; i++) { record->reserved_59[i] = arbitrary(); }
}

/* Treasury Bond Futures Data to the wire: 220 bytes from at, returning where the next byte goes */
static size_t encode_treasury_bond_futures_data(const TreasuryBondFuturesData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_of_first_quotation[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->short_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->date_ascii_str_8[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin_code[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->treasury_bond_1_isin_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_coefficient_factor_1[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->treasury_bond_2_isin_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_coefficient_factor_2[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->treasury_bond_3_isin_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_coefficient_factor_3[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->treasury_bond_4_isin_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_coefficient_factor_4[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->treasury_bond_5_isin_code[i]; }
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->conversion_coefficient_factor_5[i]; }
  for (size_t i = 0; i < 59; i++) { wire[at++] = record->reserved_59[i]; }

  return at;
}

/* Treasury Bond Futures Data off the wire: 220 bytes from at, returning where the next byte lies */
static size_t decode_treasury_bond_futures_data(TreasuryBondFuturesData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_of_first_quotation[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->short_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->date_ascii_str_8[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_1_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_1[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_2_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_2[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_3_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_3[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_4_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_4[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->treasury_bond_5_isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 9; i++) { record->conversion_coefficient_factor_5[i] = wire[at++]; }
  for (size_t i = 0; i < 59; i++) { record->reserved_59[i] = wire[at++]; }

  return at;
}

/* what was read of Treasury Bond Futures Data is what was written, byte for byte */
static void equal_treasury_bond_futures_data(const TreasuryBondFuturesData *read, const TreasuryBondFuturesData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_of_first_quotation[i] == written->date_of_first_quotation[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->short_name[i] == written->short_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->date_ascii_str_8[i] == written->date_ascii_str_8[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin_code[i] == written->underlying_isin_code[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->treasury_bond_1_isin_code[i] == written->treasury_bond_1_isin_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_coefficient_factor_1[i] == written->conversion_coefficient_factor_1[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->treasury_bond_2_isin_code[i] == written->treasury_bond_2_isin_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_coefficient_factor_2[i] == written->conversion_coefficient_factor_2[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->treasury_bond_3_isin_code[i] == written->treasury_bond_3_isin_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_coefficient_factor_3[i] == written->conversion_coefficient_factor_3[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->treasury_bond_4_isin_code[i] == written->treasury_bond_4_isin_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_coefficient_factor_4[i] == written->conversion_coefficient_factor_4[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->treasury_bond_5_isin_code[i] == written->treasury_bond_5_isin_code[i]); }
  for (size_t i = 0; i < 9; i++) { assert(read->conversion_coefficient_factor_5[i] == written->conversion_coefficient_factor_5[i]); }
  for (size_t i = 0; i < 59; i++) { assert(read->reserved_59[i] == written->reserved_59[i]); }
}

/* Treasury Bond Futures Data: written and read back, then read and written back */
static void check_treasury_bond_futures_data(void) {
  TreasuryBondFuturesData sent;
  TreasuryBondFuturesData got;
  uint8_t wire[220];
  uint8_t again[220];

  any_treasury_bond_futures_data(&sent);
  assert(encode_treasury_bond_futures_data(&sent, wire, 0) == 220);
  assert(decode_treasury_bond_futures_data(&got, wire, 0) == 220);
  equal_treasury_bond_futures_data(&got, &sent);

  for (size_t i = 0; i < 220; i++) { wire[i] = arbitrary(); }
  assert(decode_treasury_bond_futures_data(&got, wire, 0) == 220);
  assert(encode_treasury_bond_futures_data(&got, again, 0) == 220);
  for (size_t i = 0; i < 220; i++) { assert(again[i] == wire[i]); }
}

/* ---- Kid: 220 bytes ---------------------------------------------------------- */

/* Body Message for InternalMsgType field = 03, which informs about the selected values for PRIIPs key information for the given trading day and includes the link to the issuer's website */
typedef struct {
  uint8_t isin_code[12];                      /* bytes 0 to 11 */
  uint8_t type_of_instrument_ascii_str_4[4];  /* bytes 12 to 15 */
  uint8_t kid_version[10];                    /* bytes 16 to 25 */
  uint8_t kid_issue_date[8];                  /* bytes 26 to 33 */
  uint8_t value_at_risk;                      /* byte 34 */
  uint8_t holding_period[3];                  /* bytes 35 to 37 */
  uint8_t priip_kid_url[182];                 /* bytes 38 to 219 */
} Kid;

/* any Kid at all: every byte one the checker chooses */
static void any_kid(Kid *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->type_of_instrument_ascii_str_4[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->kid_version[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->kid_issue_date[i] = arbitrary(); }
  record->value_at_risk = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->holding_period[i] = arbitrary(); }
  for (size_t i = 0; i < 182; i++) { record->priip_kid_url[i] = arbitrary(); }
}

/* Kid to the wire: 220 bytes from at, returning where the next byte goes */
static size_t encode_kid(const Kid *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->type_of_instrument_ascii_str_4[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->kid_version[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->kid_issue_date[i]; }
  wire[at++] = record->value_at_risk;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->holding_period[i]; }
  for (size_t i = 0; i < 182; i++) { wire[at++] = record->priip_kid_url[i]; }

  return at;
}

/* Kid off the wire: 220 bytes from at, returning where the next byte lies */
static size_t decode_kid(Kid *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->type_of_instrument_ascii_str_4[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->kid_version[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->kid_issue_date[i] = wire[at++]; }
  record->value_at_risk = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->holding_period[i] = wire[at++]; }
  for (size_t i = 0; i < 182; i++) { record->priip_kid_url[i] = wire[at++]; }

  return at;
}

/* what was read of Kid is what was written, byte for byte */
static void equal_kid(const Kid *read, const Kid *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->type_of_instrument_ascii_str_4[i] == written->type_of_instrument_ascii_str_4[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->kid_version[i] == written->kid_version[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->kid_issue_date[i] == written->kid_issue_date[i]); }
  assert(read->value_at_risk == written->value_at_risk);
  for (size_t i = 0; i < 3; i++) { assert(read->holding_period[i] == written->holding_period[i]); }
  for (size_t i = 0; i < 182; i++) { assert(read->priip_kid_url[i] == written->priip_kid_url[i]); }
}

/* Kid: written and read back, then read and written back */
static void check_kid(void) {
  Kid sent;
  Kid got;
  uint8_t wire[220];
  uint8_t again[220];

  any_kid(&sent);
  assert(encode_kid(&sent, wire, 0) == 220);
  assert(decode_kid(&got, wire, 0) == 220);
  equal_kid(&got, &sent);

  for (size_t i = 0; i < 220; i++) { wire[i] = arbitrary(); }
  assert(decode_kid(&got, wire, 0) == 220);
  assert(encode_kid(&got, again, 0) == 220);
  for (size_t i = 0; i < 220; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Conditions: 220 bytes -------------------------------------------- */

/* Body Message for InternalMsgType field = 04, 05, which informs about the beginning or the end of a Stressed or an Exceptional Market Conditions State for a given instrument */
typedef struct {
  uint8_t isin_code[12];                /* bytes 0 to 11 */
  uint8_t market_conditions_state;      /* byte 12 */
  uint8_t market_conditions_number[4];  /* bytes 13 to 16 */
  uint8_t reserved_203[203];            /* bytes 17 to 219 */
} MarketConditions;

/* any Market Conditions at all: every byte one the checker chooses */
static void any_market_conditions(MarketConditions *record) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = arbitrary(); }
  record->market_conditions_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_conditions_number[i] = arbitrary(); }
  for (size_t i = 0; i < 203; i++) { record->reserved_203[i] = arbitrary(); }
}

/* Market Conditions to the wire: 220 bytes from at, returning where the next byte goes */
static size_t encode_market_conditions(const MarketConditions *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code[i]; }
  wire[at++] = record->market_conditions_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_conditions_number[i]; }
  for (size_t i = 0; i < 203; i++) { wire[at++] = record->reserved_203[i]; }

  return at;
}

/* Market Conditions off the wire: 220 bytes from at, returning where the next byte lies */
static size_t decode_market_conditions(MarketConditions *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->isin_code[i] = wire[at++]; }
  record->market_conditions_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_conditions_number[i] = wire[at++]; }
  for (size_t i = 0; i < 203; i++) { record->reserved_203[i] = wire[at++]; }

  return at;
}

/* what was read of Market Conditions is what was written, byte for byte */
static void equal_market_conditions(const MarketConditions *read, const MarketConditions *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code[i] == written->isin_code[i]); }
  assert(read->market_conditions_state == written->market_conditions_state);
  for (size_t i = 0; i < 4; i++) { assert(read->market_conditions_number[i] == written->market_conditions_number[i]); }
  for (size_t i = 0; i < 203; i++) { assert(read->reserved_203[i] == written->reserved_203[i]); }
}

/* Market Conditions: written and read back, then read and written back */
static void check_market_conditions(void) {
  MarketConditions sent;
  MarketConditions got;
  uint8_t wire[220];
  uint8_t again[220];

  any_market_conditions(&sent);
  assert(encode_market_conditions(&sent, wire, 0) == 220);
  assert(decode_market_conditions(&got, wire, 0) == 220);
  equal_market_conditions(&got, &sent);

  for (size_t i = 0; i < 220; i++) { wire[i] = arbitrary(); }
  assert(decode_market_conditions(&got, wire, 0) == 220);
  assert(encode_market_conditions(&got, again, 0) == 220);
  for (size_t i = 0; i < 220; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Position Message: 36 bytes ----------------------------------------- */

/* The Open Position message indicates the current number of open positions for a particular instrument */
typedef struct {
  uint8_t symbol_index[4];            /* bytes 0 to 3 */
  uint8_t source_seq_num[4];          /* bytes 4 to 7 */
  uint8_t source_time[4];             /* bytes 8 to 11 */
  uint8_t trading_date[8];            /* bytes 12 to 19 */
  uint8_t open_position[4];           /* bytes 20 to 23 */
  uint8_t transaction_number[4];      /* bytes 24 to 27 */
  uint8_t system_id[4];               /* bytes 28 to 31 */
  uint8_t source_time_micro_secs[2];  /* bytes 32 to 33 */
  uint8_t open_position_indicator;    /* byte 34 */
  uint8_t reserved_1;                 /* byte 35 */
} OpenPositionMessage;

/* any Open Position Message at all: every byte one the checker chooses */
static void any_open_position_message(OpenPositionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->open_position[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transaction_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = arbitrary(); }
  record->open_position_indicator = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Open Position Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_open_position_message(const OpenPositionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->open_position[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transaction_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->source_time_micro_secs[i]; }
  wire[at++] = record->open_position_indicator;
  wire[at++] = record->reserved_1;

  return at;
}

/* Open Position Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_open_position_message(OpenPositionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->source_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->open_position[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transaction_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->source_time_micro_secs[i] = wire[at++]; }
  record->open_position_indicator = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Open Position Message is what was written, byte for byte */
static void equal_open_position_message(const OpenPositionMessage *read, const OpenPositionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_seq_num[i] == written->source_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->source_time[i] == written->source_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_date[i] == written->trading_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->open_position[i] == written->open_position[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transaction_number[i] == written->transaction_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->source_time_micro_secs[i] == written->source_time_micro_secs[i]); }
  assert(read->open_position_indicator == written->open_position_indicator);
  assert(read->reserved_1 == written->reserved_1);
}

/* Open Position Message: written and read back, then read and written back */
static void check_open_position_message(void) {
  OpenPositionMessage sent;
  OpenPositionMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_open_position_message(&sent);
  assert(encode_open_position_message(&sent, wire, 0) == 36);
  assert(decode_open_position_message(&got, wire, 0) == 36);
  equal_open_position_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_open_position_message(&got, wire, 0) == 36);
  assert(encode_open_position_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_class_state_change_message();
  check_mail_message();
  check_collars_message();
  check_start_referential_message();
  check_end_referential_message();
  check_session_summary_message();
  check_instrument_state_change_message();
  check_indicative_matching_price_message();
  check_short_sale_change_message();
  check_treasury_bond_futures_data();
  check_kid();
  check_market_conditions();
  check_open_position_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
