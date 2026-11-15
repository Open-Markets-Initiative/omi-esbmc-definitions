// bme/bmefixedincome/recovery/BmeFixedIncome_Recovery_v1_6.c
/*
 * Bolsas y Mercados Españoles BME Fixed Income Recovery
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* What every message carries, in either direction: its length and its type. Section 2.1 gives a published message a third field, the sequence number that lets a listener continue an interrupted session without gaps and without repeated messages, and the message tables state it as the message's own first field - which is where it is declared, since a client's Logon, Replay Request and Logout do not carry one */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type;     /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 26 bytes ---------------------------------------- */

/* The Logon Response message is used by the Server to accept a new session. In this message the sequence number will always be 0 */
typedef struct {
  uint8_t sequence_number[4];           /* bytes 0 to 3 */
  uint8_t heart_bt_int;                 /* byte 4 */
  uint8_t protocol_version[6];          /* bytes 5 to 10 */
  uint8_t test_production_ind;          /* byte 11 */
  uint8_t environment_code[2];          /* bytes 12 to 13 */
  uint8_t session_date[4];              /* bytes 14 to 17 */
  uint8_t expected_sequence_number[4];  /* bytes 18 to 21 */
  uint8_t sequence_number_to[4];        /* bytes 22 to 25 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->heart_bt_int = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = arbitrary(); }
  record->test_production_ind = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->environment_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number_to[i] = arbitrary(); }
}

/* Logon Response Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->heart_bt_int;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->protocol_version[i]; }
  wire[at++] = record->test_production_ind;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->environment_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number_to[i]; }

  return at;
}

/* Logon Response Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->heart_bt_int = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = wire[at++]; }
  record->test_production_ind = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->environment_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number_to[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->heart_bt_int == written->heart_bt_int);
  for (size_t i = 0; i < 6; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  assert(read->test_production_ind == written->test_production_ind);
  for (size_t i = 0; i < 2; i++) { assert(read->environment_code[i] == written->environment_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_date[i] == written->session_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_sequence_number[i] == written->expected_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number_to[i] == written->sequence_number_to[i]); }
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 26);
  assert(decode_logon_response_message(&got, wire, 0) == 26);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 26);
  assert(encode_logon_response_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Response Message: 5 bytes ---------------------------------------- */

/* The Logout message is used by the Server to notify the end of a session, whether it is solicited or unsolicited. It may also be the answer to a failed logon attempt (see Logon message) */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t logout_reason;       /* byte 4 */
} LogoutResponseMessage;

/* any Logout Response Message at all: every byte one the checker chooses */
static void any_logout_response_message(LogoutResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->logout_reason = arbitrary();
}

/* Logout Response Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_logout_response_message(const LogoutResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->logout_reason;

  return at;
}

/* Logout Response Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_logout_response_message(LogoutResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->logout_reason = wire[at++];

  return at;
}

/* what was read of Logout Response Message is what was written, byte for byte */
static void equal_logout_response_message(const LogoutResponseMessage *read, const LogoutResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->logout_reason == written->logout_reason);
}

/* Logout Response Message: written and read back, then read and written back */
static void check_logout_response_message(void) {
  LogoutResponseMessage sent;
  LogoutResponseMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_logout_response_message(&sent);
  assert(encode_logout_response_message(&sent, wire, 0) == 5);
  assert(decode_logout_response_message(&got, wire, 0) == 5);
  equal_logout_response_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_response_message(&got, wire, 0) == 5);
  assert(encode_logout_response_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 4 bytes ---------------------------------------------- */

/* The Heartbeat message is used by the Server to indicate that the communication is active. In the Heartbeat message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Heartbeat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 4);
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  assert(encode_heartbeat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 53 bytes ------------------------------------------------- */

/* The Logon message is used to start a session by the client application */
typedef struct {
  uint8_t username[7];                  /* bytes 0 to 6 */
  uint8_t password[10];                 /* bytes 7 to 16 */
  uint8_t software_name[25];            /* bytes 17 to 41 */
  uint8_t expected_sequence_number[4];  /* bytes 42 to 45 */
  uint8_t subscriptions;                /* byte 46 */
  uint8_t protocol_version[6];          /* bytes 47 to 52 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 7; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->software_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = arbitrary(); }
  record->subscriptions = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = arbitrary(); }
}

/* Logon Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->software_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_sequence_number[i]; }
  wire[at++] = record->subscriptions;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->protocol_version[i]; }

  return at;
}

/* Logon Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->software_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = wire[at++]; }
  record->subscriptions = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->software_name[i] == written->software_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_sequence_number[i] == written->expected_sequence_number[i]); }
  assert(read->subscriptions == written->subscriptions);
  for (size_t i = 0; i < 6; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 53);
  assert(decode_logon_message(&got, wire, 0) == 53);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 53);
  assert(encode_logon_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 70 bytes ------------------------------------------------ */

/* It may be sent by the server to inform about the rejection of an unsupported or syntactically incorrect message. In the Reject message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];         /* bytes 0 to 3 */
  uint8_t session_reject_reason;      /* byte 4 */
  uint8_t text[58];                   /* bytes 5 to 62 */
  uint8_t msg_rejected_reference[7];  /* bytes 63 to 69 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->session_reject_reason = arbitrary();
  for (size_t i = 0; i < 58; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = arbitrary(); }
}

/* Reject Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->session_reject_reason;
  for (size_t i = 0; i < 58; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->msg_rejected_reference[i]; }

  return at;
}

/* Reject Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->session_reject_reason = wire[at++];
  for (size_t i = 0; i < 58; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->session_reject_reason == written->session_reject_reason);
  for (size_t i = 0; i < 58; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->msg_rejected_reference[i] == written->msg_rejected_reference[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 70);
  assert(decode_reject_message(&got, wire, 0) == 70);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 70);
  assert(encode_reject_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 15 bytes -------------------------------- */

/* Sent by the server to inform about the session status in each Trading Mode */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t trading_session_id;            /* byte 4 */
  uint8_t trading_session_sub_id;        /* byte 5 */
  uint8_t trad_ses_status;               /* byte 6 */
  uint8_t transaction_date_and_time[8];  /* bytes 7 to 14 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trad_ses_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->trading_session_id;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trad_ses_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trad_ses_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trad_ses_status == written->trad_ses_status);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 15);
  assert(decode_trading_session_status_message(&got, wire, 0) == 15);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 15);
  assert(encode_trading_session_status_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 82 bytes -------------------------------------------------- */

/* Used by the Server to communicate a Market Surveillance or system-wide text message */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t news_text[78];       /* bytes 4 to 81 */
} NewsMessage;

/* any News Message at all: every byte one the checker chooses */
static void any_news_message(NewsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 78; i++) { record->news_text[i] = arbitrary(); }
}

/* News Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_news_message(const NewsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 78; i++) { wire[at++] = record->news_text[i]; }

  return at;
}

/* News Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_news_message(NewsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 78; i++) { record->news_text[i] = wire[at++]; }

  return at;
}

/* what was read of News Message is what was written, byte for byte */
static void equal_news_message(const NewsMessage *read, const NewsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 78; i++) { assert(read->news_text[i] == written->news_text[i]); }
}

