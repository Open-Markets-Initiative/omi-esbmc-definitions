// currenex/now/CurrenexForex_Now_v10.c
/*
 * Currenex Now Forex Market Data
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
 *   - a field of no fixed width
 *   - a run of a stated number of entries
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

/* ---- Message Header: 9 bytes ------------------------------------------------- */

/* Currenex Itch Market Data Message Header */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t timestamp[4];        /* bytes 4 to 7 */
  uint8_t message_type;        /* byte 8 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->timestamp[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->timestamp[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[9];
  uint8_t again[9];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 9);
  assert(decode_message_header(&got, wire, 0) == 9);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 9);
  assert(encode_message_header(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Message: 44 bytes ------------------------------------------------- */

/* Client initiates a session by submitting a Logon message to Currenex_NOW */
typedef struct {
  uint8_t user_id[20];    /* bytes 0 to 19 */
  uint8_t password[20];   /* bytes 20 to 39 */
  uint8_t session_id[4];  /* bytes 40 to 43 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* Logon Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Logon Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 44);
  assert(decode_logon_message(&got, wire, 0) == 44);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 44);
  assert(encode_logon_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 27 bytes ------------------------------------------------ */

/* Terminate a session by sending or receiving a Logout message */
typedef struct {
  uint8_t user_id[20];        /* bytes 0 to 19 */
  uint8_t session_id[4];      /* bytes 20 to 23 */
  uint8_t reason_alpha_3[3];  /* bytes 24 to 26 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->reason_alpha_3[i] = arbitrary(); }
}

/* Logout Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->reason_alpha_3[i]; }

  return at;
}

/* Logout Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->reason_alpha_3[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->reason_alpha_3[i] == written->reason_alpha_3[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 27);
  assert(decode_logout_message(&got, wire, 0) == 27);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 27);
  assert(encode_logout_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heart Beat Message: 4 bytes --------------------------------------------- */

/* Keep-alive ping sent every 15 seconds; client must respond */
typedef struct {
  uint8_t session_id[4];  /* bytes 0 to 3 */
} HeartBeatMessage;

/* any Heart Beat Message at all: every byte one the checker chooses */
static void any_heart_beat_message(HeartBeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
}

/* Heart Beat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heart_beat_message(const HeartBeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Heart Beat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heart_beat_message(HeartBeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Heart Beat Message is what was written, byte for byte */
static void equal_heart_beat_message(const HeartBeatMessage *read, const HeartBeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Heart Beat Message: written and read back, then read and written back */
static void check_heart_beat_message(void) {
  HeartBeatMessage sent;
  HeartBeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heart_beat_message(&sent);
  assert(encode_heart_beat_message(&sent, wire, 0) == 4);
  assert(decode_heart_beat_message(&got, wire, 0) == 4);
  equal_heart_beat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heart_beat_message(&got, wire, 0) == 4);
  assert(encode_heart_beat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info: 35 bytes ----------------------------------------------- */

/* Definition of a currency or metal instrument */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
  uint8_t instrument_type;      /* byte 6 */
  uint8_t instrument_id[20];    /* bytes 7 to 26 */
  uint8_t settlement_date[8];   /* bytes 27 to 34 */
} InstrumentInfo;

/* any Instrument Info at all: every byte one the checker chooses */
static void any_instrument_info(InstrumentInfo *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->instrument_type = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = arbitrary(); }
}

/* Instrument Info to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info(const InstrumentInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->instrument_type;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_date[i]; }

  return at;
}

/* Instrument Info off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info(InstrumentInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->instrument_type = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->settlement_date[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info is what was written, byte for byte */
static void equal_instrument_info(const InstrumentInfo *read, const InstrumentInfo *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->instrument_type == written->instrument_type);
  for (size_t i = 0; i < 20; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_date[i] == written->settlement_date[i]); }
}

