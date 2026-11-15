// tmx/mx/solaorderentry/Mx_SolaOrderEntry_v1_21_Exchange.c
/*
 * TMX Group Sola Order Entry
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

/* ---- Connection Acknowledgement: 12 bytes ------------------------------------ */

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

/* ---- Heartbeat Question: 20 bytes -------------------------------------------- */

typedef struct {
  uint8_t user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[8];  /* bytes 0 to 7 */
  uint8_t last_exchange_message_id_sent_to_participant[6];                              /* bytes 8 to 13 */
  uint8_t trading_engine_timestamp_local_hhmmss[6];                                     /* bytes 14 to 19 */
} HeartbeatQuestion;

/* any Heartbeat Question at all: every byte one the checker chooses */
static void any_heartbeat_question(HeartbeatQuestion *record) {
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = arbitrary(); }
}

/* Heartbeat Question to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_question(const HeartbeatQuestion *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->last_exchange_message_id_sent_to_participant[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_local_hhmmss[i]; }

  return at;
}

/* Heartbeat Question off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_question(HeartbeatQuestion *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->last_exchange_message_id_sent_to_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Question is what was written, byte for byte */
static void equal_heartbeat_question(const HeartbeatQuestion *read, const HeartbeatQuestion *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i] == written->user_sequence_id_first_user_sequence_id_for_nextcurrent_heartbeat_period[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->last_exchange_message_id_sent_to_participant[i] == written->last_exchange_message_id_sent_to_participant[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_local_hhmmss[i] == written->trading_engine_timestamp_local_hhmmss[i]); }
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
  uint8_t received_user_sequence_id[8];            /* bytes 0 to 7 */
  uint8_t expected_last_user_sequence_id[8];       /* bytes 8 to 15 */
  uint8_t user_message_timestamp_local_hhmmss[6];  /* bytes 16 to 21 */
} OutOfSequence;

/* any Out Of Sequence at all: every byte one the checker chooses */
static void any_out_of_sequence(OutOfSequence *record) {
  for (size_t i = 0; i < 8; i++) { record->received_user_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->expected_last_user_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->user_message_timestamp_local_hhmmss[i] = arbitrary(); }
}

/* Out Of Sequence to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_out_of_sequence(const OutOfSequence *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->received_user_sequence_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->expected_last_user_sequence_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->user_message_timestamp_local_hhmmss[i]; }

  return at;
}

/* Out Of Sequence off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_out_of_sequence(OutOfSequence *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->received_user_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->expected_last_user_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->user_message_timestamp_local_hhmmss[i] = wire[at++]; }

  return at;
}

/* what was read of Out Of Sequence is what was written, byte for byte */
static void equal_out_of_sequence(const OutOfSequence *read, const OutOfSequence *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->received_user_sequence_id[i] == written->received_user_sequence_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->expected_last_user_sequence_id[i] == written->expected_last_user_sequence_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->user_message_timestamp_local_hhmmss[i] == written->user_message_timestamp_local_hhmmss[i]); }
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
  uint8_t received_message_type[2];                               /* bytes 0 to 1 */
  uint8_t preceding_user_sequence_id_received_zeroes_if_none[8];  /* bytes 2 to 9 */
  uint8_t error_code[4];                                          /* bytes 10 to 13 */
  uint8_t error_position[4];                                      /* bytes 14 to 17 */
  uint8_t error_message[100];                                     /* bytes 18 to 117 */
  uint8_t start_of_message_in_error[100];                         /* bytes 118 to 217 */
} TechnicalErrorNotice;

/* any Technical Error Notice at all: every byte one the checker chooses */
static void any_technical_error_notice(TechnicalErrorNotice *record) {
  for (size_t i = 0; i < 2; i++) { record->received_message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->preceding_user_sequence_id_received_zeroes_if_none[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_position[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->error_message[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->start_of_message_in_error[i] = arbitrary(); }
}

/* Technical Error Notice to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_technical_error_notice(const TechnicalErrorNotice *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->received_message_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->preceding_user_sequence_id_received_zeroes_if_none[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_position[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->error_message[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->start_of_message_in_error[i]; }

  return at;
}

/* Technical Error Notice off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_technical_error_notice(TechnicalErrorNotice *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->received_message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->preceding_user_sequence_id_received_zeroes_if_none[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_position[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->error_message[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->start_of_message_in_error[i] = wire[at++]; }

  return at;
}

/* what was read of Technical Error Notice is what was written, byte for byte */
static void equal_technical_error_notice(const TechnicalErrorNotice *read, const TechnicalErrorNotice *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->received_message_type[i] == written->received_message_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->preceding_user_sequence_id_received_zeroes_if_none[i] == written->preceding_user_sequence_id_received_zeroes_if_none[i]); }
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

/* ---- Disconnection Acknowledgement: 12 bytes --------------------------------- */

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
  uint8_t ended_session_id[4];                                                                  /* bytes 0 to 3 */
  uint8_t last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[8];  /* bytes 4 to 11 */
  uint8_t trading_engine_timestamp_local_hhmmss[6];                                             /* bytes 12 to 17 */
} EndOfTransmission;

/* any End Of Transmission at all: every byte one the checker chooses */
static void any_end_of_transmission(EndOfTransmission *record) {
  for (size_t i = 0; i < 4; i++) { record->ended_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = arbitrary(); }
}

/* End Of Transmission to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_end_of_transmission(const EndOfTransmission *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ended_session_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_local_hhmmss[i]; }

  return at;
}

/* End Of Transmission off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_end_of_transmission(EndOfTransmission *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ended_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = wire[at++]; }

  return at;
}

/* what was read of End Of Transmission is what was written, byte for byte */
static void equal_end_of_transmission(const EndOfTransmission *read, const EndOfTransmission *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ended_session_id[i] == written->ended_session_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[i] == written->last_user_sequence_id_received_if_no_business_message_has_been_received_o_soi8v5[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_local_hhmmss[i] == written->trading_engine_timestamp_local_hhmmss[i]); }
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

/* ---- Outgoing Messages Header: 22 bytes -------------------------------------- */

/* The guide states these fields once, as the Outgoing Messages Header, for every business message the Exchange sends. Message Type is read by the packet before the branch, so it is not repeated here. */
typedef struct {
  uint8_t trading_engine_timestamp_local_hhmmss[6];  /* bytes 0 to 5 */
  uint8_t user_sequence_id[8];                       /* bytes 6 to 13 */
  uint8_t exchange_message_id[6];                    /* bytes 14 to 19 */
  uint8_t gap_sequence_id[2];                        /* bytes 20 to 21 */
} OutgoingMessagesHeader;

/* any Outgoing Messages Header at all: every byte one the checker chooses */
static void any_outgoing_messages_header(OutgoingMessagesHeader *record) {
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->exchange_message_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->gap_sequence_id[i] = arbitrary(); }
}

/* Outgoing Messages Header to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_outgoing_messages_header(const OutgoingMessagesHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_local_hhmmss[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_sequence_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->exchange_message_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->gap_sequence_id[i]; }

  return at;
}

/* Outgoing Messages Header off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_outgoing_messages_header(OutgoingMessagesHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_local_hhmmss[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->exchange_message_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->gap_sequence_id[i] = wire[at++]; }

  return at;
}

/* what was read of Outgoing Messages Header is what was written, byte for byte */
static void equal_outgoing_messages_header(const OutgoingMessagesHeader *read, const OutgoingMessagesHeader *written) {
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_local_hhmmss[i] == written->trading_engine_timestamp_local_hhmmss[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_sequence_id[i] == written->user_sequence_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->exchange_message_id[i] == written->exchange_message_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->gap_sequence_id[i] == written->gap_sequence_id[i]); }
}

