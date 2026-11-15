// cme/brokertec/ilink3/BrokerTec_iLink3_v8_8_Client.c
/*
 * CME Group iLink 3
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
 *   - a field present only on a condition
 *   - a field read in bits
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

/* ---- Simple Open Framing Header: 4 bytes ------------------------------------- */

/* Simple Open Framing Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t encoding_type[2];   /* bytes 2 to 3 */
} SimpleOpenFramingHeader;

/* any Simple Open Framing Header at all: every byte one the checker chooses */
static void any_simple_open_framing_header(SimpleOpenFramingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
}

/* Simple Open Framing Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_simple_open_framing_header(const SimpleOpenFramingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }

  return at;
}

/* Simple Open Framing Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_simple_open_framing_header(SimpleOpenFramingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Open Framing Header is what was written, byte for byte */
static void equal_simple_open_framing_header(const SimpleOpenFramingHeader *read, const SimpleOpenFramingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
}

/* Simple Open Framing Header: written and read back, then read and written back */
static void check_simple_open_framing_header(void) {
  SimpleOpenFramingHeader sent;
  SimpleOpenFramingHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_simple_open_framing_header(&sent);
  assert(encode_simple_open_framing_header(&sent, wire, 0) == 4);
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  equal_simple_open_framing_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  assert(encode_simple_open_framing_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Template ID and length of message root */
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

/* ---- Sequence: 14 bytes ------------------------------------------------------ */

/* The Sequence message is used in both Recoverable (CME to customer) and Idempotent (customer to CME) flows. */
typedef struct {
  uint8_t uuid[8];                     /* bytes 0 to 7 */
  uint8_t next_seq_no[4];              /* bytes 8 to 11 */
  uint8_t fault_tolerance_indicator;   /* byte 12 */
  uint8_t keep_alive_interval_lapsed;  /* byte 13 */
} Sequence;

/* any Sequence at all: every byte one the checker chooses */
static void any_sequence(Sequence *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = arbitrary(); }
  record->fault_tolerance_indicator = arbitrary();
  record->keep_alive_interval_lapsed = arbitrary();
}

/* Sequence to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_sequence(const Sequence *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_seq_no[i]; }
  wire[at++] = record->fault_tolerance_indicator;
  wire[at++] = record->keep_alive_interval_lapsed;

  return at;
}

/* Sequence off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_sequence(Sequence *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_seq_no[i] = wire[at++]; }
  record->fault_tolerance_indicator = wire[at++];
  record->keep_alive_interval_lapsed = wire[at++];

  return at;
}

/* what was read of Sequence is what was written, byte for byte */
static void equal_sequence(const Sequence *read, const Sequence *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_seq_no[i] == written->next_seq_no[i]); }
  assert(read->fault_tolerance_indicator == written->fault_tolerance_indicator);
  assert(read->keep_alive_interval_lapsed == written->keep_alive_interval_lapsed);
}

