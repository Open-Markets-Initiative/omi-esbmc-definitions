// euronext/optiq/orderentrygateway/Euronext_Optiq_OrderEntryGateway_v4_3.c
/*
 * Euronext Order Entry Gateway
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
 *   - a field read in bits
 *   - a block whose stated length holds more than its fields
 *   - a run counted by a field
 *   - a Empty element
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

/* ---- Frame Header: 2 bytes --------------------------------------------------- */

/* Optiq length prefix, read before the message it frames */
typedef struct {
  uint8_t frame[2];  /* bytes 0 to 1 */
} FrameHeader;

/* any Frame Header at all: every byte one the checker chooses */
static void any_frame_header(FrameHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->frame[i] = arbitrary(); }
}

/* Frame Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_frame_header(const FrameHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->frame[i]; }

  return at;
}

/* Frame Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_frame_header(FrameHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->frame[i] = wire[at++]; }

  return at;
}

/* what was read of Frame Header is what was written, byte for byte */
static void equal_frame_header(const FrameHeader *read, const FrameHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->frame[i] == written->frame[i]); }
}

/* Frame Header: written and read back, then read and written back */
static void check_frame_header(void) {
  FrameHeader sent;
  FrameHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_frame_header(&sent);
  assert(encode_frame_header(&sent, wire, 0) == 2);
  assert(decode_frame_header(&got, wire, 0) == 2);
  equal_frame_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_frame_header(&got, wire, 0) == 2);
  assert(encode_frame_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 8 bytes ------------------------------------------------- */

/* Optiq Sbe message header — message identifiers and length of message root */
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

/* ---- Group Size Encoding: 2 bytes -------------------------------------------- */

/* groupSizeEncoding */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Group Size Encoding to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Group Size Encoding off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[2];
  uint8_t again[2];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 2);
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 2);
  assert(encode_group_size_encoding(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open Order Request Message: 58 bytes ------------------------------------ */

/* OpenOrderRequestMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];                    /* bytes 0 to 3 */
  uint8_t firm_id[8];                           /* bytes 4 to 11 */
  uint8_t sending_time[8];                      /* bytes 12 to 19 */
  uint8_t execution_within_firm_short_code[4];  /* bytes 20 to 23 */
  uint8_t client_identification_shortcode[4];   /* bytes 24 to 27 */
  uint8_t client_order_id[8];                   /* bytes 28 to 35 */
  uint8_t order_id_optional[8];                 /* bytes 36 to 43 */
  uint8_t orig_client_order_id[8];              /* bytes 44 to 51 */
  uint8_t symbol_index[4];                      /* bytes 52 to 55 */
  uint8_t emm;                                  /* byte 56 */
  uint8_t order_category;                       /* byte 57 */
} OpenOrderRequestMessage;

/* any Open Order Request Message at all: every byte one the checker chooses */
static void any_open_order_request_message(OpenOrderRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->order_category = arbitrary();
}

/* Open Order Request Message to the wire: 58 bytes from at, returning where the next byte goes */
static size_t encode_open_order_request_message(const OpenOrderRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_within_firm_short_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identification_shortcode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->order_category;

  return at;
}

/* Open Order Request Message off the wire: 58 bytes from at, returning where the next byte lies */
static size_t decode_open_order_request_message(OpenOrderRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->order_category = wire[at++];

  return at;
}

/* what was read of Open Order Request Message is what was written, byte for byte */
static void equal_open_order_request_message(const OpenOrderRequestMessage *read, const OpenOrderRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_within_firm_short_code[i] == written->execution_within_firm_short_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_identification_shortcode[i] == written->client_identification_shortcode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_client_order_id[i] == written->orig_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->order_category == written->order_category);
}

/* Open Order Request Message: written and read back, then read and written back */
static void check_open_order_request_message(void) {
  OpenOrderRequestMessage sent;
  OpenOrderRequestMessage got;
  uint8_t wire[58];
  uint8_t again[58];

  any_open_order_request_message(&sent);
  assert(encode_open_order_request_message(&sent, wire, 0) == 58);
  assert(decode_open_order_request_message(&got, wire, 0) == 58);
  equal_open_order_request_message(&got, &sent);

  for (size_t i = 0; i < 58; i++) { wire[i] = arbitrary(); }
  assert(decode_open_order_request_message(&got, wire, 0) == 58);
  assert(encode_open_order_request_message(&got, again, 0) == 58);
  for (size_t i = 0; i < 58; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ownership Request Ack Message: 43 bytes --------------------------------- */

/* OwnershipRequestAckMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t firm_id[8];                     /* bytes 4 to 11 */
  uint8_t client_order_id[8];             /* bytes 12 to 19 */
  uint8_t order_id_optional[8];           /* bytes 20 to 27 */
  uint8_t symbol_index[4];                /* bytes 28 to 31 */
  uint8_t logical_access_id_optional[4];  /* bytes 32 to 35 */
  uint8_t oe_partition_id_optional[2];    /* bytes 36 to 37 */
  uint8_t total_affected_orders[4];       /* bytes 38 to 41 */
  uint8_t order_category;                 /* byte 42 */
} OwnershipRequestAckMessage;

/* any Ownership Request Ack Message at all: every byte one the checker chooses */
static void any_ownership_request_ack_message(OwnershipRequestAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->logical_access_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = arbitrary(); }
  record->order_category = arbitrary();
}

/* Ownership Request Ack Message to the wire: 43 bytes from at, returning where the next byte goes */
static size_t encode_ownership_request_ack_message(const OwnershipRequestAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->logical_access_id_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oe_partition_id_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_affected_orders[i]; }
  wire[at++] = record->order_category;

  return at;
}