/* Outgoing Messages Header: written and read back, then read and written back */
static void check_outgoing_messages_header(void) {
  OutgoingMessagesHeader sent;
  OutgoingMessagesHeader got;
  uint8_t wire[22];
  uint8_t again[22];

  any_outgoing_messages_header(&sent);
  assert(encode_outgoing_messages_header(&sent, wire, 0) == 22);
  assert(decode_outgoing_messages_header(&got, wire, 0) == 22);
  equal_outgoing_messages_header(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_outgoing_messages_header(&got, wire, 0) == 22);
  assert(encode_outgoing_messages_header(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Data: 20 bytes ------------------------------------------------- */

/* The guide states these fields once, as Clearing Data, for every message that carries them. */
typedef struct {
  uint8_t clearing_instruction[12];  /* bytes 0 to 11 */
  uint8_t account_type;              /* byte 12 */
  uint8_t open_close;                /* byte 13 */
  uint8_t hedge_spec;                /* byte 14 */
  uint8_t filler_5[5];               /* bytes 15 to 19 */
} ClearingData;

/* any Clearing Data at all: every byte one the checker chooses */
static void any_clearing_data(ClearingData *record) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  record->hedge_spec = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = arbitrary(); }
}

/* Clearing Data to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_clearing_data(const ClearingData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->clearing_instruction[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  wire[at++] = record->hedge_spec;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->filler_5[i]; }

  return at;
}

/* Clearing Data off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_clearing_data(ClearingData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 12; i++) { record->clearing_instruction[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  record->hedge_spec = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->filler_5[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Data is what was written, byte for byte */
static void equal_clearing_data(const ClearingData *read, const ClearingData *written) {
  for (size_t i = 0; i < 12; i++) { assert(read->clearing_instruction[i] == written->clearing_instruction[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  assert(read->hedge_spec == written->hedge_spec);
  for (size_t i = 0; i < 5; i++) { assert(read->filler_5[i] == written->filler_5[i]); }
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

/* ---- Owner Data: 50 bytes ---------------------------------------------------- */

/* The guide states this field once, as Owner Data, for every message that carries it. */
typedef struct {
  uint8_t memo[50];  /* bytes 0 to 49 */
} OwnerData;

/* any Owner Data at all: every byte one the checker chooses */
static void any_owner_data(OwnerData *record) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Owner Data to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_owner_data(const OwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Owner Data off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_owner_data(OwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Owner Data is what was written, byte for byte */
static void equal_owner_data(const OwnerData *read, const OwnerData *written) {
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Owner Data: written and read back, then read and written back */
static void check_owner_data(void) {
  OwnerData sent;
  OwnerData got;
  uint8_t wire[50];
  uint8_t again[50];

  any_owner_data(&sent);
  assert(encode_owner_data(&sent, wire, 0) == 50);
  assert(decode_owner_data(&got, wire, 0) == 50);
  equal_owner_data(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_owner_data(&got, wire, 0) == 50);
  assert(encode_owner_data(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Reply: 134 bytes -------------------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t order_id[8];                              /* bytes 36 to 43 */
  uint8_t status;                                   /* byte 44 */
  uint8_t verb_side;                                /* byte 45 */
  uint8_t quantity_remaining[8];                    /* bytes 46 to 53 */
  uint8_t assigned_price[10];                       /* bytes 54 to 63 */
  ClearingData clearing_data;                       /* bytes 64 to 83 */
  OwnerData owner_data;                             /* bytes 84 to 133 */
} OrderReply;

/* any Order Reply at all: every byte one the checker chooses */
static void any_order_reply(OrderReply *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_remaining[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
}

/* Order Reply to the wire: 134 bytes from at, returning where the next byte goes */
static size_t encode_order_reply(const OrderReply *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_remaining[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);

  return at;
}

/* Order Reply off the wire: 134 bytes from at, returning where the next byte lies */
static size_t decode_order_reply(OrderReply *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_remaining[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);

  return at;
}

/* what was read of Order Reply is what was written, byte for byte */
static void equal_order_reply(const OrderReply *read, const OrderReply *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_remaining[i] == written->quantity_remaining[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
}

/* Order Reply: written and read back, then read and written back */
static void check_order_reply(void) {
  OrderReply sent;
  OrderReply got;
  uint8_t wire[134];
  uint8_t again[134];

  any_order_reply(&sent);
  assert(encode_order_reply(&sent, wire, 0) == 134);
  assert(decode_order_reply(&got, wire, 0) == 134);
  equal_order_reply(&got, &sent);

  for (size_t i = 0; i < 134; i++) { wire[i] = arbitrary(); }
  assert(decode_order_reply(&got, wire, 0) == 134);
  assert(encode_order_reply(&got, again, 0) == 134);
  for (size_t i = 0; i < 134; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Notice: 126 bytes ------------------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t error_code[4];                            /* bytes 22 to 25 */
  uint8_t error_description[100];                   /* bytes 26 to 125 */
} ErrorNotice;

/* any Error Notice at all: every byte one the checker chooses */
static void any_error_notice(ErrorNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->error_description[i] = arbitrary(); }
}

/* Error Notice to the wire: 126 bytes from at, returning where the next byte goes */
static size_t encode_error_notice(const ErrorNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->error_description[i]; }

  return at;
}

/* Error Notice off the wire: 126 bytes from at, returning where the next byte lies */
static size_t decode_error_notice(ErrorNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->error_description[i] = wire[at++]; }

  return at;
}

/* what was read of Error Notice is what was written, byte for byte */
static void equal_error_notice(const ErrorNotice *read, const ErrorNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 4; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->error_description[i] == written->error_description[i]); }
}

/* Error Notice: written and read back, then read and written back */
static void check_error_notice(void) {
  ErrorNotice sent;
  ErrorNotice got;
  uint8_t wire[126];
  uint8_t again[126];

  any_error_notice(&sent);
  assert(encode_error_notice(&sent, wire, 0) == 126);
  assert(decode_error_notice(&got, wire, 0) == 126);
  equal_error_notice(&got, &sent);

  for (size_t i = 0; i < 126; i++) { wire[i] = arbitrary(); }
  assert(decode_error_notice(&got, wire, 0) == 126);
  assert(encode_error_notice(&got, again, 0) == 126);
  for (size_t i = 0; i < 126; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulk Quote Data Acknowledgement: 40 bytes ------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;             /* bytes 0 to 21 */
  uint8_t group[2];                                            /* bytes 22 to 23 */
  uint8_t trader_id[8];                                        /* bytes 24 to 31 */
  uint8_t quote_id_identifies_traders_quote_on_this_group[8];  /* bytes 32 to 39 */
} BulkQuoteDataAcknowledgement;

/* any Bulk Quote Data Acknowledgement at all: every byte one the checker chooses */
static void any_bulk_quote_data_acknowledgement(BulkQuoteDataAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quote_id_identifies_traders_quote_on_this_group[i] = arbitrary(); }
}

/* Bulk Quote Data Acknowledgement to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_bulk_quote_data_acknowledgement(const BulkQuoteDataAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quote_id_identifies_traders_quote_on_this_group[i]; }

  return at;
}

/* Bulk Quote Data Acknowledgement off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_bulk_quote_data_acknowledgement(BulkQuoteDataAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quote_id_identifies_traders_quote_on_this_group[i] = wire[at++]; }

  return at;
}

/* what was read of Bulk Quote Data Acknowledgement is what was written, byte for byte */
static void equal_bulk_quote_data_acknowledgement(const BulkQuoteDataAcknowledgement *read, const BulkQuoteDataAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quote_id_identifies_traders_quote_on_this_group[i] == written->quote_id_identifies_traders_quote_on_this_group[i]); }
}

/* Bulk Quote Data Acknowledgement: written and read back, then read and written back */
static void check_bulk_quote_data_acknowledgement(void) {
  BulkQuoteDataAcknowledgement sent;
  BulkQuoteDataAcknowledgement got;
  uint8_t wire[40];
  uint8_t again[40];

  any_bulk_quote_data_acknowledgement(&sent);
  assert(encode_bulk_quote_data_acknowledgement(&sent, wire, 0) == 40);
  assert(decode_bulk_quote_data_acknowledgement(&got, wire, 0) == 40);
  equal_bulk_quote_data_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_bulk_quote_data_acknowledgement(&got, wire, 0) == 40);
  assert(encode_bulk_quote_data_acknowledgement(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Acknowledgement: 148 bytes ---------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t order_id[8];                              /* bytes 36 to 43 */
  uint8_t status;                                   /* byte 44 */
  uint8_t verb_side;                                /* byte 45 */
  uint8_t quantity[8];                              /* bytes 46 to 53 */
  uint8_t assigned_price[10];                       /* bytes 54 to 63 */
  ClearingData clearing_data;                       /* bytes 64 to 83 */
  OwnerData owner_data;                             /* bytes 84 to 133 */
  uint8_t original_order_id[8];                     /* bytes 134 to 141 */
  uint8_t filler_6[6];                              /* bytes 142 to 147 */
} OrderAcknowledgement;

/* any Order Acknowledgement at all: every byte one the checker chooses */
static void any_order_acknowledgement(OrderAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
}

/* Order Acknowledgement to the wire: 148 bytes from at, returning where the next byte goes */
static size_t encode_order_acknowledgement(const OrderAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }

  return at;
}

/* Order Acknowledgement off the wire: 148 bytes from at, returning where the next byte lies */
static size_t decode_order_acknowledgement(OrderAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }

  return at;
}

/* what was read of Order Acknowledgement is what was written, byte for byte */
static void equal_order_acknowledgement(const OrderAcknowledgement *read, const OrderAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
}

/* Order Acknowledgement: written and read back, then read and written back */
static void check_order_acknowledgement(void) {
  OrderAcknowledgement sent;
  OrderAcknowledgement got;
  uint8_t wire[148];
  uint8_t again[148];

  any_order_acknowledgement(&sent);
  assert(encode_order_acknowledgement(&sent, wire, 0) == 148);
  assert(decode_order_acknowledgement(&got, wire, 0) == 148);
  equal_order_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 148; i++) { wire[i] = arbitrary(); }
  assert(decode_order_acknowledgement(&got, wire, 0) == 148);
  assert(encode_order_acknowledgement(&got, again, 0) == 148);
  for (size_t i = 0; i < 148; i++) { assert(again[i] == wire[i]); }
}

/* ---- Global Cancellation Confirmation: 33 bytes ------------------------------ */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;                  /* bytes 0 to 21 */
  uint8_t group[2];                                                 /* bytes 22 to 23 */
  uint8_t trader_id[8];                                             /* bytes 24 to 31 */
  uint8_t type_of_cancellation_only_q_quotes_only_can_be_returned;  /* byte 32 */
} GlobalCancellationConfirmation;

/* any Global Cancellation Confirmation at all: every byte one the checker chooses */
static void any_global_cancellation_confirmation(GlobalCancellationConfirmation *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->type_of_cancellation_only_q_quotes_only_can_be_returned = arbitrary();
}

/* Global Cancellation Confirmation to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_global_cancellation_confirmation(const GlobalCancellationConfirmation *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->type_of_cancellation_only_q_quotes_only_can_be_returned;

  return at;
}

/* Global Cancellation Confirmation off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_global_cancellation_confirmation(GlobalCancellationConfirmation *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->type_of_cancellation_only_q_quotes_only_can_be_returned = wire[at++];

  return at;
}

/* what was read of Global Cancellation Confirmation is what was written, byte for byte */
static void equal_global_cancellation_confirmation(const GlobalCancellationConfirmation *read, const GlobalCancellationConfirmation *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->type_of_cancellation_only_q_quotes_only_can_be_returned == written->type_of_cancellation_only_q_quotes_only_can_be_returned);
}

/* Global Cancellation Confirmation: written and read back, then read and written back */
static void check_global_cancellation_confirmation(void) {
  GlobalCancellationConfirmation sent;
  GlobalCancellationConfirmation got;
  uint8_t wire[33];
  uint8_t again[33];

  any_global_cancellation_confirmation(&sent);
  assert(encode_global_cancellation_confirmation(&sent, wire, 0) == 33);
  assert(decode_global_cancellation_confirmation(&got, wire, 0) == 33);
  equal_global_cancellation_confirmation(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_global_cancellation_confirmation(&got, wire, 0) == 33);
  assert(encode_global_cancellation_confirmation(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Modification Acknowledgement: 148 bytes --------------------------- */

/* This message is sent by the Exchange to acknowledge an OM: Order Modification message. This message has the same format as the KE: Order Acknowledgement (the extensive list of fields is only described there), KZ: Order Cancellation Acknowledgement and NZ: Order Cancellation Notice (by MOD or System) messages. */
typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t order_id[8];                              /* bytes 36 to 43 */
  uint8_t status;                                   /* byte 44 */
  uint8_t verb_side;                                /* byte 45 */
  uint8_t quantity[8];                              /* bytes 46 to 53 */
  uint8_t assigned_price[10];                       /* bytes 54 to 63 */
  ClearingData clearing_data;                       /* bytes 64 to 83 */
  OwnerData owner_data;                             /* bytes 84 to 133 */
  uint8_t original_order_id[8];                     /* bytes 134 to 141 */
  uint8_t filler_6[6];                              /* bytes 142 to 147 */
} OrderModificationAcknowledgement;

/* any Order Modification Acknowledgement at all: every byte one the checker chooses */
static void any_order_modification_acknowledgement(OrderModificationAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
}

/* Order Modification Acknowledgement to the wire: 148 bytes from at, returning where the next byte goes */
static size_t encode_order_modification_acknowledgement(const OrderModificationAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }

  return at;
}

/* Order Modification Acknowledgement off the wire: 148 bytes from at, returning where the next byte lies */
static size_t decode_order_modification_acknowledgement(OrderModificationAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }

  return at;
}

/* what was read of Order Modification Acknowledgement is what was written, byte for byte */
static void equal_order_modification_acknowledgement(const OrderModificationAcknowledgement *read, const OrderModificationAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
}

/* Order Modification Acknowledgement: written and read back, then read and written back */
static void check_order_modification_acknowledgement(void) {
  OrderModificationAcknowledgement sent;
  OrderModificationAcknowledgement got;
  uint8_t wire[148];
  uint8_t again[148];

  any_order_modification_acknowledgement(&sent);
  assert(encode_order_modification_acknowledgement(&sent, wire, 0) == 148);
  assert(decode_order_modification_acknowledgement(&got, wire, 0) == 148);
  equal_order_modification_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 148; i++) { wire[i] = arbitrary(); }
  assert(decode_order_modification_acknowledgement(&got, wire, 0) == 148);
  assert(encode_order_modification_acknowledgement(&got, again, 0) == 148);
  for (size_t i = 0; i < 148; i++) { assert(again[i] == wire[i]); }
}

/* ---- Standard Acknowledgement: 32 bytes -------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;     /* bytes 0 to 21 */
  uint8_t trader_id[8];                                /* bytes 22 to 29 */
  uint8_t original_message_type_af_gz_ml_ox_or_rq[2];  /* bytes 30 to 31 */
} StandardAcknowledgement;

