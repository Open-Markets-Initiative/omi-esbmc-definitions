// bme/bmeequities/recovery/BmeEquities_Recovery_v1_6.c
/*
 * Bolsas y Mercados Españoles BME Equities Recovery
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

/* ---- Security List Message: 976 bytes ---------------------------------------- */

/* Message sent by the server to provide the definition of one security. It shares the same layout as the Security List Update Report message, but with a different Message Type */
typedef struct {
  uint8_t sequence_number[4];                              /* bytes 0 to 3 */
  uint8_t market_id[4];                                    /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                            /* bytes 8 to 11 */
  uint8_t security_code[4];                                /* bytes 12 to 15 */
  uint8_t symbol[22];                                      /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                                 /* bytes 38 to 49 */
  uint8_t fisn[35];                                        /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                                  /* bytes 85 to 104 */
  uint8_t security_group[2];                               /* bytes 105 to 106 */
  uint8_t cfi_code[6];                                     /* bytes 107 to 112 */
  uint8_t security_type[2];                                /* bytes 113 to 114 */
  uint8_t maturity_date[4];                                /* bytes 115 to 118 */
  uint8_t issue_date[4];                                   /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                          /* bytes 123 to 130 */
  uint8_t li_spre[8];                                      /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                                     /* bytes 139 to 146 */
  uint8_t li_spost[8];                                     /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                                    /* bytes 155 to 162 */
  uint8_t liquid_instrument;                               /* byte 163 */
  uint8_t admission_requested_by_issuer;                   /* byte 164 */
  uint8_t min_trade_vol[4];                                /* bytes 165 to 168 */
  uint8_t round_lot[4];                                    /* bytes 169 to 172 */
  uint8_t currency[3];                                     /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                            /* bytes 176 to 179 */
  uint8_t security_description[80];                        /* bytes 180 to 259 */
  uint8_t trading_obligation;                              /* byte 260 */
  uint8_t security_name[40];                               /* bytes 261 to 300 */
  uint8_t net_asset_value_identifier[7];                   /* bytes 301 to 307 */
  uint8_t security_sub_type[2];                            /* bytes 308 to 309 */
  uint8_t maturity_month_year[8];                          /* bytes 310 to 317 */
  uint8_t security_status;                                 /* byte 318 */
  uint8_t strike_price[8];                                 /* bytes 319 to 326 */
  uint8_t strike_value[8];                                 /* bytes 327 to 334 */
  uint8_t exercise_style;                                  /* byte 335 */
  uint8_t put_or_call;                                     /* byte 336 */
  uint8_t position_limit[8];                               /* bytes 337 to 344 */
  uint8_t nt_position_limit[8];                            /* bytes 345 to 352 */
  uint8_t issuer[12];                                      /* bytes 353 to 364 */
  uint8_t cp_reg_type;                                     /* byte 365 */
  uint8_t barrier[8];                                      /* bytes 366 to 373 */
  uint8_t last_trading_day[4];                             /* bytes 374 to 377 */
  uint8_t automatic_expiration;                            /* byte 378 */
  uint8_t fee_type[2];                                     /* bytes 379 to 380 */
  uint8_t barrier_2[8];                                    /* bytes 381 to 388 */
  uint8_t trigger_barrier[8];                              /* bytes 389 to 396 */
  uint8_t trigger_upper_barrier[8];                        /* bytes 397 to 404 */
  uint8_t average_quarterly_turnover[8];                   /* bytes 405 to 412 */
  uint8_t trading_scope;                                   /* byte 413 */
  uint8_t sicav_counterparty_member[4];                    /* bytes 414 to 417 */
  uint8_t net_asset_value_indicator;                       /* byte 418 */
  uint8_t reference_trading_venue;                         /* byte 419 */
  uint8_t outstanding_capital[8];                          /* bytes 420 to 427 */
  uint8_t first_trading_date[4];                           /* bytes 428 to 431 */
  uint8_t settlement_system;                               /* byte 432 */
  uint8_t number_of_decimals;                              /* byte 433 */
  uint8_t number_of_holders[4];                            /* bytes 434 to 437 */
  uint8_t outstanding_shares[4];                           /* bytes 438 to 441 */
  uint8_t minimum_authorized_shares[4];                    /* bytes 442 to 445 */
  uint8_t minimum_capital[8];                              /* bytes 446 to 453 */
  uint8_t last_admission_date[4];                          /* bytes 454 to 457 */
  uint8_t barrier_return[8];                               /* bytes 458 to 465 */
  uint8_t investment_fund_manager[80];                     /* bytes 466 to 545 */
  uint8_t effective_amount_filters_routed_orders[8];       /* bytes 546 to 553 */
  uint8_t order_number_of_decimals;                        /* byte 554 */
  uint8_t investment_fund_class;                           /* byte 555 */
  uint8_t master_fund_name[80];                            /* bytes 556 to 635 */
  uint8_t investment_fund_management_company[80];          /* bytes 636 to 715 */
  uint8_t investment_fund_depository[80];                  /* bytes 716 to 795 */
  uint8_t investment_fund_category[80];                    /* bytes 796 to 875 */
  uint8_t investment_fund_minimum_subscription_amount[8];  /* bytes 876 to 883 */
  uint8_t investment_fund_minimum_maintenance_amount[8];   /* bytes 884 to 891 */
  uint8_t investment_fund_cut_off_time[8];                 /* bytes 892 to 899 */
  uint8_t nav_communication_term;                          /* byte 900 */
  uint8_t investment_fund_number_of_decimals;              /* byte 901 */
  uint8_t commodity_derivative_indicator;                  /* byte 902 */
  uint8_t double_volume_cap_reached;                       /* byte 903 */
  uint8_t adt[8];                                          /* bytes 904 to 911 */
  uint8_t base_product[4];                                 /* bytes 912 to 915 */
  uint8_t sub_product[4];                                  /* bytes 916 to 919 */
  uint8_t further_sub_product[4];                          /* bytes 920 to 923 */
  uint8_t adnt[8];                                         /* bytes 924 to 931 */
  uint8_t price_tick_rule;                                 /* byte 932 */
  uint8_t underlying_symbol[22];                           /* bytes 933 to 954 */
  uint8_t underlying_isin[12];                             /* bytes 955 to 966 */
  uint8_t underlying_currency[3];                          /* bytes 967 to 969 */
  uint8_t minimum_display_qty[4];                          /* bytes 970 to 973 */
  uint8_t retail_service_flag;                             /* byte 974 */
  uint8_t self_match_prevention;                           /* byte 975 */
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
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->cp_reg_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->automatic_expiration = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = arbitrary(); }
  record->trading_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = arbitrary(); }
  record->net_asset_value_indicator = arbitrary();
  record->reference_trading_venue = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  record->number_of_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = arbitrary(); }
  record->order_number_of_decimals = arbitrary();
  record->investment_fund_class = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = arbitrary(); }
  record->nav_communication_term = arbitrary();
  record->investment_fund_number_of_decimals = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  record->double_volume_cap_reached = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = arbitrary(); }
  record->price_tick_rule = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = arbitrary(); }
  record->retail_service_flag = arbitrary();
  record->self_match_prevention = arbitrary();
}