/* Ownership Request Ack Message off the wire: 43 bytes from at, returning where the next byte lies */
static size_t decode_ownership_request_ack_message(OwnershipRequestAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->logical_access_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_affected_orders[i] = wire[at++]; }
  record->order_category = wire[at++];

  return at;
}

/* what was read of Ownership Request Ack Message is what was written, byte for byte */
static void equal_ownership_request_ack_message(const OwnershipRequestAckMessage *read, const OwnershipRequestAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->logical_access_id_optional[i] == written->logical_access_id_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oe_partition_id_optional[i] == written->oe_partition_id_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_affected_orders[i] == written->total_affected_orders[i]); }
  assert(read->order_category == written->order_category);
}

/* Ownership Request Ack Message: written and read back, then read and written back */
static void check_ownership_request_ack_message(void) {
  OwnershipRequestAckMessage sent;
  OwnershipRequestAckMessage got;
  uint8_t wire[43];
  uint8_t again[43];

  any_ownership_request_ack_message(&sent);
  assert(encode_ownership_request_ack_message(&sent, wire, 0) == 43);
  assert(decode_ownership_request_ack_message(&got, wire, 0) == 43);
  equal_ownership_request_ack_message(&got, &sent);

  for (size_t i = 0; i < 43; i++) { wire[i] = arbitrary(); }
  assert(decode_ownership_request_ack_message(&got, wire, 0) == 43);
  assert(encode_ownership_request_ack_message(&got, again, 0) == 43);
  for (size_t i = 0; i < 43; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ownership Request Message: 64 bytes ------------------------------------- */

/* OwnershipRequestMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];                    /* bytes 0 to 3 */
  uint8_t firm_id[8];                           /* bytes 4 to 11 */
  uint8_t sending_time[8];                      /* bytes 12 to 19 */
  uint8_t execution_within_firm_short_code[4];  /* bytes 20 to 23 */
  uint8_t client_identification_shortcode[4];   /* bytes 24 to 27 */
  uint8_t client_order_id[8];                   /* bytes 28 to 35 */
  uint8_t order_id_optional[8];                 /* bytes 36 to 43 */
  uint8_t orig_client_order_id[8];              /* bytes 44 to 51 */
  uint8_t symbol_index[4];                      /* bytes 52 to 55 */
  uint8_t emm;                                  /* byte 56 */
  uint8_t logical_access_id_optional[4];        /* bytes 57 to 60 */
  uint8_t oe_partition_id_optional[2];          /* bytes 61 to 62 */
  uint8_t order_category;                       /* byte 63 */
} OwnershipRequestMessage;

/* any Ownership Request Message at all: every byte one the checker chooses */
static void any_ownership_request_message(OwnershipRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->logical_access_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id_optional[i] = arbitrary(); }
  record->order_category = arbitrary();
}

/* Ownership Request Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_ownership_request_message(const OwnershipRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_within_firm_short_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identification_shortcode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->logical_access_id_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oe_partition_id_optional[i]; }
  wire[at++] = record->order_category;

  return at;
}

/* Ownership Request Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_ownership_request_message(OwnershipRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->logical_access_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id_optional[i] = wire[at++]; }
  record->order_category = wire[at++];

  return at;
}

/* what was read of Ownership Request Message is what was written, byte for byte */
static void equal_ownership_request_message(const OwnershipRequestMessage *read, const OwnershipRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_within_firm_short_code[i] == written->execution_within_firm_short_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_identification_shortcode[i] == written->client_identification_shortcode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_client_order_id[i] == written->orig_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 4; i++) { assert(read->logical_access_id_optional[i] == written->logical_access_id_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oe_partition_id_optional[i] == written->oe_partition_id_optional[i]); }
  assert(read->order_category == written->order_category);
}

/* Ownership Request Message: written and read back, then read and written back */
static void check_ownership_request_message(void) {
  OwnershipRequestMessage sent;
  OwnershipRequestMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_ownership_request_message(&sent);
  assert(encode_ownership_request_message(&sent, wire, 0) == 64);
  assert(decode_ownership_request_message(&got, wire, 0) == 64);
  equal_ownership_request_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_ownership_request_message(&got, wire, 0) == 64);
  assert(encode_ownership_request_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Notification Message: 81 bytes ------------------------------- */

/* TradeBustNotificationMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t firm_id[8];                     /* bytes 4 to 11 */
  uint8_t book_in[8];                     /* bytes 12 to 19 */
  uint8_t book_out_time_optional[8];      /* bytes 20 to 27 */
  uint8_t oeg_in_from_me_optional[8];     /* bytes 28 to 35 */
  uint8_t oeg_out_to_member_optional[8];  /* bytes 36 to 43 */
  uint8_t symbol_index[4];                /* bytes 44 to 47 */
  uint8_t emm;                            /* byte 48 */
  uint8_t execution_id[4];                /* bytes 49 to 52 */
  uint8_t last_traded_px[8];              /* bytes 53 to 60 */
  uint8_t last_shares[8];                 /* bytes 61 to 68 */
  uint8_t lis_transaction_id[4];          /* bytes 69 to 72 */
  uint8_t parent_exec_id[4];              /* bytes 73 to 76 */
  uint8_t parent_symbol_index[4];         /* bytes 77 to 80 */
} TradeBustNotificationMessage;

/* any Trade Bust Notification Message at all: every byte one the checker chooses */
static void any_trade_bust_notification_message(TradeBustNotificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_traded_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lis_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->parent_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->parent_symbol_index[i] = arbitrary(); }
}