/* Instrument Info: written and read back, then read and written back */
static void check_instrument_info(void) {
  InstrumentInfo sent;
  InstrumentInfo got;
  uint8_t wire[35];
  uint8_t again[35];

  any_instrument_info(&sent);
  assert(encode_instrument_info(&sent, wire, 0) == 35);
  assert(decode_instrument_info(&got, wire, 0) == 35);
  equal_instrument_info(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info(&got, wire, 0) == 35);
  assert(encode_instrument_info(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Info Ack Message: 6 bytes ------------------------------------ */

/* Acknowledge receipt of InstrumentInfo */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
} InstrumentInfoAckMessage;

/* any Instrument Info Ack Message at all: every byte one the checker chooses */
static void any_instrument_info_ack_message(InstrumentInfoAckMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
}

/* Instrument Info Ack Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_instrument_info_ack_message(const InstrumentInfoAckMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }

  return at;
}

/* Instrument Info Ack Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_instrument_info_ack_message(InstrumentInfoAckMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Info Ack Message is what was written, byte for byte */
static void equal_instrument_info_ack_message(const InstrumentInfoAckMessage *read, const InstrumentInfoAckMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
}

/* Instrument Info Ack Message: written and read back, then read and written back */
static void check_instrument_info_ack_message(void) {
  InstrumentInfoAckMessage sent;
  InstrumentInfoAckMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_instrument_info_ack_message(&sent);
  assert(encode_instrument_info_ack_message(&sent, wire, 0) == 6);
  assert(decode_instrument_info_ack_message(&got, wire, 0) == 6);
  equal_instrument_info_ack_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_info_ack_message(&got, wire, 0) == 6);
  assert(encode_instrument_info_ack_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscription Reply Message: 57 bytes ------------------------------------ */

/* Response to SubscriptionRequest */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t instrument_index[2];  /* bytes 4 to 5 */
  uint8_t type;                 /* byte 6 */
  uint8_t reason_alpha_50[50];  /* bytes 7 to 56 */
} SubscriptionReplyMessage;

/* any Subscription Reply Message at all: every byte one the checker chooses */
static void any_subscription_reply_message(SubscriptionReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = arbitrary(); }
}

/* Subscription Reply Message to the wire: 57 bytes from at, returning where the next byte goes */
static size_t encode_subscription_reply_message(const SubscriptionReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reason_alpha_50[i]; }

  return at;
}

/* Subscription Reply Message off the wire: 57 bytes from at, returning where the next byte lies */
static size_t decode_subscription_reply_message(SubscriptionReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = wire[at++]; }

  return at;
}

/* what was read of Subscription Reply Message is what was written, byte for byte */
static void equal_subscription_reply_message(const SubscriptionReplyMessage *read, const SubscriptionReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->type == written->type);
  for (size_t i = 0; i < 50; i++) { assert(read->reason_alpha_50[i] == written->reason_alpha_50[i]); }
}

/* Subscription Reply Message: written and read back, then read and written back */
static void check_subscription_reply_message(void) {
  SubscriptionReplyMessage sent;
  SubscriptionReplyMessage got;
  uint8_t wire[57];
  uint8_t again[57];

  any_subscription_reply_message(&sent);
  assert(encode_subscription_reply_message(&sent, wire, 0) == 57);
  assert(decode_subscription_reply_message(&got, wire, 0) == 57);
  equal_subscription_reply_message(&got, &sent);

  for (size_t i = 0; i < 57; i++) { wire[i] = arbitrary(); }
  assert(decode_subscription_reply_message(&got, wire, 0) == 57);
  assert(encode_subscription_reply_message(&got, again, 0) == 57);
  for (size_t i = 0; i < 57; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Subscription Reply Message: 55 bytes ------------------------------- */

/* Response to MassSubscriptionRequest */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t type;                 /* byte 4 */
  uint8_t reason_alpha_50[50];  /* bytes 5 to 54 */
} MassSubscriptionReplyMessage;

/* any Mass Subscription Reply Message at all: every byte one the checker chooses */
static void any_mass_subscription_reply_message(MassSubscriptionReplyMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = arbitrary(); }
}

