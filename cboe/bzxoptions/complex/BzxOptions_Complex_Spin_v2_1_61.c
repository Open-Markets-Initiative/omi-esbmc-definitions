// cboe/bzxoptions/complex/BzxOptions_Complex_Spin_v2_1_61.c
/*
 * Chicago Board Options Exchange Complex
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

/* The Spin Finished message is sent to indicate that all messages for the spin requested have been sent. A Spin Finished message is only sent if a Spin Request was not rejected. Upon receipt of a Spin Finished message, any buffered multicast messages should be applied to the customer's copy of the book to make it current. */
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

/* The Instrument Definition Request message is used by a user's process to request transmission of this unit's Symbol Mappings and Complex Instrument Definitions. All Symbol Mapping messages will be sent before Complex Instrument Definition Expanded and Exchange Designated Complex Instrument Definition messages. */
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

/* A Time message is immediately generated and sent when there is a PITCH event for a given clock second. If there is no PITCH event for a given clock second, then no Time message is sent for that second. All subsequent time offset fields for the same unit will use the new Time value as the base until another Time message is received for the same unit. */
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

/* ---- Symbol Mapping Message: 36 bytes ---------------------------------------- */

/* A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. These messages are not sequenced (sequence = 0) and are sent continuously through the day at variable rates as bandwidth allows. */
typedef struct {
  uint8_t feed_symbol[6];    /* bytes 0 to 5 */
  uint8_t osi_symbol[21];    /* bytes 6 to 26 */
  uint8_t symbol_condition;  /* byte 27 */
  uint8_t underlying[8];     /* bytes 28 to 35 */
} SymbolMappingMessage;

/* any Symbol Mapping Message at all: every byte one the checker chooses */
static void any_symbol_mapping_message(SymbolMappingMessage *record) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = arbitrary(); }
  record->symbol_condition = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = arbitrary(); }
}

/* Symbol Mapping Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_symbol_mapping_message(const SymbolMappingMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->feed_symbol[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->osi_symbol[i]; }
  wire[at++] = record->symbol_condition;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->underlying[i]; }

  return at;
}

/* Symbol Mapping Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_symbol_mapping_message(SymbolMappingMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->feed_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->osi_symbol[i] = wire[at++]; }
  record->symbol_condition = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->underlying[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Mapping Message is what was written, byte for byte */
static void equal_symbol_mapping_message(const SymbolMappingMessage *read, const SymbolMappingMessage *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->feed_symbol[i] == written->feed_symbol[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->osi_symbol[i] == written->osi_symbol[i]); }
  assert(read->symbol_condition == written->symbol_condition);
  for (size_t i = 0; i < 8; i++) { assert(read->underlying[i] == written->underlying[i]); }
}

/* Symbol Mapping Message: written and read back, then read and written back */
static void check_symbol_mapping_message(void) {
  SymbolMappingMessage sent;
  SymbolMappingMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_symbol_mapping_message(&sent);
  assert(encode_symbol_mapping_message(&sent, wire, 0) == 36);
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  equal_symbol_mapping_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_mapping_message(&got, wire, 0) == 36);
  assert(encode_symbol_mapping_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Long Message: 32 bytes ---------------------------------------- */

/* An Add Order message represents a newly accepted visible order on the Cboe complex book. It includes a day-specific Order Id assigned by Cboe to the complex order. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t order_id[8];               /* bytes 4 to 11 */
  uint8_t side_indicator;            /* byte 12 */
  uint8_t quantity_long[4];          /* bytes 13 to 16 */
  uint8_t complex_instrument_id[6];  /* bytes 17 to 22 */
  uint8_t signed_price_long[8];      /* bytes 23 to 30 */
  uint8_t reserved_1;                /* byte 31 */
} AddOrderLongMessage;