/* News Message: written and read back, then read and written back */
static void check_news_message(void) {
  NewsMessage sent;
  NewsMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_news_message(&sent);
  assert(encode_news_message(&sent, wire, 0) == 82);
  assert(decode_news_message(&got, wire, 0) == 82);
  equal_news_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_news_message(&got, wire, 0) == 82);
  assert(encode_news_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Cancellation Report Message: 50 bytes --------------------- */

/* Message sent by the server for cancelling previously defined securities */
typedef struct {
  uint8_t sequence_number[4];    /* bytes 0 to 3 */
  uint8_t market_id[4];          /* bytes 4 to 7 */
  uint8_t market_segment_id[4];  /* bytes 8 to 11 */
  uint8_t security_code[4];      /* bytes 12 to 15 */
  uint8_t symbol[22];            /* bytes 16 to 37 */
  uint8_t symbol_isin[12];       /* bytes 38 to 49 */
} SecurityListCancellationReportMessage;

/* any Security List Cancellation Report Message at all: every byte one the checker chooses */
static void any_security_list_cancellation_report_message(SecurityListCancellationReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
}

/* Security List Cancellation Report Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_security_list_cancellation_report_message(const SecurityListCancellationReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }

  return at;
}

/* Security List Cancellation Report Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_security_list_cancellation_report_message(SecurityListCancellationReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Cancellation Report Message is what was written, byte for byte */
static void equal_security_list_cancellation_report_message(const SecurityListCancellationReportMessage *read, const SecurityListCancellationReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
}

/* Security List Cancellation Report Message: written and read back, then read and written back */
static void check_security_list_cancellation_report_message(void) {
  SecurityListCancellationReportMessage sent;
  SecurityListCancellationReportMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_security_list_cancellation_report_message(&sent);
  assert(encode_security_list_cancellation_report_message(&sent, wire, 0) == 50);
  assert(decode_security_list_cancellation_report_message(&got, wire, 0) == 50);
  equal_security_list_cancellation_report_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_cancellation_report_message(&got, wire, 0) == 50);
  assert(encode_security_list_cancellation_report_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Message: 450 bytes ---------------------------------------- */

/* Message sent by the server to provide the definition of one security. It shares the same layout as the Security List Update Report message, but with a different Message Type */
typedef struct {
  uint8_t sequence_number[4];                      /* bytes 0 to 3 */
  uint8_t market_id[4];                            /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                    /* bytes 8 to 11 */
  uint8_t security_code[4];                        /* bytes 12 to 15 */
  uint8_t symbol[22];                              /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                         /* bytes 38 to 49 */
  uint8_t fisn[35];                                /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                          /* bytes 85 to 104 */
  uint8_t security_group[2];                       /* bytes 105 to 106 */
  uint8_t cfi_code[6];                             /* bytes 107 to 112 */
  uint8_t security_type[2];                        /* bytes 113 to 114 */
  uint8_t maturity_date[4];                        /* bytes 115 to 118 */
  uint8_t issue_date[4];                           /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                  /* bytes 123 to 130 */
  uint8_t li_spre[8];                              /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                             /* bytes 139 to 146 */
  uint8_t li_spost[8];                             /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                            /* bytes 155 to 162 */
  uint8_t liquid_instrument;                       /* byte 163 */
  uint8_t admission_requested_by_issuer;           /* byte 164 */
  uint8_t min_trade_vol[4];                        /* bytes 165 to 168 */
  uint8_t round_lot[4];                            /* bytes 169 to 172 */
  uint8_t currency[3];                             /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                    /* bytes 176 to 179 */
  uint8_t security_description[80];                /* bytes 180 to 259 */
  uint8_t trading_obligation;                      /* byte 260 */
  uint8_t security_name[40];                       /* bytes 261 to 300 */
  uint8_t security_status;                         /* byte 301 */
  uint8_t coupon_payment_date[4];                  /* bytes 302 to 305 */
  uint8_t min_price_increment[8];                  /* bytes 306 to 313 */
  uint8_t number_of_decimals;                      /* byte 314 */
  uint8_t order_number_of_decimals;                /* byte 315 */
  uint8_t coupon_rate[8];                          /* bytes 316 to 323 */
  uint8_t issuer[12];                              /* bytes 324 to 335 */
  uint8_t trading_scope_b_1;                       /* byte 336 */
  uint8_t first_trading_date[4];                   /* bytes 337 to 340 */
  uint8_t settlement_system;                       /* byte 341 */
  uint8_t maturity[8];                             /* bytes 342 to 349 */
  uint8_t coupon_periodicity;                      /* byte 350 */
  uint8_t benchmark;                               /* byte 351 */
  uint8_t strippable;                              /* byte 352 */
  uint8_t volume_issued[8];                        /* bytes 353 to 360 */
  uint8_t alive_volume[8];                         /* bytes 361 to 368 */
  uint8_t coupon_type;                             /* byte 369 */
  uint8_t coupon_quotation;                        /* byte 370 */
  uint8_t accrued_interest_calculation_procedure;  /* byte 371 */
  uint8_t next_redemption_date[4];                 /* bytes 372 to 375 */
  uint8_t type_of_redemption[2];                   /* bytes 376 to 377 */
  uint8_t facial[8];                               /* bytes 378 to 385 */
  uint8_t calculation_method;                      /* byte 386 */
  uint8_t date_last_coupon_was_paid[4];            /* bytes 387 to 390 */
  uint8_t bond_seniority[4];                       /* bytes 391 to 394 */
  uint8_t interest_accrual_date[4];                /* bytes 395 to 398 */
  uint8_t start_date[4];                           /* bytes 399 to 402 */
  uint8_t price_type;                              /* byte 403 */
  uint8_t spread_to_index[8];                      /* bytes 404 to 411 */
  uint8_t benchmark_curve_points_units[4];         /* bytes 412 to 415 */
  uint8_t benchmark_curve_points_value;            /* byte 416 */
  uint8_t benchmark_security_id[25];               /* bytes 417 to 441 */
  uint8_t accrued_interest_rate_r_8[8];            /* bytes 442 to 449 */
} SecurityListMessage;

/* any Security List Message at all: every byte one the checker chooses */
static void any_security_list_message(SecurityListMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = arbitrary(); }
  record->liquid_instrument = arbitrary();
  record->admission_requested_by_issuer = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = arbitrary(); }
  record->trading_obligation = arbitrary();
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->coupon_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = arbitrary(); }
  record->number_of_decimals = arbitrary();
  record->order_number_of_decimals = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->trading_scope_b_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maturity[i] = arbitrary(); }
  record->coupon_periodicity = arbitrary();
  record->benchmark = arbitrary();
  record->strippable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume_issued[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alive_volume[i] = arbitrary(); }
  record->coupon_type = arbitrary();
  record->coupon_quotation = arbitrary();
  record->accrued_interest_calculation_procedure = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->next_redemption_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_redemption[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->facial[i] = arbitrary(); }
  record->calculation_method = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->date_last_coupon_was_paid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bond_seniority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->interest_accrual_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->spread_to_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->benchmark_curve_points_units[i] = arbitrary(); }
  record->benchmark_curve_points_value = arbitrary();
  for (size_t i = 0; i < 25; i++) { record->benchmark_security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_r_8[i] = arbitrary(); }
}

/* Security List Message to the wire: 450 bytes from at, returning where the next byte goes */
static size_t encode_security_list_message(const SecurityListMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->fisn[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issuer_lei[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spost[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipost[i]; }
  wire[at++] = record->liquid_instrument;
  wire[at++] = record->admission_requested_by_issuer;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modality_mask_b_4[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->security_description[i]; }
  wire[at++] = record->trading_obligation;
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->security_name[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_payment_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment[i]; }
  wire[at++] = record->number_of_decimals;
  wire[at++] = record->order_number_of_decimals;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->trading_scope_b_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity[i]; }
  wire[at++] = record->coupon_periodicity;
  wire[at++] = record->benchmark;
  wire[at++] = record->strippable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_issued[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alive_volume[i]; }
  wire[at++] = record->coupon_type;
  wire[at++] = record->coupon_quotation;
  wire[at++] = record->accrued_interest_calculation_procedure;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_redemption_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_redemption[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->facial[i]; }
  wire[at++] = record->calculation_method;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_last_coupon_was_paid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bond_seniority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->interest_accrual_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_date[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spread_to_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->benchmark_curve_points_units[i]; }
  wire[at++] = record->benchmark_curve_points_value;
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->benchmark_security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_rate_r_8[i]; }

  return at;
}

