// nse/nsecm/orderentry/NseCm_OrderEntry_Nnf_v6_6_Client.c
/*
 * National Stock Exchange of India Ltd Order Entry
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
 *   - a Composite rule
 *   - a field read in bits
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

/* ---- Message Header: 40 bytes ------------------------------------------------ */

/* MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t log_time[4];          /* bytes 2 to 5 */
  uint8_t alpha_char[2];        /* bytes 6 to 7 */
  uint8_t trader_id[4];         /* bytes 8 to 11 */
  uint8_t error_code[2];        /* bytes 12 to 13 */
  uint8_t header_timestamp[8];  /* bytes 14 to 21 */
  uint8_t time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t message_length[2];    /* bytes 38 to 39 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Message Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->alpha_char[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->header_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Message Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->log_time[i] == written->log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->alpha_char[i] == written->alpha_char[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->header_timestamp[i] == written->header_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_1[i] == written->time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_2[i] == written->time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 40);
  assert(decode_message_header(&got, wire, 0) == 40);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 40);
  assert(encode_message_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel On Logout Status Request Message: 12 bytes ----------------------- */

/* Sent as COL_USER_STATUS_CHANGE _IN */
typedef struct {
  uint8_t user_id[4];     /* bytes 0 to 3 */
  uint8_t colo_user_bit;  /* byte 4 */
  uint8_t reserved_7[7];  /* bytes 5 to 11 */
} CancelOnLogoutStatusRequestMessage;

/* any Cancel On Logout Status Request Message at all: every byte one the checker chooses */
static void any_cancel_on_logout_status_request_message(CancelOnLogoutStatusRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->colo_user_bit = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
}

/* Cancel On Logout Status Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_cancel_on_logout_status_request_message(const CancelOnLogoutStatusRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->colo_user_bit;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }

  return at;
}

/* Cancel On Logout Status Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_cancel_on_logout_status_request_message(CancelOnLogoutStatusRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->colo_user_bit = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel On Logout Status Request Message is what was written, byte for byte */
static void equal_cancel_on_logout_status_request_message(const CancelOnLogoutStatusRequestMessage *read, const CancelOnLogoutStatusRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->colo_user_bit == written->colo_user_bit);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
}

/* Cancel On Logout Status Request Message: written and read back, then read and written back */
static void check_cancel_on_logout_status_request_message(void) {
  CancelOnLogoutStatusRequestMessage sent;
  CancelOnLogoutStatusRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_cancel_on_logout_status_request_message(&sent);
  assert(encode_cancel_on_logout_status_request_message(&sent, wire, 0) == 12);
  assert(decode_cancel_on_logout_status_request_message(&got, wire, 0) == 12);
  equal_cancel_on_logout_status_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_on_logout_status_request_message(&got, wire, 0) == 12);
  assert(encode_cancel_on_logout_status_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sec Info: 12 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t symbol[10];  /* bytes 0 to 9 */
  uint8_t series[2];   /* bytes 10 to 11 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
}

/* Sec Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }

  return at;
}

/* Sec Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 12);
  assert(decode_sec_info(&got, wire, 0) == 12);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 12);
  assert(encode_sec_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Inquiry Request Message: 16 bytes ------------------------------- */

/* Sent as AUCTION_INQUIRY_IN */
typedef struct {
  SecInfo sec_info;        /* bytes 0 to 11 */
  uint8_t auction_no[2];   /* bytes 12 to 13 */
  uint8_t page_indicator;  /* byte 14 */
  uint8_t filler;          /* byte 15 */
} AuctionInquiryRequestMessage;

/* any Auction Inquiry Request Message at all: every byte one the checker chooses */
static void any_auction_inquiry_request_message(AuctionInquiryRequestMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 2; i++) { record->auction_no[i] = arbitrary(); }
  record->page_indicator = arbitrary();
  record->filler = arbitrary();
}