/* any Standard Acknowledgement at all: every byte one the checker chooses */
static void any_standard_acknowledgement(StandardAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->original_message_type_af_gz_ml_ox_or_rq[i] = arbitrary(); }
}

/* Standard Acknowledgement to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_standard_acknowledgement(const StandardAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->original_message_type_af_gz_ml_ox_or_rq[i]; }

  return at;
}

/* Standard Acknowledgement off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_standard_acknowledgement(StandardAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->original_message_type_af_gz_ml_ox_or_rq[i] = wire[at++]; }

  return at;
}

/* what was read of Standard Acknowledgement is what was written, byte for byte */
static void equal_standard_acknowledgement(const StandardAcknowledgement *read, const StandardAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->original_message_type_af_gz_ml_ox_or_rq[i] == written->original_message_type_af_gz_ml_ox_or_rq[i]); }
}

/* Standard Acknowledgement: written and read back, then read and written back */
static void check_standard_acknowledgement(void) {
  StandardAcknowledgement sent;
  StandardAcknowledgement got;
  uint8_t wire[32];
  uint8_t again[32];

  any_standard_acknowledgement(&sent);
  assert(encode_standard_acknowledgement(&sent, wire, 0) == 32);
  assert(decode_standard_acknowledgement(&got, wire, 0) == 32);
  equal_standard_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_standard_acknowledgement(&got, wire, 0) == 32);
  assert(encode_standard_acknowledgement(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Acknowledgement: 148 bytes --------------------------- */

/* This message is to acknowledge an XE: Order Cancellation message. This message has the same number of bytes and format as the KE: Order Acknowledgement (the extensive list of fields is only described there), the KM: Order Modification Acknowledgement and the NZ: Order Cancellation Notice (by MOD or System) messages. */
typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t order_id[8];                              /* bytes 36 to 43 */
  uint8_t status;                                   /* byte 44 */
  uint8_t verb_side;                                /* byte 45 */
  uint8_t quantity[8];                              /* bytes 46 to 53 */
  uint8_t assigned_price[10];                       /* bytes 54 to 63 */
  ClearingData clearing_data;                       /* bytes 64 to 83 */
  OwnerData owner_data;                             /* bytes 84 to 133 */
  uint8_t original_order_id[8];                     /* bytes 134 to 141 */
  uint8_t filler_6[6];                              /* bytes 142 to 147 */
} OrderCancellationAcknowledgement;

/* any Order Cancellation Acknowledgement at all: every byte one the checker chooses */
static void any_order_cancellation_acknowledgement(OrderCancellationAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
}

/* Order Cancellation Acknowledgement to the wire: 148 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_acknowledgement(const OrderCancellationAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }

  return at;
}

/* Order Cancellation Acknowledgement off the wire: 148 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_acknowledgement(OrderCancellationAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Acknowledgement is what was written, byte for byte */
static void equal_order_cancellation_acknowledgement(const OrderCancellationAcknowledgement *read, const OrderCancellationAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
}

/* Order Cancellation Acknowledgement: written and read back, then read and written back */
static void check_order_cancellation_acknowledgement(void) {
  OrderCancellationAcknowledgement sent;
  OrderCancellationAcknowledgement got;
  uint8_t wire[148];
  uint8_t again[148];

  any_order_cancellation_acknowledgement(&sent);
  assert(encode_order_cancellation_acknowledgement(&sent, wire, 0) == 148);
  assert(decode_order_cancellation_acknowledgement(&got, wire, 0) == 148);
  equal_order_cancellation_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 148; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_acknowledgement(&got, wire, 0) == 148);
  assert(encode_order_cancellation_acknowledgement(&got, again, 0) == 148);
  for (size_t i = 0; i < 148; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group State Change: 25 bytes -------------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t group_state;                              /* byte 24 */
} GroupStateChange;

/* any Group State Change at all: every byte one the checker chooses */
static void any_group_state_change(GroupStateChange *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  record->group_state = arbitrary();
}

/* Group State Change to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_group_state_change(const GroupStateChange *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  wire[at++] = record->group_state;

  return at;
}

/* Group State Change off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_group_state_change(GroupStateChange *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  record->group_state = wire[at++];

  return at;
}

/* what was read of Group State Change is what was written, byte for byte */
static void equal_group_state_change(const GroupStateChange *read, const GroupStateChange *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  assert(read->group_state == written->group_state);
}

/* Group State Change: written and read back, then read and written back */
static void check_group_state_change(void) {
  GroupStateChange sent;
  GroupStateChange got;
  uint8_t wire[25];
  uint8_t again[25];

  any_group_state_change(&sent);
  assert(encode_group_state_change(&sent, wire, 0) == 25);
  assert(decode_group_state_change(&got, wire, 0) == 25);
  equal_group_state_change(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_group_state_change(&got, wire, 0) == 25);
  assert(encode_group_state_change(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument State Change: 29 bytes --------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t instrument_state;                         /* byte 28 */
} InstrumentStateChange;

/* any Instrument State Change at all: every byte one the checker chooses */
static void any_instrument_state_change(InstrumentStateChange *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  record->instrument_state = arbitrary();
}

/* Instrument State Change to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_instrument_state_change(const InstrumentStateChange *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->instrument_state;

  return at;
}

/* Instrument State Change off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_instrument_state_change(InstrumentStateChange *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  record->instrument_state = wire[at++];

  return at;
}

/* what was read of Instrument State Change is what was written, byte for byte */
static void equal_instrument_state_change(const InstrumentStateChange *read, const InstrumentStateChange *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->instrument_state == written->instrument_state);
}

/* Instrument State Change: written and read back, then read and written back */
static void check_instrument_state_change(void) {
  InstrumentStateChange sent;
  InstrumentStateChange got;
  uint8_t wire[29];
  uint8_t again[29];

  any_instrument_state_change(&sent);
  assert(encode_instrument_state_change(&sent, wire, 0) == 29);
  assert(decode_instrument_state_change(&got, wire, 0) == 29);
  equal_instrument_state_change(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_state_change(&got, wire, 0) == 29);
  assert(encode_instrument_state_change(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Execution Notice: 235 bytes ----------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;                /* bytes 0 to 21 */
  uint8_t group[2];                                               /* bytes 22 to 23 */
  uint8_t instrument[4];                                          /* bytes 24 to 27 */
  uint8_t trader_id[8];                                           /* bytes 28 to 35 */
  uint8_t reference_id_order_id_or_quote_id[8];                   /* bytes 36 to 43 */
  uint8_t verb_side;                                              /* byte 44 */
  uint8_t quantity_traded[8];                                     /* bytes 45 to 52 */
  uint8_t trade_price[10];                                        /* bytes 53 to 62 */
  uint8_t trading_engine_timestamp_of_the_trade_local_hhmmss[6];  /* bytes 63 to 68 */
  ClearingData clearing_data;                                     /* bytes 69 to 88 */
  OwnerData owner_data;                                           /* bytes 89 to 138 */
  uint8_t special_trade_indicator;                                /* byte 139 */
  uint8_t price_type;                                             /* byte 140 */
  uint8_t trade_type;                                             /* byte 141 */
  uint8_t filler_6[6];                                            /* bytes 142 to 147 */
  uint8_t trade_number[8];                                        /* bytes 148 to 155 */
  uint8_t trade_memo[50];                                         /* bytes 156 to 205 */
  uint8_t original_reference_id[8];                               /* bytes 206 to 213 */
  uint8_t id_code_for_the_counterpart_participant[4];             /* bytes 214 to 217 */
  uint8_t strategy_group[2];                                      /* bytes 218 to 219 */
  uint8_t strategy_instrument_id[4];                              /* bytes 220 to 223 */
  uint8_t strategy_verb_side;                                     /* byte 224 */
  uint8_t strategy_trade_number[8];                               /* bytes 225 to 232 */
  uint8_t leg_number[2];                                          /* bytes 233 to 234 */
} LegExecutionNotice;

/* any Leg Execution Notice at all: every byte one the checker chooses */
static void any_leg_execution_notice(LegExecutionNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = arbitrary(); }
  record->strategy_verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = arbitrary(); }
}

/* Leg Execution Notice to the wire: 235 bytes from at, returning where the next byte goes */
static size_t encode_leg_execution_notice(const LegExecutionNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id_order_id_or_quote_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_of_the_trade_local_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strategy_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_instrument_id[i]; }
  wire[at++] = record->strategy_verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strategy_trade_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_number[i]; }

  return at;
}