/* Security List Message to the wire: 976 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_asset_value_identifier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nt_position_limit[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->cp_reg_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->automatic_expiration;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_upper_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_quarterly_turnover[i]; }
  wire[at++] = record->trading_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sicav_counterparty_member[i]; }
  wire[at++] = record->net_asset_value_indicator;
  wire[at++] = record->reference_trading_venue;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  wire[at++] = record->number_of_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_holders[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_authorized_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_admission_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_return[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_manager[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_amount_filters_routed_orders[i]; }
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->investment_fund_class;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->master_fund_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_management_company[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_depository[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_category[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_subscription_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_maintenance_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_cut_off_time[i]; }
  wire[at++] = record->nav_communication_term;
  wire[at++] = record->investment_fund_number_of_decimals;
  wire[at++] = record->commodity_derivative_indicator;
  wire[at++] = record->double_volume_cap_reached;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adnt[i]; }
  wire[at++] = record->price_tick_rule;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_display_qty[i]; }
  wire[at++] = record->retail_service_flag;
  wire[at++] = record->self_match_prevention;

  return at;
}

/* Security List Message off the wire: 976 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->cp_reg_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->automatic_expiration = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = wire[at++]; }
  record->trading_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = wire[at++]; }
  record->net_asset_value_indicator = wire[at++];
  record->reference_trading_venue = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  record->number_of_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = wire[at++]; }
  record->order_number_of_decimals = wire[at++];
  record->investment_fund_class = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = wire[at++]; }
  record->nav_communication_term = wire[at++];
  record->investment_fund_number_of_decimals = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  record->double_volume_cap_reached = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = wire[at++]; }
  record->price_tick_rule = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = wire[at++]; }
  record->retail_service_flag = wire[at++];
  record->self_match_prevention = wire[at++];

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
  for (size_t i = 0; i < 7; i++) { assert(read->net_asset_value_identifier[i] == written->net_asset_value_identifier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->position_limit[i] == written->position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nt_position_limit[i] == written->nt_position_limit[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->cp_reg_type == written->cp_reg_type);
  for (size_t i = 0; i < 8; i++) { assert(read->barrier[i] == written->barrier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->automatic_expiration == written->automatic_expiration);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_type[i] == written->fee_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_2[i] == written->barrier_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_barrier[i] == written->trigger_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_upper_barrier[i] == written->trigger_upper_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_quarterly_turnover[i] == written->average_quarterly_turnover[i]); }
  assert(read->trading_scope == written->trading_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->sicav_counterparty_member[i] == written->sicav_counterparty_member[i]); }
  assert(read->net_asset_value_indicator == written->net_asset_value_indicator);
  assert(read->reference_trading_venue == written->reference_trading_venue);
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_capital[i] == written->outstanding_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  assert(read->number_of_decimals == written->number_of_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_holders[i] == written->number_of_holders[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_authorized_shares[i] == written->minimum_authorized_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_capital[i] == written->minimum_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_admission_date[i] == written->last_admission_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_return[i] == written->barrier_return[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_manager[i] == written->investment_fund_manager[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_amount_filters_routed_orders[i] == written->effective_amount_filters_routed_orders[i]); }
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->investment_fund_class == written->investment_fund_class);
  for (size_t i = 0; i < 80; i++) { assert(read->master_fund_name[i] == written->master_fund_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_management_company[i] == written->investment_fund_management_company[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_depository[i] == written->investment_fund_depository[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_category[i] == written->investment_fund_category[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_subscription_amount[i] == written->investment_fund_minimum_subscription_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_maintenance_amount[i] == written->investment_fund_minimum_maintenance_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_cut_off_time[i] == written->investment_fund_cut_off_time[i]); }
  assert(read->nav_communication_term == written->nav_communication_term);
  assert(read->investment_fund_number_of_decimals == written->investment_fund_number_of_decimals);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  assert(read->double_volume_cap_reached == written->double_volume_cap_reached);
  for (size_t i = 0; i < 8; i++) { assert(read->adt[i] == written->adt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->adnt[i] == written->adnt[i]); }
  assert(read->price_tick_rule == written->price_tick_rule);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_display_qty[i] == written->minimum_display_qty[i]); }
  assert(read->retail_service_flag == written->retail_service_flag);
  assert(read->self_match_prevention == written->self_match_prevention);
}

/* Security List Message: written and read back, then read and written back */
static void check_security_list_message(void) {
  SecurityListMessage sent;
  SecurityListMessage got;
  uint8_t wire[976];
  uint8_t again[976];

  any_security_list_message(&sent);
  assert(encode_security_list_message(&sent, wire, 0) == 976);
  assert(decode_security_list_message(&got, wire, 0) == 976);
  equal_security_list_message(&got, &sent);

  for (size_t i = 0; i < 976; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_message(&got, wire, 0) == 976);
  assert(encode_security_list_message(&got, again, 0) == 976);
  for (size_t i = 0; i < 976; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Update Report Message: 976 bytes -------------------------- */

/* Message sent by the server for reporting updates, during the session, to the security definition */
typedef struct {
  uint8_t sequence_number[4];                              /* bytes 0 to 3 */
  uint8_t market_id[4];                                    /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                            /* bytes 8 to 11 */
  uint8_t security_code[4];                                /* bytes 12 to 15 */
  uint8_t symbol[22];                                      /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                                 /* bytes 38 to 49 */
  uint8_t fisn[35];                                        /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                                  /* bytes 85 to 104 */
  uint8_t security_group[2];                               /* bytes 105 to 106 */
  uint8_t cfi_code[6];                                     /* bytes 107 to 112 */
  uint8_t security_type[2];                                /* bytes 113 to 114 */
  uint8_t maturity_date[4];                                /* bytes 115 to 118 */
  uint8_t issue_date[4];                                   /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                          /* bytes 123 to 130 */
  uint8_t li_spre[8];                                      /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                                     /* bytes 139 to 146 */
  uint8_t li_spost[8];                                     /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                                    /* bytes 155 to 162 */
  uint8_t liquid_instrument;                               /* byte 163 */
  uint8_t admission_requested_by_issuer;                   /* byte 164 */
  uint8_t min_trade_vol[4];                                /* bytes 165 to 168 */
  uint8_t round_lot[4];                                    /* bytes 169 to 172 */
  uint8_t currency[3];                                     /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                            /* bytes 176 to 179 */
  uint8_t security_description[80];                        /* bytes 180 to 259 */
  uint8_t trading_obligation;                              /* byte 260 */
  uint8_t security_name[40];                               /* bytes 261 to 300 */
  uint8_t net_asset_value_identifier[7];                   /* bytes 301 to 307 */
  uint8_t security_sub_type[2];                            /* bytes 308 to 309 */
  uint8_t maturity_month_year[8];                          /* bytes 310 to 317 */
  uint8_t security_status;                                 /* byte 318 */
  uint8_t strike_price[8];                                 /* bytes 319 to 326 */
  uint8_t strike_value[8];                                 /* bytes 327 to 334 */
  uint8_t exercise_style;                                  /* byte 335 */
  uint8_t put_or_call;                                     /* byte 336 */
  uint8_t position_limit[8];                               /* bytes 337 to 344 */
  uint8_t nt_position_limit[8];                            /* bytes 345 to 352 */
  uint8_t issuer[12];                                      /* bytes 353 to 364 */
  uint8_t cp_reg_type;                                     /* byte 365 */
  uint8_t barrier[8];                                      /* bytes 366 to 373 */
  uint8_t last_trading_day[4];                             /* bytes 374 to 377 */
  uint8_t automatic_expiration;                            /* byte 378 */
  uint8_t fee_type[2];                                     /* bytes 379 to 380 */
  uint8_t barrier_2[8];                                    /* bytes 381 to 388 */
  uint8_t trigger_barrier[8];                              /* bytes 389 to 396 */
  uint8_t trigger_upper_barrier[8];                        /* bytes 397 to 404 */
  uint8_t average_quarterly_turnover[8];                   /* bytes 405 to 412 */
  uint8_t trading_scope;                                   /* byte 413 */
  uint8_t sicav_counterparty_member[4];                    /* bytes 414 to 417 */
  uint8_t net_asset_value_indicator;                       /* byte 418 */
  uint8_t reference_trading_venue;                         /* byte 419 */
  uint8_t outstanding_capital[8];                          /* bytes 420 to 427 */
  uint8_t first_trading_date[4];                           /* bytes 428 to 431 */
  uint8_t settlement_system;                               /* byte 432 */
  uint8_t number_of_decimals;                              /* byte 433 */
  uint8_t number_of_holders[4];                            /* bytes 434 to 437 */
  uint8_t outstanding_shares[4];                           /* bytes 438 to 441 */
  uint8_t minimum_authorized_shares[4];                    /* bytes 442 to 445 */
  uint8_t minimum_capital[8];                              /* bytes 446 to 453 */
  uint8_t last_admission_date[4];                          /* bytes 454 to 457 */
  uint8_t barrier_return[8];                               /* bytes 458 to 465 */
  uint8_t investment_fund_manager[80];                     /* bytes 466 to 545 */
  uint8_t effective_amount_filters_routed_orders[8];       /* bytes 546 to 553 */
  uint8_t order_number_of_decimals;                        /* byte 554 */
  uint8_t investment_fund_class;                           /* byte 555 */
  uint8_t master_fund_name[80];                            /* bytes 556 to 635 */
  uint8_t investment_fund_management_company[80];          /* bytes 636 to 715 */
  uint8_t investment_fund_depository[80];                  /* bytes 716 to 795 */
  uint8_t investment_fund_category[80];                    /* bytes 796 to 875 */
  uint8_t investment_fund_minimum_subscription_amount[8];  /* bytes 876 to 883 */
  uint8_t investment_fund_minimum_maintenance_amount[8];   /* bytes 884 to 891 */
  uint8_t investment_fund_cut_off_time[8];                 /* bytes 892 to 899 */
  uint8_t nav_communication_term;                          /* byte 900 */
  uint8_t investment_fund_number_of_decimals;              /* byte 901 */
  uint8_t commodity_derivative_indicator;                  /* byte 902 */
  uint8_t double_volume_cap_reached;                       /* byte 903 */
  uint8_t adt[8];                                          /* bytes 904 to 911 */
  uint8_t base_product[4];                                 /* bytes 912 to 915 */
  uint8_t sub_product[4];                                  /* bytes 916 to 919 */
  uint8_t further_sub_product[4];                          /* bytes 920 to 923 */
  uint8_t adnt[8];                                         /* bytes 924 to 931 */
  uint8_t price_tick_rule;                                 /* byte 932 */
  uint8_t underlying_symbol[22];                           /* bytes 933 to 954 */
  uint8_t underlying_isin[12];                             /* bytes 955 to 966 */
  uint8_t underlying_currency[3];                          /* bytes 967 to 969 */
  uint8_t minimum_display_qty[4];                          /* bytes 970 to 973 */
  uint8_t retail_service_flag;                             /* byte 974 */
  uint8_t self_match_prevention;                           /* byte 975 */
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
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->cp_reg_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->automatic_expiration = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = arbitrary(); }
  record->trading_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = arbitrary(); }
  record->net_asset_value_indicator = arbitrary();
  record->reference_trading_venue = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  record->number_of_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = arbitrary(); }
  record->order_number_of_decimals = arbitrary();
  record->investment_fund_class = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = arbitrary(); }
  record->nav_communication_term = arbitrary();
  record->investment_fund_number_of_decimals = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  record->double_volume_cap_reached = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = arbitrary(); }
  record->price_tick_rule = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = arbitrary(); }
  record->retail_service_flag = arbitrary();
  record->self_match_prevention = arbitrary();
}

