// szse/szsesecurities/multicastmarketdata/SzseSecurities_MulticastMarketData_v1_17.c
/*
 * Shenzhen Stock Exchange Szse Multicast Market Data
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
 *   - a field read in bits
 *   - a Conversion rule
 *   - a field present only on a condition
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

/* Szse Binary message header, defining the type and body length of a message */
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

/* ---- Channel Heartbeat Message: 12 bytes ------------------------------------- */

/* Sent on a market data channel every 3 seconds, carrying the sequence number of the last market data message on the channel. */
typedef struct {
  uint8_t channel_no[2];         /* bytes 0 to 1 */
  uint8_t appl_last_seq_num[8];  /* bytes 2 to 9 */
  uint8_t end_of_channel[2];     /* bytes 10 to 11 */
} ChannelHeartbeatMessage;

/* any Channel Heartbeat Message at all: every byte one the checker chooses */
static void any_channel_heartbeat_message(ChannelHeartbeatMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->end_of_channel[i] = arbitrary(); }
}

/* Channel Heartbeat Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_channel_heartbeat_message(const ChannelHeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_last_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->end_of_channel[i]; }

  return at;
}

/* Channel Heartbeat Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_channel_heartbeat_message(ChannelHeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_last_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->end_of_channel[i] = wire[at++]; }

  return at;
}

/* what was read of Channel Heartbeat Message is what was written, byte for byte */
static void equal_channel_heartbeat_message(const ChannelHeartbeatMessage *read, const ChannelHeartbeatMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_last_seq_num[i] == written->appl_last_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->end_of_channel[i] == written->end_of_channel[i]); }
}

/* Channel Heartbeat Message: written and read back, then read and written back */
static void check_channel_heartbeat_message(void) {
  ChannelHeartbeatMessage sent;
  ChannelHeartbeatMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_channel_heartbeat_message(&sent);
  assert(encode_channel_heartbeat_message(&sent, wire, 0) == 12);
  assert(decode_channel_heartbeat_message(&got, wire, 0) == 12);
  equal_channel_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_channel_heartbeat_message(&got, wire, 0) == 12);
  assert(encode_channel_heartbeat_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmitting Message: 44 bytes ---------------------------------------- */

/* Vendor Supplied System sends a re-transmission message to Market Data GateWay, which returns the re-transmission data needed followed by a re-transmission message indicating completion, or the failure reason if it fails. Market Data GateWay handles multiple requests in the order in which they arrive, so this message type is transmitted by both sides; ResendStatus and RejectText are only effective on the gateway reply. */
typedef struct {
  uint8_t resend_type;          /* byte 0 */
  uint8_t channel_no[2];        /* bytes 1 to 2 */
  uint8_t appl_beg_seq_num[8];  /* bytes 3 to 10 */
  uint8_t appl_end_seq_num[8];  /* bytes 11 to 18 */
  uint8_t news_id[8];           /* bytes 19 to 26 */
  uint8_t resend_status;        /* byte 27 */
  uint8_t reject_text[16];      /* bytes 28 to 43 */
} RetransmittingMessage;

/* any Retransmitting Message at all: every byte one the checker chooses */
static void any_retransmitting_message(RetransmittingMessage *record) {
  record->resend_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->news_id[i] = arbitrary(); }
  record->resend_status = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = arbitrary(); }
}

/* Retransmitting Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_retransmitting_message(const RetransmittingMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->resend_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_beg_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_end_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->news_id[i]; }
  wire[at++] = record->resend_status;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reject_text[i]; }

  return at;
}

/* Retransmitting Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_retransmitting_message(RetransmittingMessage *record, const uint8_t *wire, size_t at) {
  record->resend_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_beg_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_end_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->news_id[i] = wire[at++]; }
  record->resend_status = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmitting Message is what was written, byte for byte */
static void equal_retransmitting_message(const RetransmittingMessage *read, const RetransmittingMessage *written) {
  assert(read->resend_type == written->resend_type);
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_beg_seq_num[i] == written->appl_beg_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_end_seq_num[i] == written->appl_end_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->news_id[i] == written->news_id[i]); }
  assert(read->resend_status == written->resend_status);
  for (size_t i = 0; i < 16; i++) { assert(read->reject_text[i] == written->reject_text[i]); }
}

/* Retransmitting Message: written and read back, then read and written back */
static void check_retransmitting_message(void) {
  RetransmittingMessage sent;
  RetransmittingMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_retransmitting_message(&sent);
  assert(encode_retransmitting_message(&sent, wire, 0) == 44);
  assert(decode_retransmitting_message(&got, wire, 0) == 44);
  equal_retransmitting_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmitting_message(&got, wire, 0) == 44);
  assert(encode_retransmitting_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Client User Information Reporting Message: 26 bytes --------------------- */

/* Vendor Supplied System reports the number of client users connected to it at the current time to the Market Data GateWay front-end processor at regular intervals. Only the Vendor Supplied System of a vendor sends this message. */
typedef struct {
  uint8_t orig_time[8];      /* bytes 0 to 7 */
  uint8_t version_code[16];  /* bytes 8 to 23 */
  uint8_t user_num[2];       /* bytes 24 to 25 */
} ClientUserInformationReportingMessage;

/* any Client User Information Reporting Message at all: every byte one the checker chooses */
static void any_client_user_information_reporting_message(ClientUserInformationReportingMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->version_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->user_num[i] = arbitrary(); }
}

/* Client User Information Reporting Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_client_user_information_reporting_message(const ClientUserInformationReportingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->version_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->user_num[i]; }

  return at;
}

/* Client User Information Reporting Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_client_user_information_reporting_message(ClientUserInformationReportingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->version_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->user_num[i] = wire[at++]; }

  return at;
}

/* what was read of Client User Information Reporting Message is what was written, byte for byte */
static void equal_client_user_information_reporting_message(const ClientUserInformationReportingMessage *read, const ClientUserInformationReportingMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->version_code[i] == written->version_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->user_num[i] == written->user_num[i]); }
}

