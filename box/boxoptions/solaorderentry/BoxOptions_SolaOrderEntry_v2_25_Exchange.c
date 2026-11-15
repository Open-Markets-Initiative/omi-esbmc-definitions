// box/boxoptions/solaorderentry/BoxOptions_SolaOrderEntry_v2_25_Exchange.c
/*
 * Box Options Market Sola Order Entry
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

/* ---- Outgoing Header: 30 bytes ----------------------------------------------- */

/* The header on all outgoing exchange messages */
typedef struct {
  uint8_t message_type[2];         /* bytes 0 to 1 */
  uint8_t message_timestamp[6];    /* bytes 2 to 7 */
  uint8_t user_sequence_i_d[8];    /* bytes 8 to 15 */
  uint8_t exchange_message_id[6];  /* bytes 16 to 21 */
  uint8_t gap_sequence_i_d[2];     /* bytes 22 to 23 */
  uint8_t system_sequence_i_d[6];  /* bytes 24 to 29 */
} OutgoingHeader;

/* any Outgoing Header at all: every byte one the checker chooses */
static void any_outgoing_header(OutgoingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->message_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->gap_sequence_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->system_sequence_i_d[i] = arbitrary(); }
}

/* Outgoing Header to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_outgoing_header(const OutgoingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->message_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_i_d[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange_message_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->gap_sequence_i_d[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->system_sequence_i_d[i]; }

  return at;
}

/* Outgoing Header off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_outgoing_header(OutgoingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->message_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->gap_sequence_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->system_sequence_i_d[i] = wire[at++]; }

  return at;
}

/* what was read of Outgoing Header is what was written, byte for byte */
static void equal_outgoing_header(const OutgoingHeader *read, const OutgoingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->message_timestamp[i] == written->message_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_i_d[i] == written->user_sequence_i_d[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange_message_id[i] == written->exchange_message_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->gap_sequence_i_d[i] == written->gap_sequence_i_d[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->system_sequence_i_d[i] == written->system_sequence_i_d[i]); }
}