/* Security List Message off the wire: 450 bytes from at, returning where the next byte lies */
static size_t decode_security_list_message(SecurityListMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = wire[at++]; }
  record->liquid_instrument = wire[at++];
  record->admission_requested_by_issuer = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = wire[at++]; }
  record->trading_obligation = wire[at++];
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->coupon_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = wire[at++]; }
  record->number_of_decimals = wire[at++];
  record->order_number_of_decimals = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->trading_scope_b_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maturity[i] = wire[at++]; }
  record->coupon_periodicity = wire[at++];
  record->benchmark = wire[at++];
  record->strippable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume_issued[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alive_volume[i] = wire[at++]; }
  record->coupon_type = wire[at++];
  record->coupon_quotation = wire[at++];
  record->accrued_interest_calculation_procedure = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->next_redemption_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_redemption[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->facial[i] = wire[at++]; }
  record->calculation_method = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->date_last_coupon_was_paid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bond_seniority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->interest_accrual_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->spread_to_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->benchmark_curve_points_units[i] = wire[at++]; }
  record->benchmark_curve_points_value = wire[at++];
  for (size_t i = 0; i < 25; i++) { record->benchmark_security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_r_8[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Message is what was written, byte for byte */
static void equal_security_list_message(const SecurityListMessage *read, const SecurityListMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->fisn[i] == written->fisn[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->issuer_lei[i] == written->issuer_lei[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_type[i] == written->security_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spre[i] == written->li_spre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipre[i] == written->sst_ipre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spost[i] == written->li_spost[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipost[i] == written->sst_ipost[i]); }
  assert(read->liquid_instrument == written->liquid_instrument);
  assert(read->admission_requested_by_issuer == written->admission_requested_by_issuer);
  for (size_t i = 0; i < 4; i++) { assert(read->min_trade_vol[i] == written->min_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot[i] == written->round_lot[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modality_mask_b_4[i] == written->modality_mask_b_4[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->security_description[i] == written->security_description[i]); }
  assert(read->trading_obligation == written->trading_obligation);
  for (size_t i = 0; i < 40; i++) { assert(read->security_name[i] == written->security_name[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_payment_date[i] == written->coupon_payment_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment[i] == written->min_price_increment[i]); }
  assert(read->number_of_decimals == written->number_of_decimals);
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  for (size_t i = 0; i < 8; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->trading_scope_b_1 == written->trading_scope_b_1);
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  for (size_t i = 0; i < 8; i++) { assert(read->maturity[i] == written->maturity[i]); }
  assert(read->coupon_periodicity == written->coupon_periodicity);
  assert(read->benchmark == written->benchmark);
  assert(read->strippable == written->strippable);
  for (size_t i = 0; i < 8; i++) { assert(read->volume_issued[i] == written->volume_issued[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alive_volume[i] == written->alive_volume[i]); }
  assert(read->coupon_type == written->coupon_type);
  assert(read->coupon_quotation == written->coupon_quotation);
  assert(read->accrued_interest_calculation_procedure == written->accrued_interest_calculation_procedure);
  for (size_t i = 0; i < 4; i++) { assert(read->next_redemption_date[i] == written->next_redemption_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_redemption[i] == written->type_of_redemption[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->facial[i] == written->facial[i]); }
  assert(read->calculation_method == written->calculation_method);
  for (size_t i = 0; i < 4; i++) { assert(read->date_last_coupon_was_paid[i] == written->date_last_coupon_was_paid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bond_seniority[i] == written->bond_seniority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->interest_accrual_date[i] == written->interest_accrual_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_date[i] == written->start_date[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->spread_to_index[i] == written->spread_to_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->benchmark_curve_points_units[i] == written->benchmark_curve_points_units[i]); }
  assert(read->benchmark_curve_points_value == written->benchmark_curve_points_value);
  for (size_t i = 0; i < 25; i++) { assert(read->benchmark_security_id[i] == written->benchmark_security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_rate_r_8[i] == written->accrued_interest_rate_r_8[i]); }
}

/* Security List Message: written and read back, then read and written back */
static void check_security_list_message(void) {
  SecurityListMessage sent;
  SecurityListMessage got;
  uint8_t wire[450];
  uint8_t again[450];

  any_security_list_message(&sent);
  assert(encode_security_list_message(&sent, wire, 0) == 450);
  assert(decode_security_list_message(&got, wire, 0) == 450);
  equal_security_list_message(&got, &sent);

  for (size_t i = 0; i < 450; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_message(&got, wire, 0) == 450);
  assert(encode_security_list_message(&got, again, 0) == 450);
  for (size_t i = 0; i < 450; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Update Report Message: 450 bytes -------------------------- */

/* Message sent by the server for reporting updates, during the session, to the security definition */
typedef struct {
  uint8_t sequence_number[4];                      /* bytes 0 to 3 */
  uint8_t market_id[4];                            /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                    /* bytes 8 to 11 */
  uint8_t security_code[4];                        /* bytes 12 to 15 */
  uint8_t symbol[22];                              /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                         /* bytes 38 to 49 */
  uint8_t fisn[35];                                /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                          /* bytes 85 to 104 */
  uint8_t security_group[2];                       /* bytes 105 to 106 */
  uint8_t cfi_code[6];                             /* bytes 107 to 112 */
  uint8_t security_type[2];                        /* bytes 113 to 114 */
  uint8_t maturity_date[4];                        /* bytes 115 to 118 */
  uint8_t issue_date[4];                           /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                  /* bytes 123 to 130 */
  uint8_t li_spre[8];                              /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                             /* bytes 139 to 146 */
  uint8_t li_spost[8];                             /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                            /* bytes 155 to 162 */
  uint8_t liquid_instrument;                       /* byte 163 */
  uint8_t admission_requested_by_issuer;           /* byte 164 */
  uint8_t min_trade_vol[4];                        /* bytes 165 to 168 */
  uint8_t round_lot[4];                            /* bytes 169 to 172 */
  uint8_t currency[3];                             /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                    /* bytes 176 to 179 */
  uint8_t security_description[80];                /* bytes 180 to 259 */
  uint8_t trading_obligation;                      /* byte 260 */
  uint8_t security_name[40];                       /* bytes 261 to 300 */
  uint8_t security_status;                         /* byte 301 */
  uint8_t coupon_payment_date[4];                  /* bytes 302 to 305 */
  uint8_t min_price_increment[8];                  /* bytes 306 to 313 */
  uint8_t number_of_decimals;                      /* byte 314 */
  uint8_t order_number_of_decimals;                /* byte 315 */
  uint8_t coupon_rate[8];                          /* bytes 316 to 323 */
  uint8_t issuer[12];                              /* bytes 324 to 335 */
  uint8_t trading_scope_b_1;                       /* byte 336 */
  uint8_t first_trading_date[4];                   /* bytes 337 to 340 */
  uint8_t settlement_system;                       /* byte 341 */
  uint8_t maturity[8];                             /* bytes 342 to 349 */
  uint8_t coupon_periodicity;                      /* byte 350 */
  uint8_t benchmark;                               /* byte 351 */
  uint8_t strippable;                              /* byte 352 */
  uint8_t volume_issued[8];                        /* bytes 353 to 360 */
  uint8_t alive_volume[8];                         /* bytes 361 to 368 */
  uint8_t coupon_type;                             /* byte 369 */
  uint8_t coupon_quotation;                        /* byte 370 */
  uint8_t accrued_interest_calculation_procedure;  /* byte 371 */
  uint8_t next_redemption_date[4];                 /* bytes 372 to 375 */
  uint8_t type_of_redemption[2];                   /* bytes 376 to 377 */
  uint8_t facial[8];                               /* bytes 378 to 385 */
  uint8_t calculation_method;                      /* byte 386 */
  uint8_t date_last_coupon_was_paid[4];            /* bytes 387 to 390 */
  uint8_t bond_seniority[4];                       /* bytes 391 to 394 */
  uint8_t interest_accrual_date[4];                /* bytes 395 to 398 */
  uint8_t start_date[4];                           /* bytes 399 to 402 */
  uint8_t price_type;                              /* byte 403 */
  uint8_t spread_to_index[8];                      /* bytes 404 to 411 */
  uint8_t benchmark_curve_points_units[4];         /* bytes 412 to 415 */
  uint8_t benchmark_curve_points_value;            /* byte 416 */
  uint8_t benchmark_security_id[25];               /* bytes 417 to 441 */
  uint8_t accrued_interest_rate_r_8[8];            /* bytes 442 to 449 */
} SecurityListUpdateReportMessage;

/* any Security List Update Report Message at all: every byte one the checker chooses */
static void any_security_list_update_report_message(SecurityListUpdateReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = arbitrary(); }
  record->liquid_instrument = arbitrary();
  record->admission_requested_by_issuer = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = arbitrary(); }
  record->trading_obligation = arbitrary();
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->coupon_payment_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = arbitrary(); }
  record->number_of_decimals = arbitrary();
  record->order_number_of_decimals = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->trading_scope_b_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maturity[i] = arbitrary(); }
  record->coupon_periodicity = arbitrary();
  record->benchmark = arbitrary();
  record->strippable = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume_issued[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alive_volume[i] = arbitrary(); }
  record->coupon_type = arbitrary();
  record->coupon_quotation = arbitrary();
  record->accrued_interest_calculation_procedure = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->next_redemption_date[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->type_of_redemption[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->facial[i] = arbitrary(); }
  record->calculation_method = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->date_last_coupon_was_paid[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bond_seniority[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->interest_accrual_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = arbitrary(); }
  record->price_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->spread_to_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->benchmark_curve_points_units[i] = arbitrary(); }
  record->benchmark_curve_points_value = arbitrary();
  for (size_t i = 0; i < 25; i++) { record->benchmark_security_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_r_8[i] = arbitrary(); }
}

/* Security List Update Report Message to the wire: 450 bytes from at, returning where the next byte goes */
static size_t encode_security_list_update_report_message(const SecurityListUpdateReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->fisn[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issuer_lei[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spost[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipost[i]; }
  wire[at++] = record->liquid_instrument;
  wire[at++] = record->admission_requested_by_issuer;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modality_mask_b_4[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->security_description[i]; }
  wire[at++] = record->trading_obligation;
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->security_name[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_payment_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment[i]; }
  wire[at++] = record->number_of_decimals;
  wire[at++] = record->order_number_of_decimals;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->trading_scope_b_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity[i]; }
  wire[at++] = record->coupon_periodicity;
  wire[at++] = record->benchmark;
  wire[at++] = record->strippable;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_issued[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alive_volume[i]; }
  wire[at++] = record->coupon_type;
  wire[at++] = record->coupon_quotation;
  wire[at++] = record->accrued_interest_calculation_procedure;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_redemption_date[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->type_of_redemption[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->facial[i]; }
  wire[at++] = record->calculation_method;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_last_coupon_was_paid[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bond_seniority[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->interest_accrual_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_date[i]; }
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spread_to_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->benchmark_curve_points_units[i]; }
  wire[at++] = record->benchmark_curve_points_value;
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->benchmark_security_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_rate_r_8[i]; }

  return at;
}

/* Security List Update Report Message off the wire: 450 bytes from at, returning where the next byte lies */
static size_t decode_security_list_update_report_message(SecurityListUpdateReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = wire[at++]; }
  record->liquid_instrument = wire[at++];
  record->admission_requested_by_issuer = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = wire[at++]; }
  record->trading_obligation = wire[at++];
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->coupon_payment_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = wire[at++]; }
  record->number_of_decimals = wire[at++];
  record->order_number_of_decimals = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->trading_scope_b_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maturity[i] = wire[at++]; }
  record->coupon_periodicity = wire[at++];
  record->benchmark = wire[at++];
  record->strippable = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume_issued[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alive_volume[i] = wire[at++]; }
  record->coupon_type = wire[at++];
  record->coupon_quotation = wire[at++];
  record->accrued_interest_calculation_procedure = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->next_redemption_date[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->type_of_redemption[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->facial[i] = wire[at++]; }
  record->calculation_method = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->date_last_coupon_was_paid[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bond_seniority[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->interest_accrual_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->start_date[i] = wire[at++]; }
  record->price_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->spread_to_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->benchmark_curve_points_units[i] = wire[at++]; }
  record->benchmark_curve_points_value = wire[at++];
  for (size_t i = 0; i < 25; i++) { record->benchmark_security_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_r_8[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Update Report Message is what was written, byte for byte */
static void equal_security_list_update_report_message(const SecurityListUpdateReportMessage *read, const SecurityListUpdateReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->fisn[i] == written->fisn[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->issuer_lei[i] == written->issuer_lei[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_type[i] == written->security_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spre[i] == written->li_spre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipre[i] == written->sst_ipre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spost[i] == written->li_spost[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipost[i] == written->sst_ipost[i]); }
  assert(read->liquid_instrument == written->liquid_instrument);
  assert(read->admission_requested_by_issuer == written->admission_requested_by_issuer);
  for (size_t i = 0; i < 4; i++) { assert(read->min_trade_vol[i] == written->min_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot[i] == written->round_lot[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modality_mask_b_4[i] == written->modality_mask_b_4[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->security_description[i] == written->security_description[i]); }
  assert(read->trading_obligation == written->trading_obligation);
  for (size_t i = 0; i < 40; i++) { assert(read->security_name[i] == written->security_name[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_payment_date[i] == written->coupon_payment_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment[i] == written->min_price_increment[i]); }
  assert(read->number_of_decimals == written->number_of_decimals);
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  for (size_t i = 0; i < 8; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->trading_scope_b_1 == written->trading_scope_b_1);
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  for (size_t i = 0; i < 8; i++) { assert(read->maturity[i] == written->maturity[i]); }
  assert(read->coupon_periodicity == written->coupon_periodicity);
  assert(read->benchmark == written->benchmark);
  assert(read->strippable == written->strippable);
  for (size_t i = 0; i < 8; i++) { assert(read->volume_issued[i] == written->volume_issued[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alive_volume[i] == written->alive_volume[i]); }
  assert(read->coupon_type == written->coupon_type);
  assert(read->coupon_quotation == written->coupon_quotation);
  assert(read->accrued_interest_calculation_procedure == written->accrued_interest_calculation_procedure);
  for (size_t i = 0; i < 4; i++) { assert(read->next_redemption_date[i] == written->next_redemption_date[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->type_of_redemption[i] == written->type_of_redemption[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->facial[i] == written->facial[i]); }
  assert(read->calculation_method == written->calculation_method);
  for (size_t i = 0; i < 4; i++) { assert(read->date_last_coupon_was_paid[i] == written->date_last_coupon_was_paid[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bond_seniority[i] == written->bond_seniority[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->interest_accrual_date[i] == written->interest_accrual_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->start_date[i] == written->start_date[i]); }
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 8; i++) { assert(read->spread_to_index[i] == written->spread_to_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->benchmark_curve_points_units[i] == written->benchmark_curve_points_units[i]); }
  assert(read->benchmark_curve_points_value == written->benchmark_curve_points_value);
  for (size_t i = 0; i < 25; i++) { assert(read->benchmark_security_id[i] == written->benchmark_security_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_rate_r_8[i] == written->accrued_interest_rate_r_8[i]); }
}

/* Security List Update Report Message: written and read back, then read and written back */
static void check_security_list_update_report_message(void) {
  SecurityListUpdateReportMessage sent;
  SecurityListUpdateReportMessage got;
  uint8_t wire[450];
  uint8_t again[450];

  any_security_list_update_report_message(&sent);
  assert(encode_security_list_update_report_message(&sent, wire, 0) == 450);
  assert(decode_security_list_update_report_message(&got, wire, 0) == 450);
  equal_security_list_update_report_message(&got, &sent);

  for (size_t i = 0; i < 450; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_update_report_message(&got, wire, 0) == 450);
  assert(encode_security_list_update_report_message(&got, again, 0) == 450);
  for (size_t i = 0; i < 450; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 59 bytes --------------------------------------- */

/* Message sent by the server to inform on the status of one security */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t reference_price[8];            /* bytes 16 to 23 */
  uint8_t security_trading_status;       /* byte 24 */
  uint8_t non_availability_reason;       /* byte 25 */
  uint8_t high_limit_price[8];           /* bytes 26 to 33 */
  uint8_t low_limit_price[8];            /* bytes 34 to 41 */
  uint8_t static_range_type;             /* byte 42 */
  uint8_t order_static_range[8];         /* bytes 43 to 50 */
  uint8_t block_static_range[8];         /* bytes 51 to 58 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  record->non_availability_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  record->static_range_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_static_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->block_static_range[i] = arbitrary(); }
}

/* Security Status Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  wire[at++] = record->security_trading_status;
  wire[at++] = record->non_availability_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  wire[at++] = record->static_range_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_static_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->block_static_range[i]; }

  return at;
}

/* Security Status Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  record->non_availability_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  record->static_range_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_static_range[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->block_static_range[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->non_availability_reason == written->non_availability_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  assert(read->static_range_type == written->static_range_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_static_range[i] == written->order_static_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->block_static_range[i] == written->block_static_range[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 59);
  assert(decode_security_status_message(&got, wire, 0) == 59);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 59);
  assert(encode_security_status_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Book Clear Message: 16 bytes -------------------------------------- */

/* Message sent by the UDP full-depth server whenever the information about order prices must be reset. In particular, it is sent by the server when the trading mode changes from auction to open market and vice versa */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
} OrderBookClearMessage;

/* any Order Book Clear Message at all: every byte one the checker chooses */
static void any_order_book_clear_message(OrderBookClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
}

/* Order Book Clear Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_order_book_clear_message(const OrderBookClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }

  return at;
}

/* Order Book Clear Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_order_book_clear_message(OrderBookClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }

  return at;
}

/* what was read of Order Book Clear Message is what was written, byte for byte */
static void equal_order_book_clear_message(const OrderBookClearMessage *read, const OrderBookClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
}

/* Order Book Clear Message: written and read back, then read and written back */
static void check_order_book_clear_message(void) {
  OrderBookClearMessage sent;
  OrderBookClearMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_order_book_clear_message(&sent);
  assert(encode_order_book_clear_message(&sent, wire, 0) == 16);
  assert(decode_order_book_clear_message(&got, wire, 0) == 16);
  equal_order_book_clear_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_order_book_clear_message(&got, wire, 0) == 16);
  assert(encode_order_book_clear_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Market Pre Transparency Information Message: 49 bytes ------------- */

/* Used by the Server to communicate information about all active visible orders. During a session, any order is uniquely identified by the SecondaryOrderID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
  uint8_t side;                          /* byte 24 */
  uint8_t priority[4];                   /* bytes 25 to 28 */
  uint8_t price[8];                      /* bytes 29 to 36 */
  uint8_t display_qty[4];                /* bytes 37 to 40 */
  uint8_t alt_price[8];                  /* bytes 41 to 48 */
} OrderMarketPreTransparencyInformationMessage;

/* any Order Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_order_market_pre_transparency_information_message(OrderMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
}

/* Order Market Pre Transparency Information Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_order_market_pre_transparency_information_message(const OrderMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }

  return at;
}

/* Order Market Pre Transparency Information Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_order_market_pre_transparency_information_message(OrderMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }

  return at;
}

/* what was read of Order Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_order_market_pre_transparency_information_message(const OrderMarketPreTransparencyInformationMessage *read, const OrderMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
}

/* Order Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_order_market_pre_transparency_information_message(void) {
  OrderMarketPreTransparencyInformationMessage sent;
  OrderMarketPreTransparencyInformationMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_order_market_pre_transparency_information_message(&sent);
  assert(encode_order_market_pre_transparency_information_message(&sent, wire, 0) == 49);
  assert(decode_order_market_pre_transparency_information_message(&got, wire, 0) == 49);
  equal_order_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_order_market_pre_transparency_information_message(&got, wire, 0) == 49);
  assert(encode_order_market_pre_transparency_information_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Market Pre Transparency Information Message: 72 bytes ------------- */

/* Used by the Server to communicate information about active quotes. In a session, a Quote is univoquely identified by its two orders: SecurityCode and SecondaryOrderID (buy order) and SecondaryOrderID2 (sell order) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
  uint8_t priority[4];                   /* bytes 24 to 27 */
  uint8_t price[8];                      /* bytes 28 to 35 */
  uint8_t display_qty[4];                /* bytes 36 to 39 */
  uint8_t alt_price[8];                  /* bytes 40 to 47 */
  uint8_t priority_2[4];                 /* bytes 48 to 51 */
  uint8_t price_2[8];                    /* bytes 52 to 59 */
  uint8_t display_qty_2[4];              /* bytes 60 to 63 */
  uint8_t alt_price_2[8];                /* bytes 64 to 71 */
} QuoteMarketPreTransparencyInformationMessage;

/* any Quote Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_quote_market_pre_transparency_information_message(QuoteMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = arbitrary(); }
}

/* Quote Market Pre Transparency Information Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_quote_market_pre_transparency_information_message(const QuoteMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price_2[i]; }

  return at;
}

/* Quote Market Pre Transparency Information Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_quote_market_pre_transparency_information_message(QuoteMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_quote_market_pre_transparency_information_message(const QuoteMarketPreTransparencyInformationMessage *read, const QuoteMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price_2[i] == written->alt_price_2[i]); }
}

/* Quote Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_quote_market_pre_transparency_information_message(void) {
  QuoteMarketPreTransparencyInformationMessage sent;
  QuoteMarketPreTransparencyInformationMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_quote_market_pre_transparency_information_message(&sent);
  assert(encode_quote_market_pre_transparency_information_message(&sent, wire, 0) == 72);
  assert(decode_quote_market_pre_transparency_information_message(&got, wire, 0) == 72);
  equal_quote_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_market_pre_transparency_information_message(&got, wire, 0) == 72);
  assert(encode_quote_market_pre_transparency_information_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Market Member Message: 24 bytes ---------------------- */

/* Used by the Server to communicate information order cancellation. The same message is used in Full-Depth data feeds (for order cancellations of any user), in the Order Entry Server (for cancellations of user orders) and in the Market & Order Server (for order cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
} OrderCancellationMarketMemberMessage;

/* any Order Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
}

/* Order Cancellation Market Member Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }

  return at;
}

/* Order Cancellation Market Member Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Market Member Message is what was written, byte for byte */
static void equal_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *read, const OrderCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
}

/* Order Cancellation Market Member Message: written and read back, then read and written back */
static void check_order_cancellation_market_member_message(void) {
  OrderCancellationMarketMemberMessage sent;
  OrderCancellationMarketMemberMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_cancellation_market_member_message(&sent);
  assert(encode_order_cancellation_market_member_message(&sent, wire, 0) == 24);
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 24);
  equal_order_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 24);
  assert(encode_order_cancellation_market_member_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Market Member Message: 24 bytes ---------------------- */

/* Used by the Server to communicate information about quote cancellation. The same message is used in Full-Depth data feeds (for quote cancellations of any user), in the Order Entry Server (for cancellations of user quotes) and in the Market & Order Server (for quote cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
} QuoteCancellationMarketMemberMessage;

/* any Quote Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
}

/* Quote Cancellation Market Member Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }

  return at;
}

/* Quote Cancellation Market Member Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Cancellation Market Member Message is what was written, byte for byte */
static void equal_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *read, const QuoteCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
}

/* Quote Cancellation Market Member Message: written and read back, then read and written back */
static void check_quote_cancellation_market_member_message(void) {
  QuoteCancellationMarketMemberMessage sent;
  QuoteCancellationMarketMemberMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quote_cancellation_market_member_message(&sent);
  assert(encode_quote_cancellation_market_member_message(&sent, wire, 0) == 24);
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 24);
  equal_quote_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 24);
  assert(encode_quote_cancellation_market_member_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Market Post Transparency Information Top Of Book Message: 78 bytes ---- */

/* Used by the server to communicate trade information related to trades resulting from order matching in channels C/D and E/F. It is also used in channels A/B when the trade is the result of order matching at the end of an auction period (where only top-of-book information is shown) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t market_segment_id[4];          /* bytes 16 to 19 */
  uint8_t trading_session_id;            /* byte 20 */
  uint8_t trd_match_id[4];               /* bytes 21 to 24 */
  uint8_t trade_type;                    /* byte 25 */
  uint8_t last_px[8];                    /* bytes 26 to 33 */
  uint8_t last_qty[4];                   /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];            /* bytes 38 to 45 */
  uint8_t designation;                   /* byte 46 */
  uint8_t market_mechanism;              /* byte 47 */
  uint8_t algo_flag;                     /* byte 48 */
  uint8_t alt_last_px[8];                /* bytes 49 to 56 */
  uint8_t accrued_interest_amt[8];       /* bytes 57 to 64 */
  uint8_t accrued_interest_rate_p_8[8];  /* bytes 65 to 72 */
  uint8_t settl_date[4];                 /* bytes 73 to 76 */
  uint8_t transaction_category;          /* byte 77 */
} TradeMarketPostTransparencyInformationTopOfBookMessage;

/* any Trade Market Post Transparency Information Top Of Book Message at all: every byte one the checker chooses */
static void any_trade_market_post_transparency_information_top_of_book_message(TradeMarketPostTransparencyInformationTopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = arbitrary(); }
  record->designation = arbitrary();
  record->market_mechanism = arbitrary();
  record->algo_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
}

/* Trade Market Post Transparency Information Top Of Book Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_trade_market_post_transparency_information_top_of_book_message(const TradeMarketPostTransparencyInformationTopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gross_trade_amt[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->algo_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_amt[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_rate_p_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;

  return at;
}

/* Trade Market Post Transparency Information Top Of Book Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_trade_market_post_transparency_information_top_of_book_message(TradeMarketPostTransparencyInformationTopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = wire[at++]; }
  record->designation = wire[at++];
  record->market_mechanism = wire[at++];
  record->algo_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];

  return at;
}

/* what was read of Trade Market Post Transparency Information Top Of Book Message is what was written, byte for byte */
static void equal_trade_market_post_transparency_information_top_of_book_message(const TradeMarketPostTransparencyInformationTopOfBookMessage *read, const TradeMarketPostTransparencyInformationTopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gross_trade_amt[i] == written->gross_trade_amt[i]); }
  assert(read->designation == written->designation);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->algo_flag == written->algo_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->alt_last_px[i] == written->alt_last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_amt[i] == written->accrued_interest_amt[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_rate_p_8[i] == written->accrued_interest_rate_p_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
}

/* Trade Market Post Transparency Information Top Of Book Message: written and read back, then read and written back */
static void check_trade_market_post_transparency_information_top_of_book_message(void) {
  TradeMarketPostTransparencyInformationTopOfBookMessage sent;
  TradeMarketPostTransparencyInformationTopOfBookMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_trade_market_post_transparency_information_top_of_book_message(&sent);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&sent, wire, 0) == 78);
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 78);
  equal_trade_market_post_transparency_information_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 78);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation Message: 125 bytes ---------------- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. In this message, all fields with the suffix 2 refer to the sell order, and the ones without the suffix refer either to both legs or the buy order */
typedef struct {
  uint8_t sequence_number[4];              /* bytes 0 to 3 */
  uint8_t security_code[4];                /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];    /* bytes 8 to 15 */
  uint8_t market_segment_id[4];            /* bytes 16 to 19 */
  uint8_t trading_session_id;              /* byte 20 */
  uint8_t trd_match_id[4];                 /* bytes 21 to 24 */
  uint8_t trade_type;                      /* byte 25 */
  uint8_t last_px[8];                      /* bytes 26 to 33 */
  uint8_t last_qty[4];                     /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];              /* bytes 38 to 45 */
  uint8_t designation;                     /* byte 46 */
  uint8_t market_mechanism;                /* byte 47 */
  uint8_t algo_flag;                       /* byte 48 */
  uint8_t alt_last_px[8];                  /* bytes 49 to 56 */
  uint8_t accrued_interest_amt[8];         /* bytes 57 to 64 */
  uint8_t accrued_interest_rate_p_8[8];    /* bytes 65 to 72 */
  uint8_t settl_date[4];                   /* bytes 73 to 76 */
  uint8_t transaction_category;            /* byte 77 */
  uint8_t last_change_flag;                /* byte 78 */
  uint8_t benc_rfpt_flag;                  /* byte 79 */
  uint8_t trade_price_condition;           /* byte 80 */
  uint8_t pre_trade_transparency_waiver;   /* byte 81 */
  uint8_t deferral_waiver;                 /* byte 82 */
  uint8_t post_deferral_publication_type;  /* byte 83 */
  uint8_t publish_date_and_time[8];        /* bytes 84 to 91 */
  uint8_t trade_date[8];                   /* bytes 92 to 99 */
  uint8_t trade_session_date[4];           /* bytes 100 to 103 */
  uint8_t settl_date_2[4];                 /* bytes 104 to 107 */
  uint8_t end_cash[8];                     /* bytes 108 to 115 */
  uint8_t amended_trade_type;              /* byte 116 */
  uint8_t exec_ref_id[4];                  /* bytes 117 to 120 */
  uint8_t amended_trade_date[4];           /* bytes 121 to 124 */
} TradeTradeAmendmentOrCancellationMessage;

/* any Trade Trade Amendment Or Cancellation Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation_message(TradeTradeAmendmentOrCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = arbitrary(); }
  record->designation = arbitrary();
  record->market_mechanism = arbitrary();
  record->algo_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  record->post_deferral_publication_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settl_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_cash[i] = arbitrary(); }
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation Message to the wire: 125 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation_message(const TradeTradeAmendmentOrCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gross_trade_amt[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->algo_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_amt[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_rate_p_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  wire[at++] = record->post_deferral_publication_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_cash[i]; }
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation Message off the wire: 125 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation_message(TradeTradeAmendmentOrCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = wire[at++]; }
  record->designation = wire[at++];
  record->market_mechanism = wire[at++];
  record->algo_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  record->post_deferral_publication_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settl_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_cash[i] = wire[at++]; }
  record->amended_trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation_message(const TradeTradeAmendmentOrCancellationMessage *read, const TradeTradeAmendmentOrCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gross_trade_amt[i] == written->gross_trade_amt[i]); }
  assert(read->designation == written->designation);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->algo_flag == written->algo_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->alt_last_px[i] == written->alt_last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_amt[i] == written->accrued_interest_amt[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_rate_p_8[i] == written->accrued_interest_rate_p_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  assert(read->post_deferral_publication_type == written->post_deferral_publication_type);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date_2[i] == written->settl_date_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_cash[i] == written->end_cash[i]); }
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
}

/* Trade Trade Amendment Or Cancellation Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation_message(void) {
  TradeTradeAmendmentOrCancellationMessage sent;
  TradeTradeAmendmentOrCancellationMessage got;
  uint8_t wire[125];
  uint8_t again[125];

  any_trade_trade_amendment_or_cancellation_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation_message(&sent, wire, 0) == 125);
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 125);
  equal_trade_trade_amendment_or_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 125; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 125);
  assert(encode_trade_trade_amendment_or_cancellation_message(&got, again, 0) == 125);
  for (size_t i = 0; i < 125; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Market Post Transparency Information Full Depth Message: 142 bytes ---- */

/* Used by the server to communicate trade information related to trades resulting from order matching. The message also contains the situation in which the relevant orders will remain in the books */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t market_segment_id[4];          /* bytes 16 to 19 */
  uint8_t trading_session_id;            /* byte 20 */
  uint8_t trd_match_id[4];               /* bytes 21 to 24 */
  uint8_t trade_type;                    /* byte 25 */
  uint8_t last_px[8];                    /* bytes 26 to 33 */
  uint8_t last_qty[4];                   /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];            /* bytes 38 to 45 */
  uint8_t designation;                   /* byte 46 */
  uint8_t market_mechanism;              /* byte 47 */
  uint8_t algo_flag;                     /* byte 48 */
  uint8_t alt_last_px[8];                /* bytes 49 to 56 */
  uint8_t accrued_interest_amt[8];       /* bytes 57 to 64 */
  uint8_t accrued_interest_rate_p_8[8];  /* bytes 65 to 72 */
  uint8_t settl_date[4];                 /* bytes 73 to 76 */
  uint8_t transaction_category;          /* byte 77 */
  uint8_t secondary_order_id[4];         /* bytes 78 to 81 */
  uint8_t entry_date[4];                 /* bytes 82 to 85 */
  uint8_t priority[4];                   /* bytes 86 to 89 */
  uint8_t price[8];                      /* bytes 90 to 97 */
  uint8_t display_qty[4];                /* bytes 98 to 101 */
  uint8_t alt_price[8];                  /* bytes 102 to 109 */
  uint8_t secondary_order_id_2[4];       /* bytes 110 to 113 */
  uint8_t entry_date_2[4];               /* bytes 114 to 117 */
  uint8_t priority_2[4];                 /* bytes 118 to 121 */
  uint8_t price_2[8];                    /* bytes 122 to 129 */
  uint8_t display_qty_2[4];              /* bytes 130 to 133 */
  uint8_t alt_price_2[8];                /* bytes 134 to 141 */
} TradeMarketPostTransparencyInformationFullDepthMessage;

/* any Trade Market Post Transparency Information Full Depth Message at all: every byte one the checker chooses */
static void any_trade_market_post_transparency_information_full_depth_message(TradeMarketPostTransparencyInformationFullDepthMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = arbitrary(); }
  record->designation = arbitrary();
  record->market_mechanism = arbitrary();
  record->algo_flag = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = arbitrary(); }
}

/* Trade Market Post Transparency Information Full Depth Message to the wire: 142 bytes from at, returning where the next byte goes */
static size_t encode_trade_market_post_transparency_information_full_depth_message(const TradeMarketPostTransparencyInformationFullDepthMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gross_trade_amt[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->algo_flag;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_last_px[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_amt[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->accrued_interest_rate_p_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price_2[i]; }

  return at;
}

/* Trade Market Post Transparency Information Full Depth Message off the wire: 142 bytes from at, returning where the next byte lies */
static size_t decode_trade_market_post_transparency_information_full_depth_message(TradeMarketPostTransparencyInformationFullDepthMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = wire[at++]; }
  record->designation = wire[at++];
  record->market_mechanism = wire[at++];
  record->algo_flag = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->alt_last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_amt[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->accrued_interest_rate_p_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Market Post Transparency Information Full Depth Message is what was written, byte for byte */
static void equal_trade_market_post_transparency_information_full_depth_message(const TradeMarketPostTransparencyInformationFullDepthMessage *read, const TradeMarketPostTransparencyInformationFullDepthMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gross_trade_amt[i] == written->gross_trade_amt[i]); }
  assert(read->designation == written->designation);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->algo_flag == written->algo_flag);
  for (size_t i = 0; i < 8; i++) { assert(read->alt_last_px[i] == written->alt_last_px[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_amt[i] == written->accrued_interest_amt[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->accrued_interest_rate_p_8[i] == written->accrued_interest_rate_p_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price_2[i] == written->alt_price_2[i]); }
}

/* Trade Market Post Transparency Information Full Depth Message: written and read back, then read and written back */
static void check_trade_market_post_transparency_information_full_depth_message(void) {
  TradeMarketPostTransparencyInformationFullDepthMessage sent;
  TradeMarketPostTransparencyInformationFullDepthMessage got;
  uint8_t wire[142];
  uint8_t again[142];

  any_trade_market_post_transparency_information_full_depth_message(&sent);
  assert(encode_trade_market_post_transparency_information_full_depth_message(&sent, wire, 0) == 142);
  assert(decode_trade_market_post_transparency_information_full_depth_message(&got, wire, 0) == 142);
  equal_trade_market_post_transparency_information_full_depth_message(&got, &sent);

  for (size_t i = 0; i < 142; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_market_post_transparency_information_full_depth_message(&got, wire, 0) == 142);
  assert(encode_trade_market_post_transparency_information_full_depth_message(&got, again, 0) == 142);
  for (size_t i = 0; i < 142; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indication Of Interest Message: 35 bytes -------------------------------- */

/* Used by the Server to notify an indication of interest on a specific instrument. This functionality is available in Fixed Income and Derivatives */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t ioiid[4];                      /* bytes 16 to 19 */
  uint8_t ioi_trans_type;                /* byte 20 */
  uint8_t side;                          /* byte 21 */
  uint8_t ioi_qty[4];                    /* bytes 22 to 25 */
  uint8_t ioi_price[8];                  /* bytes 26 to 33 */
  uint8_t trading_session_id;            /* byte 34 */
} IndicationOfInterestMessage;

/* any Indication Of Interest Message at all: every byte one the checker chooses */
static void any_indication_of_interest_message(IndicationOfInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ioiid[i] = arbitrary(); }
  record->ioi_trans_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ioi_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ioi_price[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
}

/* Indication Of Interest Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_indication_of_interest_message(const IndicationOfInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ioiid[i]; }
  wire[at++] = record->ioi_trans_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ioi_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ioi_price[i]; }
  wire[at++] = record->trading_session_id;

  return at;
}

/* Indication Of Interest Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_indication_of_interest_message(IndicationOfInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ioiid[i] = wire[at++]; }
  record->ioi_trans_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ioi_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ioi_price[i] = wire[at++]; }
  record->trading_session_id = wire[at++];

  return at;
}

/* what was read of Indication Of Interest Message is what was written, byte for byte */
static void equal_indication_of_interest_message(const IndicationOfInterestMessage *read, const IndicationOfInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ioiid[i] == written->ioiid[i]); }
  assert(read->ioi_trans_type == written->ioi_trans_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->ioi_qty[i] == written->ioi_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ioi_price[i] == written->ioi_price[i]); }
  assert(read->trading_session_id == written->trading_session_id);
}

/* Indication Of Interest Message: written and read back, then read and written back */
static void check_indication_of_interest_message(void) {
  IndicationOfInterestMessage sent;
  IndicationOfInterestMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_indication_of_interest_message(&sent);
  assert(encode_indication_of_interest_message(&sent, wire, 0) == 35);
  assert(decode_indication_of_interest_message(&got, wire, 0) == 35);
  equal_indication_of_interest_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_indication_of_interest_message(&got, wire, 0) == 35);
  assert(encode_indication_of_interest_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rfq Market Pre Transparency Information Message: 189 bytes -------------- */

/* Used by the server to communicate price information about RFQs. The contents of the RFQID field match those of the field IOIID in the corresponding Indication of Interest message */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t rfqid[4];                      /* bytes 4 to 7 */
  uint8_t trading_session_id;            /* byte 8 */
  uint8_t security_code[4];              /* bytes 9 to 12 */
  uint8_t transaction_date_and_time[8];  /* bytes 13 to 20 */
  uint8_t mid_buy_price[8];              /* bytes 21 to 28 */
  uint8_t mid_buy_volume[4];             /* bytes 29 to 32 */
  uint8_t buy_rf_qs_number[2];           /* bytes 33 to 34 */
  uint8_t mid_sell_price[8];             /* bytes 35 to 42 */
  uint8_t mid_sell_volume[4];            /* bytes 43 to 46 */
  uint8_t sell_rf_qs_number[2];          /* bytes 47 to 48 */
  uint8_t bid_orders_1[2];               /* bytes 49 to 50 */
  uint8_t bid_size_1[4];                 /* bytes 51 to 54 */
  uint8_t bid_px_1[8];                   /* bytes 55 to 62 */
  uint8_t ask_orders_1[2];               /* bytes 63 to 64 */
  uint8_t ask_size_1[4];                 /* bytes 65 to 68 */
  uint8_t ask_px_1[8];                   /* bytes 69 to 76 */
  uint8_t bid_orders_2[2];               /* bytes 77 to 78 */
  uint8_t bid_size_2[4];                 /* bytes 79 to 82 */
  uint8_t bid_px_2[8];                   /* bytes 83 to 90 */
  uint8_t ask_orders_2[2];               /* bytes 91 to 92 */
  uint8_t ask_size_2[4];                 /* bytes 93 to 96 */
  uint8_t ask_px_2[8];                   /* bytes 97 to 104 */
  uint8_t bid_orders_3[2];               /* bytes 105 to 106 */
  uint8_t bid_size_3[4];                 /* bytes 107 to 110 */
  uint8_t bid_px_3[8];                   /* bytes 111 to 118 */
  uint8_t ask_orders_3[2];               /* bytes 119 to 120 */
  uint8_t ask_size_3[4];                 /* bytes 121 to 124 */
  uint8_t ask_px_3[8];                   /* bytes 125 to 132 */
  uint8_t bid_orders_4[2];               /* bytes 133 to 134 */
  uint8_t bid_size_4[4];                 /* bytes 135 to 138 */
  uint8_t bid_px_4[8];                   /* bytes 139 to 146 */
  uint8_t ask_orders_4[2];               /* bytes 147 to 148 */
  uint8_t ask_size_4[4];                 /* bytes 149 to 152 */
  uint8_t ask_px_4[8];                   /* bytes 153 to 160 */
  uint8_t bid_orders_5[2];               /* bytes 161 to 162 */
  uint8_t bid_size_5[4];                 /* bytes 163 to 166 */
  uint8_t bid_px_5[8];                   /* bytes 167 to 174 */
  uint8_t ask_orders_5[2];               /* bytes 175 to 176 */
  uint8_t ask_size_5[4];                 /* bytes 177 to 180 */
  uint8_t ask_px_5[8];                   /* bytes 181 to 188 */
} RfqMarketPreTransparencyInformationMessage;

/* any Rfq Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_rfq_market_pre_transparency_information_message(RfqMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rfqid[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_buy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_buy_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_rf_qs_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_sell_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_sell_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_rf_qs_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = arbitrary(); }
}

/* Rfq Market Pre Transparency Information Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_rfq_market_pre_transparency_information_message(const RfqMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rfqid[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_buy_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_buy_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_rf_qs_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_sell_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_sell_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_rf_qs_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_3[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_3[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_4[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_4[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_5[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_5[i]; }

  return at;
}

/* Rfq Market Pre Transparency Information Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_rfq_market_pre_transparency_information_message(RfqMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rfqid[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_buy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_buy_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_rf_qs_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_sell_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_sell_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_rf_qs_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = wire[at++]; }

  return at;
}

/* what was read of Rfq Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_rfq_market_pre_transparency_information_message(const RfqMarketPreTransparencyInformationMessage *read, const RfqMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rfqid[i] == written->rfqid[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_buy_price[i] == written->mid_buy_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_buy_volume[i] == written->mid_buy_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_rf_qs_number[i] == written->buy_rf_qs_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_sell_price[i] == written->mid_sell_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_sell_volume[i] == written->mid_sell_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_rf_qs_number[i] == written->sell_rf_qs_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_1[i] == written->bid_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_2[i] == written->bid_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_2[i] == written->bid_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_2[i] == written->bid_px_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_2[i] == written->ask_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_2[i] == written->ask_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_2[i] == written->ask_px_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_3[i] == written->bid_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_3[i] == written->bid_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_3[i] == written->bid_px_3[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_3[i] == written->ask_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_3[i] == written->ask_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_3[i] == written->ask_px_3[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_4[i] == written->bid_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_4[i] == written->bid_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_4[i] == written->bid_px_4[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_4[i] == written->ask_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_4[i] == written->ask_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_4[i] == written->ask_px_4[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_5[i] == written->bid_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_5[i] == written->bid_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_5[i] == written->bid_px_5[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_5[i] == written->ask_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_5[i] == written->ask_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_5[i] == written->ask_px_5[i]); }
}

/* Rfq Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_rfq_market_pre_transparency_information_message(void) {
  RfqMarketPreTransparencyInformationMessage sent;
  RfqMarketPreTransparencyInformationMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_rfq_market_pre_transparency_information_message(&sent);
  assert(encode_rfq_market_pre_transparency_information_message(&sent, wire, 0) == 189);
  assert(decode_rfq_market_pre_transparency_information_message(&got, wire, 0) == 189);
  equal_rfq_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_rfq_market_pre_transparency_information_message(&got, wire, 0) == 189);
  assert(encode_rfq_market_pre_transparency_information_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book Message: 60 bytes ------------------------------------------- */

/* Used by the UDP Servers to communicate Top-of-book price information during auctions. When there is an indicative match price, the fields BidPx1 and AskPx1 will have the same value */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t bid_orders_1[2];               /* bytes 16 to 17 */
  uint8_t bid_size_1[4];                 /* bytes 18 to 21 */
  uint8_t bid_px_1[8];                   /* bytes 22 to 29 */
  uint8_t alt_bid_px_1[8];               /* bytes 30 to 37 */
  uint8_t ask_orders_1[2];               /* bytes 38 to 39 */
  uint8_t ask_size_1[4];                 /* bytes 40 to 43 */
  uint8_t ask_px_1[8];                   /* bytes 44 to 51 */
  uint8_t alt_sell_px_1[8];              /* bytes 52 to 59 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_sell_px_1[i] = arbitrary(); }
}

/* Top Of Book Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_bid_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_sell_px_1[i]; }

  return at;
}

/* Top Of Book Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_sell_px_1[i] = wire[at++]; }

  return at;
}

/* what was read of Top Of Book Message is what was written, byte for byte */
static void equal_top_of_book_message(const TopOfBookMessage *read, const TopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_1[i] == written->bid_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_bid_px_1[i] == written->alt_bid_px_1[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_sell_px_1[i] == written->alt_sell_px_1[i]); }
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 60);
  assert(decode_top_of_book_message(&got, wire, 0) == 60);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 60);
  assert(encode_top_of_book_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_response_message();
  check_logout_response_message();
  check_heartbeat_message();
  check_logon_message();
  check_reject_message();
  check_trading_session_status_message();
  check_news_message();
  check_security_list_cancellation_report_message();
  check_security_list_message();
  check_security_list_update_report_message();
  check_security_status_message();
  check_order_book_clear_message();
  check_order_market_pre_transparency_information_message();
  check_quote_market_pre_transparency_information_message();
  check_order_cancellation_market_member_message();
  check_quote_cancellation_market_member_message();
  check_trade_market_post_transparency_information_top_of_book_message();
  check_trade_trade_amendment_or_cancellation_message();
  check_trade_market_post_transparency_information_full_depth_message();
  check_indication_of_interest_message();
  check_rfq_market_pre_transparency_information_message();
  check_top_of_book_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
