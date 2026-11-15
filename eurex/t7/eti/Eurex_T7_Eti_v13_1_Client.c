// eurex/t7/eti/Eurex_T7_Eti_v13_1_Client.c
/*
 * Eurex Exchange Enhanced Trading Interface
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

/* Eurex T7 Eti message header */
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

/* ---- Request Header Comp: 8 bytes -------------------------------------------- */

typedef struct {
  uint8_t msg_seq_num[4];    /* bytes 0 to 3 */
  uint8_t sender_sub_id[4];  /* bytes 4 to 7 */
} RequestHeaderComp;

/* any Request Header Comp at all: every byte one the checker chooses */
static void any_request_header_comp(RequestHeaderComp *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sender_sub_id[i] = arbitrary(); }
}

/* Request Header Comp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_request_header_comp(const RequestHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sender_sub_id[i]; }

  return at;
}

/* Request Header Comp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_request_header_comp(RequestHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sender_sub_id[i] = wire[at++]; }

  return at;
}

/* what was read of Request Header Comp is what was written, byte for byte */
static void equal_request_header_comp(const RequestHeaderComp *read, const RequestHeaderComp *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sender_sub_id[i] == written->sender_sub_id[i]); }
}

/* Request Header Comp: written and read back, then read and written back */
static void check_request_header_comp(void) {
  RequestHeaderComp sent;
  RequestHeaderComp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_request_header_comp(&sent);
  assert(encode_request_header_comp(&sent, wire, 0) == 8);
  assert(decode_request_header_comp(&got, wire, 0) == 8);
  equal_request_header_comp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_request_header_comp(&got, wire, 0) == 8);
  assert(encode_request_header_comp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Old Basket Data Grp Comp: 64 bytes -------------------------------------- */

typedef struct {
  uint8_t basket_trd_match_id[8];        /* bytes 0 to 7 */
  uint8_t basket_exec_id[4];             /* bytes 8 to 11 */
  uint8_t trade_report_id[20];           /* bytes 12 to 31 */
  uint8_t maturity_month_year[4];        /* bytes 32 to 35 */
  uint8_t basket_trade_report_type;      /* byte 36 */
  uint8_t basket_trade_report_text[20];  /* bytes 37 to 56 */
  uint8_t pad7[7];                       /* bytes 57 to 63 */
} OldBasketDataGrpComp;

/* any Old Basket Data Grp Comp at all: every byte one the checker chooses */
static void any_old_basket_data_grp_comp(OldBasketDataGrpComp *record) {
  for (size_t i = 0; i < 8; i++) { record->basket_trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->basket_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->trade_report_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->basket_trade_report_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->basket_trade_report_text[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = arbitrary(); }
}

/* Old Basket Data Grp Comp to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_old_basket_data_grp_comp(const OldBasketDataGrpComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->basket_trd_match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->basket_exec_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->trade_report_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->basket_trade_report_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->basket_trade_report_text[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pad7[i]; }

  return at;
}

/* Old Basket Data Grp Comp off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_old_basket_data_grp_comp(OldBasketDataGrpComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->basket_trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->basket_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->trade_report_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->basket_trade_report_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->basket_trade_report_text[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = wire[at++]; }

  return at;
}

/* what was read of Old Basket Data Grp Comp is what was written, byte for byte */
static void equal_old_basket_data_grp_comp(const OldBasketDataGrpComp *read, const OldBasketDataGrpComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->basket_trd_match_id[i] == written->basket_trd_match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->basket_exec_id[i] == written->basket_exec_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->basket_trade_report_type == written->basket_trade_report_type);
  for (size_t i = 0; i < 20; i++) { assert(read->basket_trade_report_text[i] == written->basket_trade_report_text[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->pad7[i] == written->pad7[i]); }
}

/* Old Basket Data Grp Comp: written and read back, then read and written back */
static void check_old_basket_data_grp_comp(void) {
  OldBasketDataGrpComp sent;
  OldBasketDataGrpComp got;
  uint8_t wire[64];
  uint8_t again[64];

  any_old_basket_data_grp_comp(&sent);
  assert(encode_old_basket_data_grp_comp(&sent, wire, 0) == 64);
  assert(decode_old_basket_data_grp_comp(&got, wire, 0) == 64);
  equal_old_basket_data_grp_comp(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_old_basket_data_grp_comp(&got, wire, 0) == 64);
  assert(encode_old_basket_data_grp_comp(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Basket Data Grp Comp: 48 bytes -------------------------------------- */

typedef struct {
  uint8_t trade_report_id[20];           /* bytes 0 to 19 */
  uint8_t maturity_month_year[4];        /* bytes 20 to 23 */
  uint8_t basket_trade_report_type;      /* byte 24 */
  uint8_t basket_trade_report_text[20];  /* bytes 25 to 44 */
  uint8_t pad3[3];                       /* bytes 45 to 47 */
} NewBasketDataGrpComp;

/* any New Basket Data Grp Comp at all: every byte one the checker chooses */
static void any_new_basket_data_grp_comp(NewBasketDataGrpComp *record) {
  for (size_t i = 0; i < 20; i++) { record->trade_report_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->basket_trade_report_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->basket_trade_report_text[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = arbitrary(); }
}

/* New Basket Data Grp Comp to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_new_basket_data_grp_comp(const NewBasketDataGrpComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->trade_report_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->basket_trade_report_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->basket_trade_report_text[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->pad3[i]; }

  return at;
}

/* New Basket Data Grp Comp off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_new_basket_data_grp_comp(NewBasketDataGrpComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->trade_report_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->basket_trade_report_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->basket_trade_report_text[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = wire[at++]; }

  return at;
}

/* what was read of New Basket Data Grp Comp is what was written, byte for byte */
static void equal_new_basket_data_grp_comp(const NewBasketDataGrpComp *read, const NewBasketDataGrpComp *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->basket_trade_report_type == written->basket_trade_report_type);
  for (size_t i = 0; i < 20; i++) { assert(read->basket_trade_report_text[i] == written->basket_trade_report_text[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->pad3[i] == written->pad3[i]); }
}

/* New Basket Data Grp Comp: written and read back, then read and written back */
static void check_new_basket_data_grp_comp(void) {
  NewBasketDataGrpComp sent;
  NewBasketDataGrpComp got;
  uint8_t wire[48];
  uint8_t again[48];

  any_new_basket_data_grp_comp(&sent);
  assert(encode_new_basket_data_grp_comp(&sent, wire, 0) == 48);
  assert(decode_new_basket_data_grp_comp(&got, wire, 0) == 48);
  equal_new_basket_data_grp_comp(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_new_basket_data_grp_comp(&got, wire, 0) == 48);
  assert(encode_new_basket_data_grp_comp(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_request_header_comp();
  check_old_basket_data_grp_comp();
  check_new_basket_data_grp_comp();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