/* Leg Execution Notice off the wire: 235 bytes from at, returning where the next byte lies */
static size_t decode_leg_execution_notice(LegExecutionNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = wire[at++]; }
  record->strategy_verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Execution Notice is what was written, byte for byte */
static void equal_leg_execution_notice(const LegExecutionNotice *read, const LegExecutionNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id_order_id_or_quote_id[i] == written->reference_id_order_id_or_quote_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_of_the_trade_local_hhmmss[i] == written->trading_engine_timestamp_of_the_trade_local_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->strategy_group[i] == written->strategy_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_instrument_id[i] == written->strategy_instrument_id[i]); }
  assert(read->strategy_verb_side == written->strategy_verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->strategy_trade_number[i] == written->strategy_trade_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_number[i] == written->leg_number[i]); }
}

/* Leg Execution Notice: written and read back, then read and written back */
static void check_leg_execution_notice(void) {
  LegExecutionNotice sent;
  LegExecutionNotice got;
  uint8_t wire[235];
  uint8_t again[235];

  any_leg_execution_notice(&sent);
  assert(encode_leg_execution_notice(&sent, wire, 0) == 235);
  assert(decode_leg_execution_notice(&got, wire, 0) == 235);
  equal_leg_execution_notice(&got, &sent);

  for (size_t i = 0; i < 235; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_execution_notice(&got, wire, 0) == 235);
  assert(encode_leg_execution_notice(&got, again, 0) == 235);
  for (size_t i = 0; i < 235; i++) { assert(again[i] == wire[i]); }
}

