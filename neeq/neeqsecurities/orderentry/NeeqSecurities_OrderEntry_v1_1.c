// neeq/neeqsecurities/orderentry/NeeqSecurities_OrderEntry_v1_1.c
/*
 * National Equities Exchange and Quotations Neeq Order Entry
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
 *   - a Integrity rule
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

/* Bjse Bjtg Message Header, defining the type and body length of a message, transmitted without encryption */
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

/* The first message the order management system sends to the trading gateway, which confirms a successful logon with a Logon of its own, so both sides transmit this message type. */
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

/* Sent by the trading gateway to refuse a logon, and by either side to end the session; the receiver answers with a Logout of its own, so both sides transmit this message type. */
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

/* ---- Business Reject Message: 103 bytes -------------------------------------- */

/* Sent by the trading gateway when a submission fails a basic validity check, such as an unknown security code or a submission outside its time window. */
typedef struct {
  uint8_t appl_id[3];                  /* bytes 0 to 2 */
  uint8_t transact_time[8];            /* bytes 3 to 10 */
  uint8_t submitting_pbuid[6];         /* bytes 11 to 16 */
  uint8_t security_id[8];              /* bytes 17 to 24 */
  uint8_t security_id_source[4];       /* bytes 25 to 28 */
  uint8_t ref_seq_num[8];              /* bytes 29 to 36 */
  uint8_t ref_msg_type[4];             /* bytes 37 to 40 */
  uint8_t business_reject_ref_id[10];  /* bytes 41 to 50 */
  uint8_t business_reject_reason[2];   /* bytes 51 to 52 */
  uint8_t business_reject_text[50];    /* bytes 53 to 102 */
} BusinessRejectMessage;

/* any Business Reject Message at all: every byte one the checker chooses */
static void any_business_reject_message(BusinessRejectMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ref_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ref_msg_type[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->business_reject_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->business_reject_text[i] = arbitrary(); }
}

/* Business Reject Message to the wire: 103 bytes from at, returning where the next byte goes */
static size_t encode_business_reject_message(const BusinessRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ref_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_msg_type[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->business_reject_ref_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->business_reject_reason[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->business_reject_text[i]; }

  return at;
}

/* Business Reject Message off the wire: 103 bytes from at, returning where the next byte lies */
static size_t decode_business_reject_message(BusinessRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ref_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ref_msg_type[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->business_reject_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->business_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->business_reject_text[i] = wire[at++]; }

  return at;
}

/* what was read of Business Reject Message is what was written, byte for byte */
static void equal_business_reject_message(const BusinessRejectMessage *read, const BusinessRejectMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
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
  uint8_t wire[103];
  uint8_t again[103];

  any_business_reject_message(&sent);
  assert(encode_business_reject_message(&sent, wire, 0) == 103);
  assert(decode_business_reject_message(&got, wire, 0) == 103);
  equal_business_reject_message(&got, &sent);

  for (size_t i = 0; i < 103; i++) { wire[i] = arbitrary(); }
  assert(decode_business_reject_message(&got, wire, 0) == 103);
  assert(encode_business_reject_message(&got, again, 0) == 103);
  for (size_t i = 0; i < 103; i++) { assert(again[i] == wire[i]); }
}

/* ---- Platform State Info Message: 4 bytes ------------------------------------ */

/* Sent by the trading gateway after logon and whenever a platform changes state, so the order management system can control when it submits orders. */
typedef struct {
  uint8_t platform_id[2];     /* bytes 0 to 1 */
  uint8_t platform_state[2];  /* bytes 2 to 3 */
} PlatformStateInfoMessage;

/* any Platform State Info Message at all: every byte one the checker chooses */
static void any_platform_state_info_message(PlatformStateInfoMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->platform_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->platform_state[i] = arbitrary(); }
}

/* Platform State Info Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_platform_state_info_message(const PlatformStateInfoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->platform_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->platform_state[i]; }

  return at;
}

/* Platform State Info Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_platform_state_info_message(PlatformStateInfoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->platform_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->platform_state[i] = wire[at++]; }

  return at;
}

/* what was read of Platform State Info Message is what was written, byte for byte */
static void equal_platform_state_info_message(const PlatformStateInfoMessage *read, const PlatformStateInfoMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->platform_id[i] == written->platform_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->platform_state[i] == written->platform_state[i]); }
}

/* Platform State Info Message: written and read back, then read and written back */
static void check_platform_state_info_message(void) {
  PlatformStateInfoMessage sent;
  PlatformStateInfoMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_platform_state_info_message(&sent);
  assert(encode_platform_state_info_message(&sent, wire, 0) == 4);
  assert(decode_platform_state_info_message(&got, wire, 0) == 4);
  equal_platform_state_info_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_platform_state_info_message(&got, wire, 0) == 4);
  assert(encode_platform_state_info_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Report Finished Message: 14 bytes --------------------------------------- */

/* Sent by the trading gateway when every report of the trading day for a platform partition has been sent; its record number continues the numbering of the partition's reports. */
typedef struct {
  uint8_t partition_no[4];  /* bytes 0 to 3 */
  uint8_t report_index[8];  /* bytes 4 to 11 */
  uint8_t platform_id[2];   /* bytes 12 to 13 */
} ReportFinishedMessage;

/* any Report Finished Message at all: every byte one the checker chooses */
static void any_report_finished_message(ReportFinishedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->platform_id[i] = arbitrary(); }
}

/* Report Finished Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_report_finished_message(const ReportFinishedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->platform_id[i]; }

  return at;
}

/* Report Finished Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_report_finished_message(ReportFinishedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->platform_id[i] = wire[at++]; }

  return at;
}

/* what was read of Report Finished Message is what was written, byte for byte */
static void equal_report_finished_message(const ReportFinishedMessage *read, const ReportFinishedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->platform_id[i] == written->platform_id[i]); }
}

/* Report Finished Message: written and read back, then read and written back */
static void check_report_finished_message(void) {
  ReportFinishedMessage sent;
  ReportFinishedMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_report_finished_message(&sent);
  assert(encode_report_finished_message(&sent, wire, 0) == 14);
  assert(decode_report_finished_message(&got, wire, 0) == 14);
  equal_report_finished_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_report_finished_message(&got, wire, 0) == 14);
  assert(encode_report_finished_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 42 bytes -------------------------------- */

/* Sent by the trading gateway after logon and whenever the trading session of the connected platform changes; only the fixed income platform currently sends it. */
typedef struct {
  uint8_t market_id[8];               /* bytes 0 to 7 */
  uint8_t market_segment_id[8];       /* bytes 8 to 15 */
  uint8_t trading_session_id[4];      /* bytes 16 to 19 */
  uint8_t trading_session_sub_id[4];  /* bytes 20 to 23 */
  uint8_t trad_ses_status[2];         /* bytes 24 to 25 */
  uint8_t trad_ses_start_time[8];     /* bytes 26 to 33 */
  uint8_t trad_ses_end_time[8];       /* bytes 34 to 41 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trad_ses_status[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_start_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_end_time[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_sub_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trad_ses_status[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_start_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trad_ses_end_time[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trad_ses_status[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_start_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trad_ses_end_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_id[i] == written->trading_session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_sub_id[i] == written->trading_session_sub_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trad_ses_status[i] == written->trad_ses_status[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_start_time[i] == written->trad_ses_start_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trad_ses_end_time[i] == written->trad_ses_end_time[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 42);
  assert(decode_trading_session_status_message(&got, wire, 0) == 42);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 42);
  assert(encode_trading_session_status_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Matching New Order Message: 131 bytes ------------------------- */

/* New order for spot bond trading by matching, ApplID 010. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
  uint8_t stop_px[8];             /* bytes 109 to 116 */
  uint8_t min_qty[8];             /* bytes 117 to 124 */
  uint8_t max_price_levels[2];    /* bytes 125 to 126 */
  uint8_t time_in_force;          /* byte 127 */
  uint8_t cash_margin;            /* byte 128 */
  uint8_t settl_type;             /* byte 129 */
  uint8_t settl_period;           /* byte 130 */
} BondSpotMatchingNewOrderMessage;

/* any Bond Spot Matching New Order Message at all: every byte one the checker chooses */
static void any_bond_spot_matching_new_order_message(BondSpotMatchingNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->cash_margin = arbitrary();
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
}

/* Bond Spot Matching New Order Message to the wire: 131 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_matching_new_order_message(const BondSpotMatchingNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_price_levels[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->cash_margin;
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;

  return at;
}

/* Bond Spot Matching New Order Message off the wire: 131 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_matching_new_order_message(BondSpotMatchingNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->cash_margin = wire[at++];
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];

  return at;
}

/* what was read of Bond Spot Matching New Order Message is what was written, byte for byte */
static void equal_bond_spot_matching_new_order_message(const BondSpotMatchingNewOrderMessage *read, const BondSpotMatchingNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->max_price_levels[i] == written->max_price_levels[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->cash_margin == written->cash_margin);
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
}

/* Bond Spot Matching New Order Message: written and read back, then read and written back */
static void check_bond_spot_matching_new_order_message(void) {
  BondSpotMatchingNewOrderMessage sent;
  BondSpotMatchingNewOrderMessage got;
  uint8_t wire[131];
  uint8_t again[131];

  any_bond_spot_matching_new_order_message(&sent);
  assert(encode_bond_spot_matching_new_order_message(&sent, wire, 0) == 131);
  assert(decode_bond_spot_matching_new_order_message(&got, wire, 0) == 131);
  equal_bond_spot_matching_new_order_message(&got, &sent);

  for (size_t i = 0; i < 131; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_matching_new_order_message(&got, wire, 0) == 131);
  assert(encode_bond_spot_matching_new_order_message(&got, again, 0) == 131);
  for (size_t i = 0; i < 131; i++) { assert(again[i] == wire[i]); }
}

/* ---- Centralized Auction New Order Message: 129 bytes ------------------------ */

/* New order for centralized auction stock trading, ApplID 040. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
  uint8_t stop_px[8];             /* bytes 109 to 116 */
  uint8_t min_qty[8];             /* bytes 117 to 124 */
  uint8_t max_price_levels[2];    /* bytes 125 to 126 */
  uint8_t time_in_force;          /* byte 127 */
  uint8_t cash_margin;            /* byte 128 */
} CentralizedAuctionNewOrderMessage;

/* any Centralized Auction New Order Message at all: every byte one the checker chooses */
static void any_centralized_auction_new_order_message(CentralizedAuctionNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->cash_margin = arbitrary();
}