/* Security List Update Report Message to the wire: 976 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_asset_value_identifier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nt_position_limit[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->cp_reg_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->automatic_expiration;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_upper_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_quarterly_turnover[i]; }
  wire[at++] = record->trading_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sicav_counterparty_member[i]; }
  wire[at++] = record->net_asset_value_indicator;
  wire[at++] = record->reference_trading_venue;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  wire[at++] = record->number_of_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_holders[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_authorized_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_admission_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_return[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_manager[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_amount_filters_routed_orders[i]; }
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->investment_fund_class;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->master_fund_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_management_company[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_depository[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_category[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_subscription_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_maintenance_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_cut_off_time[i]; }
  wire[at++] = record->nav_communication_term;
  wire[at++] = record->investment_fund_number_of_decimals;
  wire[at++] = record->commodity_derivative_indicator;
  wire[at++] = record->double_volume_cap_reached;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adnt[i]; }
  wire[at++] = record->price_tick_rule;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_display_qty[i]; }
  wire[at++] = record->retail_service_flag;
  wire[at++] = record->self_match_prevention;

  return at;
}

/* Security List Update Report Message off the wire: 976 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->cp_reg_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->automatic_expiration = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = wire[at++]; }
  record->trading_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = wire[at++]; }
  record->net_asset_value_indicator = wire[at++];
  record->reference_trading_venue = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  record->number_of_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = wire[at++]; }
  record->order_number_of_decimals = wire[at++];
  record->investment_fund_class = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = wire[at++]; }
  record->nav_communication_term = wire[at++];
  record->investment_fund_number_of_decimals = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  record->double_volume_cap_reached = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = wire[at++]; }
  record->price_tick_rule = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = wire[at++]; }
  record->retail_service_flag = wire[at++];
  record->self_match_prevention = wire[at++];

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
  for (size_t i = 0; i < 7; i++) { assert(read->net_asset_value_identifier[i] == written->net_asset_value_identifier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->position_limit[i] == written->position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nt_position_limit[i] == written->nt_position_limit[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->cp_reg_type == written->cp_reg_type);
  for (size_t i = 0; i < 8; i++) { assert(read->barrier[i] == written->barrier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->automatic_expiration == written->automatic_expiration);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_type[i] == written->fee_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_2[i] == written->barrier_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_barrier[i] == written->trigger_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_upper_barrier[i] == written->trigger_upper_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_quarterly_turnover[i] == written->average_quarterly_turnover[i]); }
  assert(read->trading_scope == written->trading_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->sicav_counterparty_member[i] == written->sicav_counterparty_member[i]); }
  assert(read->net_asset_value_indicator == written->net_asset_value_indicator);
  assert(read->reference_trading_venue == written->reference_trading_venue);
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_capital[i] == written->outstanding_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  assert(read->number_of_decimals == written->number_of_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_holders[i] == written->number_of_holders[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_authorized_shares[i] == written->minimum_authorized_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_capital[i] == written->minimum_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_admission_date[i] == written->last_admission_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_return[i] == written->barrier_return[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_manager[i] == written->investment_fund_manager[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_amount_filters_routed_orders[i] == written->effective_amount_filters_routed_orders[i]); }
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->investment_fund_class == written->investment_fund_class);
  for (size_t i = 0; i < 80; i++) { assert(read->master_fund_name[i] == written->master_fund_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_management_company[i] == written->investment_fund_management_company[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_depository[i] == written->investment_fund_depository[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_category[i] == written->investment_fund_category[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_subscription_amount[i] == written->investment_fund_minimum_subscription_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_maintenance_amount[i] == written->investment_fund_minimum_maintenance_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_cut_off_time[i] == written->investment_fund_cut_off_time[i]); }
  assert(read->nav_communication_term == written->nav_communication_term);
  assert(read->investment_fund_number_of_decimals == written->investment_fund_number_of_decimals);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  assert(read->double_volume_cap_reached == written->double_volume_cap_reached);
  for (size_t i = 0; i < 8; i++) { assert(read->adt[i] == written->adt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->adnt[i] == written->adnt[i]); }
  assert(read->price_tick_rule == written->price_tick_rule);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_display_qty[i] == written->minimum_display_qty[i]); }
  assert(read->retail_service_flag == written->retail_service_flag);
  assert(read->self_match_prevention == written->self_match_prevention);
}

/* Security List Update Report Message: written and read back, then read and written back */
static void check_security_list_update_report_message(void) {
  SecurityListUpdateReportMessage sent;
  SecurityListUpdateReportMessage got;
  uint8_t wire[976];
  uint8_t again[976];

  any_security_list_update_report_message(&sent);
  assert(encode_security_list_update_report_message(&sent, wire, 0) == 976);
  assert(decode_security_list_update_report_message(&got, wire, 0) == 976);
  equal_security_list_update_report_message(&got, &sent);

  for (size_t i = 0; i < 976; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_update_report_message(&got, wire, 0) == 976);
  assert(encode_security_list_update_report_message(&got, again, 0) == 976);
  for (size_t i = 0; i < 976; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 115 bytes -------------------------------------- */

/* Message sent by the server to inform on the status of one security */
typedef struct {
  uint8_t sequence_number[4];                      /* bytes 0 to 3 */
  uint8_t security_code[4];                        /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];            /* bytes 8 to 15 */
  uint8_t reference_price[8];                      /* bytes 16 to 23 */
  uint8_t static_price[8];                         /* bytes 24 to 31 */
  uint8_t dynamic_price_oscilation_percentage[8];  /* bytes 32 to 39 */
  uint8_t dynamic_range_multiplier;                /* byte 40 */
  uint8_t auction_trigger_price[8];                /* bytes 41 to 48 */
  uint8_t auction_end_time[8];                     /* bytes 49 to 56 */
  uint8_t liquidative_value_date[4];               /* bytes 57 to 60 */
  uint8_t bonus_warrants_with_active_bonus;        /* byte 61 */
  uint8_t security_trading_status;                 /* byte 62 */
  uint8_t auction_origin;                          /* byte 63 */
  uint8_t non_availability_reason;                 /* byte 64 */
  uint8_t exemption_situation;                     /* byte 65 */
  uint8_t block_oscilation_percentage[8];          /* bytes 66 to 73 */
  uint8_t high_limit_price[8];                     /* bytes 74 to 81 */
  uint8_t low_limit_price[8];                      /* bytes 82 to 89 */
  uint8_t liquidative_value[8];                    /* bytes 90 to 97 */
  uint8_t static_range_type;                       /* byte 98 */
  uint8_t order_static_range[8];                   /* bytes 99 to 106 */
  uint8_t block_static_range[8];                   /* bytes 107 to 114 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->static_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dynamic_price_oscilation_percentage[i] = arbitrary(); }
  record->dynamic_range_multiplier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_trigger_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->liquidative_value_date[i] = arbitrary(); }
  record->bonus_warrants_with_active_bonus = arbitrary();
  record->security_trading_status = arbitrary();
  record->auction_origin = arbitrary();
  record->non_availability_reason = arbitrary();
  record->exemption_situation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->block_oscilation_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->liquidative_value[i] = arbitrary(); }
  record->static_range_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_static_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->block_static_range[i] = arbitrary(); }
}

/* Security Status Message to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->static_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dynamic_price_oscilation_percentage[i]; }
  wire[at++] = record->dynamic_range_multiplier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_trigger_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->liquidative_value_date[i]; }
  wire[at++] = record->bonus_warrants_with_active_bonus;
  wire[at++] = record->security_trading_status;
  wire[at++] = record->auction_origin;
  wire[at++] = record->non_availability_reason;
  wire[at++] = record->exemption_situation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->block_oscilation_percentage[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->liquidative_value[i]; }
  wire[at++] = record->static_range_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_static_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->block_static_range[i]; }

  return at;
}

/* Security Status Message off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->static_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dynamic_price_oscilation_percentage[i] = wire[at++]; }
  record->dynamic_range_multiplier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_trigger_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->liquidative_value_date[i] = wire[at++]; }
  record->bonus_warrants_with_active_bonus = wire[at++];
  record->security_trading_status = wire[at++];
  record->auction_origin = wire[at++];
  record->non_availability_reason = wire[at++];
  record->exemption_situation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->block_oscilation_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->liquidative_value[i] = wire[at++]; }
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
  for (size_t i = 0; i < 8; i++) { assert(read->static_price[i] == written->static_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dynamic_price_oscilation_percentage[i] == written->dynamic_price_oscilation_percentage[i]); }
  assert(read->dynamic_range_multiplier == written->dynamic_range_multiplier);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_trigger_price[i] == written->auction_trigger_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_end_time[i] == written->auction_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->liquidative_value_date[i] == written->liquidative_value_date[i]); }
  assert(read->bonus_warrants_with_active_bonus == written->bonus_warrants_with_active_bonus);
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->auction_origin == written->auction_origin);
  assert(read->non_availability_reason == written->non_availability_reason);
  assert(read->exemption_situation == written->exemption_situation);
  for (size_t i = 0; i < 8; i++) { assert(read->block_oscilation_percentage[i] == written->block_oscilation_percentage[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->liquidative_value[i] == written->liquidative_value[i]); }
  assert(read->static_range_type == written->static_range_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_static_range[i] == written->order_static_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->block_static_range[i] == written->block_static_range[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[115];
  uint8_t again[115];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 115);
  assert(decode_security_status_message(&got, wire, 0) == 115);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 115);
  assert(encode_security_status_message(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
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

/* ---- Order Market Pre Transparency Information Message: 42 bytes ------------- */

/* Used by the Server to communicate information about all active visible orders. During a session, any order is uniquely identified by the SecondaryOrderID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
  uint8_t side;                          /* byte 25 */
  uint8_t priority[4];                   /* bytes 26 to 29 */
  uint8_t price[8];                      /* bytes 30 to 37 */
  uint8_t display_qty[4];                /* bytes 38 to 41 */
} OrderMarketPreTransparencyInformationMessage;

/* any Order Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_order_market_pre_transparency_information_message(OrderMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  record->retail_flag = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
}

/* Order Market Pre Transparency Information Message to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_order_market_pre_transparency_information_message(const OrderMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  wire[at++] = record->retail_flag;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }

  return at;
}

/* Order Market Pre Transparency Information Message off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_order_market_pre_transparency_information_message(OrderMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  record->retail_flag = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }

  return at;
}

/* what was read of Order Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_order_market_pre_transparency_information_message(const OrderMarketPreTransparencyInformationMessage *read, const OrderMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  assert(read->retail_flag == written->retail_flag);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
}

/* Order Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_order_market_pre_transparency_information_message(void) {
  OrderMarketPreTransparencyInformationMessage sent;
  OrderMarketPreTransparencyInformationMessage got;
  uint8_t wire[42];
  uint8_t again[42];

  any_order_market_pre_transparency_information_message(&sent);
  assert(encode_order_market_pre_transparency_information_message(&sent, wire, 0) == 42);
  assert(decode_order_market_pre_transparency_information_message(&got, wire, 0) == 42);
  equal_order_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_order_market_pre_transparency_information_message(&got, wire, 0) == 42);
  assert(encode_order_market_pre_transparency_information_message(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Market Pre Transparency Information Message: 57 bytes ------------- */

/* Used by the Server to communicate information about active quotes. In a session, a Quote is univoquely identified by its two orders: SecurityCode and SecondaryOrderID (buy order) and SecondaryOrderID2 (sell order) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
  uint8_t priority[4];                   /* bytes 25 to 28 */
  uint8_t price[8];                      /* bytes 29 to 36 */
  uint8_t display_qty[4];                /* bytes 37 to 40 */
  uint8_t priority_2[4];                 /* bytes 41 to 44 */
  uint8_t price_2[8];                    /* bytes 45 to 52 */
  uint8_t display_qty_2[4];              /* bytes 53 to 56 */
} QuoteMarketPreTransparencyInformationMessage;