/* ---- Counterpart Owner Data: 50 bytes ---------------------------------------- */

/* Owner Data of the counterpart, which NO: Overstepped Order or Quote Notice carries. */
typedef struct {
  uint8_t memo[50];  /* bytes 0 to 49 */
} CounterpartOwnerData;

/* any Counterpart Owner Data at all: every byte one the checker chooses */
static void any_counterpart_owner_data(CounterpartOwnerData *record) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = arbitrary(); }
}

/* Counterpart Owner Data to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_counterpart_owner_data(const CounterpartOwnerData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Counterpart Owner Data off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_counterpart_owner_data(CounterpartOwnerData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 50; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Counterpart Owner Data is what was written, byte for byte */
static void equal_counterpart_owner_data(const CounterpartOwnerData *read, const CounterpartOwnerData *written) {
  for (size_t i = 0; i < 50; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Counterpart Owner Data: written and read back, then read and written back */
static void check_counterpart_owner_data(void) {
  CounterpartOwnerData sent;
  CounterpartOwnerData got;
  uint8_t wire[50];
  uint8_t again[50];

  any_counterpart_owner_data(&sent);
  assert(encode_counterpart_owner_data(&sent, wire, 0) == 50);
  assert(decode_counterpart_owner_data(&got, wire, 0) == 50);
  equal_counterpart_owner_data(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_counterpart_owner_data(&got, wire, 0) == 50);
  assert(encode_counterpart_owner_data(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overstepped Order Or Quote Notice: 112 bytes ---------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t verb;                                     /* byte 28 */
  uint8_t order_type;                               /* byte 29 */
  uint8_t trader_id[8];                             /* bytes 30 to 37 */
  uint8_t order_id[8];                              /* bytes 38 to 45 */
  uint8_t counterpart_trader_id[8];                 /* bytes 46 to 53 */
  uint8_t counterpart_order_id[8];                  /* bytes 54 to 61 */
  CounterpartOwnerData counterpart_owner_data;      /* bytes 62 to 111 */
} OversteppedOrderOrQuoteNotice;

/* any Overstepped Order Or Quote Notice at all: every byte one the checker chooses */
static void any_overstepped_order_or_quote_notice(OversteppedOrderOrQuoteNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  record->verb = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->counterpart_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->counterpart_order_id[i] = arbitrary(); }
  any_counterpart_owner_data(&record->counterpart_owner_data);
}

/* Overstepped Order Or Quote Notice to the wire: 112 bytes from at, returning where the next byte goes */
static size_t encode_overstepped_order_or_quote_notice(const OversteppedOrderOrQuoteNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  wire[at++] = record->verb;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->counterpart_trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->counterpart_order_id[i]; }
  at = encode_counterpart_owner_data(&record->counterpart_owner_data, wire, at);

  return at;
}

/* Overstepped Order Or Quote Notice off the wire: 112 bytes from at, returning where the next byte lies */
static size_t decode_overstepped_order_or_quote_notice(OversteppedOrderOrQuoteNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  record->verb = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->counterpart_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->counterpart_order_id[i] = wire[at++]; }
  at = decode_counterpart_owner_data(&record->counterpart_owner_data, wire, at);

  return at;
}

/* what was read of Overstepped Order Or Quote Notice is what was written, byte for byte */
static void equal_overstepped_order_or_quote_notice(const OversteppedOrderOrQuoteNotice *read, const OversteppedOrderOrQuoteNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  assert(read->verb == written->verb);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->counterpart_trader_id[i] == written->counterpart_trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->counterpart_order_id[i] == written->counterpart_order_id[i]); }
  equal_counterpart_owner_data(&read->counterpart_owner_data, &written->counterpart_owner_data);
}

