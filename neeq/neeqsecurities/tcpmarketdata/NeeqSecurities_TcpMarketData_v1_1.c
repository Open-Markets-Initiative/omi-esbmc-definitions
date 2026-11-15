// neeq/neeqsecurities/tcpmarketdata/NeeqSecurities_TcpMarketData_v1_1.c
/*
 * National Equities Exchange and Quotations Neeq Tcp Market Data
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
 *   - the dispatch that chooses a message by its type
 *   - a run counted by a field
 *   - a length prefix framing what follows
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

/* Bjse Bjqg Message Header, defining the type and body length of a message, transmitted without encryption */
typedef struct {
  uint8_t msg_type[4];     /* bytes 0 to 3 */
  uint8_t body_length[4];  /* bytes 4 to 7 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->body_length[i] = arbitrary(); }
}

/* Message Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->body_length[i]; }

  return at;
}

/* Message Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->body_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_type[i] == written->msg_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->body_length[i] == written->body_length[i]); }
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

/* ---- Logon Message: 92 bytes ------------------------------------------------- */

/* The first message the Vendor Supplied System sends to the market quotation gateway, which confirms a successful logon with a Logon of its own, so both sides transmit this message type. */
typedef struct {
  uint8_t sender_comp_id[20];       /* bytes 0 to 19 */
  uint8_t target_comp_id[20];       /* bytes 20 to 39 */
  uint8_t heart_bt_int[4];          /* bytes 40 to 43 */
  uint8_t password[16];             /* bytes 44 to 59 */
  uint8_t default_appl_ver_id[32];  /* bytes 60 to 91 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->sender_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->target_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->heart_bt_int[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->default_appl_ver_id[i] = arbitrary(); }
}

/* Logon Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sender_comp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->target_comp_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->heart_bt_int[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->default_appl_ver_id[i]; }

  return at;
}

/* Logon Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->sender_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->target_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->heart_bt_int[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->default_appl_ver_id[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->sender_comp_id[i] == written->sender_comp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->target_comp_id[i] == written->target_comp_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->heart_bt_int[i] == written->heart_bt_int[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->default_appl_ver_id[i] == written->default_appl_ver_id[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 92);
  assert(decode_logon_message(&got, wire, 0) == 92);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 92);
  assert(encode_logon_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 204 bytes ----------------------------------------------- */

/* Sent by the gateway to refuse a logon request it does not accept; the Vendor Supplied System may also send it to end the connection, so both sides transmit this message type. */
typedef struct {
  uint8_t session_status[4];  /* bytes 0 to 3 */
  uint8_t text[200];          /* bytes 4 to 203 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_status[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->text[i] = arbitrary(); }
}

/* Logout Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_status[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Logout Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_status[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_status[i] == written->session_status[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->text[i] == written->text[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 204);
  assert(decode_logout_message(&got, wire, 0) == 204);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 204);
  assert(encode_logout_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Channel Heartbeat Message: 20 bytes ------------------------------------- */

/* Sent on a market data channel every 3 seconds, carrying the sequence number of the last tick message on the channel. */
typedef struct {
  uint8_t channel_no[2];         /* bytes 0 to 1 */
  uint8_t appl_last_seq_num[8];  /* bytes 2 to 9 */
  uint8_t end_of_channel[2];     /* bytes 10 to 11 */
  uint8_t orig_time[8];          /* bytes 12 to 19 */
} ChannelHeartbeatMessage;

/* any Channel Heartbeat Message at all: every byte one the checker chooses */
static void any_channel_heartbeat_message(ChannelHeartbeatMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->end_of_channel[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
}

/* Channel Heartbeat Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_channel_heartbeat_message(const ChannelHeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_last_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->end_of_channel[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }

  return at;
}

/* Channel Heartbeat Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_channel_heartbeat_message(ChannelHeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->end_of_channel[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }

  return at;
}

/* what was read of Channel Heartbeat Message is what was written, byte for byte */
static void equal_channel_heartbeat_message(const ChannelHeartbeatMessage *read, const ChannelHeartbeatMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_last_seq_num[i] == written->appl_last_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->end_of_channel[i] == written->end_of_channel[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
}

/* Channel Heartbeat Message: written and read back, then read and written back */
static void check_channel_heartbeat_message(void) {
  ChannelHeartbeatMessage sent;
  ChannelHeartbeatMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_channel_heartbeat_message(&sent);
  assert(encode_channel_heartbeat_message(&sent, wire, 0) == 20);
  assert(decode_channel_heartbeat_message(&got, wire, 0) == 20);
  equal_channel_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_channel_heartbeat_message(&got, wire, 0) == 20);
  assert(encode_channel_heartbeat_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Message: 52 bytes ---------------------------------------- */

/* Sent by the Vendor Supplied System to request tick data or announcements again; the gateway returns the data and then the same message type to mark the retransmission complete or report why it failed, so both sides transmit this message type. */
typedef struct {
  uint8_t resend_type;          /* byte 0 */
  uint8_t channel_no[2];        /* bytes 1 to 2 */
  uint8_t appl_beg_seq_num[8];  /* bytes 3 to 10 */
  uint8_t appl_end_seq_num[8];  /* bytes 11 to 18 */
  uint8_t news_id[16];          /* bytes 19 to 34 */
  uint8_t resend_status;        /* byte 35 */
  uint8_t reject_text[16];      /* bytes 36 to 51 */
} RetransmissionMessage;

/* any Retransmission Message at all: every byte one the checker chooses */
static void any_retransmission_message(RetransmissionMessage *record) {
  record->resend_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->news_id[i] = arbitrary(); }
  record->resend_status = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = arbitrary(); }
}

/* Retransmission Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_message(const RetransmissionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->resend_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_beg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_end_seq_num[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->news_id[i]; }
  wire[at++] = record->resend_status;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reject_text[i]; }

  return at;
}

/* Retransmission Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_message(RetransmissionMessage *record, const uint8_t *wire, size_t at) {
  record->resend_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->news_id[i] = wire[at++]; }
  record->resend_status = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Message is what was written, byte for byte */
static void equal_retransmission_message(const RetransmissionMessage *read, const RetransmissionMessage *written) {
  assert(read->resend_type == written->resend_type);
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_beg_seq_num[i] == written->appl_beg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_end_seq_num[i] == written->appl_end_seq_num[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->news_id[i] == written->news_id[i]); }
  assert(read->resend_status == written->resend_status);
  for (size_t i = 0; i < 16; i++) { assert(read->reject_text[i] == written->reject_text[i]); }
}

/* Retransmission Message: written and read back, then read and written back */
static void check_retransmission_message(void) {
  RetransmissionMessage sent;
  RetransmissionMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_retransmission_message(&sent);
  assert(encode_retransmission_message(&sent, wire, 0) == 52);
  assert(decode_retransmission_message(&got, wire, 0) == 52);
  equal_retransmission_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_message(&got, wire, 0) == 52);
  assert(encode_retransmission_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Reject Message: 74 bytes --------------------------------------- */

/* Rejects an application message that satisfies the session layer rules but not the business layer rules, mainly an invalid retransmission request. */
typedef struct {
  uint8_t ref_seq_num[8];              /* bytes 0 to 7 */
  uint8_t ref_msg_type[4];             /* bytes 8 to 11 */
  uint8_t business_reject_ref_id[10];  /* bytes 12 to 21 */
  uint8_t business_reject_reason[2];   /* bytes 22 to 23 */
  uint8_t business_reject_text[50];    /* bytes 24 to 73 */
} BusinessRejectMessage;

/* any Business Reject Message at all: every byte one the checker chooses */
static void any_business_reject_message(BusinessRejectMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->ref_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ref_msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->business_reject_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->business_reject_text[i] = arbitrary(); }
}

/* Business Reject Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_business_reject_message(const BusinessRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ref_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_msg_type[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->business_reject_ref_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->business_reject_reason[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->business_reject_text[i]; }

  return at;
}

/* Business Reject Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_business_reject_message(BusinessRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->ref_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ref_msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->business_reject_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->business_reject_text[i] = wire[at++]; }

  return at;
}

/* what was read of Business Reject Message is what was written, byte for byte */
static void equal_business_reject_message(const BusinessRejectMessage *read, const BusinessRejectMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->ref_seq_num[i] == written->ref_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ref_msg_type[i] == written->ref_msg_type[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->business_reject_ref_id[i] == written->business_reject_ref_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->business_reject_reason[i] == written->business_reject_reason[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->business_reject_text[i] == written->business_reject_text[i]); }
}

/* Business Reject Message: written and read back, then read and written back */
static void check_business_reject_message(void) {
  BusinessRejectMessage sent;
  BusinessRejectMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_business_reject_message(&sent);
  assert(encode_business_reject_message(&sent, wire, 0) == 74);
  assert(decode_business_reject_message(&got, wire, 0) == 74);
  equal_business_reject_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_business_reject_message(&got, wire, 0) == 74);
  assert(encode_business_reject_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Matching Large Order Tick Message: 53 bytes ------------------- */

/* Order tick of large lot matching in spot bond trading, market data category 011, published in real time. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transact_time[8];       /* bytes 42 to 49 */
  uint8_t ord_type;               /* byte 50 */
  uint8_t settl_type;             /* byte 51 */
  uint8_t settl_period;           /* byte 52 */
} BondSpotMatchingLargeOrderTickMessage;

/* any Bond Spot Matching Large Order Tick Message at all: every byte one the checker chooses */
static void any_bond_spot_matching_large_order_tick_message(BondSpotMatchingLargeOrderTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
}

/* Bond Spot Matching Large Order Tick Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_matching_large_order_tick_message(const BondSpotMatchingLargeOrderTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;

  return at;
}

/* Bond Spot Matching Large Order Tick Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_matching_large_order_tick_message(BondSpotMatchingLargeOrderTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];

  return at;
}

/* what was read of Bond Spot Matching Large Order Tick Message is what was written, byte for byte */
static void equal_bond_spot_matching_large_order_tick_message(const BondSpotMatchingLargeOrderTickMessage *read, const BondSpotMatchingLargeOrderTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
}

/* Bond Spot Matching Large Order Tick Message: written and read back, then read and written back */
static void check_bond_spot_matching_large_order_tick_message(void) {
  BondSpotMatchingLargeOrderTickMessage sent;
  BondSpotMatchingLargeOrderTickMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_bond_spot_matching_large_order_tick_message(&sent);
  assert(encode_bond_spot_matching_large_order_tick_message(&sent, wire, 0) == 53);
  assert(decode_bond_spot_matching_large_order_tick_message(&got, wire, 0) == 53);
  equal_bond_spot_matching_large_order_tick_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_matching_large_order_tick_message(&got, wire, 0) == 53);
  assert(encode_bond_spot_matching_large_order_tick_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Agreement Trading Order Tick Message: 54 bytes -------------------------- */

/* Order tick of agreement trading on the trading support platform, market data category 021, published in real time; not yet enabled. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transact_time[8];       /* bytes 42 to 49 */
  uint8_t confirm_id[4];          /* bytes 50 to 53 */
} AgreementTradingOrderTickMessage;

/* any Agreement Trading Order Tick Message at all: every byte one the checker chooses */
static void any_agreement_trading_order_tick_message(AgreementTradingOrderTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
}

/* Agreement Trading Order Tick Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_agreement_trading_order_tick_message(const AgreementTradingOrderTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }

  return at;
}

/* Agreement Trading Order Tick Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_agreement_trading_order_tick_message(AgreementTradingOrderTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }

  return at;
}

/* what was read of Agreement Trading Order Tick Message is what was written, byte for byte */
static void equal_agreement_trading_order_tick_message(const AgreementTradingOrderTickMessage *read, const AgreementTradingOrderTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
}

/* Agreement Trading Order Tick Message: written and read back, then read and written back */
static void check_agreement_trading_order_tick_message(void) {
  AgreementTradingOrderTickMessage sent;
  AgreementTradingOrderTickMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_agreement_trading_order_tick_message(&sent);
  assert(encode_agreement_trading_order_tick_message(&sent, wire, 0) == 54);
  assert(decode_agreement_trading_order_tick_message(&got, wire, 0) == 54);
  equal_agreement_trading_order_tick_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_agreement_trading_order_tick_message(&got, wire, 0) == 54);
  assert(encode_agreement_trading_order_tick_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Lending Order Tick Message: 53 bytes ------------------------- */

/* Order tick of refinancing securities lending, market data category 023, published in real time; not yet enabled. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transact_time[8];       /* bytes 42 to 49 */
  uint8_t expiration_days[2];     /* bytes 50 to 51 */
  uint8_t expiration_type;        /* byte 52 */
} SecuritiesLendingOrderTickMessage;

/* any Securities Lending Order Tick Message at all: every byte one the checker chooses */
static void any_securities_lending_order_tick_message(SecuritiesLendingOrderTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
}

/* Securities Lending Order Tick Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_securities_lending_order_tick_message(const SecuritiesLendingOrderTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;

  return at;
}

/* Securities Lending Order Tick Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_securities_lending_order_tick_message(SecuritiesLendingOrderTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];

  return at;
}

/* what was read of Securities Lending Order Tick Message is what was written, byte for byte */
static void equal_securities_lending_order_tick_message(const SecuritiesLendingOrderTickMessage *read, const SecuritiesLendingOrderTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
}

/* Securities Lending Order Tick Message: written and read back, then read and written back */
static void check_securities_lending_order_tick_message(void) {
  SecuritiesLendingOrderTickMessage sent;
  SecuritiesLendingOrderTickMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_securities_lending_order_tick_message(&sent);
  assert(encode_securities_lending_order_tick_message(&sent, wire, 0) == 53);
  assert(decode_securities_lending_order_tick_message(&got, wire, 0) == 53);
  equal_securities_lending_order_tick_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_lending_order_tick_message(&got, wire, 0) == 53);
  assert(encode_securities_lending_order_tick_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Matching Large Trade Tick Message: 76 bytes ------------------- */

/* Trade tick of large lot matching in spot bond trading, market data category 011, published in real time. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t bid_appl_seq_num[8];    /* bytes 25 to 32 */
  uint8_t ask_appl_seq_num[8];    /* bytes 33 to 40 */
  uint8_t trade_price[8];         /* bytes 41 to 48 */
  uint8_t trade_qty[8];           /* bytes 49 to 56 */
  uint8_t trade_money[8];         /* bytes 57 to 64 */
  uint8_t exec_type;              /* byte 65 */
  uint8_t transact_time[8];       /* bytes 66 to 73 */
  uint8_t settl_period;           /* byte 74 */
  uint8_t settl_type;             /* byte 75 */
} BondSpotMatchingLargeTradeTickMessage;

/* any Bond Spot Matching Large Trade Tick Message at all: every byte one the checker chooses */
static void any_bond_spot_matching_large_trade_tick_message(BondSpotMatchingLargeTradeTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->settl_period = arbitrary();
  record->settl_type = arbitrary();
}

/* Bond Spot Matching Large Trade Tick Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_matching_large_trade_tick_message(const BondSpotMatchingLargeTradeTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_money[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->settl_period;
  wire[at++] = record->settl_type;

  return at;
}

/* Bond Spot Matching Large Trade Tick Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_matching_large_trade_tick_message(BondSpotMatchingLargeTradeTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->settl_period = wire[at++];
  record->settl_type = wire[at++];

  return at;
}

/* what was read of Bond Spot Matching Large Trade Tick Message is what was written, byte for byte */
static void equal_bond_spot_matching_large_trade_tick_message(const BondSpotMatchingLargeTradeTickMessage *read, const BondSpotMatchingLargeTradeTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_appl_seq_num[i] == written->ask_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_qty[i] == written->trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_money[i] == written->trade_money[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->settl_period == written->settl_period);
  assert(read->settl_type == written->settl_type);
}

/* Bond Spot Matching Large Trade Tick Message: written and read back, then read and written back */
static void check_bond_spot_matching_large_trade_tick_message(void) {
  BondSpotMatchingLargeTradeTickMessage sent;
  BondSpotMatchingLargeTradeTickMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_bond_spot_matching_large_trade_tick_message(&sent);
  assert(encode_bond_spot_matching_large_trade_tick_message(&sent, wire, 0) == 76);
  assert(decode_bond_spot_matching_large_trade_tick_message(&got, wire, 0) == 76);
  equal_bond_spot_matching_large_trade_tick_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_matching_large_trade_tick_message(&got, wire, 0) == 76);
  assert(encode_bond_spot_matching_large_trade_tick_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Negotiated Trade Tick Message: 76 bytes ----------------------- */

/* Trade tick of negotiated trading in spot bond trading, market data category 012, published in real time. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t bid_appl_seq_num[8];    /* bytes 25 to 32 */
  uint8_t ask_appl_seq_num[8];    /* bytes 33 to 40 */
  uint8_t trade_price[8];         /* bytes 41 to 48 */
  uint8_t trade_qty[8];           /* bytes 49 to 56 */
  uint8_t trade_money[8];         /* bytes 57 to 64 */
  uint8_t exec_type;              /* byte 65 */
  uint8_t transact_time[8];       /* bytes 66 to 73 */
  uint8_t settl_period;           /* byte 74 */
  uint8_t settl_type;             /* byte 75 */
} BondSpotNegotiatedTradeTickMessage;

/* any Bond Spot Negotiated Trade Tick Message at all: every byte one the checker chooses */
static void any_bond_spot_negotiated_trade_tick_message(BondSpotNegotiatedTradeTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->settl_period = arbitrary();
  record->settl_type = arbitrary();
}

/* Bond Spot Negotiated Trade Tick Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_negotiated_trade_tick_message(const BondSpotNegotiatedTradeTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_money[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->settl_period;
  wire[at++] = record->settl_type;

  return at;
}

/* Bond Spot Negotiated Trade Tick Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_negotiated_trade_tick_message(BondSpotNegotiatedTradeTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->settl_period = wire[at++];
  record->settl_type = wire[at++];

  return at;
}

/* what was read of Bond Spot Negotiated Trade Tick Message is what was written, byte for byte */
static void equal_bond_spot_negotiated_trade_tick_message(const BondSpotNegotiatedTradeTickMessage *read, const BondSpotNegotiatedTradeTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_appl_seq_num[i] == written->ask_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_qty[i] == written->trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_money[i] == written->trade_money[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->settl_period == written->settl_period);
  assert(read->settl_type == written->settl_type);
}

/* Bond Spot Negotiated Trade Tick Message: written and read back, then read and written back */
static void check_bond_spot_negotiated_trade_tick_message(void) {
  BondSpotNegotiatedTradeTickMessage sent;
  BondSpotNegotiatedTradeTickMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_bond_spot_negotiated_trade_tick_message(&sent);
  assert(encode_bond_spot_negotiated_trade_tick_message(&sent, wire, 0) == 76);
  assert(decode_bond_spot_negotiated_trade_tick_message(&got, wire, 0) == 76);
  equal_bond_spot_negotiated_trade_tick_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_negotiated_trade_tick_message(&got, wire, 0) == 76);
  assert(encode_bond_spot_negotiated_trade_tick_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Securities Lending Trade Tick Message: 74 bytes ------------------------- */

/* Trade tick of refinancing securities lending, market data category 023, published in real time; it has no extension fields and is not yet enabled. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t bid_appl_seq_num[8];    /* bytes 25 to 32 */
  uint8_t ask_appl_seq_num[8];    /* bytes 33 to 40 */
  uint8_t trade_price[8];         /* bytes 41 to 48 */
  uint8_t trade_qty[8];           /* bytes 49 to 56 */
  uint8_t trade_money[8];         /* bytes 57 to 64 */
  uint8_t exec_type;              /* byte 65 */
  uint8_t transact_time[8];       /* bytes 66 to 73 */
} SecuritiesLendingTradeTickMessage;

/* any Securities Lending Trade Tick Message at all: every byte one the checker chooses */
static void any_securities_lending_trade_tick_message(SecuritiesLendingTradeTickMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Securities Lending Trade Tick Message to the wire: 74 bytes from at, returning where the next byte goes */
static size_t encode_securities_lending_trade_tick_message(const SecuritiesLendingTradeTickMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_money[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Securities Lending Trade Tick Message off the wire: 74 bytes from at, returning where the next byte lies */
static size_t decode_securities_lending_trade_tick_message(SecuritiesLendingTradeTickMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_money[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Securities Lending Trade Tick Message is what was written, byte for byte */
static void equal_securities_lending_trade_tick_message(const SecuritiesLendingTradeTickMessage *read, const SecuritiesLendingTradeTickMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_appl_seq_num[i] == written->ask_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_qty[i] == written->trade_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_money[i] == written->trade_money[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Securities Lending Trade Tick Message: written and read back, then read and written back */
static void check_securities_lending_trade_tick_message(void) {
  SecuritiesLendingTradeTickMessage sent;
  SecuritiesLendingTradeTickMessage got;
  uint8_t wire[74];
  uint8_t again[74];

  any_securities_lending_trade_tick_message(&sent);
  assert(encode_securities_lending_trade_tick_message(&sent, wire, 0) == 74);
  assert(decode_securities_lending_trade_tick_message(&got, wire, 0) == 74);
  equal_securities_lending_trade_tick_message(&got, &sent);

  for (size_t i = 0; i < 74; i++) { wire[i] = arbitrary(); }
  assert(decode_securities_lending_trade_tick_message(&got, wire, 0) == 74);
  assert(encode_securities_lending_trade_tick_message(&got, again, 0) == 74);
  for (size_t i = 0; i < 74; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Tail: 4 bytes --------------------------------------------------- */

/* Bjse Bjqg Message Tail, defining the checksum of a message, transmitted without encryption */
typedef struct {
  uint8_t checksum[4];  /* bytes 0 to 3 */
} MessageTail;

/* any Message Tail at all: every byte one the checker chooses */
static void any_message_tail(MessageTail *record) {
  for (size_t i = 0; i < 4; i++) { record->checksum[i] = arbitrary(); }
}

/* Message Tail to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_tail(const MessageTail *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->checksum[i]; }

  return at;
}

/* Message Tail off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_tail(MessageTail *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Message Tail is what was written, byte for byte */
static void equal_message_tail(const MessageTail *read, const MessageTail *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->checksum[i] == written->checksum[i]); }
}

/* Message Tail: written and read back, then read and written back */
static void check_message_tail(void) {
  MessageTail sent;
  MessageTail got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_tail(&sent);
  assert(encode_message_tail(&sent, wire, 0) == 4);
  assert(decode_message_tail(&got, wire, 0) == 4);
  equal_message_tail(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_tail(&got, wire, 0) == 4);
  assert(encode_message_tail(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_message();
  check_logout_message();
  check_channel_heartbeat_message();
  check_retransmission_message();
  check_business_reject_message();
  check_bond_spot_matching_large_order_tick_message();
  check_agreement_trading_order_tick_message();
  check_securities_lending_order_tick_message();
  check_bond_spot_matching_large_trade_tick_message();
  check_bond_spot_negotiated_trade_tick_message();
  check_securities_lending_trade_tick_message();
  check_message_tail();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