/* any Quote Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_quote_market_pre_transparency_information_message(QuoteMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  record->retail_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
}

/* Quote Market Pre Transparency Information Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_quote_market_pre_transparency_information_message(const QuoteMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  wire[at++] = record->retail_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }

  return at;
}

/* Quote Market Pre Transparency Information Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_quote_market_pre_transparency_information_message(QuoteMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  record->retail_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_quote_market_pre_transparency_information_message(const QuoteMarketPreTransparencyInformationMessage *read, const QuoteMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  assert(read->retail_flag == written->retail_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
}

/* Quote Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_quote_market_pre_transparency_information_message(void) {
  QuoteMarketPreTransparencyInformationMessage sent;
  QuoteMarketPreTransparencyInformationMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_quote_market_pre_transparency_information_message(&sent);
  assert(encode_quote_market_pre_transparency_information_message(&sent, wire, 0) == 57);
  assert(decode_quote_market_pre_transparency_information_message(&got, wire, 0) == 57);
  equal_quote_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_market_pre_transparency_information_message(&got, wire, 0) == 57);
  assert(encode_quote_market_pre_transparency_information_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Market Member Message: 25 bytes ---------------------- */

/* Used by the Server to communicate information order cancellation. The same message is used in Full-Depth data feeds (for order cancellations of any user), in the Order Entry Server (for cancellations of user orders) and in the Market & Order Server (for order cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
} OrderCancellationMarketMemberMessage;

/* any Order Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  record->retail_flag = arbitrary();
}

/* Order Cancellation Market Member Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  wire[at++] = record->retail_flag;

  return at;
}

/* Order Cancellation Market Member Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  record->retail_flag = wire[at++];

  return at;
}

/* what was read of Order Cancellation Market Member Message is what was written, byte for byte */
static void equal_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *read, const OrderCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  assert(read->retail_flag == written->retail_flag);
}