/* Outgoing Header: written and read back, then read and written back */
static void check_outgoing_header(void) {
  OutgoingHeader sent;
  OutgoingHeader got;
  uint8_t wire[30];
  uint8_t again[30];

  any_outgoing_header(&sent);
  assert(encode_outgoing_header(&sent, wire, 0) == 30);
  assert(decode_outgoing_header(&got, wire, 0) == 30);
  equal_outgoing_header(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_outgoing_header(&got, wire, 0) == 30);
  assert(encode_outgoing_header(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Question: 20 bytes -------------------------------------------- */

typedef struct {
  uint8_t first_user_sequence_i_d[8];                       /* bytes 0 to 7 */
  uint8_t last_exchange_message_id_sent_to_participant[6];  /* bytes 8 to 13 */
  uint8_t time_local[6];                                    /* bytes 14 to 19 */
} HeartbeatQuestion;

/* any Heartbeat Question at all: every byte one the checker chooses */
static void any_heartbeat_question(HeartbeatQuestion *record) {
  for (size_t i = 0; i < 8; i++) { record->first_user_sequence_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_local[i] = arbitrary(); }
}

/* Heartbeat Question to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_question(const HeartbeatQuestion *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->first_user_sequence_i_d[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_exchange_message_id_sent_to_participant[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_local[i]; }

  return at;
}

/* Heartbeat Question off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_question(HeartbeatQuestion *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->first_user_sequence_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_local[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Question is what was written, byte for byte */
static void equal_heartbeat_question(const HeartbeatQuestion *read, const HeartbeatQuestion *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->first_user_sequence_i_d[i] == written->first_user_sequence_i_d[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_exchange_message_id_sent_to_participant[i] == written->last_exchange_message_id_sent_to_participant[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_local[i] == written->time_local[i]); }
}

/* Heartbeat Question: written and read back, then read and written back */
static void check_heartbeat_question(void) {
  HeartbeatQuestion sent;
  HeartbeatQuestion got;
  uint8_t wire[20];
  uint8_t again[20];

  any_heartbeat_question(&sent);
  assert(encode_heartbeat_question(&sent, wire, 0) == 20);
  assert(decode_heartbeat_question(&got, wire, 0) == 20);
  equal_heartbeat_question(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_question(&got, wire, 0) == 20);
  assert(encode_heartbeat_question(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Out Of Sequence: 22 bytes ----------------------------------------------- */

typedef struct {
  uint8_t received_user_sequence_id[8];       /* bytes 0 to 7 */
  uint8_t expected_last_user_sequence_id[8];  /* bytes 8 to 15 */
  uint8_t message_time_local[6];              /* bytes 16 to 21 */
} OutOfSequence;

/* any Out Of Sequence at all: every byte one the checker chooses */
static void any_out_of_sequence(OutOfSequence *record) {
  for (size_t i = 0; i < 8; i++) { record->received_user_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expected_last_user_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->message_time_local[i] = arbitrary(); }
}

/* Out Of Sequence to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_out_of_sequence(const OutOfSequence *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->received_user_sequence_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expected_last_user_sequence_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->message_time_local[i]; }

  return at;
}

/* Out Of Sequence off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_out_of_sequence(OutOfSequence *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->received_user_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expected_last_user_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->message_time_local[i] = wire[at++]; }

  return at;
}

/* what was read of Out Of Sequence is what was written, byte for byte */
static void equal_out_of_sequence(const OutOfSequence *read, const OutOfSequence *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->received_user_sequence_id[i] == written->received_user_sequence_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expected_last_user_sequence_id[i] == written->expected_last_user_sequence_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->message_time_local[i] == written->message_time_local[i]); }
}

/* Out Of Sequence: written and read back, then read and written back */
static void check_out_of_sequence(void) {
  OutOfSequence sent;
  OutOfSequence got;
  uint8_t wire[22];
  uint8_t again[22];

  any_out_of_sequence(&sent);
  assert(encode_out_of_sequence(&sent, wire, 0) == 22);
  assert(decode_out_of_sequence(&got, wire, 0) == 22);
  equal_out_of_sequence(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_out_of_sequence(&got, wire, 0) == 22);
  assert(encode_out_of_sequence(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Technical Error Notice: 218 bytes --------------------------------------- */

typedef struct {
  uint8_t received_message_type[2];                 /* bytes 0 to 1 */
  uint8_t preceding_user_sequence_i_d_received[8];  /* bytes 2 to 9 */
  uint8_t error_code[4];                            /* bytes 10 to 13 */
  uint8_t error_position[4];                        /* bytes 14 to 17 */
  uint8_t error_message[100];                       /* bytes 18 to 117 */
  uint8_t start_of_message_in_error[100];           /* bytes 118 to 217 */
} TechnicalErrorNotice;

/* any Technical Error Notice at all: every byte one the checker chooses */
static void any_technical_error_notice(TechnicalErrorNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->received_message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->preceding_user_sequence_i_d_received[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_position[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->error_message[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->start_of_message_in_error[i] = arbitrary(); }
}

/* Technical Error Notice to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_technical_error_notice(const TechnicalErrorNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->received_message_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->preceding_user_sequence_i_d_received[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_position[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->error_message[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->start_of_message_in_error[i]; }

  return at;
}

/* Technical Error Notice off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_technical_error_notice(TechnicalErrorNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->received_message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->preceding_user_sequence_i_d_received[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_position[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->error_message[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->start_of_message_in_error[i] = wire[at++]; }

  return at;
}

/* what was read of Technical Error Notice is what was written, byte for byte */
static void equal_technical_error_notice(const TechnicalErrorNotice *read, const TechnicalErrorNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->received_message_type[i] == written->received_message_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->preceding_user_sequence_i_d_received[i] == written->preceding_user_sequence_i_d_received[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->error_position[i] == written->error_position[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->error_message[i] == written->error_message[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->start_of_message_in_error[i] == written->start_of_message_in_error[i]); }
}

/* Technical Error Notice: written and read back, then read and written back */
static void check_technical_error_notice(void) {
  TechnicalErrorNotice sent;
  TechnicalErrorNotice got;
  uint8_t wire[218];
  uint8_t again[218];

  any_technical_error_notice(&sent);
  assert(encode_technical_error_notice(&sent, wire, 0) == 218);
  assert(decode_technical_error_notice(&got, wire, 0) == 218);
  equal_technical_error_notice(&got, &sent);

  for (size_t i = 0; i < 218; i++) { wire[i] = arbitrary(); }
  assert(decode_technical_error_notice(&got, wire, 0) == 218);
  assert(encode_technical_error_notice(&got, again, 0) == 218);
  for (size_t i = 0; i < 218; i++) { assert(again[i] == wire[i]); }
}

/* ---- Disconnection Instruction Acknowledgement: 12 bytes --------------------- */

typedef struct {
  uint8_t current_session_id[4];              /* bytes 0 to 3 */
  uint8_t last_user_sequence_id_received[8];  /* bytes 4 to 11 */
} DisconnectionInstructionAcknowledgement;

/* any Disconnection Instruction Acknowledgement at all: every byte one the checker chooses */
static void any_disconnection_instruction_acknowledgement(DisconnectionInstructionAcknowledgement *record) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = arbitrary(); }
}

/* Disconnection Instruction Acknowledgement to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_disconnection_instruction_acknowledgement(const DisconnectionInstructionAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_id_received[i]; }

  return at;
}

/* Disconnection Instruction Acknowledgement off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_disconnection_instruction_acknowledgement(DisconnectionInstructionAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = wire[at++]; }

  return at;
}

/* what was read of Disconnection Instruction Acknowledgement is what was written, byte for byte */
static void equal_disconnection_instruction_acknowledgement(const DisconnectionInstructionAcknowledgement *read, const DisconnectionInstructionAcknowledgement *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_session_id[i] == written->current_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_id_received[i] == written->last_user_sequence_id_received[i]); }
}

/* Disconnection Instruction Acknowledgement: written and read back, then read and written back */
static void check_disconnection_instruction_acknowledgement(void) {
  DisconnectionInstructionAcknowledgement sent;
  DisconnectionInstructionAcknowledgement got;
  uint8_t wire[12];
  uint8_t again[12];

  any_disconnection_instruction_acknowledgement(&sent);
  assert(encode_disconnection_instruction_acknowledgement(&sent, wire, 0) == 12);
  assert(decode_disconnection_instruction_acknowledgement(&got, wire, 0) == 12);
  equal_disconnection_instruction_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_disconnection_instruction_acknowledgement(&got, wire, 0) == 12);
  assert(encode_disconnection_instruction_acknowledgement(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Connection Acknowledgement: 12 bytes ------------------------------------ */

/* Stated by the guide as having the same number of bytes and format as TM, whose fields are written out here. */
typedef struct {
  uint8_t current_session_id[4];              /* bytes 0 to 3 */
  uint8_t last_user_sequence_id_received[8];  /* bytes 4 to 11 */
} ConnectionAcknowledgement;

/* any Connection Acknowledgement at all: every byte one the checker chooses */
static void any_connection_acknowledgement(ConnectionAcknowledgement *record) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = arbitrary(); }
}

/* Connection Acknowledgement to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_connection_acknowledgement(const ConnectionAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_id_received[i]; }

  return at;
}

/* Connection Acknowledgement off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_connection_acknowledgement(ConnectionAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = wire[at++]; }

  return at;
}

/* what was read of Connection Acknowledgement is what was written, byte for byte */
static void equal_connection_acknowledgement(const ConnectionAcknowledgement *read, const ConnectionAcknowledgement *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_session_id[i] == written->current_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_id_received[i] == written->last_user_sequence_id_received[i]); }
}

/* Connection Acknowledgement: written and read back, then read and written back */
static void check_connection_acknowledgement(void) {
  ConnectionAcknowledgement sent;
  ConnectionAcknowledgement got;
  uint8_t wire[12];
  uint8_t again[12];

  any_connection_acknowledgement(&sent);
  assert(encode_connection_acknowledgement(&sent, wire, 0) == 12);
  assert(decode_connection_acknowledgement(&got, wire, 0) == 12);
  equal_connection_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_connection_acknowledgement(&got, wire, 0) == 12);
  assert(encode_connection_acknowledgement(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Disconnection Acknowledgement: 12 bytes --------------------------------- */

/* Stated by the guide as having the same number of bytes and format as TM, whose fields are written out here. */
typedef struct {
  uint8_t current_session_id[4];              /* bytes 0 to 3 */
  uint8_t last_user_sequence_id_received[8];  /* bytes 4 to 11 */
} DisconnectionAcknowledgement;

/* any Disconnection Acknowledgement at all: every byte one the checker chooses */
static void any_disconnection_acknowledgement(DisconnectionAcknowledgement *record) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = arbitrary(); }
}

/* Disconnection Acknowledgement to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_disconnection_acknowledgement(const DisconnectionAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->current_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_id_received[i]; }

  return at;
}

/* Disconnection Acknowledgement off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_disconnection_acknowledgement(DisconnectionAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->current_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = wire[at++]; }

  return at;
}

/* what was read of Disconnection Acknowledgement is what was written, byte for byte */
static void equal_disconnection_acknowledgement(const DisconnectionAcknowledgement *read, const DisconnectionAcknowledgement *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->current_session_id[i] == written->current_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_id_received[i] == written->last_user_sequence_id_received[i]); }
}

/* Disconnection Acknowledgement: written and read back, then read and written back */
static void check_disconnection_acknowledgement(void) {
  DisconnectionAcknowledgement sent;
  DisconnectionAcknowledgement got;
  uint8_t wire[12];
  uint8_t again[12];

  any_disconnection_acknowledgement(&sent);
  assert(encode_disconnection_acknowledgement(&sent, wire, 0) == 12);
  assert(decode_disconnection_acknowledgement(&got, wire, 0) == 12);
  equal_disconnection_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_disconnection_acknowledgement(&got, wire, 0) == 12);
  assert(encode_disconnection_acknowledgement(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- End Of Transmission: 18 bytes ------------------------------------------- */

typedef struct {
  uint8_t ended_session_id[4];                /* bytes 0 to 3 */
  uint8_t last_user_sequence_id_received[8];  /* bytes 4 to 11 */
  uint8_t time[6];                            /* bytes 12 to 17 */
} EndOfTransmission;

/* any End Of Transmission at all: every byte one the checker chooses */
static void any_end_of_transmission(EndOfTransmission *record) {
  for (size_t i = 0; i < 4; i++) { record->ended_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
}

/* End Of Transmission to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmission(const EndOfTransmission *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ended_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_id_received[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }

  return at;
}

/* End Of Transmission off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmission(EndOfTransmission *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ended_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Transmission is what was written, byte for byte */
static void equal_end_of_transmission(const EndOfTransmission *read, const EndOfTransmission *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ended_session_id[i] == written->ended_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_id_received[i] == written->last_user_sequence_id_received[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
}

/* End Of Transmission: written and read back, then read and written back */
static void check_end_of_transmission(void) {
  EndOfTransmission sent;
  EndOfTransmission got;
  uint8_t wire[18];
  uint8_t again[18];

  any_end_of_transmission(&sent);
  assert(encode_end_of_transmission(&sent, wire, 0) == 18);
  assert(decode_end_of_transmission(&got, wire, 0) == 18);
  equal_end_of_transmission(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_end_of_transmission(&got, wire, 0) == 18);
  assert(encode_end_of_transmission(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Notice: 358 bytes ------------------------------------------------- */

typedef struct {
  uint8_t error_code[4];              /* bytes 0 to 3 */
  uint8_t error_description[100];     /* bytes 4 to 103 */
  uint8_t group[2];                   /* bytes 104 to 105 */
  uint8_t instrument_optional[4];     /* bytes 106 to 109 */
  uint8_t order_id_error_notice[20];  /* bytes 110 to 129 */
  uint8_t auction_i_d_optional[6];    /* bytes 130 to 135 */
  uint8_t original_message_type[2];   /* bytes 136 to 137 */
  uint8_t error_detail[200];          /* bytes 138 to 337 */
  uint8_t client_order_id[20];        /* bytes 338 to 357 */
} ErrorNotice;

/* any Error Notice at all: every byte one the checker chooses */
static void any_error_notice(ErrorNotice *record) {
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->error_description[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->order_id_error_notice[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->original_message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 200; i++) { record->error_detail[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
}

/* Error Notice to the wire: 358 bytes from at, returning where the next byte goes */
static size_t encode_error_notice(const ErrorNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->error_description[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->order_id_error_notice[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->original_message_type[i]; }
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->error_detail[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }

  return at;
}

/* Error Notice off the wire: 358 bytes from at, returning where the next byte lies */
static size_t decode_error_notice(ErrorNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->error_description[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->order_id_error_notice[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->original_message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 200; i++) { record->error_detail[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Error Notice is what was written, byte for byte */
static void equal_error_notice(const ErrorNotice *read, const ErrorNotice *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->error_description[i] == written->error_description[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->order_id_error_notice[i] == written->order_id_error_notice[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->original_message_type[i] == written->original_message_type[i]); }
  for (size_t i = 0; i < 200; i++) { assert(read->error_detail[i] == written->error_detail[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
}

/* Error Notice: written and read back, then read and written back */
static void check_error_notice(void) {
  ErrorNotice sent;
  ErrorNotice got;
  uint8_t wire[358];
  uint8_t again[358];

  any_error_notice(&sent);
  assert(encode_error_notice(&sent, wire, 0) == 358);
  assert(decode_error_notice(&got, wire, 0) == 358);
  equal_error_notice(&got, &sent);

  for (size_t i = 0; i < 358; i++) { wire[i] = arbitrary(); }
  assert(decode_error_notice(&got, wire, 0) == 358);
  assert(encode_error_notice(&got, again, 0) == 358);
  for (size_t i = 0; i < 358; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulk Quote Data Acknowledgement: 18 bytes ------------------------------- */

typedef struct {
  uint8_t group[2];      /* bytes 0 to 1 */
  uint8_t trader_id[8];  /* bytes 2 to 9 */
  uint8_t quote_i_d[8];  /* bytes 10 to 17 */
} BulkQuoteDataAcknowledgement;

/* any Bulk Quote Data Acknowledgement at all: every byte one the checker chooses */
static void any_bulk_quote_data_acknowledgement(BulkQuoteDataAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_i_d[i] = arbitrary(); }
}

/* Bulk Quote Data Acknowledgement to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_bulk_quote_data_acknowledgement(const BulkQuoteDataAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_i_d[i]; }

  return at;
}

/* Bulk Quote Data Acknowledgement off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_bulk_quote_data_acknowledgement(BulkQuoteDataAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_i_d[i] = wire[at++]; }

  return at;
}

/* what was read of Bulk Quote Data Acknowledgement is what was written, byte for byte */
static void equal_bulk_quote_data_acknowledgement(const BulkQuoteDataAcknowledgement *read, const BulkQuoteDataAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_i_d[i] == written->quote_i_d[i]); }
}

/* Bulk Quote Data Acknowledgement: written and read back, then read and written back */
static void check_bulk_quote_data_acknowledgement(void) {
  BulkQuoteDataAcknowledgement sent;
  BulkQuoteDataAcknowledgement got;
  uint8_t wire[18];
  uint8_t again[18];

  any_bulk_quote_data_acknowledgement(&sent);
  assert(encode_bulk_quote_data_acknowledgement(&sent, wire, 0) == 18);
  assert(decode_bulk_quote_data_acknowledgement(&got, wire, 0) == 18);
  equal_bulk_quote_data_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_bulk_quote_data_acknowledgement(&got, wire, 0) == 18);
  assert(encode_bulk_quote_data_acknowledgement(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Data: 20 bytes ------------------------------------------------- */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t clearing_operation_mode;   /* byte 15 */
  uint8_t clearing_destination[4];   /* bytes 16 to 19 */
} ClearingData;

/* any Clearing Data at all: every byte one the checker chooses */
static void any_clearing_data(ClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  record->clearing_operation_mode = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = arbitrary(); }
}

/* Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_clearing_data(const ClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  wire[at++] = record->clearing_operation_mode;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_destination[i]; }

  return at;
}

/* Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_clearing_data(ClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  record->clearing_operation_mode = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->clearing_destination[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Data is what was written, byte for byte */
static void equal_clearing_data(const ClearingData *read, const ClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  assert(read->clearing_operation_mode == written->clearing_operation_mode);
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_destination[i] == written->clearing_destination[i]); }
}

/* Clearing Data: written and read back, then read and written back */
static void check_clearing_data(void) {
  ClearingData sent;
  ClearingData got;
  uint8_t wire[20];
  uint8_t again[20];

  any_clearing_data(&sent);
  assert(encode_clearing_data(&sent, wire, 0) == 20);
  assert(decode_clearing_data(&got, wire, 0) == 20);
  equal_clearing_data(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_data(&got, wire, 0) == 20);
  assert(encode_clearing_data(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Owner Data: 71 bytes ---------------------------------------------------- */

/* The guide states these fields once, as Owner Data, for every message that carries them. */
typedef struct {
  uint8_t client_order_id[20];  /* bytes 0 to 19 */
  uint8_t pound_sign;           /* byte 20 */
  uint8_t memo[50];             /* bytes 21 to 70 */
} OwnerData;

/* any Owner Data at all: every byte one the checker chooses */
static void any_owner_data(OwnerData *record) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->pound_sign = arbitrary();
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Owner Data to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_owner_data(const OwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->pound_sign;
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Owner Data off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_owner_data(OwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->pound_sign = wire[at++];
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Owner Data is what was written, byte for byte */
static void equal_owner_data(const OwnerData *read, const OwnerData *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->pound_sign == written->pound_sign);
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Owner Data: written and read back, then read and written back */
static void check_owner_data(void) {
  OwnerData sent;
  OwnerData got;
  uint8_t wire[71];
  uint8_t again[71];

  any_owner_data(&sent);
  assert(encode_owner_data(&sent, wire, 0) == 71);
  assert(decode_owner_data(&got, wire, 0) == 71);
  equal_owner_data(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_owner_data(&got, wire, 0) == 71);
  assert(encode_owner_data(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Acknowledgement: 167 bytes ---------------------------------------- */

typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t reserved_6[6];               /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} OrderAcknowledgement;

/* any Order Acknowledgement at all: every byte one the checker chooses */
static void any_order_acknowledgement(OrderAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reserved_6[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Acknowledgement to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement(const OrderAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reserved_6[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Acknowledgement off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement(OrderAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reserved_6[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement is what was written, byte for byte */
static void equal_order_acknowledgement(const OrderAcknowledgement *read, const OrderAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reserved_6[i] == written->reserved_6[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Acknowledgement: written and read back, then read and written back */
static void check_order_acknowledgement(void) {
  OrderAcknowledgement sent;
  OrderAcknowledgement got;
  uint8_t wire[167];
  uint8_t again[167];

  any_order_acknowledgement(&sent);
  assert(encode_order_acknowledgement(&sent, wire, 0) == 167);
  assert(decode_order_acknowledgement(&got, wire, 0) == 167);
  equal_order_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement(&got, wire, 0) == 167);
  assert(encode_order_acknowledgement(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Cancellation Confirmation: 11 bytes ------------------------------ */

typedef struct {
  uint8_t group[2];              /* bytes 0 to 1 */
  uint8_t trader_id[8];          /* bytes 2 to 9 */
  uint8_t type_of_cancellation;  /* byte 10 */
} GlobalCancellationConfirmation;

/* any Global Cancellation Confirmation at all: every byte one the checker chooses */
static void any_global_cancellation_confirmation(GlobalCancellationConfirmation *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->type_of_cancellation = arbitrary();
}

/* Global Cancellation Confirmation to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_global_cancellation_confirmation(const GlobalCancellationConfirmation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->type_of_cancellation;

  return at;
}

/* Global Cancellation Confirmation off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_global_cancellation_confirmation(GlobalCancellationConfirmation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->type_of_cancellation = wire[at++];

  return at;
}

/* what was read of Global Cancellation Confirmation is what was written, byte for byte */
static void equal_global_cancellation_confirmation(const GlobalCancellationConfirmation *read, const GlobalCancellationConfirmation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->type_of_cancellation == written->type_of_cancellation);
}

/* Global Cancellation Confirmation: written and read back, then read and written back */
static void check_global_cancellation_confirmation(void) {
  GlobalCancellationConfirmation sent;
  GlobalCancellationConfirmation got;
  uint8_t wire[11];
  uint8_t again[11];

  any_global_cancellation_confirmation(&sent);
  assert(encode_global_cancellation_confirmation(&sent, wire, 0) == 11);
  assert(decode_global_cancellation_confirmation(&got, wire, 0) == 11);
  equal_global_cancellation_confirmation(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_global_cancellation_confirmation(&got, wire, 0) == 11);
  assert(encode_global_cancellation_confirmation(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Improvement Order Acknowlegment: 167 bytes ------------------------------ */

typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t auction_i_d[6];              /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} ImprovementOrderAcknowlegment;

/* any Improvement Order Acknowlegment at all: every byte one the checker chooses */
static void any_improvement_order_acknowlegment(ImprovementOrderAcknowlegment *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Improvement Order Acknowlegment to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_improvement_order_acknowlegment(const ImprovementOrderAcknowlegment *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Improvement Order Acknowlegment off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_improvement_order_acknowlegment(ImprovementOrderAcknowlegment *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Improvement Order Acknowlegment is what was written, byte for byte */
static void equal_improvement_order_acknowlegment(const ImprovementOrderAcknowlegment *read, const ImprovementOrderAcknowlegment *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d[i] == written->auction_i_d[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Improvement Order Acknowlegment: written and read back, then read and written back */
static void check_improvement_order_acknowlegment(void) {
  ImprovementOrderAcknowlegment sent;
  ImprovementOrderAcknowlegment got;
  uint8_t wire[167];
  uint8_t again[167];

  any_improvement_order_acknowlegment(&sent);
  assert(encode_improvement_order_acknowlegment(&sent, wire, 0) == 167);
  assert(decode_improvement_order_acknowlegment(&got, wire, 0) == 167);
  equal_improvement_order_acknowlegment(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_improvement_order_acknowlegment(&got, wire, 0) == 167);
  assert(encode_improvement_order_acknowlegment(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modification Acknowledgement: 167 bytes --------------------------- */

typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t reserved_6[6];               /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} OrderModificationAcknowledgement;

/* any Order Modification Acknowledgement at all: every byte one the checker chooses */
static void any_order_modification_acknowledgement(OrderModificationAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->reserved_6[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Modification Acknowledgement to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_order_modification_acknowledgement(const OrderModificationAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->reserved_6[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Modification Acknowledgement off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_order_modification_acknowledgement(OrderModificationAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->reserved_6[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modification Acknowledgement is what was written, byte for byte */
static void equal_order_modification_acknowledgement(const OrderModificationAcknowledgement *read, const OrderModificationAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->reserved_6[i] == written->reserved_6[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Modification Acknowledgement: written and read back, then read and written back */
static void check_order_modification_acknowledgement(void) {
  OrderModificationAcknowledgement sent;
  OrderModificationAcknowledgement got;
  uint8_t wire[167];
  uint8_t again[167];

  any_order_modification_acknowledgement(&sent);
  assert(encode_order_modification_acknowledgement(&sent, wire, 0) == 167);
  assert(decode_order_modification_acknowledgement(&got, wire, 0) == 167);
  equal_order_modification_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modification_acknowledgement(&got, wire, 0) == 167);
  assert(encode_order_modification_acknowledgement(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- Standard Acknowledgement: 10 bytes -------------------------------------- */

typedef struct {
  uint8_t trader_id[8];              /* bytes 0 to 7 */
  uint8_t original_message_type[2];  /* bytes 8 to 9 */
} StandardAcknowledgement;

/* any Standard Acknowledgement at all: every byte one the checker chooses */
static void any_standard_acknowledgement(StandardAcknowledgement *record) {
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->original_message_type[i] = arbitrary(); }
}

/* Standard Acknowledgement to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_standard_acknowledgement(const StandardAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->original_message_type[i]; }

  return at;
}

/* Standard Acknowledgement off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_standard_acknowledgement(StandardAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->original_message_type[i] = wire[at++]; }

  return at;
}

/* what was read of Standard Acknowledgement is what was written, byte for byte */
static void equal_standard_acknowledgement(const StandardAcknowledgement *read, const StandardAcknowledgement *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->original_message_type[i] == written->original_message_type[i]); }
}

/* Standard Acknowledgement: written and read back, then read and written back */
static void check_standard_acknowledgement(void) {
  StandardAcknowledgement sent;
  StandardAcknowledgement got;
  uint8_t wire[10];
  uint8_t again[10];

  any_standard_acknowledgement(&sent);
  assert(encode_standard_acknowledgement(&sent, wire, 0) == 10);
  assert(decode_standard_acknowledgement(&got, wire, 0) == 10);
  equal_standard_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_standard_acknowledgement(&got, wire, 0) == 10);
  assert(encode_standard_acknowledgement(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Complex Order Auction Acknowledgement: 167 bytes ------------------------ */

typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t auction_i_d_optional[6];     /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} ComplexOrderAuctionAcknowledgement;

/* any Complex Order Auction Acknowledgement at all: every byte one the checker chooses */
static void any_complex_order_auction_acknowledgement(ComplexOrderAuctionAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Complex Order Auction Acknowledgement to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_complex_order_auction_acknowledgement(const ComplexOrderAuctionAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Complex Order Auction Acknowledgement off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_complex_order_auction_acknowledgement(ComplexOrderAuctionAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Complex Order Auction Acknowledgement is what was written, byte for byte */
static void equal_complex_order_auction_acknowledgement(const ComplexOrderAuctionAcknowledgement *read, const ComplexOrderAuctionAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Complex Order Auction Acknowledgement: written and read back, then read and written back */
static void check_complex_order_auction_acknowledgement(void) {
  ComplexOrderAuctionAcknowledgement sent;
  ComplexOrderAuctionAcknowledgement got;
  uint8_t wire[167];
  uint8_t again[167];

  any_complex_order_auction_acknowledgement(&sent);
  assert(encode_complex_order_auction_acknowledgement(&sent, wire, 0) == 167);
  assert(decode_complex_order_auction_acknowledgement(&got, wire, 0) == 167);
  equal_complex_order_auction_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_complex_order_auction_acknowledgement(&got, wire, 0) == 167);
  assert(encode_complex_order_auction_acknowledgement(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- Auction Or Improvement Cancellation Acknowledgement: 147 bytes ---------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t trader_id[8];            /* bytes 6 to 13 */
  uint8_t order_id[8];             /* bytes 14 to 21 */
  uint8_t status;                  /* byte 22 */
  uint8_t verb_side;               /* byte 23 */
  uint8_t quantity[8];             /* bytes 24 to 31 */
  uint8_t assigned_price[10];      /* bytes 32 to 41 */
  ClearingData clearing_data;      /* bytes 42 to 61 */
  OwnerData owner_data;            /* bytes 62 to 132 */
  uint8_t original_order_id[8];    /* bytes 133 to 140 */
  uint8_t auction_i_d[6];          /* bytes 141 to 146 */
} AuctionOrImprovementCancellationAcknowledgement;

/* any Auction Or Improvement Cancellation Acknowledgement at all: every byte one the checker chooses */
static void any_auction_or_improvement_cancellation_acknowledgement(AuctionOrImprovementCancellationAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = arbitrary(); }
}

/* Auction Or Improvement Cancellation Acknowledgement to the wire: 147 bytes from at, returning where the next byte goes */
static size_t encode_auction_or_improvement_cancellation_acknowledgement(const AuctionOrImprovementCancellationAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d[i]; }

  return at;
}

/* Auction Or Improvement Cancellation Acknowledgement off the wire: 147 bytes from at, returning where the next byte lies */
static size_t decode_auction_or_improvement_cancellation_acknowledgement(AuctionOrImprovementCancellationAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = wire[at++]; }

  return at;
}

/* what was read of Auction Or Improvement Cancellation Acknowledgement is what was written, byte for byte */
static void equal_auction_or_improvement_cancellation_acknowledgement(const AuctionOrImprovementCancellationAcknowledgement *read, const AuctionOrImprovementCancellationAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d[i] == written->auction_i_d[i]); }
}

/* Auction Or Improvement Cancellation Acknowledgement: written and read back, then read and written back */
static void check_auction_or_improvement_cancellation_acknowledgement(void) {
  AuctionOrImprovementCancellationAcknowledgement sent;
  AuctionOrImprovementCancellationAcknowledgement got;
  uint8_t wire[147];
  uint8_t again[147];

  any_auction_or_improvement_cancellation_acknowledgement(&sent);
  assert(encode_auction_or_improvement_cancellation_acknowledgement(&sent, wire, 0) == 147);
  assert(decode_auction_or_improvement_cancellation_acknowledgement(&got, wire, 0) == 147);
  equal_auction_or_improvement_cancellation_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 147; i++) { wire[i] = arbitrary(); }
  assert(decode_auction_or_improvement_cancellation_acknowledgement(&got, wire, 0) == 147);
  assert(encode_auction_or_improvement_cancellation_acknowledgement(&got, again, 0) == 147);
  for (size_t i = 0; i < 147; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Acknowledgement: 167 bytes --------------------------- */

typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t auction_i_d[6];              /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} OrderCancellationAcknowledgement;

/* any Order Cancellation Acknowledgement at all: every byte one the checker chooses */
static void any_order_cancellation_acknowledgement(OrderCancellationAcknowledgement *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Cancellation Acknowledgement to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_acknowledgement(const OrderCancellationAcknowledgement *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Cancellation Acknowledgement off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_acknowledgement(OrderCancellationAcknowledgement *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Acknowledgement is what was written, byte for byte */
static void equal_order_cancellation_acknowledgement(const OrderCancellationAcknowledgement *read, const OrderCancellationAcknowledgement *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d[i] == written->auction_i_d[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Cancellation Acknowledgement: written and read back, then read and written back */
static void check_order_cancellation_acknowledgement(void) {
  OrderCancellationAcknowledgement sent;
  OrderCancellationAcknowledgement got;
  uint8_t wire[167];
  uint8_t again[167];

  any_order_cancellation_acknowledgement(&sent);
  assert(encode_order_cancellation_acknowledgement(&sent, wire, 0) == 167);
  assert(decode_order_cancellation_acknowledgement(&got, wire, 0) == 167);
  equal_order_cancellation_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_acknowledgement(&got, wire, 0) == 167);
  assert(encode_order_cancellation_acknowledgement(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trader Status: 10 bytes ------------------------------------------------- */

typedef struct {
  uint8_t trader_id[8];        /* bytes 0 to 7 */
  uint8_t trader_lock_out;     /* byte 8 */
  uint8_t risk_team_lock_out;  /* byte 9 */
} TraderStatus;

/* any Trader Status at all: every byte one the checker chooses */
static void any_trader_status(TraderStatus *record) {
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->trader_lock_out = arbitrary();
  record->risk_team_lock_out = arbitrary();
}

/* Trader Status to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_trader_status(const TraderStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->trader_lock_out;
  wire[at++] = record->risk_team_lock_out;

  return at;
}

/* Trader Status off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_trader_status(TraderStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->trader_lock_out = wire[at++];
  record->risk_team_lock_out = wire[at++];

  return at;
}

/* what was read of Trader Status is what was written, byte for byte */
static void equal_trader_status(const TraderStatus *read, const TraderStatus *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->trader_lock_out == written->trader_lock_out);
  assert(read->risk_team_lock_out == written->risk_team_lock_out);
}

/* Trader Status: written and read back, then read and written back */
static void check_trader_status(void) {
  TraderStatus sent;
  TraderStatus got;
  uint8_t wire[10];
  uint8_t again[10];

  any_trader_status(&sent);
  assert(encode_trader_status(&sent, wire, 0) == 10);
  assert(decode_trader_status(&got, wire, 0) == 10);
  equal_trader_status(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_trader_status(&got, wire, 0) == 10);
  assert(encode_trader_status(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Directed Order Cancellation Notice: 41 bytes ---------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t trader_id[8];            /* bytes 6 to 13 */
  uint8_t verb_side;               /* byte 14 */
  uint8_t quantity[8];             /* bytes 15 to 22 */
  uint8_t price[10];               /* bytes 23 to 32 */
  uint8_t referenced_order_id[8];  /* bytes 33 to 40 */
} DirectedOrderCancellationNotice;

/* any Directed Order Cancellation Notice at all: every byte one the checker chooses */
static void any_directed_order_cancellation_notice(DirectedOrderCancellationNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = arbitrary(); }
}

/* Directed Order Cancellation Notice to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_directed_order_cancellation_notice(const DirectedOrderCancellationNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->referenced_order_id[i]; }

  return at;
}

/* Directed Order Cancellation Notice off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_directed_order_cancellation_notice(DirectedOrderCancellationNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Directed Order Cancellation Notice is what was written, byte for byte */
static void equal_directed_order_cancellation_notice(const DirectedOrderCancellationNotice *read, const DirectedOrderCancellationNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->referenced_order_id[i] == written->referenced_order_id[i]); }
}

/* Directed Order Cancellation Notice: written and read back, then read and written back */
static void check_directed_order_cancellation_notice(void) {
  DirectedOrderCancellationNotice sent;
  DirectedOrderCancellationNotice got;
  uint8_t wire[41];
  uint8_t again[41];

  any_directed_order_cancellation_notice(&sent);
  assert(encode_directed_order_cancellation_notice(&sent, wire, 0) == 41);
  assert(decode_directed_order_cancellation_notice(&got, wire, 0) == 41);
  equal_directed_order_cancellation_notice(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_directed_order_cancellation_notice(&got, wire, 0) == 41);
  assert(encode_directed_order_cancellation_notice(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Directed Order Notice: 41 bytes ----------------------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t trader_id[8];            /* bytes 6 to 13 */
  uint8_t verb_side;               /* byte 14 */
  uint8_t quantity[8];             /* bytes 15 to 22 */
  uint8_t price[10];               /* bytes 23 to 32 */
  uint8_t referenced_order_id[8];  /* bytes 33 to 40 */
} DirectedOrderNotice;

/* any Directed Order Notice at all: every byte one the checker chooses */
static void any_directed_order_notice(DirectedOrderNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = arbitrary(); }
}

/* Directed Order Notice to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_directed_order_notice(const DirectedOrderNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->referenced_order_id[i]; }

  return at;
}

/* Directed Order Notice off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_directed_order_notice(DirectedOrderNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->referenced_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Directed Order Notice is what was written, byte for byte */
static void equal_directed_order_notice(const DirectedOrderNotice *read, const DirectedOrderNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->referenced_order_id[i] == written->referenced_order_id[i]); }
}

/* Directed Order Notice: written and read back, then read and written back */
static void check_directed_order_notice(void) {
  DirectedOrderNotice sent;
  DirectedOrderNotice got;
  uint8_t wire[41];
  uint8_t again[41];

  any_directed_order_notice(&sent);
  assert(encode_directed_order_notice(&sent, wire, 0) == 41);
  assert(decode_directed_order_notice(&got, wire, 0) == 41);
  equal_directed_order_notice(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_directed_order_notice(&got, wire, 0) == 41);
  assert(encode_directed_order_notice(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Excluded Instrument Notice: 22 bytes ------------------------------------ */

typedef struct {
  uint8_t group[2];              /* bytes 0 to 1 */
  uint8_t reserved_2[2];         /* bytes 2 to 3 */
  uint8_t trader_id[8];          /* bytes 4 to 11 */
  uint8_t second_reserved_2[2];  /* bytes 12 to 13 */
  uint8_t nb_of_instruments[4];  /* bytes 14 to 17 */
  uint8_t instrument[4];         /* bytes 18 to 21 */
} ExcludedInstrumentNotice;

/* any Excluded Instrument Notice at all: every byte one the checker chooses */
static void any_excluded_instrument_notice(ExcludedInstrumentNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nb_of_instruments[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
}

/* Excluded Instrument Notice to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_excluded_instrument_notice(const ExcludedInstrumentNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->second_reserved_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nb_of_instruments[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }

  return at;
}

/* Excluded Instrument Notice off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_excluded_instrument_notice(ExcludedInstrumentNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->second_reserved_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nb_of_instruments[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }

  return at;
}

/* what was read of Excluded Instrument Notice is what was written, byte for byte */
static void equal_excluded_instrument_notice(const ExcludedInstrumentNotice *read, const ExcludedInstrumentNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->second_reserved_2[i] == written->second_reserved_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nb_of_instruments[i] == written->nb_of_instruments[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
}

/* Excluded Instrument Notice: written and read back, then read and written back */
static void check_excluded_instrument_notice(void) {
  ExcludedInstrumentNotice sent;
  ExcludedInstrumentNotice got;
  uint8_t wire[22];
  uint8_t again[22];

  any_excluded_instrument_notice(&sent);
  assert(encode_excluded_instrument_notice(&sent, wire, 0) == 22);
  assert(decode_excluded_instrument_notice(&got, wire, 0) == 22);
  equal_excluded_instrument_notice(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_excluded_instrument_notice(&got, wire, 0) == 22);
  assert(encode_excluded_instrument_notice(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group State Change: 3 bytes --------------------------------------------- */

typedef struct {
  uint8_t group[2];     /* bytes 0 to 1 */
  uint8_t group_state;  /* byte 2 */
} GroupStateChange;

/* any Group State Change at all: every byte one the checker chooses */
static void any_group_state_change(GroupStateChange *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->group_state = arbitrary();
}

/* Group State Change to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_group_state_change(const GroupStateChange *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->group_state;

  return at;
}

/* Group State Change off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_group_state_change(GroupStateChange *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->group_state = wire[at++];

  return at;
}

/* what was read of Group State Change is what was written, byte for byte */
static void equal_group_state_change(const GroupStateChange *read, const GroupStateChange *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->group_state == written->group_state);
}

/* Group State Change: written and read back, then read and written back */
static void check_group_state_change(void) {
  GroupStateChange sent;
  GroupStateChange got;
  uint8_t wire[3];
  uint8_t again[3];

  any_group_state_change(&sent);
  assert(encode_group_state_change(&sent, wire, 0) == 3);
  assert(decode_group_state_change(&got, wire, 0) == 3);
  equal_group_state_change(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_group_state_change(&got, wire, 0) == 3);
  assert(encode_group_state_change(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Execution Notice: 257 bytes ----------------------------------------- */

typedef struct {
  uint8_t group[2];                                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                      /* bytes 2 to 5 */
  uint8_t trader_id[8];                                /* bytes 6 to 13 */
  uint8_t reference_id[8];                             /* bytes 14 to 21 */
  uint8_t verb_side;                                   /* byte 22 */
  uint8_t quantity_traded[8];                          /* bytes 23 to 30 */
  uint8_t trade_price[10];                             /* bytes 31 to 40 */
  uint8_t time_trade_hhmmss[6];                        /* bytes 41 to 46 */
  ClearingData clearing_data;                          /* bytes 47 to 66 */
  OwnerData owner_data;                                /* bytes 67 to 137 */
  uint8_t special_trade_indicator;                     /* byte 138 */
  uint8_t price_type;                                  /* byte 139 */
  uint8_t trade_type;                                  /* byte 140 */
  uint8_t auction_i_d_optional[6];                     /* bytes 141 to 146 */
  uint8_t trade_number[8];                             /* bytes 147 to 154 */
  uint8_t trade_memo[50];                              /* bytes 155 to 204 */
  uint8_t original_reference_id[8];                    /* bytes 205 to 212 */
  uint8_t id_code_for_the_counterpart_participant[4];  /* bytes 213 to 216 */
  uint8_t liquidity_status;                            /* byte 217 */
  uint8_t strategy_group[2];                           /* bytes 218 to 219 */
  uint8_t strategy_instrument_id[4];                   /* bytes 220 to 223 */
  uint8_t strategy_verb_side;                          /* byte 224 */
  uint8_t strategy_trade_number[8];                    /* bytes 225 to 232 */
  uint8_t leg_number[2];                               /* bytes 233 to 234 */
  uint8_t counterpart_account_type;                    /* byte 235 */
  uint8_t additional_client_memo[16];                  /* bytes 236 to 251 */
  uint8_t reserved_1;                                  /* byte 252 */
  uint8_t reserved_4[4];                               /* bytes 253 to 256 */
} LegExecutionNotice;

/* any Leg Execution Notice at all: every byte one the checker chooses */
static void any_leg_execution_notice(LegExecutionNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_trade_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = arbitrary(); }
  record->strategy_verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = arbitrary(); }
  record->counterpart_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Leg Execution Notice to the wire: 257 bytes from at, returning where the next byte goes */
static size_t encode_leg_execution_notice(const LegExecutionNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_trade_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  wire[at++] = record->liquidity_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strategy_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_instrument_id[i]; }
  wire[at++] = record->strategy_verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strategy_trade_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_number[i]; }
  wire[at++] = record->counterpart_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Leg Execution Notice off the wire: 257 bytes from at, returning where the next byte lies */
static size_t decode_leg_execution_notice(LegExecutionNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_trade_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = wire[at++]; }
  record->strategy_verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = wire[at++]; }
  record->counterpart_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Execution Notice is what was written, byte for byte */
static void equal_leg_execution_notice(const LegExecutionNotice *read, const LegExecutionNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id[i] == written->reference_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_trade_hhmmss[i] == written->time_trade_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  for (size_t i = 0; i < 2; i++) { assert(read->strategy_group[i] == written->strategy_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_instrument_id[i] == written->strategy_instrument_id[i]); }
  assert(read->strategy_verb_side == written->strategy_verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->strategy_trade_number[i] == written->strategy_trade_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_number[i] == written->leg_number[i]); }
  assert(read->counterpart_account_type == written->counterpart_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Leg Execution Notice: written and read back, then read and written back */
static void check_leg_execution_notice(void) {
  LegExecutionNotice sent;
  LegExecutionNotice got;
  uint8_t wire[257];
  uint8_t again[257];

  any_leg_execution_notice(&sent);
  assert(encode_leg_execution_notice(&sent, wire, 0) == 257);
  assert(decode_leg_execution_notice(&got, wire, 0) == 257);
  equal_leg_execution_notice(&got, &sent);

  for (size_t i = 0; i < 257; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_execution_notice(&got, wire, 0) == 257);
  assert(encode_leg_execution_notice(&got, again, 0) == 257);
  for (size_t i = 0; i < 257; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancellation Of All Quotes Notices: 15 bytes ---------------------------- */

typedef struct {
  uint8_t group[2];                /* bytes 0 to 1 */
  uint8_t instrument_optional[4];  /* bytes 2 to 5 */
  uint8_t trader_id[8];            /* bytes 6 to 13 */
  uint8_t quote_cancel_reason;     /* byte 14 */
} CancellationOfAllQuotesNotices;

/* any Cancellation Of All Quotes Notices at all: every byte one the checker chooses */
static void any_cancellation_of_all_quotes_notices(CancellationOfAllQuotesNotices *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->quote_cancel_reason = arbitrary();
}

/* Cancellation Of All Quotes Notices to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_cancellation_of_all_quotes_notices(const CancellationOfAllQuotesNotices *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->quote_cancel_reason;

  return at;
}

/* Cancellation Of All Quotes Notices off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_cancellation_of_all_quotes_notices(CancellationOfAllQuotesNotices *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->quote_cancel_reason = wire[at++];

  return at;
}

/* what was read of Cancellation Of All Quotes Notices is what was written, byte for byte */
static void equal_cancellation_of_all_quotes_notices(const CancellationOfAllQuotesNotices *read, const CancellationOfAllQuotesNotices *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->quote_cancel_reason == written->quote_cancel_reason);
}

/* Cancellation Of All Quotes Notices: written and read back, then read and written back */
static void check_cancellation_of_all_quotes_notices(void) {
  CancellationOfAllQuotesNotices sent;
  CancellationOfAllQuotesNotices got;
  uint8_t wire[15];
  uint8_t again[15];

  any_cancellation_of_all_quotes_notices(&sent);
  assert(encode_cancellation_of_all_quotes_notices(&sent, wire, 0) == 15);
  assert(decode_cancellation_of_all_quotes_notices(&got, wire, 0) == 15);
  equal_cancellation_of_all_quotes_notices(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_cancellation_of_all_quotes_notices(&got, wire, 0) == 15);
  assert(encode_cancellation_of_all_quotes_notices(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quality Market Maker Notification: 65 bytes ----------------------------- */

typedef struct {
  uint8_t group[2];                 /* bytes 0 to 1 */
  uint8_t instrument_optional[4];   /* bytes 2 to 5 */
  uint8_t trader_id[8];             /* bytes 6 to 13 */
  uint8_t auction_i_d_optional[6];  /* bytes 14 to 19 */
  uint8_t verb;                     /* byte 20 */
  uint8_t auction_quantity[8];      /* bytes 21 to 28 */
  uint8_t auction_price[10];        /* bytes 29 to 38 */
  uint8_t quote_quantity[8];        /* bytes 39 to 46 */
  uint8_t quote_price[10];          /* bytes 47 to 56 */
  uint8_t qualified_quantity[8];    /* bytes 57 to 64 */
} QualityMarketMakerNotification;

/* any Quality Market Maker Notification at all: every byte one the checker chooses */
static void any_quality_market_maker_notification(QualityMarketMakerNotification *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  record->verb = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->auction_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->quote_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->qualified_quantity[i] = arbitrary(); }
}

/* Quality Market Maker Notification to the wire: 65 bytes from at, returning where the next byte goes */
static size_t encode_quality_market_maker_notification(const QualityMarketMakerNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  wire[at++] = record->verb;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->auction_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->quote_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->qualified_quantity[i]; }

  return at;
}

/* Quality Market Maker Notification off the wire: 65 bytes from at, returning where the next byte lies */
static size_t decode_quality_market_maker_notification(QualityMarketMakerNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  record->verb = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->auction_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->quote_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->qualified_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Quality Market Maker Notification is what was written, byte for byte */
static void equal_quality_market_maker_notification(const QualityMarketMakerNotification *read, const QualityMarketMakerNotification *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  assert(read->verb == written->verb);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_quantity[i] == written->auction_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->auction_price[i] == written->auction_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_quantity[i] == written->quote_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->quote_price[i] == written->quote_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->qualified_quantity[i] == written->qualified_quantity[i]); }
}

/* Quality Market Maker Notification: written and read back, then read and written back */
static void check_quality_market_maker_notification(void) {
  QualityMarketMakerNotification sent;
  QualityMarketMakerNotification got;
  uint8_t wire[65];
  uint8_t again[65];

  any_quality_market_maker_notification(&sent);
  assert(encode_quality_market_maker_notification(&sent, wire, 0) == 65);
  assert(decode_quality_market_maker_notification(&got, wire, 0) == 65);
  equal_quality_market_maker_notification(&got, &sent);

  for (size_t i = 0; i < 65; i++) { wire[i] = arbitrary(); }
  assert(decode_quality_market_maker_notification(&got, wire, 0) == 65);
  assert(encode_quality_market_maker_notification(&got, again, 0) == 65);
  for (size_t i = 0; i < 65; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notice: 240 bytes --------------------------------------------- */

typedef struct {
  uint8_t group[2];                                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                      /* bytes 2 to 5 */
  uint8_t trader_id[8];                                /* bytes 6 to 13 */
  uint8_t reference_id[8];                             /* bytes 14 to 21 */
  uint8_t verb_side;                                   /* byte 22 */
  uint8_t quantity_traded[8];                          /* bytes 23 to 30 */
  uint8_t trade_price[10];                             /* bytes 31 to 40 */
  uint8_t time_of_the_trade_hhmmss[6];                 /* bytes 41 to 46 */
  ClearingData clearing_data;                          /* bytes 47 to 66 */
  OwnerData owner_data;                                /* bytes 67 to 137 */
  uint8_t special_trade_indicator;                     /* byte 138 */
  uint8_t price_type;                                  /* byte 139 */
  uint8_t trade_type;                                  /* byte 140 */
  uint8_t auction_i_d_optional[6];                     /* bytes 141 to 146 */
  uint8_t trade_number[8];                             /* bytes 147 to 154 */
  uint8_t trade_memo[50];                              /* bytes 155 to 204 */
  uint8_t original_reference_id[8];                    /* bytes 205 to 212 */
  uint8_t id_code_for_the_counterpart_participant[4];  /* bytes 213 to 216 */
  uint8_t liquidity_status;                            /* byte 217 */
  uint8_t counterpart_account_type;                    /* byte 218 */
  uint8_t additional_client_memo[16];                  /* bytes 219 to 234 */
  uint8_t reserved_1;                                  /* byte 235 */
  uint8_t reserved_4[4];                               /* bytes 236 to 239 */
} ExecutionNotice;

/* any Execution Notice at all: every byte one the checker chooses */
static void any_execution_notice(ExecutionNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_of_the_trade_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->counterpart_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Execution Notice to the wire: 240 bytes from at, returning where the next byte goes */
static size_t encode_execution_notice(const ExecutionNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_of_the_trade_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->counterpart_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Execution Notice off the wire: 240 bytes from at, returning where the next byte lies */
static size_t decode_execution_notice(ExecutionNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_of_the_trade_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->counterpart_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Notice is what was written, byte for byte */
static void equal_execution_notice(const ExecutionNotice *read, const ExecutionNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id[i] == written->reference_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_of_the_trade_hhmmss[i] == written->time_of_the_trade_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->counterpart_account_type == written->counterpart_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Execution Notice: written and read back, then read and written back */
static void check_execution_notice(void) {
  ExecutionNotice sent;
  ExecutionNotice got;
  uint8_t wire[240];
  uint8_t again[240];

  any_execution_notice(&sent);
  assert(encode_execution_notice(&sent, wire, 0) == 240);
  assert(decode_execution_notice(&got, wire, 0) == 240);
  equal_execution_notice(&got, &sent);

  for (size_t i = 0; i < 240; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notice(&got, wire, 0) == 240);
  assert(encode_execution_notice(&got, again, 0) == 240);
  for (size_t i = 0; i < 240; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Notice: 75 bytes -------------------------------------------------- */

typedef struct {
  uint8_t group[2];                                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                      /* bytes 2 to 5 */
  uint8_t trader_id[8];                                /* bytes 6 to 13 */
  uint8_t reference_id_quote[8];                       /* bytes 14 to 21 */
  uint8_t verb_side;                                   /* byte 22 */
  uint8_t order_type;                                  /* byte 23 */
  uint8_t action;                                      /* byte 24 */
  uint8_t new_quantity[8];                             /* bytes 25 to 32 */
  uint8_t new_price[10];                               /* bytes 33 to 42 */
  uint8_t previous_quantity[8];                        /* bytes 43 to 50 */
  uint8_t previous_price[10];                          /* bytes 51 to 60 */
  uint8_t auction_i_d_optional[6];                     /* bytes 61 to 66 */
  uint8_t original_reference_id_quote_or_order_id[8];  /* bytes 67 to 74 */
} QuoteNotice;

/* any Quote Notice at all: every byte one the checker chooses */
static void any_quote_notice(QuoteNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id_quote[i] = arbitrary(); }
  record->verb_side = arbitrary();
  record->order_type = arbitrary();
  record->action = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->new_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->new_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->previous_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id_quote_or_order_id[i] = arbitrary(); }
}

/* Quote Notice to the wire: 75 bytes from at, returning where the next byte goes */
static size_t encode_quote_notice(const QuoteNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id_quote[i]; }
  wire[at++] = record->verb_side;
  wire[at++] = record->order_type;
  wire[at++] = record->action;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->new_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->new_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->previous_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id_quote_or_order_id[i]; }

  return at;
}

/* Quote Notice off the wire: 75 bytes from at, returning where the next byte lies */
static size_t decode_quote_notice(QuoteNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id_quote[i] = wire[at++]; }
  record->verb_side = wire[at++];
  record->order_type = wire[at++];
  record->action = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->new_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->new_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->previous_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id_quote_or_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Notice is what was written, byte for byte */
static void equal_quote_notice(const QuoteNotice *read, const QuoteNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id_quote[i] == written->reference_id_quote[i]); }
  assert(read->verb_side == written->verb_side);
  assert(read->order_type == written->order_type);
  assert(read->action == written->action);
  for (size_t i = 0; i < 8; i++) { assert(read->new_quantity[i] == written->new_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->new_price[i] == written->new_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_quantity[i] == written->previous_quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->previous_price[i] == written->previous_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id_quote_or_order_id[i] == written->original_reference_id_quote_or_order_id[i]); }
}

/* Quote Notice: written and read back, then read and written back */
static void check_quote_notice(void) {
  QuoteNotice sent;
  QuoteNotice got;
  uint8_t wire[75];
  uint8_t again[75];

  any_quote_notice(&sent);
  assert(encode_quote_notice(&sent, wire, 0) == 75);
  assert(decode_quote_notice(&got, wire, 0) == 75);
  equal_quote_notice(&got, &sent);

  for (size_t i = 0; i < 75; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_notice(&got, wire, 0) == 75);
  assert(encode_quote_notice(&got, again, 0) == 75);
  for (size_t i = 0; i < 75; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Cancellation Notice: 240 bytes -------------------------------- */

/* Stated by the guide as having the same number of bytes and format as NT, whose fields are written out here. */
typedef struct {
  uint8_t group[2];                                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                      /* bytes 2 to 5 */
  uint8_t trader_id[8];                                /* bytes 6 to 13 */
  uint8_t reference_id[8];                             /* bytes 14 to 21 */
  uint8_t verb_side;                                   /* byte 22 */
  uint8_t quantity_traded[8];                          /* bytes 23 to 30 */
  uint8_t trade_price[10];                             /* bytes 31 to 40 */
  uint8_t time_of_the_trade_hhmmss[6];                 /* bytes 41 to 46 */
  ClearingData clearing_data;                          /* bytes 47 to 66 */
  OwnerData owner_data;                                /* bytes 67 to 137 */
  uint8_t special_trade_indicator;                     /* byte 138 */
  uint8_t price_type;                                  /* byte 139 */
  uint8_t trade_type;                                  /* byte 140 */
  uint8_t auction_i_d_optional[6];                     /* bytes 141 to 146 */
  uint8_t trade_number[8];                             /* bytes 147 to 154 */
  uint8_t trade_memo[50];                              /* bytes 155 to 204 */
  uint8_t original_reference_id[8];                    /* bytes 205 to 212 */
  uint8_t id_code_for_the_counterpart_participant[4];  /* bytes 213 to 216 */
  uint8_t liquidity_status;                            /* byte 217 */
  uint8_t counterpart_account_type;                    /* byte 218 */
  uint8_t additional_client_memo[16];                  /* bytes 219 to 234 */
  uint8_t reserved_1;                                  /* byte 235 */
  uint8_t reserved_4[4];                               /* bytes 236 to 239 */
} ExecutionCancellationNotice;

/* any Execution Cancellation Notice at all: every byte one the checker chooses */
static void any_execution_cancellation_notice(ExecutionCancellationNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_of_the_trade_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->counterpart_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Execution Cancellation Notice to the wire: 240 bytes from at, returning where the next byte goes */
static size_t encode_execution_cancellation_notice(const ExecutionCancellationNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_of_the_trade_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->counterpart_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Execution Cancellation Notice off the wire: 240 bytes from at, returning where the next byte lies */
static size_t decode_execution_cancellation_notice(ExecutionCancellationNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_of_the_trade_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->counterpart_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Cancellation Notice is what was written, byte for byte */
static void equal_execution_cancellation_notice(const ExecutionCancellationNotice *read, const ExecutionCancellationNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id[i] == written->reference_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_of_the_trade_hhmmss[i] == written->time_of_the_trade_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->counterpart_account_type == written->counterpart_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Execution Cancellation Notice: written and read back, then read and written back */
static void check_execution_cancellation_notice(void) {
  ExecutionCancellationNotice sent;
  ExecutionCancellationNotice got;
  uint8_t wire[240];
  uint8_t again[240];

  any_execution_cancellation_notice(&sent);
  assert(encode_execution_cancellation_notice(&sent, wire, 0) == 240);
  assert(decode_execution_cancellation_notice(&got, wire, 0) == 240);
  equal_execution_cancellation_notice(&got, &sent);

  for (size_t i = 0; i < 240; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_cancellation_notice(&got, wire, 0) == 240);
  assert(encode_execution_cancellation_notice(&got, again, 0) == 240);
  for (size_t i = 0; i < 240; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Execution Cancellation Notice: 257 bytes ---------------------------- */

/* Stated by the guide as having the same number of bytes and format as NL, whose fields are written out here. */
typedef struct {
  uint8_t group[2];                                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];                      /* bytes 2 to 5 */
  uint8_t trader_id[8];                                /* bytes 6 to 13 */
  uint8_t reference_id[8];                             /* bytes 14 to 21 */
  uint8_t verb_side;                                   /* byte 22 */
  uint8_t quantity_traded[8];                          /* bytes 23 to 30 */
  uint8_t trade_price[10];                             /* bytes 31 to 40 */
  uint8_t time_trade_hhmmss[6];                        /* bytes 41 to 46 */
  ClearingData clearing_data;                          /* bytes 47 to 66 */
  OwnerData owner_data;                                /* bytes 67 to 137 */
  uint8_t special_trade_indicator;                     /* byte 138 */
  uint8_t price_type;                                  /* byte 139 */
  uint8_t trade_type;                                  /* byte 140 */
  uint8_t auction_i_d_optional[6];                     /* bytes 141 to 146 */
  uint8_t trade_number[8];                             /* bytes 147 to 154 */
  uint8_t trade_memo[50];                              /* bytes 155 to 204 */
  uint8_t original_reference_id[8];                    /* bytes 205 to 212 */
  uint8_t id_code_for_the_counterpart_participant[4];  /* bytes 213 to 216 */
  uint8_t liquidity_status;                            /* byte 217 */
  uint8_t strategy_group[2];                           /* bytes 218 to 219 */
  uint8_t strategy_instrument_id[4];                   /* bytes 220 to 223 */
  uint8_t strategy_verb_side;                          /* byte 224 */
  uint8_t strategy_trade_number[8];                    /* bytes 225 to 232 */
  uint8_t leg_number[2];                               /* bytes 233 to 234 */
  uint8_t counterpart_account_type;                    /* byte 235 */
  uint8_t additional_client_memo[16];                  /* bytes 236 to 251 */
  uint8_t reserved_1;                                  /* byte 252 */
  uint8_t reserved_4[4];                               /* bytes 253 to 256 */
} LegExecutionCancellationNotice;

/* any Leg Execution Cancellation Notice at all: every byte one the checker chooses */
static void any_leg_execution_cancellation_notice(LegExecutionCancellationNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_trade_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = arbitrary(); }
  record->strategy_verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = arbitrary(); }
  record->counterpart_account_type = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Leg Execution Cancellation Notice to the wire: 257 bytes from at, returning where the next byte goes */
static size_t encode_leg_execution_cancellation_notice(const LegExecutionCancellationNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_trade_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  wire[at++] = record->liquidity_status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strategy_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_instrument_id[i]; }
  wire[at++] = record->strategy_verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strategy_trade_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_number[i]; }
  wire[at++] = record->counterpart_account_type;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  wire[at++] = record->reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Leg Execution Cancellation Notice off the wire: 257 bytes from at, returning where the next byte lies */
static size_t decode_leg_execution_cancellation_notice(LegExecutionCancellationNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_trade_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->auction_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = wire[at++]; }
  record->strategy_verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = wire[at++]; }
  record->counterpart_account_type = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Execution Cancellation Notice is what was written, byte for byte */
static void equal_leg_execution_cancellation_notice(const LegExecutionCancellationNotice *read, const LegExecutionCancellationNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id[i] == written->reference_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_trade_hhmmss[i] == written->time_trade_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d_optional[i] == written->auction_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  for (size_t i = 0; i < 2; i++) { assert(read->strategy_group[i] == written->strategy_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_instrument_id[i] == written->strategy_instrument_id[i]); }
  assert(read->strategy_verb_side == written->strategy_verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->strategy_trade_number[i] == written->strategy_trade_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_number[i] == written->leg_number[i]); }
  assert(read->counterpart_account_type == written->counterpart_account_type);
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  assert(read->reserved_1 == written->reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Leg Execution Cancellation Notice: written and read back, then read and written back */
static void check_leg_execution_cancellation_notice(void) {
  LegExecutionCancellationNotice sent;
  LegExecutionCancellationNotice got;
  uint8_t wire[257];
  uint8_t again[257];

  any_leg_execution_cancellation_notice(&sent);
  assert(encode_leg_execution_cancellation_notice(&sent, wire, 0) == 257);
  assert(decode_leg_execution_cancellation_notice(&got, wire, 0) == 257);
  equal_leg_execution_cancellation_notice(&got, &sent);

  for (size_t i = 0; i < 257; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_execution_cancellation_notice(&got, wire, 0) == 257);
  assert(encode_leg_execution_cancellation_notice(&got, again, 0) == 257);
  for (size_t i = 0; i < 257; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Notice By System: 167 bytes -------------------------- */

/* Stated by the guide as having the same number of bytes and format as KZ, whose fields are written out here. */
typedef struct {
  uint8_t group[2];                    /* bytes 0 to 1 */
  uint8_t instrument_optional[4];      /* bytes 2 to 5 */
  uint8_t trader_id[8];                /* bytes 6 to 13 */
  uint8_t order_id[8];                 /* bytes 14 to 21 */
  uint8_t status;                      /* byte 22 */
  uint8_t verb_side;                   /* byte 23 */
  uint8_t quantity[8];                 /* bytes 24 to 31 */
  uint8_t assigned_price[10];          /* bytes 32 to 41 */
  ClearingData clearing_data;          /* bytes 42 to 61 */
  OwnerData owner_data;                /* bytes 62 to 132 */
  uint8_t original_order_id[8];        /* bytes 133 to 140 */
  uint8_t auction_i_d[6];              /* bytes 141 to 146 */
  uint8_t additional_client_memo[16];  /* bytes 147 to 162 */
  uint8_t reserved_4[4];               /* bytes 163 to 166 */
} OrderCancellationNoticeBySystem;

/* any Order Cancellation Notice By System at all: every byte one the checker chooses */
static void any_order_cancellation_notice_by_system(OrderCancellationNoticeBySystem *record) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Order Cancellation Notice By System to the wire: 167 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_notice_by_system(const OrderCancellationNoticeBySystem *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->auction_i_d[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Order Cancellation Notice By System off the wire: 167 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_notice_by_system(OrderCancellationNoticeBySystem *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->auction_i_d[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Notice By System is what was written, byte for byte */
static void equal_order_cancellation_notice_by_system(const OrderCancellationNoticeBySystem *read, const OrderCancellationNoticeBySystem *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_optional[i] == written->instrument_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->auction_i_d[i] == written->auction_i_d[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Order Cancellation Notice By System: written and read back, then read and written back */
static void check_order_cancellation_notice_by_system(void) {
  OrderCancellationNoticeBySystem sent;
  OrderCancellationNoticeBySystem got;
  uint8_t wire[167];
  uint8_t again[167];

  any_order_cancellation_notice_by_system(&sent);
  assert(encode_order_cancellation_notice_by_system(&sent, wire, 0) == 167);
  assert(decode_order_cancellation_notice_by_system(&got, wire, 0) == 167);
  equal_order_cancellation_notice_by_system(&got, &sent);

  for (size_t i = 0; i < 167; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_notice_by_system(&got, wire, 0) == 167);
  assert(encode_order_cancellation_notice_by_system(&got, again, 0) == 167);
  for (size_t i = 0; i < 167; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_outgoing_header();
  check_heartbeat_question();
  check_out_of_sequence();
  check_technical_error_notice();
  check_disconnection_instruction_acknowledgement();
  check_connection_acknowledgement();
  check_disconnection_acknowledgement();
  check_end_of_transmission();
  check_error_notice();
  check_bulk_quote_data_acknowledgement();
  check_clearing_data();
  check_owner_data();
  check_order_acknowledgement();
  check_global_cancellation_confirmation();
  check_improvement_order_acknowlegment();
  check_order_modification_acknowledgement();
  check_standard_acknowledgement();
  check_complex_order_auction_acknowledgement();
  check_auction_or_improvement_cancellation_acknowledgement();
  check_order_cancellation_acknowledgement();
  check_trader_status();
  check_directed_order_cancellation_notice();
  check_directed_order_notice();
  check_excluded_instrument_notice();
  check_group_state_change();
  check_leg_execution_notice();
  check_cancellation_of_all_quotes_notices();
  check_quality_market_maker_notification();
  check_execution_notice();
  check_quote_notice();
  check_execution_cancellation_notice();
  check_leg_execution_cancellation_notice();
  check_order_cancellation_notice_by_system();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
