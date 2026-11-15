// bse/bseindia/eti/BseIndia_Eti_v1_6_14_Server.c
/*
 * BSE Limited Enhanced Trading Interface
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
 *   - a length prefix framing what follows
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

/* ---- Message Header: 6 bytes ------------------------------------------------- */

/* Bse Eti message header */
typedef struct {
  uint8_t body_len[4];     /* bytes 0 to 3 */
  uint8_t template_id[2];  /* bytes 4 to 5 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->body_len[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
}

/* Message Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->body_len[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }

  return at;
}

/* Message Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->body_len[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->body_len[i] == written->body_len[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 6);
  assert(decode_message_header(&got, wire, 0) == 6);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 6);
  assert(encode_message_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Notif Header Comp: 8 bytes ---------------------------------------------- */

typedef struct {
  uint8_t sending_time[8];  /* bytes 0 to 7 */
} NotifHeaderComp;

/* any Notif Header Comp at all: every byte one the checker chooses */
static void any_notif_header_comp(NotifHeaderComp *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
}

/* Notif Header Comp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_notif_header_comp(const NotifHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }

  return at;
}

/* Notif Header Comp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_notif_header_comp(NotifHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }

  return at;
}

/* what was read of Notif Header Comp is what was written, byte for byte */
static void equal_notif_header_comp(const NotifHeaderComp *read, const NotifHeaderComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
}

/* Notif Header Comp: written and read back, then read and written back */
static void check_notif_header_comp(void) {
  NotifHeaderComp sent;
  NotifHeaderComp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_notif_header_comp(&sent);
  assert(encode_notif_header_comp(&sent, wire, 0) == 8);
  assert(decode_notif_header_comp(&got, wire, 0) == 8);
  equal_notif_header_comp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_notif_header_comp(&got, wire, 0) == 8);
  assert(encode_notif_header_comp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nr Response Header Me Comp: 56 bytes ------------------------------------ */

typedef struct {
  uint8_t request_time[8];         /* bytes 0 to 7 */
  uint8_t request_out[8];          /* bytes 8 to 15 */
  uint8_t trd_reg_ts_time_in[8];   /* bytes 16 to 23 */
  uint8_t trd_reg_ts_time_out[8];  /* bytes 24 to 31 */
  uint8_t response_in[8];          /* bytes 32 to 39 */
  uint8_t sending_time[8];         /* bytes 40 to 47 */
  uint8_t msg_seq_num[4];          /* bytes 48 to 51 */
  uint8_t last_fragment;           /* byte 52 */
  uint8_t pad3[3];                 /* bytes 53 to 55 */
} NrResponseHeaderMeComp;

/* any Nr Response Header Me Comp at all: every byte one the checker chooses */
static void any_nr_response_header_me_comp(NrResponseHeaderMeComp *record) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->response_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  record->last_fragment = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = arbitrary(); }
}

/* Nr Response Header Me Comp to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_nr_response_header_me_comp(const NrResponseHeaderMeComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->response_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  wire[at++] = record->last_fragment;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->pad3[i]; }

  return at;
}

/* Nr Response Header Me Comp off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_nr_response_header_me_comp(NrResponseHeaderMeComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->response_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  record->last_fragment = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = wire[at++]; }

  return at;
}

/* what was read of Nr Response Header Me Comp is what was written, byte for byte */
static void equal_nr_response_header_me_comp(const NrResponseHeaderMeComp *read, const NrResponseHeaderMeComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->request_time[i] == written->request_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_out[i] == written->request_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_out[i] == written->trd_reg_ts_time_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->response_in[i] == written->response_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  assert(read->last_fragment == written->last_fragment);
  for (size_t i = 0; i < 3; i++) { assert(read->pad3[i] == written->pad3[i]); }
}

