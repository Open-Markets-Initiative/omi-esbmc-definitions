// iex/iexoptions/binaryorderentry/IexOptions_BinaryOrderEntry_v1_02_Client.c
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

/* ---- Login Request Message: 48 bytes ----------------------------------------- */

/* LoginRequestMessage */
typedef struct {
  uint8_t logon_id[16];  /* bytes 0 to 15 */
  uint8_t token[32];     /* bytes 16 to 47 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->token[i] = arbitrary(); }
}

/* Login Request Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->logon_id[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->token[i]; }

  return at;
}

/* Login Request Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->logon_id[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->token[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->logon_id[i] == written->logon_id[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->token[i] == written->token[i]); }
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 48);
  assert(decode_login_request_message(&got, wire, 0) == 48);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 48);
  assert(encode_login_request_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
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

/* ---- Subsession Join Message: 16 bytes --------------------------------------- */

/* SubsessionJoinMessage */
typedef struct {
  uint8_t subsession_id[8];   /* bytes 0 to 7 */
  uint8_t start_sequence[4];  /* bytes 8 to 11 */
  uint8_t end_sequence[4];    /* bytes 12 to 15 */
} SubsessionJoinMessage;

/* any Subsession Join Message at all: every byte one the checker chooses */
static void any_subsession_join_message(SubsessionJoinMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_sequence[i] = arbitrary(); }
}

/* Subsession Join Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_subsession_join_message(const SubsessionJoinMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_sequence[i]; }

  return at;
}

/* Subsession Join Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_subsession_join_message(SubsessionJoinMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Subsession Join Message is what was written, byte for byte */
static void equal_subsession_join_message(const SubsessionJoinMessage *read, const SubsessionJoinMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_sequence[i] == written->start_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_sequence[i] == written->end_sequence[i]); }
}

/* Subsession Join Message: written and read back, then read and written back */
static void check_subsession_join_message(void) {
  SubsessionJoinMessage sent;
  SubsessionJoinMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_subsession_join_message(&sent);
  assert(encode_subsession_join_message(&sent, wire, 0) == 16);
  assert(decode_subsession_join_message(&got, wire, 0) == 16);
  equal_subsession_join_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_join_message(&got, wire, 0) == 16);
  assert(encode_subsession_join_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subsession Leave Message: 8 bytes --------------------------------------- */

/* SubsessionLeaveMessage */
typedef struct {
  uint8_t subsession_id[8];  /* bytes 0 to 7 */
} SubsessionLeaveMessage;

/* any Subsession Leave Message at all: every byte one the checker chooses */
static void any_subsession_leave_message(SubsessionLeaveMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = arbitrary(); }
}

/* Subsession Leave Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_subsession_leave_message(const SubsessionLeaveMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->subsession_id[i]; }

  return at;
}

/* Subsession Leave Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_subsession_leave_message(SubsessionLeaveMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->subsession_id[i] = wire[at++]; }

  return at;
}

/* what was read of Subsession Leave Message is what was written, byte for byte */
static void equal_subsession_leave_message(const SubsessionLeaveMessage *read, const SubsessionLeaveMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->subsession_id[i] == written->subsession_id[i]); }
}

