// eurex/t7/eobi/Eurex_T7_Eobi_v3_0.c
/*
 * Eurex Exchange Enhanced Order Book Interface
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

/* ---- Eobi Header: 8 bytes ---------------------------------------------------- */

/* EOBI PacketHeader MessageHeaderComp (BodyLen + TemplateID + MsgSeqNum) — first 8 bytes of every Eurex T7 EOBI packet. */
typedef struct {
  uint8_t body_len[2];     /* bytes 0 to 1 */
  uint8_t template_id[2];  /* bytes 2 to 3 */
  uint8_t msg_seq_num[4];  /* bytes 4 to 7 */
} EobiHeader;

/* any Eobi Header at all: every byte one the checker chooses */
static void any_eobi_header(EobiHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->body_len[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
}

/* Eobi Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_eobi_header(const EobiHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->body_len[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }

  return at;
}

/* Eobi Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_eobi_header(EobiHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->body_len[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Eobi Header is what was written, byte for byte */
static void equal_eobi_header(const EobiHeader *read, const EobiHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->body_len[i] == written->body_len[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
}

/* Eobi Header: written and read back, then read and written back */
static void check_eobi_header(void) {
  EobiHeader sent;
  EobiHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_eobi_header(&sent);
  assert(encode_eobi_header(&sent, wire, 0) == 8);
  assert(decode_eobi_header(&got, wire, 0) == 8);
  equal_eobi_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_eobi_header(&got, wire, 0) == 8);
  assert(encode_eobi_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet Header: 32 bytes ------------------------------------------------- */

/* Eurex Eobi Packet Header */
typedef struct {
  EobiHeader eobi_header;            /* bytes 0 to 7 */
  uint8_t appl_seq_num[4];           /* bytes 8 to 11 */
  uint8_t market_segment_id[4];      /* bytes 12 to 15 */
  uint8_t partition_id;              /* byte 16 */
  uint8_t completion_indicator;      /* byte 17 */
  uint8_t appl_seq_reset_indicator;  /* byte 18 */
  uint8_t pad5[5];                   /* bytes 19 to 23 */
  uint8_t transact_time[8];          /* bytes 24 to 31 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  any_eobi_header(&record->eobi_header);
  for (size_t i = 0; i < 4; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->partition_id = arbitrary();
  record->completion_indicator = arbitrary();
  record->appl_seq_reset_indicator = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->pad5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Packet Header to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  at = encode_eobi_header(&record->eobi_header, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->partition_id;
  wire[at++] = record->completion_indicator;
  wire[at++] = record->appl_seq_reset_indicator;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->pad5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Packet Header off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  at = decode_eobi_header(&record->eobi_header, wire, at);
  for (size_t i = 0; i < 4; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->partition_id = wire[at++];
  record->completion_indicator = wire[at++];
  record->appl_seq_reset_indicator = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->pad5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  equal_eobi_header(&read->eobi_header, &written->eobi_header);
  for (size_t i = 0; i < 4; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->partition_id == written->partition_id);
  assert(read->completion_indicator == written->completion_indicator);
  assert(read->appl_seq_reset_indicator == written->appl_seq_reset_indicator);
  for (size_t i = 0; i < 5; i++) { assert(read->pad5[i] == written->pad5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[32];
  uint8_t again[32];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 32);
  assert(decode_packet_header(&got, wire, 0) == 32);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 32);
  assert(encode_packet_header(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header Comp: 8 bytes -------------------------------------------- */

typedef struct {
  uint8_t body_len[2];     /* bytes 0 to 1 */
  uint8_t template_id[2];  /* bytes 2 to 3 */
  uint8_t msg_seq_num[4];  /* bytes 4 to 7 */
} MessageHeaderComp;

/* any Message Header Comp at all: every byte one the checker chooses */
static void any_message_header_comp(MessageHeaderComp *record) {
  for (size_t i = 0; i < 2; i++) { record->body_len[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
}

/* Message Header Comp to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header_comp(const MessageHeaderComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->body_len[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->template_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }

  return at;
}

/* Message Header Comp off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header_comp(MessageHeaderComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->body_len[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->template_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header Comp is what was written, byte for byte */
static void equal_message_header_comp(const MessageHeaderComp *read, const MessageHeaderComp *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->body_len[i] == written->body_len[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->template_id[i] == written->template_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
}

/* Message Header Comp: written and read back, then read and written back */
static void check_message_header_comp(void) {
  MessageHeaderComp sent;
  MessageHeaderComp got;
  uint8_t wire[8];
  uint8_t again[8];

  any_message_header_comp(&sent);
  assert(encode_message_header_comp(&sent, wire, 0) == 8);
  assert(decode_message_header_comp(&got, wire, 0) == 8);
  equal_message_header_comp(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header_comp(&got, wire, 0) == 8);
  assert(encode_message_header_comp(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Bbo: 32 bytes --------------------------------------------------- */

typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t security_id[8];    /* bytes 8 to 15 */
  uint8_t bid_px[8];         /* bytes 16 to 23 */
  uint8_t offer_px[8];       /* bytes 24 to 31 */
} AuctionBbo;

/* any Auction Bbo at all: every byte one the checker chooses */
static void any_auction_bbo(AuctionBbo *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_px[i] = arbitrary(); }
}

/* Auction Bbo to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_bbo(const AuctionBbo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_px[i]; }

  return at;
}

/* Auction Bbo off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_bbo(AuctionBbo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_px[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Bbo is what was written, byte for byte */
static void equal_auction_bbo(const AuctionBbo *read, const AuctionBbo *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px[i] == written->bid_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_px[i] == written->offer_px[i]); }
}

/* Auction Bbo: written and read back, then read and written back */
static void check_auction_bbo(void) {
  AuctionBbo sent;
  AuctionBbo got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_bbo(&sent);
  assert(encode_auction_bbo(&sent, wire, 0) == 32);
  assert(decode_auction_bbo(&got, wire, 0) == 32);
  equal_auction_bbo(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_bbo(&got, wire, 0) == 32);
  assert(encode_auction_bbo(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Clearing Price: 24 bytes ---------------------------------------- */

typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t security_id[8];    /* bytes 8 to 15 */
  uint8_t last_px[8];        /* bytes 16 to 23 */
} AuctionClearingPrice;

/* any Auction Clearing Price at all: every byte one the checker chooses */
static void any_auction_clearing_price(AuctionClearingPrice *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
}

/* Auction Clearing Price to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_auction_clearing_price(const AuctionClearingPrice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }

  return at;
}

/* Auction Clearing Price off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_auction_clearing_price(AuctionClearingPrice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Clearing Price is what was written, byte for byte */
static void equal_auction_clearing_price(const AuctionClearingPrice *read, const AuctionClearingPrice *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
}

/* Auction Clearing Price: written and read back, then read and written back */
static void check_auction_clearing_price(void) {
  AuctionClearingPrice sent;
  AuctionClearingPrice got;
  uint8_t wire[24];
  uint8_t again[24];

  any_auction_clearing_price(&sent);
  assert(encode_auction_clearing_price(&sent, wire, 0) == 24);
  assert(decode_auction_clearing_price(&got, wire, 0) == 24);
  equal_auction_clearing_price(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_clearing_price(&got, wire, 0) == 24);
  assert(encode_auction_clearing_price(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cross Request: 24 bytes ------------------------------------------------- */

typedef struct {
  uint8_t security_id[8];    /* bytes 0 to 7 */
  uint8_t last_qty[4];       /* bytes 8 to 11 */
  uint8_t pad4[4];           /* bytes 12 to 15 */
  uint8_t transact_time[8];  /* bytes 16 to 23 */
} CrossRequest;

/* any Cross Request at all: every byte one the checker chooses */
static void any_cross_request(CrossRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Cross Request to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_cross_request(const CrossRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Cross Request off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_cross_request(CrossRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Cross Request is what was written, byte for byte */
static void equal_cross_request(const CrossRequest *read, const CrossRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Cross Request: written and read back, then read and written back */
static void check_cross_request(void) {
  CrossRequest sent;
  CrossRequest got;
  uint8_t wire[24];
  uint8_t again[24];

  any_cross_request(&sent);
  assert(encode_cross_request(&sent, wire, 0) == 24);
  assert(decode_cross_request(&got, wire, 0) == 24);
  equal_cross_request(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_cross_request(&got, wire, 0) == 24);
  assert(encode_cross_request(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Summary: 56 bytes --------------------------------------------- */

typedef struct {
  uint8_t security_id[8];          /* bytes 0 to 7 */
  uint8_t aggressor_timestamp[8];  /* bytes 8 to 15 */
  uint8_t request_time[8];         /* bytes 16 to 23 */
  uint8_t exec_id[8];              /* bytes 24 to 31 */
  uint8_t last_qty[4];             /* bytes 32 to 35 */
  uint8_t aggressor_side;          /* byte 36 */
  uint8_t trade_condition;         /* byte 37 */
  uint8_t pad2[2];                 /* bytes 38 to 39 */
  uint8_t last_px[8];              /* bytes 40 to 47 */
  uint8_t resting_hidden_qty[4];   /* bytes 48 to 51 */
  uint8_t resting_cxl_qty[4];      /* bytes 52 to 55 */
} ExecutionSummary;

/* any Execution Summary at all: every byte one the checker chooses */
static void any_execution_summary(ExecutionSummary *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->aggressor_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  record->aggressor_side = arbitrary();
  record->trade_condition = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->pad2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->resting_hidden_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->resting_cxl_qty[i] = arbitrary(); }
}

/* Execution Summary to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_execution_summary(const ExecutionSummary *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aggressor_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->request_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->aggressor_side;
  wire[at++] = record->trade_condition;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->pad2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->resting_hidden_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->resting_cxl_qty[i]; }

  return at;
}

/* Execution Summary off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_execution_summary(ExecutionSummary *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->aggressor_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->request_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  record->aggressor_side = wire[at++];
  record->trade_condition = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->pad2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->resting_hidden_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->resting_cxl_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Summary is what was written, byte for byte */
static void equal_execution_summary(const ExecutionSummary *read, const ExecutionSummary *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->aggressor_timestamp[i] == written->aggressor_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->request_time[i] == written->request_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->aggressor_side == written->aggressor_side);
  assert(read->trade_condition == written->trade_condition);
  for (size_t i = 0; i < 2; i++) { assert(read->pad2[i] == written->pad2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->resting_hidden_qty[i] == written->resting_hidden_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->resting_cxl_qty[i] == written->resting_cxl_qty[i]); }
}

/* Execution Summary: written and read back, then read and written back */
static void check_execution_summary(void) {
  ExecutionSummary sent;
  ExecutionSummary got;
  uint8_t wire[56];
  uint8_t again[56];

  any_execution_summary(&sent);
  assert(encode_execution_summary(&sent, wire, 0) == 56);
  assert(decode_execution_summary(&got, wire, 0) == 56);
  equal_execution_summary(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_summary(&got, wire, 0) == 56);
  assert(encode_execution_summary(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Full Order Execution: 48 bytes ------------------------------------------ */

typedef struct {
  uint8_t side;                         /* byte 0 */
  uint8_t pad7[7];                      /* bytes 1 to 7 */
  uint8_t price[8];                     /* bytes 8 to 15 */
  uint8_t trd_reg_ts_time_priority[8];  /* bytes 16 to 23 */
  uint8_t security_id[8];               /* bytes 24 to 31 */
  uint8_t trd_match_id[4];              /* bytes 32 to 35 */
  uint8_t last_qty[4];                  /* bytes 36 to 39 */
  uint8_t last_px[8];                   /* bytes 40 to 47 */
} FullOrderExecution;

/* any Full Order Execution at all: every byte one the checker chooses */
static void any_full_order_execution(FullOrderExecution *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
}

/* Full Order Execution to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_full_order_execution(const FullOrderExecution *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pad7[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }

  return at;
}

/* Full Order Execution off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_full_order_execution(FullOrderExecution *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }

  return at;
}

/* what was read of Full Order Execution is what was written, byte for byte */
static void equal_full_order_execution(const FullOrderExecution *read, const FullOrderExecution *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 7; i++) { assert(read->pad7[i] == written->pad7[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_priority[i] == written->trd_reg_ts_time_priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
}

/* Full Order Execution: written and read back, then read and written back */
static void check_full_order_execution(void) {
  FullOrderExecution sent;
  FullOrderExecution got;
  uint8_t wire[48];
  uint8_t again[48];

  any_full_order_execution(&sent);
  assert(encode_full_order_execution(&sent, wire, 0) == 48);
  assert(decode_full_order_execution(&got, wire, 0) == 48);
  equal_full_order_execution(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_full_order_execution(&got, wire, 0) == 48);
  assert(encode_full_order_execution(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat: 8 bytes ------------------------------------------------------ */

typedef struct {
  uint8_t last_msg_seq_num_processed[4];  /* bytes 0 to 3 */
  uint8_t pad4[4];                        /* bytes 4 to 7 */
} Heartbeat;

/* any Heartbeat at all: every byte one the checker chooses */
static void any_heartbeat(Heartbeat *record) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
}

/* Heartbeat to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat(const Heartbeat *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num_processed[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }

  return at;
}

/* Heartbeat off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat(Heartbeat *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat is what was written, byte for byte */
static void equal_heartbeat(const Heartbeat *read, const Heartbeat *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num_processed[i] == written->last_msg_seq_num_processed[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
}

/* Heartbeat: written and read back, then read and written back */
static void check_heartbeat(void) {
  Heartbeat sent;
  Heartbeat got;
  uint8_t wire[8];
  uint8_t again[8];

  any_heartbeat(&sent);
  assert(encode_heartbeat(&sent, wire, 0) == 8);
  assert(decode_heartbeat(&got, wire, 0) == 8);
  equal_heartbeat(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat(&got, wire, 0) == 8);
  assert(encode_heartbeat(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument State Change: 24 bytes --------------------------------------- */

typedef struct {
  uint8_t security_id[8];           /* bytes 0 to 7 */
  uint8_t security_status;          /* byte 8 */
  uint8_t security_trading_status;  /* byte 9 */
  uint8_t fast_market_indicator;    /* byte 10 */
  uint8_t pad5[5];                  /* bytes 11 to 15 */
  uint8_t transact_time[8];         /* bytes 16 to 23 */
} InstrumentStateChange;

/* any Instrument State Change at all: every byte one the checker chooses */
static void any_instrument_state_change(InstrumentStateChange *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  record->security_status = arbitrary();
  record->security_trading_status = arbitrary();
  record->fast_market_indicator = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->pad5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Instrument State Change to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_instrument_state_change(const InstrumentStateChange *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  wire[at++] = record->security_status;
  wire[at++] = record->security_trading_status;
  wire[at++] = record->fast_market_indicator;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->pad5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Instrument State Change off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_instrument_state_change(InstrumentStateChange *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  record->security_status = wire[at++];
  record->security_trading_status = wire[at++];
  record->fast_market_indicator = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->pad5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument State Change is what was written, byte for byte */
static void equal_instrument_state_change(const InstrumentStateChange *read, const InstrumentStateChange *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  assert(read->security_status == written->security_status);
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->fast_market_indicator == written->fast_market_indicator);
  for (size_t i = 0; i < 5; i++) { assert(read->pad5[i] == written->pad5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Instrument State Change: written and read back, then read and written back */
static void check_instrument_state_change(void) {
  InstrumentStateChange sent;
  InstrumentStateChange got;
  uint8_t wire[24];
  uint8_t again[24];

  any_instrument_state_change(&sent);
  assert(encode_instrument_state_change(&sent, wire, 0) == 24);
  assert(decode_instrument_state_change(&got, wire, 0) == 24);
  equal_instrument_state_change(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_state_change(&got, wire, 0) == 24);
  assert(encode_instrument_state_change(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Details Comp: 24 bytes -------------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_priority[8];  /* bytes 0 to 7 */
  uint8_t display_qty[4];               /* bytes 8 to 11 */
  uint8_t side;                         /* byte 12 */
  uint8_t pad3[3];                      /* bytes 13 to 15 */
  uint8_t price[8];                     /* bytes 16 to 23 */
} OrderDetailsComp;

/* any Order Details Comp at all: every byte one the checker chooses */
static void any_order_details_comp(OrderDetailsComp *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Order Details Comp to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_details_comp(const OrderDetailsComp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_priority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->pad3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Order Details Comp off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_details_comp(OrderDetailsComp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Details Comp is what was written, byte for byte */
static void equal_order_details_comp(const OrderDetailsComp *read, const OrderDetailsComp *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_priority[i] == written->trd_reg_ts_time_priority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 3; i++) { assert(read->pad3[i] == written->pad3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Order Details Comp: written and read back, then read and written back */
static void check_order_details_comp(void) {
  OrderDetailsComp sent;
  OrderDetailsComp got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_details_comp(&sent);
  assert(encode_order_details_comp(&sent, wire, 0) == 24);
  assert(decode_order_details_comp(&got, wire, 0) == 24);
  equal_order_details_comp(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_details_comp(&got, wire, 0) == 24);
  assert(encode_order_details_comp(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Add: 40 bytes ----------------------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_in[8];        /* bytes 0 to 7 */
  uint8_t security_id[8];               /* bytes 8 to 15 */
  OrderDetailsComp order_details_comp;  /* bytes 16 to 39 */
} OrderAdd;

/* any Order Add at all: every byte one the checker chooses */
static void any_order_add(OrderAdd *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  any_order_details_comp(&record->order_details_comp);
}

/* Order Add to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_order_add(const OrderAdd *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  at = encode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* Order Add off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_order_add(OrderAdd *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  at = decode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* what was read of Order Add is what was written, byte for byte */
static void equal_order_add(const OrderAdd *read, const OrderAdd *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  equal_order_details_comp(&read->order_details_comp, &written->order_details_comp);
}

/* Order Add: written and read back, then read and written back */
static void check_order_add(void) {
  OrderAdd sent;
  OrderAdd got;
  uint8_t wire[40];
  uint8_t again[40];

  any_order_add(&sent);
  assert(encode_order_add(&sent, wire, 0) == 40);
  assert(decode_order_add(&got, wire, 0) == 40);
  equal_order_add(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_order_add(&got, wire, 0) == 40);
  assert(encode_order_add(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Delete: 48 bytes -------------------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_in[8];        /* bytes 0 to 7 */
  uint8_t transact_time[8];             /* bytes 8 to 15 */
  uint8_t security_id[8];               /* bytes 16 to 23 */
  OrderDetailsComp order_details_comp;  /* bytes 24 to 47 */
} OrderDelete;

/* any Order Delete at all: every byte one the checker chooses */
static void any_order_delete(OrderDelete *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  any_order_details_comp(&record->order_details_comp);
}

/* Order Delete to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_delete(const OrderDelete *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  at = encode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* Order Delete off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_delete(OrderDelete *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  at = decode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* what was read of Order Delete is what was written, byte for byte */
static void equal_order_delete(const OrderDelete *read, const OrderDelete *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  equal_order_details_comp(&read->order_details_comp, &written->order_details_comp);
}

/* Order Delete: written and read back, then read and written back */
static void check_order_delete(void) {
  OrderDelete sent;
  OrderDelete got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_delete(&sent);
  assert(encode_order_delete(&sent, wire, 0) == 48);
  assert(decode_order_delete(&got, wire, 0) == 48);
  equal_order_delete(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_delete(&got, wire, 0) == 48);
  assert(encode_order_delete(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Delete: 16 bytes --------------------------------------------- */

typedef struct {
  uint8_t security_id[8];    /* bytes 0 to 7 */
  uint8_t transact_time[8];  /* bytes 8 to 15 */
} OrderMassDelete;

/* any Order Mass Delete at all: every byte one the checker chooses */
static void any_order_mass_delete(OrderMassDelete *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Order Mass Delete to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_delete(const OrderMassDelete *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Order Mass Delete off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_delete(OrderMassDelete *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Delete is what was written, byte for byte */
static void equal_order_mass_delete(const OrderMassDelete *read, const OrderMassDelete *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Order Mass Delete: written and read back, then read and written back */
static void check_order_mass_delete(void) {
  OrderMassDelete sent;
  OrderMassDelete got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_mass_delete(&sent);
  assert(encode_order_mass_delete(&sent, wire, 0) == 16);
  assert(decode_order_mass_delete(&got, wire, 0) == 16);
  equal_order_mass_delete(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_delete(&got, wire, 0) == 16);
  assert(encode_order_mass_delete(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modify: 64 bytes -------------------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_in[8];             /* bytes 0 to 7 */
  uint8_t trd_reg_ts_prev_time_priority[8];  /* bytes 8 to 15 */
  uint8_t prev_price[8];                     /* bytes 16 to 23 */
  uint8_t prev_display_qty[4];               /* bytes 24 to 27 */
  uint8_t pad4[4];                           /* bytes 28 to 31 */
  uint8_t security_id[8];                    /* bytes 32 to 39 */
  OrderDetailsComp order_details_comp;       /* bytes 40 to 63 */
} OrderModify;

/* any Order Modify at all: every byte one the checker chooses */
static void any_order_modify(OrderModify *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_prev_time_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prev_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  any_order_details_comp(&record->order_details_comp);
}

/* Order Modify to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_order_modify(const OrderModify *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_prev_time_priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prev_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  at = encode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* Order Modify off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_order_modify(OrderModify *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_prev_time_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prev_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  at = decode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* what was read of Order Modify is what was written, byte for byte */
static void equal_order_modify(const OrderModify *read, const OrderModify *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_prev_time_priority[i] == written->trd_reg_ts_prev_time_priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prev_price[i] == written->prev_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_display_qty[i] == written->prev_display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  equal_order_details_comp(&read->order_details_comp, &written->order_details_comp);
}

/* Order Modify: written and read back, then read and written back */
static void check_order_modify(void) {
  OrderModify sent;
  OrderModify got;
  uint8_t wire[64];
  uint8_t again[64];

  any_order_modify(&sent);
  assert(encode_order_modify(&sent, wire, 0) == 64);
  assert(decode_order_modify(&got, wire, 0) == 64);
  equal_order_modify(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modify(&got, wire, 0) == 64);
  assert(encode_order_modify(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modify Same Prio: 56 bytes ---------------------------------------- */

typedef struct {
  uint8_t trd_reg_ts_time_in[8];        /* bytes 0 to 7 */
  uint8_t transact_time[8];             /* bytes 8 to 15 */
  uint8_t prev_display_qty[4];          /* bytes 16 to 19 */
  uint8_t pad4[4];                      /* bytes 20 to 23 */
  uint8_t security_id[8];               /* bytes 24 to 31 */
  OrderDetailsComp order_details_comp;  /* bytes 32 to 55 */
} OrderModifySamePrio;

/* any Order Modify Same Prio at all: every byte one the checker chooses */
static void any_order_modify_same_prio(OrderModifySamePrio *record) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->prev_display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  any_order_details_comp(&record->order_details_comp);
}

/* Order Modify Same Prio to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_order_modify_same_prio(const OrderModifySamePrio *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_in[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->prev_display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  at = encode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* Order Modify Same Prio off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_order_modify_same_prio(OrderModifySamePrio *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_in[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->prev_display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  at = decode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* what was read of Order Modify Same Prio is what was written, byte for byte */
static void equal_order_modify_same_prio(const OrderModifySamePrio *read, const OrderModifySamePrio *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_in[i] == written->trd_reg_ts_time_in[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->prev_display_qty[i] == written->prev_display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  equal_order_details_comp(&read->order_details_comp, &written->order_details_comp);
}

/* Order Modify Same Prio: written and read back, then read and written back */
static void check_order_modify_same_prio(void) {
  OrderModifySamePrio sent;
  OrderModifySamePrio got;
  uint8_t wire[56];
  uint8_t again[56];

  any_order_modify_same_prio(&sent);
  assert(encode_order_modify_same_prio(&sent, wire, 0) == 56);
  assert(decode_order_modify_same_prio(&got, wire, 0) == 56);
  equal_order_modify_same_prio(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modify_same_prio(&got, wire, 0) == 56);
  assert(encode_order_modify_same_prio(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Partial Order Execution: 48 bytes --------------------------------------- */

typedef struct {
  uint8_t side;                         /* byte 0 */
  uint8_t pad7[7];                      /* bytes 1 to 7 */
  uint8_t price[8];                     /* bytes 8 to 15 */
  uint8_t trd_reg_ts_time_priority[8];  /* bytes 16 to 23 */
  uint8_t security_id[8];               /* bytes 24 to 31 */
  uint8_t trd_match_id[4];              /* bytes 32 to 35 */
  uint8_t last_qty[4];                  /* bytes 36 to 39 */
  uint8_t last_px[8];                   /* bytes 40 to 47 */
} PartialOrderExecution;

/* any Partial Order Execution at all: every byte one the checker chooses */
static void any_partial_order_execution(PartialOrderExecution *record) {
  record->side = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
}

/* Partial Order Execution to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_partial_order_execution(const PartialOrderExecution *record, uint8_t *wire, size_t at) {
  wire[at++] = record->side;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->pad7[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trd_reg_ts_time_priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }

  return at;
}

/* Partial Order Execution off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_partial_order_execution(PartialOrderExecution *record, const uint8_t *wire, size_t at) {
  record->side = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->pad7[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trd_reg_ts_time_priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }

  return at;
}

/* what was read of Partial Order Execution is what was written, byte for byte */
static void equal_partial_order_execution(const PartialOrderExecution *read, const PartialOrderExecution *written) {
  assert(read->side == written->side);
  for (size_t i = 0; i < 7; i++) { assert(read->pad7[i] == written->pad7[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trd_reg_ts_time_priority[i] == written->trd_reg_ts_time_priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
}

/* Partial Order Execution: written and read back, then read and written back */
static void check_partial_order_execution(void) {
  PartialOrderExecution sent;
  PartialOrderExecution got;
  uint8_t wire[48];
  uint8_t again[48];

  any_partial_order_execution(&sent);
  assert(encode_partial_order_execution(&sent, wire, 0) == 48);
  assert(decode_partial_order_execution(&got, wire, 0) == 48);
  equal_partial_order_execution(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_partial_order_execution(&got, wire, 0) == 48);
  assert(encode_partial_order_execution(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Product State Change: 16 bytes ------------------------------------------ */

typedef struct {
  uint8_t trading_session_id;      /* byte 0 */
  uint8_t trading_session_sub_id;  /* byte 1 */
  uint8_t trad_ses_status;         /* byte 2 */
  uint8_t fast_market_indicator;   /* byte 3 */
  uint8_t pad4[4];                 /* bytes 4 to 7 */
  uint8_t transact_time[8];        /* bytes 8 to 15 */
} ProductStateChange;

/* any Product State Change at all: every byte one the checker chooses */
static void any_product_state_change(ProductStateChange *record) {
  record->trading_session_id = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trad_ses_status = arbitrary();
  record->fast_market_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Product State Change to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_product_state_change(const ProductStateChange *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_session_id;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trad_ses_status;
  wire[at++] = record->fast_market_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pad4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Product State Change off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_product_state_change(ProductStateChange *record, const uint8_t *wire, size_t at) {
  record->trading_session_id = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trad_ses_status = wire[at++];
  record->fast_market_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->pad4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Product State Change is what was written, byte for byte */
static void equal_product_state_change(const ProductStateChange *read, const ProductStateChange *written) {
  assert(read->trading_session_id == written->trading_session_id);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trad_ses_status == written->trad_ses_status);
  assert(read->fast_market_indicator == written->fast_market_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->pad4[i] == written->pad4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Product State Change: written and read back, then read and written back */
static void check_product_state_change(void) {
  ProductStateChange sent;
  ProductStateChange got;
  uint8_t wire[16];
  uint8_t again[16];

  any_product_state_change(&sent);
  assert(encode_product_state_change(&sent, wire, 0) == 16);
  assert(decode_product_state_change(&got, wire, 0) == 16);
  equal_product_state_change(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_product_state_change(&got, wire, 0) == 16);
  assert(encode_product_state_change(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Product Summary: 8 bytes ------------------------------------------------ */

typedef struct {
  uint8_t last_msg_seq_num_processed[4];  /* bytes 0 to 3 */
  uint8_t trading_session_id;             /* byte 4 */
  uint8_t trading_session_sub_id;         /* byte 5 */
  uint8_t trad_ses_status;                /* byte 6 */
  uint8_t fast_market_indicator;          /* byte 7 */
} ProductSummary;

/* any Product Summary at all: every byte one the checker chooses */
static void any_product_summary(ProductSummary *record) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trad_ses_status = arbitrary();
  record->fast_market_indicator = arbitrary();
}

/* Product Summary to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_product_summary(const ProductSummary *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num_processed[i]; }
  wire[at++] = record->trading_session_id;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trad_ses_status;
  wire[at++] = record->fast_market_indicator;

  return at;
}

/* Product Summary off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_product_summary(ProductSummary *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num_processed[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trad_ses_status = wire[at++];
  record->fast_market_indicator = wire[at++];

  return at;
}

/* what was read of Product Summary is what was written, byte for byte */
static void equal_product_summary(const ProductSummary *read, const ProductSummary *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num_processed[i] == written->last_msg_seq_num_processed[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trad_ses_status == written->trad_ses_status);
  assert(read->fast_market_indicator == written->fast_market_indicator);
}

/* Product Summary: written and read back, then read and written back */
static void check_product_summary(void) {
  ProductSummary sent;
  ProductSummary got;
  uint8_t wire[8];
  uint8_t again[8];

  any_product_summary(&sent);
  assert(encode_product_summary(&sent, wire, 0) == 8);
  assert(decode_product_summary(&got, wire, 0) == 8);
  equal_product_summary(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_product_summary(&got, wire, 0) == 8);
  assert(encode_product_summary(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request: 24 bytes ------------------------------------------------- */

typedef struct {
  uint8_t security_id[8];    /* bytes 0 to 7 */
  uint8_t last_qty[4];       /* bytes 8 to 11 */
  uint8_t side;              /* byte 12 */
  uint8_t pad3[3];           /* bytes 13 to 15 */
  uint8_t transact_time[8];  /* bytes 16 to 23 */
} QuoteRequest;

/* any Quote Request at all: every byte one the checker chooses */
static void any_quote_request(QuoteRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Quote Request to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quote_request(const QuoteRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->pad3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Quote Request off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quote_request(QuoteRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->pad3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request is what was written, byte for byte */
static void equal_quote_request(const QuoteRequest *read, const QuoteRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 3; i++) { assert(read->pad3[i] == written->pad3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Quote Request: written and read back, then read and written back */
static void check_quote_request(void) {
  QuoteRequest sent;
  QuoteRequest got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quote_request(&sent);
  assert(encode_quote_request(&sent, wire, 0) == 24);
  assert(decode_quote_request(&got, wire, 0) == 24);
  equal_quote_request(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request(&got, wire, 0) == 24);
  assert(encode_quote_request(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Snapshot Order: 24 bytes ------------------------------------------------ */

typedef struct {
  OrderDetailsComp order_details_comp;  /* bytes 0 to 23 */
} SnapshotOrder;

/* any Snapshot Order at all: every byte one the checker chooses */
static void any_snapshot_order(SnapshotOrder *record) {
  any_order_details_comp(&record->order_details_comp);
}

/* Snapshot Order to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_snapshot_order(const SnapshotOrder *record, uint8_t *wire, size_t at) {
  at = encode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* Snapshot Order off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_snapshot_order(SnapshotOrder *record, const uint8_t *wire, size_t at) {
  at = decode_order_details_comp(&record->order_details_comp, wire, at);

  return at;
}

/* what was read of Snapshot Order is what was written, byte for byte */
static void equal_snapshot_order(const SnapshotOrder *read, const SnapshotOrder *written) {
  equal_order_details_comp(&read->order_details_comp, &written->order_details_comp);
}

/* Snapshot Order: written and read back, then read and written back */
static void check_snapshot_order(void) {
  SnapshotOrder sent;
  SnapshotOrder got;
  uint8_t wire[24];
  uint8_t again[24];

  any_snapshot_order(&sent);
  assert(encode_snapshot_order(&sent, wire, 0) == 24);
  assert(decode_snapshot_order(&got, wire, 0) == 24);
  equal_snapshot_order(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_snapshot_order(&got, wire, 0) == 24);
  assert(encode_snapshot_order(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book: 32 bytes --------------------------------------------------- */

typedef struct {
  uint8_t transact_time[8];  /* bytes 0 to 7 */
  uint8_t security_id[8];    /* bytes 8 to 15 */
  uint8_t bid_px[8];         /* bytes 16 to 23 */
  uint8_t offer_px[8];       /* bytes 24 to 31 */
} TopOfBook;

/* any Top Of Book at all: every byte one the checker chooses */
static void any_top_of_book(TopOfBook *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_px[i] = arbitrary(); }
}

/* Top Of Book to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book(const TopOfBook *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_px[i]; }

  return at;
}

/* Top Of Book off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book(TopOfBook *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_px[i] = wire[at++]; }

  return at;
}

/* what was read of Top Of Book is what was written, byte for byte */
static void equal_top_of_book(const TopOfBook *read, const TopOfBook *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px[i] == written->bid_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_px[i] == written->offer_px[i]); }
}

/* Top Of Book: written and read back, then read and written back */
static void check_top_of_book(void) {
  TopOfBook sent;
  TopOfBook got;
  uint8_t wire[32];
  uint8_t again[32];

  any_top_of_book(&sent);
  assert(encode_top_of_book(&sent, wire, 0) == 32);
  assert(decode_top_of_book(&got, wire, 0) == 32);
  equal_top_of_book(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book(&got, wire, 0) == 32);
  assert(encode_top_of_book(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Report: 40 bytes -------------------------------------------------- */

typedef struct {
  uint8_t security_id[8];    /* bytes 0 to 7 */
  uint8_t transact_time[8];  /* bytes 8 to 15 */
  uint8_t trd_match_id[4];   /* bytes 16 to 19 */
  uint8_t last_qty[4];       /* bytes 20 to 23 */
  uint8_t last_px[8];        /* bytes 24 to 31 */
  uint8_t match_type;        /* byte 32 */
  uint8_t match_sub_type;    /* byte 33 */
  uint8_t pad6[6];           /* bytes 34 to 39 */
} TradeReport;

/* any Trade Report at all: every byte one the checker chooses */
static void any_trade_report(TradeReport *record) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  record->match_type = arbitrary();
  record->match_sub_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pad6[i] = arbitrary(); }
}

/* Trade Report to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_trade_report(const TradeReport *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  wire[at++] = record->match_type;
  wire[at++] = record->match_sub_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pad6[i]; }

  return at;
}

/* Trade Report off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_trade_report(TradeReport *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  record->match_type = wire[at++];
  record->match_sub_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pad6[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Report is what was written, byte for byte */
static void equal_trade_report(const TradeReport *read, const TradeReport *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  assert(read->match_type == written->match_type);
  assert(read->match_sub_type == written->match_sub_type);
  for (size_t i = 0; i < 6; i++) { assert(read->pad6[i] == written->pad6[i]); }
}

/* Trade Report: written and read back, then read and written back */
static void check_trade_report(void) {
  TradeReport sent;
  TradeReport got;
  uint8_t wire[40];
  uint8_t again[40];

  any_trade_report(&sent);
  assert(encode_trade_report(&sent, wire, 0) == 40);
  assert(decode_trade_report(&got, wire, 0) == 40);
  equal_trade_report(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_report(&got, wire, 0) == 40);
  assert(encode_trade_report(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_eobi_header();
  check_packet_header();
  check_message_header_comp();
  check_auction_bbo();
  check_auction_clearing_price();
  check_cross_request();
  check_execution_summary();
  check_full_order_execution();
  check_heartbeat();
  check_instrument_state_change();
  check_order_details_comp();
  check_order_add();
  check_order_delete();
  check_order_mass_delete();
  check_order_modify();
  check_order_modify_same_prio();
  check_partial_order_execution();
  check_product_state_change();
  check_product_summary();
  check_quote_request();
  check_snapshot_order();
  check_top_of_book();
  check_trade_report();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
