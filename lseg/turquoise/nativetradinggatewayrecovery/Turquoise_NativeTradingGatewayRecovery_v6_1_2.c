// lseg/turquoise/nativetradinggatewayrecovery/Turquoise_NativeTradingGatewayRecovery_v6_1_2.c
/*
 * London Stock Exchange Native Trading Gateway Recovery
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Native Trading Gateway Message Header */
typedef struct {
  uint8_t start_of_message;   /* byte 0 */
  uint8_t message_length[2];  /* bytes 1 to 2 */
  uint8_t message_type;       /* byte 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->start_of_message = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->start_of_message;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->start_of_message = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->start_of_message == written->start_of_message);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 76 bytes ------------------------------------------------- */

/* Allows the Participant and server to establish a session. */
typedef struct {
  uint8_t comp_id[25];       /* bytes 0 to 24 */
  uint8_t password[25];      /* bytes 25 to 49 */
  uint8_t new_password[25];  /* bytes 50 to 74 */
  uint8_t message_version;   /* byte 75 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 25; i++) { record->comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = arbitrary(); }
  record->message_version = arbitrary();
}

/* Logon Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->comp_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->new_password[i]; }
  wire[at++] = record->message_version;

  return at;
}

/* Logon Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 25; i++) { record->comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = wire[at++]; }
  record->message_version = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 25; i++) { assert(read->comp_id[i] == written->comp_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->new_password[i] == written->new_password[i]); }
  assert(read->message_version == written->message_version);
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 76);
  assert(decode_logon_message(&got, wire, 0) == 76);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 76);
  assert(encode_logon_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Reply Message: 34 bytes ------------------------------------------- */

/* Allows the server to acknowledge a Participant's Logon. */
typedef struct {
  uint8_t reject_code[4];                 /* bytes 0 to 3 */
  uint8_t password_expiry_day_count[30];  /* bytes 4 to 33 */
} LogonReplyMessage;

/* any Logon Reply Message at all: every byte one the checker chooses */
static void any_logon_reply_message(LogonReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->password_expiry_day_count[i] = arbitrary(); }
}

/* Logon Reply Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_logon_reply_message(const LogonReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->password_expiry_day_count[i]; }

  return at;
}

/* Logon Reply Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_logon_reply_message(LogonReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->password_expiry_day_count[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Reply Message is what was written, byte for byte */
static void equal_logon_reply_message(const LogonReplyMessage *read, const LogonReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->password_expiry_day_count[i] == written->password_expiry_day_count[i]); }
}