/* Subsession Leave Message: written and read back, then read and written back */
static void check_subsession_leave_message(void) {
  SubsessionLeaveMessage sent;
  SubsessionLeaveMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_subsession_leave_message(&sent);
  assert(encode_subsession_leave_message(&sent, wire, 0) == 8);
  assert(decode_subsession_leave_message(&got, wire, 0) == 8);
  equal_subsession_leave_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_subsession_leave_message(&got, wire, 0) == 8);
  assert(encode_subsession_leave_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Single Message: 92 bytes -------------------------------------- */

/* NewOrderSingleMessage */
typedef struct {
  uint8_t account_account[16];             /* bytes 0 to 15 */
  uint8_t instrument_id[4];                /* bytes 16 to 19 */
  uint8_t market_participant_id[4];        /* bytes 20 to 23 */
  uint8_t cl_ord_id[8];                    /* bytes 24 to 31 */
  uint8_t clearing_account[4];             /* bytes 32 to 35 */
  uint8_t customer_or_firm;                /* byte 36 */
  uint8_t open_close;                      /* byte 37 */
  uint8_t attributed_quote;                /* byte 38 */
  uint8_t time_in_force;                   /* byte 39 */
  uint8_t cancel_instead_of_slide;         /* byte 40 */
  uint8_t display_inst;                    /* byte 41 */
  uint8_t exec_inst;                       /* byte 42 */
  uint8_t ord_type;                        /* byte 43 */
  uint8_t target_party_id[4];              /* bytes 44 to 47 */
  uint8_t auction_id[4];                   /* bytes 48 to 51 */
  uint8_t clearing_firm[4];                /* bytes 52 to 55 */
  uint8_t optional_data[16];               /* bytes 56 to 71 */
  uint8_t routing_firm_id[4];              /* bytes 72 to 75 */
  uint8_t aiq[3];                          /* bytes 76 to 78 */
  uint8_t side;                            /* byte 79 */
  uint8_t price_price_8[8];                /* bytes 80 to 87 */
  uint8_t order_qty_quantity_non_zero[4];  /* bytes 88 to 91 */
} NewOrderSingleMessage;

/* any New Order Single Message at all: every byte one the checker chooses */
static void any_new_order_single_message(NewOrderSingleMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
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
  for (size_t i = 0; i < 4; i++) { record->order_qty_quantity_non_zero[i] = arbitrary(); }
}

/* New Order Single Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_new_order_single_message(const NewOrderSingleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_quantity_non_zero[i]; }

  return at;
}

/* New Order Single Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_new_order_single_message(NewOrderSingleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
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
  for (size_t i = 0; i < 4; i++) { record->order_qty_quantity_non_zero[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Single Message is what was written, byte for byte */
static void equal_new_order_single_message(const NewOrderSingleMessage *read, const NewOrderSingleMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account_account[i] == written->account_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_quantity_non_zero[i] == written->order_qty_quantity_non_zero[i]); }
}

/* New Order Single Message: written and read back, then read and written back */
static void check_new_order_single_message(void) {
  NewOrderSingleMessage sent;
  NewOrderSingleMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_new_order_single_message(&sent);
  assert(encode_new_order_single_message(&sent, wire, 0) == 92);
  assert(decode_new_order_single_message(&got, wire, 0) == 92);
  equal_new_order_single_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_single_message(&got, wire, 0) == 92);
  assert(encode_new_order_single_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Replace Request Message: 100 bytes ------------------------- */

/* OrderCancelReplaceRequestMessage */
typedef struct {
  uint8_t account_account[16];               /* bytes 0 to 15 */
  uint8_t instrument_id[4];                  /* bytes 16 to 19 */
  uint8_t market_participant_id[4];          /* bytes 20 to 23 */
  uint8_t cl_ord_id[8];                      /* bytes 24 to 31 */
  uint8_t clearing_account[4];               /* bytes 32 to 35 */
  uint8_t orig_cl_ord_id[8];                 /* bytes 36 to 43 */
  uint8_t customer_or_firm;                  /* byte 44 */
  uint8_t open_close;                        /* byte 45 */
  uint8_t attributed_quote;                  /* byte 46 */
  uint8_t time_in_force;                     /* byte 47 */
  uint8_t cancel_instead_of_slide_optional;  /* byte 48 */
  uint8_t display_inst;                      /* byte 49 */
  uint8_t exec_inst;                         /* byte 50 */
  uint8_t ord_type;                          /* byte 51 */
  uint8_t target_party_id[4];                /* bytes 52 to 55 */
  uint8_t auction_id[4];                     /* bytes 56 to 59 */
  uint8_t clearing_firm[4];                  /* bytes 60 to 63 */
  uint8_t optional_data[16];                 /* bytes 64 to 79 */
  uint8_t routing_firm_id[4];                /* bytes 80 to 83 */
  uint8_t aiq[3];                            /* bytes 84 to 86 */
  uint8_t side;                              /* byte 87 */
  uint8_t price_price_8[8];                  /* bytes 88 to 95 */
  uint8_t order_qty_quantity_non_zero[4];    /* bytes 96 to 99 */
} OrderCancelReplaceRequestMessage;

/* any Order Cancel Replace Request Message at all: every byte one the checker chooses */
static void any_order_cancel_replace_request_message(OrderCancelReplaceRequestMessage *record) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->customer_or_firm = arbitrary();
  record->open_close = arbitrary();
  record->attributed_quote = arbitrary();
  record->time_in_force = arbitrary();
  record->cancel_instead_of_slide_optional = arbitrary();
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
  for (size_t i = 0; i < 4; i++) { record->order_qty_quantity_non_zero[i] = arbitrary(); }
}