/* any Add Order Long Message at all: every byte one the checker chooses */
static void any_add_order_long_message(AddOrderLongMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Long Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_add_order_long_message(const AddOrderLongMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_long[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->signed_price_long[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Long Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_add_order_long_message(AddOrderLongMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_long[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->signed_price_long[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Long Message is what was written, byte for byte */
static void equal_add_order_long_message(const AddOrderLongMessage *read, const AddOrderLongMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_long[i] == written->quantity_long[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id[i] == written->complex_instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->signed_price_long[i] == written->signed_price_long[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Long Message: written and read back, then read and written back */
static void check_add_order_long_message(void) {
  AddOrderLongMessage sent;
  AddOrderLongMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_add_order_long_message(&sent);
  assert(encode_add_order_long_message(&sent, wire, 0) == 32);
  assert(decode_add_order_long_message(&got, wire, 0) == 32);
  equal_add_order_long_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_long_message(&got, wire, 0) == 32);
  assert(encode_add_order_long_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Add Order Short Message: 24 bytes --------------------------------------- */

/* An Add Order Short message represents a newly accepted visible order on the Cboe complex book whose Price fits in a Binary Signed Short Price and Quantity fits in an unsigned 16-bit integer. */
typedef struct {
  uint8_t time_offset[4];            /* bytes 0 to 3 */
  uint8_t order_id[8];               /* bytes 4 to 11 */
  uint8_t side_indicator;            /* byte 12 */
  uint8_t quantity_short[2];         /* bytes 13 to 14 */
  uint8_t complex_instrument_id[6];  /* bytes 15 to 20 */
  uint8_t signed_price_short[2];     /* bytes 21 to 22 */
  uint8_t reserved_1;                /* byte 23 */
} AddOrderShortMessage;

/* any Add Order Short Message at all: every byte one the checker chooses */
static void any_add_order_short_message(AddOrderShortMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->side_indicator = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Add Order Short Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_add_order_short_message(const AddOrderShortMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side_indicator;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quantity_short[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_instrument_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->signed_price_short[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Add Order Short Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_add_order_short_message(AddOrderShortMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->side_indicator = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->quantity_short[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->signed_price_short[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Add Order Short Message is what was written, byte for byte */
static void equal_add_order_short_message(const AddOrderShortMessage *read, const AddOrderShortMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side_indicator == written->side_indicator);
  for (size_t i = 0; i < 2; i++) { assert(read->quantity_short[i] == written->quantity_short[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_instrument_id[i] == written->complex_instrument_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->signed_price_short[i] == written->signed_price_short[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Add Order Short Message: written and read back, then read and written back */
static void check_add_order_short_message(void) {
  AddOrderShortMessage sent;
  AddOrderShortMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_add_order_short_message(&sent);
  assert(encode_add_order_short_message(&sent, wire, 0) == 24);
  assert(decode_add_order_short_message(&got, wire, 0) == 24);
  equal_add_order_short_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_short_message(&got, wire, 0) == 24);
  assert(encode_add_order_short_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Status Message: 16 bytes ---------------------------------------- */

/* The Trading Status message is used to indicate the current trading status of a complex instrument. A Trading Status message will be sent whenever a complex instrument trading status changes. The Trading Status field will be used to represent the status of the RTH (9:30 a.m. ET - 4:15 p.m. ET) and Curb sessions. The GTH Trading Status field will be used to represent the status of series that trade during the GTH session (C1 Only). The GTH session runs from 8:15 p.m. to 9:25 a.m. ET for SPX and VIX series (C1 only). */
typedef struct {
  uint8_t time_offset[4];        /* bytes 0 to 3 */
  uint8_t complex_symbol_id[6];  /* bytes 4 to 9 */
  uint8_t reserved_2[2];         /* bytes 10 to 11 */
  uint8_t trading_status;        /* byte 12 */
  uint8_t reserved_1;            /* byte 13 */
  uint8_t gth_trading_status;    /* byte 14 */
  uint8_t second_reserved_1;     /* byte 15 */
} TradingStatusMessage;

/* any Trading Status Message at all: every byte one the checker chooses */
static void any_trading_status_message(TradingStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->complex_symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->trading_status = arbitrary();
  record->reserved_1 = arbitrary();
  record->gth_trading_status = arbitrary();
  record->second_reserved_1 = arbitrary();
}

/* Trading Status Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_trading_status_message(const TradingStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_offset[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->complex_symbol_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->trading_status;
  wire[at++] = record->reserved_1;
  wire[at++] = record->gth_trading_status;
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Trading Status Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_trading_status_message(TradingStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time_offset[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->complex_symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->trading_status = wire[at++];
  record->reserved_1 = wire[at++];
  record->gth_trading_status = wire[at++];
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Status Message is what was written, byte for byte */
static void equal_trading_status_message(const TradingStatusMessage *read, const TradingStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time_offset[i] == written->time_offset[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->complex_symbol_id[i] == written->complex_symbol_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->trading_status == written->trading_status);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->gth_trading_status == written->gth_trading_status);
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
  check_symbol_mapping_message();
  check_add_order_long_message();
  check_add_order_short_message();
  check_trading_status_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
