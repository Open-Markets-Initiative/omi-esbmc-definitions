// bme/bmefixedincome/orderentry/BmeFixedIncome_OrderEntry_v1_6.c
/*
 * Bolsas y Mercados Españoles BME Fixed Income Order Entry
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

/* ---- Network Status Message: 5 bytes ----------------------------------------- */

/* Message sent by the server with information about the connectivity between the Server and the central systems. In the Network Status message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];    /* bytes 0 to 3 */
  uint8_t network_status_value;  /* byte 4 */
} NetworkStatusMessage;

/* any Network Status Message at all: every byte one the checker chooses */
static void any_network_status_message(NetworkStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->network_status_value = arbitrary();
}

/* Network Status Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_network_status_message(const NetworkStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->network_status_value;

  return at;
}

/* Network Status Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_network_status_message(NetworkStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->network_status_value = wire[at++];

  return at;
}

/* what was read of Network Status Message is what was written, byte for byte */
static void equal_network_status_message(const NetworkStatusMessage *read, const NetworkStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->network_status_value == written->network_status_value);
}

/* Network Status Message: written and read back, then read and written back */
static void check_network_status_message(void) {
  NetworkStatusMessage sent;
  NetworkStatusMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_network_status_message(&sent);
  assert(encode_network_status_message(&sent, wire, 0) == 5);
  assert(decode_network_status_message(&got, wire, 0) == 5);
  equal_network_status_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_network_status_message(&got, wire, 0) == 5);
  assert(encode_network_status_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
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
  uint8_t text_c_58[58];              /* bytes 5 to 62 */
  uint8_t msg_rejected_reference[7];  /* bytes 63 to 69 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->session_reject_reason = arbitrary();
  for (size_t i = 0; i < 58; i++) { record->text_c_58[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = arbitrary(); }
}

/* Reject Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->session_reject_reason;
  for (size_t i = 0; i < 58; i++) { wire[at++] = record->text_c_58[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->msg_rejected_reference[i]; }

  return at;
}

/* Reject Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->session_reject_reason = wire[at++];
  for (size_t i = 0; i < 58; i++) { record->text_c_58[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->session_reject_reason == written->session_reject_reason);
  for (size_t i = 0; i < 58; i++) { assert(read->text_c_58[i] == written->text_c_58[i]); }
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

/* ---- Order And Quote Client Data Message: 64 bytes --------------------------- */

/* Sent by the client to set default attributes for subsequent orders and quotes. Please note that in Fixed Income it is possible to enter orders on behalf of other members (AccountMember), based on the corresponding brokerage permissions */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t client_data_id[2];             /* bytes 4 to 5 */
  uint8_t algorithmic_trade_indicator;   /* byte 6 */
  uint8_t client_id[4];                  /* bytes 7 to 10 */
  uint8_t account_bolsa[16];             /* bytes 11 to 26 */
  uint8_t account[5];                    /* bytes 27 to 31 */
  uint8_t dea_flag;                      /* byte 32 */
  uint8_t decisor_id[4];                 /* bytes 33 to 36 */
  uint8_t executor_id[4];                /* bytes 37 to 40 */
  uint8_t liquidity_provision_activity;  /* byte 41 */
  uint8_t account_member[4];             /* bytes 42 to 45 */
  uint8_t last_capacity;                 /* byte 46 */
  uint8_t received_dept_id;              /* byte 47 */
  uint8_t persistence;                   /* byte 48 */
  uint8_t client_data_reference[15];     /* bytes 49 to 63 */
} OrderAndQuoteClientDataMessage;

/* any Order And Quote Client Data Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_message(const OrderAndQuoteClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Order And Quote Client Data Message is what was written, byte for byte */
static void equal_order_and_quote_client_data_message(const OrderAndQuoteClientDataMessage *read, const OrderAndQuoteClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_message(void) {
  OrderAndQuoteClientDataMessage sent;
  OrderAndQuoteClientDataMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_order_and_quote_client_data_message(&sent);
  assert(encode_order_and_quote_client_data_message(&sent, wire, 0) == 64);
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 64);
  equal_order_and_quote_client_data_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 64);
  assert(encode_order_and_quote_client_data_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order Message: 28 bytes -------------------------------------- */

/* Message sent by the client to enter a new order */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[4];        /* bytes 10 to 13 */
  uint8_t side;               /* byte 14 */
  uint8_t price[8];           /* bytes 15 to 22 */
  uint8_t order_qty[4];       /* bytes 23 to 26 */
  uint8_t time_in_force;      /* byte 27 */
} SimpleNewOrderMessage;

/* any Simple New Order Message at all: every byte one the checker chooses */
static void any_simple_new_order_message(SimpleNewOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->time_in_force = arbitrary();
}

/* Simple New Order Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_message(const SimpleNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;

  return at;
}

/* Simple New Order Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_message(SimpleNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];

  return at;
}

/* what was read of Simple New Order Message is what was written, byte for byte */
static void equal_simple_new_order_message(const SimpleNewOrderMessage *read, const SimpleNewOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->time_in_force == written->time_in_force);
}

/* Simple New Order Message: written and read back, then read and written back */
static void check_simple_new_order_message(void) {
  SimpleNewOrderMessage sent;
  SimpleNewOrderMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_simple_new_order_message(&sent);
  assert(encode_simple_new_order_message(&sent, wire, 0) == 28);
  assert(decode_simple_new_order_message(&got, wire, 0) == 28);
  equal_simple_new_order_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_message(&got, wire, 0) == 28);
  assert(encode_simple_new_order_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order With Client Data Message: 84 bytes --------------------- */

/* Message sent by the client to enter a new order and, at the same time, the values for the Client Data parmeters. Note that no ClientDataID may be assigned */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t order_id[4];                   /* bytes 8 to 11 */
  uint8_t side;                          /* byte 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t order_qty[4];                  /* bytes 21 to 24 */
  uint8_t time_in_force;                 /* byte 25 */
  uint8_t algorithmic_trade_indicator;   /* byte 26 */
  uint8_t client_id[4];                  /* bytes 27 to 30 */
  uint8_t account_bolsa[16];             /* bytes 31 to 46 */
  uint8_t account[5];                    /* bytes 47 to 51 */
  uint8_t dea_flag;                      /* byte 52 */
  uint8_t decisor_id[4];                 /* bytes 53 to 56 */
  uint8_t executor_id[4];                /* bytes 57 to 60 */
  uint8_t liquidity_provision_activity;  /* byte 61 */
  uint8_t account_member[4];             /* bytes 62 to 65 */
  uint8_t last_capacity;                 /* byte 66 */
  uint8_t received_dept_id;              /* byte 67 */
  uint8_t persistence;                   /* byte 68 */
  uint8_t client_data_reference[15];     /* bytes 69 to 83 */
} SimpleNewOrderWithClientDataMessage;