/* Centralized Auction New Order Message to the wire: 129 bytes from at, returning where the next byte goes */
static size_t encode_centralized_auction_new_order_message(const CentralizedAuctionNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_price_levels[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->cash_margin;

  return at;
}

/* Centralized Auction New Order Message off the wire: 129 bytes from at, returning where the next byte lies */
static size_t decode_centralized_auction_new_order_message(CentralizedAuctionNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of Centralized Auction New Order Message is what was written, byte for byte */
static void equal_centralized_auction_new_order_message(const CentralizedAuctionNewOrderMessage *read, const CentralizedAuctionNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->max_price_levels[i] == written->max_price_levels[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->cash_margin == written->cash_margin);
}

/* Centralized Auction New Order Message: written and read back, then read and written back */
static void check_centralized_auction_new_order_message(void) {
  CentralizedAuctionNewOrderMessage sent;
  CentralizedAuctionNewOrderMessage got;
  uint8_t wire[129];
  uint8_t again[129];

  any_centralized_auction_new_order_message(&sent);
  assert(encode_centralized_auction_new_order_message(&sent, wire, 0) == 129);
  assert(decode_centralized_auction_new_order_message(&got, wire, 0) == 129);
  equal_centralized_auction_new_order_message(&got, &sent);

  for (size_t i = 0; i < 129; i++) { wire[i] = arbitrary(); }
  assert(decode_centralized_auction_new_order_message(&got, wire, 0) == 129);
  assert(encode_centralized_auction_new_order_message(&got, again, 0) == 129);
  for (size_t i = 0; i < 129; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conversion New Order Message: 109 bytes --------------------------------- */

/* New order for conversion, ApplID 041. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
} ConversionNewOrderMessage;

/* any Conversion New Order Message at all: every byte one the checker chooses */
static void any_conversion_new_order_message(ConversionNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Conversion New Order Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_conversion_new_order_message(const ConversionNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Conversion New Order Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_conversion_new_order_message(ConversionNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Conversion New Order Message is what was written, byte for byte */
static void equal_conversion_new_order_message(const ConversionNewOrderMessage *read, const ConversionNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Conversion New Order Message: written and read back, then read and written back */
static void check_conversion_new_order_message(void) {
  ConversionNewOrderMessage sent;
  ConversionNewOrderMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_conversion_new_order_message(&sent);
  assert(encode_conversion_new_order_message(&sent, wire, 0) == 109);
  assert(decode_conversion_new_order_message(&got, wire, 0) == 109);
  equal_conversion_new_order_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_conversion_new_order_message(&got, wire, 0) == 109);
  assert(encode_conversion_new_order_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inquiry New Order Message: 109 bytes ------------------------------------ */

/* New order for inquiry, ApplID 042. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
} InquiryNewOrderMessage;

/* any Inquiry New Order Message at all: every byte one the checker chooses */
static void any_inquiry_new_order_message(InquiryNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Inquiry New Order Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_inquiry_new_order_message(const InquiryNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Inquiry New Order Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_inquiry_new_order_message(InquiryNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Inquiry New Order Message is what was written, byte for byte */
static void equal_inquiry_new_order_message(const InquiryNewOrderMessage *read, const InquiryNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Inquiry New Order Message: written and read back, then read and written back */
static void check_inquiry_new_order_message(void) {
  InquiryNewOrderMessage sent;
  InquiryNewOrderMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_inquiry_new_order_message(&sent);
  assert(encode_inquiry_new_order_message(&sent, wire, 0) == 109);
  assert(decode_inquiry_new_order_message(&got, wire, 0) == 109);
  equal_inquiry_new_order_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_inquiry_new_order_message(&got, wire, 0) == 109);
  assert(encode_inquiry_new_order_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription New Order Message: 109 bytes ------------------------------- */

/* New order for subscription, ApplID 043. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
} SubscriptionNewOrderMessage;

/* any Subscription New Order Message at all: every byte one the checker chooses */
static void any_subscription_new_order_message(SubscriptionNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Subscription New Order Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_subscription_new_order_message(const SubscriptionNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Subscription New Order Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_subscription_new_order_message(SubscriptionNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Subscription New Order Message is what was written, byte for byte */
static void equal_subscription_new_order_message(const SubscriptionNewOrderMessage *read, const SubscriptionNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Subscription New Order Message: written and read back, then read and written back */
static void check_subscription_new_order_message(void) {
  SubscriptionNewOrderMessage sent;
  SubscriptionNewOrderMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_subscription_new_order_message(&sent);
  assert(encode_subscription_new_order_message(&sent, wire, 0) == 109);
  assert(decode_subscription_new_order_message(&got, wire, 0) == 109);
  equal_subscription_new_order_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_new_order_message(&got, wire, 0) == 109);
  assert(encode_subscription_new_order_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Put Back New Order Message: 109 bytes ----------------------------------- */

/* New order for put back, ApplID 044. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
} PutBackNewOrderMessage;

/* any Put Back New Order Message at all: every byte one the checker chooses */
static void any_put_back_new_order_message(PutBackNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Put Back New Order Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_put_back_new_order_message(const PutBackNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Put Back New Order Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_put_back_new_order_message(PutBackNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Put Back New Order Message is what was written, byte for byte */
static void equal_put_back_new_order_message(const PutBackNewOrderMessage *read, const PutBackNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Put Back New Order Message: written and read back, then read and written back */
static void check_put_back_new_order_message(void) {
  PutBackNewOrderMessage sent;
  PutBackNewOrderMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_put_back_new_order_message(&sent);
  assert(encode_put_back_new_order_message(&sent, wire, 0) == 109);
  assert(decode_put_back_new_order_message(&got, wire, 0) == 109);
  equal_put_back_new_order_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_put_back_new_order_message(&got, wire, 0) == 109);
  assert(encode_put_back_new_order_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tender Offer Acceptance New Order Message: 109 bytes -------------------- */

/* New order for tender offer acceptance, ApplID 045. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
} TenderOfferAcceptanceNewOrderMessage;

/* any Tender Offer Acceptance New Order Message at all: every byte one the checker chooses */
static void any_tender_offer_acceptance_new_order_message(TenderOfferAcceptanceNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Tender Offer Acceptance New Order Message to the wire: 109 bytes from at, returning where the next byte goes */
static size_t encode_tender_offer_acceptance_new_order_message(const TenderOfferAcceptanceNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Tender Offer Acceptance New Order Message off the wire: 109 bytes from at, returning where the next byte lies */
static size_t decode_tender_offer_acceptance_new_order_message(TenderOfferAcceptanceNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Tender Offer Acceptance New Order Message is what was written, byte for byte */
static void equal_tender_offer_acceptance_new_order_message(const TenderOfferAcceptanceNewOrderMessage *read, const TenderOfferAcceptanceNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Tender Offer Acceptance New Order Message: written and read back, then read and written back */
static void check_tender_offer_acceptance_new_order_message(void) {
  TenderOfferAcceptanceNewOrderMessage sent;
  TenderOfferAcceptanceNewOrderMessage got;
  uint8_t wire[109];
  uint8_t again[109];

  any_tender_offer_acceptance_new_order_message(&sent);
  assert(encode_tender_offer_acceptance_new_order_message(&sent, wire, 0) == 109);
  assert(decode_tender_offer_acceptance_new_order_message(&got, wire, 0) == 109);
  equal_tender_offer_acceptance_new_order_message(&got, &sent);

  for (size_t i = 0; i < 109; i++) { wire[i] = arbitrary(); }
  assert(decode_tender_offer_acceptance_new_order_message(&got, wire, 0) == 109);
  assert(encode_tender_offer_acceptance_new_order_message(&got, again, 0) == 109);
  for (size_t i = 0; i < 109; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Non Agreed New Order Message: 114 bytes ---- */

/* New order for refinancing securities lending without agreement, ApplID 050. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t account_id[10];         /* bytes 75 to 84 */
  uint8_t branch_id[2];           /* bytes 85 to 86 */
  uint8_t order_restrictions[4];  /* bytes 87 to 90 */
  uint8_t side;                   /* byte 91 */
  uint8_t ord_type;               /* byte 92 */
  uint8_t order_qty[8];           /* bytes 93 to 100 */
  uint8_t price[8];               /* bytes 101 to 108 */
  uint8_t expiration_days[2];     /* bytes 109 to 110 */
  uint8_t expiration_type;        /* byte 111 */
  uint8_t share_property[2];      /* bytes 112 to 113 */
} RefinancingSecuritiesLendingNonAgreedNewOrderMessage;

/* any Refinancing Securities Lending Non Agreed New Order Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_non_agreed_new_order_message(RefinancingSecuritiesLendingNonAgreedNewOrderMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Non Agreed New Order Message to the wire: 114 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_non_agreed_new_order_message(const RefinancingSecuritiesLendingNonAgreedNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Non Agreed New Order Message off the wire: 114 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_non_agreed_new_order_message(RefinancingSecuritiesLendingNonAgreedNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Non Agreed New Order Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_non_agreed_new_order_message(const RefinancingSecuritiesLendingNonAgreedNewOrderMessage *read, const RefinancingSecuritiesLendingNonAgreedNewOrderMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Non Agreed New Order Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_non_agreed_new_order_message(void) {
  RefinancingSecuritiesLendingNonAgreedNewOrderMessage sent;
  RefinancingSecuritiesLendingNonAgreedNewOrderMessage got;
  uint8_t wire[114];
  uint8_t again[114];

  any_refinancing_securities_lending_non_agreed_new_order_message(&sent);
  assert(encode_refinancing_securities_lending_non_agreed_new_order_message(&sent, wire, 0) == 114);
  assert(decode_refinancing_securities_lending_non_agreed_new_order_message(&got, wire, 0) == 114);
  equal_refinancing_securities_lending_non_agreed_new_order_message(&got, &sent);

  for (size_t i = 0; i < 114; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_non_agreed_new_order_message(&got, wire, 0) == 114);
  assert(encode_refinancing_securities_lending_non_agreed_new_order_message(&got, again, 0) == 114);
  for (size_t i = 0; i < 114; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Request Message: 121 bytes --------------------------------- */

/* Cancels an order; the exchange does not check the original order quantity it carries. */
typedef struct {
  uint8_t appl_id[3];             /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];    /* bytes 3 to 8 */
  uint8_t security_id[8];         /* bytes 9 to 16 */
  uint8_t security_id_source[4];  /* bytes 17 to 20 */
  uint8_t owner_type[2];          /* bytes 21 to 22 */
  uint8_t clearing_firm[2];       /* bytes 23 to 24 */
  uint8_t transact_time[8];       /* bytes 25 to 32 */
  uint8_t user_info[32];          /* bytes 33 to 64 */
  uint8_t cl_ord_id[10];          /* bytes 65 to 74 */
  uint8_t orig_cl_ord_id[10];     /* bytes 75 to 84 */
  uint8_t account_id[10];         /* bytes 85 to 94 */
  uint8_t branch_id[2];           /* bytes 95 to 96 */
  uint8_t order_id[16];           /* bytes 97 to 112 */
  uint8_t order_qty[8];           /* bytes 113 to 120 */
} OrderCancelRequestMessage;

/* any Order Cancel Request Message at all: every byte one the checker chooses */
static void any_order_cancel_request_message(OrderCancelRequestMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
}

/* Order Cancel Request Message to the wire: 121 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_request_message(const OrderCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }

  return at;
}

/* Order Cancel Request Message off the wire: 121 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_request_message(OrderCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Request Message is what was written, byte for byte */
static void equal_order_cancel_request_message(const OrderCancelRequestMessage *read, const OrderCancelRequestMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
}

/* Order Cancel Request Message: written and read back, then read and written back */
static void check_order_cancel_request_message(void) {
  OrderCancelRequestMessage sent;
  OrderCancelRequestMessage got;
  uint8_t wire[121];
  uint8_t again[121];

  any_order_cancel_request_message(&sent);
  assert(encode_order_cancel_request_message(&sent, wire, 0) == 121);
  assert(decode_order_cancel_request_message(&got, wire, 0) == 121);
  equal_order_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 121; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_request_message(&got, wire, 0) == 121);
  assert(encode_order_cancel_request_message(&got, again, 0) == 121);
  for (size_t i = 0; i < 121; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Reject Message: 150 bytes ---------------------------------------- */

/* Sent by the trading gateway when an order cancel request fails. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t cl_ord_id[10];          /* bytes 83 to 92 */
  uint8_t orig_cl_ord_id[10];     /* bytes 93 to 102 */
  uint8_t account_id[10];         /* bytes 103 to 112 */
  uint8_t branch_id[2];           /* bytes 113 to 114 */
  uint8_t ord_status;             /* byte 115 */
  uint8_t cxl_rej_reason[2];      /* bytes 116 to 117 */
  uint8_t reject_text[16];        /* bytes 118 to 133 */
  uint8_t order_id[16];           /* bytes 134 to 149 */
} CancelRejectMessage;

/* any Cancel Reject Message at all: every byte one the checker chooses */
static void any_cancel_reject_message(CancelRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
}

/* Cancel Reject Message to the wire: 150 bytes from at, returning where the next byte goes */
static size_t encode_cancel_reject_message(const CancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->cxl_rej_reason[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reject_text[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Cancel Reject Message off the wire: 150 bytes from at, returning where the next byte lies */
static size_t decode_cancel_reject_message(CancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->cxl_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reject_text[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Reject Message is what was written, byte for byte */
static void equal_cancel_reject_message(const CancelRejectMessage *read, const CancelRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->cxl_rej_reason[i] == written->cxl_rej_reason[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reject_text[i] == written->reject_text[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Cancel Reject Message: written and read back, then read and written back */
static void check_cancel_reject_message(void) {
  CancelRejectMessage sent;
  CancelRejectMessage got;
  uint8_t wire[150];
  uint8_t again[150];

  any_cancel_reject_message(&sent);
  assert(encode_cancel_reject_message(&sent, wire, 0) == 150);
  assert(decode_cancel_reject_message(&got, wire, 0) == 150);
  equal_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 150; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_reject_message(&got, wire, 0) == 150);
  assert(encode_cancel_reject_message(&got, again, 0) == 150);
  for (size_t i = 0; i < 150; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Matching Execution Report Message: 209 bytes ------------------ */

/* Order response and cancel execution report for spot bond trading by matching, ApplID 010: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
  uint8_t stop_px[8];             /* bytes 189 to 196 */
  uint8_t min_qty[8];             /* bytes 197 to 204 */
  uint8_t max_price_levels[2];    /* bytes 205 to 206 */
  uint8_t time_in_force;          /* byte 207 */
  uint8_t cash_margin;            /* byte 208 */
} BondSpotMatchingExecutionReportMessage;

/* any Bond Spot Matching Execution Report Message at all: every byte one the checker chooses */
static void any_bond_spot_matching_execution_report_message(BondSpotMatchingExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->cash_margin = arbitrary();
}

/* Bond Spot Matching Execution Report Message to the wire: 209 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_matching_execution_report_message(const BondSpotMatchingExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_price_levels[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->cash_margin;

  return at;
}

/* Bond Spot Matching Execution Report Message off the wire: 209 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_matching_execution_report_message(BondSpotMatchingExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of Bond Spot Matching Execution Report Message is what was written, byte for byte */
static void equal_bond_spot_matching_execution_report_message(const BondSpotMatchingExecutionReportMessage *read, const BondSpotMatchingExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->max_price_levels[i] == written->max_price_levels[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->cash_margin == written->cash_margin);
}

/* Bond Spot Matching Execution Report Message: written and read back, then read and written back */
static void check_bond_spot_matching_execution_report_message(void) {
  BondSpotMatchingExecutionReportMessage sent;
  BondSpotMatchingExecutionReportMessage got;
  uint8_t wire[209];
  uint8_t again[209];

  any_bond_spot_matching_execution_report_message(&sent);
  assert(encode_bond_spot_matching_execution_report_message(&sent, wire, 0) == 209);
  assert(decode_bond_spot_matching_execution_report_message(&got, wire, 0) == 209);
  equal_bond_spot_matching_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 209; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_matching_execution_report_message(&got, wire, 0) == 209);
  assert(encode_bond_spot_matching_execution_report_message(&got, again, 0) == 209);
  for (size_t i = 0; i < 209; i++) { assert(again[i] == wire[i]); }
}

/* ---- Centralized Auction Execution Report Message: 209 bytes ----------------- */

/* Order response and cancel execution report for centralized auction stock trading, ApplID 040: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
  uint8_t stop_px[8];             /* bytes 189 to 196 */
  uint8_t min_qty[8];             /* bytes 197 to 204 */
  uint8_t max_price_levels[2];    /* bytes 205 to 206 */
  uint8_t time_in_force;          /* byte 207 */
  uint8_t cash_margin;            /* byte 208 */
} CentralizedAuctionExecutionReportMessage;

/* any Centralized Auction Execution Report Message at all: every byte one the checker chooses */
static void any_centralized_auction_execution_report_message(CentralizedAuctionExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->cash_margin = arbitrary();
}

/* Centralized Auction Execution Report Message to the wire: 209 bytes from at, returning where the next byte goes */
static size_t encode_centralized_auction_execution_report_message(const CentralizedAuctionExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_price_levels[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->cash_margin;

  return at;
}

/* Centralized Auction Execution Report Message off the wire: 209 bytes from at, returning where the next byte lies */
static size_t decode_centralized_auction_execution_report_message(CentralizedAuctionExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->max_price_levels[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of Centralized Auction Execution Report Message is what was written, byte for byte */
static void equal_centralized_auction_execution_report_message(const CentralizedAuctionExecutionReportMessage *read, const CentralizedAuctionExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->max_price_levels[i] == written->max_price_levels[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->cash_margin == written->cash_margin);
}

/* Centralized Auction Execution Report Message: written and read back, then read and written back */
static void check_centralized_auction_execution_report_message(void) {
  CentralizedAuctionExecutionReportMessage sent;
  CentralizedAuctionExecutionReportMessage got;
  uint8_t wire[209];
  uint8_t again[209];

  any_centralized_auction_execution_report_message(&sent);
  assert(encode_centralized_auction_execution_report_message(&sent, wire, 0) == 209);
  assert(decode_centralized_auction_execution_report_message(&got, wire, 0) == 209);
  equal_centralized_auction_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 209; i++) { wire[i] = arbitrary(); }
  assert(decode_centralized_auction_execution_report_message(&got, wire, 0) == 209);
  assert(encode_centralized_auction_execution_report_message(&got, again, 0) == 209);
  for (size_t i = 0; i < 209; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conversion Execution Report Message: 189 bytes -------------------------- */

/* Order response and cancel execution report for conversion, ApplID 041: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
} ConversionExecutionReportMessage;

/* any Conversion Execution Report Message at all: every byte one the checker chooses */
static void any_conversion_execution_report_message(ConversionExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
}

/* Conversion Execution Report Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_conversion_execution_report_message(const ConversionExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }

  return at;
}

/* Conversion Execution Report Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_conversion_execution_report_message(ConversionExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }

  return at;
}

/* what was read of Conversion Execution Report Message is what was written, byte for byte */
static void equal_conversion_execution_report_message(const ConversionExecutionReportMessage *read, const ConversionExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
}

/* Conversion Execution Report Message: written and read back, then read and written back */
static void check_conversion_execution_report_message(void) {
  ConversionExecutionReportMessage sent;
  ConversionExecutionReportMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_conversion_execution_report_message(&sent);
  assert(encode_conversion_execution_report_message(&sent, wire, 0) == 189);
  assert(decode_conversion_execution_report_message(&got, wire, 0) == 189);
  equal_conversion_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_conversion_execution_report_message(&got, wire, 0) == 189);
  assert(encode_conversion_execution_report_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inquiry Execution Report Message: 189 bytes ----------------------------- */

/* Order response and cancel execution report for inquiry, ApplID 042: confirms or rejects a new order; the business does not allow cancellation. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
} InquiryExecutionReportMessage;

/* any Inquiry Execution Report Message at all: every byte one the checker chooses */
static void any_inquiry_execution_report_message(InquiryExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
}

/* Inquiry Execution Report Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_inquiry_execution_report_message(const InquiryExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }

  return at;
}

/* Inquiry Execution Report Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_inquiry_execution_report_message(InquiryExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }

  return at;
}

/* what was read of Inquiry Execution Report Message is what was written, byte for byte */
static void equal_inquiry_execution_report_message(const InquiryExecutionReportMessage *read, const InquiryExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
}

/* Inquiry Execution Report Message: written and read back, then read and written back */
static void check_inquiry_execution_report_message(void) {
  InquiryExecutionReportMessage sent;
  InquiryExecutionReportMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_inquiry_execution_report_message(&sent);
  assert(encode_inquiry_execution_report_message(&sent, wire, 0) == 189);
  assert(decode_inquiry_execution_report_message(&got, wire, 0) == 189);
  equal_inquiry_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_inquiry_execution_report_message(&got, wire, 0) == 189);
  assert(encode_inquiry_execution_report_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription Execution Report Message: 189 bytes ------------------------ */

/* Order response and cancel execution report for subscription, ApplID 043: confirms or rejects a new order; the business does not allow cancellation. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
} SubscriptionExecutionReportMessage;

/* any Subscription Execution Report Message at all: every byte one the checker chooses */
static void any_subscription_execution_report_message(SubscriptionExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
}

/* Subscription Execution Report Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_subscription_execution_report_message(const SubscriptionExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }

  return at;
}

/* Subscription Execution Report Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_subscription_execution_report_message(SubscriptionExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }

  return at;
}

/* what was read of Subscription Execution Report Message is what was written, byte for byte */
static void equal_subscription_execution_report_message(const SubscriptionExecutionReportMessage *read, const SubscriptionExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
}

/* Subscription Execution Report Message: written and read back, then read and written back */
static void check_subscription_execution_report_message(void) {
  SubscriptionExecutionReportMessage sent;
  SubscriptionExecutionReportMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_subscription_execution_report_message(&sent);
  assert(encode_subscription_execution_report_message(&sent, wire, 0) == 189);
  assert(decode_subscription_execution_report_message(&got, wire, 0) == 189);
  equal_subscription_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_execution_report_message(&got, wire, 0) == 189);
  assert(encode_subscription_execution_report_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Put Back Execution Report Message: 189 bytes ---------------------------- */

/* Order response and cancel execution report for put back, ApplID 044: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
} PutBackExecutionReportMessage;

/* any Put Back Execution Report Message at all: every byte one the checker chooses */
static void any_put_back_execution_report_message(PutBackExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
}

/* Put Back Execution Report Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_put_back_execution_report_message(const PutBackExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }

  return at;
}

/* Put Back Execution Report Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_put_back_execution_report_message(PutBackExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }

  return at;
}

/* what was read of Put Back Execution Report Message is what was written, byte for byte */
static void equal_put_back_execution_report_message(const PutBackExecutionReportMessage *read, const PutBackExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
}

/* Put Back Execution Report Message: written and read back, then read and written back */
static void check_put_back_execution_report_message(void) {
  PutBackExecutionReportMessage sent;
  PutBackExecutionReportMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_put_back_execution_report_message(&sent);
  assert(encode_put_back_execution_report_message(&sent, wire, 0) == 189);
  assert(decode_put_back_execution_report_message(&got, wire, 0) == 189);
  equal_put_back_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_put_back_execution_report_message(&got, wire, 0) == 189);
  assert(encode_put_back_execution_report_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Tender Offer Acceptance Execution Report Message: 189 bytes ------------- */

/* Order response and cancel execution report for tender offer acceptance, ApplID 045: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
} TenderOfferAcceptanceExecutionReportMessage;

/* any Tender Offer Acceptance Execution Report Message at all: every byte one the checker chooses */
static void any_tender_offer_acceptance_execution_report_message(TenderOfferAcceptanceExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
}

/* Tender Offer Acceptance Execution Report Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_tender_offer_acceptance_execution_report_message(const TenderOfferAcceptanceExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }

  return at;
}

/* Tender Offer Acceptance Execution Report Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_tender_offer_acceptance_execution_report_message(TenderOfferAcceptanceExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }

  return at;
}

/* what was read of Tender Offer Acceptance Execution Report Message is what was written, byte for byte */
static void equal_tender_offer_acceptance_execution_report_message(const TenderOfferAcceptanceExecutionReportMessage *read, const TenderOfferAcceptanceExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
}

/* Tender Offer Acceptance Execution Report Message: written and read back, then read and written back */
static void check_tender_offer_acceptance_execution_report_message(void) {
  TenderOfferAcceptanceExecutionReportMessage sent;
  TenderOfferAcceptanceExecutionReportMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_tender_offer_acceptance_execution_report_message(&sent);
  assert(encode_tender_offer_acceptance_execution_report_message(&sent, wire, 0) == 189);
  assert(decode_tender_offer_acceptance_execution_report_message(&got, wire, 0) == 189);
  equal_tender_offer_acceptance_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_tender_offer_acceptance_execution_report_message(&got, wire, 0) == 189);
  assert(encode_tender_offer_acceptance_execution_report_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Non Agreed Execution Report Message: 194 bytes ---- */

/* Order response and cancel execution report for refinancing securities lending without agreement, ApplID 050: confirms or rejects a new order, a successful cancel, or an order the system cancels itself. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t orig_cl_ord_id[10];     /* bytes 109 to 118 */
  uint8_t exec_id[16];            /* bytes 119 to 134 */
  uint8_t exec_type;              /* byte 135 */
  uint8_t ord_status;             /* byte 136 */
  uint8_t ord_rej_reason[2];      /* bytes 137 to 138 */
  uint8_t leaves_qty[8];          /* bytes 139 to 146 */
  uint8_t cum_qty[8];             /* bytes 147 to 154 */
  uint8_t side;                   /* byte 155 */
  uint8_t ord_type;               /* byte 156 */
  uint8_t order_qty[8];           /* bytes 157 to 164 */
  uint8_t price[8];               /* bytes 165 to 172 */
  uint8_t account_id[10];         /* bytes 173 to 182 */
  uint8_t branch_id[2];           /* bytes 183 to 184 */
  uint8_t order_restrictions[4];  /* bytes 185 to 188 */
  uint8_t expiration_days[2];     /* bytes 189 to 190 */
  uint8_t expiration_type;        /* byte 191 */
  uint8_t share_property[2];      /* bytes 192 to 193 */
} RefinancingSecuritiesLendingNonAgreedExecutionReportMessage;

/* any Refinancing Securities Lending Non Agreed Execution Report Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_non_agreed_execution_report_message(RefinancingSecuritiesLendingNonAgreedExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  record->ord_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Non Agreed Execution Report Message to the wire: 194 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_non_agreed_execution_report_message(const RefinancingSecuritiesLendingNonAgreedExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ord_rej_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  wire[at++] = record->ord_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_restrictions[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Non Agreed Execution Report Message off the wire: 194 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_non_agreed_execution_report_message(RefinancingSecuritiesLendingNonAgreedExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ord_rej_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  record->ord_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_restrictions[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Non Agreed Execution Report Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_non_agreed_execution_report_message(const RefinancingSecuritiesLendingNonAgreedExecutionReportMessage *read, const RefinancingSecuritiesLendingNonAgreedExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 2; i++) { assert(read->ord_rej_reason[i] == written->ord_rej_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  assert(read->ord_type == written->ord_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_restrictions[i] == written->order_restrictions[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Non Agreed Execution Report Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_non_agreed_execution_report_message(void) {
  RefinancingSecuritiesLendingNonAgreedExecutionReportMessage sent;
  RefinancingSecuritiesLendingNonAgreedExecutionReportMessage got;
  uint8_t wire[194];
  uint8_t again[194];

  any_refinancing_securities_lending_non_agreed_execution_report_message(&sent);
  assert(encode_refinancing_securities_lending_non_agreed_execution_report_message(&sent, wire, 0) == 194);
  assert(decode_refinancing_securities_lending_non_agreed_execution_report_message(&got, wire, 0) == 194);
  equal_refinancing_securities_lending_non_agreed_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 194; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_non_agreed_execution_report_message(&got, wire, 0) == 194);
  assert(encode_refinancing_securities_lending_non_agreed_execution_report_message(&got, again, 0) == 194);
  for (size_t i = 0; i < 194; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Matching Trade Execution Report Message: 175 bytes ------------ */

/* Execution report for a trade on an order for spot bond trading by matching, ApplID 010. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t exec_id[16];            /* bytes 109 to 124 */
  uint8_t exec_type;              /* byte 125 */
  uint8_t ord_status;             /* byte 126 */
  uint8_t last_px[8];             /* bytes 127 to 134 */
  uint8_t last_qty[8];            /* bytes 135 to 142 */
  uint8_t leaves_qty[8];          /* bytes 143 to 150 */
  uint8_t cum_qty[8];             /* bytes 151 to 158 */
  uint8_t side;                   /* byte 159 */
  uint8_t account_id[10];         /* bytes 160 to 169 */
  uint8_t branch_id[2];           /* bytes 170 to 171 */
  uint8_t cash_margin;            /* byte 172 */
  uint8_t settl_type;             /* byte 173 */
  uint8_t settl_period;           /* byte 174 */
} BondSpotMatchingTradeExecutionReportMessage;

/* any Bond Spot Matching Trade Execution Report Message at all: every byte one the checker chooses */
static void any_bond_spot_matching_trade_execution_report_message(BondSpotMatchingTradeExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  record->cash_margin = arbitrary();
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
}

/* Bond Spot Matching Trade Execution Report Message to the wire: 175 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_matching_trade_execution_report_message(const BondSpotMatchingTradeExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  wire[at++] = record->cash_margin;
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;

  return at;
}

/* Bond Spot Matching Trade Execution Report Message off the wire: 175 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_matching_trade_execution_report_message(BondSpotMatchingTradeExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  record->cash_margin = wire[at++];
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];

  return at;
}

/* what was read of Bond Spot Matching Trade Execution Report Message is what was written, byte for byte */
static void equal_bond_spot_matching_trade_execution_report_message(const BondSpotMatchingTradeExecutionReportMessage *read, const BondSpotMatchingTradeExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  assert(read->cash_margin == written->cash_margin);
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
}

/* Bond Spot Matching Trade Execution Report Message: written and read back, then read and written back */
static void check_bond_spot_matching_trade_execution_report_message(void) {
  BondSpotMatchingTradeExecutionReportMessage sent;
  BondSpotMatchingTradeExecutionReportMessage got;
  uint8_t wire[175];
  uint8_t again[175];

  any_bond_spot_matching_trade_execution_report_message(&sent);
  assert(encode_bond_spot_matching_trade_execution_report_message(&sent, wire, 0) == 175);
  assert(decode_bond_spot_matching_trade_execution_report_message(&got, wire, 0) == 175);
  equal_bond_spot_matching_trade_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 175; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_matching_trade_execution_report_message(&got, wire, 0) == 175);
  assert(encode_bond_spot_matching_trade_execution_report_message(&got, again, 0) == 175);
  for (size_t i = 0; i < 175; i++) { assert(again[i] == wire[i]); }
}

/* ---- Centralized Auction Trade Execution Report Message: 173 bytes ----------- */

/* Execution report for a trade on an order for centralized auction stock trading, ApplID 040. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t exec_id[16];            /* bytes 109 to 124 */
  uint8_t exec_type;              /* byte 125 */
  uint8_t ord_status;             /* byte 126 */
  uint8_t last_px[8];             /* bytes 127 to 134 */
  uint8_t last_qty[8];            /* bytes 135 to 142 */
  uint8_t leaves_qty[8];          /* bytes 143 to 150 */
  uint8_t cum_qty[8];             /* bytes 151 to 158 */
  uint8_t side;                   /* byte 159 */
  uint8_t account_id[10];         /* bytes 160 to 169 */
  uint8_t branch_id[2];           /* bytes 170 to 171 */
  uint8_t cash_margin;            /* byte 172 */
} CentralizedAuctionTradeExecutionReportMessage;

/* any Centralized Auction Trade Execution Report Message at all: every byte one the checker chooses */
static void any_centralized_auction_trade_execution_report_message(CentralizedAuctionTradeExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  record->cash_margin = arbitrary();
}

/* Centralized Auction Trade Execution Report Message to the wire: 173 bytes from at, returning where the next byte goes */
static size_t encode_centralized_auction_trade_execution_report_message(const CentralizedAuctionTradeExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  wire[at++] = record->cash_margin;

  return at;
}

/* Centralized Auction Trade Execution Report Message off the wire: 173 bytes from at, returning where the next byte lies */
static size_t decode_centralized_auction_trade_execution_report_message(CentralizedAuctionTradeExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of Centralized Auction Trade Execution Report Message is what was written, byte for byte */
static void equal_centralized_auction_trade_execution_report_message(const CentralizedAuctionTradeExecutionReportMessage *read, const CentralizedAuctionTradeExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  assert(read->cash_margin == written->cash_margin);
}

/* Centralized Auction Trade Execution Report Message: written and read back, then read and written back */
static void check_centralized_auction_trade_execution_report_message(void) {
  CentralizedAuctionTradeExecutionReportMessage sent;
  CentralizedAuctionTradeExecutionReportMessage got;
  uint8_t wire[173];
  uint8_t again[173];

  any_centralized_auction_trade_execution_report_message(&sent);
  assert(encode_centralized_auction_trade_execution_report_message(&sent, wire, 0) == 173);
  assert(decode_centralized_auction_trade_execution_report_message(&got, wire, 0) == 173);
  equal_centralized_auction_trade_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 173; i++) { wire[i] = arbitrary(); }
  assert(decode_centralized_auction_trade_execution_report_message(&got, wire, 0) == 173);
  assert(encode_centralized_auction_trade_execution_report_message(&got, again, 0) == 173);
  for (size_t i = 0; i < 173; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Non Agreed Trade Execution Report Message: 181 bytes ---- */

/* Execution report for a trade on an order for refinancing securities lending without agreement, ApplID 050. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];        /* bytes 0 to 3 */
  uint8_t report_index[8];        /* bytes 4 to 11 */
  uint8_t appl_id[3];             /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];     /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];    /* bytes 21 to 26 */
  uint8_t security_id[8];         /* bytes 27 to 34 */
  uint8_t security_id_source[4];  /* bytes 35 to 38 */
  uint8_t owner_type[2];          /* bytes 39 to 40 */
  uint8_t clearing_firm[2];       /* bytes 41 to 42 */
  uint8_t transact_time[8];       /* bytes 43 to 50 */
  uint8_t user_info[32];          /* bytes 51 to 82 */
  uint8_t order_id[16];           /* bytes 83 to 98 */
  uint8_t cl_ord_id[10];          /* bytes 99 to 108 */
  uint8_t exec_id[16];            /* bytes 109 to 124 */
  uint8_t exec_type;              /* byte 125 */
  uint8_t ord_status;             /* byte 126 */
  uint8_t last_px[8];             /* bytes 127 to 134 */
  uint8_t last_qty[8];            /* bytes 135 to 142 */
  uint8_t leaves_qty[8];          /* bytes 143 to 150 */
  uint8_t cum_qty[8];             /* bytes 151 to 158 */
  uint8_t side;                   /* byte 159 */
  uint8_t account_id[10];         /* bytes 160 to 169 */
  uint8_t branch_id[2];           /* bytes 170 to 171 */
  uint8_t expiration_days[2];     /* bytes 172 to 173 */
  uint8_t expiration_type;        /* byte 174 */
  uint8_t maturity_date[4];       /* bytes 175 to 178 */
  uint8_t share_property[2];      /* bytes 179 to 180 */
} RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage;

/* any Refinancing Securities Lending Non Agreed Trade Execution Report Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_non_agreed_trade_execution_report_message(RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  record->ord_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Non Agreed Trade Execution Report Message to the wire: 181 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_non_agreed_trade_execution_report_message(const RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->exec_type;
  wire[at++] = record->ord_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Non Agreed Trade Execution Report Message off the wire: 181 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_non_agreed_trade_execution_report_message(RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  record->ord_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Non Agreed Trade Execution Report Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_non_agreed_trade_execution_report_message(const RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage *read, const RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->exec_type == written->exec_type);
  assert(read->ord_status == written->ord_status);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Non Agreed Trade Execution Report Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_non_agreed_trade_execution_report_message(void) {
  RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage sent;
  RefinancingSecuritiesLendingNonAgreedTradeExecutionReportMessage got;
  uint8_t wire[181];
  uint8_t again[181];

  any_refinancing_securities_lending_non_agreed_trade_execution_report_message(&sent);
  assert(encode_refinancing_securities_lending_non_agreed_trade_execution_report_message(&sent, wire, 0) == 181);
  assert(decode_refinancing_securities_lending_non_agreed_trade_execution_report_message(&got, wire, 0) == 181);
  equal_refinancing_securities_lending_non_agreed_trade_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 181; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_non_agreed_trade_execution_report_message(&got, wire, 0) == 181);
  assert(encode_refinancing_securities_lending_non_agreed_trade_execution_report_message(&got, again, 0) == 181);
  for (size_t i = 0; i < 181; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Negotiated Trade Capture Report Message: 294 bytes ------------ */

/* Trade capture report for spot bond trading by negotiation, ApplID 031, submitted for matching. */
typedef struct {
  uint8_t appl_id[3];                   /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];          /* bytes 3 to 8 */
  uint8_t security_id[8];               /* bytes 9 to 16 */
  uint8_t security_id_source[4];        /* bytes 17 to 20 */
  uint8_t owner_type[2];                /* bytes 21 to 22 */
  uint8_t clearing_firm[2];             /* bytes 23 to 24 */
  uint8_t transact_time[8];             /* bytes 25 to 32 */
  uint8_t user_info[32];                /* bytes 33 to 64 */
  uint8_t trade_report_id[10];          /* bytes 65 to 74 */
  uint8_t trade_report_type;            /* byte 75 */
  uint8_t trade_report_trans_type;      /* byte 76 */
  uint8_t trade_handling_instr;         /* byte 77 */
  uint8_t trade_report_ref_id[10];      /* bytes 78 to 87 */
  uint8_t last_px[8];                   /* bytes 88 to 95 */
  uint8_t last_qty[8];                  /* bytes 96 to 103 */
  uint8_t trd_type[2];                  /* bytes 104 to 105 */
  uint8_t trd_sub_type[2];              /* bytes 106 to 107 */
  uint8_t confirm_id[4];                /* bytes 108 to 111 */
  uint8_t side;                         /* byte 112 */
  uint8_t pbuid[6];                     /* bytes 113 to 118 */
  uint8_t account_id[10];               /* bytes 119 to 128 */
  uint8_t branch_id[2];                 /* bytes 129 to 130 */
  uint8_t counterparty_pbuid[6];        /* bytes 131 to 136 */
  uint8_t counterparty_account_id[10];  /* bytes 137 to 146 */
  uint8_t counterparty_branch_id[2];    /* bytes 147 to 148 */
  uint8_t member_id[6];                 /* bytes 149 to 154 */
  uint8_t trader_code[5];               /* bytes 155 to 159 */
  uint8_t counterparty_member_id[6];    /* bytes 160 to 165 */
  uint8_t counterparty_trader_code[5];  /* bytes 166 to 170 */
  uint8_t settl_type;                   /* byte 171 */
  uint8_t settl_period;                 /* byte 172 */
  uint8_t cash_margin;                  /* byte 173 */
  uint8_t memo[120];                    /* bytes 174 to 293 */
} BondSpotNegotiatedTradeCaptureReportMessage;

/* any Bond Spot Negotiated Trade Capture Report Message at all: every byte one the checker chooses */
static void any_bond_spot_negotiated_trade_capture_report_message(BondSpotNegotiatedTradeCaptureReportMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = arbitrary(); }
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
  record->cash_margin = arbitrary();
  for (size_t i = 0; i < 120; i++) { record->memo[i] = arbitrary(); }
}

/* Bond Spot Negotiated Trade Capture Report Message to the wire: 294 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_negotiated_trade_capture_report_message(const BondSpotNegotiatedTradeCaptureReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->trader_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counterparty_trader_code[i]; }
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;
  wire[at++] = record->cash_margin;
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Bond Spot Negotiated Trade Capture Report Message off the wire: 294 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_negotiated_trade_capture_report_message(BondSpotNegotiatedTradeCaptureReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = wire[at++]; }
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];
  record->cash_margin = wire[at++];
  for (size_t i = 0; i < 120; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Bond Spot Negotiated Trade Capture Report Message is what was written, byte for byte */
static void equal_bond_spot_negotiated_trade_capture_report_message(const BondSpotNegotiatedTradeCaptureReportMessage *read, const BondSpotNegotiatedTradeCaptureReportMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->member_id[i] == written->member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_member_id[i] == written->counterparty_member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counterparty_trader_code[i] == written->counterparty_trader_code[i]); }
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
  assert(read->cash_margin == written->cash_margin);
  for (size_t i = 0; i < 120; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Bond Spot Negotiated Trade Capture Report Message: written and read back, then read and written back */
static void check_bond_spot_negotiated_trade_capture_report_message(void) {
  BondSpotNegotiatedTradeCaptureReportMessage sent;
  BondSpotNegotiatedTradeCaptureReportMessage got;
  uint8_t wire[294];
  uint8_t again[294];

  any_bond_spot_negotiated_trade_capture_report_message(&sent);
  assert(encode_bond_spot_negotiated_trade_capture_report_message(&sent, wire, 0) == 294);
  assert(decode_bond_spot_negotiated_trade_capture_report_message(&got, wire, 0) == 294);
  equal_bond_spot_negotiated_trade_capture_report_message(&got, &sent);

  for (size_t i = 0; i < 294; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_negotiated_trade_capture_report_message(&got, wire, 0) == 294);
  assert(encode_bond_spot_negotiated_trade_capture_report_message(&got, again, 0) == 294);
  for (size_t i = 0; i < 294; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Agreed Trade Capture Report Message: 154 bytes ---- */

/* Trade capture report for refinancing securities lending by agreement, ApplID 051, submitted for matching. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];                   /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];          /* bytes 3 to 8 */
  uint8_t security_id[8];               /* bytes 9 to 16 */
  uint8_t security_id_source[4];        /* bytes 17 to 20 */
  uint8_t owner_type[2];                /* bytes 21 to 22 */
  uint8_t clearing_firm[2];             /* bytes 23 to 24 */
  uint8_t transact_time[8];             /* bytes 25 to 32 */
  uint8_t user_info[32];                /* bytes 33 to 64 */
  uint8_t trade_report_id[10];          /* bytes 65 to 74 */
  uint8_t trade_report_type;            /* byte 75 */
  uint8_t trade_report_trans_type;      /* byte 76 */
  uint8_t trade_handling_instr;         /* byte 77 */
  uint8_t trade_report_ref_id[10];      /* bytes 78 to 87 */
  uint8_t last_px[8];                   /* bytes 88 to 95 */
  uint8_t last_qty[8];                  /* bytes 96 to 103 */
  uint8_t trd_type[2];                  /* bytes 104 to 105 */
  uint8_t trd_sub_type[2];              /* bytes 106 to 107 */
  uint8_t confirm_id[4];                /* bytes 108 to 111 */
  uint8_t side;                         /* byte 112 */
  uint8_t pbuid[6];                     /* bytes 113 to 118 */
  uint8_t account_id[10];               /* bytes 119 to 128 */
  uint8_t branch_id[2];                 /* bytes 129 to 130 */
  uint8_t counterparty_pbuid[6];        /* bytes 131 to 136 */
  uint8_t counterparty_account_id[10];  /* bytes 137 to 146 */
  uint8_t counterparty_branch_id[2];    /* bytes 147 to 148 */
  uint8_t expiration_days[2];           /* bytes 149 to 150 */
  uint8_t expiration_type;              /* byte 151 */
  uint8_t share_property[2];            /* bytes 152 to 153 */
} RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage;

/* any Refinancing Securities Lending Agreed Trade Capture Report Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_agreed_trade_capture_report_message(RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Message to the wire: 154 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_agreed_trade_capture_report_message(const RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Agreed Trade Capture Report Message off the wire: 154 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_agreed_trade_capture_report_message(RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Agreed Trade Capture Report Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_agreed_trade_capture_report_message(const RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage *read, const RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_agreed_trade_capture_report_message(void) {
  RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage sent;
  RefinancingSecuritiesLendingAgreedTradeCaptureReportMessage got;
  uint8_t wire[154];
  uint8_t again[154];

  any_refinancing_securities_lending_agreed_trade_capture_report_message(&sent);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_message(&sent, wire, 0) == 154);
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_message(&got, wire, 0) == 154);
  equal_refinancing_securities_lending_agreed_trade_capture_report_message(&got, &sent);

  for (size_t i = 0; i < 154; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_message(&got, wire, 0) == 154);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_message(&got, again, 0) == 154);
  for (size_t i = 0; i < 154; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Trade Confirmation Trade Capture Report Message: 149 bytes ------- */

/* Trade capture report for mutual trade confirmation, ApplID 060, submitted for matching. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];                   /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];          /* bytes 3 to 8 */
  uint8_t security_id[8];               /* bytes 9 to 16 */
  uint8_t security_id_source[4];        /* bytes 17 to 20 */
  uint8_t owner_type[2];                /* bytes 21 to 22 */
  uint8_t clearing_firm[2];             /* bytes 23 to 24 */
  uint8_t transact_time[8];             /* bytes 25 to 32 */
  uint8_t user_info[32];                /* bytes 33 to 64 */
  uint8_t trade_report_id[10];          /* bytes 65 to 74 */
  uint8_t trade_report_type;            /* byte 75 */
  uint8_t trade_report_trans_type;      /* byte 76 */
  uint8_t trade_handling_instr;         /* byte 77 */
  uint8_t trade_report_ref_id[10];      /* bytes 78 to 87 */
  uint8_t last_px[8];                   /* bytes 88 to 95 */
  uint8_t last_qty[8];                  /* bytes 96 to 103 */
  uint8_t trd_type[2];                  /* bytes 104 to 105 */
  uint8_t trd_sub_type[2];              /* bytes 106 to 107 */
  uint8_t confirm_id[4];                /* bytes 108 to 111 */
  uint8_t side;                         /* byte 112 */
  uint8_t pbuid[6];                     /* bytes 113 to 118 */
  uint8_t account_id[10];               /* bytes 119 to 128 */
  uint8_t branch_id[2];                 /* bytes 129 to 130 */
  uint8_t counterparty_pbuid[6];        /* bytes 131 to 136 */
  uint8_t counterparty_account_id[10];  /* bytes 137 to 146 */
  uint8_t counterparty_branch_id[2];    /* bytes 147 to 148 */
} MutualTradeConfirmationTradeCaptureReportMessage;

/* any Mutual Trade Confirmation Trade Capture Report Message at all: every byte one the checker chooses */
static void any_mutual_trade_confirmation_trade_capture_report_message(MutualTradeConfirmationTradeCaptureReportMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Mutual Trade Confirmation Trade Capture Report Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_mutual_trade_confirmation_trade_capture_report_message(const MutualTradeConfirmationTradeCaptureReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Mutual Trade Confirmation Trade Capture Report Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_mutual_trade_confirmation_trade_capture_report_message(MutualTradeConfirmationTradeCaptureReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Trade Confirmation Trade Capture Report Message is what was written, byte for byte */
static void equal_mutual_trade_confirmation_trade_capture_report_message(const MutualTradeConfirmationTradeCaptureReportMessage *read, const MutualTradeConfirmationTradeCaptureReportMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Mutual Trade Confirmation Trade Capture Report Message: written and read back, then read and written back */
static void check_mutual_trade_confirmation_trade_capture_report_message(void) {
  MutualTradeConfirmationTradeCaptureReportMessage sent;
  MutualTradeConfirmationTradeCaptureReportMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_mutual_trade_confirmation_trade_capture_report_message(&sent);
  assert(encode_mutual_trade_confirmation_trade_capture_report_message(&sent, wire, 0) == 149);
  assert(decode_mutual_trade_confirmation_trade_capture_report_message(&got, wire, 0) == 149);
  equal_mutual_trade_confirmation_trade_capture_report_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_trade_confirmation_trade_capture_report_message(&got, wire, 0) == 149);
  assert(encode_mutual_trade_confirmation_trade_capture_report_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Making Mutual Trade Confirmation Trade Capture Report Message: 149 bytes ---- */

/* Trade capture report for market making mutual trade confirmation, ApplID 061, submitted for matching. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];                   /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];          /* bytes 3 to 8 */
  uint8_t security_id[8];               /* bytes 9 to 16 */
  uint8_t security_id_source[4];        /* bytes 17 to 20 */
  uint8_t owner_type[2];                /* bytes 21 to 22 */
  uint8_t clearing_firm[2];             /* bytes 23 to 24 */
  uint8_t transact_time[8];             /* bytes 25 to 32 */
  uint8_t user_info[32];                /* bytes 33 to 64 */
  uint8_t trade_report_id[10];          /* bytes 65 to 74 */
  uint8_t trade_report_type;            /* byte 75 */
  uint8_t trade_report_trans_type;      /* byte 76 */
  uint8_t trade_handling_instr;         /* byte 77 */
  uint8_t trade_report_ref_id[10];      /* bytes 78 to 87 */
  uint8_t last_px[8];                   /* bytes 88 to 95 */
  uint8_t last_qty[8];                  /* bytes 96 to 103 */
  uint8_t trd_type[2];                  /* bytes 104 to 105 */
  uint8_t trd_sub_type[2];              /* bytes 106 to 107 */
  uint8_t confirm_id[4];                /* bytes 108 to 111 */
  uint8_t side;                         /* byte 112 */
  uint8_t pbuid[6];                     /* bytes 113 to 118 */
  uint8_t account_id[10];               /* bytes 119 to 128 */
  uint8_t branch_id[2];                 /* bytes 129 to 130 */
  uint8_t counterparty_pbuid[6];        /* bytes 131 to 136 */
  uint8_t counterparty_account_id[10];  /* bytes 137 to 146 */
  uint8_t counterparty_branch_id[2];    /* bytes 147 to 148 */
} MarketMakingMutualTradeConfirmationTradeCaptureReportMessage;

/* any Market Making Mutual Trade Confirmation Trade Capture Report Message at all: every byte one the checker chooses */
static void any_market_making_mutual_trade_confirmation_trade_capture_report_message(MarketMakingMutualTradeConfirmationTradeCaptureReportMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Message to the wire: 149 bytes from at, returning where the next byte goes */
static size_t encode_market_making_mutual_trade_confirmation_trade_capture_report_message(const MarketMakingMutualTradeConfirmationTradeCaptureReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Message off the wire: 149 bytes from at, returning where the next byte lies */
static size_t decode_market_making_mutual_trade_confirmation_trade_capture_report_message(MarketMakingMutualTradeConfirmationTradeCaptureReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Market Making Mutual Trade Confirmation Trade Capture Report Message is what was written, byte for byte */
static void equal_market_making_mutual_trade_confirmation_trade_capture_report_message(const MarketMakingMutualTradeConfirmationTradeCaptureReportMessage *read, const MarketMakingMutualTradeConfirmationTradeCaptureReportMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Message: written and read back, then read and written back */
static void check_market_making_mutual_trade_confirmation_trade_capture_report_message(void) {
  MarketMakingMutualTradeConfirmationTradeCaptureReportMessage sent;
  MarketMakingMutualTradeConfirmationTradeCaptureReportMessage got;
  uint8_t wire[149];
  uint8_t again[149];

  any_market_making_mutual_trade_confirmation_trade_capture_report_message(&sent);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_message(&sent, wire, 0) == 149);
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_message(&got, wire, 0) == 149);
  equal_market_making_mutual_trade_confirmation_trade_capture_report_message(&got, &sent);

  for (size_t i = 0; i < 149; i++) { wire[i] = arbitrary(); }
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_message(&got, wire, 0) == 149);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_message(&got, again, 0) == 149);
  for (size_t i = 0; i < 149; i++) { assert(again[i] == wire[i]); }
}

/* ---- After Hours Block Trade Trade Capture Report Message: 150 bytes --------- */

/* Trade capture report for after hours block trading, ApplID 062, submitted for matching. Not yet enabled. */
typedef struct {
  uint8_t appl_id[3];                   /* bytes 0 to 2 */
  uint8_t submitting_pbuid[6];          /* bytes 3 to 8 */
  uint8_t security_id[8];               /* bytes 9 to 16 */
  uint8_t security_id_source[4];        /* bytes 17 to 20 */
  uint8_t owner_type[2];                /* bytes 21 to 22 */
  uint8_t clearing_firm[2];             /* bytes 23 to 24 */
  uint8_t transact_time[8];             /* bytes 25 to 32 */
  uint8_t user_info[32];                /* bytes 33 to 64 */
  uint8_t trade_report_id[10];          /* bytes 65 to 74 */
  uint8_t trade_report_type;            /* byte 75 */
  uint8_t trade_report_trans_type;      /* byte 76 */
  uint8_t trade_handling_instr;         /* byte 77 */
  uint8_t trade_report_ref_id[10];      /* bytes 78 to 87 */
  uint8_t last_px[8];                   /* bytes 88 to 95 */
  uint8_t last_qty[8];                  /* bytes 96 to 103 */
  uint8_t trd_type[2];                  /* bytes 104 to 105 */
  uint8_t trd_sub_type[2];              /* bytes 106 to 107 */
  uint8_t confirm_id[4];                /* bytes 108 to 111 */
  uint8_t side;                         /* byte 112 */
  uint8_t pbuid[6];                     /* bytes 113 to 118 */
  uint8_t account_id[10];               /* bytes 119 to 128 */
  uint8_t branch_id[2];                 /* bytes 129 to 130 */
  uint8_t counterparty_pbuid[6];        /* bytes 131 to 136 */
  uint8_t counterparty_account_id[10];  /* bytes 137 to 146 */
  uint8_t counterparty_branch_id[2];    /* bytes 147 to 148 */
  uint8_t cash_margin;                  /* byte 149 */
} AfterHoursBlockTradeTradeCaptureReportMessage;

/* any After Hours Block Trade Trade Capture Report Message at all: every byte one the checker chooses */
static void any_after_hours_block_trade_trade_capture_report_message(AfterHoursBlockTradeTradeCaptureReportMessage *record) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  record->cash_margin = arbitrary();
}

/* After Hours Block Trade Trade Capture Report Message to the wire: 150 bytes from at, returning where the next byte goes */
static size_t encode_after_hours_block_trade_trade_capture_report_message(const AfterHoursBlockTradeTradeCaptureReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  wire[at++] = record->cash_margin;

  return at;
}

/* After Hours Block Trade Trade Capture Report Message off the wire: 150 bytes from at, returning where the next byte lies */
static size_t decode_after_hours_block_trade_trade_capture_report_message(AfterHoursBlockTradeTradeCaptureReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of After Hours Block Trade Trade Capture Report Message is what was written, byte for byte */
static void equal_after_hours_block_trade_trade_capture_report_message(const AfterHoursBlockTradeTradeCaptureReportMessage *read, const AfterHoursBlockTradeTradeCaptureReportMessage *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  assert(read->cash_margin == written->cash_margin);
}

/* After Hours Block Trade Trade Capture Report Message: written and read back, then read and written back */
static void check_after_hours_block_trade_trade_capture_report_message(void) {
  AfterHoursBlockTradeTradeCaptureReportMessage sent;
  AfterHoursBlockTradeTradeCaptureReportMessage got;
  uint8_t wire[150];
  uint8_t again[150];

  any_after_hours_block_trade_trade_capture_report_message(&sent);
  assert(encode_after_hours_block_trade_trade_capture_report_message(&sent, wire, 0) == 150);
  assert(decode_after_hours_block_trade_trade_capture_report_message(&got, wire, 0) == 150);
  equal_after_hours_block_trade_trade_capture_report_message(&got, &sent);

  for (size_t i = 0; i < 150; i++) { wire[i] = arbitrary(); }
  assert(decode_after_hours_block_trade_trade_capture_report_message(&got, wire, 0) == 150);
  assert(encode_after_hours_block_trade_trade_capture_report_message(&got, again, 0) == 150);
  for (size_t i = 0; i < 150; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Negotiated Trade Capture Report Ack Message: 348 bytes -------- */

/* Trading gateway response to a trade capture report for spot bond trading by negotiation, ApplID 031. */
typedef struct {
  uint8_t partition_no[4];                /* bytes 0 to 3 */
  uint8_t report_index[8];                /* bytes 4 to 11 */
  uint8_t appl_id[3];                     /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];             /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];            /* bytes 21 to 26 */
  uint8_t security_id[8];                 /* bytes 27 to 34 */
  uint8_t security_id_source[4];          /* bytes 35 to 38 */
  uint8_t owner_type[2];                  /* bytes 39 to 40 */
  uint8_t clearing_firm[2];               /* bytes 41 to 42 */
  uint8_t transact_time[8];               /* bytes 43 to 50 */
  uint8_t user_info[32];                  /* bytes 51 to 82 */
  uint8_t trade_id[16];                   /* bytes 83 to 98 */
  uint8_t trade_report_id[10];            /* bytes 99 to 108 */
  uint8_t trade_report_type;              /* byte 109 */
  uint8_t trade_report_trans_type;        /* byte 110 */
  uint8_t trade_handling_instr;           /* byte 111 */
  uint8_t trade_report_ref_id[10];        /* bytes 112 to 121 */
  uint8_t trd_ack_status;                 /* byte 122 */
  uint8_t trd_rpt_status;                 /* byte 123 */
  uint8_t trade_report_reject_reason[2];  /* bytes 124 to 125 */
  uint8_t last_px[8];                     /* bytes 126 to 133 */
  uint8_t last_qty[8];                    /* bytes 134 to 141 */
  uint8_t trd_type[2];                    /* bytes 142 to 143 */
  uint8_t trd_sub_type[2];                /* bytes 144 to 145 */
  uint8_t confirm_id[4];                  /* bytes 146 to 149 */
  uint8_t exec_id[16];                    /* bytes 150 to 165 */
  uint8_t side;                           /* byte 166 */
  uint8_t pbuid[6];                       /* bytes 167 to 172 */
  uint8_t account_id[10];                 /* bytes 173 to 182 */
  uint8_t branch_id[2];                   /* bytes 183 to 184 */
  uint8_t counterparty_pbuid[6];          /* bytes 185 to 190 */
  uint8_t counterparty_account_id[10];    /* bytes 191 to 200 */
  uint8_t counterparty_branch_id[2];      /* bytes 201 to 202 */
  uint8_t member_id[6];                   /* bytes 203 to 208 */
  uint8_t trader_code[5];                 /* bytes 209 to 213 */
  uint8_t counterparty_member_id[6];      /* bytes 214 to 219 */
  uint8_t counterparty_trader_code[5];    /* bytes 220 to 224 */
  uint8_t settl_type;                     /* byte 225 */
  uint8_t settl_period;                   /* byte 226 */
  uint8_t cash_margin;                    /* byte 227 */
  uint8_t memo[120];                      /* bytes 228 to 347 */
} BondSpotNegotiatedTradeCaptureReportAckMessage;

/* any Bond Spot Negotiated Trade Capture Report Ack Message at all: every byte one the checker chooses */
static void any_bond_spot_negotiated_trade_capture_report_ack_message(BondSpotNegotiatedTradeCaptureReportAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  record->trd_ack_status = arbitrary();
  record->trd_rpt_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = arbitrary(); }
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
  record->cash_margin = arbitrary();
  for (size_t i = 0; i < 120; i++) { record->memo[i] = arbitrary(); }
}

/* Bond Spot Negotiated Trade Capture Report Ack Message to the wire: 348 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_negotiated_trade_capture_report_ack_message(const BondSpotNegotiatedTradeCaptureReportAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  wire[at++] = record->trd_ack_status;
  wire[at++] = record->trd_rpt_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->trader_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counterparty_trader_code[i]; }
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;
  wire[at++] = record->cash_margin;
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Bond Spot Negotiated Trade Capture Report Ack Message off the wire: 348 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_negotiated_trade_capture_report_ack_message(BondSpotNegotiatedTradeCaptureReportAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  record->trd_ack_status = wire[at++];
  record->trd_rpt_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = wire[at++]; }
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];
  record->cash_margin = wire[at++];
  for (size_t i = 0; i < 120; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Bond Spot Negotiated Trade Capture Report Ack Message is what was written, byte for byte */
static void equal_bond_spot_negotiated_trade_capture_report_ack_message(const BondSpotNegotiatedTradeCaptureReportAckMessage *read, const BondSpotNegotiatedTradeCaptureReportAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  assert(read->trd_ack_status == written->trd_ack_status);
  assert(read->trd_rpt_status == written->trd_rpt_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_reject_reason[i] == written->trade_report_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->member_id[i] == written->member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_member_id[i] == written->counterparty_member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counterparty_trader_code[i] == written->counterparty_trader_code[i]); }
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
  assert(read->cash_margin == written->cash_margin);
  for (size_t i = 0; i < 120; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Bond Spot Negotiated Trade Capture Report Ack Message: written and read back, then read and written back */
static void check_bond_spot_negotiated_trade_capture_report_ack_message(void) {
  BondSpotNegotiatedTradeCaptureReportAckMessage sent;
  BondSpotNegotiatedTradeCaptureReportAckMessage got;
  uint8_t wire[348];
  uint8_t again[348];

  any_bond_spot_negotiated_trade_capture_report_ack_message(&sent);
  assert(encode_bond_spot_negotiated_trade_capture_report_ack_message(&sent, wire, 0) == 348);
  assert(decode_bond_spot_negotiated_trade_capture_report_ack_message(&got, wire, 0) == 348);
  equal_bond_spot_negotiated_trade_capture_report_ack_message(&got, &sent);

  for (size_t i = 0; i < 348; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_negotiated_trade_capture_report_ack_message(&got, wire, 0) == 348);
  assert(encode_bond_spot_negotiated_trade_capture_report_ack_message(&got, again, 0) == 348);
  for (size_t i = 0; i < 348; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Agreed Trade Capture Report Ack Message: 208 bytes ---- */

/* Trading gateway response to a trade capture report for refinancing securities lending by agreement, ApplID 051. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];                /* bytes 0 to 3 */
  uint8_t report_index[8];                /* bytes 4 to 11 */
  uint8_t appl_id[3];                     /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];             /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];            /* bytes 21 to 26 */
  uint8_t security_id[8];                 /* bytes 27 to 34 */
  uint8_t security_id_source[4];          /* bytes 35 to 38 */
  uint8_t owner_type[2];                  /* bytes 39 to 40 */
  uint8_t clearing_firm[2];               /* bytes 41 to 42 */
  uint8_t transact_time[8];               /* bytes 43 to 50 */
  uint8_t user_info[32];                  /* bytes 51 to 82 */
  uint8_t trade_id[16];                   /* bytes 83 to 98 */
  uint8_t trade_report_id[10];            /* bytes 99 to 108 */
  uint8_t trade_report_type;              /* byte 109 */
  uint8_t trade_report_trans_type;        /* byte 110 */
  uint8_t trade_handling_instr;           /* byte 111 */
  uint8_t trade_report_ref_id[10];        /* bytes 112 to 121 */
  uint8_t trd_ack_status;                 /* byte 122 */
  uint8_t trd_rpt_status;                 /* byte 123 */
  uint8_t trade_report_reject_reason[2];  /* bytes 124 to 125 */
  uint8_t last_px[8];                     /* bytes 126 to 133 */
  uint8_t last_qty[8];                    /* bytes 134 to 141 */
  uint8_t trd_type[2];                    /* bytes 142 to 143 */
  uint8_t trd_sub_type[2];                /* bytes 144 to 145 */
  uint8_t confirm_id[4];                  /* bytes 146 to 149 */
  uint8_t exec_id[16];                    /* bytes 150 to 165 */
  uint8_t side;                           /* byte 166 */
  uint8_t pbuid[6];                       /* bytes 167 to 172 */
  uint8_t account_id[10];                 /* bytes 173 to 182 */
  uint8_t branch_id[2];                   /* bytes 183 to 184 */
  uint8_t counterparty_pbuid[6];          /* bytes 185 to 190 */
  uint8_t counterparty_account_id[10];    /* bytes 191 to 200 */
  uint8_t counterparty_branch_id[2];      /* bytes 201 to 202 */
  uint8_t expiration_days[2];             /* bytes 203 to 204 */
  uint8_t expiration_type;                /* byte 205 */
  uint8_t share_property[2];              /* bytes 206 to 207 */
} RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage;

/* any Refinancing Securities Lending Agreed Trade Capture Report Ack Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_agreed_trade_capture_report_ack_message(RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  record->trd_ack_status = arbitrary();
  record->trd_rpt_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Ack Message to the wire: 208 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(const RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  wire[at++] = record->trd_ack_status;
  wire[at++] = record->trd_rpt_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Agreed Trade Capture Report Ack Message off the wire: 208 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  record->trd_ack_status = wire[at++];
  record->trd_rpt_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Agreed Trade Capture Report Ack Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_agreed_trade_capture_report_ack_message(const RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage *read, const RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  assert(read->trd_ack_status == written->trd_ack_status);
  assert(read->trd_rpt_status == written->trd_rpt_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_reject_reason[i] == written->trade_report_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Ack Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_agreed_trade_capture_report_ack_message(void) {
  RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage sent;
  RefinancingSecuritiesLendingAgreedTradeCaptureReportAckMessage got;
  uint8_t wire[208];
  uint8_t again[208];

  any_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&sent);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&sent, wire, 0) == 208);
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&got, wire, 0) == 208);
  equal_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&got, &sent);

  for (size_t i = 0; i < 208; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&got, wire, 0) == 208);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_ack_message(&got, again, 0) == 208);
  for (size_t i = 0; i < 208; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Trade Confirmation Trade Capture Report Ack Message: 203 bytes ---- */

/* Trading gateway response to a trade capture report for mutual trade confirmation, ApplID 060. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];                /* bytes 0 to 3 */
  uint8_t report_index[8];                /* bytes 4 to 11 */
  uint8_t appl_id[3];                     /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];             /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];            /* bytes 21 to 26 */
  uint8_t security_id[8];                 /* bytes 27 to 34 */
  uint8_t security_id_source[4];          /* bytes 35 to 38 */
  uint8_t owner_type[2];                  /* bytes 39 to 40 */
  uint8_t clearing_firm[2];               /* bytes 41 to 42 */
  uint8_t transact_time[8];               /* bytes 43 to 50 */
  uint8_t user_info[32];                  /* bytes 51 to 82 */
  uint8_t trade_id[16];                   /* bytes 83 to 98 */
  uint8_t trade_report_id[10];            /* bytes 99 to 108 */
  uint8_t trade_report_type;              /* byte 109 */
  uint8_t trade_report_trans_type;        /* byte 110 */
  uint8_t trade_handling_instr;           /* byte 111 */
  uint8_t trade_report_ref_id[10];        /* bytes 112 to 121 */
  uint8_t trd_ack_status;                 /* byte 122 */
  uint8_t trd_rpt_status;                 /* byte 123 */
  uint8_t trade_report_reject_reason[2];  /* bytes 124 to 125 */
  uint8_t last_px[8];                     /* bytes 126 to 133 */
  uint8_t last_qty[8];                    /* bytes 134 to 141 */
  uint8_t trd_type[2];                    /* bytes 142 to 143 */
  uint8_t trd_sub_type[2];                /* bytes 144 to 145 */
  uint8_t confirm_id[4];                  /* bytes 146 to 149 */
  uint8_t exec_id[16];                    /* bytes 150 to 165 */
  uint8_t side;                           /* byte 166 */
  uint8_t pbuid[6];                       /* bytes 167 to 172 */
  uint8_t account_id[10];                 /* bytes 173 to 182 */
  uint8_t branch_id[2];                   /* bytes 183 to 184 */
  uint8_t counterparty_pbuid[6];          /* bytes 185 to 190 */
  uint8_t counterparty_account_id[10];    /* bytes 191 to 200 */
  uint8_t counterparty_branch_id[2];      /* bytes 201 to 202 */
} MutualTradeConfirmationTradeCaptureReportAckMessage;

/* any Mutual Trade Confirmation Trade Capture Report Ack Message at all: every byte one the checker chooses */
static void any_mutual_trade_confirmation_trade_capture_report_ack_message(MutualTradeConfirmationTradeCaptureReportAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  record->trd_ack_status = arbitrary();
  record->trd_rpt_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Mutual Trade Confirmation Trade Capture Report Ack Message to the wire: 203 bytes from at, returning where the next byte goes */
static size_t encode_mutual_trade_confirmation_trade_capture_report_ack_message(const MutualTradeConfirmationTradeCaptureReportAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  wire[at++] = record->trd_ack_status;
  wire[at++] = record->trd_rpt_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Mutual Trade Confirmation Trade Capture Report Ack Message off the wire: 203 bytes from at, returning where the next byte lies */
static size_t decode_mutual_trade_confirmation_trade_capture_report_ack_message(MutualTradeConfirmationTradeCaptureReportAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  record->trd_ack_status = wire[at++];
  record->trd_rpt_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Trade Confirmation Trade Capture Report Ack Message is what was written, byte for byte */
static void equal_mutual_trade_confirmation_trade_capture_report_ack_message(const MutualTradeConfirmationTradeCaptureReportAckMessage *read, const MutualTradeConfirmationTradeCaptureReportAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  assert(read->trd_ack_status == written->trd_ack_status);
  assert(read->trd_rpt_status == written->trd_rpt_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_reject_reason[i] == written->trade_report_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Mutual Trade Confirmation Trade Capture Report Ack Message: written and read back, then read and written back */
static void check_mutual_trade_confirmation_trade_capture_report_ack_message(void) {
  MutualTradeConfirmationTradeCaptureReportAckMessage sent;
  MutualTradeConfirmationTradeCaptureReportAckMessage got;
  uint8_t wire[203];
  uint8_t again[203];

  any_mutual_trade_confirmation_trade_capture_report_ack_message(&sent);
  assert(encode_mutual_trade_confirmation_trade_capture_report_ack_message(&sent, wire, 0) == 203);
  assert(decode_mutual_trade_confirmation_trade_capture_report_ack_message(&got, wire, 0) == 203);
  equal_mutual_trade_confirmation_trade_capture_report_ack_message(&got, &sent);

  for (size_t i = 0; i < 203; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_trade_confirmation_trade_capture_report_ack_message(&got, wire, 0) == 203);
  assert(encode_mutual_trade_confirmation_trade_capture_report_ack_message(&got, again, 0) == 203);
  for (size_t i = 0; i < 203; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Making Mutual Trade Confirmation Trade Capture Report Ack Message: 203 bytes ---- */

/* Trading gateway response to a trade capture report for market making mutual trade confirmation, ApplID 061. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];                /* bytes 0 to 3 */
  uint8_t report_index[8];                /* bytes 4 to 11 */
  uint8_t appl_id[3];                     /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];             /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];            /* bytes 21 to 26 */
  uint8_t security_id[8];                 /* bytes 27 to 34 */
  uint8_t security_id_source[4];          /* bytes 35 to 38 */
  uint8_t owner_type[2];                  /* bytes 39 to 40 */
  uint8_t clearing_firm[2];               /* bytes 41 to 42 */
  uint8_t transact_time[8];               /* bytes 43 to 50 */
  uint8_t user_info[32];                  /* bytes 51 to 82 */
  uint8_t trade_id[16];                   /* bytes 83 to 98 */
  uint8_t trade_report_id[10];            /* bytes 99 to 108 */
  uint8_t trade_report_type;              /* byte 109 */
  uint8_t trade_report_trans_type;        /* byte 110 */
  uint8_t trade_handling_instr;           /* byte 111 */
  uint8_t trade_report_ref_id[10];        /* bytes 112 to 121 */
  uint8_t trd_ack_status;                 /* byte 122 */
  uint8_t trd_rpt_status;                 /* byte 123 */
  uint8_t trade_report_reject_reason[2];  /* bytes 124 to 125 */
  uint8_t last_px[8];                     /* bytes 126 to 133 */
  uint8_t last_qty[8];                    /* bytes 134 to 141 */
  uint8_t trd_type[2];                    /* bytes 142 to 143 */
  uint8_t trd_sub_type[2];                /* bytes 144 to 145 */
  uint8_t confirm_id[4];                  /* bytes 146 to 149 */
  uint8_t exec_id[16];                    /* bytes 150 to 165 */
  uint8_t side;                           /* byte 166 */
  uint8_t pbuid[6];                       /* bytes 167 to 172 */
  uint8_t account_id[10];                 /* bytes 173 to 182 */
  uint8_t branch_id[2];                   /* bytes 183 to 184 */
  uint8_t counterparty_pbuid[6];          /* bytes 185 to 190 */
  uint8_t counterparty_account_id[10];    /* bytes 191 to 200 */
  uint8_t counterparty_branch_id[2];      /* bytes 201 to 202 */
} MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage;

/* any Market Making Mutual Trade Confirmation Trade Capture Report Ack Message at all: every byte one the checker chooses */
static void any_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  record->trd_ack_status = arbitrary();
  record->trd_rpt_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Ack Message to the wire: 203 bytes from at, returning where the next byte goes */
static size_t encode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(const MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  wire[at++] = record->trd_ack_status;
  wire[at++] = record->trd_rpt_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Ack Message off the wire: 203 bytes from at, returning where the next byte lies */
static size_t decode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  record->trd_ack_status = wire[at++];
  record->trd_rpt_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Market Making Mutual Trade Confirmation Trade Capture Report Ack Message is what was written, byte for byte */
static void equal_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(const MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage *read, const MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  assert(read->trd_ack_status == written->trd_ack_status);
  assert(read->trd_rpt_status == written->trd_rpt_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_reject_reason[i] == written->trade_report_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Ack Message: written and read back, then read and written back */
static void check_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(void) {
  MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage sent;
  MarketMakingMutualTradeConfirmationTradeCaptureReportAckMessage got;
  uint8_t wire[203];
  uint8_t again[203];

  any_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&sent);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&sent, wire, 0) == 203);
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&got, wire, 0) == 203);
  equal_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&got, &sent);

  for (size_t i = 0; i < 203; i++) { wire[i] = arbitrary(); }
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&got, wire, 0) == 203);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_ack_message(&got, again, 0) == 203);
  for (size_t i = 0; i < 203; i++) { assert(again[i] == wire[i]); }
}

/* ---- After Hours Block Trade Trade Capture Report Ack Message: 204 bytes ----- */

/* Trading gateway response to a trade capture report for after hours block trading, ApplID 062. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];                /* bytes 0 to 3 */
  uint8_t report_index[8];                /* bytes 4 to 11 */
  uint8_t appl_id[3];                     /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];             /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];            /* bytes 21 to 26 */
  uint8_t security_id[8];                 /* bytes 27 to 34 */
  uint8_t security_id_source[4];          /* bytes 35 to 38 */
  uint8_t owner_type[2];                  /* bytes 39 to 40 */
  uint8_t clearing_firm[2];               /* bytes 41 to 42 */
  uint8_t transact_time[8];               /* bytes 43 to 50 */
  uint8_t user_info[32];                  /* bytes 51 to 82 */
  uint8_t trade_id[16];                   /* bytes 83 to 98 */
  uint8_t trade_report_id[10];            /* bytes 99 to 108 */
  uint8_t trade_report_type;              /* byte 109 */
  uint8_t trade_report_trans_type;        /* byte 110 */
  uint8_t trade_handling_instr;           /* byte 111 */
  uint8_t trade_report_ref_id[10];        /* bytes 112 to 121 */
  uint8_t trd_ack_status;                 /* byte 122 */
  uint8_t trd_rpt_status;                 /* byte 123 */
  uint8_t trade_report_reject_reason[2];  /* bytes 124 to 125 */
  uint8_t last_px[8];                     /* bytes 126 to 133 */
  uint8_t last_qty[8];                    /* bytes 134 to 141 */
  uint8_t trd_type[2];                    /* bytes 142 to 143 */
  uint8_t trd_sub_type[2];                /* bytes 144 to 145 */
  uint8_t confirm_id[4];                  /* bytes 146 to 149 */
  uint8_t exec_id[16];                    /* bytes 150 to 165 */
  uint8_t side;                           /* byte 166 */
  uint8_t pbuid[6];                       /* bytes 167 to 172 */
  uint8_t account_id[10];                 /* bytes 173 to 182 */
  uint8_t branch_id[2];                   /* bytes 183 to 184 */
  uint8_t counterparty_pbuid[6];          /* bytes 185 to 190 */
  uint8_t counterparty_account_id[10];    /* bytes 191 to 200 */
  uint8_t counterparty_branch_id[2];      /* bytes 201 to 202 */
  uint8_t cash_margin;                    /* byte 203 */
} AfterHoursBlockTradeTradeCaptureReportAckMessage;

/* any After Hours Block Trade Trade Capture Report Ack Message at all: every byte one the checker chooses */
static void any_after_hours_block_trade_trade_capture_report_ack_message(AfterHoursBlockTradeTradeCaptureReportAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = arbitrary(); }
  record->trd_ack_status = arbitrary();
  record->trd_rpt_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  record->cash_margin = arbitrary();
}

/* After Hours Block Trade Trade Capture Report Ack Message to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_after_hours_block_trade_trade_capture_report_ack_message(const AfterHoursBlockTradeTradeCaptureReportAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_ref_id[i]; }
  wire[at++] = record->trd_ack_status;
  wire[at++] = record->trd_rpt_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_report_reject_reason[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  wire[at++] = record->cash_margin;

  return at;
}

/* After Hours Block Trade Trade Capture Report Ack Message off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_after_hours_block_trade_trade_capture_report_ack_message(AfterHoursBlockTradeTradeCaptureReportAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->trade_report_ref_id[i] = wire[at++]; }
  record->trd_ack_status = wire[at++];
  record->trd_rpt_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_report_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of After Hours Block Trade Trade Capture Report Ack Message is what was written, byte for byte */
static void equal_after_hours_block_trade_trade_capture_report_ack_message(const AfterHoursBlockTradeTradeCaptureReportAckMessage *read, const AfterHoursBlockTradeTradeCaptureReportAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_ref_id[i] == written->trade_report_ref_id[i]); }
  assert(read->trd_ack_status == written->trd_ack_status);
  assert(read->trd_rpt_status == written->trd_rpt_status);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_report_reject_reason[i] == written->trade_report_reject_reason[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  assert(read->cash_margin == written->cash_margin);
}

/* After Hours Block Trade Trade Capture Report Ack Message: written and read back, then read and written back */
static void check_after_hours_block_trade_trade_capture_report_ack_message(void) {
  AfterHoursBlockTradeTradeCaptureReportAckMessage sent;
  AfterHoursBlockTradeTradeCaptureReportAckMessage got;
  uint8_t wire[204];
  uint8_t again[204];

  any_after_hours_block_trade_trade_capture_report_ack_message(&sent);
  assert(encode_after_hours_block_trade_trade_capture_report_ack_message(&sent, wire, 0) == 204);
  assert(decode_after_hours_block_trade_trade_capture_report_ack_message(&got, wire, 0) == 204);
  equal_after_hours_block_trade_trade_capture_report_ack_message(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_after_hours_block_trade_trade_capture_report_ack_message(&got, wire, 0) == 204);
  assert(encode_after_hours_block_trade_trade_capture_report_ack_message(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bond Spot Negotiated Trade Capture Report Confirmation Message: 334 bytes ---- */

/* Trade confirmation of a trade capture report for spot bond trading by negotiation, ApplID 031. */
typedef struct {
  uint8_t partition_no[4];              /* bytes 0 to 3 */
  uint8_t report_index[8];              /* bytes 4 to 11 */
  uint8_t appl_id[3];                   /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];           /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];          /* bytes 21 to 26 */
  uint8_t security_id[8];               /* bytes 27 to 34 */
  uint8_t security_id_source[4];        /* bytes 35 to 38 */
  uint8_t owner_type[2];                /* bytes 39 to 40 */
  uint8_t clearing_firm[2];             /* bytes 41 to 42 */
  uint8_t transact_time[8];             /* bytes 43 to 50 */
  uint8_t user_info[32];                /* bytes 51 to 82 */
  uint8_t trade_id[16];                 /* bytes 83 to 98 */
  uint8_t trade_report_id[10];          /* bytes 99 to 108 */
  uint8_t trade_report_type;            /* byte 109 */
  uint8_t trade_report_trans_type;      /* byte 110 */
  uint8_t trade_handling_instr;         /* byte 111 */
  uint8_t last_px[8];                   /* bytes 112 to 119 */
  uint8_t last_qty[8];                  /* bytes 120 to 127 */
  uint8_t trd_type[2];                  /* bytes 128 to 129 */
  uint8_t trd_sub_type[2];              /* bytes 130 to 131 */
  uint8_t confirm_id[4];                /* bytes 132 to 135 */
  uint8_t exec_id[16];                  /* bytes 136 to 151 */
  uint8_t side;                         /* byte 152 */
  uint8_t pbuid[6];                     /* bytes 153 to 158 */
  uint8_t account_id[10];               /* bytes 159 to 168 */
  uint8_t branch_id[2];                 /* bytes 169 to 170 */
  uint8_t counterparty_pbuid[6];        /* bytes 171 to 176 */
  uint8_t counterparty_account_id[10];  /* bytes 177 to 186 */
  uint8_t counterparty_branch_id[2];    /* bytes 187 to 188 */
  uint8_t member_id[6];                 /* bytes 189 to 194 */
  uint8_t trader_code[5];               /* bytes 195 to 199 */
  uint8_t counterparty_member_id[6];    /* bytes 200 to 205 */
  uint8_t counterparty_trader_code[5];  /* bytes 206 to 210 */
  uint8_t settl_type;                   /* byte 211 */
  uint8_t settl_period;                 /* byte 212 */
  uint8_t cash_margin;                  /* byte 213 */
  uint8_t memo[120];                    /* bytes 214 to 333 */
} BondSpotNegotiatedTradeCaptureReportConfirmationMessage;

/* any Bond Spot Negotiated Trade Capture Report Confirmation Message at all: every byte one the checker chooses */
static void any_bond_spot_negotiated_trade_capture_report_confirmation_message(BondSpotNegotiatedTradeCaptureReportConfirmationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = arbitrary(); }
  record->settl_type = arbitrary();
  record->settl_period = arbitrary();
  record->cash_margin = arbitrary();
  for (size_t i = 0; i < 120; i++) { record->memo[i] = arbitrary(); }
}

/* Bond Spot Negotiated Trade Capture Report Confirmation Message to the wire: 334 bytes from at, returning where the next byte goes */
static size_t encode_bond_spot_negotiated_trade_capture_report_confirmation_message(const BondSpotNegotiatedTradeCaptureReportConfirmationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->trader_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_member_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->counterparty_trader_code[i]; }
  wire[at++] = record->settl_type;
  wire[at++] = record->settl_period;
  wire[at++] = record->cash_margin;
  for (size_t i = 0; i < 120; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Bond Spot Negotiated Trade Capture Report Confirmation Message off the wire: 334 bytes from at, returning where the next byte lies */
static size_t decode_bond_spot_negotiated_trade_capture_report_confirmation_message(BondSpotNegotiatedTradeCaptureReportConfirmationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->trader_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_member_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->counterparty_trader_code[i] = wire[at++]; }
  record->settl_type = wire[at++];
  record->settl_period = wire[at++];
  record->cash_margin = wire[at++];
  for (size_t i = 0; i < 120; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Bond Spot Negotiated Trade Capture Report Confirmation Message is what was written, byte for byte */
static void equal_bond_spot_negotiated_trade_capture_report_confirmation_message(const BondSpotNegotiatedTradeCaptureReportConfirmationMessage *read, const BondSpotNegotiatedTradeCaptureReportConfirmationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->member_id[i] == written->member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->trader_code[i] == written->trader_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_member_id[i] == written->counterparty_member_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->counterparty_trader_code[i] == written->counterparty_trader_code[i]); }
  assert(read->settl_type == written->settl_type);
  assert(read->settl_period == written->settl_period);
  assert(read->cash_margin == written->cash_margin);
  for (size_t i = 0; i < 120; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Bond Spot Negotiated Trade Capture Report Confirmation Message: written and read back, then read and written back */
static void check_bond_spot_negotiated_trade_capture_report_confirmation_message(void) {
  BondSpotNegotiatedTradeCaptureReportConfirmationMessage sent;
  BondSpotNegotiatedTradeCaptureReportConfirmationMessage got;
  uint8_t wire[334];
  uint8_t again[334];

  any_bond_spot_negotiated_trade_capture_report_confirmation_message(&sent);
  assert(encode_bond_spot_negotiated_trade_capture_report_confirmation_message(&sent, wire, 0) == 334);
  assert(decode_bond_spot_negotiated_trade_capture_report_confirmation_message(&got, wire, 0) == 334);
  equal_bond_spot_negotiated_trade_capture_report_confirmation_message(&got, &sent);

  for (size_t i = 0; i < 334; i++) { wire[i] = arbitrary(); }
  assert(decode_bond_spot_negotiated_trade_capture_report_confirmation_message(&got, wire, 0) == 334);
  assert(encode_bond_spot_negotiated_trade_capture_report_confirmation_message(&got, again, 0) == 334);
  for (size_t i = 0; i < 334; i++) { assert(again[i] == wire[i]); }
}

/* ---- Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message: 198 bytes ---- */

/* Trade confirmation of a trade capture report for refinancing securities lending by agreement, ApplID 051. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];              /* bytes 0 to 3 */
  uint8_t report_index[8];              /* bytes 4 to 11 */
  uint8_t appl_id[3];                   /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];           /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];          /* bytes 21 to 26 */
  uint8_t security_id[8];               /* bytes 27 to 34 */
  uint8_t security_id_source[4];        /* bytes 35 to 38 */
  uint8_t owner_type[2];                /* bytes 39 to 40 */
  uint8_t clearing_firm[2];             /* bytes 41 to 42 */
  uint8_t transact_time[8];             /* bytes 43 to 50 */
  uint8_t user_info[32];                /* bytes 51 to 82 */
  uint8_t trade_id[16];                 /* bytes 83 to 98 */
  uint8_t trade_report_id[10];          /* bytes 99 to 108 */
  uint8_t trade_report_type;            /* byte 109 */
  uint8_t trade_report_trans_type;      /* byte 110 */
  uint8_t trade_handling_instr;         /* byte 111 */
  uint8_t last_px[8];                   /* bytes 112 to 119 */
  uint8_t last_qty[8];                  /* bytes 120 to 127 */
  uint8_t trd_type[2];                  /* bytes 128 to 129 */
  uint8_t trd_sub_type[2];              /* bytes 130 to 131 */
  uint8_t confirm_id[4];                /* bytes 132 to 135 */
  uint8_t exec_id[16];                  /* bytes 136 to 151 */
  uint8_t side;                         /* byte 152 */
  uint8_t pbuid[6];                     /* bytes 153 to 158 */
  uint8_t account_id[10];               /* bytes 159 to 168 */
  uint8_t branch_id[2];                 /* bytes 169 to 170 */
  uint8_t counterparty_pbuid[6];        /* bytes 171 to 176 */
  uint8_t counterparty_account_id[10];  /* bytes 177 to 186 */
  uint8_t counterparty_branch_id[2];    /* bytes 187 to 188 */
  uint8_t expiration_days[2];           /* bytes 189 to 190 */
  uint8_t expiration_type;              /* byte 191 */
  uint8_t maturity_date[4];             /* bytes 192 to 195 */
  uint8_t share_property[2];            /* bytes 196 to 197 */
} RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc;

/* any Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message at all: every byte one the checker chooses */
static void any_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = arbitrary(); }
  record->expiration_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = arbitrary(); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message to the wire: 198 bytes from at, returning where the next byte goes */
static size_t encode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(const RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expiration_days[i]; }
  wire[at++] = record->expiration_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->share_property[i]; }

  return at;
}

/* Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message off the wire: 198 bytes from at, returning where the next byte lies */
static size_t decode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expiration_days[i] = wire[at++]; }
  record->expiration_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->share_property[i] = wire[at++]; }

  return at;
}

/* what was read of Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message is what was written, byte for byte */
static void equal_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(const RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc *read, const RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expiration_days[i] == written->expiration_days[i]); }
  assert(read->expiration_type == written->expiration_type);
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->share_property[i] == written->share_property[i]); }
}

/* Refinancing Securities Lending Agreed Trade Capture Report Confirmation Message: written and read back, then read and written back */
static void check_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(void) {
  RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc sent;
  RefinancingSecuritiesLendingAgreedTradeCaptureReportConfi_mi0bzc got;
  uint8_t wire[198];
  uint8_t again[198];

  any_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&sent);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&sent, wire, 0) == 198);
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&got, wire, 0) == 198);
  equal_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&got, &sent);

  for (size_t i = 0; i < 198; i++) { wire[i] = arbitrary(); }
  assert(decode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&got, wire, 0) == 198);
  assert(encode_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc(&got, again, 0) == 198);
  for (size_t i = 0; i < 198; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mutual Trade Confirmation Trade Capture Report Confirmation Message: 189 bytes ---- */

/* Trade confirmation of a trade capture report for mutual trade confirmation, ApplID 060. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];              /* bytes 0 to 3 */
  uint8_t report_index[8];              /* bytes 4 to 11 */
  uint8_t appl_id[3];                   /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];           /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];          /* bytes 21 to 26 */
  uint8_t security_id[8];               /* bytes 27 to 34 */
  uint8_t security_id_source[4];        /* bytes 35 to 38 */
  uint8_t owner_type[2];                /* bytes 39 to 40 */
  uint8_t clearing_firm[2];             /* bytes 41 to 42 */
  uint8_t transact_time[8];             /* bytes 43 to 50 */
  uint8_t user_info[32];                /* bytes 51 to 82 */
  uint8_t trade_id[16];                 /* bytes 83 to 98 */
  uint8_t trade_report_id[10];          /* bytes 99 to 108 */
  uint8_t trade_report_type;            /* byte 109 */
  uint8_t trade_report_trans_type;      /* byte 110 */
  uint8_t trade_handling_instr;         /* byte 111 */
  uint8_t last_px[8];                   /* bytes 112 to 119 */
  uint8_t last_qty[8];                  /* bytes 120 to 127 */
  uint8_t trd_type[2];                  /* bytes 128 to 129 */
  uint8_t trd_sub_type[2];              /* bytes 130 to 131 */
  uint8_t confirm_id[4];                /* bytes 132 to 135 */
  uint8_t exec_id[16];                  /* bytes 136 to 151 */
  uint8_t side;                         /* byte 152 */
  uint8_t pbuid[6];                     /* bytes 153 to 158 */
  uint8_t account_id[10];               /* bytes 159 to 168 */
  uint8_t branch_id[2];                 /* bytes 169 to 170 */
  uint8_t counterparty_pbuid[6];        /* bytes 171 to 176 */
  uint8_t counterparty_account_id[10];  /* bytes 177 to 186 */
  uint8_t counterparty_branch_id[2];    /* bytes 187 to 188 */
} MutualTradeConfirmationTradeCaptureReportConfirmationMessage;

/* any Mutual Trade Confirmation Trade Capture Report Confirmation Message at all: every byte one the checker chooses */
static void any_mutual_trade_confirmation_trade_capture_report_confirmation_message(MutualTradeConfirmationTradeCaptureReportConfirmationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Mutual Trade Confirmation Trade Capture Report Confirmation Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_mutual_trade_confirmation_trade_capture_report_confirmation_message(const MutualTradeConfirmationTradeCaptureReportConfirmationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Mutual Trade Confirmation Trade Capture Report Confirmation Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_mutual_trade_confirmation_trade_capture_report_confirmation_message(MutualTradeConfirmationTradeCaptureReportConfirmationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mutual Trade Confirmation Trade Capture Report Confirmation Message is what was written, byte for byte */
static void equal_mutual_trade_confirmation_trade_capture_report_confirmation_message(const MutualTradeConfirmationTradeCaptureReportConfirmationMessage *read, const MutualTradeConfirmationTradeCaptureReportConfirmationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Mutual Trade Confirmation Trade Capture Report Confirmation Message: written and read back, then read and written back */
static void check_mutual_trade_confirmation_trade_capture_report_confirmation_message(void) {
  MutualTradeConfirmationTradeCaptureReportConfirmationMessage sent;
  MutualTradeConfirmationTradeCaptureReportConfirmationMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_mutual_trade_confirmation_trade_capture_report_confirmation_message(&sent);
  assert(encode_mutual_trade_confirmation_trade_capture_report_confirmation_message(&sent, wire, 0) == 189);
  assert(decode_mutual_trade_confirmation_trade_capture_report_confirmation_message(&got, wire, 0) == 189);
  equal_mutual_trade_confirmation_trade_capture_report_confirmation_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_mutual_trade_confirmation_trade_capture_report_confirmation_message(&got, wire, 0) == 189);
  assert(encode_mutual_trade_confirmation_trade_capture_report_confirmation_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message: 189 bytes ---- */

/* Trade confirmation of a trade capture report for market making mutual trade confirmation, ApplID 061. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];              /* bytes 0 to 3 */
  uint8_t report_index[8];              /* bytes 4 to 11 */
  uint8_t appl_id[3];                   /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];           /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];          /* bytes 21 to 26 */
  uint8_t security_id[8];               /* bytes 27 to 34 */
  uint8_t security_id_source[4];        /* bytes 35 to 38 */
  uint8_t owner_type[2];                /* bytes 39 to 40 */
  uint8_t clearing_firm[2];             /* bytes 41 to 42 */
  uint8_t transact_time[8];             /* bytes 43 to 50 */
  uint8_t user_info[32];                /* bytes 51 to 82 */
  uint8_t trade_id[16];                 /* bytes 83 to 98 */
  uint8_t trade_report_id[10];          /* bytes 99 to 108 */
  uint8_t trade_report_type;            /* byte 109 */
  uint8_t trade_report_trans_type;      /* byte 110 */
  uint8_t trade_handling_instr;         /* byte 111 */
  uint8_t last_px[8];                   /* bytes 112 to 119 */
  uint8_t last_qty[8];                  /* bytes 120 to 127 */
  uint8_t trd_type[2];                  /* bytes 128 to 129 */
  uint8_t trd_sub_type[2];              /* bytes 130 to 131 */
  uint8_t confirm_id[4];                /* bytes 132 to 135 */
  uint8_t exec_id[16];                  /* bytes 136 to 151 */
  uint8_t side;                         /* byte 152 */
  uint8_t pbuid[6];                     /* bytes 153 to 158 */
  uint8_t account_id[10];               /* bytes 159 to 168 */
  uint8_t branch_id[2];                 /* bytes 169 to 170 */
  uint8_t counterparty_pbuid[6];        /* bytes 171 to 176 */
  uint8_t counterparty_account_id[10];  /* bytes 177 to 186 */
  uint8_t counterparty_branch_id[2];    /* bytes 187 to 188 */
} MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr;

/* any Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message at all: every byte one the checker chooses */
static void any_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(const MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }

  return at;
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }

  return at;
}

/* what was read of Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message is what was written, byte for byte */
static void equal_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(const MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr *read, const MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
}

/* Market Making Mutual Trade Confirmation Trade Capture Report Confirmation Message: written and read back, then read and written back */
static void check_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(void) {
  MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr sent;
  MarketMakingMutualTradeConfirmationTradeCaptureReportConf_wnbyqr got;
  uint8_t wire[189];
  uint8_t again[189];

  any_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&sent);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&sent, wire, 0) == 189);
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&got, wire, 0) == 189);
  equal_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&got, wire, 0) == 189);
  assert(encode_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- After Hours Block Trade Trade Capture Report Confirmation Message: 190 bytes ---- */

/* Trade confirmation of a trade capture report for after hours block trading, ApplID 062. Not yet enabled. */
typedef struct {
  uint8_t partition_no[4];              /* bytes 0 to 3 */
  uint8_t report_index[8];              /* bytes 4 to 11 */
  uint8_t appl_id[3];                   /* bytes 12 to 14 */
  uint8_t reporting_pbuid[6];           /* bytes 15 to 20 */
  uint8_t submitting_pbuid[6];          /* bytes 21 to 26 */
  uint8_t security_id[8];               /* bytes 27 to 34 */
  uint8_t security_id_source[4];        /* bytes 35 to 38 */
  uint8_t owner_type[2];                /* bytes 39 to 40 */
  uint8_t clearing_firm[2];             /* bytes 41 to 42 */
  uint8_t transact_time[8];             /* bytes 43 to 50 */
  uint8_t user_info[32];                /* bytes 51 to 82 */
  uint8_t trade_id[16];                 /* bytes 83 to 98 */
  uint8_t trade_report_id[10];          /* bytes 99 to 108 */
  uint8_t trade_report_type;            /* byte 109 */
  uint8_t trade_report_trans_type;      /* byte 110 */
  uint8_t trade_handling_instr;         /* byte 111 */
  uint8_t last_px[8];                   /* bytes 112 to 119 */
  uint8_t last_qty[8];                  /* bytes 120 to 127 */
  uint8_t trd_type[2];                  /* bytes 128 to 129 */
  uint8_t trd_sub_type[2];              /* bytes 130 to 131 */
  uint8_t confirm_id[4];                /* bytes 132 to 135 */
  uint8_t exec_id[16];                  /* bytes 136 to 151 */
  uint8_t side;                         /* byte 152 */
  uint8_t pbuid[6];                     /* bytes 153 to 158 */
  uint8_t account_id[10];               /* bytes 159 to 168 */
  uint8_t branch_id[2];                 /* bytes 169 to 170 */
  uint8_t counterparty_pbuid[6];        /* bytes 171 to 176 */
  uint8_t counterparty_account_id[10];  /* bytes 177 to 186 */
  uint8_t counterparty_branch_id[2];    /* bytes 187 to 188 */
  uint8_t cash_margin;                  /* byte 189 */
} AfterHoursBlockTradeTradeCaptureReportConfirmationMessage;

/* any After Hours Block Trade Trade Capture Report Confirmation Message at all: every byte one the checker chooses */
static void any_after_hours_block_trade_trade_capture_report_confirmation_message(AfterHoursBlockTradeTradeCaptureReportConfirmationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = arbitrary(); }
  record->trade_report_type = arbitrary();
  record->trade_report_trans_type = arbitrary();
  record->trade_handling_instr = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = arbitrary(); }
  record->cash_margin = arbitrary();
}

/* After Hours Block Trade Trade Capture Report Confirmation Message to the wire: 190 bytes from at, returning where the next byte goes */
static size_t encode_after_hours_block_trade_trade_capture_report_confirmation_message(const AfterHoursBlockTradeTradeCaptureReportConfirmationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->partition_no[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->report_index[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->appl_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reporting_pbuid[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->submitting_pbuid[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->security_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_source[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->owner_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->user_info[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->trade_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_report_id[i]; }
  wire[at++] = record->trade_report_type;
  wire[at++] = record->trade_report_trans_type;
  wire[at++] = record->trade_handling_instr;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_type[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trd_sub_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->confirm_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->exec_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->branch_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->counterparty_pbuid[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->counterparty_account_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->counterparty_branch_id[i]; }
  wire[at++] = record->cash_margin;

  return at;
}

/* After Hours Block Trade Trade Capture Report Confirmation Message off the wire: 190 bytes from at, returning where the next byte lies */
static size_t decode_after_hours_block_trade_trade_capture_report_confirmation_message(AfterHoursBlockTradeTradeCaptureReportConfirmationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->partition_no[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->report_index[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->appl_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reporting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->submitting_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_source[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->owner_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 32; i++) { record->user_info[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->trade_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_report_id[i] = wire[at++]; }
  record->trade_report_type = wire[at++];
  record->trade_report_trans_type = wire[at++];
  record->trade_handling_instr = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_type[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->trd_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->confirm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->exec_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->branch_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->counterparty_pbuid[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->counterparty_account_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->counterparty_branch_id[i] = wire[at++]; }
  record->cash_margin = wire[at++];

  return at;
}

/* what was read of After Hours Block Trade Trade Capture Report Confirmation Message is what was written, byte for byte */
static void equal_after_hours_block_trade_trade_capture_report_confirmation_message(const AfterHoursBlockTradeTradeCaptureReportConfirmationMessage *read, const AfterHoursBlockTradeTradeCaptureReportConfirmationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->partition_no[i] == written->partition_no[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->report_index[i] == written->report_index[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->appl_id[i] == written->appl_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reporting_pbuid[i] == written->reporting_pbuid[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->submitting_pbuid[i] == written->submitting_pbuid[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->security_id[i] == written->security_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_source[i] == written->security_id_source[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->owner_type[i] == written->owner_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 32; i++) { assert(read->user_info[i] == written->user_info[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_report_id[i] == written->trade_report_id[i]); }
  assert(read->trade_report_type == written->trade_report_type);
  assert(read->trade_report_trans_type == written->trade_report_trans_type);
  assert(read->trade_handling_instr == written->trade_handling_instr);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_type[i] == written->trd_type[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->trd_sub_type[i] == written->trd_sub_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->confirm_id[i] == written->confirm_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->exec_id[i] == written->exec_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 6; i++) { assert(read->pbuid[i] == written->pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->account_id[i] == written->account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->branch_id[i] == written->branch_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->counterparty_pbuid[i] == written->counterparty_pbuid[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->counterparty_account_id[i] == written->counterparty_account_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->counterparty_branch_id[i] == written->counterparty_branch_id[i]); }
  assert(read->cash_margin == written->cash_margin);
}

/* After Hours Block Trade Trade Capture Report Confirmation Message: written and read back, then read and written back */
static void check_after_hours_block_trade_trade_capture_report_confirmation_message(void) {
  AfterHoursBlockTradeTradeCaptureReportConfirmationMessage sent;
  AfterHoursBlockTradeTradeCaptureReportConfirmationMessage got;
  uint8_t wire[190];
  uint8_t again[190];

  any_after_hours_block_trade_trade_capture_report_confirmation_message(&sent);
  assert(encode_after_hours_block_trade_trade_capture_report_confirmation_message(&sent, wire, 0) == 190);
  assert(decode_after_hours_block_trade_trade_capture_report_confirmation_message(&got, wire, 0) == 190);
  equal_after_hours_block_trade_trade_capture_report_confirmation_message(&got, &sent);

  for (size_t i = 0; i < 190; i++) { wire[i] = arbitrary(); }
  assert(decode_after_hours_block_trade_trade_capture_report_confirmation_message(&got, wire, 0) == 190);
  assert(encode_after_hours_block_trade_trade_capture_report_confirmation_message(&got, again, 0) == 190);
  for (size_t i = 0; i < 190; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_message();
  check_logout_message();
  check_business_reject_message();
  check_platform_state_info_message();
  check_report_finished_message();
  check_trading_session_status_message();
  check_bond_spot_matching_new_order_message();
  check_centralized_auction_new_order_message();
  check_conversion_new_order_message();
  check_inquiry_new_order_message();
  check_subscription_new_order_message();
  check_put_back_new_order_message();
  check_tender_offer_acceptance_new_order_message();
  check_refinancing_securities_lending_non_agreed_new_order_message();
  check_order_cancel_request_message();
  check_cancel_reject_message();
  check_bond_spot_matching_execution_report_message();
  check_centralized_auction_execution_report_message();
  check_conversion_execution_report_message();
  check_inquiry_execution_report_message();
  check_subscription_execution_report_message();
  check_put_back_execution_report_message();
  check_tender_offer_acceptance_execution_report_message();
  check_refinancing_securities_lending_non_agreed_execution_report_message();
  check_bond_spot_matching_trade_execution_report_message();
  check_centralized_auction_trade_execution_report_message();
  check_refinancing_securities_lending_non_agreed_trade_execution_report_message();
  check_bond_spot_negotiated_trade_capture_report_message();
  check_refinancing_securities_lending_agreed_trade_capture_report_message();
  check_mutual_trade_confirmation_trade_capture_report_message();
  check_market_making_mutual_trade_confirmation_trade_capture_report_message();
  check_after_hours_block_trade_trade_capture_report_message();
  check_bond_spot_negotiated_trade_capture_report_ack_message();
  check_refinancing_securities_lending_agreed_trade_capture_report_ack_message();
  check_mutual_trade_confirmation_trade_capture_report_ack_message();
  check_market_making_mutual_trade_confirmation_trade_capture_report_ack_message();
  check_after_hours_block_trade_trade_capture_report_ack_message();
  check_bond_spot_negotiated_trade_capture_report_confirmation_message();
  check_refinancing_securities_lending_agreed_trade_capture_report_confi_mi0bzc();
  check_mutual_trade_confirmation_trade_capture_report_confirmation_message();
  check_market_making_mutual_trade_confirmation_trade_capture_report_conf_wnbyqr();
  check_after_hours_block_trade_trade_capture_report_confirmation_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
