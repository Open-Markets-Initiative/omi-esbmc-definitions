// lseg/millennium/nativetradinggatewayrecovery/Lseg_Millennium_NativeTradingGatewayRecovery_v21_2.c
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

/* Allows the client and server to establish a session. */
typedef struct {
  uint8_t user_name[25];     /* bytes 0 to 24 */
  uint8_t password[25];      /* bytes 25 to 49 */
  uint8_t new_password[25];  /* bytes 50 to 74 */
  uint8_t message_version;   /* byte 75 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 25; i++) { record->user_name[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = arbitrary(); }
  record->message_version = arbitrary();
}

/* Logon Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->user_name[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->new_password[i]; }
  wire[at++] = record->message_version;

  return at;
}

/* Logon Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 25; i++) { record->user_name[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = wire[at++]; }
  record->message_version = wire[at++];

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 25; i++) { assert(read->user_name[i] == written->user_name[i]); }
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

/* Allows the server to acknowledge a client's Logon. */
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

/* Allows the client and server to terminate a session. */
typedef struct {
  uint8_t reason[20];  /* bytes 0 to 19 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->reason[i] = arbitrary(); }
}

/* Logout Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->reason[i]; }

  return at;
}

/* Logout Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->reason[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->reason[i] == written->reason[i]); }
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

/* Allows the client to subscribe to missed messages through the Recovery Channel. */
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

/* Allows the server to acknowledge a client's Missed Message Request. */
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

/* Allows the server to communicate the result of a Missed Message Request. */
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

/* Used to reject a message that does not comply with the Native Trading Gateway messaging protocol. */
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

/* Indicates service non availability of a partition, disseminated on the recovery and realtime channels. */
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

/* ---- Order Mass Cancel Report Message: 52 bytes ------------------------------ */

/* Indicates that a mass order cancel request was accepted or rejected. */
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

/* ---- Quote Status Report Message: 143 bytes ---------------------------------- */

/* Allows the server to communicate the status of the RFQ to the Requester. */
typedef struct {
  uint8_t partition_id;                 /* byte 0 */
  uint8_t sequence_number[4];           /* bytes 1 to 4 */
  uint8_t quote_msg_id[20];             /* bytes 5 to 24 */
  uint8_t quote_req_id[10];             /* bytes 25 to 34 */
  uint8_t quote_status;                 /* byte 35 */
  uint8_t reject_code[4];               /* bytes 36 to 39 */
  uint8_t order_book;                   /* byte 40 */
  uint8_t market_makers[60];            /* bytes 41 to 100 */
  uint8_t rfq_id[10];                   /* bytes 101 to 110 */
  uint8_t expire_time[4];               /* bytes 111 to 114 */
  uint8_t bid_id[12];                   /* bytes 115 to 126 */
  uint8_t offer_id[12];                 /* bytes 127 to 138 */
  uint8_t expire_time_milliseconds[4];  /* bytes 139 to 142 */
} QuoteStatusReportMessage;

/* any Quote Status Report Message at all: every byte one the checker chooses */
static void any_quote_status_report_message(QuoteStatusReportMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quote_req_id[i] = arbitrary(); }
  record->quote_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  record->order_book = arbitrary();
  for (size_t i = 0; i < 60; i++) { record->market_makers[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expire_time[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expire_time_milliseconds[i] = arbitrary(); }
}

/* Quote Status Report Message to the wire: 143 bytes from at, returning where the next byte goes */
static size_t encode_quote_status_report_message(const QuoteStatusReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quote_msg_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quote_req_id[i]; }
  wire[at++] = record->quote_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  wire[at++] = record->order_book;
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->market_makers[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_time[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->offer_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expire_time_milliseconds[i]; }

  return at;
}

/* Quote Status Report Message off the wire: 143 bytes from at, returning where the next byte lies */
static size_t decode_quote_status_report_message(QuoteStatusReportMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quote_req_id[i] = wire[at++]; }
  record->quote_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  record->order_book = wire[at++];
  for (size_t i = 0; i < 60; i++) { record->market_makers[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expire_time[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expire_time_milliseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Status Report Message is what was written, byte for byte */
static void equal_quote_status_report_message(const QuoteStatusReportMessage *read, const QuoteStatusReportMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quote_msg_id[i] == written->quote_msg_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quote_req_id[i] == written->quote_req_id[i]); }
  assert(read->quote_status == written->quote_status);
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  assert(read->order_book == written->order_book);
  for (size_t i = 0; i < 60; i++) { assert(read->market_makers[i] == written->market_makers[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expire_time[i] == written->expire_time[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_id[i] == written->bid_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->offer_id[i] == written->offer_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expire_time_milliseconds[i] == written->expire_time_milliseconds[i]); }
}

/* Quote Status Report Message: written and read back, then read and written back */
static void check_quote_status_report_message(void) {
  QuoteStatusReportMessage sent;
  QuoteStatusReportMessage got;
  uint8_t wire[143];
  uint8_t again[143];

  any_quote_status_report_message(&sent);
  assert(encode_quote_status_report_message(&sent, wire, 0) == 143);
  assert(decode_quote_status_report_message(&got, wire, 0) == 143);
  equal_quote_status_report_message(&got, &sent);

  for (size_t i = 0; i < 143; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_status_report_message(&got, wire, 0) == 143);
  assert(encode_quote_status_report_message(&got, again, 0) == 143);
  for (size_t i = 0; i < 143; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Reject Message: 110 bytes --------------------------------- */

/* Rejects an RFQ. Sent by the Market Maker to reject, and by the server to reject or to relay a Market Maker rejection. */
typedef struct {
  uint8_t partition_id;        /* byte 0 */
  uint8_t sequence_number[4];  /* bytes 1 to 4 */
  uint8_t quote_req_id[10];    /* bytes 5 to 14 */
  uint8_t reject_code[4];      /* bytes 15 to 18 */
  uint8_t order_book;          /* byte 19 */
  uint8_t instrument_id[4];    /* bytes 20 to 23 */
  uint8_t side;                /* byte 24 */
  uint8_t order_quantity[4];   /* bytes 25 to 28 */
  uint8_t market_makers[60];   /* bytes 29 to 88 */
  uint8_t contra_trader[11];   /* bytes 89 to 99 */
  uint8_t rfq_id[10];          /* bytes 100 to 109 */
} QuoteRequestRejectMessage;

/* any Quote Request Reject Message at all: every byte one the checker chooses */
static void any_quote_request_reject_message(QuoteRequestRejectMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quote_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  record->order_book = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->market_makers[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->contra_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
}

/* Quote Request Reject Message to the wire: 110 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_reject_message(const QuoteRequestRejectMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quote_req_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  wire[at++] = record->order_book;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->market_makers[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->contra_trader[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }

  return at;
}

/* Quote Request Reject Message off the wire: 110 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_reject_message(QuoteRequestRejectMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quote_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  record->order_book = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->market_makers[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->contra_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Reject Message is what was written, byte for byte */
static void equal_quote_request_reject_message(const QuoteRequestRejectMessage *read, const QuoteRequestRejectMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quote_req_id[i] == written->quote_req_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  assert(read->order_book == written->order_book);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->market_makers[i] == written->market_makers[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->contra_trader[i] == written->contra_trader[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
}

/* Quote Request Reject Message: written and read back, then read and written back */
static void check_quote_request_reject_message(void) {
  QuoteRequestRejectMessage sent;
  QuoteRequestRejectMessage got;
  uint8_t wire[110];
  uint8_t again[110];

  any_quote_request_reject_message(&sent);
  assert(encode_quote_request_reject_message(&sent, wire, 0) == 110);
  assert(decode_quote_request_reject_message(&got, wire, 0) == 110);
  equal_quote_request_reject_message(&got, &sent);

  for (size_t i = 0; i < 110; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_reject_message(&got, wire, 0) == 110);
  assert(encode_quote_request_reject_message(&got, again, 0) == 110);
  for (size_t i = 0; i < 110; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Ack Message: 65 bytes --------------------------------------------- */

/* Allows the server to acknowledge a new or modified RFQ Quote to the Market Maker. */
typedef struct {
  uint8_t partition_id;        /* byte 0 */
  uint8_t sequence_number[4];  /* bytes 1 to 4 */
  uint8_t quote_msg_id[20];    /* bytes 5 to 24 */
  uint8_t rfq_id[10];          /* bytes 25 to 34 */
  uint8_t bid_id[12];          /* bytes 35 to 46 */
  uint8_t offer_id[12];        /* bytes 47 to 58 */
  uint8_t quote_ack_status;    /* byte 59 */
  uint8_t reject_code[4];      /* bytes 60 to 63 */
  uint8_t order_book;          /* byte 64 */
} QuoteAckMessage;

/* any Quote Ack Message at all: every byte one the checker chooses */
static void any_quote_ack_message(QuoteAckMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = arbitrary(); }
  record->quote_ack_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  record->order_book = arbitrary();
}

/* Quote Ack Message to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_quote_ack_message(const QuoteAckMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quote_msg_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->offer_id[i]; }
  wire[at++] = record->quote_ack_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  wire[at++] = record->order_book;

  return at;
}

/* Quote Ack Message off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_quote_ack_message(QuoteAckMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = wire[at++]; }
  record->quote_ack_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  record->order_book = wire[at++];

  return at;
}

/* what was read of Quote Ack Message is what was written, byte for byte */
static void equal_quote_ack_message(const QuoteAckMessage *read, const QuoteAckMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quote_msg_id[i] == written->quote_msg_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->bid_id[i] == written->bid_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->offer_id[i] == written->offer_id[i]); }
  assert(read->quote_ack_status == written->quote_ack_status);
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  assert(read->order_book == written->order_book);
}

/* Quote Ack Message: written and read back, then read and written back */
static void check_quote_ack_message(void) {
  QuoteAckMessage sent;
  QuoteAckMessage got;
  uint8_t wire[65];
  uint8_t again[65];

  any_quote_ack_message(&sent);
  assert(encode_quote_ack_message(&sent, wire, 0) == 65);
  assert(decode_quote_ack_message(&got, wire, 0) == 65);
  equal_quote_ack_message(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_ack_message(&got, wire, 0) == 65);
  assert(encode_quote_ack_message(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Response Message: 88 bytes ---------------------------------------- */

/* Carries an RFQ response. Sent by the Requester to execute or cancel an RFQ Quote, and by the server to report quote and RFQ status. */
typedef struct {
  uint8_t partition_id;        /* byte 0 */
  uint8_t sequence_number[4];  /* bytes 1 to 4 */
  uint8_t quote_msg_id[20];    /* bytes 5 to 24 */
  uint8_t rfq_id[10];          /* bytes 25 to 34 */
  uint8_t quote_resp_type;     /* byte 35 */
  uint8_t instrument_id[4];    /* bytes 36 to 39 */
  uint8_t side;                /* byte 40 */
  uint8_t order_quantity[4];   /* bytes 41 to 44 */
  uint8_t limit_price[8];      /* bytes 45 to 52 */
  uint8_t order_book;          /* byte 53 */
  uint8_t bid_id[12];          /* bytes 54 to 65 */
  uint8_t offer_id[12];        /* bytes 66 to 77 */
  uint8_t capacity;            /* byte 78 */
  uint8_t clearing_account;    /* byte 79 */
  uint8_t reserved_8[8];       /* bytes 80 to 87 */
} QuoteResponseMessage;

/* any Quote Response Message at all: every byte one the checker chooses */
static void any_quote_response_message(QuoteResponseMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = arbitrary(); }
  record->quote_resp_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = arbitrary(); }
  record->order_book = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = arbitrary(); }
  record->capacity = arbitrary();
  record->clearing_account = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Quote Response Message to the wire: 88 bytes from at, returning where the next byte goes */
static size_t encode_quote_response_message(const QuoteResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->quote_msg_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->rfq_id[i]; }
  wire[at++] = record->quote_resp_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->limit_price[i]; }
  wire[at++] = record->order_book;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->bid_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->offer_id[i]; }
  wire[at++] = record->capacity;
  wire[at++] = record->clearing_account;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Quote Response Message off the wire: 88 bytes from at, returning where the next byte lies */
static size_t decode_quote_response_message(QuoteResponseMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->quote_msg_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->rfq_id[i] = wire[at++]; }
  record->quote_resp_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->limit_price[i] = wire[at++]; }
  record->order_book = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->bid_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->offer_id[i] = wire[at++]; }
  record->capacity = wire[at++];
  record->clearing_account = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Response Message is what was written, byte for byte */
static void equal_quote_response_message(const QuoteResponseMessage *read, const QuoteResponseMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->quote_msg_id[i] == written->quote_msg_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->rfq_id[i] == written->rfq_id[i]); }
  assert(read->quote_resp_type == written->quote_resp_type);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->order_quantity[i] == written->order_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->limit_price[i] == written->limit_price[i]); }
  assert(read->order_book == written->order_book);
  for (size_t i = 0; i < 12; i++) { assert(read->bid_id[i] == written->bid_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->offer_id[i] == written->offer_id[i]); }
  assert(read->capacity == written->capacity);
  assert(read->clearing_account == written->clearing_account);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Quote Response Message: written and read back, then read and written back */
static void check_quote_response_message(void) {
  QuoteResponseMessage sent;
  QuoteResponseMessage got;
  uint8_t wire[88];
  uint8_t again[88];

  any_quote_response_message(&sent);
  assert(encode_quote_response_message(&sent, wire, 0) == 88);
  assert(decode_quote_response_message(&got, wire, 0) == 88);
  equal_quote_response_message(&got, &sent);

  for (size_t i = 0; i < 88; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_response_message(&got, wire, 0) == 88);
  assert(encode_quote_response_message(&got, again, 0) == 88);
  for (size_t i = 0; i < 88; i++) { assert(again[i] == wire[i]); }
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
  check_order_mass_cancel_report_message();
  check_quote_status_report_message();
  check_quote_request_reject_message();
  check_quote_ack_message();
  check_quote_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