/* Client User Information Reporting Message: written and read back, then read and written back */
static void check_client_user_information_reporting_message(void) {
  ClientUserInformationReportingMessage sent;
  ClientUserInformationReportingMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_client_user_information_reporting_message(&sent);
  assert(encode_client_user_information_reporting_message(&sent, wire, 0) == 26);
  assert(decode_client_user_information_reporting_message(&got, wire, 0) == 26);
  equal_client_user_information_reporting_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_client_user_information_reporting_message(&got, wire, 0) == 26);
  assert(encode_client_user_information_reporting_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Reject Message: 74 bytes --------------------------------------- */

/* Rejects an application layer message that satisfies the session layer rules but does not satisfy the rules of the business layer. It reports on an incorrect re-transmitted message or client user information reporting message declared by the user. */
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

/* ---- Real Time Market Status Message: 69 bytes ------------------------------- */

/* Released every 3 seconds, carrying the trading session state of a market and, for stock connect, the daily quota balance. */
typedef struct {
  uint8_t orig_time[8];               /* bytes 0 to 7 */
  uint8_t channel_no[2];              /* bytes 8 to 9 */
  uint8_t market_id[8];               /* bytes 10 to 17 */
  uint8_t market_segment_id[8];       /* bytes 18 to 25 */
  uint8_t trading_session_id[4];      /* bytes 26 to 29 */
  uint8_t trading_session_sub_id[4];  /* bytes 30 to 33 */
  uint8_t trad_ses_status[2];         /* bytes 34 to 35 */
  uint8_t trad_ses_start_time[8];     /* bytes 36 to 43 */
  uint8_t trad_ses_end_time[8];       /* bytes 44 to 51 */
  uint8_t thredhold_amount[8];        /* bytes 52 to 59 */
  uint8_t pos_amt[8];                 /* bytes 60 to 67 */
  uint8_t amounts_status;             /* byte 68 */
} RealTimeMarketStatusMessage;

/* any Real Time Market Status Message at all: every byte one the checker chooses */
static void any_real_time_market_status_message(RealTimeMarketStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trad_ses_status[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->thredhold_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->pos_amt[i] = arbitrary(); }
  record->amounts_status = arbitrary();
}

/* Real Time Market Status Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_real_time_market_status_message(const RealTimeMarketStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_sub_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trad_ses_status[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_end_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->thredhold_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->pos_amt[i]; }
  wire[at++] = record->amounts_status;

  return at;
}

/* Real Time Market Status Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_real_time_market_status_message(RealTimeMarketStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trad_ses_status[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->thredhold_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->pos_amt[i] = wire[at++]; }
  record->amounts_status = wire[at++];

  return at;
}

/* what was read of Real Time Market Status Message is what was written, byte for byte */
static void equal_real_time_market_status_message(const RealTimeMarketStatusMessage *read, const RealTimeMarketStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_id[i] == written->trading_session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_sub_id[i] == written->trading_session_sub_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trad_ses_status[i] == written->trad_ses_status[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_start_time[i] == written->trad_ses_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_end_time[i] == written->trad_ses_end_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->thredhold_amount[i] == written->thredhold_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->pos_amt[i] == written->pos_amt[i]); }
  assert(read->amounts_status == written->amounts_status);
}