/* any Simple New Order With Client Data Message at all: every byte one the checker chooses */
static void any_simple_new_order_with_client_data_message(SimpleNewOrderWithClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple New Order With Client Data Message to the wire: 84 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_with_client_data_message(const SimpleNewOrderWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple New Order With Client Data Message off the wire: 84 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_with_client_data_message(SimpleNewOrderWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Simple New Order With Client Data Message is what was written, byte for byte */
static void equal_simple_new_order_with_client_data_message(const SimpleNewOrderWithClientDataMessage *read, const SimpleNewOrderWithClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple New Order With Client Data Message: written and read back, then read and written back */
static void check_simple_new_order_with_client_data_message(void) {
  SimpleNewOrderWithClientDataMessage sent;
  SimpleNewOrderWithClientDataMessage got;
  uint8_t wire[84];
  uint8_t again[84];

  any_simple_new_order_with_client_data_message(&sent);
  assert(encode_simple_new_order_with_client_data_message(&sent, wire, 0) == 84);
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 84);
  equal_simple_new_order_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 84; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 84);
  assert(encode_simple_new_order_with_client_data_message(&got, again, 0) == 84);
  for (size_t i = 0; i < 84; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Modification Message: 27 bytes ----------------------------- */

/* Message sent by the client to modify an order. The field OrderID must contain the client reference of the order that is to be modified */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t order_id[4];        /* bytes 8 to 11 */
  uint8_t side;               /* byte 12 */
  uint8_t price[8];           /* bytes 13 to 20 */
  uint8_t order_qty[4];       /* bytes 21 to 24 */
  uint8_t client_data_id[2];  /* bytes 25 to 26 */
} SimpleOrderModificationMessage;

/* any Simple Order Modification Message at all: every byte one the checker chooses */
static void any_simple_order_modification_message(SimpleOrderModificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Simple Order Modification Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_modification_message(const SimpleOrderModificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Simple Order Modification Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_modification_message(SimpleOrderModificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Modification Message is what was written, byte for byte */
static void equal_simple_order_modification_message(const SimpleOrderModificationMessage *read, const SimpleOrderModificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Simple Order Modification Message: written and read back, then read and written back */
static void check_simple_order_modification_message(void) {
  SimpleOrderModificationMessage sent;
  SimpleOrderModificationMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_simple_order_modification_message(&sent);
  assert(encode_simple_order_modification_message(&sent, wire, 0) == 27);
  assert(decode_simple_order_modification_message(&got, wire, 0) == 27);
  equal_simple_order_modification_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_modification_message(&got, wire, 0) == 27);
  assert(encode_simple_order_modification_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Modification With Client Data Message: 83 bytes ------------ */

/* Message sent by the client to modify an order. The field OrderID must contain the client reference of the order that is to be modified */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t order_id[4];                   /* bytes 8 to 11 */
  uint8_t side;                          /* byte 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t order_qty[4];                  /* bytes 21 to 24 */
  uint8_t algorithmic_trade_indicator;   /* byte 25 */
  uint8_t client_id[4];                  /* bytes 26 to 29 */
  uint8_t account_bolsa[16];             /* bytes 30 to 45 */
  uint8_t account[5];                    /* bytes 46 to 50 */
  uint8_t dea_flag;                      /* byte 51 */
  uint8_t decisor_id[4];                 /* bytes 52 to 55 */
  uint8_t executor_id[4];                /* bytes 56 to 59 */
  uint8_t liquidity_provision_activity;  /* byte 60 */
  uint8_t account_member[4];             /* bytes 61 to 64 */
  uint8_t last_capacity;                 /* byte 65 */
  uint8_t received_dept_id;              /* byte 66 */
  uint8_t persistence;                   /* byte 67 */
  uint8_t client_data_reference[15];     /* bytes 68 to 82 */
} SimpleOrderModificationWithClientDataMessage;

/* any Simple Order Modification With Client Data Message at all: every byte one the checker chooses */
static void any_simple_order_modification_with_client_data_message(SimpleOrderModificationWithClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple Order Modification With Client Data Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_modification_with_client_data_message(const SimpleOrderModificationWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple Order Modification With Client Data Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_modification_with_client_data_message(SimpleOrderModificationWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Modification With Client Data Message is what was written, byte for byte */
static void equal_simple_order_modification_with_client_data_message(const SimpleOrderModificationWithClientDataMessage *read, const SimpleOrderModificationWithClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple Order Modification With Client Data Message: written and read back, then read and written back */
static void check_simple_order_modification_with_client_data_message(void) {
  SimpleOrderModificationWithClientDataMessage sent;
  SimpleOrderModificationWithClientDataMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_simple_order_modification_with_client_data_message(&sent);
  assert(encode_simple_order_modification_with_client_data_message(&sent, wire, 0) == 83);
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 83);
  equal_simple_order_modification_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 83);
  assert(encode_simple_order_modification_with_client_data_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Request Message: 12 bytes ---------------------------- */

/* Message sent by the client to cancel an order. The field OrderID must contain a reference to the order that is to be cancelled */
typedef struct {
  uint8_t request_id[4];     /* bytes 0 to 3 */
  uint8_t security_code[4];  /* bytes 4 to 7 */
  uint8_t order_id[4];       /* bytes 8 to 11 */
} OrderCancellationRequestMessage;

/* any Order Cancellation Request Message at all: every byte one the checker chooses */
static void any_order_cancellation_request_message(OrderCancellationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Cancellation Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_request_message(const OrderCancellationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Cancellation Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_request_message(OrderCancellationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Request Message is what was written, byte for byte */
static void equal_order_cancellation_request_message(const OrderCancellationRequestMessage *read, const OrderCancellationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Cancellation Request Message: written and read back, then read and written back */
static void check_order_cancellation_request_message(void) {
  OrderCancellationRequestMessage sent;
  OrderCancellationRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_cancellation_request_message(&sent);
  assert(encode_order_cancellation_request_message(&sent, wire, 0) == 12);
  assert(decode_order_cancellation_request_message(&got, wire, 0) == 12);
  equal_order_cancellation_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_request_message(&got, wire, 0) == 12);
  assert(encode_order_cancellation_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Quote Message: 34 bytes --------------------------------------------- */

/* Message sent by the client application to create a new quote. A new quote by the same user on the same SecurityCode and with the same ClientDataID cancels the previous one */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t bid_size_1[4];      /* bytes 10 to 13 */
  uint8_t bid_px_1[8];        /* bytes 14 to 21 */
  uint8_t ask_size_1[4];      /* bytes 22 to 25 */
  uint8_t ask_px_1[8];        /* bytes 26 to 33 */
} NewQuoteMessage;

/* any New Quote Message at all: every byte one the checker chooses */
static void any_new_quote_message(NewQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
}

/* New Quote Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_new_quote_message(const NewQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }

  return at;
}

/* New Quote Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_new_quote_message(NewQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }

  return at;
}

/* what was read of New Quote Message is what was written, byte for byte */
static void equal_new_quote_message(const NewQuoteMessage *read, const NewQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
}

/* New Quote Message: written and read back, then read and written back */
static void check_new_quote_message(void) {
  NewQuoteMessage sent;
  NewQuoteMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_new_quote_message(&sent);
  assert(encode_new_quote_message(&sent, wire, 0) == 34);
  assert(decode_new_quote_message(&got, wire, 0) == 34);
  equal_new_quote_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_new_quote_message(&got, wire, 0) == 34);
  assert(encode_new_quote_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Modification Request Message: 26 bytes ---------------------------- */

/* Message sent by the client to modify a quote. Field ClientDataID is required in RF to identify a quote */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t bid_px_1[8];        /* bytes 10 to 17 */
  uint8_t ask_px_1[8];        /* bytes 18 to 25 */
} QuoteModificationRequestMessage;

/* any Quote Modification Request Message at all: every byte one the checker chooses */
static void any_quote_modification_request_message(QuoteModificationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
}

/* Quote Modification Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_quote_modification_request_message(const QuoteModificationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }

  return at;
}

/* Quote Modification Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_quote_modification_request_message(QuoteModificationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Modification Request Message is what was written, byte for byte */
static void equal_quote_modification_request_message(const QuoteModificationRequestMessage *read, const QuoteModificationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
}

/* Quote Modification Request Message: written and read back, then read and written back */
static void check_quote_modification_request_message(void) {
  QuoteModificationRequestMessage sent;
  QuoteModificationRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_quote_modification_request_message(&sent);
  assert(encode_quote_modification_request_message(&sent, wire, 0) == 26);
  assert(decode_quote_modification_request_message(&got, wire, 0) == 26);
  equal_quote_modification_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_modification_request_message(&got, wire, 0) == 26);
  assert(encode_quote_modification_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Request Message: 10 bytes ---------------------------- */

/* Message sent by the client to cancel a quote */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
} QuoteCancellationRequestMessage;

/* any Quote Cancellation Request Message at all: every byte one the checker chooses */
static void any_quote_cancellation_request_message(QuoteCancellationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Quote Cancellation Request Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_request_message(const QuoteCancellationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Quote Cancellation Request Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_request_message(QuoteCancellationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Cancellation Request Message is what was written, byte for byte */
static void equal_quote_cancellation_request_message(const QuoteCancellationRequestMessage *read, const QuoteCancellationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Quote Cancellation Request Message: written and read back, then read and written back */
static void check_quote_cancellation_request_message(void) {
  QuoteCancellationRequestMessage sent;
  QuoteCancellationRequestMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_quote_cancellation_request_message(&sent);
  assert(encode_quote_cancellation_request_message(&sent, wire, 0) == 10);
  assert(decode_quote_cancellation_request_message(&got, wire, 0) == 10);
  equal_quote_cancellation_request_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_request_message(&got, wire, 0) == 10);
  assert(encode_quote_cancellation_request_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Message: 48 bytes -------------------------- */

/* Message sent by the client to request the cancellation of multiple orders and or quotes, based on the specified selection criteria */
typedef struct {
  uint8_t request_id[4];          /* bytes 0 to 3 */
  uint8_t account[5];             /* bytes 4 to 8 */
  uint8_t security_code[4];       /* bytes 9 to 12 */
  uint8_t side;                   /* byte 13 */
  uint8_t cancellation_type;      /* byte 14 */
  uint8_t issuer[12];             /* bytes 15 to 26 */
  uint8_t account_bolsa[16];      /* bytes 27 to 42 */
  uint8_t account_member[4];      /* bytes 43 to 46 */
  uint8_t order_or_quote_cancel;  /* byte 47 */
} MassOrderquoteCancellationMessage;

/* any Mass Orderquote Cancellation Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->side = arbitrary();
  record->cancellation_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->order_or_quote_cancel = arbitrary();
}

/* Mass Orderquote Cancellation Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->side;
  wire[at++] = record->cancellation_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->order_or_quote_cancel;

  return at;
}

/* Mass Orderquote Cancellation Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->side = wire[at++];
  record->cancellation_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->order_or_quote_cancel = wire[at++];

  return at;
}

/* what was read of Mass Orderquote Cancellation Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *read, const MassOrderquoteCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->side == written->side);
  assert(read->cancellation_type == written->cancellation_type);
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->order_or_quote_cancel == written->order_or_quote_cancel);
}

/* Mass Orderquote Cancellation Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_message(void) {
  MassOrderquoteCancellationMessage sent;
  MassOrderquoteCancellationMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_mass_orderquote_cancellation_message(&sent);
  assert(encode_mass_orderquote_cancellation_message(&sent, wire, 0) == 48);
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 48);
  equal_mass_orderquote_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 48);
  assert(encode_mass_orderquote_cancellation_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order And Quote Client Data Parameters Ack Nack Message: 69 bytes ------- */

/* Sent by the server to confirm an Order and Quote Client Data Parameters message */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t request_id[4];                 /* bytes 4 to 7 */
  uint8_t status;                        /* byte 8 */
  uint8_t client_data_id[2];             /* bytes 9 to 10 */
  uint8_t algorithmic_trade_indicator;   /* byte 11 */
  uint8_t client_id[4];                  /* bytes 12 to 15 */
  uint8_t account_bolsa[16];             /* bytes 16 to 31 */
  uint8_t account[5];                    /* bytes 32 to 36 */
  uint8_t dea_flag;                      /* byte 37 */
  uint8_t decisor_id[4];                 /* bytes 38 to 41 */
  uint8_t executor_id[4];                /* bytes 42 to 45 */
  uint8_t liquidity_provision_activity;  /* byte 46 */
  uint8_t account_member[4];             /* bytes 47 to 50 */
  uint8_t last_capacity;                 /* byte 51 */
  uint8_t received_dept_id;              /* byte 52 */
  uint8_t persistence;                   /* byte 53 */
  uint8_t client_data_reference[15];     /* bytes 54 to 68 */
} OrderAndQuoteClientDataParametersAckNackMessage;

/* any Order And Quote Client Data Parameters Ack Nack Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Parameters Ack Nack Message to the wire: 69 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_parameters_ack_nack_message(const OrderAndQuoteClientDataParametersAckNackMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Parameters Ack Nack Message off the wire: 69 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Order And Quote Client Data Parameters Ack Nack Message is what was written, byte for byte */
static void equal_order_and_quote_client_data_parameters_ack_nack_message(const OrderAndQuoteClientDataParametersAckNackMessage *read, const OrderAndQuoteClientDataParametersAckNackMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Parameters Ack Nack Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_parameters_ack_nack_message(void) {
  OrderAndQuoteClientDataParametersAckNackMessage sent;
  OrderAndQuoteClientDataParametersAckNackMessage got;
  uint8_t wire[69];
  uint8_t again[69];

  any_order_and_quote_client_data_parameters_ack_nack_message(&sent);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&sent, wire, 0) == 69);
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 69);
  equal_order_and_quote_client_data_parameters_ack_nack_message(&got, &sent);

  for (size_t i = 0; i < 69; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 69);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&got, again, 0) == 69);
  for (size_t i = 0; i < 69; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Status Message: 70 bytes ----------------------------------- */

/* Sent by the server to inform about the order status. Please note that the first fields of this message are the same as the ones for Order Market Pre- Transparency Information (Msg Type = 0x03) (see section 5.4.12) */
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
  uint8_t order_id[4];                   /* bytes 49 to 52 */
  uint8_t secondary_exec_id[4];          /* bytes 53 to 56 */
  uint8_t order_qty[4];                  /* bytes 57 to 60 */
  uint8_t ord_status;                    /* byte 61 */
  uint8_t ord_rej_reason;                /* byte 62 */
  uint8_t exec_type;                     /* byte 63 */
  uint8_t request_id[4];                 /* bytes 64 to 67 */
  uint8_t client_data_id[2];             /* bytes 68 to 69 */
} SimpleOrderStatusMessage;

/* any Simple Order Status Message at all: every byte one the checker chooses */
static void any_simple_order_status_message(SimpleOrderStatusMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ord_rej_reason = arbitrary();
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Simple Order Status Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_status_message(const SimpleOrderStatusMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ord_rej_reason;
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Simple Order Status Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_status_message(SimpleOrderStatusMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ord_rej_reason = wire[at++];
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Status Message is what was written, byte for byte */
static void equal_simple_order_status_message(const SimpleOrderStatusMessage *read, const SimpleOrderStatusMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ord_rej_reason == written->ord_rej_reason);
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Simple Order Status Message: written and read back, then read and written back */
static void check_simple_order_status_message(void) {
  SimpleOrderStatusMessage sent;
  SimpleOrderStatusMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_simple_order_status_message(&sent);
  assert(encode_simple_order_status_message(&sent, wire, 0) == 70);
  assert(decode_simple_order_status_message(&got, wire, 0) == 70);
  equal_simple_order_status_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_status_message(&got, wire, 0) == 70);
  assert(encode_simple_order_status_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Status Message: 108 bytes ----------------------------------------- */

/* Sent by the server to inform about the status of a Quote */
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
  uint8_t order_id[4];                   /* bytes 72 to 75 */
  uint8_t secondary_exec_id[4];          /* bytes 76 to 79 */
  uint8_t order_qty[4];                  /* bytes 80 to 83 */
  uint8_t ord_status;                    /* byte 84 */
  uint8_t ord_rej_reason;                /* byte 85 */
  uint8_t exec_type;                     /* byte 86 */
  uint8_t order_id_2[4];                 /* bytes 87 to 90 */
  uint8_t secondary_exec_id_2[4];        /* bytes 91 to 94 */
  uint8_t order_qty_2[4];                /* bytes 95 to 98 */
  uint8_t ord_status_2;                  /* byte 99 */
  uint8_t ord_rej_reason_2;              /* byte 100 */
  uint8_t exec_type_2;                   /* byte 101 */
  uint8_t request_id[4];                 /* bytes 102 to 105 */
  uint8_t client_data_id[2];             /* bytes 106 to 107 */
} QuoteStatusMessage;

/* any Quote Status Message at all: every byte one the checker chooses */
static void any_quote_status_message(QuoteStatusMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ord_rej_reason = arbitrary();
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ord_rej_reason_2 = arbitrary();
  record->exec_type_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Quote Status Message to the wire: 108 bytes from at, returning where the next byte goes */
static size_t encode_quote_status_message(const QuoteStatusMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ord_rej_reason;
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ord_rej_reason_2;
  wire[at++] = record->exec_type_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Quote Status Message off the wire: 108 bytes from at, returning where the next byte lies */
static size_t decode_quote_status_message(QuoteStatusMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ord_rej_reason = wire[at++];
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ord_rej_reason_2 = wire[at++];
  record->exec_type_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Status Message is what was written, byte for byte */
static void equal_quote_status_message(const QuoteStatusMessage *read, const QuoteStatusMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ord_rej_reason == written->ord_rej_reason);
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ord_rej_reason_2 == written->ord_rej_reason_2);
  assert(read->exec_type_2 == written->exec_type_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Quote Status Message: written and read back, then read and written back */
static void check_quote_status_message(void) {
  QuoteStatusMessage sent;
  QuoteStatusMessage got;
  uint8_t wire[108];
  uint8_t again[108];

  any_quote_status_message(&sent);
  assert(encode_quote_status_message(&sent, wire, 0) == 108);
  assert(decode_quote_status_message(&got, wire, 0) == 108);
  equal_quote_status_message(&got, &sent);

  for (size_t i = 0; i < 108; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_status_message(&got, wire, 0) == 108);
  assert(encode_quote_status_message(&got, again, 0) == 108);
  for (size_t i = 0; i < 108; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject Message: 23 bytes ----------------------------------- */

/* Sent by the server to inform about the rejection of a Simple order modification (MsgType = 0x47) or an Order cancellation request (MsgType = 0x46) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t order_id[4];                   /* bytes 12 to 15 */
  uint8_t ord_status;                    /* byte 16 */
  uint8_t cxl_rej_response_to;           /* byte 17 */
  uint8_t cxl_rej_reason;                /* byte 18 */
  uint8_t request_id[4];                 /* bytes 19 to 22 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->cxl_rej_response_to = arbitrary();
  record->cxl_rej_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Order Cancel Reject Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->cxl_rej_response_to;
  wire[at++] = record->cxl_rej_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Order Cancel Reject Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->cxl_rej_response_to = wire[at++];
  record->cxl_rej_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->cxl_rej_response_to == written->cxl_rej_response_to);
  assert(read->cxl_rej_reason == written->cxl_rej_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 23);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 23);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 23);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Completion Message: 19 bytes --------------- */

/* Message reporting the completion of a valid mass order cancellation request. More than one message may be sent for a single RequestID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t trading_unit;                  /* byte 12 */
  uint8_t cancellation_type;             /* byte 13 */
  uint8_t order_or_quote_cancel;         /* byte 14 */
  uint8_t request_id[4];                 /* bytes 15 to 18 */
} MassOrderquoteCancellationCompletionMessage;

/* any Mass Orderquote Cancellation Completion Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_completion_message(MassOrderquoteCancellationCompletionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->trading_unit = arbitrary();
  record->cancellation_type = arbitrary();
  record->order_or_quote_cancel = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Mass Orderquote Cancellation Completion Message to the wire: 19 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_completion_message(const MassOrderquoteCancellationCompletionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->trading_unit;
  wire[at++] = record->cancellation_type;
  wire[at++] = record->order_or_quote_cancel;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Mass Orderquote Cancellation Completion Message off the wire: 19 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_completion_message(MassOrderquoteCancellationCompletionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->trading_unit = wire[at++];
  record->cancellation_type = wire[at++];
  record->order_or_quote_cancel = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Orderquote Cancellation Completion Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_completion_message(const MassOrderquoteCancellationCompletionMessage *read, const MassOrderquoteCancellationCompletionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->trading_unit == written->trading_unit);
  assert(read->cancellation_type == written->cancellation_type);
  assert(read->order_or_quote_cancel == written->order_or_quote_cancel);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Mass Orderquote Cancellation Completion Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_completion_message(void) {
  MassOrderquoteCancellationCompletionMessage sent;
  MassOrderquoteCancellationCompletionMessage got;
  uint8_t wire[19];
  uint8_t again[19];

  any_mass_orderquote_cancellation_completion_message(&sent);
  assert(encode_mass_orderquote_cancellation_completion_message(&sent, wire, 0) == 19);
  assert(decode_mass_orderquote_cancellation_completion_message(&got, wire, 0) == 19);
  equal_mass_orderquote_cancellation_completion_message(&got, &sent);

  for (size_t i = 0; i < 19; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_completion_message(&got, wire, 0) == 19);
  assert(encode_mass_orderquote_cancellation_completion_message(&got, again, 0) == 19);
  for (size_t i = 0; i < 19; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Reject Message: 14 bytes ------------------- */

/* Message reporting the rejection of a mass order cancellation request. More than one message may be sent for a single RequestID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t trading_unit;                  /* byte 12 */
  uint8_t mass_cancel_reject_reason;     /* byte 13 */
} MassOrderquoteCancellationRejectMessage;

/* any Mass Orderquote Cancellation Reject Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_reject_message(MassOrderquoteCancellationRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->trading_unit = arbitrary();
  record->mass_cancel_reject_reason = arbitrary();
}

/* Mass Orderquote Cancellation Reject Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_reject_message(const MassOrderquoteCancellationRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->trading_unit;
  wire[at++] = record->mass_cancel_reject_reason;

  return at;
}

/* Mass Orderquote Cancellation Reject Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_reject_message(MassOrderquoteCancellationRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->trading_unit = wire[at++];
  record->mass_cancel_reject_reason = wire[at++];

  return at;
}

/* what was read of Mass Orderquote Cancellation Reject Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_reject_message(const MassOrderquoteCancellationRejectMessage *read, const MassOrderquoteCancellationRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->trading_unit == written->trading_unit);
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
}

/* Mass Orderquote Cancellation Reject Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_reject_message(void) {
  MassOrderquoteCancellationRejectMessage sent;
  MassOrderquoteCancellationRejectMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_mass_orderquote_cancellation_reject_message(&sent);
  assert(encode_mass_orderquote_cancellation_reject_message(&sent, wire, 0) == 14);
  assert(decode_mass_orderquote_cancellation_reject_message(&got, wire, 0) == 14);
  equal_mass_orderquote_cancellation_reject_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_reject_message(&got, wire, 0) == 14);
  assert(encode_mass_orderquote_cancellation_reject_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Message Reject Message: 83 bytes ------------------------------- */

/* It may be sent by the server to inform about the rejection of a supported message that is syntactically correct in an unsupported situation */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t ref_msg_type;                  /* byte 12 */
  uint8_t business_reject_reason;        /* byte 13 */
  uint8_t text_c_65[65];                 /* bytes 14 to 78 */
  uint8_t request_id[4];                 /* bytes 79 to 82 */
} BusinessMessageRejectMessage;

/* any Business Message Reject Message at all: every byte one the checker chooses */
static void any_business_message_reject_message(BusinessMessageRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->ref_msg_type = arbitrary();
  record->business_reject_reason = arbitrary();
  for (size_t i = 0; i < 65; i++) { record->text_c_65[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Business Message Reject Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_business_message_reject_message(const BusinessMessageRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->ref_msg_type;
  wire[at++] = record->business_reject_reason;
  for (size_t i = 0; i < 65; i++) { wire[at++] = record->text_c_65[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Business Message Reject Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_business_message_reject_message(BusinessMessageRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->ref_msg_type = wire[at++];
  record->business_reject_reason = wire[at++];
  for (size_t i = 0; i < 65; i++) { record->text_c_65[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Business Message Reject Message is what was written, byte for byte */
static void equal_business_message_reject_message(const BusinessMessageRejectMessage *read, const BusinessMessageRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->ref_msg_type == written->ref_msg_type);
  assert(read->business_reject_reason == written->business_reject_reason);
  for (size_t i = 0; i < 65; i++) { assert(read->text_c_65[i] == written->text_c_65[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Business Message Reject Message: written and read back, then read and written back */
static void check_business_message_reject_message(void) {
  BusinessMessageRejectMessage sent;
  BusinessMessageRejectMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_business_message_reject_message(&sent);
  assert(encode_business_message_reject_message(&sent, wire, 0) == 83);
  assert(decode_business_message_reject_message(&got, wire, 0) == 83);
  equal_business_message_reject_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_business_message_reject_message(&got, wire, 0) == 83);
  assert(encode_business_message_reject_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 2 Legs Message: 184 bytes ----------------- */

/* Sent by the server to inform about a trade where two orders of the user are involved both as Buyer and Seller */
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
  uint8_t order_id[4];                   /* bytes 110 to 113 */
  uint8_t secondary_exec_id[4];          /* bytes 114 to 117 */
  uint8_t order_qty[4];                  /* bytes 118 to 121 */
  uint8_t ord_status;                    /* byte 122 */
  uint8_t ccp_code;                      /* byte 123 */
  uint8_t aggressor_indicator;           /* byte 124 */
  uint8_t request_id[4];                 /* bytes 125 to 128 */
  uint8_t client_data_id[2];             /* bytes 129 to 130 */
  uint8_t secondary_order_id_2[4];       /* bytes 131 to 134 */
  uint8_t entry_date_2[4];               /* bytes 135 to 138 */
  uint8_t priority_2[4];                 /* bytes 139 to 142 */
  uint8_t price_2[8];                    /* bytes 143 to 150 */
  uint8_t display_qty_2[4];              /* bytes 151 to 154 */
  uint8_t alt_price_2[8];                /* bytes 155 to 162 */
  uint8_t order_id_2[4];                 /* bytes 163 to 166 */
  uint8_t secondary_exec_id_2[4];        /* bytes 167 to 170 */
  uint8_t order_qty_2[4];                /* bytes 171 to 174 */
  uint8_t ord_status_2;                  /* byte 175 */
  uint8_t ccp_code_2;                    /* byte 176 */
  uint8_t aggressor_indicator_2;         /* byte 177 */
  uint8_t request_id_2[4];               /* bytes 178 to 181 */
  uint8_t client_data_id_2[2];           /* bytes 182 to 183 */
} ExecutionPrivateInformation2LegsMessage;

/* any Execution Private Information 2 Legs Message at all: every byte one the checker chooses */
static void any_execution_private_information2_legs_message(ExecutionPrivateInformation2LegsMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ccp_code_2 = arbitrary();
  record->aggressor_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = arbitrary(); }
}

/* Execution Private Information 2 Legs Message to the wire: 184 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information2_legs_message(const ExecutionPrivateInformation2LegsMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ccp_code_2;
  wire[at++] = record->aggressor_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id_2[i]; }

  return at;
}

/* Execution Private Information 2 Legs Message off the wire: 184 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information2_legs_message(ExecutionPrivateInformation2LegsMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ccp_code_2 = wire[at++];
  record->aggressor_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 2 Legs Message is what was written, byte for byte */
static void equal_execution_private_information2_legs_message(const ExecutionPrivateInformation2LegsMessage *read, const ExecutionPrivateInformation2LegsMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price_2[i] == written->alt_price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ccp_code_2 == written->ccp_code_2);
  assert(read->aggressor_indicator_2 == written->aggressor_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id_2[i] == written->request_id_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id_2[i] == written->client_data_id_2[i]); }
}

/* Execution Private Information 2 Legs Message: written and read back, then read and written back */
static void check_execution_private_information2_legs_message(void) {
  ExecutionPrivateInformation2LegsMessage sent;
  ExecutionPrivateInformation2LegsMessage got;
  uint8_t wire[184];
  uint8_t again[184];

  any_execution_private_information2_legs_message(&sent);
  assert(encode_execution_private_information2_legs_message(&sent, wire, 0) == 184);
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 184);
  equal_execution_private_information2_legs_message(&got, &sent);

  for (size_t i = 0; i < 184; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 184);
  assert(encode_execution_private_information2_legs_message(&got, again, 0) == 184);
  for (size_t i = 0; i < 184; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: 255 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Buyer. It is also sent to inform about the amendment or cancellation of whatever origin trade where the user is involved as Buyer. Shares the same layout as the next message */
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
  uint8_t broker_trader[3];                /* bytes 125 to 127 */
  uint8_t broker_text[15];                 /* bytes 128 to 142 */
  uint8_t secondary_order_id[4];           /* bytes 143 to 146 */
  uint8_t entry_date[4];                   /* bytes 147 to 150 */
  uint8_t priority[4];                     /* bytes 151 to 154 */
  uint8_t price[8];                        /* bytes 155 to 162 */
  uint8_t display_qty[4];                  /* bytes 163 to 166 */
  uint8_t alt_price[8];                    /* bytes 167 to 174 */
  uint8_t order_id[4];                     /* bytes 175 to 178 */
  uint8_t secondary_exec_id[4];            /* bytes 179 to 182 */
  uint8_t order_qty[4];                    /* bytes 183 to 186 */
  uint8_t ord_status;                      /* byte 187 */
  uint8_t ccp_code;                        /* byte 188 */
  uint8_t aggressor_indicator;             /* byte 189 */
  uint8_t request_id[4];                   /* bytes 190 to 193 */
  uint8_t client_data_id[2];               /* bytes 194 to 195 */
  uint8_t algorithmic_trade_indicator;     /* byte 196 */
  uint8_t client_id[4];                    /* bytes 197 to 200 */
  uint8_t account_bolsa[16];               /* bytes 201 to 216 */
  uint8_t account[5];                      /* bytes 217 to 221 */
  uint8_t dea_flag;                        /* byte 222 */
  uint8_t decisor_id[4];                   /* bytes 223 to 226 */
  uint8_t executor_id[4];                  /* bytes 227 to 230 */
  uint8_t liquidity_provision_activity;    /* byte 231 */
  uint8_t account_member[4];               /* bytes 232 to 235 */
  uint8_t last_capacity;                   /* byte 236 */
  uint8_t received_dept_id;                /* byte 237 */
  uint8_t persistence;                     /* byte 238 */
  uint8_t member[4];                       /* bytes 239 to 242 */
  uint8_t trader[3];                       /* bytes 243 to 245 */
  uint8_t sub_member;                      /* byte 246 */
  uint8_t cross_id[4];                     /* bytes 247 to 250 */
  uint8_t order_security_code[4];          /* bytes 251 to 254 */
} TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1;

/* any Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message to the wire: 255 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message off the wire: 255 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *read, const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *written) {
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
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(void) {
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 sent;
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 got;
  uint8_t wire[255];
  uint8_t again[255];

  any_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent, wire, 0) == 255);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 255);
  equal_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 255);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: 255 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Seller */
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
  uint8_t broker_trader[3];                /* bytes 125 to 127 */
  uint8_t broker_text[15];                 /* bytes 128 to 142 */
  uint8_t secondary_order_id[4];           /* bytes 143 to 146 */
  uint8_t entry_date[4];                   /* bytes 147 to 150 */
  uint8_t priority[4];                     /* bytes 151 to 154 */
  uint8_t price[8];                        /* bytes 155 to 162 */
  uint8_t display_qty[4];                  /* bytes 163 to 166 */
  uint8_t alt_price[8];                    /* bytes 167 to 174 */
  uint8_t order_id[4];                     /* bytes 175 to 178 */
  uint8_t secondary_exec_id[4];            /* bytes 179 to 182 */
  uint8_t order_qty[4];                    /* bytes 183 to 186 */
  uint8_t ord_status;                      /* byte 187 */
  uint8_t ccp_code;                        /* byte 188 */
  uint8_t aggressor_indicator;             /* byte 189 */
  uint8_t request_id[4];                   /* bytes 190 to 193 */
  uint8_t client_data_id[2];               /* bytes 194 to 195 */
  uint8_t algorithmic_trade_indicator;     /* byte 196 */
  uint8_t client_id[4];                    /* bytes 197 to 200 */
  uint8_t account_bolsa[16];               /* bytes 201 to 216 */
  uint8_t account[5];                      /* bytes 217 to 221 */
  uint8_t dea_flag;                        /* byte 222 */
  uint8_t decisor_id[4];                   /* bytes 223 to 226 */
  uint8_t executor_id[4];                  /* bytes 227 to 230 */
  uint8_t liquidity_provision_activity;    /* byte 231 */
  uint8_t account_member[4];               /* bytes 232 to 235 */
  uint8_t last_capacity;                   /* byte 236 */
  uint8_t received_dept_id;                /* byte 237 */
  uint8_t persistence;                     /* byte 238 */
  uint8_t member[4];                       /* bytes 239 to 242 */
  uint8_t trader[3];                       /* bytes 243 to 245 */
  uint8_t sub_member;                      /* byte 246 */
  uint8_t cross_id[4];                     /* bytes 247 to 250 */
  uint8_t order_security_code[4];          /* bytes 251 to 254 */
} TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv;

/* any Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message to the wire: 255 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message off the wire: 255 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *read, const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *written) {
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
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(void) {
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv sent;
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv got;
  uint8_t wire[255];
  uint8_t again[255];

  any_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent, wire, 0) == 255);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 255);
  equal_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 255);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: 367 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade both as Buyer and Seller */
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
  uint8_t broker_trader[3];                /* bytes 125 to 127 */
  uint8_t broker_text[15];                 /* bytes 128 to 142 */
  uint8_t secondary_order_id[4];           /* bytes 143 to 146 */
  uint8_t entry_date[4];                   /* bytes 147 to 150 */
  uint8_t priority[4];                     /* bytes 151 to 154 */
  uint8_t price[8];                        /* bytes 155 to 162 */
  uint8_t display_qty[4];                  /* bytes 163 to 166 */
  uint8_t alt_price[8];                    /* bytes 167 to 174 */
  uint8_t order_id[4];                     /* bytes 175 to 178 */
  uint8_t secondary_exec_id[4];            /* bytes 179 to 182 */
  uint8_t order_qty[4];                    /* bytes 183 to 186 */
  uint8_t ord_status;                      /* byte 187 */
  uint8_t ccp_code;                        /* byte 188 */
  uint8_t aggressor_indicator;             /* byte 189 */
  uint8_t request_id[4];                   /* bytes 190 to 193 */
  uint8_t client_data_id[2];               /* bytes 194 to 195 */
  uint8_t algorithmic_trade_indicator;     /* byte 196 */
  uint8_t client_id[4];                    /* bytes 197 to 200 */
  uint8_t account_bolsa[16];               /* bytes 201 to 216 */
  uint8_t account[5];                      /* bytes 217 to 221 */
  uint8_t dea_flag;                        /* byte 222 */
  uint8_t decisor_id[4];                   /* bytes 223 to 226 */
  uint8_t executor_id[4];                  /* bytes 227 to 230 */
  uint8_t liquidity_provision_activity;    /* byte 231 */
  uint8_t account_member[4];               /* bytes 232 to 235 */
  uint8_t last_capacity;                   /* byte 236 */
  uint8_t received_dept_id;                /* byte 237 */
  uint8_t persistence;                     /* byte 238 */
  uint8_t member[4];                       /* bytes 239 to 242 */
  uint8_t trader[3];                       /* bytes 243 to 245 */
  uint8_t sub_member;                      /* byte 246 */
  uint8_t cross_id[4];                     /* bytes 247 to 250 */
  uint8_t order_security_code[4];          /* bytes 251 to 254 */
  uint8_t secondary_order_id_2[4];         /* bytes 255 to 258 */
  uint8_t entry_date_2[4];                 /* bytes 259 to 262 */
  uint8_t priority_2[4];                   /* bytes 263 to 266 */
  uint8_t price_2[8];                      /* bytes 267 to 274 */
  uint8_t display_qty_2[4];                /* bytes 275 to 278 */
  uint8_t alt_price_2[8];                  /* bytes 279 to 286 */
  uint8_t order_id_2[4];                   /* bytes 287 to 290 */
  uint8_t secondary_exec_id_2[4];          /* bytes 291 to 294 */
  uint8_t order_qty_2[4];                  /* bytes 295 to 298 */
  uint8_t ord_status_2;                    /* byte 299 */
  uint8_t ccp_code_2;                      /* byte 300 */
  uint8_t aggressor_indicator_2;           /* byte 301 */
  uint8_t request_id_2[4];                 /* bytes 302 to 305 */
  uint8_t client_data_id_2[2];             /* bytes 306 to 307 */
  uint8_t algorithmic_trade_indicator_2;   /* byte 308 */
  uint8_t client_id_2[4];                  /* bytes 309 to 312 */
  uint8_t account_bolsa_2[16];             /* bytes 313 to 328 */
  uint8_t account_2[5];                    /* bytes 329 to 333 */
  uint8_t dea_flag_2;                      /* byte 334 */
  uint8_t decisor_id_2[4];                 /* bytes 335 to 338 */
  uint8_t executor_id_2[4];                /* bytes 339 to 342 */
  uint8_t liquidity_provision_activity_2;  /* byte 343 */
  uint8_t account_member_2[4];             /* bytes 344 to 347 */
  uint8_t last_capacity_2;                 /* byte 348 */
  uint8_t received_dept_id_2;              /* byte 349 */
  uint8_t persistence_2;                   /* byte 350 */
  uint8_t member_2[4];                     /* bytes 351 to 354 */
  uint8_t trader_2[3];                     /* bytes 355 to 357 */
  uint8_t sub_member_2;                    /* byte 358 */
  uint8_t cross_id_2[4];                   /* bytes 359 to 362 */
  uint8_t order_security_code_2[4];        /* bytes 363 to 366 */
} TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage;

/* any Trade Trade Amendment Or Cancellation 2 Legs Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation2_legs_private_information_message(TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ccp_code_2 = arbitrary();
  record->aggressor_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = arbitrary(); }
  record->algorithmic_trade_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account_2[i] = arbitrary(); }
  record->dea_flag_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id_2[i] = arbitrary(); }
  record->liquidity_provision_activity_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->account_member_2[i] = arbitrary(); }
  record->last_capacity_2 = arbitrary();
  record->received_dept_id_2 = arbitrary();
  record->persistence_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = arbitrary(); }
  record->sub_member_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message to the wire: 367 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member[i]; }
  wire[at++] = record->last_capacity;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->alt_price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ccp_code_2;
  wire[at++] = record->aggressor_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id_2[i]; }
  wire[at++] = record->algorithmic_trade_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id_2[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account_2[i]; }
  wire[at++] = record->dea_flag_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id_2[i]; }
  wire[at++] = record->liquidity_provision_activity_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->account_member_2[i]; }
  wire[at++] = record->last_capacity_2;
  wire[at++] = record->received_dept_id_2;
  wire[at++] = record->persistence_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_2[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader_2[i]; }
  wire[at++] = record->sub_member_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code_2[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message off the wire: 367 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->alt_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ccp_code_2 = wire[at++];
  record->aggressor_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = wire[at++]; }
  record->algorithmic_trade_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account_2[i] = wire[at++]; }
  record->dea_flag_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id_2[i] = wire[at++]; }
  record->liquidity_provision_activity_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->account_member_2[i] = wire[at++]; }
  record->last_capacity_2 = wire[at++];
  record->received_dept_id_2 = wire[at++];
  record->persistence_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = wire[at++]; }
  record->sub_member_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 2 Legs Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation2_legs_private_information_message(const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *read, const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *written) {
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
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price[i] == written->alt_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member[i] == written->account_member[i]); }
  assert(read->last_capacity == written->last_capacity);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->alt_price_2[i] == written->alt_price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ccp_code_2 == written->ccp_code_2);
  assert(read->aggressor_indicator_2 == written->aggressor_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id_2[i] == written->request_id_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id_2[i] == written->client_data_id_2[i]); }
  assert(read->algorithmic_trade_indicator_2 == written->algorithmic_trade_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id_2[i] == written->client_id_2[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa_2[i] == written->account_bolsa_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account_2[i] == written->account_2[i]); }
  assert(read->dea_flag_2 == written->dea_flag_2);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id_2[i] == written->decisor_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id_2[i] == written->executor_id_2[i]); }
  assert(read->liquidity_provision_activity_2 == written->liquidity_provision_activity_2);
  for (size_t i = 0; i < 4; i++) { assert(read->account_member_2[i] == written->account_member_2[i]); }
  assert(read->last_capacity_2 == written->last_capacity_2);
  assert(read->received_dept_id_2 == written->received_dept_id_2);
  assert(read->persistence_2 == written->persistence_2);
  for (size_t i = 0; i < 4; i++) { assert(read->member_2[i] == written->member_2[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader_2[i] == written->trader_2[i]); }
  assert(read->sub_member_2 == written->sub_member_2);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id_2[i] == written->cross_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code_2[i] == written->order_security_code_2[i]); }
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation2_legs_private_information_message(void) {
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage sent;
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage got;
  uint8_t wire[367];
  uint8_t again[367];

  any_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent, wire, 0) == 367);
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 367);
  equal_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, &sent);

  for (size_t i = 0; i < 367; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 367);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, again, 0) == 367);
  for (size_t i = 0; i < 367; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Buy Order Entry Message: 131 bytes ---- */

/* Sent by the server to inform about a trade where the user is involved as Buyer. Shares the same layout as the next message */
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
  uint8_t order_id[4];                   /* bytes 110 to 113 */
  uint8_t secondary_exec_id[4];          /* bytes 114 to 117 */
  uint8_t order_qty[4];                  /* bytes 118 to 121 */
  uint8_t ord_status;                    /* byte 122 */
  uint8_t ccp_code;                      /* byte 123 */
  uint8_t aggressor_indicator;           /* byte 124 */
  uint8_t request_id[4];                 /* bytes 125 to 128 */
  uint8_t client_data_id[2];             /* bytes 129 to 130 */
} ExecutionPrivateInformation1LegBuyOrderEntryMessage;

/* any Execution Private Information 1 Leg Buy Order Entry Message at all: every byte one the checker chooses */
static void any_execution_private_information1_leg_buy_order_entry_message(ExecutionPrivateInformation1LegBuyOrderEntryMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Execution Private Information 1 Leg Buy Order Entry Message to the wire: 131 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information1_leg_buy_order_entry_message(const ExecutionPrivateInformation1LegBuyOrderEntryMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Execution Private Information 1 Leg Buy Order Entry Message off the wire: 131 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information1_leg_buy_order_entry_message(ExecutionPrivateInformation1LegBuyOrderEntryMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 1 Leg Buy Order Entry Message is what was written, byte for byte */
static void equal_execution_private_information1_leg_buy_order_entry_message(const ExecutionPrivateInformation1LegBuyOrderEntryMessage *read, const ExecutionPrivateInformation1LegBuyOrderEntryMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Execution Private Information 1 Leg Buy Order Entry Message: written and read back, then read and written back */
static void check_execution_private_information1_leg_buy_order_entry_message(void) {
  ExecutionPrivateInformation1LegBuyOrderEntryMessage sent;
  ExecutionPrivateInformation1LegBuyOrderEntryMessage got;
  uint8_t wire[131];
  uint8_t again[131];

  any_execution_private_information1_leg_buy_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&sent, wire, 0) == 131);
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 131);
  equal_execution_private_information1_leg_buy_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 131; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 131);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&got, again, 0) == 131);
  for (size_t i = 0; i < 131; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Sell Order Entry Message: 131 bytes ---- */

/* Sent by the server to inform about a trade where the user is involved as Seller */
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
  uint8_t order_id[4];                   /* bytes 110 to 113 */
  uint8_t secondary_exec_id[4];          /* bytes 114 to 117 */
  uint8_t order_qty[4];                  /* bytes 118 to 121 */
  uint8_t ord_status;                    /* byte 122 */
  uint8_t ccp_code;                      /* byte 123 */
  uint8_t aggressor_indicator;           /* byte 124 */
  uint8_t request_id[4];                 /* bytes 125 to 128 */
  uint8_t client_data_id[2];             /* bytes 129 to 130 */
} ExecutionPrivateInformation1LegSellOrderEntryMessage;

/* any Execution Private Information 1 Leg Sell Order Entry Message at all: every byte one the checker chooses */
static void any_execution_private_information1_leg_sell_order_entry_message(ExecutionPrivateInformation1LegSellOrderEntryMessage *record) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Execution Private Information 1 Leg Sell Order Entry Message to the wire: 131 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information1_leg_sell_order_entry_message(const ExecutionPrivateInformation1LegSellOrderEntryMessage *record, uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Execution Private Information 1 Leg Sell Order Entry Message off the wire: 131 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information1_leg_sell_order_entry_message(ExecutionPrivateInformation1LegSellOrderEntryMessage *record, const uint8_t *wire, size_t at) {
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
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 1 Leg Sell Order Entry Message is what was written, byte for byte */
static void equal_execution_private_information1_leg_sell_order_entry_message(const ExecutionPrivateInformation1LegSellOrderEntryMessage *read, const ExecutionPrivateInformation1LegSellOrderEntryMessage *written) {
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
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Execution Private Information 1 Leg Sell Order Entry Message: written and read back, then read and written back */
static void check_execution_private_information1_leg_sell_order_entry_message(void) {
  ExecutionPrivateInformation1LegSellOrderEntryMessage sent;
  ExecutionPrivateInformation1LegSellOrderEntryMessage got;
  uint8_t wire[131];
  uint8_t again[131];

  any_execution_private_information1_leg_sell_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&sent, wire, 0) == 131);
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 131);
  equal_execution_private_information1_leg_sell_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 131; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 131);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&got, again, 0) == 131);
  for (size_t i = 0; i < 131; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_response_message();
  check_logout_response_message();
  check_heartbeat_message();
  check_network_status_message();
  check_logon_message();
  check_reject_message();
  check_trading_session_status_message();
  check_news_message();
  check_security_list_cancellation_report_message();
  check_security_list_message();
  check_security_list_update_report_message();
  check_security_status_message();
  check_order_cancellation_market_member_message();
  check_quote_cancellation_market_member_message();
  check_indication_of_interest_message();
  check_order_and_quote_client_data_message();
  check_simple_new_order_message();
  check_simple_new_order_with_client_data_message();
  check_simple_order_modification_message();
  check_simple_order_modification_with_client_data_message();
  check_order_cancellation_request_message();
  check_new_quote_message();
  check_quote_modification_request_message();
  check_quote_cancellation_request_message();
  check_mass_orderquote_cancellation_message();
  check_order_and_quote_client_data_parameters_ack_nack_message();
  check_simple_order_status_message();
  check_quote_status_message();
  check_order_cancel_reject_message();
  check_mass_orderquote_cancellation_completion_message();
  check_mass_orderquote_cancellation_reject_message();
  check_business_message_reject_message();
  check_execution_private_information2_legs_message();
  check_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1();
  check_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv();
  check_trade_trade_amendment_or_cancellation2_legs_private_information_message();
  check_execution_private_information1_leg_buy_order_entry_message();
  check_execution_private_information1_leg_sell_order_entry_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