/* Nr Response Header Me Comp: written and read back, then read and written back */
static void check_nr_response_header_me_comp(void) {
  NrResponseHeaderMeComp sent;
  NrResponseHeaderMeComp got;
  uint8_t wire[56];
  uint8_t again[56];

  any_nr_response_header_me_comp(&sent);
  assert(encode_nr_response_header_me_comp(&sent, wire, 0) == 56);
  assert(decode_nr_response_header_me_comp(&got, wire, 0) == 56);
  equal_nr_response_header_me_comp(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_nr_response_header_me_comp(&got, wire, 0) == 56);
  assert(encode_nr_response_header_me_comp(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rbc Header Me Comp: 48 bytes -------------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_out[8];  /* bytes 0 to 7 */
  uint8_t sending_time[8];         /* bytes 8 to 15 */
  uint8_t appl_sub_id[4];          /* bytes 16 to 19 */
  uint8_t partition_id[2];         /* bytes 20 to 21 */
  uint8_t appl_msg_id[16];         /* bytes 22 to 37 */
  uint8_t appl_id;                 /* byte 38 */
  uint8_t appl_resend_flag;        /* byte 39 */
  uint8_t last_fragment;           /* byte 40 */
  uint8_t pad7[7];                 /* bytes 41 to 47 */
} RbcHeaderMeComp;

/* any Rbc Header Me Comp at all: every byte one the checker chooses */
static void any_rbc_header_me_comp(RbcHeaderMeComp *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->appl_msg_id[i] = arbitrary(); }
  record->appl_id = arbitrary();
  record->appl_resend_flag = arbitrary();
  record->last_fragment = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = arbitrary(); }
}

/* Rbc Header Me Comp to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_rbc_header_me_comp(const RbcHeaderMeComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_sub_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->partition_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->appl_msg_id[i]; }
  wire[at++] = record->appl_id;
  wire[at++] = record->appl_resend_flag;
  wire[at++] = record->last_fragment;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pad7[i]; }

  return at;
}

/* Rbc Header Me Comp off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_rbc_header_me_comp(RbcHeaderMeComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->appl_msg_id[i] = wire[at++]; }
  record->appl_id = wire[at++];
  record->appl_resend_flag = wire[at++];
  record->last_fragment = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = wire[at++]; }

  return at;
}

/* what was read of Rbc Header Me Comp is what was written, byte for byte */
static void equal_rbc_header_me_comp(const RbcHeaderMeComp *read, const RbcHeaderMeComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_out[i] == written->trd_reg_ts_time_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->appl_sub_id[i] == written->appl_sub_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->appl_msg_id[i] == written->appl_msg_id[i]); }
  assert(read->appl_id == written->appl_id);
  assert(read->appl_resend_flag == written->appl_resend_flag);
  assert(read->last_fragment == written->last_fragment);
  for (size_t i = 0; i < 7; i++) { assert(read->pad7[i] == written->pad7[i]); }
}

/* Rbc Header Me Comp: written and read back, then read and written back */
static void check_rbc_header_me_comp(void) {
  RbcHeaderMeComp sent;
  RbcHeaderMeComp got;
  uint8_t wire[48];
  uint8_t again[48];

  any_rbc_header_me_comp(&sent);
  assert(encode_rbc_header_me_comp(&sent, wire, 0) == 48);
  assert(decode_rbc_header_me_comp(&got, wire, 0) == 48);
  equal_rbc_header_me_comp(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_rbc_header_me_comp(&got, wire, 0) == 48);
  assert(encode_rbc_header_me_comp(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Response Header Me Comp: 72 bytes --------------------------------------- */

typedef struct {
  uint8_t request_time[8];         /* bytes 0 to 7 */
  uint8_t request_out[8];          /* bytes 8 to 15 */
  uint8_t trd_reg_ts_time_in[8];   /* bytes 16 to 23 */
  uint8_t trd_reg_ts_time_out[8];  /* bytes 24 to 31 */
  uint8_t response_in[8];          /* bytes 32 to 39 */
  uint8_t sending_time[8];         /* bytes 40 to 47 */
  uint8_t msg_seq_num[4];          /* bytes 48 to 51 */
  uint8_t partition_id[2];         /* bytes 52 to 53 */
  uint8_t appl_id;                 /* byte 54 */
  uint8_t appl_msg_id[16];         /* bytes 55 to 70 */
  uint8_t last_fragment;           /* byte 71 */
} ResponseHeaderMeComp;

/* any Response Header Me Comp at all: every byte one the checker chooses */
static void any_response_header_me_comp(ResponseHeaderMeComp *record) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->response_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = arbitrary(); }
  record->appl_id = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->appl_msg_id[i] = arbitrary(); }
  record->last_fragment = arbitrary();
}

