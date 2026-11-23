// nse/nsecm/orderentry/NseCm_OrderEntry_NnfDirect_v6_6_Server.c
/*
 * National Stock Exchange of India Ltd Order Entry
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
 *   - a Integrity rule
 *   - a run of a stated number of entries
 *   - a Composite rule
 *   - the dispatch that chooses a message by its type
 *   - a field read in bits
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

/* ---- Packet Header: 6 bytes -------------------------------------------------- */

/* Packet Length and Sequence number, the first six bytes of the direct interface's twenty two byte packet header; its last sixteen open each packet body branch */
typedef struct {
  uint8_t packet_length[2];           /* bytes 0 to 1 */
  uint8_t packet_sequence_number[4];  /* bytes 2 to 5 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = arbitrary(); }
}

/* Packet Header to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->packet_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->packet_sequence_number[i]; }

  return at;
}

/* Packet Header off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->packet_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->packet_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->packet_length[i] == written->packet_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->packet_sequence_number[i] == written->packet_sequence_number[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[6];
  uint8_t again[6];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 6);
  assert(decode_packet_header(&got, wire, 0) == 6);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 6);
  assert(encode_packet_header(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 40 bytes ------------------------------------------------ */

/* MESSAGE_HEADER */
typedef struct {
  uint8_t transaction_code[2];  /* bytes 0 to 1 */
  uint8_t log_time[4];          /* bytes 2 to 5 */
  uint8_t alpha_char[2];        /* bytes 6 to 7 */
  uint8_t trader_id[4];         /* bytes 8 to 11 */
  uint8_t error_code[2];        /* bytes 12 to 13 */
  uint8_t header_timestamp[8];  /* bytes 14 to 21 */
  uint8_t time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t message_length[2];    /* bytes 38 to 39 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
}

/* Message Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->transaction_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->alpha_char[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->header_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }

  return at;
}

/* Message Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->header_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->transaction_code[i] == written->transaction_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->log_time[i] == written->log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->alpha_char[i] == written->alpha_char[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->header_timestamp[i] == written->header_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_1[i] == written->time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_stamp_2[i] == written->time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 40);
  assert(decode_message_header(&got, wire, 0) == 40);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 40);
  assert(encode_message_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel On Logout Status Response Message: 6 bytes ----------------------- */

/* Sent as COL_USER_STATUS_CHANGE _OUT */
typedef struct {
  uint8_t user_id[4];     /* bytes 0 to 3 */
  uint8_t colo_user_bit;  /* byte 4 */
  uint8_t reserved_1;     /* byte 5 */
} CancelOnLogoutStatusResponseMessage;

/* any Cancel On Logout Status Response Message at all: every byte one the checker chooses */
static void any_cancel_on_logout_status_response_message(CancelOnLogoutStatusResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->colo_user_bit = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Cancel On Logout Status Response Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_cancel_on_logout_status_response_message(const CancelOnLogoutStatusResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->colo_user_bit;
  wire[at++] = record->reserved_1;

  return at;
}

/* Cancel On Logout Status Response Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_cancel_on_logout_status_response_message(CancelOnLogoutStatusResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->colo_user_bit = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Cancel On Logout Status Response Message is what was written, byte for byte */
static void equal_cancel_on_logout_status_response_message(const CancelOnLogoutStatusResponseMessage *read, const CancelOnLogoutStatusResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->colo_user_bit == written->colo_user_bit);
  assert(read->reserved_1 == written->reserved_1);
}

/* Cancel On Logout Status Response Message: written and read back, then read and written back */
static void check_cancel_on_logout_status_response_message(void) {
  CancelOnLogoutStatusResponseMessage sent;
  CancelOnLogoutStatusResponseMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_cancel_on_logout_status_response_message(&sent);
  assert(encode_cancel_on_logout_status_response_message(&sent, wire, 0) == 6);
  assert(decode_cancel_on_logout_status_response_message(&got, wire, 0) == 6);
  equal_cancel_on_logout_status_response_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_on_logout_status_response_message(&got, wire, 0) == 6);
  assert(encode_cancel_on_logout_status_response_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sec Info: 12 bytes ------------------------------------------------------ */

/* SEC_INFO */
typedef struct {
  uint8_t symbol[10];  /* bytes 0 to 9 */
  uint8_t series[2];   /* bytes 10 to 11 */
} SecInfo;

/* any Sec Info at all: every byte one the checker chooses */
static void any_sec_info(SecInfo *record) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->series[i] = arbitrary(); }
}

/* Sec Info to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_sec_info(const SecInfo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->series[i]; }

  return at;
}

/* Sec Info off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_sec_info(SecInfo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->series[i] = wire[at++]; }

  return at;
}

/* what was read of Sec Info is what was written, byte for byte */
static void equal_sec_info(const SecInfo *read, const SecInfo *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->series[i] == written->series[i]); }
}