/* Trade Bust Notification Message to the wire: 81 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_notification_message(const TradeBustNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_in_from_me_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lis_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->parent_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->parent_symbol_index[i]; }

  return at;
}

/* Trade Bust Notification Message off the wire: 81 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_notification_message(TradeBustNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_traded_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lis_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->parent_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->parent_symbol_index[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Notification Message is what was written, byte for byte */
static void equal_trade_bust_notification_message(const TradeBustNotificationMessage *read, const TradeBustNotificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time_optional[i] == written->book_out_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_in_from_me_optional[i] == written->oeg_in_from_me_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 4; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_px[i] == written->last_traded_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_shares[i] == written->last_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lis_transaction_id[i] == written->lis_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->parent_exec_id[i] == written->parent_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->parent_symbol_index[i] == written->parent_symbol_index[i]); }
}

/* Trade Bust Notification Message: written and read back, then read and written back */
static void check_trade_bust_notification_message(void) {
  TradeBustNotificationMessage sent;
  TradeBustNotificationMessage got;
  uint8_t wire[81];
  uint8_t again[81];

  any_trade_bust_notification_message(&sent);
  assert(encode_trade_bust_notification_message(&sent, wire, 0) == 81);
  assert(decode_trade_bust_notification_message(&got, wire, 0) == 81);
  equal_trade_bust_notification_message(&got, &sent);

  for (size_t i = 0; i < 81; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_notification_message(&got, wire, 0) == 81);
  assert(encode_trade_bust_notification_message(&got, again, 0) == 81);
  for (size_t i = 0; i < 81; i++) { assert(again[i] == wire[i]); }
}

/* ---- Collar Breach Confirmation Message: 57 bytes ---------------------------- */

/* CollarBreachConfirmationMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];                    /* bytes 0 to 3 */
  uint8_t firm_id[8];                           /* bytes 4 to 11 */
  uint8_t sending_time[8];                      /* bytes 12 to 19 */
  uint8_t execution_within_firm_short_code[4];  /* bytes 20 to 23 */
  uint8_t client_identification_shortcode[4];   /* bytes 24 to 27 */
  uint8_t client_order_id[8];                   /* bytes 28 to 35 */
  uint8_t symbol_index[4];                      /* bytes 36 to 39 */
  uint8_t emm;                                  /* byte 40 */
  uint8_t order_id_optional[8];                 /* bytes 41 to 48 */
  uint8_t orig_client_order_id[8];              /* bytes 49 to 56 */
} CollarBreachConfirmationMessage;

/* any Collar Breach Confirmation Message at all: every byte one the checker chooses */
static void any_collar_breach_confirmation_message(CollarBreachConfirmationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = arbitrary(); }
}

/* Collar Breach Confirmation Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_collar_breach_confirmation_message(const CollarBreachConfirmationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_within_firm_short_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identification_shortcode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_client_order_id[i]; }

  return at;
}

/* Collar Breach Confirmation Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_collar_breach_confirmation_message(CollarBreachConfirmationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_client_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Collar Breach Confirmation Message is what was written, byte for byte */
static void equal_collar_breach_confirmation_message(const CollarBreachConfirmationMessage *read, const CollarBreachConfirmationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_within_firm_short_code[i] == written->execution_within_firm_short_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_identification_shortcode[i] == written->client_identification_shortcode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_client_order_id[i] == written->orig_client_order_id[i]); }
}

/* Collar Breach Confirmation Message: written and read back, then read and written back */
static void check_collar_breach_confirmation_message(void) {
  CollarBreachConfirmationMessage sent;
  CollarBreachConfirmationMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_collar_breach_confirmation_message(&sent);
  assert(encode_collar_breach_confirmation_message(&sent, wire, 0) == 57);
  assert(decode_collar_breach_confirmation_message(&got, wire, 0) == 57);
  equal_collar_breach_confirmation_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_collar_breach_confirmation_message(&got, wire, 0) == 57);
  assert(encode_collar_breach_confirmation_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price Input Message: 50 bytes ------------------------------------------- */

/* PriceInputMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];                    /* bytes 0 to 3 */
  uint8_t firm_id[8];                           /* bytes 4 to 11 */
  uint8_t sending_time[8];                      /* bytes 12 to 19 */
  uint8_t execution_within_firm_short_code[4];  /* bytes 20 to 23 */
  uint8_t client_identification_shortcode[4];   /* bytes 24 to 27 */
  uint8_t client_order_id[8];                   /* bytes 28 to 35 */
  uint8_t symbol_index[4];                      /* bytes 36 to 39 */
  uint8_t emm;                                  /* byte 40 */
  uint8_t input_price_type;                     /* byte 41 */
  uint8_t price_optional[8];                    /* bytes 42 to 49 */
} PriceInputMessage;

/* any Price Input Message at all: every byte one the checker chooses */
static void any_price_input_message(PriceInputMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->input_price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
}

/* Price Input Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_price_input_message(const PriceInputMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_within_firm_short_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identification_shortcode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->input_price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }

  return at;
}

/* Price Input Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_price_input_message(PriceInputMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->input_price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Price Input Message is what was written, byte for byte */
static void equal_price_input_message(const PriceInputMessage *read, const PriceInputMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_within_firm_short_code[i] == written->execution_within_firm_short_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_identification_shortcode[i] == written->client_identification_shortcode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->input_price_type == written->input_price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
}

/* Price Input Message: written and read back, then read and written back */
static void check_price_input_message(void) {
  PriceInputMessage sent;
  PriceInputMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_price_input_message(&sent);
  assert(encode_price_input_message(&sent, wire, 0) == 50);
  assert(decode_price_input_message(&got, wire, 0) == 50);
  equal_price_input_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_price_input_message(&got, wire, 0) == 50);
  assert(encode_price_input_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Liquidity Provider Command Message: 42 bytes ---------------------------- */

/* LiquidityProviderCommandMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];                    /* bytes 0 to 3 */
  uint8_t firm_id[8];                           /* bytes 4 to 11 */
  uint8_t sending_time[8];                      /* bytes 12 to 19 */
  uint8_t execution_within_firm_short_code[4];  /* bytes 20 to 23 */
  uint8_t client_identification_shortcode[4];   /* bytes 24 to 27 */
  uint8_t client_order_id[8];                   /* bytes 28 to 35 */
  uint8_t symbol_index[4];                      /* bytes 36 to 39 */
  uint8_t emm;                                  /* byte 40 */
  uint8_t lp_action_code;                       /* byte 41 */
} LiquidityProviderCommandMessage;