/* Logon Reply Message: written and read back, then read and written back */
static void check_logon_reply_message(void) {
  LogonReplyMessage sent;
  LogonReplyMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_logon_reply_message(&sent);
  assert(encode_logon_reply_message(&sent, wire, 0) == 34);
  assert(decode_logon_reply_message(&got, wire, 0) == 34);
  equal_logon_reply_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_reply_message(&got, wire, 0) == 34);
  assert(encode_logon_reply_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 20 bytes ------------------------------------------------ */

/* Allows the Participant and server to terminate a session. */
typedef struct {
  uint8_t logout_reason[20];  /* bytes 0 to 19 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->logout_reason[i] = arbitrary(); }
}

/* Logout Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->logout_reason[i]; }

  return at;
}

/* Logout Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->logout_reason[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->logout_reason[i] == written->logout_reason[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 20);
  assert(decode_logout_message(&got, wire, 0) == 20);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 20);
  assert(encode_logout_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Missed Message Request Message: 5 bytes --------------------------------- */

/* Allows the Participant to subscribe to missed messages through the Recovery Channel. */
typedef struct {
  uint8_t app_id;               /* byte 0 */
  uint8_t last_msg_seq_num[4];  /* bytes 1 to 4 */
} MissedMessageRequestMessage;

/* any Missed Message Request Message at all: every byte one the checker chooses */
static void any_missed_message_request_message(MissedMessageRequestMessage *record) {
  record->app_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num[i] = arbitrary(); }
}

/* Missed Message Request Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_missed_message_request_message(const MissedMessageRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_msg_seq_num[i]; }

  return at;
}

/* Missed Message Request Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_missed_message_request_message(MissedMessageRequestMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_msg_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Missed Message Request Message is what was written, byte for byte */
static void equal_missed_message_request_message(const MissedMessageRequestMessage *read, const MissedMessageRequestMessage *written) {
  assert(read->app_id == written->app_id);
  for (size_t i = 0; i < 4; i++) { assert(read->last_msg_seq_num[i] == written->last_msg_seq_num[i]); }
}

/* Missed Message Request Message: written and read back, then read and written back */
static void check_missed_message_request_message(void) {
  MissedMessageRequestMessage sent;
  MissedMessageRequestMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_missed_message_request_message(&sent);
  assert(encode_missed_message_request_message(&sent, wire, 0) == 5);
  assert(decode_missed_message_request_message(&got, wire, 0) == 5);
  equal_missed_message_request_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_missed_message_request_message(&got, wire, 0) == 5);
  assert(encode_missed_message_request_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Missed Message Request Ack Message: 1 byte ------------------------------ */

/* Allows the server to acknowledge a Participant's Missed Message Request. */
typedef struct {
  uint8_t missed_message_request_ack_response_type;  /* byte 0 */
} MissedMessageRequestAckMessage;

/* any Missed Message Request Ack Message at all: every byte one the checker chooses */
static void any_missed_message_request_ack_message(MissedMessageRequestAckMessage *record) {
  record->missed_message_request_ack_response_type = arbitrary();
}

/* Missed Message Request Ack Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_missed_message_request_ack_message(const MissedMessageRequestAckMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->missed_message_request_ack_response_type;

  return at;
}

/* Missed Message Request Ack Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_missed_message_request_ack_message(MissedMessageRequestAckMessage *record, const uint8_t *wire, size_t at) {
  record->missed_message_request_ack_response_type = wire[at++];

  return at;
}

/* what was read of Missed Message Request Ack Message is what was written, byte for byte */
static void equal_missed_message_request_ack_message(const MissedMessageRequestAckMessage *read, const MissedMessageRequestAckMessage *written) {
  assert(read->missed_message_request_ack_response_type == written->missed_message_request_ack_response_type);
}

/* Missed Message Request Ack Message: written and read back, then read and written back */
static void check_missed_message_request_ack_message(void) {
  MissedMessageRequestAckMessage sent;
  MissedMessageRequestAckMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_missed_message_request_ack_message(&sent);
  assert(encode_missed_message_request_ack_message(&sent, wire, 0) == 1);
  assert(decode_missed_message_request_ack_message(&got, wire, 0) == 1);
  equal_missed_message_request_ack_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_missed_message_request_ack_message(&got, wire, 0) == 1);
  assert(encode_missed_message_request_ack_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Missed Message Report Message: 1 byte ----------------------------------- */

/* Allows the Server to communicate the result of a Missed Message Request. */
typedef struct {
  uint8_t missed_message_report_response_type;  /* byte 0 */
} MissedMessageReportMessage;

/* any Missed Message Report Message at all: every byte one the checker chooses */
static void any_missed_message_report_message(MissedMessageReportMessage *record) {
  record->missed_message_report_response_type = arbitrary();
}

/* Missed Message Report Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_missed_message_report_message(const MissedMessageReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->missed_message_report_response_type;

  return at;
}

/* Missed Message Report Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_missed_message_report_message(MissedMessageReportMessage *record, const uint8_t *wire, size_t at) {
  record->missed_message_report_response_type = wire[at++];

  return at;
}

/* what was read of Missed Message Report Message is what was written, byte for byte */
static void equal_missed_message_report_message(const MissedMessageReportMessage *read, const MissedMessageReportMessage *written) {
  assert(read->missed_message_report_response_type == written->missed_message_report_response_type);
}

/* Missed Message Report Message: written and read back, then read and written back */
static void check_missed_message_report_message(void) {
  MissedMessageReportMessage sent;
  MissedMessageReportMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_missed_message_report_message(&sent);
  assert(encode_missed_message_report_message(&sent, wire, 0) == 1);
  assert(decode_missed_message_report_message(&got, wire, 0) == 1);
  equal_missed_message_report_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_missed_message_report_message(&got, wire, 0) == 1);
  assert(encode_missed_message_report_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 55 bytes ------------------------------------------------ */

/* Allows the Server to reject a message that does not comply with the Native Trading Gateway messaging protocol. */
typedef struct {
  uint8_t reject_code[4];         /* bytes 0 to 3 */
  uint8_t reject_reason[30];      /* bytes 4 to 33 */
  uint8_t rejected_message_type;  /* byte 34 */
  uint8_t client_order_id[20];    /* bytes 35 to 54 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->reject_reason[i] = arbitrary(); }
  record->rejected_message_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
}

/* Reject Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->reject_reason[i]; }
  wire[at++] = record->rejected_message_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }

  return at;
}

/* Reject Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->reject_reason[i] = wire[at++]; }
  record->rejected_message_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
  assert(read->rejected_message_type == written->rejected_message_type);
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 55);
  assert(decode_reject_message(&got, wire, 0) == 55);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 55);
  assert(encode_reject_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Status Message: 2 bytes ------------------------------------------ */

/* Sent to All Native Recovery Channel Participants on the event of Order Cache Outage. */
typedef struct {
  uint8_t app_id;      /* byte 0 */
  uint8_t app_status;  /* byte 1 */
} SystemStatusMessage;

/* any System Status Message at all: every byte one the checker chooses */
static void any_system_status_message(SystemStatusMessage *record) {
  record->app_id = arbitrary();
  record->app_status = arbitrary();
}

/* System Status Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_system_status_message(const SystemStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  wire[at++] = record->app_status;

  return at;
}

/* System Status Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_system_status_message(SystemStatusMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  record->app_status = wire[at++];

  return at;
}

/* what was read of System Status Message is what was written, byte for byte */
static void equal_system_status_message(const SystemStatusMessage *read, const SystemStatusMessage *written) {
  assert(read->app_id == written->app_id);
  assert(read->app_status == written->app_status);
}

/* System Status Message: written and read back, then read and written back */
static void check_system_status_message(void) {
  SystemStatusMessage sent;
  SystemStatusMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_system_status_message(&sent);
  assert(encode_system_status_message(&sent, wire, 0) == 2);
  assert(decode_system_status_message(&got, wire, 0) == 2);
  equal_system_status_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_system_status_message(&got, wire, 0) == 2);
  assert(encode_system_status_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transact Time: 8 bytes -------------------------------------------------- */

/* Composite */
typedef struct {
  uint8_t seconds[4];      /* bytes 0 to 3 */
  uint8_t nanoseconds[4];  /* bytes 4 to 7 */
} TransactTime;

/* any Transact Time at all: every byte one the checker chooses */
static void any_transact_time(TransactTime *record) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = arbitrary(); }
}

/* Transact Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_transact_time(const TransactTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanoseconds[i]; }

  return at;
}

/* Transact Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_transact_time(TransactTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time is what was written, byte for byte */
static void equal_transact_time(const TransactTime *read, const TransactTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->seconds[i] == written->seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanoseconds[i] == written->nanoseconds[i]); }
}

/* Transact Time: written and read back, then read and written back */
static void check_transact_time(void) {
  TransactTime sent;
  TransactTime got;
  uint8_t wire[8];
  uint8_t again[8];

  any_transact_time(&sent);
  assert(encode_transact_time(&sent, wire, 0) == 8);
  assert(decode_transact_time(&got, wire, 0) == 8);
  equal_transact_time(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_transact_time(&got, wire, 0) == 8);
  assert(encode_transact_time(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Message: 179 bytes ------------------------------------- */

/* Indicates order accepted, rejected, executed, expired, cancelled, cancel/replaced, trade cancel, BI triggered or pending cancel. */
typedef struct {
  uint8_t app_id;                       /* byte 0 */
  uint8_t sequence_no[4];               /* bytes 1 to 4 */
  uint8_t execution_id[12];             /* bytes 5 to 16 */
  uint8_t client_order_id[20];          /* bytes 17 to 36 */
  uint8_t order_id[12];                 /* bytes 37 to 48 */
  uint8_t exec_type;                    /* byte 49 */
  uint8_t execution_report_ref_id[12];  /* bytes 50 to 61 */
  uint8_t order_status;                 /* byte 62 */
  uint8_t order_reject_code[4];         /* bytes 63 to 66 */
  uint8_t executed_price[8];            /* bytes 67 to 74 */
  uint8_t executed_qty[4];              /* bytes 75 to 78 */
  uint8_t leaves_qty[4];                /* bytes 79 to 82 */
  uint8_t waiver_flags;                 /* byte 83 */
  uint8_t display_qty[4];               /* bytes 84 to 87 */
  uint8_t common_symbol[8];             /* bytes 88 to 95 */
  uint8_t side;                         /* byte 96 */
  uint8_t secondary_order_id[8];        /* bytes 97 to 104 */
  uint8_t counterparty[11];             /* bytes 105 to 115 */
  uint8_t trade_liquidity_indicator;    /* byte 116 */
  uint8_t trade_match_id[8];            /* bytes 117 to 124 */
  TransactTime transact_time;           /* bytes 125 to 132 */
  uint8_t target_book;                  /* byte 133 */
  uint8_t type_of_trade;                /* byte 134 */
  uint8_t capacity;                     /* byte 135 */
  uint8_t reserved_1;                   /* byte 136 */
  uint8_t public_order_id[12];          /* bytes 137 to 148 */
  uint8_t minimum_quantity[4];          /* bytes 149 to 152 */
  uint8_t reputational_score;           /* byte 153 */
  uint8_t last_market;                  /* byte 154 */
  uint8_t peg_price_type;               /* byte 155 */
  uint8_t owner_type;                   /* byte 156 */
  uint8_t waiver_flags_2;               /* byte 157 */
  uint8_t reserved_21[21];              /* bytes 158 to 178 */
} ExecutionReportMessage;

/* any Execution Report Message at all: every byte one the checker chooses */
static void any_execution_report_message(ExecutionReportMessage *record) {
  record->app_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->execution_report_ref_id[i] = arbitrary(); }
  record->order_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->executed_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->waiver_flags = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->common_symbol[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->counterparty[i] = arbitrary(); }
  record->trade_liquidity_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  record->target_book = arbitrary();
  record->type_of_trade = arbitrary();
  record->capacity = arbitrary();
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->public_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
  record->reputational_score = arbitrary();
  record->last_market = arbitrary();
  record->peg_price_type = arbitrary();
  record->owner_type = arbitrary();
  record->waiver_flags_2 = arbitrary();
  for (size_t i = 0; i < 21; i++) { record->reserved_21[i] = arbitrary(); }
}

/* Execution Report Message to the wire: 179 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_message(const ExecutionReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_no[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->execution_report_ref_id[i]; }
  wire[at++] = record->order_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reject_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->executed_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->waiver_flags;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->common_symbol[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->counterparty[i]; }
  wire[at++] = record->trade_liquidity_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_match_id[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  wire[at++] = record->target_book;
  wire[at++] = record->type_of_trade;
  wire[at++] = record->capacity;
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->public_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }
  wire[at++] = record->reputational_score;
  wire[at++] = record->last_market;
  wire[at++] = record->peg_price_type;
  wire[at++] = record->owner_type;
  wire[at++] = record->waiver_flags_2;
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->reserved_21[i]; }

  return at;
}

/* Execution Report Message off the wire: 179 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_message(ExecutionReportMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->execution_report_ref_id[i] = wire[at++]; }
  record->order_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->executed_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->waiver_flags = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->common_symbol[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->counterparty[i] = wire[at++]; }
  record->trade_liquidity_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_match_id[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  record->target_book = wire[at++];
  record->type_of_trade = wire[at++];
  record->capacity = wire[at++];
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->public_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }
  record->reputational_score = wire[at++];
  record->last_market = wire[at++];
  record->peg_price_type = wire[at++];
  record->owner_type = wire[at++];
  record->waiver_flags_2 = wire[at++];
  for (size_t i = 0; i < 21; i++) { record->reserved_21[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Message is what was written, byte for byte */
static void equal_execution_report_message(const ExecutionReportMessage *read, const ExecutionReportMessage *written) {
  assert(read->app_id == written->app_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_no[i] == written->sequence_no[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 12; i++) { assert(read->execution_report_ref_id[i] == written->execution_report_ref_id[i]); }
  assert(read->order_status == written->order_status);
  for (size_t i = 0; i < 4; i++) { assert(read->order_reject_code[i] == written->order_reject_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->executed_price[i] == written->executed_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_qty[i] == written->executed_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->waiver_flags == written->waiver_flags);
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->common_symbol[i] == written->common_symbol[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->counterparty[i] == written->counterparty[i]); }
  assert(read->trade_liquidity_indicator == written->trade_liquidity_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_match_id[i] == written->trade_match_id[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  assert(read->target_book == written->target_book);
  assert(read->type_of_trade == written->type_of_trade);
  assert(read->capacity == written->capacity);
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 12; i++) { assert(read->public_order_id[i] == written->public_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
  assert(read->reputational_score == written->reputational_score);
  assert(read->last_market == written->last_market);
  assert(read->peg_price_type == written->peg_price_type);
  assert(read->owner_type == written->owner_type);
  assert(read->waiver_flags_2 == written->waiver_flags_2);
  for (size_t i = 0; i < 21; i++) { assert(read->reserved_21[i] == written->reserved_21[i]); }
}

/* Execution Report Message: written and read back, then read and written back */
static void check_execution_report_message(void) {
  ExecutionReportMessage sent;
  ExecutionReportMessage got;
  uint8_t wire[179];
  uint8_t again[179];

  any_execution_report_message(&sent);
  assert(encode_execution_report_message(&sent, wire, 0) == 179);
  assert(decode_execution_report_message(&got, wire, 0) == 179);
  equal_execution_report_message(&got, &sent);

  for (size_t i = 0; i < 179; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_message(&got, wire, 0) == 179);
  assert(encode_execution_report_message(&got, again, 0) == 179);
  for (size_t i = 0; i < 179; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject Message: 59 bytes ----------------------------------- */

/* Indicates that an Order Cancel Request or Order Cancel/Replace Request has been rejected. */
typedef struct {
  uint8_t app_id;                   /* byte 0 */
  uint8_t sequence_no[4];           /* bytes 1 to 4 */
  uint8_t client_order_id[20];      /* bytes 5 to 24 */
  uint8_t order_id[12];             /* bytes 25 to 36 */
  uint8_t cancel_reject_reason[4];  /* bytes 37 to 40 */
  TransactTime transact_time;       /* bytes 41 to 48 */
  uint8_t reserved_10[10];          /* bytes 49 to 58 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  record->app_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cancel_reject_reason[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Order Cancel Reject Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_no[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cancel_reject_reason[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Order Cancel Reject Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cancel_reject_reason[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  assert(read->app_id == written->app_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_no[i] == written->sequence_no[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cancel_reject_reason[i] == written->cancel_reject_reason[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 59);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 59);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 59);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel Report Message: 52 bytes ------------------------------ */

/* Indicates a mass order cancel request was accepted or rejected. */
typedef struct {
  uint8_t app_id;                        /* byte 0 */
  uint8_t sequence_no[4];                /* bytes 1 to 4 */
  uint8_t client_order_id[20];           /* bytes 5 to 24 */
  uint8_t mass_cancel_response;          /* byte 25 */
  uint8_t mass_cancel_reject_reason[4];  /* bytes 26 to 29 */
  uint8_t reserved_4[4];                 /* bytes 30 to 33 */
  TransactTime transact_time;            /* bytes 34 to 41 */
  uint8_t reserved_10[10];               /* bytes 42 to 51 */
} OrderMassCancelReportMessage;

/* any Order Mass Cancel Report Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_report_message(OrderMassCancelReportMessage *record) {
  record->app_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->mass_cancel_response = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->mass_cancel_reject_reason[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Order Mass Cancel Report Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_report_message(const OrderMassCancelReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_no[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->mass_cancel_response;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mass_cancel_reject_reason[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Order Mass Cancel Report Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_report_message(OrderMassCancelReportMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->mass_cancel_response = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->mass_cancel_reject_reason[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel Report Message is what was written, byte for byte */
static void equal_order_mass_cancel_report_message(const OrderMassCancelReportMessage *read, const OrderMassCancelReportMessage *written) {
  assert(read->app_id == written->app_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_no[i] == written->sequence_no[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->mass_cancel_response == written->mass_cancel_response);
  for (size_t i = 0; i < 4; i++) { assert(read->mass_cancel_reject_reason[i] == written->mass_cancel_reject_reason[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Order Mass Cancel Report Message: written and read back, then read and written back */
static void check_order_mass_cancel_report_message(void) {
  OrderMassCancelReportMessage sent;
  OrderMassCancelReportMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_order_mass_cancel_report_message(&sent);
  assert(encode_order_mass_cancel_report_message(&sent, wire, 0) == 52);
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 52);
  equal_order_mass_cancel_report_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 52);
  assert(encode_order_mass_cancel_report_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Reject Message: 59 bytes --------------------------------------- */

/* Indicates that an application message could not be processed. */
typedef struct {
  uint8_t app_id;               /* byte 0 */
  uint8_t sequence_no[4];       /* bytes 1 to 4 */
  uint8_t reject_code[4];       /* bytes 5 to 8 */
  uint8_t client_order_id[20];  /* bytes 9 to 28 */
  uint8_t order_id[12];         /* bytes 29 to 40 */
  TransactTime transact_time;   /* bytes 41 to 48 */
  uint8_t reserved_10[10];      /* bytes 49 to 58 */
} BusinessRejectMessage;

/* any Business Reject Message at all: every byte one the checker chooses */
static void any_business_reject_message(BusinessRejectMessage *record) {
  record->app_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Business Reject Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_business_reject_message(const BusinessRejectMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->app_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Business Reject Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_business_reject_message(BusinessRejectMessage *record, const uint8_t *wire, size_t at) {
  record->app_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Business Reject Message is what was written, byte for byte */
static void equal_business_reject_message(const BusinessRejectMessage *read, const BusinessRejectMessage *written) {
  assert(read->app_id == written->app_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_no[i] == written->sequence_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Business Reject Message: written and read back, then read and written back */
static void check_business_reject_message(void) {
  BusinessRejectMessage sent;
  BusinessRejectMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_business_reject_message(&sent);
  assert(encode_business_reject_message(&sent, wire, 0) == 59);
  assert(decode_business_reject_message(&got, wire, 0) == 59);
  equal_business_reject_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_business_reject_message(&got, wire, 0) == 59);
  assert(encode_business_reject_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_message();
  check_logon_reply_message();
  check_logout_message();
  check_missed_message_request_message();
  check_missed_message_request_ack_message();
  check_missed_message_report_message();
  check_reject_message();
  check_system_status_message();
  check_transact_time();
  check_execution_report_message();
  check_order_cancel_reject_message();
  check_order_mass_cancel_report_message();
  check_business_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