/* Sec Info: written and read back, then read and written back */
static void check_sec_info(void) {
  SecInfo sent;
  SecInfo got;
  uint8_t wire[12];
  uint8_t again[12];

  any_sec_info(&sent);
  assert(encode_sec_info(&sent, wire, 0) == 12);
  assert(decode_sec_info(&got, wire, 0) == 12);
  equal_sec_info(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_sec_info(&got, wire, 0) == 12);
  assert(encode_sec_info(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Response Message: 140 bytes --------------------------------------- */

/* Sent as ERROR_RESPONSE_OUT */
typedef struct {
  SecInfo sec_info;            /* bytes 0 to 11 */
  uint8_t error_message[128];  /* bytes 12 to 139 */
} ErrorResponseMessage;

/* any Error Response Message at all: every byte one the checker chooses */
static void any_error_response_message(ErrorResponseMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = arbitrary(); }
}

/* Error Response Message to the wire: 140 bytes from at, returning where the next byte goes */
static size_t encode_error_response_message(const ErrorResponseMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { wire[at++] = record->error_message[i]; }

  return at;
}

/* Error Response Message off the wire: 140 bytes from at, returning where the next byte lies */
static size_t decode_error_response_message(ErrorResponseMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 128; i++) { record->error_message[i] = wire[at++]; }

  return at;
}

/* what was read of Error Response Message is what was written, byte for byte */
static void equal_error_response_message(const ErrorResponseMessage *read, const ErrorResponseMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 128; i++) { assert(read->error_message[i] == written->error_message[i]); }
}

/* Error Response Message: written and read back, then read and written back */
static void check_error_response_message(void) {
  ErrorResponseMessage sent;
  ErrorResponseMessage got;
  uint8_t wire[140];
  uint8_t again[140];

  any_error_response_message(&sent);
  assert(encode_error_response_message(&sent, wire, 0) == 140);
  assert(decode_error_response_message(&got, wire, 0) == 140);
  equal_error_response_message(&got, &sent);

  for (size_t i = 0; i < 140; i++) { wire[i] = arbitrary(); }
  assert(decode_error_response_message(&got, wire, 0) == 140);
  assert(encode_error_response_message(&got, again, 0) == 140);
  for (size_t i = 0; i < 140; i++) { assert(again[i] == wire[i]); }
}

/* ---- Box Sign On Response Message: 12 bytes ---------------------------------- */

/* Sent as BOX_SIGN_ON_REQUEST_OUT */
typedef struct {
  uint8_t box_id[2];        /* bytes 0 to 1 */
  uint8_t reserved_10[10];  /* bytes 2 to 11 */
} BoxSignOnResponseMessage;

