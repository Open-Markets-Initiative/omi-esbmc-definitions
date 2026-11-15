// cboe/cxaequities/multicastdepthofbook/CxaEquities_MulticastDepthOfBook_Spin_v1_0_12.c
/*
 * Chicago Board Options Exchange Multicast Depth Of Book
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
 *   - a Reassemble rule
 *   - a run filling what frames it
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

/* ---- Packet Header: 8 bytes -------------------------------------------------- */

typedef struct {
  uint8_t length[2];      /* bytes 0 to 1 */
  uint8_t message_count;  /* byte 2 */
  uint8_t unit;           /* byte 3 */
  uint8_t sequence[4];    /* bytes 4 to 7 */
} PacketHeader;

/* any Packet Header at all: every byte one the checker chooses */
static void any_packet_header(PacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = arbitrary(); }
  record->message_count = arbitrary();
  record->unit = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Packet Header to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_packet_header(const PacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->length[i]; }
  wire[at++] = record->message_count;
  wire[at++] = record->unit;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Packet Header off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_packet_header(PacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->length[i] = wire[at++]; }
  record->message_count = wire[at++];
  record->unit = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Packet Header is what was written, byte for byte */
static void equal_packet_header(const PacketHeader *read, const PacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->length[i] == written->length[i]); }
  assert(read->message_count == written->message_count);
  assert(read->unit == written->unit);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Packet Header: written and read back, then read and written back */