/* Order Cancellation Market Member Message: written and read back, then read and written back */
static void check_order_cancellation_market_member_message(void) {
  OrderCancellationMarketMemberMessage sent;
  OrderCancellationMarketMemberMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_cancellation_market_member_message(&sent);
  assert(encode_order_cancellation_market_member_message(&sent, wire, 0) == 25);
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 25);
  equal_order_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 25);
  assert(encode_order_cancellation_market_member_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Market Member Message: 25 bytes ---------------------- */

/* Used by the Server to communicate information about quote cancellation. The same message is used in Full-Depth data feeds (for quote cancellations of any user), in the Order Entry Server (for cancellations of user quotes) and in the Market & Order Server (for quote cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
} QuoteCancellationMarketMemberMessage;

/* any Quote Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  record->retail_flag = arbitrary();
}

/* Quote Cancellation Market Member Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  wire[at++] = record->retail_flag;

  return at;
}

/* Quote Cancellation Market Member Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  record->retail_flag = wire[at++];

  return at;
}

/* what was read of Quote Cancellation Market Member Message is what was written, byte for byte */
static void equal_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *read, const QuoteCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  assert(read->retail_flag == written->retail_flag);
}

/* Quote Cancellation Market Member Message: written and read back, then read and written back */
static void check_quote_cancellation_market_member_message(void) {
  QuoteCancellationMarketMemberMessage sent;
  QuoteCancellationMarketMemberMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_quote_cancellation_market_member_message(&sent);
  assert(encode_quote_cancellation_market_member_message(&sent, wire, 0) == 25);
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 25);
  equal_quote_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 25);
  assert(encode_quote_cancellation_market_member_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Market Post Transparency Information Top Of Book Message: 55 bytes ---- */

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
  uint8_t buyer_bolsa_code;              /* byte 49 */
  uint8_t settl_date[4];                 /* bytes 50 to 53 */
  uint8_t transaction_category;          /* byte 54 */
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
}