/* Response Header Me Comp to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_response_header_me_comp(const ResponseHeaderMeComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_out[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->response_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->partition_id[i]; }
  wire[at++] = record->appl_id;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->appl_msg_id[i]; }
  wire[at++] = record->last_fragment;

  return at;
}

/* Response Header Me Comp off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_response_header_me_comp(ResponseHeaderMeComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_out[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->response_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = wire[at++]; }
  record->appl_id = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->appl_msg_id[i] = wire[at++]; }
  record->last_fragment = wire[at++];

  return at;
}

/* what was read of Response Header Me Comp is what was written, byte for byte */
static void equal_response_header_me_comp(const ResponseHeaderMeComp *read, const ResponseHeaderMeComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->request_time[i] == written->request_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_out[i] == written->request_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_out[i] == written->trd_reg_ts_time_out[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->response_in[i] == written->response_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
  assert(read->appl_id == written->appl_id);
  for (size_t i = 0; i < 16; i++) { assert(read->appl_msg_id[i] == written->appl_msg_id[i]); }
  assert(read->last_fragment == written->last_fragment);
}

/* Response Header Me Comp: written and read back, then read and written back */
static void check_response_header_me_comp(void) {
  ResponseHeaderMeComp sent;
  ResponseHeaderMeComp got;
  uint8_t wire[72];
  uint8_t again[72];

  any_response_header_me_comp(&sent);
  assert(encode_response_header_me_comp(&sent, wire, 0) == 72);
  assert(decode_response_header_me_comp(&got, wire, 0) == 72);
  equal_response_header_me_comp(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_response_header_me_comp(&got, wire, 0) == 72);
  assert(encode_response_header_me_comp(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Response Header Comp: 24 bytes ------------------------------------------ */

typedef struct {
  uint8_t request_time[8];  /* bytes 0 to 7 */
  uint8_t sending_time[8];  /* bytes 8 to 15 */
  uint8_t msg_seq_num[4];   /* bytes 16 to 19 */
  uint8_t pad4[4];          /* bytes 20 to 23 */
} ResponseHeaderComp;

/* any Response Header Comp at all: every byte one the checker chooses */
static void any_response_header_comp(ResponseHeaderComp *record) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
}

/* Response Header Comp to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_response_header_comp(const ResponseHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }

  return at;
}

/* Response Header Comp off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_response_header_comp(ResponseHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }

  return at;
}

/* what was read of Response Header Comp is what was written, byte for byte */
static void equal_response_header_comp(const ResponseHeaderComp *read, const ResponseHeaderComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->request_time[i] == written->request_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
}

/* Response Header Comp: written and read back, then read and written back */
static void check_response_header_comp(void) {
  ResponseHeaderComp sent;
  ResponseHeaderComp got;
  uint8_t wire[24];
  uint8_t again[24];

  any_response_header_comp(&sent);
  assert(encode_response_header_comp(&sent, wire, 0) == 24);
  assert(decode_response_header_comp(&got, wire, 0) == 24);
  equal_response_header_comp(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_response_header_comp(&got, wire, 0) == 24);
  assert(encode_response_header_comp(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rbc Header Comp: 32 bytes ----------------------------------------------- */

typedef struct {
  uint8_t sending_time[8];   /* bytes 0 to 7 */
  uint8_t appl_seq_num[8];   /* bytes 8 to 15 */
  uint8_t appl_sub_id[4];    /* bytes 16 to 19 */
  uint8_t partition_id[2];   /* bytes 20 to 21 */
  uint8_t appl_resend_flag;  /* byte 22 */
  uint8_t appl_id;           /* byte 23 */
  uint8_t last_fragment;     /* byte 24 */
  uint8_t pad7[7];           /* bytes 25 to 31 */
} RbcHeaderComp;

/* any Rbc Header Comp at all: every byte one the checker chooses */
static void any_rbc_header_comp(RbcHeaderComp *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = arbitrary(); }
  record->appl_resend_flag = arbitrary();
  record->appl_id = arbitrary();
  record->last_fragment = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = arbitrary(); }
}

/* Rbc Header Comp to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_rbc_header_comp(const RbcHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_sub_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->partition_id[i]; }
  wire[at++] = record->appl_resend_flag;
  wire[at++] = record->appl_id;
  wire[at++] = record->last_fragment;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pad7[i]; }

  return at;
}

/* Rbc Header Comp off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_rbc_header_comp(RbcHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->partition_id[i] = wire[at++]; }
  record->appl_resend_flag = wire[at++];
  record->appl_id = wire[at++];
  record->last_fragment = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = wire[at++]; }

  return at;
}

/* what was read of Rbc Header Comp is what was written, byte for byte */
static void equal_rbc_header_comp(const RbcHeaderComp *read, const RbcHeaderComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->appl_sub_id[i] == written->appl_sub_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->partition_id[i] == written->partition_id[i]); }
  assert(read->appl_resend_flag == written->appl_resend_flag);
  assert(read->appl_id == written->appl_id);
  assert(read->last_fragment == written->last_fragment);
  for (size_t i = 0; i < 7; i++) { assert(read->pad7[i] == written->pad7[i]); }
}

/* Rbc Header Comp: written and read back, then read and written back */
static void check_rbc_header_comp(void) {
  RbcHeaderComp sent;
  RbcHeaderComp got;
  uint8_t wire[32];
  uint8_t again[32];

  any_rbc_header_comp(&sent);
  assert(encode_rbc_header_comp(&sent, wire, 0) == 32);
  assert(decode_rbc_header_comp(&got, wire, 0) == 32);
  equal_rbc_header_comp(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_rbc_header_comp(&got, wire, 0) == 32);
  assert(encode_rbc_header_comp(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nrbc Header Comp: 16 bytes ---------------------------------------------- */

typedef struct {
  uint8_t sending_time[8];  /* bytes 0 to 7 */
  uint8_t appl_sub_id[4];   /* bytes 8 to 11 */
  uint8_t appl_id;          /* byte 12 */
  uint8_t last_fragment;    /* byte 13 */
  uint8_t pad2[2];          /* bytes 14 to 15 */
} NrbcHeaderComp;

/* any Nrbc Header Comp at all: every byte one the checker chooses */
static void any_nrbc_header_comp(NrbcHeaderComp *record) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = arbitrary(); }
  record->appl_id = arbitrary();
  record->last_fragment = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->pad2[i] = arbitrary(); }
}

/* Nrbc Header Comp to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_nrbc_header_comp(const NrbcHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sending_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_sub_id[i]; }
  wire[at++] = record->appl_id;
  wire[at++] = record->last_fragment;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pad2[i]; }

  return at;
}

/* Nrbc Header Comp off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_nrbc_header_comp(NrbcHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sending_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->appl_sub_id[i] = wire[at++]; }
  record->appl_id = wire[at++];
  record->last_fragment = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->pad2[i] = wire[at++]; }

  return at;
}

/* what was read of Nrbc Header Comp is what was written, byte for byte */
static void equal_nrbc_header_comp(const NrbcHeaderComp *read, const NrbcHeaderComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sending_time[i] == written->sending_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->appl_sub_id[i] == written->appl_sub_id[i]); }
  assert(read->appl_id == written->appl_id);
  assert(read->last_fragment == written->last_fragment);
  for (size_t i = 0; i < 2; i++) { assert(read->pad2[i] == written->pad2[i]); }
}

/* Nrbc Header Comp: written and read back, then read and written back */
static void check_nrbc_header_comp(void) {
  NrbcHeaderComp sent;
  NrbcHeaderComp got;
  uint8_t wire[16];
  uint8_t again[16];

  any_nrbc_header_comp(&sent);
  assert(encode_nrbc_header_comp(&sent, wire, 0) == 16);
  assert(decode_nrbc_header_comp(&got, wire, 0) == 16);
  equal_nrbc_header_comp(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_nrbc_header_comp(&got, wire, 0) == 16);
  assert(encode_nrbc_header_comp(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_notif_header_comp();
  check_nr_response_header_me_comp();
  check_rbc_header_me_comp();
  check_response_header_me_comp();
  check_response_header_comp();
  check_rbc_header_comp();
  check_nrbc_header_comp();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