/* Auction Inquiry Request Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_auction_inquiry_request_message(const AuctionInquiryRequestMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_no[i]; }
  wire[at++] = record->page_indicator;
  wire[at++] = record->filler;

  return at;
}

/* Auction Inquiry Request Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_auction_inquiry_request_message(AuctionInquiryRequestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 2; i++) { record->auction_no[i] = wire[at++]; }
  record->page_indicator = wire[at++];
  record->filler = wire[at++];

  return at;
}

/* what was read of Auction Inquiry Request Message is what was written, byte for byte */
static void equal_auction_inquiry_request_message(const AuctionInquiryRequestMessage *read, const AuctionInquiryRequestMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 2; i++) { assert(read->auction_no[i] == written->auction_no[i]); }
  assert(read->page_indicator == written->page_indicator);
  assert(read->filler == written->filler);
}

/* Auction Inquiry Request Message: written and read back, then read and written back */
static void check_auction_inquiry_request_message(void) {
  AuctionInquiryRequestMessage sent;
  AuctionInquiryRequestMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_auction_inquiry_request_message(&sent);
  assert(encode_auction_inquiry_request_message(&sent, wire, 0) == 16);
  assert(decode_auction_inquiry_request_message(&got, wire, 0) == 16);
  equal_auction_inquiry_request_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_inquiry_request_message(&got, wire, 0) == 16);
  assert(encode_auction_inquiry_request_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign Off Message: 2 bytes ------------------------------------------- */

/* Sent as BOX_SIGN_OFF */
typedef struct {
  uint8_t box_id[2];  /* bytes 0 to 1 */
} BoxSignOffMessage;

/* any Box Sign Off Message at all: every byte one the checker chooses */
static void any_box_sign_off_message(BoxSignOffMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
}

/* Box Sign Off Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_off_message(const BoxSignOffMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }

  return at;
}

/* Box Sign Off Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_off_message(BoxSignOffMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign Off Message is what was written, byte for byte */
static void equal_box_sign_off_message(const BoxSignOffMessage *read, const BoxSignOffMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
}

/* Box Sign Off Message: written and read back, then read and written back */
static void check_box_sign_off_message(void) {
  BoxSignOffMessage sent;
  BoxSignOffMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_box_sign_off_message(&sent);
  assert(encode_box_sign_off_message(&sent, wire, 0) == 2);
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  equal_box_sign_off_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_off_message(&got, wire, 0) == 2);
  assert(encode_box_sign_off_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Request Message: 20 bytes ----------------------------------- */

/* Sent as BOX_SIGN_ON_REQUEST_IN */
typedef struct {
  uint8_t box_id[2];       /* bytes 0 to 1 */
  uint8_t broker_id[5];    /* bytes 2 to 6 */
  uint8_t reserved_5[5];   /* bytes 7 to 11 */
  uint8_t session_key[8];  /* bytes 12 to 19 */
} BoxSignOnRequestMessage;

/* any Box Sign On Request Message at all: every byte one the checker chooses */
static void any_box_sign_on_request_message(BoxSignOnRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = arbitrary(); }
}

/* Box Sign On Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_request_message(const BoxSignOnRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->reserved_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session_key[i]; }

  return at;
}

/* Box Sign On Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_request_message(BoxSignOnRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->reserved_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->session_key[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Request Message is what was written, byte for byte */
static void equal_box_sign_on_request_message(const BoxSignOnRequestMessage *read, const BoxSignOnRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->reserved_5[i] == written->reserved_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->session_key[i] == written->session_key[i]); }
}

/* Box Sign On Request Message: written and read back, then read and written back */
static void check_box_sign_on_request_message(void) {
  BoxSignOnRequestMessage sent;
  BoxSignOnRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_box_sign_on_request_message(&sent);
  assert(encode_box_sign_on_request_message(&sent, wire, 0) == 20);
  assert(decode_box_sign_on_request_message(&got, wire, 0) == 20);
  equal_box_sign_on_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_request_message(&got, wire, 0) == 20);
  assert(encode_box_sign_on_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Gateway Router Request Message: 8 bytes --------------------------------- */

/* Sent as GR_REQUEST */
typedef struct {
  uint8_t box_id[2];     /* bytes 0 to 1 */
  uint8_t broker_id[5];  /* bytes 2 to 6 */
  uint8_t filler;        /* byte 7 */
} GatewayRouterRequestMessage;

/* any Gateway Router Request Message at all: every byte one the checker chooses */
static void any_gateway_router_request_message(GatewayRouterRequestMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = arbitrary(); }
  record->filler = arbitrary();
}