/* Trade Market Post Transparency Information Top Of Book Message to the wire: 55 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;

  return at;
}

/* Trade Market Post Transparency Information Top Of Book Message off the wire: 55 bytes from at, returning where the next byte lies */
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
  record->buyer_bolsa_code = wire[at++];
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
}

/* Trade Market Post Transparency Information Top Of Book Message: written and read back, then read and written back */
static void check_trade_market_post_transparency_information_top_of_book_message(void) {
  TradeMarketPostTransparencyInformationTopOfBookMessage sent;
  TradeMarketPostTransparencyInformationTopOfBookMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_trade_market_post_transparency_information_top_of_book_message(&sent);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&sent, wire, 0) == 55);
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 55);
  equal_trade_market_post_transparency_information_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 55);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation Message: 98 bytes ----------------- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. In this message, all fields with the suffix 2 refer to the sell order, and the ones without the suffix refer either to both legs or the buy order */
typedef struct {
  uint8_t sequence_number[4];             /* bytes 0 to 3 */
  uint8_t security_code[4];               /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];   /* bytes 8 to 15 */
  uint8_t market_segment_id[4];           /* bytes 16 to 19 */
  uint8_t trading_session_id;             /* byte 20 */
  uint8_t trd_match_id[4];                /* bytes 21 to 24 */
  uint8_t trade_type;                     /* byte 25 */
  uint8_t last_px[8];                     /* bytes 26 to 33 */
  uint8_t last_qty[4];                    /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];             /* bytes 38 to 45 */
  uint8_t designation;                    /* byte 46 */
  uint8_t market_mechanism;               /* byte 47 */
  uint8_t algo_flag;                      /* byte 48 */
  uint8_t buyer_bolsa_code;               /* byte 49 */
  uint8_t settl_date[4];                  /* bytes 50 to 53 */
  uint8_t transaction_category;           /* byte 54 */
  uint8_t last_change_flag;               /* byte 55 */
  uint8_t benc_rfpt_flag;                 /* byte 56 */
  uint8_t trade_price_condition;          /* byte 57 */
  uint8_t pre_trade_transparency_waiver;  /* byte 58 */
  uint8_t deferral_waiver;                /* byte 59 */
  uint8_t publish_date_and_time[8];       /* bytes 60 to 67 */
  uint8_t trade_date[8];                  /* bytes 68 to 75 */
  uint8_t trade_session_date[4];          /* bytes 76 to 79 */
  uint8_t volume_float[8];                /* bytes 80 to 87 */
  uint8_t sicav_fund_counterparty_side;   /* byte 88 */
  uint8_t amended_trade_type;             /* byte 89 */
  uint8_t exec_ref_id[4];                 /* bytes 90 to 93 */
  uint8_t amended_trade_date[4];          /* bytes 94 to 97 */
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = arbitrary(); }
  record->sicav_fund_counterparty_side = arbitrary();
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation Message to the wire: 98 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_float[i]; }
  wire[at++] = record->sicav_fund_counterparty_side;
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation Message off the wire: 98 bytes from at, returning where the next byte lies */
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = wire[at++]; }
  record->sicav_fund_counterparty_side = wire[at++];
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_float[i] == written->volume_float[i]); }
  assert(read->sicav_fund_counterparty_side == written->sicav_fund_counterparty_side);
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
}

