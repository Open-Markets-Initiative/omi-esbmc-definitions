// cboe/edgxequities/multicastdepthofbook/EdgxEquities_MulticastDepthOfBook_Spin_v2_41_66.c
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

/* The Login message is the first message sent to the Spin Server by a user's process after the connection to the Spin Server is established. Failure to login before sending any other message type will result in the connection being dropped by the Spin Server. The format of the Login message for the Spin Server is identical to that of the GRP. */
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

/* The Login Response message is sent by the Spin Server to a user's process in response to a Login message. The status field is used to reflect an accepted login or the reason the session was not accepted. If login fails, the connection will be dropped after the Login Response message is sent. */
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

/* The Spin Image Available message is sent once per second and indicates through what sequence number a spin is available. */
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

/* The Spin Request message is used by a user's process to request transmission of a spin of the unit's order book. */
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

/* The Spin Response message is sent in response to a user's Spin Request message indicating whether a spin will be sent. */
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

/* The Spin Finished message is sent to indicate that all messages for the spin requested have been sent. A Spin Finished message is only sent if a Spin Request was not rejected. Upon receipt of a Spin Finished message, any buffered multicast messages should be applied to the member's copy of the book to make it current. */
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

/* ---- Instrument Definition Request Message: 4 bytes -------------------------- */

/* The Instrument Definition Request message is used by a user's process to request transmission of this unit's Symbol Mappings and Complex Instrument Definitions. Included for consistency with the Options Spin Server; not typically used on Equities feeds. */
typedef struct {
  uint8_t sequence[4];  /* bytes 0 to 3 */
} InstrumentDefinitionRequestMessage;