/* Order Cancel Replace Request Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_replace_request_message(const OrderCancelReplaceRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->customer_or_firm;
  wire[at++] = record->open_close;
  wire[at++] = record->attributed_quote;
  wire[at++] = record->time_in_force;
  wire[at++] = record->cancel_instead_of_slide_optional;
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_quantity_non_zero[i]; }

  return at;
}

/* Order Cancel Replace Request Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_replace_request_message(OrderCancelReplaceRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->account_account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->customer_or_firm = wire[at++];
  record->open_close = wire[at++];
  record->attributed_quote = wire[at++];
  record->time_in_force = wire[at++];
  record->cancel_instead_of_slide_optional = wire[at++];
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
  for (size_t i = 0; i < 4; i++) { record->order_qty_quantity_non_zero[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Replace Request Message is what was written, byte for byte */
static void equal_order_cancel_replace_request_message(const OrderCancelReplaceRequestMessage *read, const OrderCancelReplaceRequestMessage *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->account_account[i] == written->account_account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->customer_or_firm == written->customer_or_firm);
  assert(read->open_close == written->open_close);
  assert(read->attributed_quote == written->attributed_quote);
  assert(read->time_in_force == written->time_in_force);
  assert(read->cancel_instead_of_slide_optional == written->cancel_instead_of_slide_optional);
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_quantity_non_zero[i] == written->order_qty_quantity_non_zero[i]); }
}