static void check_packet_header(void) {
  PacketHeader sent;
  PacketHeader got;
  uint8_t wire[8];
  uint8_t again[8];

  any_packet_header(&sent);
  assert(encode_packet_header(&sent, wire, 0) == 8);
  assert(decode_packet_header(&got, wire, 0) == 8);
  equal_packet_header(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_packet_header(&got, wire, 0) == 8);
  assert(encode_packet_header(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Header: 2 bytes ------------------------------------------------- */

typedef struct {
  uint8_t message_length;  /* byte 0 */
  uint8_t message_type;    /* byte 1 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  record->message_length = arbitrary();
  record->message_type = arbitrary();
}

/* Message Header to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_length;
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  record->message_length = wire[at++];
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  assert(read->message_length == written->message_length);
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[2];
  uint8_t again[2];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 2);
  assert(decode_message_header(&got, wire, 0) == 2);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 2);
  assert(encode_message_header(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 20 bytes ------------------------------------------------- */

/* First message sent to the Spin Server by the client process after the connection to the Spin Server is established. Failure to login before sending any other message type will result in the connection being dropped by the Spin Server. Identical format to the GRP Login message. */
typedef struct {
  uint8_t session_sub_id[4];  /* bytes 0 to 3 */
  uint8_t username[4];        /* bytes 4 to 7 */
  uint8_t filler[2];          /* bytes 8 to 9 */
  uint8_t password[10];       /* bytes 10 to 19 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->session_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
}

/* Login Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_sub_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->filler[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }

  return at;
}

/* Login Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->session_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->filler[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->session_sub_id[i] == written->session_sub_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->filler[i] == written->filler[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 20);
  assert(decode_login_message(&got, wire, 0) == 20);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 20);
  assert(encode_login_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 1 byte ------------------------------------------ */

/* Sent by the Spin Server to the client process in response to a Login message. The Status field reflects an accepted login or the reason the session was not accepted. If login fails, the connection will be dropped after the Login Response message is sent. */
typedef struct {
  uint8_t login_response_status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->login_response_status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_response_status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->login_response_status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->login_response_status == written->login_response_status);
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 1);
  assert(decode_login_response_message(&got, wire, 0) == 1);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 1);
  assert(encode_login_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Image Available Message: 4 bytes ----------------------------------- */

/* Sent once per second by the Spin Server, indicating through what sequence number a spin is available. */
typedef struct {
  uint8_t sequence[4];  /* bytes 0 to 3 */
} SpinImageAvailableMessage;

/* any Spin Image Available Message at all: every byte one the checker chooses */
static void any_spin_image_available_message(SpinImageAvailableMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Spin Image Available Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_spin_image_available_message(const SpinImageAvailableMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Spin Image Available Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_spin_image_available_message(SpinImageAvailableMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Spin Image Available Message is what was written, byte for byte */
static void equal_spin_image_available_message(const SpinImageAvailableMessage *read, const SpinImageAvailableMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Spin Image Available Message: written and read back, then read and written back */
static void check_spin_image_available_message(void) {
  SpinImageAvailableMessage sent;
  SpinImageAvailableMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_spin_image_available_message(&sent);
  assert(encode_spin_image_available_message(&sent, wire, 0) == 4);
  assert(decode_spin_image_available_message(&got, wire, 0) == 4);
  equal_spin_image_available_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_image_available_message(&got, wire, 0) == 4);
  assert(encode_spin_image_available_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Request Message: 4 bytes ------------------------------------------- */

/* Used by a client's process to request transmission of a spin of the unit's order book. */
typedef struct {
  uint8_t sequence[4];  /* bytes 0 to 3 */
} SpinRequestMessage;

/* any Spin Request Message at all: every byte one the checker chooses */
static void any_spin_request_message(SpinRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Spin Request Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_spin_request_message(const SpinRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Spin Request Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_spin_request_message(SpinRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Spin Request Message is what was written, byte for byte */
static void equal_spin_request_message(const SpinRequestMessage *read, const SpinRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Spin Request Message: written and read back, then read and written back */
static void check_spin_request_message(void) {
  SpinRequestMessage sent;
  SpinRequestMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_spin_request_message(&sent);
  assert(encode_spin_request_message(&sent, wire, 0) == 4);
  assert(decode_spin_request_message(&got, wire, 0) == 4);
  equal_spin_request_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_request_message(&got, wire, 0) == 4);
  assert(encode_spin_request_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Response Message: 9 bytes ------------------------------------------ */

/* Sent by the Spin Server in response to a client's Spin Request message indicating whether a spin will be sent. */
typedef struct {
  uint8_t sequence[4];           /* bytes 0 to 3 */
  uint8_t order_count[4];        /* bytes 4 to 7 */
  uint8_t spin_response_status;  /* byte 8 */
} SpinResponseMessage;

/* any Spin Response Message at all: every byte one the checker chooses */
static void any_spin_response_message(SpinResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = arbitrary(); }
  record->spin_response_status = arbitrary();
}

/* Spin Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_spin_response_message(const SpinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_count[i]; }
  wire[at++] = record->spin_response_status;

  return at;
}

/* Spin Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_spin_response_message(SpinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = wire[at++]; }
  record->spin_response_status = wire[at++];

  return at;
}

/* what was read of Spin Response Message is what was written, byte for byte */
static void equal_spin_response_message(const SpinResponseMessage *read, const SpinResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_count[i] == written->order_count[i]); }
  assert(read->spin_response_status == written->spin_response_status);
}

/* Spin Response Message: written and read back, then read and written back */
static void check_spin_response_message(void) {
  SpinResponseMessage sent;
  SpinResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_spin_response_message(&sent);
  assert(encode_spin_response_message(&sent, wire, 0) == 9);
  assert(decode_spin_response_message(&got, wire, 0) == 9);
  equal_spin_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_response_message(&got, wire, 0) == 9);
  assert(encode_spin_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Spin Finished Message: 4 bytes ------------------------------------------ */

/* Sent to indicate that all messages for the spin requested have been sent. A Spin Finished message is only sent if a Spin Request was not rejected. Upon receipt, any buffered multicast messages should be applied to the client's copy of the book to make it current. */
typedef struct {
  uint8_t sequence[4];  /* bytes 0 to 3 */
} SpinFinishedMessage;

/* any Spin Finished Message at all: every byte one the checker chooses */
static void any_spin_finished_message(SpinFinishedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Spin Finished Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_spin_finished_message(const SpinFinishedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Spin Finished Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_spin_finished_message(SpinFinishedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Spin Finished Message is what was written, byte for byte */
static void equal_spin_finished_message(const SpinFinishedMessage *read, const SpinFinishedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Spin Finished Message: written and read back, then read and written back */
static void check_spin_finished_message(void) {
  SpinFinishedMessage sent;
  SpinFinishedMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_spin_finished_message(&sent);
  assert(encode_spin_finished_message(&sent, wire, 0) == 4);
  assert(decode_spin_finished_message(&got, wire, 0) == 4);
  equal_spin_finished_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_spin_finished_message(&got, wire, 0) == 4);
  assert(encode_spin_finished_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 20 bytes ---------------------------------------- */

/* Indicates the current trading status of a security. Included in a spin response so the client can populate trading state for each symbol. */
typedef struct {
  uint8_t timestamp[8];       /* bytes 0 to 7 */
  uint8_t symbol[6];          /* bytes 8 to 13 */
  uint8_t trading_status;     /* byte 14 */
  uint8_t market_id_code[4];  /* bytes 15 to 18 */
  uint8_t reserved_1;         /* byte 19 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->trading_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_id_code[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->trading_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id_code[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Trading Status Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->trading_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_id_code[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->trading_status == written->trading_status);
  for (size_t i = 0; i < 4; i++) { assert(read->market_id_code[i] == written->market_id_code[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 20);
  assert(decode_trading_status_message(&got, wire, 0) == 20);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 20);
  assert(encode_trading_status_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Message: 40 bytes --------------------------------------------- */

/* Represents an open order on the CXA book. Included in a spin response to reconstruct the open order book at the spin sequence number. */
typedef struct {
  uint8_t timestamp[8];    /* bytes 0 to 7 */
  uint8_t order_id[8];     /* bytes 8 to 15 */
  uint8_t side_indicator;  /* byte 16 */
  uint8_t quantity[4];     /* bytes 17 to 20 */
  uint8_t symbol[6];       /* bytes 21 to 26 */
  uint8_t price[8];        /* bytes 27 to 34 */
  uint8_t pid[4];          /* bytes 35 to 38 */
  uint8_t reserved_1;      /* byte 39 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->pid[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pid[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->pid[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->pid[i] == written->pid[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 40);
  assert(decode_add_order_message(&got, wire, 0) == 40);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 40);
  assert(encode_add_order_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Calculated Value Message: 31 bytes -------------------------------------- */

/* Carries the latest calculated market value for a specified symbol. Included in a spin response so the client can populate the latest index, iNAV, or closing price value. */
typedef struct {
  uint8_t timestamp[8];        /* bytes 0 to 7 */
  uint8_t symbol[6];           /* bytes 8 to 13 */
  uint8_t value_category;      /* byte 14 */
  uint8_t value[8];            /* bytes 15 to 22 */
  uint8_t value_timestamp[8];  /* bytes 23 to 30 */
} CalculatedValueMessage;

/* any Calculated Value Message at all: every byte one the checker chooses */
static void any_calculated_value_message(CalculatedValueMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->value_category = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->value_timestamp[i] = arbitrary(); }
}

/* Calculated Value Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_calculated_value_message(const CalculatedValueMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->value_category;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->value_timestamp[i]; }

  return at;
}

/* Calculated Value Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_calculated_value_message(CalculatedValueMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->value_category = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->value_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Calculated Value Message is what was written, byte for byte */
static void equal_calculated_value_message(const CalculatedValueMessage *read, const CalculatedValueMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->value_category == written->value_category);
  for (size_t i = 0; i < 8; i++) { assert(read->value[i] == written->value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->value_timestamp[i] == written->value_timestamp[i]); }
}

/* Calculated Value Message: written and read back, then read and written back */
static void check_calculated_value_message(void) {
  CalculatedValueMessage sent;
  CalculatedValueMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_calculated_value_message(&sent);
  assert(encode_calculated_value_message(&sent, wire, 0) == 31);
  assert(decode_calculated_value_message(&got, wire, 0) == 31);
  equal_calculated_value_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_calculated_value_message(&got, wire, 0) == 31);
  assert(encode_calculated_value_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 32 bytes ---------------------------------------- */

/* Provides the latest indicative auction price and eligible shares for a symbol in an overlapping order book state. Included in a spin response so the client can populate the current auction state. */
typedef struct {
  uint8_t timestamp[8];         /* bytes 0 to 7 */
  uint8_t symbol[6];            /* bytes 8 to 13 */
  uint8_t auction_type;         /* byte 14 */
  uint8_t buy_shares[4];        /* bytes 15 to 18 */
  uint8_t sell_shares[4];       /* bytes 19 to 22 */
  uint8_t indicative_price[8];  /* bytes 23 to 30 */
  uint8_t reserved_1;           /* byte 31 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Auction Update Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Auction Update Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 32);
  assert(decode_auction_update_message(&got, wire, 0) == 32);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 32);
  assert(encode_auction_update_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_packet_header();
  check_message_header();
  check_login_message();
  check_login_response_message();
  check_spin_image_available_message();
  check_spin_request_message();
  check_spin_response_message();
  check_spin_finished_message();
  check_trading_status_message();
  check_add_order_message();
  check_calculated_value_message();
  check_auction_update_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