/* any Box Sign On Response Message at all: every byte one the checker chooses */
static void any_box_sign_on_response_message(BoxSignOnResponseMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Box Sign On Response Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_box_sign_on_response_message(const BoxSignOnResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->box_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Box Sign On Response Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_box_sign_on_response_message(BoxSignOnResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->box_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Box Sign On Response Message is what was written, byte for byte */
static void equal_box_sign_on_response_message(const BoxSignOnResponseMessage *read, const BoxSignOnResponseMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->box_id[i] == written->box_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Box Sign On Response Message: written and read back, then read and written back */
static void check_box_sign_on_response_message(void) {
  BoxSignOnResponseMessage sent;
  BoxSignOnResponseMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_box_sign_on_response_message(&sent);
  assert(encode_box_sign_on_response_message(&sent, wire, 0) == 12);
  assert(decode_box_sign_on_response_message(&got, wire, 0) == 12);
  equal_box_sign_on_response_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_box_sign_on_response_message(&got, wire, 0) == 12);
  assert(encode_box_sign_on_response_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Existing Encryption Tail: 16 bytes -------------------------------------- */

/* Initialisation vector used by the existing encryption */
typedef struct {
  uint8_t cryptographic_iv[16];  /* bytes 0 to 15 */
} ExistingEncryptionTail;

/* any Existing Encryption Tail at all: every byte one the checker chooses */
static void any_existing_encryption_tail(ExistingEncryptionTail *record) {
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = arbitrary(); }
}

/* Existing Encryption Tail to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_existing_encryption_tail(const ExistingEncryptionTail *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->cryptographic_iv[i]; }

  return at;
}

/* Existing Encryption Tail off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_existing_encryption_tail(ExistingEncryptionTail *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 16; i++) { record->cryptographic_iv[i] = wire[at++]; }

  return at;
}

/* what was read of Existing Encryption Tail is what was written, byte for byte */
static void equal_existing_encryption_tail(const ExistingEncryptionTail *read, const ExistingEncryptionTail *written) {
  for (size_t i = 0; i < 16; i++) { assert(read->cryptographic_iv[i] == written->cryptographic_iv[i]); }
}

/* Existing Encryption Tail: written and read back, then read and written back */
static void check_existing_encryption_tail(void) {
  ExistingEncryptionTail sent;
  ExistingEncryptionTail got;
  uint8_t wire[16];
  uint8_t again[16];

  any_existing_encryption_tail(&sent);
  assert(encode_existing_encryption_tail(&sent, wire, 0) == 16);
  assert(decode_existing_encryption_tail(&got, wire, 0) == 16);
  equal_existing_encryption_tail(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_existing_encryption_tail(&got, wire, 0) == 16);
  assert(encode_existing_encryption_tail(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Encryption Tail: 28 bytes ------------------------------------------- */

/* Initialisation vectors used by the new authenticated encryption */
typedef struct {
  uint8_t static_cryptographic_iv[8];        /* bytes 0 to 7 */
  uint8_t dynamic_cryptographic_iv[8];       /* bytes 8 to 15 */
  uint8_t cryptographic_additional_key[12];  /* bytes 16 to 27 */
} NewEncryptionTail;

/* any New Encryption Tail at all: every byte one the checker chooses */
static void any_new_encryption_tail(NewEncryptionTail *record) {
  for (size_t i = 0; i < 8; i++) { record->static_cryptographic_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dynamic_cryptographic_iv[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->cryptographic_additional_key[i] = arbitrary(); }
}

/* New Encryption Tail to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_new_encryption_tail(const NewEncryptionTail *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->static_cryptographic_iv[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dynamic_cryptographic_iv[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->cryptographic_additional_key[i]; }

  return at;
}

/* New Encryption Tail off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_new_encryption_tail(NewEncryptionTail *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->static_cryptographic_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dynamic_cryptographic_iv[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->cryptographic_additional_key[i] = wire[at++]; }

  return at;
}

/* what was read of New Encryption Tail is what was written, byte for byte */
static void equal_new_encryption_tail(const NewEncryptionTail *read, const NewEncryptionTail *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->static_cryptographic_iv[i] == written->static_cryptographic_iv[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dynamic_cryptographic_iv[i] == written->dynamic_cryptographic_iv[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->cryptographic_additional_key[i] == written->cryptographic_additional_key[i]); }
}

/* New Encryption Tail: written and read back, then read and written back */
static void check_new_encryption_tail(void) {
  NewEncryptionTail sent;
  NewEncryptionTail got;
  uint8_t wire[28];
  uint8_t again[28];

  any_new_encryption_tail(&sent);
  assert(encode_new_encryption_tail(&sent, wire, 0) == 28);
  assert(decode_new_encryption_tail(&got, wire, 0) == 28);
  equal_new_encryption_tail(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_new_encryption_tail(&got, wire, 0) == 28);
  assert(encode_new_encryption_tail(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message To Trader Message: 250 bytes ---------------------------- */

/* Sent as CTRL_MSG_TO_TRADER */
typedef struct {
  uint8_t trader_id[4];    /* bytes 0 to 3 */
  uint8_t action_code[3];  /* bytes 4 to 6 */
  uint8_t reserved_1;      /* byte 7 */
  uint8_t msg_length[2];   /* bytes 8 to 9 */
  uint8_t msg[240];        /* bytes 10 to 249 */
} ControlMessageToTraderMessage;

/* any Control Message To Trader Message at all: every byte one the checker chooses */
static void any_control_message_to_trader_message(ControlMessageToTraderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  for (size_t i = 0; i < 240; i++) { record->msg[i] = arbitrary(); }
}

/* Control Message To Trader Message to the wire: 250 bytes from at, returning where the next byte goes */
static size_t encode_control_message_to_trader_message(const ControlMessageToTraderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->action_code[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  for (size_t i = 0; i < 240; i++) { wire[at++] = record->msg[i]; }

  return at;
}

/* Control Message To Trader Message off the wire: 250 bytes from at, returning where the next byte lies */
static size_t decode_control_message_to_trader_message(ControlMessageToTraderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->action_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  for (size_t i = 0; i < 240; i++) { record->msg[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message To Trader Message is what was written, byte for byte */
static void equal_control_message_to_trader_message(const ControlMessageToTraderMessage *read, const ControlMessageToTraderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->action_code[i] == written->action_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  for (size_t i = 0; i < 240; i++) { assert(read->msg[i] == written->msg[i]); }
}

/* Control Message To Trader Message: written and read back, then read and written back */
static void check_control_message_to_trader_message(void) {
  ControlMessageToTraderMessage sent;
  ControlMessageToTraderMessage got;
  uint8_t wire[250];
  uint8_t again[250];

  any_control_message_to_trader_message(&sent);
  assert(encode_control_message_to_trader_message(&sent, wire, 0) == 250);
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 250);
  equal_control_message_to_trader_message(&got, &sent);

  for (size_t i = 0; i < 250; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message_to_trader_message(&got, wire, 0) == 250);
  assert(encode_control_message_to_trader_message(&got, again, 0) == 250);
  for (size_t i = 0; i < 250; i++) { assert(again[i] == wire[i]); }
}

/* ---- Password Reset Out Message: 18 bytes ------------------------------------ */

/* Sent as RESET_PASSWORD_OUT */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t reserved_14[14];  /* bytes 4 to 17 */
} PasswordResetOutMessage;

/* any Password Reset Out Message at all: every byte one the checker chooses */
static void any_password_reset_out_message(PasswordResetOutMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = arbitrary(); }
}

/* Password Reset Out Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_password_reset_out_message(const PasswordResetOutMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->reserved_14[i]; }

  return at;
}

/* Password Reset Out Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_password_reset_out_message(PasswordResetOutMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->reserved_14[i] = wire[at++]; }

  return at;
}

/* what was read of Password Reset Out Message is what was written, byte for byte */
static void equal_password_reset_out_message(const PasswordResetOutMessage *read, const PasswordResetOutMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->reserved_14[i] == written->reserved_14[i]); }
}

/* Password Reset Out Message: written and read back, then read and written back */
static void check_password_reset_out_message(void) {
  PasswordResetOutMessage sent;
  PasswordResetOutMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_password_reset_out_message(&sent);
  assert(encode_password_reset_out_message(&sent, wire, 0) == 18);
  assert(decode_password_reset_out_message(&got, wire, 0) == 18);
  equal_password_reset_out_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_password_reset_out_message(&got, wire, 0) == 18);
  assert(encode_password_reset_out_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Inquiry Out Message: 170 bytes ------------------------------------ */

/* Sent as TRADE_ERROR, TRADE_CANCEL_OUT */
typedef struct {
  SecInfo sec_info;                 /* bytes 0 to 11 */
  uint8_t fill_number[4];           /* bytes 12 to 15 */
  uint8_t fill_qty[4];              /* bytes 16 to 19 */
  uint8_t fill_price[4];            /* bytes 20 to 23 */
  uint8_t market_type[2];           /* bytes 24 to 25 */
  uint8_t new_volume[4];            /* bytes 26 to 29 */
  uint8_t reserved_24[24];          /* bytes 30 to 53 */
  uint8_t buy_broker_id[5];         /* bytes 54 to 58 */
  uint8_t sell_broker_id[5];        /* bytes 59 to 63 */
  uint8_t trader_id[4];             /* bytes 64 to 67 */
  uint8_t requested_by[2];          /* bytes 68 to 69 */
  uint8_t buy_account_number[10];   /* bytes 70 to 79 */
  uint8_t sell_account_number[10];  /* bytes 80 to 89 */
  uint8_t buy_pan[10];              /* bytes 90 to 99 */
  uint8_t sell_pan[10];             /* bytes 100 to 109 */
  uint8_t reserved_60[60];          /* bytes 110 to 169 */
} TradeInquiryOutMessage;

/* any Trade Inquiry Out Message at all: every byte one the checker chooses */
static void any_trade_inquiry_out_message(TradeInquiryOutMessage *record) {
  any_sec_info(&record->sec_info);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = arbitrary(); }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = arbitrary(); }
}

/* Trade Inquiry Out Message to the wire: 170 bytes from at, returning where the next byte goes */
static size_t encode_trade_inquiry_out_message(const TradeInquiryOutMessage *record, uint8_t *wire, size_t at) {
  at = encode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->fill_price[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->market_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_volume[i]; }
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->reserved_24[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_broker_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_broker_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->requested_by[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_account_number[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->buy_pan[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->sell_pan[i]; }
  for (size_t i = 0; i < 60; i++) { wire[at++] = record->reserved_60[i]; }

  return at;
}

/* Trade Inquiry Out Message off the wire: 170 bytes from at, returning where the next byte lies */
static size_t decode_trade_inquiry_out_message(TradeInquiryOutMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sec_info(&record->sec_info, wire, at);
  for (size_t i = 0; i < 4; i++) { record->fill_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->fill_price[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->market_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 24; i++) { record->reserved_24[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->buy_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->sell_broker_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->requested_by[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->buy_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->sell_pan[i] = wire[at++]; }
  for (size_t i = 0; i < 60; i++) { record->reserved_60[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Inquiry Out Message is what was written, byte for byte */
static void equal_trade_inquiry_out_message(const TradeInquiryOutMessage *read, const TradeInquiryOutMessage *written) {
  equal_sec_info(&read->sec_info, &written->sec_info);
  for (size_t i = 0; i < 4; i++) { assert(read->fill_number[i] == written->fill_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_qty[i] == written->fill_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->fill_price[i] == written->fill_price[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->market_type[i] == written->market_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_volume[i] == written->new_volume[i]); }
  for (size_t i = 0; i < 24; i++) { assert(read->reserved_24[i] == written->reserved_24[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->buy_broker_id[i] == written->buy_broker_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->sell_broker_id[i] == written->sell_broker_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->requested_by[i] == written->requested_by[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_account_number[i] == written->buy_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_account_number[i] == written->sell_account_number[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->buy_pan[i] == written->buy_pan[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->sell_pan[i] == written->sell_pan[i]); }
  for (size_t i = 0; i < 60; i++) { assert(read->reserved_60[i] == written->reserved_60[i]); }
}

/* Trade Inquiry Out Message: written and read back, then read and written back */
static void check_trade_inquiry_out_message(void) {
  TradeInquiryOutMessage sent;
  TradeInquiryOutMessage got;
  uint8_t wire[170];
  uint8_t again[170];

  any_trade_inquiry_out_message(&sent);
  assert(encode_trade_inquiry_out_message(&sent, wire, 0) == 170);
  assert(decode_trade_inquiry_out_message(&got, wire, 0) == 170);
  equal_trade_inquiry_out_message(&got, &sent);

  for (size_t i = 0; i < 170; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_inquiry_out_message(&got, wire, 0) == 170);
  assert(encode_trade_inquiry_out_message(&got, again, 0) == 170);
  for (size_t i = 0; i < 170; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Header Message: 2 bytes --------------------------- */

/* Sent as UPDATE_LOCALDB_HEADER */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseHeaderMessage;

/* any Update Local Database Header Message at all: every byte one the checker chooses */
static void any_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Header Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Header Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_header_message(UpdateLocalDatabaseHeaderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Header Message is what was written, byte for byte */
static void equal_update_local_database_header_message(const UpdateLocalDatabaseHeaderMessage *read, const UpdateLocalDatabaseHeaderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Header Message: written and read back, then read and written back */
static void check_update_local_database_header_message(void) {
  UpdateLocalDatabaseHeaderMessage sent;
  UpdateLocalDatabaseHeaderMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_header_message(&sent);
  assert(encode_update_local_database_header_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  equal_update_local_database_header_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_header_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_header_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Local Database Trailer Message: 2 bytes -------------------------- */

/* Sent as UPDATE_LOCALDB_TRAILER */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
} UpdateLocalDatabaseTrailerMessage;

/* any Update Local Database Trailer Message at all: every byte one the checker chooses */
static void any_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
}

/* Update Local Database Trailer Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }

  return at;
}

/* Update Local Database Trailer Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_update_local_database_trailer_message(UpdateLocalDatabaseTrailerMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }

  return at;
}

/* what was read of Update Local Database Trailer Message is what was written, byte for byte */
static void equal_update_local_database_trailer_message(const UpdateLocalDatabaseTrailerMessage *read, const UpdateLocalDatabaseTrailerMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
}

/* Update Local Database Trailer Message: written and read back, then read and written back */
static void check_update_local_database_trailer_message(void) {
  UpdateLocalDatabaseTrailerMessage sent;
  UpdateLocalDatabaseTrailerMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_update_local_database_trailer_message(&sent);
  assert(encode_update_local_database_trailer_message(&sent, wire, 0) == 2);
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  equal_update_local_database_trailer_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_update_local_database_trailer_message(&got, wire, 0) == 2);
  assert(encode_update_local_database_trailer_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Unlock Approval Rejection Message: 4 bytes ------------------------- */

/* Sent as USER_ADDR_UNLOCK_APPROVE_OUT, USER_ADDR_UNLOCK_REJECT_OUT */
typedef struct {
  uint8_t user_id[4];  /* bytes 0 to 3 */
} UserUnlockApprovalRejectionMessage;

/* any User Unlock Approval Rejection Message at all: every byte one the checker chooses */
static void any_user_unlock_approval_rejection_message(UserUnlockApprovalRejectionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
}

/* User Unlock Approval Rejection Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_user_unlock_approval_rejection_message(const UserUnlockApprovalRejectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }

  return at;
}

/* User Unlock Approval Rejection Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_user_unlock_approval_rejection_message(UserUnlockApprovalRejectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }

  return at;
}

/* what was read of User Unlock Approval Rejection Message is what was written, byte for byte */
static void equal_user_unlock_approval_rejection_message(const UserUnlockApprovalRejectionMessage *read, const UserUnlockApprovalRejectionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
}

/* User Unlock Approval Rejection Message: written and read back, then read and written back */
static void check_user_unlock_approval_rejection_message(void) {
  UserUnlockApprovalRejectionMessage sent;
  UserUnlockApprovalRejectionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_user_unlock_approval_rejection_message(&sent);
  assert(encode_user_unlock_approval_rejection_message(&sent, wire, 0) == 4);
  assert(decode_user_unlock_approval_rejection_message(&got, wire, 0) == 4);
  equal_user_unlock_approval_rejection_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_user_unlock_approval_rejection_message(&got, wire, 0) == 4);
  assert(encode_user_unlock_approval_rejection_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Unlock Requested Response Message: 4 bytes ------------------------- */

/* Sent as USER_ADDR_UNLOCK_OUT */
typedef struct {
  uint8_t user_id[4];  /* bytes 0 to 3 */
} UserUnlockRequestedResponseMessage;

/* any User Unlock Requested Response Message at all: every byte one the checker chooses */
static void any_user_unlock_requested_response_message(UserUnlockRequestedResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
}

/* User Unlock Requested Response Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_user_unlock_requested_response_message(const UserUnlockRequestedResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }

  return at;
}

/* User Unlock Requested Response Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_user_unlock_requested_response_message(UserUnlockRequestedResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }

  return at;
}

/* what was read of User Unlock Requested Response Message is what was written, byte for byte */
static void equal_user_unlock_requested_response_message(const UserUnlockRequestedResponseMessage *read, const UserUnlockRequestedResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
}

/* User Unlock Requested Response Message: written and read back, then read and written back */
static void check_user_unlock_requested_response_message(void) {
  UserUnlockRequestedResponseMessage sent;
  UserUnlockRequestedResponseMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_user_unlock_requested_response_message(&sent);
  assert(encode_user_unlock_requested_response_message(&sent, wire, 0) == 4);
  assert(decode_user_unlock_requested_response_message(&got, wire, 0) == 4);
  equal_user_unlock_requested_response_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_user_unlock_requested_response_message(&got, wire, 0) == 4);
  assert(encode_user_unlock_requested_response_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Modification Cancellation Status Response Message: 6 bytes -------- */

/* Sent as TRD_MOD_CXL_STATUS_CHANGE _OUT */
typedef struct {
  uint8_t user_id[4];       /* bytes 0 to 3 */
  uint8_t trd_mod_cxl_bit;  /* byte 4 */
  uint8_t reserved_1;       /* byte 5 */
} TradeModificationCancellationStatusResponseMessage;

/* any Trade Modification Cancellation Status Response Message at all: every byte one the checker chooses */
static void any_trade_modification_cancellation_status_response_message(TradeModificationCancellationStatusResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = arbitrary(); }
  record->trd_mod_cxl_bit = arbitrary();
  record->reserved_1 = arbitrary();
}

/* Trade Modification Cancellation Status Response Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_trade_modification_cancellation_status_response_message(const TradeModificationCancellationStatusResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_id[i]; }
  wire[at++] = record->trd_mod_cxl_bit;
  wire[at++] = record->reserved_1;

  return at;
}

/* Trade Modification Cancellation Status Response Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_trade_modification_cancellation_status_response_message(TradeModificationCancellationStatusResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->user_id[i] = wire[at++]; }
  record->trd_mod_cxl_bit = wire[at++];
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Trade Modification Cancellation Status Response Message is what was written, byte for byte */
static void equal_trade_modification_cancellation_status_response_message(const TradeModificationCancellationStatusResponseMessage *read, const TradeModificationCancellationStatusResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->user_id[i] == written->user_id[i]); }
  assert(read->trd_mod_cxl_bit == written->trd_mod_cxl_bit);
  assert(read->reserved_1 == written->reserved_1);
}

/* Trade Modification Cancellation Status Response Message: written and read back, then read and written back */
static void check_trade_modification_cancellation_status_response_message(void) {
  TradeModificationCancellationStatusResponseMessage sent;
  TradeModificationCancellationStatusResponseMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_trade_modification_cancellation_status_response_message(&sent);
  assert(encode_trade_modification_cancellation_status_response_message(&sent, wire, 0) == 6);
  assert(decode_trade_modification_cancellation_status_response_message(&got, wire, 0) == 6);
  equal_trade_modification_cancellation_status_response_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_modification_cancellation_status_response_message(&got, wire, 0) == 6);
  assert(encode_trade_modification_cancellation_status_response_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Inner Header: 40 bytes -------------------------------------------------- */

/* Forty byte header prefacing each downloaded record */
typedef struct {
  uint8_t inner_trader_id[4];         /* bytes 0 to 3 */
  uint8_t inner_log_time[4];          /* bytes 4 to 7 */
  uint8_t inner_alpha_char[2];        /* bytes 8 to 9 */
  uint8_t inner_transaction_code[2];  /* bytes 10 to 11 */
  uint8_t inner_error_code[2];        /* bytes 12 to 13 */
  uint8_t inner_timestamp[8];         /* bytes 14 to 21 */
  uint8_t inner_time_stamp_1[8];      /* bytes 22 to 29 */
  uint8_t inner_time_stamp_2[8];      /* bytes 30 to 37 */
  uint8_t inner_message_length[2];    /* bytes 38 to 39 */
} InnerHeader;

/* any Inner Header at all: every byte one the checker chooses */
static void any_inner_header(InnerHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = arbitrary(); }
}

/* Inner Header to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_inner_header(const InnerHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->inner_log_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_alpha_char[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_transaction_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_error_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->inner_time_stamp_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inner_message_length[i]; }

  return at;
}

/* Inner Header off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_inner_header(InnerHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->inner_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->inner_log_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_alpha_char[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_transaction_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->inner_time_stamp_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inner_message_length[i] = wire[at++]; }

  return at;
}

/* what was read of Inner Header is what was written, byte for byte */
static void equal_inner_header(const InnerHeader *read, const InnerHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->inner_trader_id[i] == written->inner_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->inner_log_time[i] == written->inner_log_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_alpha_char[i] == written->inner_alpha_char[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_transaction_code[i] == written->inner_transaction_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_error_code[i] == written->inner_error_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_timestamp[i] == written->inner_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_1[i] == written->inner_time_stamp_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->inner_time_stamp_2[i] == written->inner_time_stamp_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inner_message_length[i] == written->inner_message_length[i]); }
}

/* Inner Header: written and read back, then read and written back */
static void check_inner_header(void) {
  InnerHeader sent;
  InnerHeader got;
  uint8_t wire[40];
  uint8_t again[40];

  any_inner_header(&sent);
  assert(encode_inner_header(&sent, wire, 0) == 40);
  assert(decode_inner_header(&got, wire, 0) == 40);
  equal_inner_header(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_inner_header(&got, wire, 0) == 40);
  assert(encode_inner_header(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_cancel_on_logout_status_response_message();
  check_sec_info();
  check_error_response_message();
  check_box_sign_on_response_message();
  check_existing_encryption_tail();
  check_new_encryption_tail();
  check_control_message_to_trader_message();
  check_password_reset_out_message();
  check_trade_inquiry_out_message();
  check_update_local_database_header_message();
  check_update_local_database_trailer_message();
  check_user_unlock_approval_rejection_message();
  check_user_unlock_requested_response_message();
  check_trade_modification_cancellation_status_response_message();
  check_inner_header();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
