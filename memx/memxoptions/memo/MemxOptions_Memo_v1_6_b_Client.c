// memx/memxoptions/memo/MemxOptions_Memo_v1_6_b_Client.c
/*
 * The Members Exchange Members Orders
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Common Header: 3 bytes -------------------------------------------------- */

/* Tcp Common Header */
typedef struct {
  uint8_t message_type;       /* byte 0 */
  uint8_t message_length[2];  /* bytes 1 to 2 */
} CommonHeader;

/* any Common Header at all: every byte one the checker chooses */
static void any_common_header(CommonHeader *record) {
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Common Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_common_header(const CommonHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Common Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_common_header(CommonHeader *record, const uint8_t *wire, size_t at) {
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Common Header is what was written, byte for byte */
static void equal_common_header(const CommonHeader *read, const CommonHeader *written) {
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Common Header: written and read back, then read and written back */
static void check_common_header(void) {
  CommonHeader sent;
  CommonHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_common_header(&sent);
  assert(encode_common_header(&sent, wire, 0) == 3);
  assert(decode_common_header(&got, wire, 0) == 3);
  equal_common_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_common_header(&got, wire, 0) == 3);
  assert(encode_common_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request Message: 2 bytes ------------------------------------------ */

/* Memx Tcp Login message */
typedef struct {
  uint8_t token_type;  /* byte 0 */
  uint8_t token;       /* byte 1 */
} LoginRequestMessage;

/* any Login Request Message at all: every byte one the checker chooses */
static void any_login_request_message(LoginRequestMessage *record) {
  record->token_type = arbitrary();
  record->token = arbitrary();
}

/* Login Request Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_request_message(const LoginRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->token_type;
  wire[at++] = record->token;

  return at;
}

/* Login Request Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_request_message(LoginRequestMessage *record, const uint8_t *wire, size_t at) {
  record->token_type = wire[at++];
  record->token = wire[at++];

  return at;
}

/* what was read of Login Request Message is what was written, byte for byte */
static void equal_login_request_message(const LoginRequestMessage *read, const LoginRequestMessage *written) {
  assert(read->token_type == written->token_type);
  assert(read->token == written->token);
}

/* Login Request Message: written and read back, then read and written back */
static void check_login_request_message(void) {
  LoginRequestMessage sent;
  LoginRequestMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_request_message(&sent);
  assert(encode_login_request_message(&sent, wire, 0) == 2);
  assert(decode_login_request_message(&got, wire, 0) == 2);
  equal_login_request_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request_message(&got, wire, 0) == 2);
  assert(encode_login_request_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay Request Message: 20 bytes ---------------------------------------- */

/* Memx Tcp Replay Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
  uint8_t count[4];                 /* bytes 16 to 19 */
} ReplayRequestMessage;

/* any Replay Request Message at all: every byte one the checker chooses */
static void any_replay_request_message(ReplayRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->count[i] = arbitrary(); }
}

/* Replay Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_replay_request_message(const ReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->count[i]; }

  return at;
}

/* Replay Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_replay_request_message(ReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->count[i] = wire[at++]; }

  return at;
}

/* what was read of Replay Request Message is what was written, byte for byte */
static void equal_replay_request_message(const ReplayRequestMessage *read, const ReplayRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->count[i] == written->count[i]); }
}

/* Replay Request Message: written and read back, then read and written back */
static void check_replay_request_message(void) {
  ReplayRequestMessage sent;
  ReplayRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_replay_request_message(&sent);
  assert(encode_replay_request_message(&sent, wire, 0) == 20);
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  equal_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_request_message(&got, wire, 0) == 20);
  assert(encode_replay_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Replay All Request Message: 8 bytes ------------------------------------- */

/* Memx Tcp Replay All Request message */
typedef struct {
  uint8_t session_id[8];  /* bytes 0 to 7 */
} ReplayAllRequestMessage;

/* any Replay All Request Message at all: every byte one the checker chooses */
static void any_replay_all_request_message(ReplayAllRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
}

/* Replay All Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_replay_all_request_message(const ReplayAllRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Replay All Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_replay_all_request_message(ReplayAllRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Replay All Request Message is what was written, byte for byte */
static void equal_replay_all_request_message(const ReplayAllRequestMessage *read, const ReplayAllRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Replay All Request Message: written and read back, then read and written back */
static void check_replay_all_request_message(void) {
  ReplayAllRequestMessage sent;
  ReplayAllRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_replay_all_request_message(&sent);
  assert(encode_replay_all_request_message(&sent, wire, 0) == 8);
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  equal_replay_all_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_replay_all_request_message(&got, wire, 0) == 8);
  assert(encode_replay_all_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stream Request Message: 16 bytes ---------------------------------------- */

/* Memx Tcp Stream Request message */
typedef struct {
  uint8_t session_id[8];            /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];  /* bytes 8 to 15 */
} StreamRequestMessage;

/* any Stream Request Message at all: every byte one the checker chooses */
static void any_stream_request_message(StreamRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
}

/* Stream Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_stream_request_message(const StreamRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }

  return at;
}

/* Stream Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_stream_request_message(StreamRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Stream Request Message is what was written, byte for byte */
static void equal_stream_request_message(const StreamRequestMessage *read, const StreamRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
}

/* Stream Request Message: written and read back, then read and written back */
static void check_stream_request_message(void) {
  StreamRequestMessage sent;
  StreamRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_stream_request_message(&sent);
  assert(encode_stream_request_message(&sent, wire, 0) == 16);
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  equal_stream_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_stream_request_message(&got, wire, 0) == 16);
  assert(encode_stream_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sbe Header: 7 bytes ----------------------------------------------------- */

/* Sbe Header */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t template_id;      /* byte 2 */
  uint8_t schema_id;        /* byte 3 */
  uint8_t version[2];       /* bytes 4 to 5 */
  uint8_t num_groups;       /* byte 6 */
} SbeHeader;

/* any Sbe Header at all: every byte one the checker chooses */
static void any_sbe_header(SbeHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  record->template_id = arbitrary();
  record->schema_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
  record->num_groups = arbitrary();
}

/* Sbe Header to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_sbe_header(const SbeHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  wire[at++] = record->template_id;
  wire[at++] = record->schema_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }
  wire[at++] = record->num_groups;

  return at;
}

/* Sbe Header off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_sbe_header(SbeHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  record->template_id = wire[at++];
  record->schema_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }
  record->num_groups = wire[at++];

  return at;
}

/* what was read of Sbe Header is what was written, byte for byte */
static void equal_sbe_header(const SbeHeader *read, const SbeHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  assert(read->template_id == written->template_id);
  assert(read->schema_id == written->schema_id);
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
  assert(read->num_groups == written->num_groups);
}

/* Sbe Header: written and read back, then read and written back */
static void check_sbe_header(void) {
  SbeHeader sent;
  SbeHeader got;
  uint8_t wire[7];
  uint8_t again[7];

  any_sbe_header(&sent);
  assert(encode_sbe_header(&sent, wire, 0) == 7);
  assert(decode_sbe_header(&got, wire, 0) == 7);
  equal_sbe_header(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_sbe_header(&got, wire, 0) == 7);
  assert(encode_sbe_header(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Repeating Group Dimensions: 2 bytes ------------------------------------- */

/* RepeatingGroupDimensions */
typedef struct {
  uint8_t block_length_short;  /* byte 0 */
  uint8_t num_in_group;        /* byte 1 */
} RepeatingGroupDimensions;

/* any Repeating Group Dimensions at all: every byte one the checker chooses */
static void any_repeating_group_dimensions(RepeatingGroupDimensions *record) {
  record->block_length_short = arbitrary();
  record->num_in_group = arbitrary();
}

/* Repeating Group Dimensions to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_repeating_group_dimensions(const RepeatingGroupDimensions *record, uint8_t *wire, size_t at) {
  wire[at++] = record->block_length_short;
  wire[at++] = record->num_in_group;

  return at;
}

/* Repeating Group Dimensions off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_repeating_group_dimensions(RepeatingGroupDimensions *record, const uint8_t *wire, size_t at) {
  record->block_length_short = wire[at++];
  record->num_in_group = wire[at++];

  return at;
}

/* what was read of Repeating Group Dimensions is what was written, byte for byte */
static void equal_repeating_group_dimensions(const RepeatingGroupDimensions *read, const RepeatingGroupDimensions *written) {
  assert(read->block_length_short == written->block_length_short);
  assert(read->num_in_group == written->num_in_group);
}

/* Repeating Group Dimensions: written and read back, then read and written back */
static void check_repeating_group_dimensions(void) {
  RepeatingGroupDimensions sent;
  RepeatingGroupDimensions got;
  uint8_t wire[2];
  uint8_t again[2];

  any_repeating_group_dimensions(&sent);
  assert(encode_repeating_group_dimensions(&sent, wire, 0) == 2);
  assert(decode_repeating_group_dimensions(&got, wire, 0) == 2);
  equal_repeating_group_dimensions(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_repeating_group_dimensions(&got, wire, 0) == 2);
  assert(encode_repeating_group_dimensions(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Replace Request Message: 79 bytes -------------------------- */

/* OrderCancelReplaceRequestMessage */
typedef struct {
  uint8_t sending_time[8];       /* bytes 0 to 7 */
  uint8_t order_id_optional[8];  /* bytes 8 to 15 */
  uint8_t cl_ord_id[20];         /* bytes 16 to 35 */
  uint8_t list_seq_no;           /* byte 36 */
  uint8_t orig_cl_ord_id[20];    /* bytes 37 to 56 */
  uint8_t security_id[8];        /* bytes 57 to 64 */
  uint8_t side;                  /* byte 65 */
  uint8_t order_qty[4];          /* bytes 66 to 69 */
  uint8_t ord_type;              /* byte 70 */
  uint8_t price_optional[8];     /* bytes 71 to 78 */
} OrderCancelReplaceRequestMessage;

/* any Order Cancel Replace Request Message at all: every byte one the checker chooses */
static void any_order_cancel_replace_request_message(OrderCancelReplaceRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
}

/* Order Cancel Replace Request Message to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_replace_request_message(const OrderCancelReplaceRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }

  return at;
}

/* Order Cancel Replace Request Message off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_replace_request_message(OrderCancelReplaceRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Replace Request Message is what was written, byte for byte */
static void equal_order_cancel_replace_request_message(const OrderCancelReplaceRequestMessage *read, const OrderCancelReplaceRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
}

/* Order Cancel Replace Request Message: written and read back, then read and written back */
static void check_order_cancel_replace_request_message(void) {
  OrderCancelReplaceRequestMessage sent;
  OrderCancelReplaceRequestMessage got;
  uint8_t wire[79];
  uint8_t again[79];

  any_order_cancel_replace_request_message(&sent);
  assert(encode_order_cancel_replace_request_message(&sent, wire, 0) == 79);
  assert(decode_order_cancel_replace_request_message(&got, wire, 0) == 79);
  equal_order_cancel_replace_request_message(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_replace_request_message(&got, wire, 0) == 79);
  assert(encode_order_cancel_replace_request_message(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Request Message: 66 bytes ---------------------------------- */

/* OrderCancelRequestMessage */
typedef struct {
  uint8_t sending_time[8];              /* bytes 0 to 7 */
  uint8_t order_id_optional[8];         /* bytes 8 to 15 */
  uint8_t cl_ord_id[20];                /* bytes 16 to 35 */
  uint8_t list_seq_no;                  /* byte 36 */
  uint8_t orig_cl_ord_id_optional[20];  /* bytes 37 to 56 */
  uint8_t security_id[8];               /* bytes 57 to 64 */
  uint8_t side_optional;                /* byte 65 */
} OrderCancelRequestMessage;

/* any Order Cancel Request Message at all: every byte one the checker chooses */
static void any_order_cancel_request_message(OrderCancelRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  record->list_seq_no = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->side_optional = arbitrary();
}

/* Order Cancel Request Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_request_message(const OrderCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id_optional[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  wire[at++] = record->list_seq_no;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->orig_cl_ord_id_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->side_optional;

  return at;
}

/* Order Cancel Request Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_request_message(OrderCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  record->list_seq_no = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->orig_cl_ord_id_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->side_optional = wire[at++];

  return at;
}

/* what was read of Order Cancel Request Message is what was written, byte for byte */
static void equal_order_cancel_request_message(const OrderCancelRequestMessage *read, const OrderCancelRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id_optional[i] == written->order_id_optional[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  assert(read->list_seq_no == written->list_seq_no);
  for (size_t i = 0; i < 20; i++) { assert(read->orig_cl_ord_id_optional[i] == written->orig_cl_ord_id_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->side_optional == written->side_optional);
}

/* Order Cancel Request Message: written and read back, then read and written back */
static void check_order_cancel_request_message(void) {
  OrderCancelRequestMessage sent;
  OrderCancelRequestMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_order_cancel_request_message(&sent);
  assert(encode_order_cancel_request_message(&sent, wire, 0) == 66);
  assert(decode_order_cancel_request_message(&got, wire, 0) == 66);
  equal_order_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_request_message(&got, wire, 0) == 66);
  assert(encode_order_cancel_request_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Clear Lockout Request Message: 36 bytes --------------------- */

/* MassCancelClearLockoutRequestMessage */
typedef struct {
  uint8_t sending_time[8];  /* bytes 0 to 7 */
  uint8_t cl_ord_id[20];    /* bytes 8 to 27 */
  uint8_t lockout_id[8];    /* bytes 28 to 35 */
} MassCancelClearLockoutRequestMessage;

/* any Mass Cancel Clear Lockout Request Message at all: every byte one the checker chooses */
static void any_mass_cancel_clear_lockout_request_message(MassCancelClearLockoutRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = arbitrary(); }
}

/* Mass Cancel Clear Lockout Request Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_clear_lockout_request_message(const MassCancelClearLockoutRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->lockout_id[i]; }

  return at;
}

/* Mass Cancel Clear Lockout Request Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_clear_lockout_request_message(MassCancelClearLockoutRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->lockout_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Clear Lockout Request Message is what was written, byte for byte */
static void equal_mass_cancel_clear_lockout_request_message(const MassCancelClearLockoutRequestMessage *read, const MassCancelClearLockoutRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->lockout_id[i] == written->lockout_id[i]); }
}

/* Mass Cancel Clear Lockout Request Message: written and read back, then read and written back */
static void check_mass_cancel_clear_lockout_request_message(void) {
  MassCancelClearLockoutRequestMessage sent;
  MassCancelClearLockoutRequestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_mass_cancel_clear_lockout_request_message(&sent);
  assert(encode_mass_cancel_clear_lockout_request_message(&sent, wire, 0) == 36);
  assert(decode_mass_cancel_clear_lockout_request_message(&got, wire, 0) == 36);
  equal_mass_cancel_clear_lockout_request_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_clear_lockout_request_message(&got, wire, 0) == 36);
  assert(encode_mass_cancel_clear_lockout_request_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_common_header();
  check_login_request_message();
  check_replay_request_message();
  check_replay_all_request_message();
  check_stream_request_message();
  check_sbe_header();
  check_repeating_group_dimensions();
  check_order_cancel_replace_request_message();
  check_order_cancel_request_message();
  check_mass_cancel_clear_lockout_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
