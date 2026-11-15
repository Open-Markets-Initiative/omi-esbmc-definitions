// cboe/neoequities/spinserver/NeoEquities_SpinServer_v1_0_13.c
/*
 * Chicago Board Options Exchange Spin Server
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

/* The first message the Member process sends to the Spin Server after connection to the Spin Server is established. Failure to login before sending any other message type will result in the connection being dropped by the Spin Server. The format is identical to the GRP Login message. */
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

/* Sent by the Spin Server to a Member's process in response to a Login message. The Status field reflects an accepted login or the reason the session was not accepted. If login fails, the connection will be dropped after the Login Response message is sent. */
typedef struct {
  uint8_t status;  /* byte 0 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->status = arbitrary();
}

/* Login Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status;

  return at;
}

/* Login Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->status = wire[at++];

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->status == written->status);
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

/* Sent once per second and indicates through what sequence number a spin is available. */
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

/* Used by a Member's process to request transmission of a spin of the unit's order book. */
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

/* Sent in response to a Member's Spin Request message indicating whether a spin will be sent. */
typedef struct {
  uint8_t sequence[4];     /* bytes 0 to 3 */
  uint8_t order_count[4];  /* bytes 4 to 7 */
  uint8_t status;          /* byte 8 */
} SpinResponseMessage;

/* any Spin Response Message at all: every byte one the checker chooses */
static void any_spin_response_message(SpinResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Spin Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_spin_response_message(const SpinResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_count[i]; }
  wire[at++] = record->status;

  return at;
}

/* Spin Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_spin_response_message(SpinResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_count[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Spin Response Message is what was written, byte for byte */
static void equal_spin_response_message(const SpinResponseMessage *read, const SpinResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_count[i] == written->order_count[i]); }
  assert(read->status == written->status);
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

/* Indicates that all messages for the spin requested have been sent. A Spin Finished message is only sent if a Spin Request was not rejected. Upon receipt of a Spin Finished message, any buffered multicast messages should be applied to the Member's copy of the book to make it current. */
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

/* Used by a Member's process to request transmission of this unit's Instrument Directory messages. */
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

/* Indicates whether a spin will be sent in response to a Member's Instrument Definition Request message. */
typedef struct {
  uint8_t sequence[4];          /* bytes 0 to 3 */
  uint8_t instrument_count[4];  /* bytes 4 to 7 */
  uint8_t status;               /* byte 8 */
} InstrumentDefinitionResponseMessage;

/* any Instrument Definition Response Message at all: every byte one the checker chooses */
static void any_instrument_definition_response_message(InstrumentDefinitionResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_count[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Instrument Definition Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_instrument_definition_response_message(const InstrumentDefinitionResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_count[i]; }
  wire[at++] = record->status;

  return at;
}

/* Instrument Definition Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_instrument_definition_response_message(InstrumentDefinitionResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_count[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Instrument Definition Response Message is what was written, byte for byte */
static void equal_instrument_definition_response_message(const InstrumentDefinitionResponseMessage *read, const InstrumentDefinitionResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_count[i] == written->instrument_count[i]); }
  assert(read->status == written->status);
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

/* ---- Trade Replay Request Message: 4 bytes ----------------------------------- */

/* Used by a Member's process to request transmission of this unit's Trade, Trade Break, and Trade Correction messages. Note Order Executed messages will be converted to Trade messages. */
typedef struct {
  uint8_t sequence[4];  /* bytes 0 to 3 */
} TradeReplayRequestMessage;

/* any Trade Replay Request Message at all: every byte one the checker chooses */
static void any_trade_replay_request_message(TradeReplayRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
}

/* Trade Replay Request Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_trade_replay_request_message(const TradeReplayRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }

  return at;
}

/* Trade Replay Request Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_trade_replay_request_message(TradeReplayRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Replay Request Message is what was written, byte for byte */
static void equal_trade_replay_request_message(const TradeReplayRequestMessage *read, const TradeReplayRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
}

/* Trade Replay Request Message: written and read back, then read and written back */
static void check_trade_replay_request_message(void) {
  TradeReplayRequestMessage sent;
  TradeReplayRequestMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_trade_replay_request_message(&sent);
  assert(encode_trade_replay_request_message(&sent, wire, 0) == 4);
  assert(decode_trade_replay_request_message(&got, wire, 0) == 4);
  equal_trade_replay_request_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_replay_request_message(&got, wire, 0) == 4);
  assert(encode_trade_replay_request_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Replay Response Message: 13 bytes --------------------------------- */

/* Indicates whether a spin will be sent in response to a Member's Trade Replay Request message. */
typedef struct {
  uint8_t sequence[4];     /* bytes 0 to 3 */
  uint8_t trade_count[8];  /* bytes 4 to 11 */
  uint8_t status;          /* byte 12 */
} TradeReplayResponseMessage;

/* any Trade Replay Response Message at all: every byte one the checker chooses */
static void any_trade_replay_response_message(TradeReplayResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_count[i] = arbitrary(); }
  record->status = arbitrary();
}

/* Trade Replay Response Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_trade_replay_response_message(const TradeReplayResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_count[i]; }
  wire[at++] = record->status;

  return at;
}

/* Trade Replay Response Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_trade_replay_response_message(TradeReplayResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_count[i] = wire[at++]; }
  record->status = wire[at++];

  return at;
}

/* what was read of Trade Replay Response Message is what was written, byte for byte */
static void equal_trade_replay_response_message(const TradeReplayResponseMessage *read, const TradeReplayResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence[i] == written->sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_count[i] == written->trade_count[i]); }
  assert(read->status == written->status);
}

/* Trade Replay Response Message: written and read back, then read and written back */
static void check_trade_replay_response_message(void) {
  TradeReplayResponseMessage sent;
  TradeReplayResponseMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_trade_replay_response_message(&sent);
  assert(encode_trade_replay_response_message(&sent, wire, 0) == 13);
  assert(decode_trade_replay_response_message(&got, wire, 0) == 13);
  equal_trade_replay_response_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_replay_response_message(&got, wire, 0) == 13);
  assert(encode_trade_replay_response_message(&got, again, 0) == 13);
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
  check_trade_replay_request_message();
  check_trade_replay_response_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