/* Gateway Router Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_gateway_router_request_message(const GatewayRouterRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->broker_id[i]; }
  wire[at++] = record->filler;

  return at;
}

/* Gateway Router Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_gateway_router_request_message(GatewayRouterRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->broker_id[i] = wire[at++]; }
  record->filler = wire[at++];

  return at;
}

/* what was read of Gateway Router Request Message is what was written, byte for byte */
static void equal_gateway_router_request_message(const GatewayRouterRequestMessage *read, const GatewayRouterRequestMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->broker_id[i] == written->broker_id[i]); }
  assert(read->filler == written->filler);
}

/* Gateway Router Request Message: written and read back, then read and written back */
static void check_gateway_router_request_message(void) {
  GatewayRouterRequestMessage sent;
  GatewayRouterRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_gateway_router_request_message(&sent);
  assert(encode_gateway_router_request_message(&sent, wire, 0) == 8);
  assert(decode_gateway_router_request_message(&got, wire, 0) == 8);
  equal_gateway_router_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_gateway_router_request_message(&got, wire, 0) == 8);
  assert(encode_gateway_router_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Password Reset In Message: 18 bytes ------------------------------------- */

/* Sent as RESET_PASSWORD_IN */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_14[14];  /* bytes 4 to 17 */
} PasswordResetInMessage;

/* any Password Reset In Message at all: every byte one the checker chooses */
static void any_password_reset_in_message(PasswordResetInMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = arbitrary(); }
}

/* Password Reset In Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_password_reset_in_message(const PasswordResetInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reserved_14[i]; }

  return at;
}

/* Password Reset In Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_password_reset_in_message(PasswordResetInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = wire[at++]; }

  return at;
}

/* what was read of Password Reset In Message is what was written, byte for byte */
static void equal_password_reset_in_message(const PasswordResetInMessage *read, const PasswordResetInMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->reserved_14[i] == written->reserved_14[i]); }
}

/* Password Reset In Message: written and read back, then read and written back */
static void check_password_reset_in_message(void) {
  PasswordResetInMessage sent;
  PasswordResetInMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_password_reset_in_message(&sent);
  assert(encode_password_reset_in_message(&sent, wire, 0) == 18);
  assert(decode_password_reset_in_message(&got, wire, 0) == 18);
  equal_password_reset_in_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_password_reset_in_message(&got, wire, 0) == 18);
  assert(encode_password_reset_in_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry In Message: 170 bytes ------------------------------------- */

/* Sent as TRADE_CANCEL_IN, TRADE_MOD_IN */
typedef struct {
  SecInfo sec_info;                 /* bytes 0 to 11 */
  uint8_t fill_number[4];           /* bytes 12 to 15 */
  uint8_t fill_qty[4];              /* bytes 16 to 19 */
  uint8_t fill_price[4];            /* bytes 20 to 23 */
  uint8_t market_type[2];           /* bytes 24 to 25 */
  uint8_t new_volume[4];            /* bytes 26 to 29 */
  uint8_t reserved_24[24];          /* bytes 30 to 53 */
  uint8_t buy_broker_id[5];         /* bytes 54 to 58 */
  uint8_t sell_broker_id[5];        /* bytes 59 to 63 */
  uint8_t trader_id[4];             /* bytes 64 to 67 */
  uint8_t requested_by[2];          /* bytes 68 to 69 */
  uint8_t buy_account_number[10];   /* bytes 70 to 79 */
  uint8_t sell_account_number[10];  /* bytes 80 to 89 */
  uint8_t buy_pan[10];              /* bytes 90 to 99 */
  uint8_t sell_pan[10];             /* bytes 100 to 109 */
  uint8_t reserved_60[60];          /* bytes 110 to 169 */
} TradeInquiryInMessage;

/* any Trade Inquiry In Message at all: every byte one the checker chooses */
static void any_trade_inquiry_in_message(TradeInquiryInMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = arbitrary(); }
}