/* Mass Subscription Reply Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_mass_subscription_reply_message(const MassSubscriptionReplyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reason_alpha_50[i]; }

  return at;
}

/* Mass Subscription Reply Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_mass_subscription_reply_message(MassSubscriptionReplyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Subscription Reply Message is what was written, byte for byte */
static void equal_mass_subscription_reply_message(const MassSubscriptionReplyMessage *read, const MassSubscriptionReplyMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->type == written->type);
  for (size_t i = 0; i < 50; i++) { assert(read->reason_alpha_50[i] == written->reason_alpha_50[i]); }
}

/* Mass Subscription Reply Message: written and read back, then read and written back */
static void check_mass_subscription_reply_message(void) {
  MassSubscriptionReplyMessage sent;
  MassSubscriptionReplyMessage got;
  uint8_t wire[55];
  uint8_t again[55];

  any_mass_subscription_reply_message(&sent);
  assert(encode_mass_subscription_reply_message(&sent, wire, 0) == 55);
  assert(decode_mass_subscription_reply_message(&got, wire, 0) == 55);
  equal_mass_subscription_reply_message(&got, &sent);

  for (size_t i = 0; i < 55; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_subscription_reply_message(&got, wire, 0) == 55);
  assert(encode_mass_subscription_reply_message(&got, again, 0) == 55);
  for (size_t i = 0; i < 55; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid: 12 bytes ----------------------------------------------------------- */

/* Market level bid */
typedef struct {
  uint8_t rate[4];    /* bytes 0 to 3 */
  uint8_t amount[8];  /* bytes 4 to 11 */
} Bid;

/* any Bid at all: every byte one the checker chooses */
static void any_bid(Bid *record) {
  for (size_t i = 0; i < 4; i++) { record->rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
}

/* Bid to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_bid(const Bid *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }

  return at;
}

/* Bid off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_bid(Bid *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }

  return at;
}

/* what was read of Bid is what was written, byte for byte */
static void equal_bid(const Bid *read, const Bid *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->rate[i] == written->rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
}

/* Bid: written and read back, then read and written back */
static void check_bid(void) {
  Bid sent;
  Bid got;
  uint8_t wire[12];
  uint8_t again[12];

  any_bid(&sent);
  assert(encode_bid(&sent, wire, 0) == 12);
  assert(decode_bid(&got, wire, 0) == 12);
  equal_bid(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_bid(&got, wire, 0) == 12);
  assert(encode_bid(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Offer: 12 bytes --------------------------------------------------------- */

/* Market level offer */
typedef struct {
  uint8_t rate[4];    /* bytes 0 to 3 */
  uint8_t amount[8];  /* bytes 4 to 11 */
} Offer;

/* any Offer at all: every byte one the checker chooses */
static void any_offer(Offer *record) {
  for (size_t i = 0; i < 4; i++) { record->rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = arbitrary(); }
}

/* Offer to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_offer(const Offer *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->amount[i]; }

  return at;
}

/* Offer off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_offer(Offer *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->amount[i] = wire[at++]; }

  return at;
}

/* what was read of Offer is what was written, byte for byte */
static void equal_offer(const Offer *read, const Offer *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->rate[i] == written->rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->amount[i] == written->amount[i]); }
}

/* Offer: written and read back, then read and written back */
static void check_offer(void) {
  Offer sent;
  Offer got;
  uint8_t wire[12];
  uint8_t again[12];

  any_offer(&sent);
  assert(encode_offer(&sent, wire, 0) == 12);
  assert(decode_offer(&got, wire, 0) == 12);
  equal_offer(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_offer(&got, wire, 0) == 12);
  assert(encode_offer(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Paid Given Message: 16 bytes -------------------------------------------- */

/* Latest trade versus liquidity */
typedef struct {
  uint8_t instrument_index[2];   /* bytes 0 to 1 */
  uint8_t rate[4];               /* bytes 2 to 5 */
  uint8_t size_indicator;        /* byte 6 */
  uint8_t paid_given_indicator;  /* byte 7 */
  uint8_t transact_time[8];      /* bytes 8 to 15 */
} PaidGivenMessage;

/* any Paid Given Message at all: every byte one the checker chooses */
static void any_paid_given_message(PaidGivenMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rate[i] = arbitrary(); }
  record->size_indicator = arbitrary();
  record->paid_given_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
}

/* Paid Given Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_paid_given_message(const PaidGivenMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rate[i]; }
  wire[at++] = record->size_indicator;
  wire[at++] = record->paid_given_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }

  return at;
}

/* Paid Given Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_paid_given_message(PaidGivenMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rate[i] = wire[at++]; }
  record->size_indicator = wire[at++];
  record->paid_given_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }

  return at;
}

/* what was read of Paid Given Message is what was written, byte for byte */
static void equal_paid_given_message(const PaidGivenMessage *read, const PaidGivenMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rate[i] == written->rate[i]); }
  assert(read->size_indicator == written->size_indicator);
  assert(read->paid_given_indicator == written->paid_given_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
}

/* Paid Given Message: written and read back, then read and written back */
static void check_paid_given_message(void) {
  PaidGivenMessage sent;
  PaidGivenMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_paid_given_message(&sent);
  assert(encode_paid_given_message(&sent, wire, 0) == 16);
  assert(decode_paid_given_message(&got, wire, 0) == 16);
  equal_paid_given_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_paid_given_message(&got, wire, 0) == 16);
  assert(encode_paid_given_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conf Factor 75: 8 bytes ------------------------------------------------- */

/* 75th percentile confidence factor */
typedef struct {
  uint8_t bid_price[4];    /* bytes 0 to 3 */
  uint8_t offer_price[4];  /* bytes 4 to 7 */
} ConfFactor75;

/* any Conf Factor 75 at all: every byte one the checker chooses */
static void any_conf_factor75(ConfFactor75 *record) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = arbitrary(); }
}

/* Conf Factor 75 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_conf_factor75(const ConfFactor75 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price[i]; }

  return at;
}

/* Conf Factor 75 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_conf_factor75(ConfFactor75 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Conf Factor 75 is what was written, byte for byte */
static void equal_conf_factor75(const ConfFactor75 *read, const ConfFactor75 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
}

/* Conf Factor 75: written and read back, then read and written back */
static void check_conf_factor75(void) {
  ConfFactor75 sent;
  ConfFactor75 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_conf_factor75(&sent);
  assert(encode_conf_factor75(&sent, wire, 0) == 8);
  assert(decode_conf_factor75(&got, wire, 0) == 8);
  equal_conf_factor75(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_conf_factor75(&got, wire, 0) == 8);
  assert(encode_conf_factor75(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conf Factor 50: 8 bytes ------------------------------------------------- */

/* 50th percentile confidence factor */
typedef struct {
  uint8_t bid_price[4];    /* bytes 0 to 3 */
  uint8_t offer_price[4];  /* bytes 4 to 7 */
} ConfFactor50;

/* any Conf Factor 50 at all: every byte one the checker chooses */
static void any_conf_factor50(ConfFactor50 *record) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = arbitrary(); }
}

/* Conf Factor 50 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_conf_factor50(const ConfFactor50 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price[i]; }

  return at;
}

/* Conf Factor 50 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_conf_factor50(ConfFactor50 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Conf Factor 50 is what was written, byte for byte */
static void equal_conf_factor50(const ConfFactor50 *read, const ConfFactor50 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
}

/* Conf Factor 50: written and read back, then read and written back */
static void check_conf_factor50(void) {
  ConfFactor50 sent;
  ConfFactor50 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_conf_factor50(&sent);
  assert(encode_conf_factor50(&sent, wire, 0) == 8);
  assert(decode_conf_factor50(&got, wire, 0) == 8);
  equal_conf_factor50(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_conf_factor50(&got, wire, 0) == 8);
  assert(encode_conf_factor50(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Conf Factor 25: 8 bytes ------------------------------------------------- */

/* 25th percentile confidence factor */
typedef struct {
  uint8_t bid_price[4];    /* bytes 0 to 3 */
  uint8_t offer_price[4];  /* bytes 4 to 7 */
} ConfFactor25;

/* any Conf Factor 25 at all: every byte one the checker chooses */
static void any_conf_factor25(ConfFactor25 *record) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = arbitrary(); }
}

/* Conf Factor 25 to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_conf_factor25(const ConfFactor25 *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_price[i]; }

  return at;
}

/* Conf Factor 25 off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_conf_factor25(ConfFactor25 *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->bid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_price[i] = wire[at++]; }

  return at;
}

/* what was read of Conf Factor 25 is what was written, byte for byte */
static void equal_conf_factor25(const ConfFactor25 *read, const ConfFactor25 *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->bid_price[i] == written->bid_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_price[i] == written->offer_price[i]); }
}

/* Conf Factor 25: written and read back, then read and written back */
static void check_conf_factor25(void) {
  ConfFactor25 sent;
  ConfFactor25 got;
  uint8_t wire[8];
  uint8_t again[8];

  any_conf_factor25(&sent);
  assert(encode_conf_factor25(&sent, wire, 0) == 8);
  assert(decode_conf_factor25(&got, wire, 0) == 8);
  equal_conf_factor25(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_conf_factor25(&got, wire, 0) == 8);
  assert(encode_conf_factor25(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wamr With Confidence Factor Message: 38 bytes --------------------------- */

/* Weighted average mid-rate with confidence factors */
typedef struct {
  uint8_t instrument_index[2];       /* bytes 0 to 1 */
  uint8_t price[4];                  /* bytes 2 to 5 */
  ConfFactor75 conf_factor_75;       /* bytes 6 to 13 */
  ConfFactor50 conf_factor_50;       /* bytes 14 to 21 */
  ConfFactor25 conf_factor_25;       /* bytes 22 to 29 */
  uint8_t calculation_timestamp[8];  /* bytes 30 to 37 */
} WamrWithConfidenceFactorMessage;

/* any Wamr With Confidence Factor Message at all: every byte one the checker chooses */
static void any_wamr_with_confidence_factor_message(WamrWithConfidenceFactorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  any_conf_factor75(&record->conf_factor_75);
  any_conf_factor50(&record->conf_factor_50);
  any_conf_factor25(&record->conf_factor_25);
  for (size_t i = 0; i < 8; i++) { record->calculation_timestamp[i] = arbitrary(); }
}

/* Wamr With Confidence Factor Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_wamr_with_confidence_factor_message(const WamrWithConfidenceFactorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  at = encode_conf_factor75(&record->conf_factor_75, wire, at);
  at = encode_conf_factor50(&record->conf_factor_50, wire, at);
  at = encode_conf_factor25(&record->conf_factor_25, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->calculation_timestamp[i]; }

  return at;
}

/* Wamr With Confidence Factor Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_wamr_with_confidence_factor_message(WamrWithConfidenceFactorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  at = decode_conf_factor75(&record->conf_factor_75, wire, at);
  at = decode_conf_factor50(&record->conf_factor_50, wire, at);
  at = decode_conf_factor25(&record->conf_factor_25, wire, at);
  for (size_t i = 0; i < 8; i++) { record->calculation_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Wamr With Confidence Factor Message is what was written, byte for byte */
static void equal_wamr_with_confidence_factor_message(const WamrWithConfidenceFactorMessage *read, const WamrWithConfidenceFactorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  equal_conf_factor75(&read->conf_factor_75, &written->conf_factor_75);
  equal_conf_factor50(&read->conf_factor_50, &written->conf_factor_50);
  equal_conf_factor25(&read->conf_factor_25, &written->conf_factor_25);
  for (size_t i = 0; i < 8; i++) { assert(read->calculation_timestamp[i] == written->calculation_timestamp[i]); }
}

/* Wamr With Confidence Factor Message: written and read back, then read and written back */
static void check_wamr_with_confidence_factor_message(void) {
  WamrWithConfidenceFactorMessage sent;
  WamrWithConfidenceFactorMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_wamr_with_confidence_factor_message(&sent);
  assert(encode_wamr_with_confidence_factor_message(&sent, wire, 0) == 38);
  assert(decode_wamr_with_confidence_factor_message(&got, wire, 0) == 38);
  equal_wamr_with_confidence_factor_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_wamr_with_confidence_factor_message(&got, wire, 0) == 38);
  assert(encode_wamr_with_confidence_factor_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mid Activity Indicator Message: 3 bytes --------------------------------- */

/* Indicator of mid-rate activity windows */
typedef struct {
  uint8_t instrument_index[2];  /* bytes 0 to 1 */
  uint8_t activity_indicator;   /* byte 2 */
} MidActivityIndicatorMessage;

/* any Mid Activity Indicator Message at all: every byte one the checker chooses */
static void any_mid_activity_indicator_message(MidActivityIndicatorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = arbitrary(); }
  record->activity_indicator = arbitrary();
}

/* Mid Activity Indicator Message to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_mid_activity_indicator_message(const MidActivityIndicatorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->instrument_index[i]; }
  wire[at++] = record->activity_indicator;

  return at;
}

/* Mid Activity Indicator Message off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_mid_activity_indicator_message(MidActivityIndicatorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->instrument_index[i] = wire[at++]; }
  record->activity_indicator = wire[at++];

  return at;
}

/* what was read of Mid Activity Indicator Message is what was written, byte for byte */
static void equal_mid_activity_indicator_message(const MidActivityIndicatorMessage *read, const MidActivityIndicatorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->instrument_index[i] == written->instrument_index[i]); }
  assert(read->activity_indicator == written->activity_indicator);
}

/* Mid Activity Indicator Message: written and read back, then read and written back */
static void check_mid_activity_indicator_message(void) {
  MidActivityIndicatorMessage sent;
  MidActivityIndicatorMessage got;
  uint8_t wire[3];
  uint8_t again[3];

  any_mid_activity_indicator_message(&sent);
  assert(encode_mid_activity_indicator_message(&sent, wire, 0) == 3);
  assert(decode_mid_activity_indicator_message(&got, wire, 0) == 3);
  equal_mid_activity_indicator_message(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_mid_activity_indicator_message(&got, wire, 0) == 3);
  assert(encode_mid_activity_indicator_message(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 55 bytes ------------------------------------------------ */

/* Reject incorrectly formatted or invalid messages */
typedef struct {
  uint8_t session_id[4];        /* bytes 0 to 3 */
  uint8_t reject_msg_type;      /* byte 4 */
  uint8_t reason_alpha_50[50];  /* bytes 5 to 54 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = arbitrary(); }
  record->reject_msg_type = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = arbitrary(); }
}

/* Reject Message to the wire: 55 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->reject_msg_type;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->reason_alpha_50[i]; }

  return at;
}

/* Reject Message off the wire: 55 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_id[i] = wire[at++]; }
  record->reject_msg_type = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->reason_alpha_50[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->reject_msg_type == written->reject_msg_type);
  for (size_t i = 0; i < 50; i++) { assert(read->reason_alpha_50[i] == written->reason_alpha_50[i]); }
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_message();
  check_logout_message();
  check_heart_beat_message();
  check_instrument_info();
  check_instrument_info_ack_message();
  check_subscription_reply_message();
  check_mass_subscription_reply_message();
  check_bid();
  check_offer();
  check_paid_given_message();
  check_conf_factor75();
  check_conf_factor50();
  check_conf_factor25();
  check_wamr_with_confidence_factor_message();
  check_mid_activity_indicator_message();
  check_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