/* any Liquidity Provider Command Message at all: every byte one the checker chooses */
static void any_liquidity_provider_command_message(LiquidityProviderCommandMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->lp_action_code = arbitrary();
}

/* Liquidity Provider Command Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_liquidity_provider_command_message(const LiquidityProviderCommandMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->execution_within_firm_short_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_identification_shortcode[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->lp_action_code;

  return at;
}

/* Liquidity Provider Command Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_liquidity_provider_command_message(LiquidityProviderCommandMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->execution_within_firm_short_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_identification_shortcode[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->lp_action_code = wire[at++];

  return at;
}

/* what was read of Liquidity Provider Command Message is what was written, byte for byte */
static void equal_liquidity_provider_command_message(const LiquidityProviderCommandMessage *read, const LiquidityProviderCommandMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->execution_within_firm_short_code[i] == written->execution_within_firm_short_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_identification_shortcode[i] == written->client_identification_shortcode[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->lp_action_code == written->lp_action_code);
}

/* Liquidity Provider Command Message: written and read back, then read and written back */
static void check_liquidity_provider_command_message(void) {
  LiquidityProviderCommandMessage sent;
  LiquidityProviderCommandMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_liquidity_provider_command_message(&sent);
  assert(encode_liquidity_provider_command_message(&sent, wire, 0) == 42);
  assert(decode_liquidity_provider_command_message(&got, wire, 0) == 42);
  equal_liquidity_provider_command_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_liquidity_provider_command_message(&got, wire, 0) == 42);
  assert(encode_liquidity_provider_command_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask For Quote Message: 18 bytes ----------------------------------------- */

/* AskForQuoteMessage */
typedef struct {
  uint8_t msg_seq_num[4];   /* bytes 0 to 3 */
  uint8_t firm_id[8];       /* bytes 4 to 11 */
  uint8_t symbol_index[4];  /* bytes 12 to 15 */
  uint8_t emm;              /* byte 16 */
  uint8_t afq_reason;       /* byte 17 */
} AskForQuoteMessage;

/* any Ask For Quote Message at all: every byte one the checker chooses */
static void any_ask_for_quote_message(AskForQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->afq_reason = arbitrary();
}

/* Ask For Quote Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_ask_for_quote_message(const AskForQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->afq_reason;

  return at;
}

/* Ask For Quote Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_ask_for_quote_message(AskForQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->afq_reason = wire[at++];

  return at;
}

/* what was read of Ask For Quote Message is what was written, byte for byte */
static void equal_ask_for_quote_message(const AskForQuoteMessage *read, const AskForQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->afq_reason == written->afq_reason);
}

/* Ask For Quote Message: written and read back, then read and written back */
static void check_ask_for_quote_message(void) {
  AskForQuoteMessage sent;
  AskForQuoteMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_ask_for_quote_message(&sent);
  assert(encode_ask_for_quote_message(&sent, wire, 0) == 18);
  assert(decode_ask_for_quote_message(&got, wire, 0) == 18);
  equal_ask_for_quote_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_for_quote_message(&got, wire, 0) == 18);
  assert(encode_ask_for_quote_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Execution Message: 17 bytes --------------------------------- */

/* RequestForExecutionMessage */
typedef struct {
  uint8_t msg_seq_num[4];   /* bytes 0 to 3 */
  uint8_t firm_id[8];       /* bytes 4 to 11 */
  uint8_t symbol_index[4];  /* bytes 12 to 15 */
  uint8_t emm;              /* byte 16 */
} RequestForExecutionMessage;

/* any Request For Execution Message at all: every byte one the checker chooses */
static void any_request_for_execution_message(RequestForExecutionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
}

/* Request For Execution Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_request_for_execution_message(const RequestForExecutionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;

  return at;
}

/* Request For Execution Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_request_for_execution_message(RequestForExecutionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];

  return at;
}

/* what was read of Request For Execution Message is what was written, byte for byte */
static void equal_request_for_execution_message(const RequestForExecutionMessage *read, const RequestForExecutionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
}

/* Request For Execution Message: written and read back, then read and written back */
static void check_request_for_execution_message(void) {
  RequestForExecutionMessage sent;
  RequestForExecutionMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_request_for_execution_message(&sent);
  assert(encode_request_for_execution_message(&sent, wire, 0) == 17);
  assert(decode_request_for_execution_message(&got, wire, 0) == 17);
  equal_request_for_execution_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_execution_message(&got, wire, 0) == 17);
  assert(encode_request_for_execution_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rfq Matching Status Message: 76 bytes ----------------------------------- */

/* RFQMatchingStatusMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t firm_id[8];                     /* bytes 4 to 11 */
  uint8_t book_in[8];                     /* bytes 12 to 19 */
  uint8_t book_out_time_optional[8];      /* bytes 20 to 27 */
  uint8_t oeg_in_from_me_optional[8];     /* bytes 28 to 35 */
  uint8_t oeg_out_to_member_optional[8];  /* bytes 36 to 43 */
  uint8_t quote_req_id[8];                /* bytes 44 to 51 */
  uint8_t potential_matching_px[8];       /* bytes 52 to 59 */
  uint8_t potential_matching_qty[8];      /* bytes 60 to 67 */
  uint8_t symbol_index[4];                /* bytes 68 to 71 */
  uint8_t emm;                            /* byte 72 */
  uint8_t side;                           /* byte 73 */
  uint8_t number_of_lps;                  /* byte 74 */
  uint8_t recipient_type;                 /* byte 75 */
} RfqMatchingStatusMessage;

/* any Rfq Matching Status Message at all: every byte one the checker chooses */
static void any_rfq_matching_status_message(RfqMatchingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->side = arbitrary();
  record->number_of_lps = arbitrary();
  record->recipient_type = arbitrary();
}

/* Rfq Matching Status Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_rfq_matching_status_message(const RfqMatchingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_in_from_me_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->potential_matching_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->potential_matching_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->side;
  wire[at++] = record->number_of_lps;
  wire[at++] = record->recipient_type;

  return at;
}

/* Rfq Matching Status Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_rfq_matching_status_message(RfqMatchingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->side = wire[at++];
  record->number_of_lps = wire[at++];
  record->recipient_type = wire[at++];

  return at;
}

/* what was read of Rfq Matching Status Message is what was written, byte for byte */
static void equal_rfq_matching_status_message(const RfqMatchingStatusMessage *read, const RfqMatchingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time_optional[i] == written->book_out_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_in_from_me_optional[i] == written->oeg_in_from_me_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_req_id[i] == written->quote_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->potential_matching_px[i] == written->potential_matching_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->potential_matching_qty[i] == written->potential_matching_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->side == written->side);
  assert(read->number_of_lps == written->number_of_lps);
  assert(read->recipient_type == written->recipient_type);
}