/* Sequence: written and read back, then read and written back */
static void check_sequence(void) {
  Sequence sent;
  Sequence got;
  uint8_t wire[14];
  uint8_t again[14];

  any_sequence(&sent);
  assert(encode_sequence(&sent, wire, 0) == 14);
  assert(decode_sequence(&got, wire, 0) == 14);
  equal_sequence(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence(&got, wire, 0) == 14);
  assert(encode_sequence(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Terminate: 67 bytes ----------------------------------------------------- */

/* The Terminate message is sent to indicate that the sender is going to disconnect the TCP socket connection. */
typedef struct {
  uint8_t reason[48];            /* bytes 0 to 47 */
  uint8_t uuid[8];               /* bytes 48 to 55 */
  uint8_t request_timestamp[8];  /* bytes 56 to 63 */
  uint8_t error_codes[2];        /* bytes 64 to 65 */
  uint8_t split_msg;             /* byte 66 */
} Terminate;

/* any Terminate at all: every byte one the checker chooses */
static void any_terminate(Terminate *record) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = arbitrary(); }
  record->split_msg = arbitrary();
}

/* Terminate to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_terminate(const Terminate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { wire[at++] = record->reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_codes[i]; }
  wire[at++] = record->split_msg;

  return at;
}

/* Terminate off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_terminate(Terminate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 48; i++) { record->reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_codes[i] = wire[at++]; }
  record->split_msg = wire[at++];

  return at;
}

/* what was read of Terminate is what was written, byte for byte */
static void equal_terminate(const Terminate *read, const Terminate *written) {
  for (size_t i = 0; i < 48; i++) { assert(read->reason[i] == written->reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_codes[i] == written->error_codes[i]); }
  assert(read->split_msg == written->split_msg);
}

/* Terminate: written and read back, then read and written back */
static void check_terminate(void) {
  Terminate sent;
  Terminate got;
  uint8_t wire[67];
  uint8_t again[67];

  any_terminate(&sent);
  assert(encode_terminate(&sent, wire, 0) == 67);
  assert(decode_terminate(&got, wire, 0) == 67);
  equal_terminate(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_terminate(&got, wire, 0) == 67);
  assert(encode_terminate(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmit Request: 30 bytes -------------------------------------------- */

/* Customers can send the Retransmit Request message to recover missed messages. */
typedef struct {
  uint8_t uuid[8];               /* bytes 0 to 7 */
  uint8_t last_uuid[8];          /* bytes 8 to 15 */
  uint8_t request_timestamp[8];  /* bytes 16 to 23 */
  uint8_t from_seq_no[4];        /* bytes 24 to 27 */
  uint8_t msg_count_16[2];       /* bytes 28 to 29 */
} RetransmitRequest;

/* any Retransmit Request at all: every byte one the checker chooses */
static void any_retransmit_request(RetransmitRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->msg_count_16[i] = arbitrary(); }
}

/* Retransmit Request to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_retransmit_request(const RetransmitRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_uuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_timestamp[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_seq_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_count_16[i]; }

  return at;
}

/* Retransmit Request off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_retransmit_request(RetransmitRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_uuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->from_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->msg_count_16[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmit Request is what was written, byte for byte */
static void equal_retransmit_request(const RetransmitRequest *read, const RetransmitRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->uuid[i] == written->uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_uuid[i] == written->last_uuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_timestamp[i] == written->request_timestamp[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->from_seq_no[i] == written->from_seq_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->msg_count_16[i] == written->msg_count_16[i]); }
}

/* Retransmit Request: written and read back, then read and written back */
static void check_retransmit_request(void) {
  RetransmitRequest sent;
  RetransmitRequest got;
  uint8_t wire[30];
  uint8_t again[30];

  any_retransmit_request(&sent);
  assert(encode_retransmit_request(&sent, wire, 0) == 30);
  assert(decode_retransmit_request(&got, wire, 0) == 30);
  equal_retransmit_request(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmit_request(&got, wire, 0) == 30);
  assert(encode_retransmit_request(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Request: 96 bytes ------------------------------------------ */

/* Sent by client system to cancel an existing order; an order may be cancelled by referencing the Order ID. */
typedef struct {
  uint8_t order_id_optional[8];          /* bytes 0 to 7 */
  uint8_t party_details_list_req_id[8];  /* bytes 8 to 15 */
  uint8_t manual_order_indicator;        /* byte 16 */
  uint8_t seq_num[4];                    /* bytes 17 to 20 */
  uint8_t sender_id[20];                 /* bytes 21 to 40 */
  uint8_t cl_ord_id[20];                 /* bytes 41 to 60 */
  uint8_t order_request_id[8];           /* bytes 61 to 68 */
  uint8_t sending_time_epoch[8];         /* bytes 69 to 76 */
  uint8_t location[5];                   /* bytes 77 to 81 */
  uint8_t security_id[4];                /* bytes 82 to 85 */
  uint8_t side;                          /* byte 86 */
  uint8_t liquidity_flag;                /* byte 87 */
  uint8_t orig_order_user[8];            /* bytes 88 to 95 */
} OrderCancelRequest;

/* any Order Cancel Request at all: every byte one the checker chooses */
static void any_order_cancel_request(OrderCancelRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  record->liquidity_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_order_user[i] = arbitrary(); }
}

/* Order Cancel Request to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_request(const OrderCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_request_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  wire[at++] = record->liquidity_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_order_user[i]; }

  return at;
}

/* Order Cancel Request off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_request(OrderCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  record->liquidity_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_order_user[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Request is what was written, byte for byte */
static void equal_order_cancel_request(const OrderCancelRequest *read, const OrderCancelRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_request_id[i] == written->order_request_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  assert(read->liquidity_flag == written->liquidity_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_order_user[i] == written->orig_order_user[i]); }
}

/* Order Cancel Request: written and read back, then read and written back */
static void check_order_cancel_request(void) {
  OrderCancelRequest sent;
  OrderCancelRequest got;
  uint8_t wire[96];
  uint8_t again[96];

  any_order_cancel_request(&sent);
  assert(encode_order_cancel_request(&sent, wire, 0) == 96);
  assert(decode_order_cancel_request(&got, wire, 0) == 96);
  equal_order_cancel_request(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_request(&got, wire, 0) == 96);
  assert(encode_order_cancel_request(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size: 3 bytes ----------------------------------------------------- */

/* Repeating group dimensions */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group;     /* byte 2 */
} GroupSize;

/* any Group Size at all: every byte one the checker chooses */
static void any_group_size(GroupSize *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->num_in_group = arbitrary();
}

/* Group Size to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_size(const GroupSize *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_size(GroupSize *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size is what was written, byte for byte */
static void equal_group_size(const GroupSize *read, const GroupSize *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size: written and read back, then read and written back */
static void check_group_size(void) {
  GroupSize sent;
  GroupSize got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_size(&sent);
  assert(encode_group_size(&sent, wire, 0) == 3);
  assert(decode_group_size(&got, wire, 0) == 3);
  equal_group_size(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size(&got, wire, 0) == 3);
  assert(encode_group_size(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Action Request: 79 bytes ------------------------------------- */

/* An Order Mass Action Request is sent by the client system to cancel working orders for a particular SenderCompID for futures, options on futures, and BrokerTec markets on CME Globex. */
typedef struct {
  uint8_t party_details_list_req_id[8];  /* bytes 0 to 7 */
  uint8_t order_request_id[8];           /* bytes 8 to 15 */
  uint8_t manual_order_indicator;        /* byte 16 */
  uint8_t seq_num[4];                    /* bytes 17 to 20 */
  uint8_t sender_id[20];                 /* bytes 21 to 40 */
  uint8_t sending_time_epoch[8];         /* bytes 41 to 48 */
  uint8_t security_group[6];             /* bytes 49 to 54 */
  uint8_t location[5];                   /* bytes 55 to 59 */
  uint8_t security_id_optional[4];       /* bytes 60 to 63 */
  uint8_t mass_action_scope;             /* byte 64 */
  uint8_t market_segment_id;             /* byte 65 */
  uint8_t mass_cancel_request_type;      /* byte 66 */
  uint8_t side_optional;                 /* byte 67 */
  uint8_t mass_action_ord_typ;           /* byte 68 */
  uint8_t mass_cancel_tif;               /* byte 69 */
  uint8_t liquidity_flag;                /* byte 70 */
  uint8_t orig_order_user[8];            /* bytes 71 to 78 */
} OrderMassActionRequest;

/* any Order Mass Action Request at all: every byte one the checker chooses */
static void any_order_mass_action_request(OrderMassActionRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_optional[i] = arbitrary(); }
  record->mass_action_scope = arbitrary();
  record->market_segment_id = arbitrary();
  record->mass_cancel_request_type = arbitrary();
  record->side_optional = arbitrary();
  record->mass_action_ord_typ = arbitrary();
  record->mass_cancel_tif = arbitrary();
  record->liquidity_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->orig_order_user[i] = arbitrary(); }
}

/* Order Mass Action Request to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_action_request(const OrderMassActionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_request_id[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_optional[i]; }
  wire[at++] = record->mass_action_scope;
  wire[at++] = record->market_segment_id;
  wire[at++] = record->mass_cancel_request_type;
  wire[at++] = record->side_optional;
  wire[at++] = record->mass_action_ord_typ;
  wire[at++] = record->mass_cancel_tif;
  wire[at++] = record->liquidity_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_order_user[i]; }

  return at;
}

/* Order Mass Action Request off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_action_request(OrderMassActionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_request_id[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_optional[i] = wire[at++]; }
  record->mass_action_scope = wire[at++];
  record->market_segment_id = wire[at++];
  record->mass_cancel_request_type = wire[at++];
  record->side_optional = wire[at++];
  record->mass_action_ord_typ = wire[at++];
  record->mass_cancel_tif = wire[at++];
  record->liquidity_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->orig_order_user[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Action Request is what was written, byte for byte */
static void equal_order_mass_action_request(const OrderMassActionRequest *read, const OrderMassActionRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_request_id[i] == written->order_request_id[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_optional[i] == written->security_id_optional[i]); }
  assert(read->mass_action_scope == written->mass_action_scope);
  assert(read->market_segment_id == written->market_segment_id);
  assert(read->mass_cancel_request_type == written->mass_cancel_request_type);
  assert(read->side_optional == written->side_optional);
  assert(read->mass_action_ord_typ == written->mass_action_ord_typ);
  assert(read->mass_cancel_tif == written->mass_cancel_tif);
  assert(read->liquidity_flag == written->liquidity_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_order_user[i] == written->orig_order_user[i]); }
}

/* Order Mass Action Request: written and read back, then read and written back */
static void check_order_mass_action_request(void) {
  OrderMassActionRequest sent;
  OrderMassActionRequest got;
  uint8_t wire[79];
  uint8_t again[79];

  any_order_mass_action_request(&sent);
  assert(encode_order_mass_action_request(&sent, wire, 0) == 79);
  assert(decode_order_mass_action_request(&got, wire, 0) == 79);
  equal_order_mass_action_request(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_action_request(&got, wire, 0) == 79);
  assert(encode_order_mass_action_request(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Status Request: 68 bytes ------------------------------------- */

/* The Order Mass Status Request message requests the status for orders matching criteria specified within the request. */
typedef struct {
  uint8_t party_details_list_req_id[8];  /* bytes 0 to 7 */
  uint8_t mass_status_req_id[8];         /* bytes 8 to 15 */
  uint8_t manual_order_indicator;        /* byte 16 */
  uint8_t seq_num[4];                    /* bytes 17 to 20 */
  uint8_t sender_id[20];                 /* bytes 21 to 40 */
  uint8_t sending_time_epoch[8];         /* bytes 41 to 48 */
  uint8_t security_group[6];             /* bytes 49 to 54 */
  uint8_t location[5];                   /* bytes 55 to 59 */
  uint8_t security_id_optional[4];       /* bytes 60 to 63 */
  uint8_t mass_status_req_type;          /* byte 64 */
  uint8_t ord_status_req_type;           /* byte 65 */
  uint8_t mass_status_tif;               /* byte 66 */
  uint8_t market_segment_id;             /* byte 67 */
} OrderMassStatusRequest;

/* any Order Mass Status Request at all: every byte one the checker chooses */
static void any_order_mass_status_request(OrderMassStatusRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mass_status_req_id[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_optional[i] = arbitrary(); }
  record->mass_status_req_type = arbitrary();
  record->ord_status_req_type = arbitrary();
  record->mass_status_tif = arbitrary();
  record->market_segment_id = arbitrary();
}

/* Order Mass Status Request to the wire: 68 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_status_request(const OrderMassStatusRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mass_status_req_id[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_optional[i]; }
  wire[at++] = record->mass_status_req_type;
  wire[at++] = record->ord_status_req_type;
  wire[at++] = record->mass_status_tif;
  wire[at++] = record->market_segment_id;

  return at;
}

/* Order Mass Status Request off the wire: 68 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_status_request(OrderMassStatusRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mass_status_req_id[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_optional[i] = wire[at++]; }
  record->mass_status_req_type = wire[at++];
  record->ord_status_req_type = wire[at++];
  record->mass_status_tif = wire[at++];
  record->market_segment_id = wire[at++];

  return at;
}

/* what was read of Order Mass Status Request is what was written, byte for byte */
static void equal_order_mass_status_request(const OrderMassStatusRequest *read, const OrderMassStatusRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mass_status_req_id[i] == written->mass_status_req_id[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_optional[i] == written->security_id_optional[i]); }
  assert(read->mass_status_req_type == written->mass_status_req_type);
  assert(read->ord_status_req_type == written->ord_status_req_type);
  assert(read->mass_status_tif == written->mass_status_tif);
  assert(read->market_segment_id == written->market_segment_id);
}

/* Order Mass Status Request: written and read back, then read and written back */
static void check_order_mass_status_request(void) {
  OrderMassStatusRequest sent;
  OrderMassStatusRequest got;
  uint8_t wire[68];
  uint8_t again[68];

  any_order_mass_status_request(&sent);
  assert(encode_order_mass_status_request(&sent, wire, 0) == 68);
  assert(decode_order_mass_status_request(&got, wire, 0) == 68);
  equal_order_mass_status_request(&got, &sent);

  for (size_t i = 0; i < 68; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_status_request(&got, wire, 0) == 68);
  assert(encode_order_mass_status_request(&got, again, 0) == 68);
  for (size_t i = 0; i < 68; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Status Request: 62 bytes ------------------------------------------ */

/* Submitted by the client system to obtain the current status of a specific order; CME Globex returns the order status in the form of an Execution Report (MsgType=8) with the status listed in tag 39-OrdStatus. */
typedef struct {
  uint8_t party_details_list_req_id[8];  /* bytes 0 to 7 */
  uint8_t ord_status_req_id[8];          /* bytes 8 to 15 */
  uint8_t manual_order_indicator;        /* byte 16 */
  uint8_t seq_num[4];                    /* bytes 17 to 20 */
  uint8_t sender_id[20];                 /* bytes 21 to 40 */
  uint8_t order_id[8];                   /* bytes 41 to 48 */
  uint8_t sending_time_epoch[8];         /* bytes 49 to 56 */
  uint8_t location[5];                   /* bytes 57 to 61 */
} OrderStatusRequest;

/* any Order Status Request at all: every byte one the checker chooses */
static void any_order_status_request(OrderStatusRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ord_status_req_id[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
}

/* Order Status Request to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_order_status_request(const OrderStatusRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ord_status_req_id[i]; }
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }

  return at;
}

/* Order Status Request off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_order_status_request(OrderStatusRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ord_status_req_id[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }

  return at;
}

/* what was read of Order Status Request is what was written, byte for byte */
static void equal_order_status_request(const OrderStatusRequest *read, const OrderStatusRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ord_status_req_id[i] == written->ord_status_req_id[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
}

/* Order Status Request: written and read back, then read and written back */
static void check_order_status_request(void) {
  OrderStatusRequest sent;
  OrderStatusRequest got;
  uint8_t wire[62];
  uint8_t again[62];

  any_order_status_request(&sent);
  assert(encode_order_status_request(&sent, wire, 0) == 62);
  assert(decode_order_status_request(&got, wire, 0) == 62);
  equal_order_status_request(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_order_status_request(&got, wire, 0) == 62);
  assert(encode_order_status_request(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Ack: 101 bytes ------------------------------------------------ */

/* The Execution Acknowledgment message notifies CME that a given fill has either been accepted or rejected by a counterparty for EU bilateral trades. */
typedef struct {
  uint8_t party_details_list_req_id[8];  /* bytes 0 to 7 */
  uint8_t order_id[8];                   /* bytes 8 to 15 */
  uint8_t exec_ack_status;               /* byte 16 */
  uint8_t seq_num[4];                    /* bytes 17 to 20 */
  uint8_t cl_ord_id[20];                 /* bytes 21 to 40 */
  uint8_t sec_exec_id[8];                /* bytes 41 to 48 */
  uint8_t last_px[8];                    /* bytes 49 to 56 */
  uint8_t security_id[4];                /* bytes 57 to 60 */
  uint8_t last_qty[4];                   /* bytes 61 to 64 */
  uint8_t dk_reason;                     /* byte 65 */
  uint8_t side;                          /* byte 66 */
  uint8_t sender_id[20];                 /* bytes 67 to 86 */
  uint8_t sending_time_epoch[8];         /* bytes 87 to 94 */
  uint8_t location[5];                   /* bytes 95 to 99 */
  uint8_t manual_order_indicator;        /* byte 100 */
} ExecutionAck;

/* any Execution Ack at all: every byte one the checker chooses */
static void any_execution_ack(ExecutionAck *record) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->exec_ack_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sec_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  record->dk_reason = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->location[i] = arbitrary(); }
  record->manual_order_indicator = arbitrary();
}

/* Execution Ack to the wire: 101 bytes from at, returning where the next byte goes */
static size_t encode_execution_ack(const ExecutionAck *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->party_details_list_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->exec_ack_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seq_num[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sec_exec_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->dk_reason;
  wire[at++] = record->side;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_epoch[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->location[i]; }
  wire[at++] = record->manual_order_indicator;

  return at;
}

/* Execution Ack off the wire: 101 bytes from at, returning where the next byte lies */
static size_t decode_execution_ack(ExecutionAck *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->party_details_list_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->exec_ack_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sec_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  record->dk_reason = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_epoch[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->location[i] = wire[at++]; }
  record->manual_order_indicator = wire[at++];

  return at;
}

/* what was read of Execution Ack is what was written, byte for byte */
static void equal_execution_ack(const ExecutionAck *read, const ExecutionAck *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->party_details_list_req_id[i] == written->party_details_list_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->exec_ack_status == written->exec_ack_status);
  for (size_t i = 0; i < 4; i++) { assert(read->seq_num[i] == written->seq_num[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sec_exec_id[i] == written->sec_exec_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->dk_reason == written->dk_reason);
  assert(read->side == written->side);
  for (size_t i = 0; i < 20; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_epoch[i] == written->sending_time_epoch[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->location[i] == written->location[i]); }
  assert(read->manual_order_indicator == written->manual_order_indicator);
}

/* Execution Ack: written and read back, then read and written back */
static void check_execution_ack(void) {
  ExecutionAck sent;
  ExecutionAck got;
  uint8_t wire[101];
  uint8_t again[101];

  any_execution_ack(&sent);
  assert(encode_execution_ack(&sent, wire, 0) == 101);
  assert(decode_execution_ack(&got, wire, 0) == 101);
  equal_execution_ack(&got, &sent);

  for (size_t i = 0; i < 101; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_ack(&got, wire, 0) == 101);
  assert(encode_execution_ack(&got, again, 0) == 101);
  for (size_t i = 0; i < 101; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Option Delta: 5 bytes ----------------------------------------------- */

/* Up to 26 legs (i.e., repeating groups) supported for UDS for options. Up to 40 legs (i.e., repeating groups) supported for UDS for futures. Will be set to 0 for REPO */
typedef struct {
  uint8_t mantissa_32[4];  /* bytes 0 to 3 */
  uint8_t exponent;        /* byte 4 */
} LegOptionDelta;

/* any Leg Option Delta at all: every byte one the checker chooses */
static void any_leg_option_delta(LegOptionDelta *record) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = arbitrary(); }
  record->exponent = arbitrary();
}

/* Leg Option Delta to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_leg_option_delta(const LegOptionDelta *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mantissa_32[i]; }
  wire[at++] = record->exponent;

  return at;
}

/* Leg Option Delta off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_leg_option_delta(LegOptionDelta *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->mantissa_32[i] = wire[at++]; }
  record->exponent = wire[at++];

  return at;
}

/* what was read of Leg Option Delta is what was written, byte for byte */
static void equal_leg_option_delta(const LegOptionDelta *read, const LegOptionDelta *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->mantissa_32[i] == written->mantissa_32[i]); }
  assert(read->exponent == written->exponent);
}

/* Leg Option Delta: written and read back, then read and written back */
static void check_leg_option_delta(void) {
  LegOptionDelta sent;
  LegOptionDelta got;
  uint8_t wire[5];
  uint8_t again[5];

  any_leg_option_delta(&sent);
  assert(encode_leg_option_delta(&sent, wire, 0) == 5);
  assert(decode_leg_option_delta(&got, wire, 0) == 5);
  equal_leg_option_delta(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_option_delta(&got, wire, 0) == 5);
  assert(encode_leg_option_delta(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_simple_open_framing_header();
  check_message_header();
  check_sequence();
  check_terminate();
  check_retransmit_request();
  check_order_cancel_request();
  check_group_size();
  check_order_mass_action_request();
  check_order_mass_status_request();
  check_order_status_request();
  check_execution_ack();
  check_leg_option_delta();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