/* Real Time Market Status Message: written and read back, then read and written back */
static void check_real_time_market_status_message(void) {
  RealTimeMarketStatusMessage sent;
  RealTimeMarketStatusMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_real_time_market_status_message(&sent);
  assert(encode_real_time_market_status_message(&sent, wire, 0) == 69);
  assert(decode_real_time_market_status_message(&got, wire, 0) == 69);
  equal_real_time_market_status_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_real_time_market_status_message(&got, wire, 0) == 69);
  assert(encode_real_time_market_status_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Statistic Indicator Snapshot Message: 69 bytes -------------------------- */

/* Snapshot carrying market data category 910, statistic indicators. */
typedef struct {
  uint8_t orig_time[8];           /* bytes 0 to 7 */
  uint8_t channel_no[2];          /* bytes 8 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t trading_phase_code[8];  /* bytes 25 to 32 */
  uint8_t prev_close_px[8];       /* bytes 33 to 40 */
  uint8_t num_trades[8];          /* bytes 41 to 48 */
  uint8_t total_volume_trade[8];  /* bytes 49 to 56 */
  uint8_t total_value_trade[8];   /* bytes 57 to 64 */
  uint8_t stock_num[4];           /* bytes 65 to 68 */
} StatisticIndicatorSnapshotMessage;

/* any Statistic Indicator Snapshot Message at all: every byte one the checker chooses */
static void any_statistic_indicator_snapshot_message(StatisticIndicatorSnapshotMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->prev_close_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->num_trades[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_volume_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_value_trade[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stock_num[i] = arbitrary(); }
}

/* Statistic Indicator Snapshot Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_statistic_indicator_snapshot_message(const StatisticIndicatorSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trading_phase_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->prev_close_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->num_trades[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_volume_trade[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_value_trade[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stock_num[i]; }

  return at;
}

/* Statistic Indicator Snapshot Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_statistic_indicator_snapshot_message(StatisticIndicatorSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->orig_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trading_phase_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->prev_close_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->num_trades[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_volume_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_value_trade[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stock_num[i] = wire[at++]; }

  return at;
}

/* what was read of Statistic Indicator Snapshot Message is what was written, byte for byte */
static void equal_statistic_indicator_snapshot_message(const StatisticIndicatorSnapshotMessage *read, const StatisticIndicatorSnapshotMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trading_phase_code[i] == written->trading_phase_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->prev_close_px[i] == written->prev_close_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->num_trades[i] == written->num_trades[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_volume_trade[i] == written->total_volume_trade[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_value_trade[i] == written->total_value_trade[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stock_num[i] == written->stock_num[i]); }
}

/* Statistic Indicator Snapshot Message: written and read back, then read and written back */
static void check_statistic_indicator_snapshot_message(void) {
  StatisticIndicatorSnapshotMessage sent;
  StatisticIndicatorSnapshotMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_statistic_indicator_snapshot_message(&sent);
  assert(encode_statistic_indicator_snapshot_message(&sent, wire, 0) == 69);
  assert(decode_statistic_indicator_snapshot_message(&got, wire, 0) == 69);
  equal_statistic_indicator_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_statistic_indicator_snapshot_message(&got, wire, 0) == 69);
  assert(encode_statistic_indicator_snapshot_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data In Call Auction Message: 51 bytes ----------------------- */

/* Order tick carrying market data categories 011 for equities, funds and bonds in the call auction of the spot market, 021 pledge-style repo and 041 call auction in options. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transac_time[8];        /* bytes 42 to 49 */
  uint8_t ord_type;               /* byte 50 */
} OrderTickDataInCallAuctionMessage;

/* any Order Tick Data In Call Auction Message at all: every byte one the checker chooses */
static void any_order_tick_data_in_call_auction_message(OrderTickDataInCallAuctionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  record->ord_type = arbitrary();
}

/* Order Tick Data In Call Auction Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_in_call_auction_message(const OrderTickDataInCallAuctionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  wire[at++] = record->ord_type;

  return at;
}

/* Order Tick Data In Call Auction Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_in_call_auction_message(OrderTickDataInCallAuctionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  record->ord_type = wire[at++];

  return at;
}

/* what was read of Order Tick Data In Call Auction Message is what was written, byte for byte */
static void equal_order_tick_data_in_call_auction_message(const OrderTickDataInCallAuctionMessage *read, const OrderTickDataInCallAuctionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  assert(read->ord_type == written->ord_type);
}

/* Order Tick Data In Call Auction Message: written and read back, then read and written back */
static void check_order_tick_data_in_call_auction_message(void) {
  OrderTickDataInCallAuctionMessage sent;
  OrderTickDataInCallAuctionMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_order_tick_data_in_call_auction_message(&sent);
  assert(encode_order_tick_data_in_call_auction_message(&sent, wire, 0) == 51);
  assert(decode_order_tick_data_in_call_auction_message(&got, wire, 0) == 51);
  equal_order_tick_data_in_call_auction_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_in_call_auction_message(&got, wire, 0) == 51);
  assert(encode_order_tick_data_in_call_auction_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data Of Negotiable Trade Message: 100 bytes ------------------ */

/* Order tick carrying market data categories 051 indication of interest of negotiable trade and 052 quote of negotiable trade. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transac_time[8];        /* bytes 42 to 49 */
  uint8_t confirm_id[8];          /* bytes 50 to 57 */
  uint8_t contactor[12];          /* bytes 58 to 69 */
  uint8_t contact_info[30];       /* bytes 70 to 99 */
} OrderTickDataOfNegotiableTradeMessage;

/* any Order Tick Data Of Negotiable Trade Message at all: every byte one the checker chooses */
static void any_order_tick_data_of_negotiable_trade_message(OrderTickDataOfNegotiableTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->contactor[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->contact_info[i] = arbitrary(); }
}

/* Order Tick Data Of Negotiable Trade Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_of_negotiable_trade_message(const OrderTickDataOfNegotiableTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->contactor[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->contact_info[i]; }

  return at;
}

/* Order Tick Data Of Negotiable Trade Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_of_negotiable_trade_message(OrderTickDataOfNegotiableTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->contactor[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->contact_info[i] = wire[at++]; }

  return at;
}

/* what was read of Order Tick Data Of Negotiable Trade Message is what was written, byte for byte */
static void equal_order_tick_data_of_negotiable_trade_message(const OrderTickDataOfNegotiableTradeMessage *read, const OrderTickDataOfNegotiableTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->contactor[i] == written->contactor[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->contact_info[i] == written->contact_info[i]); }
}

/* Order Tick Data Of Negotiable Trade Message: written and read back, then read and written back */
static void check_order_tick_data_of_negotiable_trade_message(void) {
  OrderTickDataOfNegotiableTradeMessage sent;
  OrderTickDataOfNegotiableTradeMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_order_tick_data_of_negotiable_trade_message(&sent);
  assert(encode_order_tick_data_of_negotiable_trade_message(&sent, wire, 0) == 100);
  assert(decode_order_tick_data_of_negotiable_trade_message(&got, wire, 0) == 100);
  equal_order_tick_data_of_negotiable_trade_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_of_negotiable_trade_message(&got, wire, 0) == 100);
  assert(encode_order_tick_data_of_negotiable_trade_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data Of Security Lending Message: 53 bytes ------------------- */

/* Order tick carrying market data category 071, security lending. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transac_time[8];        /* bytes 42 to 49 */
  uint8_t expiration_days[2];     /* bytes 50 to 51 */
  uint8_t expiration_type;        /* byte 52 */
} OrderTickDataOfSecurityLendingMessage;

/* any Order Tick Data Of Security Lending Message at all: every byte one the checker chooses */
static void any_order_tick_data_of_security_lending_message(OrderTickDataOfSecurityLendingMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
}

/* Order Tick Data Of Security Lending Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_of_security_lending_message(const OrderTickDataOfSecurityLendingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;

  return at;
}

/* Order Tick Data Of Security Lending Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_of_security_lending_message(OrderTickDataOfSecurityLendingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];

  return at;
}

/* what was read of Order Tick Data Of Security Lending Message is what was written, byte for byte */
static void equal_order_tick_data_of_security_lending_message(const OrderTickDataOfSecurityLendingMessage *read, const OrderTickDataOfSecurityLendingMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
}

/* Order Tick Data Of Security Lending Message: written and read back, then read and written back */
static void check_order_tick_data_of_security_lending_message(void) {
  OrderTickDataOfSecurityLendingMessage sent;
  OrderTickDataOfSecurityLendingMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_order_tick_data_of_security_lending_message(&sent);
  assert(encode_order_tick_data_of_security_lending_message(&sent, wire, 0) == 53);
  assert(decode_order_tick_data_of_security_lending_message(&got, wire, 0) == 53);
  equal_order_tick_data_of_security_lending_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_of_security_lending_message(&got, wire, 0) == 53);
  assert(encode_order_tick_data_of_security_lending_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data Of Spot Bond Trading Matching Deal Message: 51 bytes ---- */

/* Order tick carrying market data categories 021 bond general pledged repo matching deal and 411 spot bond trading matching deal. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transac_time[8];        /* bytes 42 to 49 */
  uint8_t ord_type;               /* byte 50 */
} OrderTickDataOfSpotBondTradingMatchingDealMessage;

/* any Order Tick Data Of Spot Bond Trading Matching Deal Message at all: every byte one the checker chooses */
static void any_order_tick_data_of_spot_bond_trading_matching_deal_message(OrderTickDataOfSpotBondTradingMatchingDealMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  record->ord_type = arbitrary();
}

/* Order Tick Data Of Spot Bond Trading Matching Deal Message to the wire: 51 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_of_spot_bond_trading_matching_deal_message(const OrderTickDataOfSpotBondTradingMatchingDealMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  wire[at++] = record->ord_type;

  return at;
}

/* Order Tick Data Of Spot Bond Trading Matching Deal Message off the wire: 51 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_of_spot_bond_trading_matching_deal_message(OrderTickDataOfSpotBondTradingMatchingDealMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  record->ord_type = wire[at++];

  return at;
}

/* what was read of Order Tick Data Of Spot Bond Trading Matching Deal Message is what was written, byte for byte */
static void equal_order_tick_data_of_spot_bond_trading_matching_deal_message(const OrderTickDataOfSpotBondTradingMatchingDealMessage *read, const OrderTickDataOfSpotBondTradingMatchingDealMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  assert(read->ord_type == written->ord_type);
}

/* Order Tick Data Of Spot Bond Trading Matching Deal Message: written and read back, then read and written back */
static void check_order_tick_data_of_spot_bond_trading_matching_deal_message(void) {
  OrderTickDataOfSpotBondTradingMatchingDealMessage sent;
  OrderTickDataOfSpotBondTradingMatchingDealMessage got;
  uint8_t wire[51];
  uint8_t again[51];

  any_order_tick_data_of_spot_bond_trading_matching_deal_message(&sent);
  assert(encode_order_tick_data_of_spot_bond_trading_matching_deal_message(&sent, wire, 0) == 51);
  assert(decode_order_tick_data_of_spot_bond_trading_matching_deal_message(&got, wire, 0) == 51);
  equal_order_tick_data_of_spot_bond_trading_matching_deal_message(&got, &sent);

  for (size_t i = 0; i < 51; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_of_spot_bond_trading_matching_deal_message(&got, wire, 0) == 51);
  assert(encode_order_tick_data_of_spot_bond_trading_matching_deal_message(&got, again, 0) == 51);
  for (size_t i = 0; i < 51; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data Of Spot Bond Trading Quotation Message: 377 bytes ------- */

/* Order tick carrying market data categories 415 spot bond trading declaration of intent and 417 spot bond trading large amount matching deal, for spot bond trading other than bid. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t security_id[8];         /* bytes 13 to 20 */
  uint8_t security_id_source[4];  /* bytes 21 to 24 */
  uint8_t price[8];               /* bytes 25 to 32 */
  uint8_t order_qty[8];           /* bytes 33 to 40 */
  uint8_t side;                   /* byte 41 */
  uint8_t transac_time[8];        /* bytes 42 to 49 */
  uint8_t quote_id[10];           /* bytes 50 to 59 */
  uint8_t member_id[6];           /* bytes 60 to 65 */
  uint8_t investor_type[2];       /* bytes 66 to 67 */
  uint8_t investor_id[10];        /* bytes 68 to 77 */
  uint8_t investor_name[120];     /* bytes 78 to 197 */
  uint8_t trader_code[8];         /* bytes 198 to 205 */
  uint8_t settl_period;           /* byte 206 */
  uint8_t settl_type[2];          /* bytes 207 to 208 */
  uint8_t memo[160];              /* bytes 209 to 368 */
  uint8_t min_qty[8];             /* bytes 369 to 376 */
} OrderTickDataOfSpotBondTradingQuotationMessage;

/* any Order Tick Data Of Spot Bond Trading Quotation Message at all: every byte one the checker chooses */
static void any_order_tick_data_of_spot_bond_trading_quotation_message(OrderTickDataOfSpotBondTradingQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quote_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->investor_type[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->investor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 120; i++) { record->investor_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_code[i] = arbitrary(); }
  record->settl_period = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = arbitrary(); }
  for (size_t i = 0; i < 160; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
}

/* Order Tick Data Of Spot Bond Trading Quotation Message to the wire: 377 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_of_spot_bond_trading_quotation_message(const OrderTickDataOfSpotBondTradingQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quote_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->member_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->investor_type[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->investor_id[i]; }
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->investor_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_code[i]; }
  wire[at++] = record->settl_period;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settl_type[i]; }
  for (size_t i = 0; i < 160; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }

  return at;
}

/* Order Tick Data Of Spot Bond Trading Quotation Message off the wire: 377 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_of_spot_bond_trading_quotation_message(OrderTickDataOfSpotBondTradingQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quote_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->investor_type[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->investor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 120; i++) { record->investor_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_code[i] = wire[at++]; }
  record->settl_period = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = wire[at++]; }
  for (size_t i = 0; i < 160; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Tick Data Of Spot Bond Trading Quotation Message is what was written, byte for byte */
static void equal_order_tick_data_of_spot_bond_trading_quotation_message(const OrderTickDataOfSpotBondTradingQuotationMessage *read, const OrderTickDataOfSpotBondTradingQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quote_id[i] == written->quote_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->member_id[i] == written->member_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->investor_type[i] == written->investor_type[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->investor_id[i] == written->investor_id[i]); }
  for (size_t i = 0; i < 120; i++) { assert(read->investor_name[i] == written->investor_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  assert(read->settl_period == written->settl_period);
  for (size_t i = 0; i < 2; i++) { assert(read->settl_type[i] == written->settl_type[i]); }
  for (size_t i = 0; i < 160; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
}

/* Order Tick Data Of Spot Bond Trading Quotation Message: written and read back, then read and written back */
static void check_order_tick_data_of_spot_bond_trading_quotation_message(void) {
  OrderTickDataOfSpotBondTradingQuotationMessage sent;
  OrderTickDataOfSpotBondTradingQuotationMessage got;
  uint8_t wire[377];
  uint8_t again[377];

  any_order_tick_data_of_spot_bond_trading_quotation_message(&sent);
  assert(encode_order_tick_data_of_spot_bond_trading_quotation_message(&sent, wire, 0) == 377);
  assert(decode_order_tick_data_of_spot_bond_trading_quotation_message(&got, wire, 0) == 377);
  equal_order_tick_data_of_spot_bond_trading_quotation_message(&got, &sent);

  for (size_t i = 0; i < 377; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_of_spot_bond_trading_quotation_message(&got, wire, 0) == 377);
  assert(encode_order_tick_data_of_spot_bond_trading_quotation_message(&got, again, 0) == 377);
  for (size_t i = 0; i < 377; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Tick Data Of Bid Quotation Message: 407 bytes --------------------- */

/* Order tick carrying market data category 416, spot bond trading bidding deal, covering the bid order and bid reservation. */
typedef struct {
  uint8_t channel_no[2];           /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];         /* bytes 2 to 9 */
  uint8_t md_stream_id[3];         /* bytes 10 to 12 */
  uint8_t security_id[8];          /* bytes 13 to 20 */
  uint8_t security_id_source[4];   /* bytes 21 to 24 */
  uint8_t price[8];                /* bytes 25 to 32 */
  uint8_t order_qty[8];            /* bytes 33 to 40 */
  uint8_t side;                    /* byte 41 */
  uint8_t transac_time[8];         /* bytes 42 to 49 */
  uint8_t member_id[6];            /* bytes 50 to 55 */
  uint8_t investor_type[2];        /* bytes 56 to 57 */
  uint8_t investor_id[10];         /* bytes 58 to 67 */
  uint8_t investor_name[120];      /* bytes 68 to 187 */
  uint8_t trader_code[8];          /* bytes 188 to 195 */
  uint8_t settl_period;            /* byte 196 */
  uint8_t settl_type[2];           /* bytes 197 to 198 */
  uint8_t memo[160];               /* bytes 199 to 358 */
  uint8_t secondary_order_id[16];  /* bytes 359 to 374 */
  uint8_t bid_trans_type[2];       /* bytes 375 to 376 */
  uint8_t bid_exec_inst_type[2];   /* bytes 377 to 378 */
  uint8_t low_limit_price[8];      /* bytes 379 to 386 */
  uint8_t high_limit_price[8];     /* bytes 387 to 394 */
  uint8_t min_qty[8];              /* bytes 395 to 402 */
  uint8_t trade_date[4];           /* bytes 403 to 406 */
} OrderTickDataOfBidQuotationMessage;

/* any Order Tick Data Of Bid Quotation Message at all: every byte one the checker chooses */
static void any_order_tick_data_of_bid_quotation_message(OrderTickDataOfBidQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->investor_type[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->investor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 120; i++) { record->investor_name[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_code[i] = arbitrary(); }
  record->settl_period = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = arbitrary(); }
  for (size_t i = 0; i < 160; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_trans_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_exec_inst_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = arbitrary(); }
}

/* Order Tick Data Of Bid Quotation Message to the wire: 407 bytes from at, returning where the next byte goes */
static size_t encode_order_tick_data_of_bid_quotation_message(const OrderTickDataOfBidQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->member_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->investor_type[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->investor_id[i]; }
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->investor_name[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_code[i]; }
  wire[at++] = record->settl_period;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settl_type[i]; }
  for (size_t i = 0; i < 160; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_trans_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_exec_inst_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_date[i]; }

  return at;
}

/* Order Tick Data Of Bid Quotation Message off the wire: 407 bytes from at, returning where the next byte lies */
static size_t decode_order_tick_data_of_bid_quotation_message(OrderTickDataOfBidQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->investor_type[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->investor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 120; i++) { record->investor_name[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_code[i] = wire[at++]; }
  record->settl_period = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = wire[at++]; }
  for (size_t i = 0; i < 160; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_trans_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_exec_inst_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Tick Data Of Bid Quotation Message is what was written, byte for byte */
static void equal_order_tick_data_of_bid_quotation_message(const OrderTickDataOfBidQuotationMessage *read, const OrderTickDataOfBidQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->member_id[i] == written->member_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->investor_type[i] == written->investor_type[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->investor_id[i] == written->investor_id[i]); }
  for (size_t i = 0; i < 120; i++) { assert(read->investor_name[i] == written->investor_name[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  assert(read->settl_period == written->settl_period);
  for (size_t i = 0; i < 2; i++) { assert(read->settl_type[i] == written->settl_type[i]); }
  for (size_t i = 0; i < 160; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_trans_type[i] == written->bid_trans_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_exec_inst_type[i] == written->bid_exec_inst_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
}

/* Order Tick Data Of Bid Quotation Message: written and read back, then read and written back */
static void check_order_tick_data_of_bid_quotation_message(void) {
  OrderTickDataOfBidQuotationMessage sent;
  OrderTickDataOfBidQuotationMessage got;
  uint8_t wire[407];
  uint8_t again[407];

  any_order_tick_data_of_bid_quotation_message(&sent);
  assert(encode_order_tick_data_of_bid_quotation_message(&sent, wire, 0) == 407);
  assert(decode_order_tick_data_of_bid_quotation_message(&got, wire, 0) == 407);
  equal_order_tick_data_of_bid_quotation_message(&got, &sent);

  for (size_t i = 0; i < 407; i++) { wire[i] = arbitrary(); }
  assert(decode_order_tick_data_of_bid_quotation_message(&got, wire, 0) == 407);
  assert(encode_order_tick_data_of_bid_quotation_message(&got, again, 0) == 407);
  for (size_t i = 0; i < 407; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data In Call Auction Message: 66 bytes ----------------- */

/* Transaction tick carrying market data categories 011 for equities, funds and bonds in the call auction of the spot market, 021 pledge-style repo and 041 call auction in options. The sequence number of tick order and tick transaction data in the same channel is consecutive. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];    /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];  /* bytes 21 to 28 */
  uint8_t security_id[8];         /* bytes 29 to 36 */
  uint8_t security_id_source[4];  /* bytes 37 to 40 */
  uint8_t last_px[8];             /* bytes 41 to 48 */
  uint8_t last_qty[8];            /* bytes 49 to 56 */
  uint8_t exec_type;              /* byte 57 */
  uint8_t transac_time[8];        /* bytes 58 to 65 */
} TransactionTickDataInCallAuctionMessage;

/* any Transaction Tick Data In Call Auction Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_in_call_auction_message(TransactionTickDataInCallAuctionMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
}

/* Transaction Tick Data In Call Auction Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_in_call_auction_message(const TransactionTickDataInCallAuctionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }

  return at;
}

/* Transaction Tick Data In Call Auction Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_in_call_auction_message(TransactionTickDataInCallAuctionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data In Call Auction Message is what was written, byte for byte */
static void equal_transaction_tick_data_in_call_auction_message(const TransactionTickDataInCallAuctionMessage *read, const TransactionTickDataInCallAuctionMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
}

/* Transaction Tick Data In Call Auction Message: written and read back, then read and written back */
static void check_transaction_tick_data_in_call_auction_message(void) {
  TransactionTickDataInCallAuctionMessage sent;
  TransactionTickDataInCallAuctionMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_transaction_tick_data_in_call_auction_message(&sent);
  assert(encode_transaction_tick_data_in_call_auction_message(&sent, wire, 0) == 66);
  assert(decode_transaction_tick_data_in_call_auction_message(&got, wire, 0) == 66);
  equal_transaction_tick_data_in_call_auction_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_in_call_auction_message(&got, wire, 0) == 66);
  assert(encode_transaction_tick_data_in_call_auction_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data Of Negotiable Trade Message: 66 bytes ------------- */

/* Transaction tick carrying market data categories 051 indication of interest of negotiable trade and 052 quote of negotiable trade. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];    /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];  /* bytes 21 to 28 */
  uint8_t security_id[8];         /* bytes 29 to 36 */
  uint8_t security_id_source[4];  /* bytes 37 to 40 */
  uint8_t last_px[8];             /* bytes 41 to 48 */
  uint8_t last_qty[8];            /* bytes 49 to 56 */
  uint8_t exec_type;              /* byte 57 */
  uint8_t transac_time[8];        /* bytes 58 to 65 */
} TransactionTickDataOfNegotiableTradeMessage;

/* any Transaction Tick Data Of Negotiable Trade Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_of_negotiable_trade_message(TransactionTickDataOfNegotiableTradeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
}

/* Transaction Tick Data Of Negotiable Trade Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_of_negotiable_trade_message(const TransactionTickDataOfNegotiableTradeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }

  return at;
}

/* Transaction Tick Data Of Negotiable Trade Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_of_negotiable_trade_message(TransactionTickDataOfNegotiableTradeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data Of Negotiable Trade Message is what was written, byte for byte */
static void equal_transaction_tick_data_of_negotiable_trade_message(const TransactionTickDataOfNegotiableTradeMessage *read, const TransactionTickDataOfNegotiableTradeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
}

/* Transaction Tick Data Of Negotiable Trade Message: written and read back, then read and written back */
static void check_transaction_tick_data_of_negotiable_trade_message(void) {
  TransactionTickDataOfNegotiableTradeMessage sent;
  TransactionTickDataOfNegotiableTradeMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_transaction_tick_data_of_negotiable_trade_message(&sent);
  assert(encode_transaction_tick_data_of_negotiable_trade_message(&sent, wire, 0) == 66);
  assert(decode_transaction_tick_data_of_negotiable_trade_message(&got, wire, 0) == 66);
  equal_transaction_tick_data_of_negotiable_trade_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_of_negotiable_trade_message(&got, wire, 0) == 66);
  assert(encode_transaction_tick_data_of_negotiable_trade_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data Of Security Lending Message: 66 bytes ------------- */

/* Transaction tick carrying market data category 071, security lending. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];    /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];  /* bytes 21 to 28 */
  uint8_t security_id[8];         /* bytes 29 to 36 */
  uint8_t security_id_source[4];  /* bytes 37 to 40 */
  uint8_t last_px[8];             /* bytes 41 to 48 */
  uint8_t last_qty[8];            /* bytes 49 to 56 */
  uint8_t exec_type;              /* byte 57 */
  uint8_t transac_time[8];        /* bytes 58 to 65 */
} TransactionTickDataOfSecurityLendingMessage;

/* any Transaction Tick Data Of Security Lending Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_of_security_lending_message(TransactionTickDataOfSecurityLendingMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
}

/* Transaction Tick Data Of Security Lending Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_of_security_lending_message(const TransactionTickDataOfSecurityLendingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }

  return at;
}

/* Transaction Tick Data Of Security Lending Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_of_security_lending_message(TransactionTickDataOfSecurityLendingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data Of Security Lending Message is what was written, byte for byte */
static void equal_transaction_tick_data_of_security_lending_message(const TransactionTickDataOfSecurityLendingMessage *read, const TransactionTickDataOfSecurityLendingMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
}

/* Transaction Tick Data Of Security Lending Message: written and read back, then read and written back */
static void check_transaction_tick_data_of_security_lending_message(void) {
  TransactionTickDataOfSecurityLendingMessage sent;
  TransactionTickDataOfSecurityLendingMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_transaction_tick_data_of_security_lending_message(&sent);
  assert(encode_transaction_tick_data_of_security_lending_message(&sent, wire, 0) == 66);
  assert(decode_transaction_tick_data_of_security_lending_message(&got, wire, 0) == 66);
  equal_transaction_tick_data_of_security_lending_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_of_security_lending_message(&got, wire, 0) == 66);
  assert(encode_transaction_tick_data_of_security_lending_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data Of Bond General Pledged Repo Message: 66 bytes ---- */

/* Transaction tick carrying market data categories 021 bond general pledged repo matching deal and 411 spot bond trading matching deal. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];    /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];  /* bytes 21 to 28 */
  uint8_t security_id[8];         /* bytes 29 to 36 */
  uint8_t security_id_source[4];  /* bytes 37 to 40 */
  uint8_t last_px[8];             /* bytes 41 to 48 */
  uint8_t last_qty[8];            /* bytes 49 to 56 */
  uint8_t exec_type;              /* byte 57 */
  uint8_t transac_time[8];        /* bytes 58 to 65 */
} TransactionTickDataOfBondGeneralPledgedRepoMessage;

/* any Transaction Tick Data Of Bond General Pledged Repo Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_of_bond_general_pledged_repo_message(TransactionTickDataOfBondGeneralPledgedRepoMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
}

/* Transaction Tick Data Of Bond General Pledged Repo Message to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_of_bond_general_pledged_repo_message(const TransactionTickDataOfBondGeneralPledgedRepoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }

  return at;
}

/* Transaction Tick Data Of Bond General Pledged Repo Message off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_of_bond_general_pledged_repo_message(TransactionTickDataOfBondGeneralPledgedRepoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data Of Bond General Pledged Repo Message is what was written, byte for byte */
static void equal_transaction_tick_data_of_bond_general_pledged_repo_message(const TransactionTickDataOfBondGeneralPledgedRepoMessage *read, const TransactionTickDataOfBondGeneralPledgedRepoMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
}

/* Transaction Tick Data Of Bond General Pledged Repo Message: written and read back, then read and written back */
static void check_transaction_tick_data_of_bond_general_pledged_repo_message(void) {
  TransactionTickDataOfBondGeneralPledgedRepoMessage sent;
  TransactionTickDataOfBondGeneralPledgedRepoMessage got;
  uint8_t wire[66];
  uint8_t again[66];

  any_transaction_tick_data_of_bond_general_pledged_repo_message(&sent);
  assert(encode_transaction_tick_data_of_bond_general_pledged_repo_message(&sent, wire, 0) == 66);
  assert(decode_transaction_tick_data_of_bond_general_pledged_repo_message(&got, wire, 0) == 66);
  equal_transaction_tick_data_of_bond_general_pledged_repo_message(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_of_bond_general_pledged_repo_message(&got, wire, 0) == 66);
  assert(encode_transaction_tick_data_of_bond_general_pledged_repo_message(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data Of Spot Bond Trading Quotation Message: 69 bytes ---- */

/* Transaction tick carrying market data categories 412 spot bond trading negotiated deal, 413 click deal, 414 inquiry deal and 417 large amount matching deal, for spot bond trading other than bid. */
typedef struct {
  uint8_t channel_no[2];          /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];        /* bytes 2 to 9 */
  uint8_t md_stream_id[3];        /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];    /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];  /* bytes 21 to 28 */
  uint8_t security_id[8];         /* bytes 29 to 36 */
  uint8_t security_id_source[4];  /* bytes 37 to 40 */
  uint8_t last_px[8];             /* bytes 41 to 48 */
  uint8_t last_qty[8];            /* bytes 49 to 56 */
  uint8_t exec_type;              /* byte 57 */
  uint8_t transac_time[8];        /* bytes 58 to 65 */
  uint8_t settl_period;           /* byte 66 */
  uint8_t settl_type[2];          /* bytes 67 to 68 */
} TransactionTickDataOfSpotBondTradingQuotationMessage;

/* any Transaction Tick Data Of Spot Bond Trading Quotation Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_of_spot_bond_trading_quotation_message(TransactionTickDataOfSpotBondTradingQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  record->settl_period = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = arbitrary(); }
}

/* Transaction Tick Data Of Spot Bond Trading Quotation Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_of_spot_bond_trading_quotation_message(const TransactionTickDataOfSpotBondTradingQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  wire[at++] = record->settl_period;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settl_type[i]; }

  return at;
}

/* Transaction Tick Data Of Spot Bond Trading Quotation Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_of_spot_bond_trading_quotation_message(TransactionTickDataOfSpotBondTradingQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  record->settl_period = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data Of Spot Bond Trading Quotation Message is what was written, byte for byte */
static void equal_transaction_tick_data_of_spot_bond_trading_quotation_message(const TransactionTickDataOfSpotBondTradingQuotationMessage *read, const TransactionTickDataOfSpotBondTradingQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  assert(read->settl_period == written->settl_period);
  for (size_t i = 0; i < 2; i++) { assert(read->settl_type[i] == written->settl_type[i]); }
}

/* Transaction Tick Data Of Spot Bond Trading Quotation Message: written and read back, then read and written back */
static void check_transaction_tick_data_of_spot_bond_trading_quotation_message(void) {
  TransactionTickDataOfSpotBondTradingQuotationMessage sent;
  TransactionTickDataOfSpotBondTradingQuotationMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_transaction_tick_data_of_spot_bond_trading_quotation_message(&sent);
  assert(encode_transaction_tick_data_of_spot_bond_trading_quotation_message(&sent, wire, 0) == 69);
  assert(decode_transaction_tick_data_of_spot_bond_trading_quotation_message(&got, wire, 0) == 69);
  equal_transaction_tick_data_of_spot_bond_trading_quotation_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_of_spot_bond_trading_quotation_message(&got, wire, 0) == 69);
  assert(encode_transaction_tick_data_of_spot_bond_trading_quotation_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transaction Tick Data Of Bid Quotation Message: 95 bytes ---------------- */

/* Transaction tick carrying market data category 416, spot bond trading bidding deal. */
typedef struct {
  uint8_t channel_no[2];           /* bytes 0 to 1 */
  uint8_t appl_seq_num[8];         /* bytes 2 to 9 */
  uint8_t md_stream_id[3];         /* bytes 10 to 12 */
  uint8_t bid_appl_seq_num[8];     /* bytes 13 to 20 */
  uint8_t offer_appl_seq_num[8];   /* bytes 21 to 28 */
  uint8_t security_id[8];          /* bytes 29 to 36 */
  uint8_t security_id_source[4];   /* bytes 37 to 40 */
  uint8_t last_px[8];              /* bytes 41 to 48 */
  uint8_t last_qty[8];             /* bytes 49 to 56 */
  uint8_t exec_type;               /* byte 57 */
  uint8_t transac_time[8];         /* bytes 58 to 65 */
  uint8_t settl_period;            /* byte 66 */
  uint8_t settl_type[2];           /* bytes 67 to 68 */
  uint8_t secondary_order_id[16];  /* bytes 69 to 84 */
  uint8_t bid_exec_inst_type[2];   /* bytes 85 to 86 */
  uint8_t margin_price[8];         /* bytes 87 to 94 */
} TransactionTickDataOfBidQuotationMessage;

/* any Transaction Tick Data Of Bid Quotation Message at all: every byte one the checker chooses */
static void any_transaction_tick_data_of_bid_quotation_message(TransactionTickDataOfBidQuotationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = arbitrary(); }
  record->settl_period = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_exec_inst_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->margin_price[i] = arbitrary(); }
}

/* Transaction Tick Data Of Bid Quotation Message to the wire: 95 bytes from at, returning where the next byte goes */
static size_t encode_transaction_tick_data_of_bid_quotation_message(const TransactionTickDataOfBidQuotationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->channel_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->appl_seq_num[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->md_stream_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->offer_appl_seq_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transac_time[i]; }
  wire[at++] = record->settl_period;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->settl_type[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_exec_inst_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->margin_price[i]; }

  return at;
}

/* Transaction Tick Data Of Bid Quotation Message off the wire: 95 bytes from at, returning where the next byte lies */
static size_t decode_transaction_tick_data_of_bid_quotation_message(TransactionTickDataOfBidQuotationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->channel_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->md_stream_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->offer_appl_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transac_time[i] = wire[at++]; }
  record->settl_period = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->settl_type[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_exec_inst_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->margin_price[i] = wire[at++]; }

  return at;
}

/* what was read of Transaction Tick Data Of Bid Quotation Message is what was written, byte for byte */
static void equal_transaction_tick_data_of_bid_quotation_message(const TransactionTickDataOfBidQuotationMessage *read, const TransactionTickDataOfBidQuotationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->channel_no[i] == written->channel_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->appl_seq_num[i] == written->appl_seq_num[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->md_stream_id[i] == written->md_stream_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_appl_seq_num[i] == written->bid_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->offer_appl_seq_num[i] == written->offer_appl_seq_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 8; i++) { assert(read->transac_time[i] == written->transac_time[i]); }
  assert(read->settl_period == written->settl_period);
  for (size_t i = 0; i < 2; i++) { assert(read->settl_type[i] == written->settl_type[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_exec_inst_type[i] == written->bid_exec_inst_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->margin_price[i] == written->margin_price[i]); }
}

/* Transaction Tick Data Of Bid Quotation Message: written and read back, then read and written back */
static void check_transaction_tick_data_of_bid_quotation_message(void) {
  TransactionTickDataOfBidQuotationMessage sent;
  TransactionTickDataOfBidQuotationMessage got;
  uint8_t wire[95];
  uint8_t again[95];

  any_transaction_tick_data_of_bid_quotation_message(&sent);
  assert(encode_transaction_tick_data_of_bid_quotation_message(&sent, wire, 0) == 95);
  assert(decode_transaction_tick_data_of_bid_quotation_message(&got, wire, 0) == 95);
  equal_transaction_tick_data_of_bid_quotation_message(&got, &sent);

  for (size_t i = 0; i < 95; i++) { wire[i] = arbitrary(); }
  assert(decode_transaction_tick_data_of_bid_quotation_message(&got, wire, 0) == 95);
  assert(encode_transaction_tick_data_of_bid_quotation_message(&got, again, 0) == 95);
  for (size_t i = 0; i < 95; i++) { assert(again[i] == wire[i]); }
}

/* ---- Packet Trailer: 4 bytes ------------------------------------------------- */

/* Szse Mddp Packet Trailer, transmitted without encryption */
typedef struct {
  uint8_t checksum[4];  /* bytes 0 to 3 */
} PacketTrailer;

/* any Packet Trailer at all: every byte one the checker chooses */
static void any_packet_trailer(PacketTrailer *record) {
  for (size_t i = 0; i < 4; i++) { record->checksum[i] = arbitrary(); }
}

/* Packet Trailer to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_packet_trailer(const PacketTrailer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->checksum[i]; }

  return at;
}

/* Packet Trailer off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_packet_trailer(PacketTrailer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->checksum[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Trailer is what was written, byte for byte */
static void equal_packet_trailer(const PacketTrailer *read, const PacketTrailer *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->checksum[i] == written->checksum[i]); }
}

/* Packet Trailer: written and read back, then read and written back */
static void check_packet_trailer(void) {
  PacketTrailer sent;
  PacketTrailer got;
  uint8_t wire[4];
  uint8_t again[4];

  any_packet_trailer(&sent);
  assert(encode_packet_trailer(&sent, wire, 0) == 4);
  assert(decode_packet_trailer(&got, wire, 0) == 4);
  equal_packet_trailer(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_trailer(&got, wire, 0) == 4);
  assert(encode_packet_trailer(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_channel_heartbeat_message();
  check_retransmitting_message();
  check_client_user_information_reporting_message();
  check_business_reject_message();
  check_real_time_market_status_message();
  check_statistic_indicator_snapshot_message();
  check_order_tick_data_in_call_auction_message();
  check_order_tick_data_of_negotiable_trade_message();
  check_order_tick_data_of_security_lending_message();
  check_order_tick_data_of_spot_bond_trading_matching_deal_message();
  check_order_tick_data_of_spot_bond_trading_quotation_message();
  check_order_tick_data_of_bid_quotation_message();
  check_transaction_tick_data_in_call_auction_message();
  check_transaction_tick_data_of_negotiable_trade_message();
  check_transaction_tick_data_of_security_lending_message();
  check_transaction_tick_data_of_bond_general_pledged_repo_message();
  check_transaction_tick_data_of_spot_bond_trading_quotation_message();
  check_transaction_tick_data_of_bid_quotation_message();
  check_packet_trailer();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