/* Trade Trade Amendment Or Cancellation Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation_message(void) {
  TradeTradeAmendmentOrCancellationMessage sent;
  TradeTradeAmendmentOrCancellationMessage got;
  uint8_t wire[98];
  uint8_t again[98];

  any_trade_trade_amendment_or_cancellation_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation_message(&sent, wire, 0) == 98);
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 98);
  equal_trade_trade_amendment_or_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 98; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 98);
  assert(encode_trade_trade_amendment_or_cancellation_message(&got, again, 0) == 98);
  for (size_t i = 0; i < 98; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Market Post Transparency Information Full Depth Message: 105 bytes ---- */

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
  uint8_t buyer_bolsa_code;              /* byte 49 */
  uint8_t settl_date[4];                 /* bytes 50 to 53 */
  uint8_t transaction_category;          /* byte 54 */
  uint8_t secondary_order_id[4];         /* bytes 55 to 58 */
  uint8_t entry_date[4];                 /* bytes 59 to 62 */
  uint8_t priority[4];                   /* bytes 63 to 66 */
  uint8_t price[8];                      /* bytes 67 to 74 */
  uint8_t display_qty[4];                /* bytes 75 to 78 */
  uint8_t retail_flag;                   /* byte 79 */
  uint8_t secondary_order_id_2[4];       /* bytes 80 to 83 */
  uint8_t entry_date_2[4];               /* bytes 84 to 87 */
  uint8_t priority_2[4];                 /* bytes 88 to 91 */
  uint8_t price_2[8];                    /* bytes 92 to 99 */
  uint8_t display_qty_2[4];              /* bytes 100 to 103 */
  uint8_t retail_flag_2;                 /* byte 104 */
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  record->retail_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  record->retail_flag_2 = arbitrary();
}