/* any Instrument Definition Request Message at all: every byte one the checker chooses */
static void any_instrument_definition_request_message(InstrumentDefinitionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Instrument Definition Request Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_instrument_definition_request_message(const InstrumentDefinitionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Instrument Definition Request Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_instrument_definition_request_message(InstrumentDefinitionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Definition Request Message is what was written, byte for byte */
static void equal_instrument_definition_request_message(const InstrumentDefinitionRequestMessage *read, const InstrumentDefinitionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Instrument Definition Request Message: written and read back, then read and written back */
static void check_instrument_definition_request_message(void) {
  InstrumentDefinitionRequestMessage sent;
  InstrumentDefinitionRequestMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_instrument_definition_request_message(&sent);
  assert(encode_instrument_definition_request_message(&sent, wire, 0) == 4);
  assert(decode_instrument_definition_request_message(&got, wire, 0) == 4);
  equal_instrument_definition_request_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_definition_request_message(&got, wire, 0) == 4);
  assert(encode_instrument_definition_request_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Definition Response Message: 9 bytes ------------------------- */

/* The Instrument Definition Response message is sent in response to a user's Instrument Definition Request message indicating whether a spin will be sent. */
typedef struct {
  uint8_t sequence[4];                            /* bytes 0 to 3 */
  uint8_t instrument_count[4];                    /* bytes 4 to 7 */
  uint8_t instrument_definition_response_status;  /* byte 8 */
} InstrumentDefinitionResponseMessage;

/* any Instrument Definition Response Message at all: every byte one the checker chooses */
static void any_instrument_definition_response_message(InstrumentDefinitionResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_count[i] = arbitrary(); }
  record->instrument_definition_response_status = arbitrary();
}

/* Instrument Definition Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_instrument_definition_response_message(const InstrumentDefinitionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_count[i]; }
  wire[at++] = record->instrument_definition_response_status;

  return at;
}

/* Instrument Definition Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_instrument_definition_response_message(InstrumentDefinitionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_count[i] = wire[at++]; }
  record->instrument_definition_response_status = wire[at++];

  return at;
}

/* what was read of Instrument Definition Response Message is what was written, byte for byte */
static void equal_instrument_definition_response_message(const InstrumentDefinitionResponseMessage *read, const InstrumentDefinitionResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_count[i] == written->instrument_count[i]); }
  assert(read->instrument_definition_response_status == written->instrument_definition_response_status);
}

/* Instrument Definition Response Message: written and read back, then read and written back */
static void check_instrument_definition_response_message(void) {
  InstrumentDefinitionResponseMessage sent;
  InstrumentDefinitionResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_instrument_definition_response_message(&sent);
  assert(encode_instrument_definition_response_message(&sent, wire, 0) == 9);
  assert(decode_instrument_definition_response_message(&got, wire, 0) == 9);
  equal_instrument_definition_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_definition_response_message(&got, wire, 0) == 9);
  assert(encode_instrument_definition_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time Message: 4 bytes --------------------------------------------------- */

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second. If there is no PITCH event for a given clock second, then no Time message is sent for that second. The Time field is the number of seconds relative to midnight Eastern Time. All subsequent time offset fields for the same unit will use the new Time message value as the base until another Time message is received for the same unit. */
typedef struct {
  uint8_t time[4];  /* bytes 0 to 3 */
} TimeMessage;

/* any Time Message at all: every byte one the checker chooses */
static void any_time_message(TimeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
}

/* Time Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time_message(const TimeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* Time Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time_message(TimeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of Time Message is what was written, byte for byte */
static void equal_time_message(const TimeMessage *read, const TimeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
}

/* Time Message: written and read back, then read and written back */
static void check_time_message(void) {
  TimeMessage sent;
  TimeMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time_message(&sent);
  assert(encode_time_message(&sent, wire, 0) == 4);
  assert(decode_time_message(&got, wire, 0) == 4);
  equal_time_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time_message(&got, wire, 0) == 4);
  assert(encode_time_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Unit Clear Message: 4 bytes --------------------------------------------- */

/* The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header message. For Equities only, this message will be sent at startup each day. It would also be distributed in certain recovery events such as a data center fail-over. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} UnitClearMessage;

/* any Unit Clear Message at all: every byte one the checker chooses */
static void any_unit_clear_message(UnitClearMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* Unit Clear Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_unit_clear_message(const UnitClearMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* Unit Clear Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_unit_clear_message(UnitClearMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of Unit Clear Message is what was written, byte for byte */
static void equal_unit_clear_message(const UnitClearMessage *read, const UnitClearMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* Unit Clear Message: written and read back, then read and written back */
static void check_unit_clear_message(void) {
  UnitClearMessage sent;
  UnitClearMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_unit_clear_message(&sent);
  assert(encode_unit_clear_message(&sent, wire, 0) == 4);
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  equal_unit_clear_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_unit_clear_message(&got, wire, 0) == 4);
  assert(encode_unit_clear_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed Message: 24 bytes ---------------------------------------- */

/* Order Executed messages are sent when a visible order on the Cboe book is executed in whole or in part. The execution price equals the limit order price found in the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t order_id[8];           /* bytes 4 to 11 */
  uint8_t executed_quantity[4];  /* bytes 12 to 15 */
  uint8_t execution_id[8];       /* bytes 16 to 23 */
} OrderExecutedMessage;

/* any Order Executed Message at all: every byte one the checker chooses */
static void any_order_executed_message(OrderExecutedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Order Executed Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_message(const OrderExecutedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Order Executed Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_message(OrderExecutedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed Message is what was written, byte for byte */
static void equal_order_executed_message(const OrderExecutedMessage *read, const OrderExecutedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Order Executed Message: written and read back, then read and written back */
static void check_order_executed_message(void) {
  OrderExecutedMessage sent;
  OrderExecutedMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_executed_message(&sent);
  assert(encode_order_executed_message(&sent, wire, 0) == 24);
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  equal_order_executed_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_message(&got, wire, 0) == 24);
  assert(encode_order_executed_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Executed At Price Size Message: 36 bytes -------------------------- */

/* Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id. If the Remaining Quantity field contains a 0 the order should be completely removed from the book. */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t order_id[8];            /* bytes 4 to 11 */
  uint8_t executed_quantity[4];   /* bytes 12 to 15 */
  uint8_t remaining_quantity[4];  /* bytes 16 to 19 */
  uint8_t execution_id[8];        /* bytes 20 to 27 */
  uint8_t price_long[8];          /* bytes 28 to 35 */
} OrderExecutedAtPriceSizeMessage;

/* any Order Executed At Price Size Message at all: every byte one the checker chooses */
static void any_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
}

/* Order Executed At Price Size Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executed_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->remaining_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }

  return at;
}

/* Order Executed At Price Size Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_order_executed_at_price_size_message(OrderExecutedAtPriceSizeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executed_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->remaining_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }

  return at;
}

/* what was read of Order Executed At Price Size Message is what was written, byte for byte */
static void equal_order_executed_at_price_size_message(const OrderExecutedAtPriceSizeMessage *read, const OrderExecutedAtPriceSizeMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executed_quantity[i] == written->executed_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->remaining_quantity[i] == written->remaining_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
}

/* Order Executed At Price Size Message: written and read back, then read and written back */
static void check_order_executed_at_price_size_message(void) {
  OrderExecutedAtPriceSizeMessage sent;
  OrderExecutedAtPriceSizeMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_order_executed_at_price_size_message(&sent);
  assert(encode_order_executed_at_price_size_message(&sent, wire, 0) == 36);
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 36);
  equal_order_executed_at_price_size_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_order_executed_at_price_size_message(&got, wire, 0) == 36);
  assert(encode_order_executed_at_price_size_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Long Message: 16 bytes -------------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced. */
typedef struct {
  uint8_t time_offset[4];             /* bytes 0 to 3 */
  uint8_t order_id[8];                /* bytes 4 to 11 */
  uint8_t canceled_quantity_long[4];  /* bytes 12 to 15 */
} ReduceSizeLongMessage;

/* any Reduce Size Long Message at all: every byte one the checker chooses */
static void any_reduce_size_long_message(ReduceSizeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = arbitrary(); }
}

/* Reduce Size Long Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_long_message(const ReduceSizeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_quantity_long[i]; }

  return at;
}

/* Reduce Size Long Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_long_message(ReduceSizeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_quantity_long[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Long Message is what was written, byte for byte */
static void equal_reduce_size_long_message(const ReduceSizeLongMessage *read, const ReduceSizeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_quantity_long[i] == written->canceled_quantity_long[i]); }
}

/* Reduce Size Long Message: written and read back, then read and written back */
static void check_reduce_size_long_message(void) {
  ReduceSizeLongMessage sent;
  ReduceSizeLongMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_reduce_size_long_message(&sent);
  assert(encode_reduce_size_long_message(&sent, wire, 0) == 16);
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  equal_reduce_size_long_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_long_message(&got, wire, 0) == 16);
  assert(encode_reduce_size_long_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reduce Size Short Message: 14 bytes ------------------------------------- */

/* Reduce Size messages are sent when a visible order on the Cboe book is partially reduced. */
typedef struct {
  uint8_t time_offset[4];              /* bytes 0 to 3 */
  uint8_t order_id[8];                 /* bytes 4 to 11 */
  uint8_t canceled_quantity_short[2];  /* bytes 12 to 13 */
} ReduceSizeShortMessage;

/* any Reduce Size Short Message at all: every byte one the checker chooses */
static void any_reduce_size_short_message(ReduceSizeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = arbitrary(); }
}

/* Reduce Size Short Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_reduce_size_short_message(const ReduceSizeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->canceled_quantity_short[i]; }

  return at;
}

/* Reduce Size Short Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_reduce_size_short_message(ReduceSizeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->canceled_quantity_short[i] = wire[at++]; }

  return at;
}

/* what was read of Reduce Size Short Message is what was written, byte for byte */
static void equal_reduce_size_short_message(const ReduceSizeShortMessage *read, const ReduceSizeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->canceled_quantity_short[i] == written->canceled_quantity_short[i]); }
}

/* Reduce Size Short Message: written and read back, then read and written back */
static void check_reduce_size_short_message(void) {
  ReduceSizeShortMessage sent;
  ReduceSizeShortMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_reduce_size_short_message(&sent);
  assert(encode_reduce_size_short_message(&sent, wire, 0) == 14);
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  equal_reduce_size_short_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_reduce_size_short_message(&got, wire, 0) == 14);
  assert(encode_reduce_size_short_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 12 bytes ------------------------------------------ */

/* The Delete Order message is sent whenever a booked order is cancelled or leaves the order book. The Order Id refers to the Order Id of the original Add Order message. An order that is deleted from the book may return to the book later under certain circumstances. Therefore, a Delete Order message does not indicate that a given Order Id will not be sent again on a subsequent Add Order message. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
  uint8_t order_id[8];     /* bytes 4 to 11 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 12);
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 12);
  assert(encode_delete_order_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Long Message: 39 bytes -------------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. Trade messages are necessary to calculate Cboe execution-based data. Trade messages do not alter the book and can be ignored if messages are being used solely to build a book. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t quantity_long[4];  /* bytes 13 to 16 */
  uint8_t symbol_short[6];   /* bytes 17 to 22 */
  uint8_t price_long[8];     /* bytes 23 to 30 */
  uint8_t execution_id[8];   /* bytes 31 to 38 */
} TradeLongMessage;

/* any Trade Long Message at all: every byte one the checker chooses */
static void any_trade_long_message(TradeLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Long Message to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_trade_long_message(const TradeLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Long Message off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_trade_long_message(TradeLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Long Message is what was written, byte for byte */
static void equal_trade_long_message(const TradeLongMessage *read, const TradeLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Long Message: written and read back, then read and written back */
static void check_trade_long_message(void) {
  TradeLongMessage sent;
  TradeLongMessage got;
  uint8_t wire[39];
  uint8_t again[39];

  any_trade_long_message(&sent);
  assert(encode_trade_long_message(&sent, wire, 0) == 39);
  assert(decode_trade_long_message(&got, wire, 0) == 39);
  equal_trade_long_message(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_long_message(&got, wire, 0) == 39);
  assert(encode_trade_long_message(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Short Message: 31 bytes ------------------------------------------- */

/* The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t order_id[8];        /* bytes 4 to 11 */
  uint8_t side_indicator;     /* byte 12 */
  uint8_t quantity_short[2];  /* bytes 13 to 14 */
  uint8_t symbol_short[6];    /* bytes 15 to 20 */
  uint8_t price_short[2];     /* bytes 21 to 22 */
  uint8_t execution_id[8];    /* bytes 23 to 30 */
} TradeShortMessage;

/* any Trade Short Message at all: every byte one the checker chooses */
static void any_trade_short_message(TradeShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Short Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_trade_short_message(const TradeShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->symbol_short[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_short[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Short Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_trade_short_message(TradeShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->symbol_short[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_short[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Short Message is what was written, byte for byte */
static void equal_trade_short_message(const TradeShortMessage *read, const TradeShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->symbol_short[i] == written->symbol_short[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_short[i] == written->price_short[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Short Message: written and read back, then read and written back */
static void check_trade_short_message(void) {
  TradeShortMessage sent;
  TradeShortMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_trade_short_message(&sent);
  assert(encode_trade_short_message(&sent, wire, 0) == 31);
  assert(decode_trade_short_message(&got, wire, 0) == 31);
  equal_trade_short_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_short_message(&got, wire, 0) == 31);
  assert(encode_trade_short_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Expanded Message: 41 bytes ---------------------------------------- */

/* The expanded version of the Trade message has been made available to accommodate larger symbol sizes possible through the ISRA plan. */
typedef struct {
  uint8_t time_offset[4];    /* bytes 0 to 3 */
  uint8_t order_id[8];       /* bytes 4 to 11 */
  uint8_t side_indicator;    /* byte 12 */
  uint8_t quantity_long[4];  /* bytes 13 to 16 */
  uint8_t symbol_long[8];    /* bytes 17 to 24 */
  uint8_t price_long[8];     /* bytes 25 to 32 */
  uint8_t execution_id[8];   /* bytes 33 to 40 */
} TradeExpandedMessage;

/* any Trade Expanded Message at all: every byte one the checker chooses */
static void any_trade_expanded_message(TradeExpandedMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Expanded Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_trade_expanded_message(const TradeExpandedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Expanded Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_trade_expanded_message(TradeExpandedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Expanded Message is what was written, byte for byte */
static void equal_trade_expanded_message(const TradeExpandedMessage *read, const TradeExpandedMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Expanded Message: written and read back, then read and written back */
static void check_trade_expanded_message(void) {
  TradeExpandedMessage sent;
  TradeExpandedMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_trade_expanded_message(&sent);
  assert(encode_trade_expanded_message(&sent, wire, 0) == 41);
  assert(decode_trade_expanded_message(&got, wire, 0) == 41);
  equal_trade_expanded_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_expanded_message(&got, wire, 0) == 41);
  assert(encode_trade_expanded_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Break Message: 12 bytes ------------------------------------------- */

/* The Trade Break message is sent whenever an execution on Cboe is broken. Trade breaks are rare and only affect applications that rely upon Cboe execution-based data. Applications that simply build a Cboe book can ignore Trade Break messages. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t execution_id[8];  /* bytes 4 to 11 */
} TradeBreakMessage;

/* any Trade Break Message at all: every byte one the checker chooses */
static void any_trade_break_message(TradeBreakMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = arbitrary(); }
}

/* Trade Break Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trade_break_message(const TradeBreakMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_id[i]; }

  return at;
}

/* Trade Break Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trade_break_message(TradeBreakMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Break Message is what was written, byte for byte */
static void equal_trade_break_message(const TradeBreakMessage *read, const TradeBreakMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_id[i] == written->execution_id[i]); }
}

/* Trade Break Message: written and read back, then read and written back */
static void check_trade_break_message(void) {
  TradeBreakMessage sent;
  TradeBreakMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trade_break_message(&sent);
  assert(encode_trade_break_message(&sent, wire, 0) == 12);
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  equal_trade_break_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_break_message(&got, wire, 0) == 12);
  assert(encode_trade_break_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Session Message: 4 bytes ----------------------------------------- */

/* The End of Session message is sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received. */
typedef struct {
  uint8_t time_offset[4];  /* bytes 0 to 3 */
} EndOfSessionMessage;

/* any End Of Session Message at all: every byte one the checker chooses */
static void any_end_of_session_message(EndOfSessionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
}

/* End Of Session Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_end_of_session_message(const EndOfSessionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }

  return at;
}

/* End Of Session Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_end_of_session_message(EndOfSessionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Session Message is what was written, byte for byte */
static void equal_end_of_session_message(const EndOfSessionMessage *read, const EndOfSessionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
}

/* End Of Session Message: written and read back, then read and written back */
static void check_end_of_session_message(void) {
  EndOfSessionMessage sent;
  EndOfSessionMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_end_of_session_message(&sent);
  assert(encode_end_of_session_message(&sent, wire, 0) == 4);
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  equal_end_of_session_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_session_message(&got, wire, 0) == 4);
  assert(encode_end_of_session_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a security. A Trading Status message will be sent whenever a security's trading status changes. Trading Status of S is to be implied at system startup for all symbols. Sequenced Trading Status messages are sent upon system start up for all active securities with Trading Status = 'S' (suspended). Trading Status messages will continue to be published upon symbol state changes, such as at the beginning of order acceptance. */
typedef struct {
  uint8_t time_offset[4];     /* bytes 0 to 3 */
  uint8_t symbol_long[8];     /* bytes 4 to 11 */
  uint8_t trading_status;     /* byte 12 */
  uint8_t reg_sho_action;     /* byte 13 */
  uint8_t reserved_1;         /* byte 14 */
  uint8_t second_reserved_1;  /* byte 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reg_sho_action = arbitrary();
  record->reserved_1 = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reg_sho_action;
  wire[at++] = record->reserved_1;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reg_sho_action = wire[at++];
  record->reserved_1 = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reg_sho_action == written->reg_sho_action);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Trading Status Message: written and read back, then read and written back */
static void check_trading_status_message(void) {
  TradingStatusMessage sent;
  TradingStatusMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_trading_status_message(&sent);
  assert(encode_trading_status_message(&sent, wire, 0) == 16);
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  equal_trading_status_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_status_message(&got, wire, 0) == 16);
  assert(encode_trading_status_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Update Message: 45 bytes ---------------------------------------- */

/* BYX and BZX Equities Only. Auction Update messages are used to disseminate Cboe price and size information during auctions for Cboe listed securities and for Cboe Market Close (CMC) crosses on BZX, and for Periodic Auctions on BYX. This is the BZX Equities layout (Table 31). */
typedef struct {
  uint8_t time_offset[4];         /* bytes 0 to 3 */
  uint8_t stock_symbol[8];        /* bytes 4 to 11 */
  uint8_t auction_type;           /* byte 12 */
  uint8_t reference_price[8];     /* bytes 13 to 20 */
  uint8_t buy_shares[4];          /* bytes 21 to 24 */
  uint8_t sell_shares[4];         /* bytes 25 to 28 */
  uint8_t indicative_price[8];    /* bytes 29 to 36 */
  uint8_t auction_only_price[8];  /* bytes 37 to 44 */
} AuctionUpdateMessage;

/* any Auction Update Message at all: every byte one the checker chooses */
static void any_auction_update_message(AuctionUpdateMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = arbitrary(); }
}

/* Auction Update Message to the wire: 45 bytes from at, returning where the next byte goes */
static size_t encode_auction_update_message(const AuctionUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->buy_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sell_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->indicative_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_only_price[i]; }

  return at;
}

/* Auction Update Message off the wire: 45 bytes from at, returning where the next byte lies */
static size_t decode_auction_update_message(AuctionUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->buy_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sell_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->indicative_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_only_price[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Update Message is what was written, byte for byte */
static void equal_auction_update_message(const AuctionUpdateMessage *read, const AuctionUpdateMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->buy_shares[i] == written->buy_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sell_shares[i] == written->sell_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->indicative_price[i] == written->indicative_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_only_price[i] == written->auction_only_price[i]); }
}

/* Auction Update Message: written and read back, then read and written back */
static void check_auction_update_message(void) {
  AuctionUpdateMessage sent;
  AuctionUpdateMessage got;
  uint8_t wire[45];
  uint8_t again[45];

  any_auction_update_message(&sent);
  assert(encode_auction_update_message(&sent, wire, 0) == 45);
  assert(decode_auction_update_message(&got, wire, 0) == 45);
  equal_auction_update_message(&got, &sent);

  for (size_t i = 0; i < 45; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_update_message(&got, wire, 0) == 45);
  assert(encode_auction_update_message(&got, again, 0) == 45);
  for (size_t i = 0; i < 45; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Summary Message: 25 bytes --------------------------------------- */

/* BYX Equities, BZX Equities, and Options Only. Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security on BZX, the results of an Opening or Re-Opening of any options series on C1, and for Periodic Auctions on BYX. An Auction Summary message will be sent for Cboe Market Close (CMC) once the official closing price for each security is available. */
typedef struct {
  uint8_t time_offset[4];   /* bytes 0 to 3 */
  uint8_t stock_symbol[8];  /* bytes 4 to 11 */
  uint8_t auction_type;     /* byte 12 */
  uint8_t price_long[8];    /* bytes 13 to 20 */
  uint8_t shares[4];        /* bytes 21 to 24 */
} AuctionSummaryMessage;

/* any Auction Summary Message at all: every byte one the checker chooses */
static void any_auction_summary_message(AuctionSummaryMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = arbitrary(); }
  record->auction_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = arbitrary(); }
}

/* Auction Summary Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_auction_summary_message(const AuctionSummaryMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stock_symbol[i]; }
  wire[at++] = record->auction_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares[i]; }

  return at;
}

/* Auction Summary Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_auction_summary_message(AuctionSummaryMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stock_symbol[i] = wire[at++]; }
  record->auction_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->shares[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Summary Message is what was written, byte for byte */
static void equal_auction_summary_message(const AuctionSummaryMessage *read, const AuctionSummaryMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stock_symbol[i] == written->stock_symbol[i]); }
  assert(read->auction_type == written->auction_type);
  for (size_t i = 0; i < 8; i++) { assert(read->price_long[i] == written->price_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->shares[i] == written->shares[i]); }
}

/* Auction Summary Message: written and read back, then read and written back */
static void check_auction_summary_message(void) {
  AuctionSummaryMessage sent;
  AuctionSummaryMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_auction_summary_message(&sent);
  assert(encode_auction_summary_message(&sent, wire, 0) == 25);
  assert(decode_auction_summary_message(&got, wire, 0) == 25);
  equal_auction_summary_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_summary_message(&got, wire, 0) == 25);
  assert(encode_auction_summary_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retail Price Improvement Message: 13 bytes ------------------------------ */

/* BYX and (effective 04/10/26) EDGX Only. The Retail Price Improvement message is a Retail Liquidity Indicator (RLI) that includes symbol and side, but not price and size. An RLI will be disseminated when there is a Retail Price Improving (RPI) order present for a symbol on the Exchange order book OR to indicate a RPI order is no longer available. Cboe will disseminate a Retail Price Improvement message when the resting RPI order is priced better than the NBBO. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t symbol_long[8];            /* bytes 4 to 11 */
  uint8_t retail_price_improvement;  /* byte 12 */
} RetailPriceImprovementMessage;

/* any Retail Price Improvement Message at all: every byte one the checker chooses */
static void any_retail_price_improvement_message(RetailPriceImprovementMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = arbitrary(); }
  record->retail_price_improvement = arbitrary();
}

/* Retail Price Improvement Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_retail_price_improvement_message(const RetailPriceImprovementMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->symbol_long[i]; }
  wire[at++] = record->retail_price_improvement;

  return at;
}

/* Retail Price Improvement Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_retail_price_improvement_message(RetailPriceImprovementMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->symbol_long[i] = wire[at++]; }
  record->retail_price_improvement = wire[at++];

  return at;
}

/* what was read of Retail Price Improvement Message is what was written, byte for byte */
static void equal_retail_price_improvement_message(const RetailPriceImprovementMessage *read, const RetailPriceImprovementMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->symbol_long[i] == written->symbol_long[i]); }
  assert(read->retail_price_improvement == written->retail_price_improvement);
}

/* Retail Price Improvement Message: written and read back, then read and written back */
static void check_retail_price_improvement_message(void) {
  RetailPriceImprovementMessage sent;
  RetailPriceImprovementMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_retail_price_improvement_message(&sent);
  assert(encode_retail_price_improvement_message(&sent, wire, 0) == 13);
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 13);
  equal_retail_price_improvement_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_retail_price_improvement_message(&got, wire, 0) == 13);
  assert(encode_retail_price_improvement_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
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
  check_instrument_definition_request_message();
  check_instrument_definition_response_message();
  check_time_message();
  check_unit_clear_message();
  check_order_executed_message();
  check_order_executed_at_price_size_message();
  check_reduce_size_long_message();
  check_reduce_size_short_message();
  check_delete_order_message();
  check_trade_long_message();
  check_trade_short_message();
  check_trade_expanded_message();
  check_trade_break_message();
  check_end_of_session_message();
  check_trading_status_message();
  check_auction_update_message();
  check_auction_summary_message();
  check_retail_price_improvement_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