/* Rfq Matching Status Message: written and read back, then read and written back */
static void check_rfq_matching_status_message(void) {
  RfqMatchingStatusMessage sent;
  RfqMatchingStatusMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_rfq_matching_status_message(&sent);
  assert(encode_rfq_matching_status_message(&sent, wire, 0) == 76);
  assert(decode_rfq_matching_status_message(&got, wire, 0) == 76);
  equal_rfq_matching_status_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_rfq_matching_status_message(&got, wire, 0) == 76);
  assert(encode_rfq_matching_status_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rfqlp Matching Status Message: 66 bytes --------------------------------- */

/* RFQLPMatchingStatusMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t firm_id[8];                     /* bytes 4 to 11 */
  uint8_t book_in[8];                     /* bytes 12 to 19 */
  uint8_t book_out_time_optional[8];      /* bytes 20 to 27 */
  uint8_t oeg_in_from_me_optional[8];     /* bytes 28 to 35 */
  uint8_t oeg_out_to_member_optional[8];  /* bytes 36 to 43 */
  uint8_t quote_req_id[8];                /* bytes 44 to 51 */
  uint8_t potential_matching_qty[8];      /* bytes 52 to 59 */
  uint8_t symbol_index[4];                /* bytes 60 to 63 */
  uint8_t emm;                            /* byte 64 */
  uint8_t side;                           /* byte 65 */
} RfqlpMatchingStatusMessage;

/* any Rfqlp Matching Status Message at all: every byte one the checker chooses */
static void any_rfqlp_matching_status_message(RfqlpMatchingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  record->side = arbitrary();
}

/* Rfqlp Matching Status Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_rfqlp_matching_status_message(const RfqlpMatchingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_in_from_me_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->potential_matching_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  wire[at++] = record->side;

  return at;
}

/* Rfqlp Matching Status Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_rfqlp_matching_status_message(RfqlpMatchingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->potential_matching_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  record->side = wire[at++];

  return at;
}

/* what was read of Rfqlp Matching Status Message is what was written, byte for byte */
static void equal_rfqlp_matching_status_message(const RfqlpMatchingStatusMessage *read, const RfqlpMatchingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in[i] == written->book_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time_optional[i] == written->book_out_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_in_from_me_optional[i] == written->oeg_in_from_me_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_req_id[i] == written->quote_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->potential_matching_qty[i] == written->potential_matching_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  assert(read->side == written->side);
}

/* Rfqlp Matching Status Message: written and read back, then read and written back */
static void check_rfqlp_matching_status_message(void) {
  RfqlpMatchingStatusMessage sent;
  RfqlpMatchingStatusMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_rfqlp_matching_status_message(&sent);
  assert(encode_rfqlp_matching_status_message(&sent, wire, 0) == 66);
  assert(decode_rfqlp_matching_status_message(&got, wire, 0) == 66);
  equal_rfqlp_matching_status_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_rfqlp_matching_status_message(&got, wire, 0) == 66);
  assert(encode_rfqlp_matching_status_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synchronization Time Message: 22 bytes ---------------------------------- */

/* SynchronizationTimeMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t oeg_out_to_member_optional[8];  /* bytes 4 to 11 */
  uint8_t resynchronization_id[2];        /* bytes 12 to 13 */
  uint8_t last_book_in_time[8];           /* bytes 14 to 21 */
} SynchronizationTimeMessage;

/* any Synchronization Time Message at all: every byte one the checker chooses */
static void any_synchronization_time_message(SynchronizationTimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->resynchronization_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_book_in_time[i] = arbitrary(); }
}

/* Synchronization Time Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_synchronization_time_message(const SynchronizationTimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->resynchronization_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_book_in_time[i]; }

  return at;
}

/* Synchronization Time Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_synchronization_time_message(SynchronizationTimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->resynchronization_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_book_in_time[i] = wire[at++]; }

  return at;
}

/* what was read of Synchronization Time Message is what was written, byte for byte */
static void equal_synchronization_time_message(const SynchronizationTimeMessage *read, const SynchronizationTimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->resynchronization_id[i] == written->resynchronization_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_book_in_time[i] == written->last_book_in_time[i]); }
}