/* Trade Inquiry In Message to the wire: 170 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_in_message(const TradeInquiryInMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_volume[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->reserved_24[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_by[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_pan[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_pan[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->reserved_60[i]; }

  return at;
}

/* Trade Inquiry In Message off the wire: 170 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_in_message(TradeInquiryInMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Inquiry In Message is what was written, byte for byte */
static void equal_trade_inquiry_in_message(const TradeInquiryInMessage *read, const TradeInquiryInMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->fill_number[i] == written->fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_qty[i] == written->fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_type[i] == written->market_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_volume[i] == written->new_volume[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->reserved_24[i] == written->reserved_24[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_by[i] == written->requested_by[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_account_number[i] == written->buy_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_account_number[i] == written->sell_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_pan[i] == written->buy_pan[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_pan[i] == written->sell_pan[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->reserved_60[i] == written->reserved_60[i]); }
}

/* Trade Inquiry In Message: written and read back, then read and written back */
static void check_trade_inquiry_in_message(void) {
  TradeInquiryInMessage sent;
  TradeInquiryInMessage got;
  uint8_t wire[170];
  uint8_t again[170];

  any_trade_inquiry_in_message(&sent);
  assert(encode_trade_inquiry_in_message(&sent, wire, 0) == 170);
  assert(decode_trade_inquiry_in_message(&got, wire, 0) == 170);
  equal_trade_inquiry_in_message(&got, &sent);

  for (size_t i = 0; i < 170; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_in_message(&got, wire, 0) == 170);
  assert(encode_trade_inquiry_in_message(&got, again, 0) == 170);
  for (size_t i = 0; i < 170; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Request Message: 22 bytes ------------------------- */

/* Sent as UPDATE_LOCALDB_IN */
typedef struct {
  uint8_t last_update_security_time[4];     /* bytes 0 to 3 */
  uint8_t last_update_participant_time[4];  /* bytes 4 to 7 */
  uint8_t request_for_open_orders;          /* byte 8 */
  uint8_t reserved_1;                       /* byte 9 */
  uint8_t normal_market_status[2];          /* bytes 10 to 11 */
  uint8_t odd_lot_market_status[2];         /* bytes 12 to 13 */
  uint8_t spot_market_status[2];            /* bytes 14 to 15 */
  uint8_t auction_market_status[2];         /* bytes 16 to 17 */
  uint8_t call_auction_1_market_status[2];  /* bytes 18 to 19 */
  uint8_t call_auction_2_market_status[2];  /* bytes 20 to 21 */
} UpdateLocalDatabaseRequestMessage;

/* any Update Local Database Request Message at all: every byte one the checker chooses */
static void any_update_local_database_request_message(UpdateLocalDatabaseRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = arbitrary(); }
  record->request_for_open_orders = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->normal_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->odd_lot_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->spot_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->auction_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->call_auction_1_market_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->call_auction_2_market_status[i] = arbitrary(); }
}

/* Update Local Database Request Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_request_message(const UpdateLocalDatabaseRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_security_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_update_participant_time[i]; }
  wire[at++] = record->request_for_open_orders;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->normal_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->odd_lot_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->spot_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->auction_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->call_auction_1_market_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->call_auction_2_market_status[i]; }

  return at;
}

/* Update Local Database Request Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_request_message(UpdateLocalDatabaseRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_update_security_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_update_participant_time[i] = wire[at++]; }
  record->request_for_open_orders = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->normal_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->odd_lot_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->spot_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->auction_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->call_auction_1_market_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->call_auction_2_market_status[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Request Message is what was written, byte for byte */
static void equal_update_local_database_request_message(const UpdateLocalDatabaseRequestMessage *read, const UpdateLocalDatabaseRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_security_time[i] == written->last_update_security_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_update_participant_time[i] == written->last_update_participant_time[i]); }
  assert(read->request_for_open_orders == written->request_for_open_orders);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->normal_market_status[i] == written->normal_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->odd_lot_market_status[i] == written->odd_lot_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->spot_market_status[i] == written->spot_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->auction_market_status[i] == written->auction_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->call_auction_1_market_status[i] == written->call_auction_1_market_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->call_auction_2_market_status[i] == written->call_auction_2_market_status[i]); }
}