/* Order Cancel Replace Request Message: written and read back, then read and written back */
static void check_order_cancel_replace_request_message(void) {
  OrderCancelReplaceRequestMessage sent;
  OrderCancelReplaceRequestMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_order_cancel_replace_request_message(&sent);
  assert(encode_order_cancel_replace_request_message(&sent, wire, 0) == 100);
  assert(decode_order_cancel_replace_request_message(&got, wire, 0) == 100);
  equal_order_cancel_replace_request_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_replace_request_message(&got, wire, 0) == 100);
  assert(encode_order_cancel_replace_request_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Request Message: 24 bytes ---------------------------------- */

/* OrderCancelRequestMessage */
typedef struct {
  uint8_t instrument_id[4];          /* bytes 0 to 3 */
  uint8_t market_participant_id[4];  /* bytes 4 to 7 */
  uint8_t cl_ord_id[8];              /* bytes 8 to 15 */
  uint8_t orig_cl_ord_id[8];         /* bytes 16 to 23 */
} OrderCancelRequestMessage;

/* any Order Cancel Request Message at all: every byte one the checker chooses */
static void any_order_cancel_request_message(OrderCancelRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
}

/* Order Cancel Request Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_request_message(const OrderCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }

  return at;
}

/* Order Cancel Request Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_request_message(OrderCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Request Message is what was written, byte for byte */
static void equal_order_cancel_request_message(const OrderCancelRequestMessage *read, const OrderCancelRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
}

/* Order Cancel Request Message: written and read back, then read and written back */
static void check_order_cancel_request_message(void) {
  OrderCancelRequestMessage sent;
  OrderCancelRequestMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_cancel_request_message(&sent);
  assert(encode_order_cancel_request_message(&sent, wire, 0) == 24);
  assert(decode_order_cancel_request_message(&got, wire, 0) == 24);
  equal_order_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_request_message(&got, wire, 0) == 24);
  assert(encode_order_cancel_request_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Updates Group Encoding: 2 bytes ----------------------------------- */

/* quoteUpdatesGroupEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} QuoteUpdatesGroupEncoding;

/* any Quote Updates Group Encoding at all: every byte one the checker chooses */
static void any_quote_updates_group_encoding(QuoteUpdatesGroupEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Quote Updates Group Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_quote_updates_group_encoding(const QuoteUpdatesGroupEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Quote Updates Group Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_quote_updates_group_encoding(QuoteUpdatesGroupEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Quote Updates Group Encoding is what was written, byte for byte */
static void equal_quote_updates_group_encoding(const QuoteUpdatesGroupEncoding *read, const QuoteUpdatesGroupEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Quote Updates Group Encoding: written and read back, then read and written back */
static void check_quote_updates_group_encoding(void) {
  QuoteUpdatesGroupEncoding sent;
  QuoteUpdatesGroupEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_quote_updates_group_encoding(&sent);
  assert(encode_quote_updates_group_encoding(&sent, wire, 0) == 2);
  assert(decode_quote_updates_group_encoding(&got, wire, 0) == 2);
  equal_quote_updates_group_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_updates_group_encoding(&got, wire, 0) == 2);
  assert(encode_quote_updates_group_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Request Message: 27 bytes ----------------------------------- */

/* MassCancelRequestMessage */
typedef struct {
  uint8_t underlying_id_optional[4];        /* bytes 0 to 3 */
  uint8_t market_participant_id[4];         /* bytes 4 to 7 */
  uint8_t cl_ord_id[8];                     /* bytes 8 to 15 */
  uint8_t send_time[8];                     /* bytes 16 to 23 */
  uint8_t ack_style_mass_cancel_ack_style;  /* byte 24 */
  uint8_t mpid_filter;                      /* byte 25 */
  uint8_t bulk_action;                      /* byte 26 */
} MassCancelRequestMessage;

/* any Mass Cancel Request Message at all: every byte one the checker chooses */
static void any_mass_cancel_request_message(MassCancelRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = arbitrary(); }
  record->ack_style_mass_cancel_ack_style = arbitrary();
  record->mpid_filter = arbitrary();
  record->bulk_action = arbitrary();
}

/* Mass Cancel Request Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_request_message(const MassCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->send_time[i]; }
  wire[at++] = record->ack_style_mass_cancel_ack_style;
  wire[at++] = record->mpid_filter;
  wire[at++] = record->bulk_action;

  return at;
}

/* Mass Cancel Request Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_request_message(MassCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->send_time[i] = wire[at++]; }
  record->ack_style_mass_cancel_ack_style = wire[at++];
  record->mpid_filter = wire[at++];
  record->bulk_action = wire[at++];

  return at;
}

/* what was read of Mass Cancel Request Message is what was written, byte for byte */
static void equal_mass_cancel_request_message(const MassCancelRequestMessage *read, const MassCancelRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->send_time[i] == written->send_time[i]); }
  assert(read->ack_style_mass_cancel_ack_style == written->ack_style_mass_cancel_ack_style);
  assert(read->mpid_filter == written->mpid_filter);
  assert(read->bulk_action == written->bulk_action);
}

/* Mass Cancel Request Message: written and read back, then read and written back */
static void check_mass_cancel_request_message(void) {
  MassCancelRequestMessage sent;
  MassCancelRequestMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_mass_cancel_request_message(&sent);
  assert(encode_mass_cancel_request_message(&sent, wire, 0) == 27);
  assert(decode_mass_cancel_request_message(&got, wire, 0) == 27);
  equal_mass_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_request_message(&got, wire, 0) == 27);
  assert(encode_mass_cancel_request_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
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

/* ---- Risk Limit Update Request Message: 36 bytes ----------------------------- */

/* RiskLimitUpdateRequestMessage */
typedef struct {
  uint8_t underlying_id_optional[4];      /* bytes 0 to 3 */
  uint8_t market_participant_id[4];       /* bytes 4 to 7 */
  uint8_t cl_ord_id[8];                   /* bytes 8 to 15 */
  uint8_t risk_control_optional;          /* byte 16 */
  uint8_t risk_control_status_optional;   /* byte 17 */
  uint8_t time_limit[8];                  /* bytes 18 to 25 */
  uint8_t percentage_limit[4];            /* bytes 26 to 29 */
  uint8_t count_limit[4];                 /* bytes 30 to 33 */
  uint8_t ioc_attribution;                /* byte 34 */
  uint8_t cust_capacity_weight_optional;  /* byte 35 */
} RiskLimitUpdateRequestMessage;

/* any Risk Limit Update Request Message at all: every byte one the checker chooses */
static void any_risk_limit_update_request_message(RiskLimitUpdateRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->risk_control_optional = arbitrary();
  record->risk_control_status_optional = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = arbitrary(); }
  record->ioc_attribution = arbitrary();
  record->cust_capacity_weight_optional = arbitrary();
}

/* Risk Limit Update Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_risk_limit_update_request_message(const RiskLimitUpdateRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->risk_control_optional;
  wire[at++] = record->risk_control_status_optional;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->percentage_limit[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count_limit[i]; }
  wire[at++] = record->ioc_attribution;
  wire[at++] = record->cust_capacity_weight_optional;

  return at;
}

/* Risk Limit Update Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_risk_limit_update_request_message(RiskLimitUpdateRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->risk_control_optional = wire[at++];
  record->risk_control_status_optional = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->time_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->percentage_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count_limit[i] = wire[at++]; }
  record->ioc_attribution = wire[at++];
  record->cust_capacity_weight_optional = wire[at++];

  return at;
}

/* what was read of Risk Limit Update Request Message is what was written, byte for byte */
static void equal_risk_limit_update_request_message(const RiskLimitUpdateRequestMessage *read, const RiskLimitUpdateRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->risk_control_optional == written->risk_control_optional);
  assert(read->risk_control_status_optional == written->risk_control_status_optional);
  for (size_t i = 0; i < 8; i++) { assert(read->time_limit[i] == written->time_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->percentage_limit[i] == written->percentage_limit[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count_limit[i] == written->count_limit[i]); }
  assert(read->ioc_attribution == written->ioc_attribution);
  assert(read->cust_capacity_weight_optional == written->cust_capacity_weight_optional);
}

/* Risk Limit Update Request Message: written and read back, then read and written back */
static void check_risk_limit_update_request_message(void) {
  RiskLimitUpdateRequestMessage sent;
  RiskLimitUpdateRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_risk_limit_update_request_message(&sent);
  assert(encode_risk_limit_update_request_message(&sent, wire, 0) == 36);
  assert(decode_risk_limit_update_request_message(&got, wire, 0) == 36);
  equal_risk_limit_update_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_limit_update_request_message(&got, wire, 0) == 36);
  assert(encode_risk_limit_update_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Risk Action Request Message: 20 bytes ----------------------------------- */

/* RiskActionRequestMessage */
typedef struct {
  uint8_t underlying_id_optional[4];    /* bytes 0 to 3 */
  uint8_t market_participant_id[4];     /* bytes 4 to 7 */
  uint8_t cl_ord_id[8];                 /* bytes 8 to 15 */
  uint8_t risk_control;                 /* byte 16 */
  uint8_t risk_action;                  /* byte 17 */
  uint8_t custom_group_id_optional[2];  /* bytes 18 to 19 */
} RiskActionRequestMessage;

/* any Risk Action Request Message at all: every byte one the checker chooses */
static void any_risk_action_request_message(RiskActionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->risk_control = arbitrary();
  record->risk_action = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->custom_group_id_optional[i] = arbitrary(); }
}

/* Risk Action Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_risk_action_request_message(const RiskActionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_participant_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->risk_control;
  wire[at++] = record->risk_action;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->custom_group_id_optional[i]; }

  return at;
}

/* Risk Action Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_risk_action_request_message(RiskActionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->underlying_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_participant_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->risk_control = wire[at++];
  record->risk_action = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->custom_group_id_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Risk Action Request Message is what was written, byte for byte */
static void equal_risk_action_request_message(const RiskActionRequestMessage *read, const RiskActionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->underlying_id_optional[i] == written->underlying_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_participant_id[i] == written->market_participant_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->risk_control == written->risk_control);
  assert(read->risk_action == written->risk_action);
  for (size_t i = 0; i < 2; i++) { assert(read->custom_group_id_optional[i] == written->custom_group_id_optional[i]); }
}

/* Risk Action Request Message: written and read back, then read and written back */
static void check_risk_action_request_message(void) {
  RiskActionRequestMessage sent;
  RiskActionRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_risk_action_request_message(&sent);
  assert(encode_risk_action_request_message(&sent, wire, 0) == 20);
  assert(decode_risk_action_request_message(&got, wire, 0) == 20);
  equal_risk_action_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_risk_action_request_message(&got, wire, 0) == 20);
  assert(encode_risk_action_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_request_message();
  check_sequenced_message_header_message();
  check_subsession_join_message();
  check_subsession_leave_message();
  check_new_order_single_message();
  check_order_cancel_replace_request_message();
  check_order_cancel_request_message();
  check_quote_updates_group_encoding();
  check_mass_cancel_request_message();
  check_custom_group_ids_group_encoding();
  check_risk_limit_update_request_message();
  check_risk_action_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