/* Trade Market Post Transparency Information Full Depth Message to the wire: 105 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  wire[at++] = record->retail_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  wire[at++] = record->retail_flag_2;

  return at;
}

/* Trade Market Post Transparency Information Full Depth Message off the wire: 105 bytes from at, returning where the next byte lies */
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  record->retail_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  record->retail_flag_2 = wire[at++];

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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  assert(read->retail_flag == written->retail_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  assert(read->retail_flag_2 == written->retail_flag_2);
}

/* Trade Market Post Transparency Information Full Depth Message: written and read back, then read and written back */
static void check_trade_market_post_transparency_information_full_depth_message(void) {
  TradeMarketPostTransparencyInformationFullDepthMessage sent;
  TradeMarketPostTransparencyInformationFullDepthMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_trade_market_post_transparency_information_full_depth_message(&sent);
  assert(encode_trade_market_post_transparency_information_full_depth_message(&sent, wire, 0) == 105);
  assert(decode_trade_market_post_transparency_information_full_depth_message(&got, wire, 0) == 105);
  equal_trade_market_post_transparency_information_full_depth_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_market_post_transparency_information_full_depth_message(&got, wire, 0) == 105);
  assert(encode_trade_market_post_transparency_information_full_depth_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book Message: 44 bytes ------------------------------------------- */

/* Used by the UDP Servers to communicate Top-of-book price information during auctions. When there is an indicative match price, the fields BidPx1 and AskPx1 will have the same value */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t bid_orders_1[2];               /* bytes 16 to 17 */
  uint8_t bid_size_1[4];                 /* bytes 18 to 21 */
  uint8_t bid_px_1[8];                   /* bytes 22 to 29 */
  uint8_t ask_orders_1[2];               /* bytes 30 to 31 */
  uint8_t ask_size_1[4];                 /* bytes 32 to 35 */
  uint8_t ask_px_1[8];                   /* bytes 36 to 43 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
}

/* Top Of Book Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }

  return at;
}

/* Top Of Book Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }

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
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 44);
  assert(decode_top_of_book_message(&got, wire, 0) == 44);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 44);
  assert(encode_top_of_book_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
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
