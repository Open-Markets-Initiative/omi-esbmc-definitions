// iex/iexoptions/binaryorderentry/IexOptions_BinaryOrderEntry_v1_02_Server.c
/*
 * Investors Exchange Binary Order Entry
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
 *   - a run filling what frames it
 *   - the dispatch that chooses a message by its type
 *   - a block whose stated length holds more than its fields
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

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Iex Options Sbe message header — message identifiers and length of message root */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id[2];   /* bytes 2 to 3 */
  uint8_t schema_id[2];     /* bytes 4 to 5 */
  uint8_t version[2];       /* bytes 6 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->schema_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->schema_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->schema_id[i] == written->schema_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 8);
  assert(decode_message_header(&got, wire, 0) == 8);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 8);
  assert(encode_message_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 17 bytes ---------------------------------------- */

/* LoginResponseMessage */
typedef struct {
  uint8_t logon_id[16];  /* bytes 0 to 15 */
  uint8_t status;        /* byte 16 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Login Response Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  wire[at++] = record->status;

  return at;
}

/* Login Response Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  assert(read->status == written->status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 17);
  assert(decode_login_response_message(&got, wire, 0) == 17);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 17);
  assert(encode_login_response_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Info Group Encoding: 2 bytes ------------------------------------ */

/* sessionInfoGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} SessionInfoGroupEncoding;

/* any Session Info Group Encoding at all: every byte one the checker chooses */
static void any_session_info_group_encoding(SessionInfoGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Session Info Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_session_info_group_encoding(const SessionInfoGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Session Info Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_session_info_group_encoding(SessionInfoGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Session Info Group Encoding is what was written, byte for byte */
static void equal_session_info_group_encoding(const SessionInfoGroupEncoding *read, const SessionInfoGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Session Info Group Encoding: written and read back, then read and written back */
static void check_session_info_group_encoding(void) {
  SessionInfoGroupEncoding sent;
  SessionInfoGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_session_info_group_encoding(&sent);
  assert(encode_session_info_group_encoding(&sent, wire, 0) == 2);
  assert(decode_session_info_group_encoding(&got, wire, 0) == 2);
  equal_session_info_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_session_info_group_encoding(&got, wire, 0) == 2);
  assert(encode_session_info_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate Message: 1 byte ----------------------------------------------- */

/* TerminateMessage */
typedef struct {
  uint8_t reason;  /* byte 0 */
} TerminateMessage;

/* any Terminate Message at all: every byte one the checker chooses */
static void any_terminate_message(TerminateMessage *record) {
  record->reason = arbitrary();
}

/* Terminate Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_terminate_message(const TerminateMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reason;

  return at;
}

/* Terminate Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_terminate_message(TerminateMessage *record, const uint8_t *wire, size_t at) {
  record->reason = wire[at++];

  return at;
}

/* what was read of Terminate Message is what was written, byte for byte */
static void equal_terminate_message(const TerminateMessage *read, const TerminateMessage *written) {
  assert(read->reason == written->reason);
}

/* Terminate Message: written and read back, then read and written back */
static void check_terminate_message(void) {
  TerminateMessage sent;
  TerminateMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_terminate_message(&sent);
  assert(encode_terminate_message(&sent, wire, 0) == 1);
  assert(decode_terminate_message(&got, wire, 0) == 1);
  equal_terminate_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate_message(&got, wire, 0) == 1);
  assert(encode_terminate_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequenced Message Header Message: 20 bytes ------------------------------ */

/* SequencedMessageHeaderMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t sequence[4];       /* bytes 8 to 11 */
  uint8_t timestamp[8];      /* bytes 12 to 19 */
} SequencedMessageHeaderMessage;

/* any Sequenced Message Header Message at all: every byte one the checker chooses */
static void any_sequenced_message_header_message(SequencedMessageHeaderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Sequenced Message Header Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_sequenced_message_header_message(const SequencedMessageHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Sequenced Message Header Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_sequenced_message_header_message(SequencedMessageHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Sequenced Message Header Message is what was written, byte for byte */
static void equal_sequenced_message_header_message(const SequencedMessageHeaderMessage *read, const SequencedMessageHeaderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Sequenced Message Header Message: written and read back, then read and written back */
static void check_sequenced_message_header_message(void) {
  SequencedMessageHeaderMessage sent;
  SequencedMessageHeaderMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_sequenced_message_header_message(&sent);
  assert(encode_sequenced_message_header_message(&sent, wire, 0) == 20);
  assert(decode_sequenced_message_header_message(&got, wire, 0) == 20);
  equal_sequenced_message_header_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_sequenced_message_header_message(&got, wire, 0) == 20);
  assert(encode_sequenced_message_header_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Join Response Message: 9 bytes ------------------------------- */

/* SubsessionJoinResponseMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t status;            /* byte 8 */
} SubsessionJoinResponseMessage;

/* any Subsession Join Response Message at all: every byte one the checker chooses */
static void any_subsession_join_response_message(SubsessionJoinResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Subsession Join Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_subsession_join_response_message(const SubsessionJoinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  wire[at++] = record->status;

  return at;
}

/* Subsession Join Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_subsession_join_response_message(SubsessionJoinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Subsession Join Response Message is what was written, byte for byte */
static void equal_subsession_join_response_message(const SubsessionJoinResponseMessage *read, const SubsessionJoinResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  assert(read->status == written->status);
}

/* Subsession Join Response Message: written and read back, then read and written back */
static void check_subsession_join_response_message(void) {
  SubsessionJoinResponseMessage sent;
  SubsessionJoinResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_subsession_join_response_message(&sent);
  assert(encode_subsession_join_response_message(&sent, wire, 0) == 9);
  assert(decode_subsession_join_response_message(&got, wire, 0) == 9);
  equal_subsession_join_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_join_response_message(&got, wire, 0) == 9);
  assert(encode_subsession_join_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Leave Response Message: 9 bytes ------------------------------ */

/* SubsessionLeaveResponseMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
  uint8_t reason;            /* byte 8 */
} SubsessionLeaveResponseMessage;

/* any Subsession Leave Response Message at all: every byte one the checker chooses */
static void any_subsession_leave_response_message(SubsessionLeaveResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  record->reason = arbitrary();
}

/* Subsession Leave Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_subsession_leave_response_message(const SubsessionLeaveResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  wire[at++] = record->reason;

  return at;
}

/* Subsession Leave Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_subsession_leave_response_message(SubsessionLeaveResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  record->reason = wire[at++];

  return at;
}

/* what was read of Subsession Leave Response Message is what was written, byte for byte */
static void equal_subsession_leave_response_message(const SubsessionLeaveResponseMessage *read, const SubsessionLeaveResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  assert(read->reason == written->reason);
}

/* Subsession Leave Response Message: written and read back, then read and written back */
static void check_subsession_leave_response_message(void) {
  SubsessionLeaveResponseMessage sent;
  SubsessionLeaveResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_subsession_leave_response_message(&sent);
  assert(encode_subsession_leave_response_message(&sent, wire, 0) == 9);
  assert(decode_subsession_leave_response_message(&got, wire, 0) == 9);
  equal_subsession_leave_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_leave_response_message(&got, wire, 0) == 9);
  assert(encode_subsession_leave_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Ack Message: 139 bytes -------------------------------------------- */

/* OrderAckMessage */
typedef struct {
  uint8_t account_account[16];       /* bytes 0 to 15 */
  uint8_t transact_time[8];          /* bytes 16 to 23 */
  uint8_t instrument_id[4];          /* bytes 24 to 27 */
  uint8_t market_participant_id[4];  /* bytes 28 to 31 */
  uint8_t cl_ord_id[8];              /* bytes 32 to 39 */
  uint8_t clearing_account[4];       /* bytes 40 to 43 */
  uint8_t orig_cl_ord_id[8];         /* bytes 44 to 51 */
  uint8_t order_id[8];               /* bytes 52 to 59 */
  uint8_t customer_or_firm;          /* byte 60 */
  uint8_t open_close;                /* byte 61 */
  uint8_t attributed_quote;          /* byte 62 */
  uint8_t time_in_force;             /* byte 63 */
  uint8_t cancel_instead_of_slide;   /* byte 64 */
  uint8_t display_inst;              /* byte 65 */
  uint8_t exec_inst;                 /* byte 66 */
  uint8_t ord_type;                  /* byte 67 */
  uint8_t target_party_id[4];        /* bytes 68 to 71 */
  uint8_t auction_id[4];             /* bytes 72 to 75 */
  uint8_t clearing_firm[4];          /* bytes 76 to 79 */
  uint8_t optional_data[16];         /* bytes 80 to 95 */
  uint8_t routing_firm_id[4];        /* bytes 96 to 99 */
  uint8_t aiq[3];                    /* bytes 100 to 102 */
  uint8_t side;                      /* byte 103 */
  uint8_t price_price_8[8];          /* bytes 104 to 111 */
  uint8_t order_qty[4];              /* bytes 112 to 115 */
  uint8_t leaves_qty[4];             /* bytes 116 to 119 */
  uint8_t effective_limit_price[8];  /* bytes 120 to 127 */
  uint8_t display_price[8];          /* bytes 128 to 135 */
  uint8_t reason_code;               /* byte 136 */
  uint8_t ack_type;                  /* byte 137 */
  uint8_t throttle_indicator;        /* byte 138 */
} OrderAckMessage;

/* any Order Ack Message at all: every byte one the checker chooses */
static void any_order_ack_message(OrderAckMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->customer_or_firm = arbitrary();
  record->open_close = arbitrary();
  record->attributed_quote = arbitrary();
  record->time_in_force = arbitrary();
  record->cancel_instead_of_slide = arbitrary();
  record->display_inst = arbitrary();
  record->exec_inst = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->optional_data[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->ack_type = arbitrary();
  record->throttle_indicator = arbitrary();
}

/* Order Ack Message to the wire: 139 bytes from at, returning where the next byte goes */
static size_t encode_order_ack_message(const OrderAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->customer_or_firm;
  wire[at++] = record->open_close;
  wire[at++] = record->attributed_quote;
  wire[at++] = record->time_in_force;
  wire[at++] = record->cancel_instead_of_slide;
  wire[at++] = record->display_inst;
  wire[at++] = record->exec_inst;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->optional_data[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->aiq[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_price_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_type;
  wire[at++] = record->throttle_indicator;

  return at;
}

/* Order Ack Message off the wire: 139 bytes from at, returning where the next byte lies */
static size_t decode_order_ack_message(OrderAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->customer_or_firm = wire[at++];
  record->open_close = wire[at++];
  record->attributed_quote = wire[at++];
  record->time_in_force = wire[at++];
  record->cancel_instead_of_slide = wire[at++];
  record->display_inst = wire[at++];
  record->exec_inst = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->optional_data[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->ack_type = wire[at++];
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of Order Ack Message is what was written, byte for byte */
static void equal_order_ack_message(const OrderAckMessage *read, const OrderAckMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account_account[i] == written->account_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->customer_or_firm == written->customer_or_firm);
  assert(read->open_close == written->open_close);
  assert(read->attributed_quote == written->attributed_quote);
  assert(read->time_in_force == written->time_in_force);
  assert(read->cancel_instead_of_slide == written->cancel_instead_of_slide);
  assert(read->display_inst == written->display_inst);
  assert(read->exec_inst == written->exec_inst);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->optional_data[i] == written->optional_data[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->aiq[i] == written->aiq[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_price_8[i] == written->price_price_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_limit_price[i] == written->effective_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->ack_type == written->ack_type);
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* Order Ack Message: written and read back, then read and written back */
static void check_order_ack_message(void) {
  OrderAckMessage sent;
  OrderAckMessage got;
  uint8_t wire[139];
  uint8_t again[139];

  any_order_ack_message(&sent);
  assert(encode_order_ack_message(&sent, wire, 0) == 139);
  assert(decode_order_ack_message(&got, wire, 0) == 139);
  equal_order_ack_message(&got, &sent);

  for (size_t i = 0; i < 139; i++) { wire[i] = arbitrary(); }
  assert(decode_order_ack_message(&got, wire, 0) == 139);
  assert(encode_order_ack_message(&got, again, 0) == 139);
  for (size_t i = 0; i < 139; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unsolicited Modify Ack Message: 67 bytes -------------------------------- */

/* UnsolicitedModifyAckMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t instrument_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t orig_cl_ord_id[8];         /* bytes 16 to 23 */
  uint8_t order_id[8];               /* bytes 24 to 31 */
  uint8_t price_price_8[8];          /* bytes 32 to 39 */
  uint8_t order_qty[4];              /* bytes 40 to 43 */
  uint8_t leaves_qty[4];             /* bytes 44 to 47 */
  uint8_t effective_limit_price[8];  /* bytes 48 to 55 */
  uint8_t display_price[8];          /* bytes 56 to 63 */
  uint8_t restatement_reason;        /* byte 64 */
  uint8_t reason_code;               /* byte 65 */
  uint8_t ack_type;                  /* byte 66 */
} UnsolicitedModifyAckMessage;

/* any Unsolicited Modify Ack Message at all: every byte one the checker chooses */
static void any_unsolicited_modify_ack_message(UnsolicitedModifyAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = arbitrary(); }
  record->restatement_reason = arbitrary();
  record->reason_code = arbitrary();
  record->ack_type = arbitrary();
}

/* Unsolicited Modify Ack Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_unsolicited_modify_ack_message(const UnsolicitedModifyAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_price_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->display_price[i]; }
  wire[at++] = record->restatement_reason;
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_type;

  return at;
}

/* Unsolicited Modify Ack Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_unsolicited_modify_ack_message(UnsolicitedModifyAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->display_price[i] = wire[at++]; }
  record->restatement_reason = wire[at++];
  record->reason_code = wire[at++];
  record->ack_type = wire[at++];

  return at;
}

/* what was read of Unsolicited Modify Ack Message is what was written, byte for byte */
static void equal_unsolicited_modify_ack_message(const UnsolicitedModifyAckMessage *read, const UnsolicitedModifyAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_price_8[i] == written->price_price_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_limit_price[i] == written->effective_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->display_price[i] == written->display_price[i]); }
  assert(read->restatement_reason == written->restatement_reason);
  assert(read->reason_code == written->reason_code);
  assert(read->ack_type == written->ack_type);
}

/* Unsolicited Modify Ack Message: written and read back, then read and written back */
static void check_unsolicited_modify_ack_message(void) {
  UnsolicitedModifyAckMessage sent;
  UnsolicitedModifyAckMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_unsolicited_modify_ack_message(&sent);
  assert(encode_unsolicited_modify_ack_message(&sent, wire, 0) == 67);
  assert(decode_unsolicited_modify_ack_message(&got, wire, 0) == 67);
  equal_unsolicited_modify_ack_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_unsolicited_modify_ack_message(&got, wire, 0) == 67);
  assert(encode_unsolicited_modify_ack_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Ack Message: 55 bytes -------------------------------------- */

/* OrderCancelAckMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t instrument_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];              /* bytes 16 to 23 */
  uint8_t orig_cl_ord_id[8];         /* bytes 24 to 31 */
  uint8_t order_id[8];               /* bytes 32 to 39 */
  uint8_t price_price_8[8];          /* bytes 40 to 47 */
  uint8_t leaves_qty[4];             /* bytes 48 to 51 */
  uint8_t reason_code;               /* byte 52 */
  uint8_t ack_type;                  /* byte 53 */
  uint8_t throttle_indicator;        /* byte 54 */
} OrderCancelAckMessage;

/* any Order Cancel Ack Message at all: every byte one the checker chooses */
static void any_order_cancel_ack_message(OrderCancelAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->ack_type = arbitrary();
  record->throttle_indicator = arbitrary();
}

/* Order Cancel Ack Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_ack_message(const OrderCancelAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_price_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_type;
  wire[at++] = record->throttle_indicator;

  return at;
}

/* Order Cancel Ack Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_ack_message(OrderCancelAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->ack_type = wire[at++];
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of Order Cancel Ack Message is what was written, byte for byte */
static void equal_order_cancel_ack_message(const OrderCancelAckMessage *read, const OrderCancelAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_price_8[i] == written->price_price_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->ack_type == written->ack_type);
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* Order Cancel Ack Message: written and read back, then read and written back */
static void check_order_cancel_ack_message(void) {
  OrderCancelAckMessage sent;
  OrderCancelAckMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_order_cancel_ack_message(&sent);
  assert(encode_order_cancel_ack_message(&sent, wire, 0) == 55);
  assert(decode_order_cancel_ack_message(&got, wire, 0) == 55);
  equal_order_cancel_ack_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_ack_message(&got, wire, 0) == 55);
  assert(encode_order_cancel_ack_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Ack Message: 33 bytes --------------------------------------- */

/* MassCancelAckMessage */
typedef struct {
  uint8_t transact_time[8];                 /* bytes 0 to 7 */
  uint8_t underlying_id_optional[4];        /* bytes 8 to 11 */
  uint8_t market_participant_id[4];         /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];                     /* bytes 16 to 23 */
  uint8_t reason_code;                      /* byte 24 */
  uint8_t ack_style_mass_cancel_ack_style;  /* byte 25 */
  uint8_t mpid_filter;                      /* byte 26 */
  uint8_t bulk_action;                      /* byte 27 */
  uint8_t cancel_count[4];                  /* bytes 28 to 31 */
  uint8_t throttle_indicator;               /* byte 32 */
} MassCancelAckMessage;

/* any Mass Cancel Ack Message at all: every byte one the checker chooses */
static void any_mass_cancel_ack_message(MassCancelAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->ack_style_mass_cancel_ack_style = arbitrary();
  record->mpid_filter = arbitrary();
  record->bulk_action = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cancel_count[i] = arbitrary(); }
  record->throttle_indicator = arbitrary();
}

/* Mass Cancel Ack Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_ack_message(const MassCancelAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_style_mass_cancel_ack_style;
  wire[at++] = record->mpid_filter;
  wire[at++] = record->bulk_action;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancel_count[i]; }
  wire[at++] = record->throttle_indicator;

  return at;
}

/* Mass Cancel Ack Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_ack_message(MassCancelAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->ack_style_mass_cancel_ack_style = wire[at++];
  record->mpid_filter = wire[at++];
  record->bulk_action = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cancel_count[i] = wire[at++]; }
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of Mass Cancel Ack Message is what was written, byte for byte */
static void equal_mass_cancel_ack_message(const MassCancelAckMessage *read, const MassCancelAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->ack_style_mass_cancel_ack_style == written->ack_style_mass_cancel_ack_style);
  assert(read->mpid_filter == written->mpid_filter);
  assert(read->bulk_action == written->bulk_action);
  for (size_t i = 0; i < 4; i++) { assert(read->cancel_count[i] == written->cancel_count[i]); }
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* Mass Cancel Ack Message: written and read back, then read and written back */
static void check_mass_cancel_ack_message(void) {
  MassCancelAckMessage sent;
  MassCancelAckMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_mass_cancel_ack_message(&sent);
  assert(encode_mass_cancel_ack_message(&sent, wire, 0) == 33);
  assert(decode_mass_cancel_ack_message(&got, wire, 0) == 33);
  equal_mass_cancel_ack_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_ack_message(&got, wire, 0) == 33);
  assert(encode_mass_cancel_ack_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Acks Group Encoding: 2 bytes -------------------------------------- */

/* quoteAcksGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} QuoteAcksGroupEncoding;

/* any Quote Acks Group Encoding at all: every byte one the checker chooses */
static void any_quote_acks_group_encoding(QuoteAcksGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Quote Acks Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_quote_acks_group_encoding(const QuoteAcksGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Quote Acks Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_quote_acks_group_encoding(QuoteAcksGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Quote Acks Group Encoding is what was written, byte for byte */
static void equal_quote_acks_group_encoding(const QuoteAcksGroupEncoding *read, const QuoteAcksGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Quote Acks Group Encoding: written and read back, then read and written back */
static void check_quote_acks_group_encoding(void) {
  QuoteAcksGroupEncoding sent;
  QuoteAcksGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_quote_acks_group_encoding(&sent);
  assert(encode_quote_acks_group_encoding(&sent, wire, 0) == 2);
  assert(decode_quote_acks_group_encoding(&got, wire, 0) == 2);
  equal_quote_acks_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_acks_group_encoding(&got, wire, 0) == 2);
  assert(encode_quote_acks_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Ioc Quote Ack Message: 51 bytes ------------------------------------- */

/* NewIocQuoteAckMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t market_participant_id[4];  /* bytes 8 to 11 */
  uint8_t cl_ord_id[8];              /* bytes 12 to 19 */
  uint8_t clearing_account[4];       /* bytes 20 to 23 */
  uint8_t aiq[3];                    /* bytes 24 to 26 */
  uint8_t instrument_id[4];          /* bytes 27 to 30 */
  uint8_t side;                      /* byte 31 */
  uint8_t order_id[8];               /* bytes 32 to 39 */
  uint8_t ack_type;                  /* byte 40 */
  uint8_t price_price_4[4];          /* bytes 41 to 44 */
  uint8_t order_qty[4];              /* bytes 45 to 48 */
  uint8_t reason_code;               /* byte 49 */
  uint8_t throttle_indicator;        /* byte 50 */
} NewIocQuoteAckMessage;

/* any New Ioc Quote Ack Message at all: every byte one the checker chooses */
static void any_new_ioc_quote_ack_message(NewIocQuoteAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->ack_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->price_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->throttle_indicator = arbitrary();
}

/* New Ioc Quote Ack Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_new_ioc_quote_ack_message(const NewIocQuoteAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->aiq[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->ack_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_price_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->throttle_indicator;

  return at;
}

/* New Ioc Quote Ack Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_new_ioc_quote_ack_message(NewIocQuoteAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->ack_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->price_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of New Ioc Quote Ack Message is what was written, byte for byte */
static void equal_new_ioc_quote_ack_message(const NewIocQuoteAckMessage *read, const NewIocQuoteAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->aiq[i] == written->aiq[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->ack_type == written->ack_type);
  for (size_t i = 0; i < 4; i++) { assert(read->price_price_4[i] == written->price_price_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* New Ioc Quote Ack Message: written and read back, then read and written back */
static void check_new_ioc_quote_ack_message(void) {
  NewIocQuoteAckMessage sent;
  NewIocQuoteAckMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_new_ioc_quote_ack_message(&sent);
  assert(encode_new_ioc_quote_ack_message(&sent, wire, 0) == 51);
  assert(decode_new_ioc_quote_ack_message(&got, wire, 0) == 51);
  equal_new_ioc_quote_ack_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_new_ioc_quote_ack_message(&got, wire, 0) == 51);
  assert(encode_new_ioc_quote_ack_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Restated Message: 47 bytes ---------------------------------------- */

/* QuoteRestatedMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t instrument_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];              /* bytes 16 to 23 */
  uint8_t order_id[8];               /* bytes 24 to 31 */
  uint8_t side;                      /* byte 32 */
  uint8_t price_price_8[8];          /* bytes 33 to 40 */
  uint8_t reason_code;               /* byte 41 */
  uint8_t ack_type;                  /* byte 42 */
  uint8_t delta[4];                  /* bytes 43 to 46 */
} QuoteRestatedMessage;

/* any Quote Restated Message at all: every byte one the checker chooses */
static void any_quote_restated_message(QuoteRestatedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->ack_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->delta[i] = arbitrary(); }
}

/* Quote Restated Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_quote_restated_message(const QuoteRestatedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_price_8[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta[i]; }

  return at;
}

/* Quote Restated Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_quote_restated_message(QuoteRestatedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_price_8[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->ack_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->delta[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Restated Message is what was written, byte for byte */
static void equal_quote_restated_message(const QuoteRestatedMessage *read, const QuoteRestatedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price_price_8[i] == written->price_price_8[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->ack_type == written->ack_type);
  for (size_t i = 0; i < 4; i++) { assert(read->delta[i] == written->delta[i]); }
}

/* Quote Restated Message: written and read back, then read and written back */
static void check_quote_restated_message(void) {
  QuoteRestatedMessage sent;
  QuoteRestatedMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_quote_restated_message(&sent);
  assert(encode_quote_restated_message(&sent, wire, 0) == 47);
  assert(decode_quote_restated_message(&got, wire, 0) == 47);
  equal_quote_restated_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_restated_message(&got, wire, 0) == 47);
  assert(encode_quote_restated_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Canceled Message: 39 bytes ---------------------------------------- */

/* QuoteCanceledMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t instrument_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];              /* bytes 16 to 23 */
  uint8_t order_id[8];               /* bytes 24 to 31 */
  uint8_t side;                      /* byte 32 */
  uint8_t reason_code;               /* byte 33 */
  uint8_t ack_type;                  /* byte 34 */
  uint8_t delta[4];                  /* bytes 35 to 38 */
} QuoteCanceledMessage;

/* any Quote Canceled Message at all: every byte one the checker chooses */
static void any_quote_canceled_message(QuoteCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->reason_code = arbitrary();
  record->ack_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->delta[i] = arbitrary(); }
}

/* Quote Canceled Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_quote_canceled_message(const QuoteCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->reason_code;
  wire[at++] = record->ack_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta[i]; }

  return at;
}

/* Quote Canceled Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_quote_canceled_message(QuoteCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->reason_code = wire[at++];
  record->ack_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->delta[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Canceled Message is what was written, byte for byte */
static void equal_quote_canceled_message(const QuoteCanceledMessage *read, const QuoteCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  assert(read->reason_code == written->reason_code);
  assert(read->ack_type == written->ack_type);
  for (size_t i = 0; i < 4; i++) { assert(read->delta[i] == written->delta[i]); }
}

/* Quote Canceled Message: written and read back, then read and written back */
static void check_quote_canceled_message(void) {
  QuoteCanceledMessage sent;
  QuoteCanceledMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_quote_canceled_message(&sent);
  assert(encode_quote_canceled_message(&sent, wire, 0) == 39);
  assert(decode_quote_canceled_message(&got, wire, 0) == 39);
  equal_quote_canceled_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_canceled_message(&got, wire, 0) == 39);
  assert(encode_quote_canceled_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Custom Group Ids Group Encoding: 2 bytes -------------------------------- */

/* customGroupIdsGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} CustomGroupIdsGroupEncoding;

/* any Custom Group Ids Group Encoding at all: every byte one the checker chooses */
static void any_custom_group_ids_group_encoding(CustomGroupIdsGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Custom Group Ids Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_custom_group_ids_group_encoding(const CustomGroupIdsGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Custom Group Ids Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_custom_group_ids_group_encoding(CustomGroupIdsGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Custom Group Ids Group Encoding is what was written, byte for byte */
static void equal_custom_group_ids_group_encoding(const CustomGroupIdsGroupEncoding *read, const CustomGroupIdsGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Custom Group Ids Group Encoding: written and read back, then read and written back */
static void check_custom_group_ids_group_encoding(void) {
  CustomGroupIdsGroupEncoding sent;
  CustomGroupIdsGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_custom_group_ids_group_encoding(&sent);
  assert(encode_custom_group_ids_group_encoding(&sent, wire, 0) == 2);
  assert(decode_custom_group_ids_group_encoding(&got, wire, 0) == 2);
  equal_custom_group_ids_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_custom_group_ids_group_encoding(&got, wire, 0) == 2);
  assert(encode_custom_group_ids_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Message: 154 bytes ------------------------------------- */

/* ExecutionReportMessage */
typedef struct {
  uint8_t account_account[16];         /* bytes 0 to 15 */
  uint8_t transact_time[8];            /* bytes 16 to 23 */
  uint8_t instrument_id[4];            /* bytes 24 to 27 */
  uint8_t market_participant_id[4];    /* bytes 28 to 31 */
  uint8_t cl_ord_id[8];                /* bytes 32 to 39 */
  uint8_t clearing_account[4];         /* bytes 40 to 43 */
  uint8_t customer_or_firm;            /* byte 44 */
  uint8_t order_id[8];                 /* bytes 45 to 52 */
  uint8_t exec_id[8];                  /* bytes 53 to 60 */
  uint8_t trade_id[8];                 /* bytes 61 to 68 */
  uint8_t last_px[8];                  /* bytes 69 to 76 */
  uint8_t open_close;                  /* byte 77 */
  uint8_t side;                        /* byte 78 */
  uint8_t target_party_id[4];          /* bytes 79 to 82 */
  uint8_t auction_id[4];               /* bytes 83 to 86 */
  uint8_t clearing_firm[4];            /* bytes 87 to 90 */
  uint8_t optional_data[16];           /* bytes 91 to 106 */
  uint8_t routing_firm_id[4];          /* bytes 107 to 110 */
  uint8_t aiq[3];                      /* bytes 111 to 113 */
  uint8_t leaves_qty[4];               /* bytes 114 to 117 */
  uint8_t cum_qty[4];                  /* bytes 118 to 121 */
  uint8_t last_qty[4];                 /* bytes 122 to 125 */
  uint8_t trade_liquidity_indicator;   /* byte 126 */
  uint8_t fee_code[2];                 /* bytes 127 to 128 */
  uint8_t reason_code;                 /* byte 129 */
  uint8_t occ_id[5];                   /* bytes 130 to 134 */
  uint8_t contra_clearing_account[4];  /* bytes 135 to 138 */
  uint8_t contra_clearing_firm[4];     /* bytes 139 to 142 */
  uint8_t contra_mpid[4];              /* bytes 143 to 146 */
  uint8_t contra_open_close;           /* byte 147 */
  uint8_t contra_customer_or_firm;     /* byte 148 */
  uint8_t contra_occ_id[5];            /* bytes 149 to 153 */
} ExecutionReportMessage;

/* any Execution Report Message at all: every byte one the checker chooses */
static void any_execution_report_message(ExecutionReportMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  record->customer_or_firm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  record->open_close = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->optional_data[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  record->trade_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = arbitrary(); }
  record->reason_code = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->occ_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contra_mpid[i] = arbitrary(); }
  record->contra_open_close = arbitrary();
  record->contra_customer_or_firm = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->contra_occ_id[i] = arbitrary(); }
}

/* Execution Report Message to the wire: 154 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_message(const ExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  wire[at++] = record->customer_or_firm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  wire[at++] = record->open_close;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->optional_data[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->routing_firm_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->aiq[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->trade_liquidity_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_code[i]; }
  wire[at++] = record->reason_code;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->occ_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_clearing_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contra_mpid[i]; }
  wire[at++] = record->contra_open_close;
  wire[at++] = record->contra_customer_or_firm;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->contra_occ_id[i]; }

  return at;
}

/* Execution Report Message off the wire: 154 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_message(ExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  record->customer_or_firm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  record->open_close = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->optional_data[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->routing_firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->aiq[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  record->trade_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_code[i] = wire[at++]; }
  record->reason_code = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->occ_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contra_mpid[i] = wire[at++]; }
  record->contra_open_close = wire[at++];
  record->contra_customer_or_firm = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->contra_occ_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Message is what was written, byte for byte */
static void equal_execution_report_message(const ExecutionReportMessage *read, const ExecutionReportMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account_account[i] == written->account_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  assert(read->customer_or_firm == written->customer_or_firm);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  assert(read->open_close == written->open_close);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_id[i] == written->auction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->optional_data[i] == written->optional_data[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->routing_firm_id[i] == written->routing_firm_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->aiq[i] == written->aiq[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->trade_liquidity_indicator == written->trade_liquidity_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_code[i] == written->fee_code[i]); }
  assert(read->reason_code == written->reason_code);
  for (size_t i = 0; i < 5; i++) { assert(read->occ_id[i] == written->occ_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_clearing_account[i] == written->contra_clearing_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_clearing_firm[i] == written->contra_clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contra_mpid[i] == written->contra_mpid[i]); }
  assert(read->contra_open_close == written->contra_open_close);
  assert(read->contra_customer_or_firm == written->contra_customer_or_firm);
  for (size_t i = 0; i < 5; i++) { assert(read->contra_occ_id[i] == written->contra_occ_id[i]); }
}

/* Execution Report Message: written and read back, then read and written back */
static void check_execution_report_message(void) {
  ExecutionReportMessage sent;
  ExecutionReportMessage got;
  uint8_t wire[154];
  uint8_t again[154];

  any_execution_report_message(&sent);
  assert(encode_execution_report_message(&sent, wire, 0) == 154);
  assert(decode_execution_report_message(&got, wire, 0) == 154);
  equal_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 154; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_message(&got, wire, 0) == 154);
  assert(encode_execution_report_message(&got, again, 0) == 154);
  for (size_t i = 0; i < 154; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Correct Message: 86 bytes ------------------------------------ */

/* TradeBustCorrectMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t instrument_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];              /* bytes 16 to 23 */
  uint8_t order_id[8];               /* bytes 24 to 31 */
  uint8_t exec_id[8];                /* bytes 32 to 39 */
  uint8_t trade_id[8];               /* bytes 40 to 47 */
  uint8_t trade_ref_id[8];           /* bytes 48 to 55 */
  uint8_t last_px[8];                /* bytes 56 to 63 */
  uint8_t account_account[16];       /* bytes 64 to 79 */
  uint8_t last_qty[4];               /* bytes 80 to 83 */
  uint8_t reason_code;               /* byte 84 */
  uint8_t bust_or_correction;        /* byte 85 */
} TradeBustCorrectMessage;

/* any Trade Bust Correct Message at all: every byte one the checker chooses */
static void any_trade_bust_correct_message(TradeBustCorrectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->bust_or_correction = arbitrary();
}

/* Trade Bust Correct Message to the wire: 86 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_correct_message(const TradeBustCorrectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->bust_or_correction;

  return at;
}

/* Trade Bust Correct Message off the wire: 86 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_correct_message(TradeBustCorrectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->bust_or_correction = wire[at++];

  return at;
}

/* what was read of Trade Bust Correct Message is what was written, byte for byte */
static void equal_trade_bust_correct_message(const TradeBustCorrectMessage *read, const TradeBustCorrectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_ref_id[i] == written->trade_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_account[i] == written->account_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->bust_or_correction == written->bust_or_correction);
}

/* Trade Bust Correct Message: written and read back, then read and written back */
static void check_trade_bust_correct_message(void) {
  TradeBustCorrectMessage sent;
  TradeBustCorrectMessage got;
  uint8_t wire[86];
  uint8_t again[86];

  any_trade_bust_correct_message(&sent);
  assert(encode_trade_bust_correct_message(&sent, wire, 0) == 86);
  assert(decode_trade_bust_correct_message(&got, wire, 0) == 86);
  equal_trade_bust_correct_message(&got, &sent);

  for (size_t i = 0; i < 86; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_correct_message(&got, wire, 0) == 86);
  assert(encode_trade_bust_correct_message(&got, again, 0) == 86);
  for (size_t i = 0; i < 86; i++) { assert(again[i] == wire[i]); }
}

/* ---- Application Layer Reject Message: 47 bytes ------------------------------ */

/* ApplicationLayerRejectMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t underlying_id[4];          /* bytes 8 to 11 */
  uint8_t instrument_id[4];          /* bytes 12 to 15 */
  uint8_t market_participant_id[4];  /* bytes 16 to 19 */
  uint8_t cl_ord_id[8];              /* bytes 20 to 27 */
  uint8_t account_string_16[16];     /* bytes 28 to 43 */
  uint8_t reason_code;               /* byte 44 */
  uint8_t reject_type;               /* byte 45 */
  uint8_t throttle_indicator;        /* byte 46 */
} ApplicationLayerRejectMessage;

/* any Application Layer Reject Message at all: every byte one the checker chooses */
static void any_application_layer_reject_message(ApplicationLayerRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_string_16[i] = arbitrary(); }
  record->reason_code = arbitrary();
  record->reject_type = arbitrary();
  record->throttle_indicator = arbitrary();
}

/* Application Layer Reject Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_application_layer_reject_message(const ApplicationLayerRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_string_16[i]; }
  wire[at++] = record->reason_code;
  wire[at++] = record->reject_type;
  wire[at++] = record->throttle_indicator;

  return at;
}

/* Application Layer Reject Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_application_layer_reject_message(ApplicationLayerRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_string_16[i] = wire[at++]; }
  record->reason_code = wire[at++];
  record->reject_type = wire[at++];
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of Application Layer Reject Message is what was written, byte for byte */
static void equal_application_layer_reject_message(const ApplicationLayerRejectMessage *read, const ApplicationLayerRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_string_16[i] == written->account_string_16[i]); }
  assert(read->reason_code == written->reason_code);
  assert(read->reject_type == written->reject_type);
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* Application Layer Reject Message: written and read back, then read and written back */
static void check_application_layer_reject_message(void) {
  ApplicationLayerRejectMessage sent;
  ApplicationLayerRejectMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_application_layer_reject_message(&sent);
  assert(encode_application_layer_reject_message(&sent, wire, 0) == 47);
  assert(decode_application_layer_reject_message(&got, wire, 0) == 47);
  equal_application_layer_reject_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_application_layer_reject_message(&got, wire, 0) == 47);
  assert(encode_application_layer_reject_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Underlying Ref Data Message: 25 bytes ----------------------------------- */

/* UnderlyingRefDataMessage */
typedef struct {
  uint8_t transact_time[8];      /* bytes 0 to 7 */
  uint8_t underlying_id[4];      /* bytes 8 to 11 */
  uint8_t underlying_symbol[8];  /* bytes 12 to 19 */
  uint8_t mic[4];                /* bytes 20 to 23 */
  uint8_t mpv_group;             /* byte 24 */
} UnderlyingRefDataMessage;

/* any Underlying Ref Data Message at all: every byte one the checker chooses */
static void any_underlying_ref_data_message(UnderlyingRefDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  record->mpv_group = arbitrary();
}

/* Underlying Ref Data Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_underlying_ref_data_message(const UnderlyingRefDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  wire[at++] = record->mpv_group;

  return at;
}

/* Underlying Ref Data Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_underlying_ref_data_message(UnderlyingRefDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  record->mpv_group = wire[at++];

  return at;
}

/* what was read of Underlying Ref Data Message is what was written, byte for byte */
static void equal_underlying_ref_data_message(const UnderlyingRefDataMessage *read, const UnderlyingRefDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  assert(read->mpv_group == written->mpv_group);
}

/* Underlying Ref Data Message: written and read back, then read and written back */
static void check_underlying_ref_data_message(void) {
  UnderlyingRefDataMessage sent;
  UnderlyingRefDataMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_underlying_ref_data_message(&sent);
  assert(encode_underlying_ref_data_message(&sent, wire, 0) == 25);
  assert(decode_underlying_ref_data_message(&got, wire, 0) == 25);
  equal_underlying_ref_data_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_underlying_ref_data_message(&got, wire, 0) == 25);
  assert(encode_underlying_ref_data_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Ref Data Message: 59 bytes ----------------------------------- */

/* InstrumentRefDataMessage */
typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t instrument_id[4];  /* bytes 8 to 11 */
  uint8_t underlying_id[4];  /* bytes 12 to 15 */
  uint8_t osi_symbol[21];    /* bytes 16 to 36 */
  uint8_t maturity_date[8];  /* bytes 37 to 44 */
  uint8_t option_type;       /* byte 45 */
  uint8_t strike_price[8];   /* bytes 46 to 53 */
  uint8_t closing_only;      /* byte 54 */
  uint8_t orp_enabled;       /* byte 55 */
  uint8_t trading_ring;      /* byte 56 */
  uint8_t matching_unit[2];  /* bytes 57 to 58 */
} InstrumentRefDataMessage;

/* any Instrument Ref Data Message at all: every byte one the checker chooses */
static void any_instrument_ref_data_message(InstrumentRefDataMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = arbitrary(); }
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->closing_only = arbitrary();
  record->orp_enabled = arbitrary();
  record->trading_ring = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->matching_unit[i] = arbitrary(); }
}

/* Instrument Ref Data Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_instrument_ref_data_message(const InstrumentRefDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_date[i]; }
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->closing_only;
  wire[at++] = record->orp_enabled;
  wire[at++] = record->trading_ring;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->matching_unit[i]; }

  return at;
}

/* Instrument Ref Data Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_instrument_ref_data_message(InstrumentRefDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_date[i] = wire[at++]; }
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->closing_only = wire[at++];
  record->orp_enabled = wire[at++];
  record->trading_ring = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->matching_unit[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Ref Data Message is what was written, byte for byte */
static void equal_instrument_ref_data_message(const InstrumentRefDataMessage *read, const InstrumentRefDataMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->closing_only == written->closing_only);
  assert(read->orp_enabled == written->orp_enabled);
  assert(read->trading_ring == written->trading_ring);
  for (size_t i = 0; i < 2; i++) { assert(read->matching_unit[i] == written->matching_unit[i]); }
}

/* Instrument Ref Data Message: written and read back, then read and written back */
static void check_instrument_ref_data_message(void) {
  InstrumentRefDataMessage sent;
  InstrumentRefDataMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_instrument_ref_data_message(&sent);
  assert(encode_instrument_ref_data_message(&sent, wire, 0) == 59);
  assert(decode_instrument_ref_data_message(&got, wire, 0) == 59);
  equal_instrument_ref_data_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_ref_data_message(&got, wire, 0) == 59);
  assert(encode_instrument_ref_data_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mpid Configuration Acknowledgement Message: 76 bytes -------------------- */

/* MPIDConfigurationAcknowledgementMessage */
typedef struct {
  uint8_t transact_time[8];             /* bytes 0 to 7 */
  uint8_t market_participant_id[4];     /* bytes 8 to 11 */
  uint8_t mpid_status;                  /* byte 12 */
  uint8_t member[8];                    /* bytes 13 to 20 */
  uint8_t max_qty[4];                   /* bytes 21 to 24 */
  uint8_t max_notional[8];              /* bytes 25 to 32 */
  uint8_t default_account[16];          /* bytes 33 to 48 */
  uint8_t default_optional_data[16];    /* bytes 49 to 64 */
  uint8_t default_clearing_account[4];  /* bytes 65 to 68 */
  uint8_t allow_market_orders;          /* byte 69 */
  uint8_t allow_isoioc;                 /* byte 70 */
  uint8_t allow_iso_day;                /* byte 71 */
  uint8_t max_duplicative[4];           /* bytes 72 to 75 */
} MpidConfigurationAcknowledgementMessage;

/* any Mpid Configuration Acknowledgement Message at all: every byte one the checker chooses */
static void any_mpid_configuration_acknowledgement_message(MpidConfigurationAcknowledgementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  record->mpid_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->max_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_notional[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->default_account[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->default_optional_data[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->default_clearing_account[i] = arbitrary(); }
  record->allow_market_orders = arbitrary();
  record->allow_isoioc = arbitrary();
  record->allow_iso_day = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_duplicative[i] = arbitrary(); }
}

/* Mpid Configuration Acknowledgement Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_mpid_configuration_acknowledgement_message(const MpidConfigurationAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  wire[at++] = record->mpid_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_notional[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->default_account[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->default_optional_data[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->default_clearing_account[i]; }
  wire[at++] = record->allow_market_orders;
  wire[at++] = record->allow_isoioc;
  wire[at++] = record->allow_iso_day;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_duplicative[i]; }

  return at;
}

/* Mpid Configuration Acknowledgement Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_mpid_configuration_acknowledgement_message(MpidConfigurationAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  record->mpid_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->max_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_notional[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->default_account[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->default_optional_data[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->default_clearing_account[i] = wire[at++]; }
  record->allow_market_orders = wire[at++];
  record->allow_isoioc = wire[at++];
  record->allow_iso_day = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_duplicative[i] = wire[at++]; }

  return at;
}

/* what was read of Mpid Configuration Acknowledgement Message is what was written, byte for byte */
static void equal_mpid_configuration_acknowledgement_message(const MpidConfigurationAcknowledgementMessage *read, const MpidConfigurationAcknowledgementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  assert(read->mpid_status == written->mpid_status);
  for (size_t i = 0; i < 8; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->max_qty[i] == written->max_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_notional[i] == written->max_notional[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->default_account[i] == written->default_account[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->default_optional_data[i] == written->default_optional_data[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->default_clearing_account[i] == written->default_clearing_account[i]); }
  assert(read->allow_market_orders == written->allow_market_orders);
  assert(read->allow_isoioc == written->allow_isoioc);
  assert(read->allow_iso_day == written->allow_iso_day);
  for (size_t i = 0; i < 4; i++) { assert(read->max_duplicative[i] == written->max_duplicative[i]); }
}

/* Mpid Configuration Acknowledgement Message: written and read back, then read and written back */
static void check_mpid_configuration_acknowledgement_message(void) {
  MpidConfigurationAcknowledgementMessage sent;
  MpidConfigurationAcknowledgementMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_mpid_configuration_acknowledgement_message(&sent);
  assert(encode_mpid_configuration_acknowledgement_message(&sent, wire, 0) == 76);
  assert(decode_mpid_configuration_acknowledgement_message(&got, wire, 0) == 76);
  equal_mpid_configuration_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_mpid_configuration_acknowledgement_message(&got, wire, 0) == 76);
  assert(encode_mpid_configuration_acknowledgement_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Maker Symbol Appointment Message: 26 bytes ----------------------- */

/* MarketMakerSymbolAppointmentMessage */
typedef struct {
  uint8_t transact_time[8];          /* bytes 0 to 7 */
  uint8_t underlying_id[4];          /* bytes 8 to 11 */
  uint8_t market_participant_id[4];  /* bytes 12 to 15 */
  uint8_t appointment_type;          /* byte 16 */
  uint8_t appointment_status;        /* byte 17 */
  uint8_t max_allowable_width[4];    /* bytes 18 to 21 */
  uint8_t quote_relief_mult[4];      /* bytes 22 to 25 */
} MarketMakerSymbolAppointmentMessage;

/* any Market Maker Symbol Appointment Message at all: every byte one the checker chooses */
static void any_market_maker_symbol_appointment_message(MarketMakerSymbolAppointmentMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  record->appointment_type = arbitrary();
  record->appointment_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->max_allowable_width[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_relief_mult[i] = arbitrary(); }
}

/* Market Maker Symbol Appointment Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_market_maker_symbol_appointment_message(const MarketMakerSymbolAppointmentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  wire[at++] = record->appointment_type;
  wire[at++] = record->appointment_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->max_allowable_width[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_relief_mult[i]; }

  return at;
}

/* Market Maker Symbol Appointment Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_market_maker_symbol_appointment_message(MarketMakerSymbolAppointmentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  record->appointment_type = wire[at++];
  record->appointment_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->max_allowable_width[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_relief_mult[i] = wire[at++]; }

  return at;
}

/* what was read of Market Maker Symbol Appointment Message is what was written, byte for byte */
static void equal_market_maker_symbol_appointment_message(const MarketMakerSymbolAppointmentMessage *read, const MarketMakerSymbolAppointmentMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id[i] == written->underlying_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  assert(read->appointment_type == written->appointment_type);
  assert(read->appointment_status == written->appointment_status);
  for (size_t i = 0; i < 4; i++) { assert(read->max_allowable_width[i] == written->max_allowable_width[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_relief_mult[i] == written->quote_relief_mult[i]); }
}

/* Market Maker Symbol Appointment Message: written and read back, then read and written back */
static void check_market_maker_symbol_appointment_message(void) {
  MarketMakerSymbolAppointmentMessage sent;
  MarketMakerSymbolAppointmentMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_market_maker_symbol_appointment_message(&sent);
  assert(encode_market_maker_symbol_appointment_message(&sent, wire, 0) == 26);
  assert(decode_market_maker_symbol_appointment_message(&got, wire, 0) == 26);
  equal_market_maker_symbol_appointment_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_market_maker_symbol_appointment_message(&got, wire, 0) == 26);
  assert(encode_market_maker_symbol_appointment_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Configuration Acknowledgement Message: 35 bytes ----------------- */

/* SessionConfigurationAcknowledgementMessage */
typedef struct {
  uint8_t transact_time[8];                    /* bytes 0 to 7 */
  uint8_t user_session_type;                   /* byte 8 */
  uint8_t user_session_status;                 /* byte 9 */
  uint8_t member[8];                           /* bytes 10 to 17 */
  uint8_t default_mpid[4];                     /* bytes 18 to 21 */
  uint8_t mic[4];                              /* bytes 22 to 25 */
  uint8_t cancel_on_disconnect;                /* byte 26 */
  uint8_t aiq_default[3];                      /* bytes 27 to 29 */
  uint8_t order_unsolicited_ack_subscription;  /* byte 30 */
  uint8_t quote_unsolicited_ack_subscription;  /* byte 31 */
  uint8_t default_attributed_quote;            /* byte 32 */
  uint8_t default_cancel_instead_of_slide;     /* byte 33 */
  uint8_t trading_ring;                        /* byte 34 */
} SessionConfigurationAcknowledgementMessage;

/* any Session Configuration Acknowledgement Message at all: every byte one the checker chooses */
static void any_session_configuration_acknowledgement_message(SessionConfigurationAcknowledgementMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->user_session_type = arbitrary();
  record->user_session_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->default_mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = arbitrary(); }
  record->cancel_on_disconnect = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->aiq_default[i] = arbitrary(); }
  record->order_unsolicited_ack_subscription = arbitrary();
  record->quote_unsolicited_ack_subscription = arbitrary();
  record->default_attributed_quote = arbitrary();
  record->default_cancel_instead_of_slide = arbitrary();
  record->trading_ring = arbitrary();
}

/* Session Configuration Acknowledgement Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_session_configuration_acknowledgement_message(const SessionConfigurationAcknowledgementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->user_session_type;
  wire[at++] = record->user_session_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->default_mpid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mic[i]; }
  wire[at++] = record->cancel_on_disconnect;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->aiq_default[i]; }
  wire[at++] = record->order_unsolicited_ack_subscription;
  wire[at++] = record->quote_unsolicited_ack_subscription;
  wire[at++] = record->default_attributed_quote;
  wire[at++] = record->default_cancel_instead_of_slide;
  wire[at++] = record->trading_ring;

  return at;
}

/* Session Configuration Acknowledgement Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_session_configuration_acknowledgement_message(SessionConfigurationAcknowledgementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->user_session_type = wire[at++];
  record->user_session_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->default_mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mic[i] = wire[at++]; }
  record->cancel_on_disconnect = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->aiq_default[i] = wire[at++]; }
  record->order_unsolicited_ack_subscription = wire[at++];
  record->quote_unsolicited_ack_subscription = wire[at++];
  record->default_attributed_quote = wire[at++];
  record->default_cancel_instead_of_slide = wire[at++];
  record->trading_ring = wire[at++];

  return at;
}

/* what was read of Session Configuration Acknowledgement Message is what was written, byte for byte */
static void equal_session_configuration_acknowledgement_message(const SessionConfigurationAcknowledgementMessage *read, const SessionConfigurationAcknowledgementMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->user_session_type == written->user_session_type);
  assert(read->user_session_status == written->user_session_status);
  for (size_t i = 0; i < 8; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->default_mpid[i] == written->default_mpid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mic[i] == written->mic[i]); }
  assert(read->cancel_on_disconnect == written->cancel_on_disconnect);
  for (size_t i = 0; i < 3; i++) { assert(read->aiq_default[i] == written->aiq_default[i]); }
  assert(read->order_unsolicited_ack_subscription == written->order_unsolicited_ack_subscription);
  assert(read->quote_unsolicited_ack_subscription == written->quote_unsolicited_ack_subscription);
  assert(read->default_attributed_quote == written->default_attributed_quote);
  assert(read->default_cancel_instead_of_slide == written->default_cancel_instead_of_slide);
  assert(read->trading_ring == written->trading_ring);
}

/* Session Configuration Acknowledgement Message: written and read back, then read and written back */
static void check_session_configuration_acknowledgement_message(void) {
  SessionConfigurationAcknowledgementMessage sent;
  SessionConfigurationAcknowledgementMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_session_configuration_acknowledgement_message(&sent);
  assert(encode_session_configuration_acknowledgement_message(&sent, wire, 0) == 35);
  assert(decode_session_configuration_acknowledgement_message(&got, wire, 0) == 35);
  equal_session_configuration_acknowledgement_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_session_configuration_acknowledgement_message(&got, wire, 0) == 35);
  assert(encode_session_configuration_acknowledgement_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Control Acknowledgment Message: 50 bytes --------------------------- */

/* RiskControlAcknowledgmentMessage */
typedef struct {
  uint8_t transact_time[8];             /* bytes 0 to 7 */
  uint8_t underlying_id_optional[4];    /* bytes 8 to 11 */
  uint8_t market_participant_id[4];     /* bytes 12 to 15 */
  uint8_t cl_ord_id[8];                 /* bytes 16 to 23 */
  uint8_t custom_group_id_optional[2];  /* bytes 24 to 25 */
  uint8_t risk_ack_type;                /* byte 26 */
  uint8_t risk_control_status;          /* byte 27 */
  uint8_t risk_control;                 /* byte 28 */
  uint8_t risk_action;                  /* byte 29 */
  uint8_t time_limit[8];                /* bytes 30 to 37 */
  uint8_t percentage_limit[4];          /* bytes 38 to 41 */
  uint8_t count_limit[4];               /* bytes 42 to 45 */
  uint8_t ioc_attribution;              /* byte 46 */
  uint8_t blocked_by_breach_indicator;  /* byte 47 */
  uint8_t cust_capacity_weight;         /* byte 48 */
  uint8_t throttle_indicator;           /* byte 49 */
} RiskControlAcknowledgmentMessage;

/* any Risk Control Acknowledgment Message at all: every byte one the checker chooses */
static void any_risk_control_acknowledgment_message(RiskControlAcknowledgmentMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id_optional[i] = arbitrary(); }
  record->risk_ack_type = arbitrary();
  record->risk_control_status = arbitrary();
  record->risk_control = arbitrary();
  record->risk_action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = arbitrary(); }
  record->ioc_attribution = arbitrary();
  record->blocked_by_breach_indicator = arbitrary();
  record->cust_capacity_weight = arbitrary();
  record->throttle_indicator = arbitrary();
}

/* Risk Control Acknowledgment Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_risk_control_acknowledgment_message(const RiskControlAcknowledgmentMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id_optional[i]; }
  wire[at++] = record->risk_ack_type;
  wire[at++] = record->risk_control_status;
  wire[at++] = record->risk_control;
  wire[at++] = record->risk_action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count_limit[i]; }
  wire[at++] = record->ioc_attribution;
  wire[at++] = record->blocked_by_breach_indicator;
  wire[at++] = record->cust_capacity_weight;
  wire[at++] = record->throttle_indicator;

  return at;
}

/* Risk Control Acknowledgment Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_risk_control_acknowledgment_message(RiskControlAcknowledgmentMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->custom_group_id_optional[i] = wire[at++]; }
  record->risk_ack_type = wire[at++];
  record->risk_control_status = wire[at++];
  record->risk_control = wire[at++];
  record->risk_action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = wire[at++]; }
  record->ioc_attribution = wire[at++];
  record->blocked_by_breach_indicator = wire[at++];
  record->cust_capacity_weight = wire[at++];
  record->throttle_indicator = wire[at++];

  return at;
}

/* what was read of Risk Control Acknowledgment Message is what was written, byte for byte */
static void equal_risk_control_acknowledgment_message(const RiskControlAcknowledgmentMessage *read, const RiskControlAcknowledgmentMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id_optional[i] == written->custom_group_id_optional[i]); }
  assert(read->risk_ack_type == written->risk_ack_type);
  assert(read->risk_control_status == written->risk_control_status);
  assert(read->risk_control == written->risk_control);
  assert(read->risk_action == written->risk_action);
  for (size_t i = 0; i < 8; i++) { assert(read->time_limit[i] == written->time_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage_limit[i] == written->percentage_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count_limit[i] == written->count_limit[i]); }
  assert(read->ioc_attribution == written->ioc_attribution);
  assert(read->blocked_by_breach_indicator == written->blocked_by_breach_indicator);
  assert(read->cust_capacity_weight == written->cust_capacity_weight);
  assert(read->throttle_indicator == written->throttle_indicator);
}

/* Risk Control Acknowledgment Message: written and read back, then read and written back */
static void check_risk_control_acknowledgment_message(void) {
  RiskControlAcknowledgmentMessage sent;
  RiskControlAcknowledgmentMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_risk_control_acknowledgment_message(&sent);
  assert(encode_risk_control_acknowledgment_message(&sent, wire, 0) == 50);
  assert(decode_risk_control_acknowledgment_message(&got, wire, 0) == 50);
  equal_risk_control_acknowledgment_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_control_acknowledgment_message(&got, wire, 0) == 50);
  assert(encode_risk_control_acknowledgment_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Control Alert Message: 34 bytes ------------------------------------ */

/* RiskControlAlertMessage */
typedef struct {
  uint8_t transact_time[8];           /* bytes 0 to 7 */
  uint8_t underlying_id_optional[4];  /* bytes 8 to 11 */
  uint8_t market_participant_id[4];   /* bytes 12 to 15 */
  uint8_t risk_control;               /* byte 16 */
  uint8_t time_limit[8];              /* bytes 17 to 24 */
  uint8_t percentage_limit[4];        /* bytes 25 to 28 */
  uint8_t count_limit[4];             /* bytes 29 to 32 */
  uint8_t notification_reason;        /* byte 33 */
} RiskControlAlertMessage;

/* any Risk Control Alert Message at all: every byte one the checker chooses */
static void any_risk_control_alert_message(RiskControlAlertMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  record->risk_control = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = arbitrary(); }
  record->notification_reason = arbitrary();
}

/* Risk Control Alert Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_risk_control_alert_message(const RiskControlAlertMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  wire[at++] = record->risk_control;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count_limit[i]; }
  wire[at++] = record->notification_reason;

  return at;
}

/* Risk Control Alert Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_risk_control_alert_message(RiskControlAlertMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  record->risk_control = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = wire[at++]; }
  record->notification_reason = wire[at++];

  return at;
}

/* what was read of Risk Control Alert Message is what was written, byte for byte */
static void equal_risk_control_alert_message(const RiskControlAlertMessage *read, const RiskControlAlertMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  assert(read->risk_control == written->risk_control);
  for (size_t i = 0; i < 8; i++) { assert(read->time_limit[i] == written->time_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage_limit[i] == written->percentage_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count_limit[i] == written->count_limit[i]); }
  assert(read->notification_reason == written->notification_reason);
}

/* Risk Control Alert Message: written and read back, then read and written back */
static void check_risk_control_alert_message(void) {
  RiskControlAlertMessage sent;
  RiskControlAlertMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_risk_control_alert_message(&sent);
  assert(encode_risk_control_alert_message(&sent, wire, 0) == 34);
  assert(decode_risk_control_alert_message(&got, wire, 0) == 34);
  equal_risk_control_alert_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_control_alert_message(&got, wire, 0) == 34);
  assert(encode_risk_control_alert_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_response_message();
  check_session_info_group_encoding();
  check_terminate_message();
  check_sequenced_message_header_message();
  check_subsession_join_response_message();
  check_subsession_leave_response_message();
  check_order_ack_message();
  check_unsolicited_modify_ack_message();
  check_order_cancel_ack_message();
  check_mass_cancel_ack_message();
  check_quote_acks_group_encoding();
  check_new_ioc_quote_ack_message();
  check_quote_restated_message();
  check_quote_canceled_message();
  check_custom_group_ids_group_encoding();
  check_execution_report_message();
  check_trade_bust_correct_message();
  check_application_layer_reject_message();
  check_underlying_ref_data_message();
  check_instrument_ref_data_message();
  check_mpid_configuration_acknowledgement_message();
  check_market_maker_symbol_appointment_message();
  check_session_configuration_acknowledgement_message();
  check_risk_control_acknowledgment_message();
  check_risk_control_alert_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