/* Synchronization Time Message: written and read back, then read and written back */
static void check_synchronization_time_message(void) {
  SynchronizationTimeMessage sent;
  SynchronizationTimeMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_synchronization_time_message(&sent);
  assert(encode_synchronization_time_message(&sent, wire, 0) == 22);
  assert(decode_synchronization_time_message(&got, wire, 0) == 22);
  equal_synchronization_time_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_synchronization_time_message(&got, wire, 0) == 22);
  assert(encode_synchronization_time_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Ack Message: 80 bytes ------------------------------- */

/* SecurityDefinitionAckMessage */
typedef struct {
  uint8_t msg_seq_num[4];                 /* bytes 0 to 3 */
  uint8_t firm_id[8];                     /* bytes 4 to 11 */
  uint8_t sending_time_optional[8];       /* bytes 12 to 19 */
  uint8_t oeg_in_from_member[8];          /* bytes 20 to 27 */
  uint8_t oeg_out_time_to_me[8];          /* bytes 28 to 35 */
  uint8_t book_in_optional[8];            /* bytes 36 to 43 */
  uint8_t book_out_time_optional[8];      /* bytes 44 to 51 */
  uint8_t oeg_in_from_me_optional[8];     /* bytes 52 to 59 */
  uint8_t oeg_out_to_member_optional[8];  /* bytes 60 to 67 */
  uint8_t security_req_id[8];             /* bytes 68 to 75 */
  uint8_t symbol_index[4];                /* bytes 76 to 79 */
} SecurityDefinitionAckMessage;

/* any Security Definition Ack Message at all: every byte one the checker chooses */
static void any_security_definition_ack_message(SecurityDefinitionAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_member[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_time_to_me[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_in_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
}

/* Security Definition Ack Message to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_ack_message(const SecurityDefinitionAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_in_from_member[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_time_to_me[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_in_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->book_out_time_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_in_from_me_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_req_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }

  return at;
}

/* Security Definition Ack Message off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_ack_message(SecurityDefinitionAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_member[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_time_to_me[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_in_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->book_out_time_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_in_from_me_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Ack Message is what was written, byte for byte */
static void equal_security_definition_ack_message(const SecurityDefinitionAckMessage *read, const SecurityDefinitionAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time_optional[i] == written->sending_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_in_from_member[i] == written->oeg_in_from_member[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_time_to_me[i] == written->oeg_out_time_to_me[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_in_optional[i] == written->book_in_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->book_out_time_optional[i] == written->book_out_time_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_in_from_me_optional[i] == written->oeg_in_from_me_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
}

/* Security Definition Ack Message: written and read back, then read and written back */
static void check_security_definition_ack_message(void) {
  SecurityDefinitionAckMessage sent;
  SecurityDefinitionAckMessage got;
  uint8_t wire[80];
  uint8_t again[80];

  any_security_definition_ack_message(&sent);
  assert(encode_security_definition_ack_message(&sent, wire, 0) == 80);
  assert(decode_security_definition_ack_message(&got, wire, 0) == 80);
  equal_security_definition_ack_message(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_ack_message(&got, wire, 0) == 80);
  assert(encode_security_definition_ack_message(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 19 bytes ------------------------------------------------- */

/* LogonMessage */
typedef struct {
  uint8_t logical_access_id[4];          /* bytes 0 to 3 */
  uint8_t oe_partition_id[2];            /* bytes 4 to 5 */
  uint8_t last_msg_seq_num_optional[4];  /* bytes 6 to 9 */
  uint8_t software_provider[8];          /* bytes 10 to 17 */
  uint8_t queueing_indicator;            /* byte 18 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->logical_access_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->software_provider[i] = arbitrary(); }
  record->queueing_indicator = arbitrary();
}

/* Logon Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->logical_access_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->oe_partition_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->software_provider[i]; }
  wire[at++] = record->queueing_indicator;

  return at;
}

/* Logon Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->logical_access_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->oe_partition_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->software_provider[i] = wire[at++]; }
  record->queueing_indicator = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->logical_access_id[i] == written->logical_access_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->oe_partition_id[i] == written->oe_partition_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num_optional[i] == written->last_msg_seq_num_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->software_provider[i] == written->software_provider[i]); }
  assert(read->queueing_indicator == written->queueing_indicator);
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 19);
  assert(decode_logon_message(&got, wire, 0) == 19);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 19);
  assert(encode_logon_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Ack Message: 12 bytes --------------------------------------------- */

/* LogonAckMessage */
typedef struct {
  uint8_t exchange_id[8];          /* bytes 0 to 7 */
  uint8_t last_cl_msg_seq_num[4];  /* bytes 8 to 11 */
} LogonAckMessage;

/* any Logon Ack Message at all: every byte one the checker chooses */
static void any_logon_ack_message(LogonAckMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->exchange_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_cl_msg_seq_num[i] = arbitrary(); }
}

/* Logon Ack Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_logon_ack_message(const LogonAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_cl_msg_seq_num[i]; }

  return at;
}

/* Logon Ack Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_logon_ack_message(LogonAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->exchange_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_cl_msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Ack Message is what was written, byte for byte */
static void equal_logon_ack_message(const LogonAckMessage *read, const LogonAckMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_cl_msg_seq_num[i] == written->last_cl_msg_seq_num[i]); }
}

/* Logon Ack Message: written and read back, then read and written back */
static void check_logon_ack_message(void) {
  LogonAckMessage sent;
  LogonAckMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_logon_ack_message(&sent);
  assert(encode_logon_ack_message(&sent, wire, 0) == 12);
  assert(decode_logon_ack_message(&got, wire, 0) == 12);
  equal_logon_ack_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_ack_message(&got, wire, 0) == 12);
  assert(encode_logon_ack_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Reject Message: 17 bytes ------------------------------------------ */

/* LogonRejectMessage */
typedef struct {
  uint8_t exchange_id[8];          /* bytes 0 to 7 */
  uint8_t logon_reject_code;       /* byte 8 */
  uint8_t last_cl_msg_seq_num[4];  /* bytes 9 to 12 */
  uint8_t last_msg_seq_num[4];     /* bytes 13 to 16 */
} LogonRejectMessage;

/* any Logon Reject Message at all: every byte one the checker chooses */
static void any_logon_reject_message(LogonRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->exchange_id[i] = arbitrary(); }
  record->logon_reject_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num[i] = arbitrary(); }
}

/* Logon Reject Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_logon_reject_message(const LogonRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exchange_id[i]; }
  wire[at++] = record->logon_reject_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num[i]; }

  return at;
}

/* Logon Reject Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_logon_reject_message(LogonRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->exchange_id[i] = wire[at++]; }
  record->logon_reject_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Reject Message is what was written, byte for byte */
static void equal_logon_reject_message(const LogonRejectMessage *read, const LogonRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->exchange_id[i] == written->exchange_id[i]); }
  assert(read->logon_reject_code == written->logon_reject_code);
  for (size_t i = 0; i < 4; i++) { assert(read->last_cl_msg_seq_num[i] == written->last_cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num[i] == written->last_msg_seq_num[i]); }
}

/* Logon Reject Message: written and read back, then read and written back */
static void check_logon_reject_message(void) {
  LogonRejectMessage sent;
  LogonRejectMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_logon_reject_message(&sent);
  assert(encode_logon_reject_message(&sent, wire, 0) == 17);
  assert(decode_logon_reject_message(&got, wire, 0) == 17);
  equal_logon_reject_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_reject_message(&got, wire, 0) == 17);
  assert(encode_logon_reject_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 1 byte -------------------------------------------------- */

/* LogoutMessage */
typedef struct {
  uint8_t log_out_reason_code;  /* byte 0 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  record->log_out_reason_code = arbitrary();
}

/* Logout Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->log_out_reason_code;

  return at;
}

/* Logout Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  record->log_out_reason_code = wire[at++];

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  assert(read->log_out_reason_code == written->log_out_reason_code);
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 1);
  assert(decode_logout_message(&got, wire, 0) == 1);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 1);
  assert(encode_logout_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Technical Reject Message: 17 bytes -------------------------------------- */

/* TechnicalRejectMessage */
typedef struct {
  uint8_t oeg_out_to_member_optional[8];               /* bytes 0 to 7 */
  uint8_t rejected_client_message_sequence_number[4];  /* bytes 8 to 11 */
  uint8_t rejected_message;                            /* byte 12 */
  uint8_t error_code[2];                               /* bytes 13 to 14 */
  uint8_t rejected_message_id[2];                      /* bytes 15 to 16 */
} TechnicalRejectMessage;

/* any Technical Reject Message at all: every byte one the checker chooses */
static void any_technical_reject_message(TechnicalRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rejected_client_message_sequence_number[i] = arbitrary(); }
  record->rejected_message = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->rejected_message_id[i] = arbitrary(); }
}

/* Technical Reject Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_technical_reject_message(const TechnicalRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->oeg_out_to_member_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rejected_client_message_sequence_number[i]; }
  wire[at++] = record->rejected_message;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rejected_message_id[i]; }

  return at;
}

/* Technical Reject Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_technical_reject_message(TechnicalRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->oeg_out_to_member_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rejected_client_message_sequence_number[i] = wire[at++]; }
  record->rejected_message = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->rejected_message_id[i] = wire[at++]; }

  return at;
}

/* what was read of Technical Reject Message is what was written, byte for byte */
static void equal_technical_reject_message(const TechnicalRejectMessage *read, const TechnicalRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->oeg_out_to_member_optional[i] == written->oeg_out_to_member_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rejected_client_message_sequence_number[i] == written->rejected_client_message_sequence_number[i]); }
  assert(read->rejected_message == written->rejected_message);
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->rejected_message_id[i] == written->rejected_message_id[i]); }
}