/* Overstepped Order Or Quote Notice: written and read back, then read and written back */
static void check_overstepped_order_or_quote_notice(void) {
  OversteppedOrderOrQuoteNotice sent;
  OversteppedOrderOrQuoteNotice got;
  uint8_t wire[112];
  uint8_t again[112];

  any_overstepped_order_or_quote_notice(&sent);
  assert(encode_overstepped_order_or_quote_notice(&sent, wire, 0) == 112);
  assert(decode_overstepped_order_or_quote_notice(&got, wire, 0) == 112);
  equal_overstepped_order_or_quote_notice(&got, &sent);

  for (size_t i = 0; i < 112; i++) { wire[i] = arbitrary(); }
  assert(decode_overstepped_order_or_quote_notice(&got, wire, 0) == 112);
  assert(encode_overstepped_order_or_quote_notice(&got, again, 0) == 112);
  for (size_t i = 0; i < 112; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancellation Of All Quotes Notice: 37 bytes ----------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t cancel_reason;                            /* byte 36 */
} CancellationOfAllQuotesNotice;

/* any Cancellation Of All Quotes Notice at all: every byte one the checker chooses */
static void any_cancellation_of_all_quotes_notice(CancellationOfAllQuotesNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Cancellation Of All Quotes Notice to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_cancellation_of_all_quotes_notice(const CancellationOfAllQuotesNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Cancellation Of All Quotes Notice off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_cancellation_of_all_quotes_notice(CancellationOfAllQuotesNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Cancellation Of All Quotes Notice is what was written, byte for byte */
static void equal_cancellation_of_all_quotes_notice(const CancellationOfAllQuotesNotice *read, const CancellationOfAllQuotesNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Cancellation Of All Quotes Notice: written and read back, then read and written back */
static void check_cancellation_of_all_quotes_notice(void) {
  CancellationOfAllQuotesNotice sent;
  CancellationOfAllQuotesNotice got;
  uint8_t wire[37];
  uint8_t again[37];

  any_cancellation_of_all_quotes_notice(&sent);
  assert(encode_cancellation_of_all_quotes_notice(&sent, wire, 0) == 37);
  assert(decode_cancellation_of_all_quotes_notice(&got, wire, 0) == 37);
  equal_cancellation_of_all_quotes_notice(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_cancellation_of_all_quotes_notice(&got, wire, 0) == 37);
  assert(encode_cancellation_of_all_quotes_notice(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Notice: 218 bytes --------------------------------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;                /* bytes 0 to 21 */
  uint8_t group[2];                                               /* bytes 22 to 23 */
  uint8_t instrument[4];                                          /* bytes 24 to 27 */
  uint8_t trader_id[8];                                           /* bytes 28 to 35 */
  uint8_t reference_id_order_id_or_quote_id[8];                   /* bytes 36 to 43 */
  uint8_t verb_side;                                              /* byte 44 */
  uint8_t quantity_traded[8];                                     /* bytes 45 to 52 */
  uint8_t trade_price[10];                                        /* bytes 53 to 62 */
  uint8_t trading_engine_timestamp_of_the_trade_local_hhmmss[6];  /* bytes 63 to 68 */
  ClearingData clearing_data;                                     /* bytes 69 to 88 */
  OwnerData owner_data;                                           /* bytes 89 to 138 */
  uint8_t special_trade_indicator;                                /* byte 139 */
  uint8_t price_type;                                             /* byte 140 */
  uint8_t trade_type;                                             /* byte 141 */
  uint8_t filler_6[6];                                            /* bytes 142 to 147 */
  uint8_t trade_number[8];                                        /* bytes 148 to 155 */
  uint8_t trade_memo[50];                                         /* bytes 156 to 205 */
  uint8_t original_reference_id[8];                               /* bytes 206 to 213 */
  uint8_t id_code_for_the_counterpart_participant[4];             /* bytes 214 to 217 */
} ExecutionNotice;

/* any Execution Notice at all: every byte one the checker chooses */
static void any_execution_notice(ExecutionNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
}

/* Execution Notice to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_execution_notice(const ExecutionNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id_order_id_or_quote_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_of_the_trade_local_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }

  return at;
}

/* Execution Notice off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_execution_notice(ExecutionNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Notice is what was written, byte for byte */
static void equal_execution_notice(const ExecutionNotice *read, const ExecutionNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id_order_id_or_quote_id[i] == written->reference_id_order_id_or_quote_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_of_the_trade_local_hhmmss[i] == written->trading_engine_timestamp_of_the_trade_local_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
}

/* Execution Notice: written and read back, then read and written back */
static void check_execution_notice(void) {
  ExecutionNotice sent;
  ExecutionNotice got;
  uint8_t wire[218];
  uint8_t again[218];

  any_execution_notice(&sent);
  assert(encode_execution_notice(&sent, wire, 0) == 218);
  assert(decode_execution_notice(&got, wire, 0) == 218);
  equal_execution_notice(&got, &sent);

  for (size_t i = 0; i < 218; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_notice(&got, wire, 0) == 218);
  assert(encode_execution_notice(&got, again, 0) == 218);
  for (size_t i = 0; i < 218; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Cancellation Notice: 218 bytes -------------------------------- */

/* This message is sent by the Exchange to report the execution of a trade cancellation by the MOD. This message has the same number of bytes and format as the NT: SAIL Execution Notice messages. */
typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;                /* bytes 0 to 21 */
  uint8_t group[2];                                               /* bytes 22 to 23 */
  uint8_t instrument[4];                                          /* bytes 24 to 27 */
  uint8_t trader_id[8];                                           /* bytes 28 to 35 */
  uint8_t reference_id_order_id_or_quote_id[8];                   /* bytes 36 to 43 */
  uint8_t verb_side;                                              /* byte 44 */
  uint8_t quantity_traded[8];                                     /* bytes 45 to 52 */
  uint8_t trade_price[10];                                        /* bytes 53 to 62 */
  uint8_t trading_engine_timestamp_of_the_trade_local_hhmmss[6];  /* bytes 63 to 68 */
  ClearingData clearing_data;                                     /* bytes 69 to 88 */
  OwnerData owner_data;                                           /* bytes 89 to 138 */
  uint8_t special_trade_indicator;                                /* byte 139 */
  uint8_t price_type;                                             /* byte 140 */
  uint8_t trade_type;                                             /* byte 141 */
  uint8_t filler_6[6];                                            /* bytes 142 to 147 */
  uint8_t trade_number[8];                                        /* bytes 148 to 155 */
  uint8_t trade_memo[50];                                         /* bytes 156 to 205 */
  uint8_t original_reference_id[8];                               /* bytes 206 to 213 */
  uint8_t id_code_for_the_counterpart_participant[4];             /* bytes 214 to 217 */
} ExecutionCancellationNotice;

/* any Execution Cancellation Notice at all: every byte one the checker chooses */
static void any_execution_cancellation_notice(ExecutionCancellationNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
}

/* Execution Cancellation Notice to the wire: 218 bytes from at, returning where the next byte goes */
static size_t encode_execution_cancellation_notice(const ExecutionCancellationNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id_order_id_or_quote_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_of_the_trade_local_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }

  return at;
}

/* Execution Cancellation Notice off the wire: 218 bytes from at, returning where the next byte lies */
static size_t decode_execution_cancellation_notice(ExecutionCancellationNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Cancellation Notice is what was written, byte for byte */
static void equal_execution_cancellation_notice(const ExecutionCancellationNotice *read, const ExecutionCancellationNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id_order_id_or_quote_id[i] == written->reference_id_order_id_or_quote_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_of_the_trade_local_hhmmss[i] == written->trading_engine_timestamp_of_the_trade_local_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
}

/* Execution Cancellation Notice: written and read back, then read and written back */
static void check_execution_cancellation_notice(void) {
  ExecutionCancellationNotice sent;
  ExecutionCancellationNotice got;
  uint8_t wire[218];
  uint8_t again[218];

  any_execution_cancellation_notice(&sent);
  assert(encode_execution_cancellation_notice(&sent, wire, 0) == 218);
  assert(decode_execution_cancellation_notice(&got, wire, 0) == 218);
  equal_execution_cancellation_notice(&got, &sent);

  for (size_t i = 0; i < 218; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_cancellation_notice(&got, wire, 0) == 218);
  assert(encode_execution_cancellation_notice(&got, again, 0) == 218);
  for (size_t i = 0; i < 218; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Execution Cancellation Notice: 235 bytes ---------------------------- */

/* This message is sent by the Exchange to report the execution of a cancellation by the MOD for a leg of the strategy trade. This message has the same number of bytes and format as the NL: Leg Execution Notice message. */
typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;                /* bytes 0 to 21 */
  uint8_t group[2];                                               /* bytes 22 to 23 */
  uint8_t instrument[4];                                          /* bytes 24 to 27 */
  uint8_t trader_id[8];                                           /* bytes 28 to 35 */
  uint8_t reference_id_order_id_or_quote_id[8];                   /* bytes 36 to 43 */
  uint8_t verb_side;                                              /* byte 44 */
  uint8_t quantity_traded[8];                                     /* bytes 45 to 52 */
  uint8_t trade_price[10];                                        /* bytes 53 to 62 */
  uint8_t trading_engine_timestamp_of_the_trade_local_hhmmss[6];  /* bytes 63 to 68 */
  ClearingData clearing_data;                                     /* bytes 69 to 88 */
  OwnerData owner_data;                                           /* bytes 89 to 138 */
  uint8_t special_trade_indicator;                                /* byte 139 */
  uint8_t price_type;                                             /* byte 140 */
  uint8_t trade_type;                                             /* byte 141 */
  uint8_t filler_6[6];                                            /* bytes 142 to 147 */
  uint8_t trade_number[8];                                        /* bytes 148 to 155 */
  uint8_t trade_memo[50];                                         /* bytes 156 to 205 */
  uint8_t original_reference_id[8];                               /* bytes 206 to 213 */
  uint8_t id_code_for_the_counterpart_participant[4];             /* bytes 214 to 217 */
  uint8_t strategy_group[2];                                      /* bytes 218 to 219 */
  uint8_t strategy_instrument_id[4];                              /* bytes 220 to 223 */
  uint8_t strategy_verb_side;                                     /* byte 224 */
  uint8_t strategy_trade_number[8];                               /* bytes 225 to 232 */
  uint8_t leg_number[2];                                          /* bytes 233 to 234 */
} LegExecutionCancellationNotice;

/* any Leg Execution Cancellation Notice at all: every byte one the checker chooses */
static void any_leg_execution_cancellation_notice(LegExecutionCancellationNotice *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = arbitrary(); }
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  record->special_trade_indicator = arbitrary();
  record->price_type = arbitrary();
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = arbitrary(); }
  record->strategy_verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = arbitrary(); }
}

/* Leg Execution Cancellation Notice to the wire: 235 bytes from at, returning where the next byte goes */
static size_t encode_leg_execution_cancellation_notice(const LegExecutionCancellationNotice *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_id_order_id_or_quote_id[i]; }
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_traded[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->trade_price[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->trading_engine_timestamp_of_the_trade_local_hhmmss[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  wire[at++] = record->special_trade_indicator;
  wire[at++] = record->price_type;
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_number[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->trade_memo[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_reference_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_code_for_the_counterpart_participant[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->strategy_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_instrument_id[i]; }
  wire[at++] = record->strategy_verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strategy_trade_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->leg_number[i]; }

  return at;
}

/* Leg Execution Cancellation Notice off the wire: 235 bytes from at, returning where the next byte lies */
static size_t decode_leg_execution_cancellation_notice(LegExecutionCancellationNotice *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_id_order_id_or_quote_id[i] = wire[at++]; }
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity_traded[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->trade_price[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->trading_engine_timestamp_of_the_trade_local_hhmmss[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  record->special_trade_indicator = wire[at++];
  record->price_type = wire[at++];
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->trade_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_reference_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->id_code_for_the_counterpart_participant[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->strategy_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strategy_instrument_id[i] = wire[at++]; }
  record->strategy_verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strategy_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->leg_number[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Execution Cancellation Notice is what was written, byte for byte */
static void equal_leg_execution_cancellation_notice(const LegExecutionCancellationNotice *read, const LegExecutionCancellationNotice *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_id_order_id_or_quote_id[i] == written->reference_id_order_id_or_quote_id[i]); }
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_traded[i] == written->quantity_traded[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->trade_price[i] == written->trade_price[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->trading_engine_timestamp_of_the_trade_local_hhmmss[i] == written->trading_engine_timestamp_of_the_trade_local_hhmmss[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  assert(read->special_trade_indicator == written->special_trade_indicator);
  assert(read->price_type == written->price_type);
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->trade_memo[i] == written->trade_memo[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_reference_id[i] == written->original_reference_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->id_code_for_the_counterpart_participant[i] == written->id_code_for_the_counterpart_participant[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->strategy_group[i] == written->strategy_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_instrument_id[i] == written->strategy_instrument_id[i]); }
  assert(read->strategy_verb_side == written->strategy_verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->strategy_trade_number[i] == written->strategy_trade_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->leg_number[i] == written->leg_number[i]); }
}

/* Leg Execution Cancellation Notice: written and read back, then read and written back */
static void check_leg_execution_cancellation_notice(void) {
  LegExecutionCancellationNotice sent;
  LegExecutionCancellationNotice got;
  uint8_t wire[235];
  uint8_t again[235];

  any_leg_execution_cancellation_notice(&sent);
  assert(encode_leg_execution_cancellation_notice(&sent, wire, 0) == 235);
  assert(decode_leg_execution_cancellation_notice(&got, wire, 0) == 235);
  equal_leg_execution_cancellation_notice(&got, &sent);

  for (size_t i = 0; i < 235; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_execution_cancellation_notice(&got, wire, 0) == 235);
  assert(encode_leg_execution_cancellation_notice(&got, again, 0) == 235);
  for (size_t i = 0; i < 235; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Notice By Mod Or System: 148 bytes ------------------- */

/* This triggered message is sent by the Exchange to report the cancellation of an order by the MOD or by the System. This message has the same number of bytes and format as the KE: Order Acknowledgement, KM: Order Modification Acknowledgement and KZ: Order Cancellation Acknowledgement messages. */
typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t trader_id[8];                             /* bytes 28 to 35 */
  uint8_t order_id[8];                              /* bytes 36 to 43 */
  uint8_t status;                                   /* byte 44 */
  uint8_t verb_side;                                /* byte 45 */
  uint8_t quantity[8];                              /* bytes 46 to 53 */
  uint8_t assigned_price[10];                       /* bytes 54 to 63 */
  ClearingData clearing_data;                       /* bytes 64 to 83 */
  OwnerData owner_data;                             /* bytes 84 to 133 */
  uint8_t original_order_id[8];                     /* bytes 134 to 141 */
  uint8_t filler_6[6];                              /* bytes 142 to 147 */
} OrderCancellationNoticeByModOrSystem;

/* any Order Cancellation Notice By Mod Or System at all: every byte one the checker chooses */
static void any_order_cancellation_notice_by_mod_or_system(OrderCancellationNoticeByModOrSystem *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->status = arbitrary();
  record->verb_side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = arbitrary(); }
  any_clearing_data(&record->clearing_data);
  any_owner_data(&record->owner_data);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = arbitrary(); }
}

/* Order Cancellation Notice By Mod Or System to the wire: 148 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_notice_by_mod_or_system(const OrderCancellationNoticeByModOrSystem *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trader_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->status;
  wire[at++] = record->verb_side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->assigned_price[i]; }
  at = encode_clearing_data(&record->clearing_data, wire, at);
  at = encode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_order_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->filler_6[i]; }

  return at;
}

/* Order Cancellation Notice By Mod Or System off the wire: 148 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_notice_by_mod_or_system(OrderCancellationNoticeByModOrSystem *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->status = wire[at++];
  record->verb_side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->assigned_price[i] = wire[at++]; }
  at = decode_clearing_data(&record->clearing_data, wire, at);
  at = decode_owner_data(&record->owner_data, wire, at);
  for (size_t i = 0; i < 8; i++) { record->original_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->filler_6[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Notice By Mod Or System is what was written, byte for byte */
static void equal_order_cancellation_notice_by_mod_or_system(const OrderCancellationNoticeByModOrSystem *read, const OrderCancellationNoticeByModOrSystem *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trader_id[i] == written->trader_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->status == written->status);
  assert(read->verb_side == written->verb_side);
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->assigned_price[i] == written->assigned_price[i]); }
  equal_clearing_data(&read->clearing_data, &written->clearing_data);
  equal_owner_data(&read->owner_data, &written->owner_data);
  for (size_t i = 0; i < 8; i++) { assert(read->original_order_id[i] == written->original_order_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->filler_6[i] == written->filler_6[i]); }
}

/* Order Cancellation Notice By Mod Or System: written and read back, then read and written back */
static void check_order_cancellation_notice_by_mod_or_system(void) {
  OrderCancellationNoticeByModOrSystem sent;
  OrderCancellationNoticeByModOrSystem got;
  uint8_t wire[148];
  uint8_t again[148];

  any_order_cancellation_notice_by_mod_or_system(&sent);
  assert(encode_order_cancellation_notice_by_mod_or_system(&sent, wire, 0) == 148);
  assert(decode_order_cancellation_notice_by_mod_or_system(&got, wire, 0) == 148);
  equal_order_cancellation_notice_by_mod_or_system(&got, &sent);

  for (size_t i = 0; i < 148; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_notice_by_mod_or_system(&got, wire, 0) == 148);
  assert(encode_order_cancellation_notice_by_mod_or_system(&got, again, 0) == 148);
  for (size_t i = 0; i < 148; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Quote With Side Acknowledgement: 37 bytes ------------------- */

typedef struct {
  OutgoingMessagesHeader outgoing_messages_header;  /* bytes 0 to 21 */
  uint8_t group[2];                                 /* bytes 22 to 23 */
  uint8_t instrument[4];                            /* bytes 24 to 27 */
  uint8_t quantity[8];                              /* bytes 28 to 35 */
  uint8_t market_side;                              /* byte 36 */
} RequestForQuoteWithSideAcknowledgement;

/* any Request For Quote With Side Acknowledgement at all: every byte one the checker chooses */
static void any_request_for_quote_with_side_acknowledgement(RequestForQuoteWithSideAcknowledgement *record) {
  any_outgoing_messages_header(&record->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { record->group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
  record->market_side = arbitrary();
}

/* Request For Quote With Side Acknowledgement to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_request_for_quote_with_side_acknowledgement(const RequestForQuoteWithSideAcknowledgement *record, uint8_t *wire, size_t at) {
  at = encode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->market_side;

  return at;
}

/* Request For Quote With Side Acknowledgement off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_request_for_quote_with_side_acknowledgement(RequestForQuoteWithSideAcknowledgement *record, const uint8_t *wire, size_t at) {
  at = decode_outgoing_messages_header(&record->outgoing_messages_header, wire, at);
  for (size_t i = 0; i < 2; i++) { record->group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }
  record->market_side = wire[at++];

  return at;
}

/* what was read of Request For Quote With Side Acknowledgement is what was written, byte for byte */
static void equal_request_for_quote_with_side_acknowledgement(const RequestForQuoteWithSideAcknowledgement *read, const RequestForQuoteWithSideAcknowledgement *written) {
  equal_outgoing_messages_header(&read->outgoing_messages_header, &written->outgoing_messages_header);
  for (size_t i = 0; i < 2; i++) { assert(read->group[i] == written->group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument[i] == written->instrument[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->market_side == written->market_side);
}

/* Request For Quote With Side Acknowledgement: written and read back, then read and written back */
static void check_request_for_quote_with_side_acknowledgement(void) {
  RequestForQuoteWithSideAcknowledgement sent;
  RequestForQuoteWithSideAcknowledgement got;
  uint8_t wire[37];
  uint8_t again[37];

  any_request_for_quote_with_side_acknowledgement(&sent);
  assert(encode_request_for_quote_with_side_acknowledgement(&sent, wire, 0) == 37);
  assert(decode_request_for_quote_with_side_acknowledgement(&got, wire, 0) == 37);
  equal_request_for_quote_with_side_acknowledgement(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_quote_with_side_acknowledgement(&got, wire, 0) == 37);
  assert(encode_request_for_quote_with_side_acknowledgement(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_connection_acknowledgement();
  check_disconnection_instruction_acknowledgement();
  check_heartbeat_question();
  check_out_of_sequence();
  check_technical_error_notice();
  check_disconnection_acknowledgement();
  check_end_of_transmission();
  check_outgoing_messages_header();
  check_clearing_data();
  check_owner_data();
  check_order_reply();
  check_error_notice();
  check_bulk_quote_data_acknowledgement();
  check_order_acknowledgement();
  check_global_cancellation_confirmation();
  check_order_modification_acknowledgement();
  check_standard_acknowledgement();
  check_order_cancellation_acknowledgement();
  check_group_state_change();
  check_instrument_state_change();
  check_leg_execution_notice();
  check_counterpart_owner_data();
  check_overstepped_order_or_quote_notice();
  check_cancellation_of_all_quotes_notice();
  check_execution_notice();
  check_execution_cancellation_notice();
  check_leg_execution_cancellation_notice();
  check_order_cancellation_notice_by_mod_or_system();
  check_request_for_quote_with_side_acknowledgement();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
