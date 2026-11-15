// jse/itac/basicnativetradingrecovery/Jse_Itac_BasicNativeTradingRecovery_v4_05.c
/*
 * JSE Limited Basic Native Trading Recovery
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

/* Jse Native Trading Gateway Message Header */
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

/* ---- Logon Message: 60 bytes ------------------------------------------------- */

/* Allows the client to login to the server. */
typedef struct {
  uint8_t comp_id[6];           /* bytes 0 to 5 */
  uint8_t password[25];         /* bytes 6 to 30 */
  uint8_t new_password[25];     /* bytes 31 to 55 */
  uint8_t protocol_version[4];  /* bytes 56 to 59 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->protocol_version[i] = arbitrary(); }
}

/* Logon Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->comp_id[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->new_password[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->protocol_version[i]; }

  return at;
}

/* Logon Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->new_password[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->protocol_version[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->comp_id[i] == written->comp_id[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->new_password[i] == written->new_password[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 60);
  assert(decode_logon_message(&got, wire, 0) == 60);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 60);
  assert(encode_logon_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 8 bytes ----------------------------------------- */

/* Used by the server to accept or reject a login request. */
typedef struct {
  uint8_t reject_code[4];      /* bytes 0 to 3 */
  uint8_t password_expiry[4];  /* bytes 4 to 7 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->password_expiry[i] = arbitrary(); }
}

/* Logon Response Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->password_expiry[i]; }

  return at;
}

/* Logon Response Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->password_expiry[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->password_expiry[i] == written->password_expiry[i]); }
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 8);
  assert(decode_logon_response_message(&got, wire, 0) == 8);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 8);
  assert(encode_logon_response_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 20 bytes ------------------------------------------------ */

/* Used by the client or server to terminate a session. */
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

/* ---- Reject Message: 55 bytes ------------------------------------------------ */

/* Used by the server to reject a message that does not comply with the specifications. */
typedef struct {
  uint8_t reject_code[4];       /* bytes 0 to 3 */
  uint8_t reject_reason[30];    /* bytes 4 to 33 */
  uint8_t message_type;         /* byte 34 */
  uint8_t client_order_id[20];  /* bytes 35 to 54 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->reject_reason[i] = arbitrary(); }
  record->message_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
}

/* Reject Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->reject_reason[i]; }
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }

  return at;
}

/* Reject Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->reject_reason[i] = wire[at++]; }
  record->message_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->reject_reason[i] == written->reject_reason[i]); }
  assert(read->message_type == written->message_type);
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

/* ---- Missed Message Request Message: 5 bytes --------------------------------- */

/* Used by the client to recover missed messages through the Recovery Channel. */
typedef struct {
  uint8_t partition_id;        /* byte 0 */
  uint8_t sequence_number[4];  /* bytes 1 to 4 */
} MissedMessageRequestMessage;

/* any Missed Message Request Message at all: every byte one the checker chooses */
static void any_missed_message_request_message(MissedMessageRequestMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Missed Message Request Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_missed_message_request_message(const MissedMessageRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Missed Message Request Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_missed_message_request_message(MissedMessageRequestMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Missed Message Request Message is what was written, byte for byte */
static void equal_missed_message_request_message(const MissedMessageRequestMessage *read, const MissedMessageRequestMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
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

/* Used by the server to accept or reject a request for missed messages. */
typedef struct {
  uint8_t missed_message_status;  /* byte 0 */
} MissedMessageRequestAckMessage;

/* any Missed Message Request Ack Message at all: every byte one the checker chooses */
static void any_missed_message_request_ack_message(MissedMessageRequestAckMessage *record) {
  record->missed_message_status = arbitrary();
}

/* Missed Message Request Ack Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_missed_message_request_ack_message(const MissedMessageRequestAckMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->missed_message_status;

  return at;
}

/* Missed Message Request Ack Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_missed_message_request_ack_message(MissedMessageRequestAckMessage *record, const uint8_t *wire, size_t at) {
  record->missed_message_status = wire[at++];

  return at;
}

/* what was read of Missed Message Request Ack Message is what was written, byte for byte */
static void equal_missed_message_request_ack_message(const MissedMessageRequestAckMessage *read, const MissedMessageRequestAckMessage *written) {
  assert(read->missed_message_status == written->missed_message_status);
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

/* ---- Transmission Complete Message: 1 byte ----------------------------------- */

/* Used by the server to indicate that the transmission of missed messages is complete. */
typedef struct {
  uint8_t transmission_status;  /* byte 0 */
} TransmissionCompleteMessage;

/* any Transmission Complete Message at all: every byte one the checker chooses */
static void any_transmission_complete_message(TransmissionCompleteMessage *record) {
  record->transmission_status = arbitrary();
}

/* Transmission Complete Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_transmission_complete_message(const TransmissionCompleteMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->transmission_status;

  return at;
}

/* Transmission Complete Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_transmission_complete_message(TransmissionCompleteMessage *record, const uint8_t *wire, size_t at) {
  record->transmission_status = wire[at++];

  return at;
}

/* what was read of Transmission Complete Message is what was written, byte for byte */
static void equal_transmission_complete_message(const TransmissionCompleteMessage *read, const TransmissionCompleteMessage *written) {
  assert(read->transmission_status == written->transmission_status);
}

/* Transmission Complete Message: written and read back, then read and written back */
static void check_transmission_complete_message(void) {
  TransmissionCompleteMessage sent;
  TransmissionCompleteMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_transmission_complete_message(&sent);
  assert(encode_transmission_complete_message(&sent, wire, 0) == 1);
  assert(decode_transmission_complete_message(&got, wire, 0) == 1);
  equal_transmission_complete_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_transmission_complete_message(&got, wire, 0) == 1);
  assert(encode_transmission_complete_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Status Message: 2 bytes ------------------------------------------ */

/* Disseminated in the recovery channel to indicate the status of a partition. */
typedef struct {
  uint8_t partition_id;   /* byte 0 */
  uint8_t system_status;  /* byte 1 */
} SystemStatusMessage;

/* any System Status Message at all: every byte one the checker chooses */
static void any_system_status_message(SystemStatusMessage *record) {
  record->partition_id = arbitrary();
  record->system_status = arbitrary();
}

/* System Status Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_system_status_message(const SystemStatusMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  wire[at++] = record->system_status;

  return at;
}

/* System Status Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_system_status_message(SystemStatusMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  record->system_status = wire[at++];

  return at;
}

/* what was read of System Status Message is what was written, byte for byte */
static void equal_system_status_message(const SystemStatusMessage *read, const SystemStatusMessage *written) {
  assert(read->partition_id == written->partition_id);
  assert(read->system_status == written->system_status);
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

/* Time the Execution Report was generated */
typedef struct {
  uint8_t transact_time_seconds[4];      /* bytes 0 to 3 */
  uint8_t transact_time_nanoseconds[4];  /* bytes 4 to 7 */
} TransactTime;

/* any Transact Time at all: every byte one the checker chooses */
static void any_transact_time(TransactTime *record) {
  for (size_t i = 0; i < 4; i++) { record->transact_time_seconds[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->transact_time_nanoseconds[i] = arbitrary(); }
}

/* Transact Time to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_transact_time(const TransactTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transact_time_seconds[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->transact_time_nanoseconds[i]; }

  return at;
}

/* Transact Time off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_transact_time(TransactTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->transact_time_seconds[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->transact_time_nanoseconds[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time is what was written, byte for byte */
static void equal_transact_time(const TransactTime *read, const TransactTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->transact_time_seconds[i] == written->transact_time_seconds[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->transact_time_nanoseconds[i] == written->transact_time_nanoseconds[i]); }
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

/* ---- Order Cancel Reject Message: 50 bytes ----------------------------------- */

/* Indicates that an order cancel or cancel replace request has been rejected. */
typedef struct {
  uint8_t partition_id;         /* byte 0 */
  uint8_t sequence_number[4];   /* bytes 1 to 4 */
  uint8_t client_order_id[20];  /* bytes 5 to 24 */
  uint8_t order_id[12];         /* bytes 25 to 36 */
  TransactTime transact_time;   /* bytes 37 to 44 */
  uint8_t reject_code[4];       /* bytes 45 to 48 */
  uint8_t order_book;           /* byte 49 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  record->order_book = arbitrary();
}

/* Order Cancel Reject Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  wire[at++] = record->order_book;

  return at;
}

/* Order Cancel Reject Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  record->order_book = wire[at++];

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  assert(read->order_book == written->order_book);
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 50);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 50);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 50);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel Report Message: 39 bytes ------------------------------ */

/* Indicates the outcome of an order mass cancel request. */
typedef struct {
  uint8_t partition_id;         /* byte 0 */
  uint8_t sequence_number[4];   /* bytes 1 to 4 */
  uint8_t client_order_id[20];  /* bytes 5 to 24 */
  uint8_t mass_cancel_status;   /* byte 25 */
  uint8_t reject_code[4];       /* bytes 26 to 29 */
  TransactTime transact_time;   /* bytes 30 to 37 */
  uint8_t order_book;           /* byte 38 */
} OrderMassCancelReportMessage;

/* any Order Mass Cancel Report Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_report_message(OrderMassCancelReportMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->mass_cancel_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
  record->order_book = arbitrary();
}

/* Order Mass Cancel Report Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_report_message(const OrderMassCancelReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->mass_cancel_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);
  wire[at++] = record->order_book;

  return at;
}

/* Order Mass Cancel Report Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_report_message(OrderMassCancelReportMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->mass_cancel_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);
  record->order_book = wire[at++];

  return at;
}

/* what was read of Order Mass Cancel Report Message is what was written, byte for byte */
static void equal_order_mass_cancel_report_message(const OrderMassCancelReportMessage *read, const OrderMassCancelReportMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->mass_cancel_status == written->mass_cancel_status);
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
  assert(read->order_book == written->order_book);
}

/* Order Mass Cancel Report Message: written and read back, then read and written back */
static void check_order_mass_cancel_report_message(void) {
  OrderMassCancelReportMessage sent;
  OrderMassCancelReportMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_order_mass_cancel_report_message(&sent);
  assert(encode_order_mass_cancel_report_message(&sent, wire, 0) == 39);
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 39);
  equal_order_mass_cancel_report_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 39);
  assert(encode_order_mass_cancel_report_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 1188 bytes ------------------------------------------------ */

/* Carries a market operations announcement. */
typedef struct {
  uint8_t partition_id;        /* byte 0 */
  uint8_t sequence_number[4];  /* bytes 1 to 4 */
  uint8_t orig_time[24];       /* bytes 5 to 28 */
  uint8_t urgency;             /* byte 29 */
  uint8_t headline[100];       /* bytes 30 to 129 */
  uint8_t text[750];           /* bytes 130 to 879 */
  uint8_t instruments[100];    /* bytes 880 to 979 */
  uint8_t underlyings[100];    /* bytes 980 to 1079 */
  uint8_t firm_list[54];       /* bytes 1080 to 1133 */
  uint8_t user_list[54];       /* bytes 1134 to 1187 */
} NewsMessage;

/* any News Message at all: every byte one the checker chooses */
static void any_news_message(NewsMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->orig_time[i] = arbitrary(); }
  record->urgency = arbitrary();
  for (size_t i = 0; i < 100; i++) { record->headline[i] = arbitrary(); }
  for (size_t i = 0; i < 750; i++) { record->text[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->underlyings[i] = arbitrary(); }
  for (size_t i = 0; i < 54; i++) { record->firm_list[i] = arbitrary(); }
  for (size_t i = 0; i < 54; i++) { record->user_list[i] = arbitrary(); }
}

/* News Message to the wire: 1188 bytes from at, returning where the next byte goes */
static size_t encode_news_message(const NewsMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->orig_time[i]; }
  wire[at++] = record->urgency;
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->headline[i]; }
  for (size_t i = 0; i < 750; i++) { wire[at++] = record->text[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->instruments[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->underlyings[i]; }
  for (size_t i = 0; i < 54; i++) { wire[at++] = record->firm_list[i]; }
  for (size_t i = 0; i < 54; i++) { wire[at++] = record->user_list[i]; }

  return at;
}

/* News Message off the wire: 1188 bytes from at, returning where the next byte lies */
static size_t decode_news_message(NewsMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->orig_time[i] = wire[at++]; }
  record->urgency = wire[at++];
  for (size_t i = 0; i < 100; i++) { record->headline[i] = wire[at++]; }
  for (size_t i = 0; i < 750; i++) { record->text[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->underlyings[i] = wire[at++]; }
  for (size_t i = 0; i < 54; i++) { record->firm_list[i] = wire[at++]; }
  for (size_t i = 0; i < 54; i++) { record->user_list[i] = wire[at++]; }

  return at;
}

/* what was read of News Message is what was written, byte for byte */
static void equal_news_message(const NewsMessage *read, const NewsMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->orig_time[i] == written->orig_time[i]); }
  assert(read->urgency == written->urgency);
  for (size_t i = 0; i < 100; i++) { assert(read->headline[i] == written->headline[i]); }
  for (size_t i = 0; i < 750; i++) { assert(read->text[i] == written->text[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->instruments[i] == written->instruments[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->underlyings[i] == written->underlyings[i]); }
  for (size_t i = 0; i < 54; i++) { assert(read->firm_list[i] == written->firm_list[i]); }
  for (size_t i = 0; i < 54; i++) { assert(read->user_list[i] == written->user_list[i]); }
}

/* News Message: written and read back, then read and written back */
static void check_news_message(void) {
  NewsMessage sent;
  NewsMessage got;
  uint8_t wire[1188];
  uint8_t again[1188];

  any_news_message(&sent);
  assert(encode_news_message(&sent, wire, 0) == 1188);
  assert(decode_news_message(&got, wire, 0) == 1188);
  equal_news_message(&got, &sent);

  for (size_t i = 0; i < 1188; i++) { wire[i] = arbitrary(); }
  assert(decode_news_message(&got, wire, 0) == 1188);
  assert(encode_news_message(&got, again, 0) == 1188);
  for (size_t i = 0; i < 1188; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Reject Message: 49 bytes --------------------------------------- */

/* Indicates that an application message could not be processed. */
typedef struct {
  uint8_t partition_id;         /* byte 0 */
  uint8_t sequence_number[4];   /* bytes 1 to 4 */
  uint8_t reject_code[4];       /* bytes 5 to 8 */
  uint8_t client_order_id[20];  /* bytes 9 to 28 */
  uint8_t order_id[12];         /* bytes 29 to 40 */
  TransactTime transact_time;   /* bytes 41 to 48 */
} BusinessRejectMessage;

/* any Business Reject Message at all: every byte one the checker chooses */
static void any_business_reject_message(BusinessRejectMessage *record) {
  record->partition_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = arbitrary(); }
  any_transact_time(&record->transact_time);
}

/* Business Reject Message to the wire: 49 bytes from at, returning where the next byte goes */
static size_t encode_business_reject_message(const BusinessRejectMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->partition_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reject_code[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->order_id[i]; }
  at = encode_transact_time(&record->transact_time, wire, at);

  return at;
}

/* Business Reject Message off the wire: 49 bytes from at, returning where the next byte lies */
static size_t decode_business_reject_message(BusinessRejectMessage *record, const uint8_t *wire, size_t at) {
  record->partition_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reject_code[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->order_id[i] = wire[at++]; }
  at = decode_transact_time(&record->transact_time, wire, at);

  return at;
}

/* what was read of Business Reject Message is what was written, byte for byte */
static void equal_business_reject_message(const BusinessRejectMessage *read, const BusinessRejectMessage *written) {
  assert(read->partition_id == written->partition_id);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reject_code[i] == written->reject_code[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->order_id[i] == written->order_id[i]); }
  equal_transact_time(&read->transact_time, &written->transact_time);
}

/* Business Reject Message: written and read back, then read and written back */
static void check_business_reject_message(void) {
  BusinessRejectMessage sent;
  BusinessRejectMessage got;
  uint8_t wire[49];
  uint8_t again[49];

  any_business_reject_message(&sent);
  assert(encode_business_reject_message(&sent, wire, 0) == 49);
  assert(decode_business_reject_message(&got, wire, 0) == 49);
  equal_business_reject_message(&got, &sent);

  for (size_t i = 0; i < 49; i++) { wire[i] = arbitrary(); }
  assert(decode_business_reject_message(&got, wire, 0) == 49);
  assert(encode_business_reject_message(&got, again, 0) == 49);
  for (size_t i = 0; i < 49; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_message();
  check_logon_response_message();
  check_logout_message();
  check_reject_message();
  check_missed_message_request_message();
  check_missed_message_request_ack_message();
  check_transmission_complete_message();
  check_system_status_message();
  check_transact_time();
  check_order_cancel_reject_message();
  check_order_mass_cancel_report_message();
  check_news_message();
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