/* Technical Reject Message: written and read back, then read and written back */
static void check_technical_reject_message(void) {
  TechnicalRejectMessage sent;
  TechnicalRejectMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_technical_reject_message(&sent);
  assert(encode_technical_reject_message(&sent, wire, 0) == 17);
  assert(decode_technical_reject_message(&got, wire, 0) == 17);
  equal_technical_reject_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_technical_reject_message(&got, wire, 0) == 17);
  assert(encode_technical_reject_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Declaration Cancel And Refusal Message: 42 bytes ------------------------ */

/* DeclarationCancelAndRefusalMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];   /* bytes 0 to 3 */
  uint8_t firm_id[8];          /* bytes 4 to 11 */
  uint8_t sending_time[8];     /* bytes 12 to 19 */
  uint8_t client_order_id[8];  /* bytes 20 to 27 */
  uint8_t symbol_index[4];     /* bytes 28 to 31 */
  uint8_t emm;                 /* byte 32 */
  uint8_t declaration_id[8];   /* bytes 33 to 40 */
  uint8_t action_type;         /* byte 41 */
} DeclarationCancelAndRefusalMessage;

/* any Declaration Cancel And Refusal Message at all: every byte one the checker chooses */
static void any_declaration_cancel_and_refusal_message(DeclarationCancelAndRefusalMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = arbitrary(); }
  record->action_type = arbitrary();
}

/* Declaration Cancel And Refusal Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_declaration_cancel_and_refusal_message(const DeclarationCancelAndRefusalMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->declaration_id[i]; }
  wire[at++] = record->action_type;

  return at;
}

/* Declaration Cancel And Refusal Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_declaration_cancel_and_refusal_message(DeclarationCancelAndRefusalMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->declaration_id[i] = wire[at++]; }
  record->action_type = wire[at++];

  return at;
}

/* what was read of Declaration Cancel And Refusal Message is what was written, byte for byte */
static void equal_declaration_cancel_and_refusal_message(const DeclarationCancelAndRefusalMessage *read, const DeclarationCancelAndRefusalMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->declaration_id[i] == written->declaration_id[i]); }
  assert(read->action_type == written->action_type);
}