/* Update Local Database Request Message: written and read back, then read and written back */
static void check_update_local_database_request_message(void) {
  UpdateLocalDatabaseRequestMessage sent;
  UpdateLocalDatabaseRequestMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_update_local_database_request_message(&sent);
  assert(encode_update_local_database_request_message(&sent, wire, 0) == 22);
  assert(decode_update_local_database_request_message(&got, wire, 0) == 22);
  equal_update_local_database_request_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_request_message(&got, wire, 0) == 22);
  assert(encode_update_local_database_request_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Modification Cancellation Status Request Message: 12 bytes -------- */

/* Sent as TRD_MOD_CXL_STATUS_CHANGE _IN */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t trd_mod_cxl_bit;  /* byte 4 */
  uint8_t reserved_7[7];    /* bytes 5 to 11 */
} TradeModificationCancellationStatusRequestMessage;

/* any Trade Modification Cancellation Status Request Message at all: every byte one the checker chooses */
static void any_trade_modification_cancellation_status_request_message(TradeModificationCancellationStatusRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->trd_mod_cxl_bit = arbitrary();
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = arbitrary(); }
}

/* Trade Modification Cancellation Status Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trade_modification_cancellation_status_request_message(const TradeModificationCancellationStatusRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->trd_mod_cxl_bit;
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->reserved_7[i]; }

  return at;
}

/* Trade Modification Cancellation Status Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trade_modification_cancellation_status_request_message(TradeModificationCancellationStatusRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->trd_mod_cxl_bit = wire[at++];
  for (size_t i = 0; i < 7; i++) { record->reserved_7[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Modification Cancellation Status Request Message is what was written, byte for byte */
static void equal_trade_modification_cancellation_status_request_message(const TradeModificationCancellationStatusRequestMessage *read, const TradeModificationCancellationStatusRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->trd_mod_cxl_bit == written->trd_mod_cxl_bit);
  for (size_t i = 0; i < 7; i++) { assert(read->reserved_7[i] == written->reserved_7[i]); }
}

/* Trade Modification Cancellation Status Request Message: written and read back, then read and written back */
static void check_trade_modification_cancellation_status_request_message(void) {
  TradeModificationCancellationStatusRequestMessage sent;
  TradeModificationCancellationStatusRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trade_modification_cancellation_status_request_message(&sent);
  assert(encode_trade_modification_cancellation_status_request_message(&sent, wire, 0) == 12);
  assert(decode_trade_modification_cancellation_status_request_message(&got, wire, 0) == 12);
  equal_trade_modification_cancellation_status_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_modification_cancellation_status_request_message(&got, wire, 0) == 12);
  assert(encode_trade_modification_cancellation_status_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Unlock Request Message: 28 bytes ----------------------------------- */

/* Sent as USER_ADDR_UNLOCK_IN */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_24[24];  /* bytes 4 to 27 */
} UserUnlockRequestMessage;

/* any User Unlock Request Message at all: every byte one the checker chooses */
static void any_user_unlock_request_message(UserUnlockRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = arbitrary(); }
}

/* User Unlock Request Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_user_unlock_request_message(const UserUnlockRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->reserved_24[i]; }

  return at;
}

/* User Unlock Request Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_user_unlock_request_message(UserUnlockRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = wire[at++]; }

  return at;
}

/* what was read of User Unlock Request Message is what was written, byte for byte */
static void equal_user_unlock_request_message(const UserUnlockRequestMessage *read, const UserUnlockRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->reserved_24[i] == written->reserved_24[i]); }
}

/* User Unlock Request Message: written and read back, then read and written back */
static void check_user_unlock_request_message(void) {
  UserUnlockRequestMessage sent;
  UserUnlockRequestMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_user_unlock_request_message(&sent);
  assert(encode_user_unlock_request_message(&sent, wire, 0) == 28);
  assert(decode_user_unlock_request_message(&got, wire, 0) == 28);
  equal_user_unlock_request_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_user_unlock_request_message(&got, wire, 0) == 28);
  assert(encode_user_unlock_request_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_cancel_on_logout_status_request_message();
  check_sec_info();
  check_auction_inquiry_request_message();
  check_box_sign_off_message();
  check_box_sign_on_request_message();
  check_gateway_router_request_message();
  check_password_reset_in_message();
  check_trade_inquiry_in_message();
  check_update_local_database_request_message();
  check_trade_modification_cancellation_status_request_message();
  check_user_unlock_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