/* Declaration Cancel And Refusal Message: written and read back, then read and written back */
static void check_declaration_cancel_and_refusal_message(void) {
  DeclarationCancelAndRefusalMessage sent;
  DeclarationCancelAndRefusalMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_declaration_cancel_and_refusal_message(&sent);
  assert(encode_declaration_cancel_and_refusal_message(&sent, wire, 0) == 42);
  assert(decode_declaration_cancel_and_refusal_message(&got, wire, 0) == 42);
  equal_declaration_cancel_and_refusal_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_declaration_cancel_and_refusal_message(&got, wire, 0) == 42);
  assert(encode_declaration_cancel_and_refusal_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fund Price Input Message: 42 bytes -------------------------------------- */

/* FundPriceInputMessage */
typedef struct {
  uint8_t cl_msg_seq_num[4];   /* bytes 0 to 3 */
  uint8_t firm_id[8];          /* bytes 4 to 11 */
  uint8_t sending_time[8];     /* bytes 12 to 19 */
  uint8_t client_order_id[8];  /* bytes 20 to 27 */
  uint8_t symbol_index[4];     /* bytes 28 to 31 */
  uint8_t emm;                 /* byte 32 */
  uint8_t price[8];            /* bytes 33 to 40 */
  uint8_t bypass_indicator;    /* byte 41 */
} FundPriceInputMessage;

/* any Fund Price Input Message at all: every byte one the checker chooses */
static void any_fund_price_input_message(FundPriceInputMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->bypass_indicator = arbitrary();
}

/* Fund Price Input Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_fund_price_input_message(const FundPriceInputMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cl_msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->bypass_indicator;

  return at;
}

/* Fund Price Input Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_fund_price_input_message(FundPriceInputMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->cl_msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->bypass_indicator = wire[at++];

  return at;
}

/* what was read of Fund Price Input Message is what was written, byte for byte */
static void equal_fund_price_input_message(const FundPriceInputMessage *read, const FundPriceInputMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->cl_msg_seq_num[i] == written->cl_msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->bypass_indicator == written->bypass_indicator);
}

/* Fund Price Input Message: written and read back, then read and written back */
static void check_fund_price_input_message(void) {
  FundPriceInputMessage sent;
  FundPriceInputMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_fund_price_input_message(&sent);
  assert(encode_fund_price_input_message(&sent, wire, 0) == 42);
  assert(decode_fund_price_input_message(&got, wire, 0) == 42);
  equal_fund_price_input_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_fund_price_input_message(&got, wire, 0) == 42);
  assert(encode_fund_price_input_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Fund Price Input Ack Message: 34 bytes ---------------------------------- */

/* FundPriceInputAckMessage */
typedef struct {
  uint8_t msg_seq_num[4];      /* bytes 0 to 3 */
  uint8_t firm_id[8];          /* bytes 4 to 11 */
  uint8_t client_order_id[8];  /* bytes 12 to 19 */
  uint8_t symbol_index[4];     /* bytes 20 to 23 */
  uint8_t emm;                 /* byte 24 */
  uint8_t price[8];            /* bytes 25 to 32 */
  uint8_t bypass_indicator;    /* byte 33 */
} FundPriceInputAckMessage;

/* any Fund Price Input Ack Message at all: every byte one the checker chooses */
static void any_fund_price_input_ack_message(FundPriceInputAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = arbitrary(); }
  record->emm = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->bypass_indicator = arbitrary();
}

/* Fund Price Input Ack Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_fund_price_input_ack_message(const FundPriceInputAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->firm_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_index[i]; }
  wire[at++] = record->emm;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->bypass_indicator;

  return at;
}

/* Fund Price Input Ack Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_fund_price_input_ack_message(FundPriceInputAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->firm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_index[i] = wire[at++]; }
  record->emm = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->bypass_indicator = wire[at++];

  return at;
}

/* what was read of Fund Price Input Ack Message is what was written, byte for byte */
static void equal_fund_price_input_ack_message(const FundPriceInputAckMessage *read, const FundPriceInputAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->firm_id[i] == written->firm_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_index[i] == written->symbol_index[i]); }
  assert(read->emm == written->emm);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->bypass_indicator == written->bypass_indicator);
}

/* Fund Price Input Ack Message: written and read back, then read and written back */
static void check_fund_price_input_ack_message(void) {
  FundPriceInputAckMessage sent;
  FundPriceInputAckMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_fund_price_input_ack_message(&sent);
  assert(encode_fund_price_input_ack_message(&sent, wire, 0) == 34);
  assert(decode_fund_price_input_ack_message(&got, wire, 0) == 34);
  equal_fund_price_input_ack_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_fund_price_input_ack_message(&got, wire, 0) == 34);
  assert(encode_fund_price_input_ack_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_frame_header();
  check_message_header();
  check_group_size_encoding();
  check_open_order_request_message();
  check_ownership_request_ack_message();
  check_ownership_request_message();
  check_trade_bust_notification_message();
  check_collar_breach_confirmation_message();
  check_price_input_message();
  check_liquidity_provider_command_message();
  check_ask_for_quote_message();
  check_request_for_execution_message();
  check_rfq_matching_status_message();
  check_rfqlp_matching_status_message();
  check_synchronization_time_message();
  check_security_definition_ack_message();
  check_logon_message();
  check_logon_ack_message();
  check_logon_reject_message();
  check_logout_message();
  check_technical_reject_message();
  check_declaration_cancel_and_refusal_message();
  check_fund_price_input_message();
  check_fund_price_input_ack_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
