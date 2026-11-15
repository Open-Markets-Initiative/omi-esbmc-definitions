// taifex/taifexderivatives/clearingmember/TaifexDerivatives_ClearingMember_v2_18_7.c
/*
 * Taiwan Futures Exchange Clearing Member Order And Execution Report
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
 *   - the dispatch that chooses a message by its type
 *   - a run of a stated number of entries
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

/* ---- Header Time: 6 bytes ---------------------------------------------------- */

/* Message time, the Tmp time format of section 2.1 carried by the common message header */
typedef struct {
  uint8_t header_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t header_ms[2];       /* bytes 4 to 5 */
} HeaderTime;

/* any Header Time at all: every byte one the checker chooses */
static void any_header_time(HeaderTime *record) {
  for (size_t i = 0; i < 4; i++) { record->header_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->header_ms[i] = arbitrary(); }
}

/* Header Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_header_time(const HeaderTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->header_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->header_ms[i]; }

  return at;
}

/* Header Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_header_time(HeaderTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->header_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->header_ms[i] = wire[at++]; }

  return at;
}

/* what was read of Header Time is what was written, byte for byte */
static void equal_header_time(const HeaderTime *read, const HeaderTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->header_epoch_s[i] == written->header_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->header_ms[i] == written->header_ms[i]); }
}

/* Header Time: written and read back, then read and written back */
static void check_header_time(void) {
  HeaderTime sent;
  HeaderTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_header_time(&sent);
  assert(encode_header_time(&sent, wire, 0) == 6);
  assert(decode_header_time(&got, wire, 0) == 6);
  equal_header_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_header_time(&got, wire, 0) == 6);
  assert(encode_header_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Hdr: 17 bytes ----------------------------------------------------------- */

/* Tmp Common message header, carried by every Tmp message */
typedef struct {
  uint8_t msg_length[2];   /* bytes 0 to 1 */
  uint8_t msg_seq_num[4];  /* bytes 2 to 5 */
  HeaderTime header_time;  /* bytes 6 to 11 */
  uint8_t message_type;    /* byte 12 */
  uint8_t fcm_id[2];       /* bytes 13 to 14 */
  uint8_t session_id[2];   /* bytes 15 to 16 */
} Hdr;

/* any Hdr at all: every byte one the checker chooses */
static void any_hdr(Hdr *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  any_header_time(&record->header_time);
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
}

/* Hdr to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_hdr(const Hdr *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  at = encode_header_time(&record->header_time, wire, at);
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Hdr off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_hdr(Hdr *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  at = decode_header_time(&record->header_time, wire, at);
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Hdr is what was written, byte for byte */
static void equal_hdr(const Hdr *read, const Hdr *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  equal_header_time(&read->header_time, &written->header_time);
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Hdr: written and read back, then read and written back */
static void check_hdr(void) {
  Hdr sent;
  Hdr got;
  uint8_t wire[17];
  uint8_t again[17];

  any_hdr(&sent);
  assert(encode_hdr(&sent, wire, 0) == 17);
  assert(decode_hdr(&got, wire, 0) == 17);
  equal_hdr(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_hdr(&got, wire, 0) == 17);
  assert(encode_hdr(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wake Up Call Message: 5 bytes ------------------------------------------- */

/* Wake up call message, which either Taifex or the futures commission merchant may initiate in the logon phase of the Link Subsystem. */
typedef struct {
  uint8_t status_code;            /* byte 0 */
  uint8_t start_in_bound_num[4];  /* bytes 1 to 4 */
} WakeUpCallMessage;

/* any Wake Up Call Message at all: every byte one the checker chooses */
static void any_wake_up_call_message(WakeUpCallMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->start_in_bound_num[i] = arbitrary(); }
}

/* Wake Up Call Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_wake_up_call_message(const WakeUpCallMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_in_bound_num[i]; }

  return at;
}

/* Wake Up Call Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_wake_up_call_message(WakeUpCallMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->start_in_bound_num[i] = wire[at++]; }

  return at;
}

/* what was read of Wake Up Call Message is what was written, byte for byte */
static void equal_wake_up_call_message(const WakeUpCallMessage *read, const WakeUpCallMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 4; i++) { assert(read->start_in_bound_num[i] == written->start_in_bound_num[i]); }
}

/* Wake Up Call Message: written and read back, then read and written back */
static void check_wake_up_call_message(void) {
  WakeUpCallMessage sent;
  WakeUpCallMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_wake_up_call_message(&sent);
  assert(encode_wake_up_call_message(&sent, wire, 0) == 5);
  assert(decode_wake_up_call_message(&got, wire, 0) == 5);
  equal_wake_up_call_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_wake_up_call_message(&got, wire, 0) == 5);
  assert(encode_wake_up_call_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wake Up Call Confirmed Message: 1 byte ---------------------------------- */

/* Wake up call confirmed message, sent by the futures commission merchant to Taifex. */
typedef struct {
  uint8_t version;  /* byte 0 */
} WakeUpCallConfirmedMessage;

/* any Wake Up Call Confirmed Message at all: every byte one the checker chooses */
static void any_wake_up_call_confirmed_message(WakeUpCallConfirmedMessage *record) {
  record->version = arbitrary();
}

/* Wake Up Call Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_wake_up_call_confirmed_message(const WakeUpCallConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;

  return at;
}

/* Wake Up Call Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_wake_up_call_confirmed_message(WakeUpCallConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];

  return at;
}

/* what was read of Wake Up Call Confirmed Message is what was written, byte for byte */
static void equal_wake_up_call_confirmed_message(const WakeUpCallConfirmedMessage *read, const WakeUpCallConfirmedMessage *written) {
  assert(read->version == written->version);
}

/* Wake Up Call Confirmed Message: written and read back, then read and written back */
static void check_wake_up_call_confirmed_message(void) {
  WakeUpCallConfirmedMessage sent;
  WakeUpCallConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_wake_up_call_confirmed_message(&sent);
  assert(encode_wake_up_call_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_wake_up_call_confirmed_message(&got, wire, 0) == 1);
  equal_wake_up_call_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_wake_up_call_confirmed_message(&got, wire, 0) == 1);
  assert(encode_wake_up_call_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Notice Message: 9 bytes ------------------------------------------- */

/* Logon notice message, carrying the sequence No of the last message Taifex sent the futures commission merchant in the session. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t append_no[2];          /* bytes 1 to 2 */
  uint8_t end_out_bound_num[4];  /* bytes 3 to 6 */
  uint8_t system_type;           /* byte 7 */
  uint8_t encrypt_method;        /* byte 8 */
} LogonNoticeMessage;

/* any Logon Notice Message at all: every byte one the checker chooses */
static void any_logon_notice_message(LogonNoticeMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = arbitrary(); }
  record->system_type = arbitrary();
  record->encrypt_method = arbitrary();
}

/* Logon Notice Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_logon_notice_message(const LogonNoticeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->append_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_out_bound_num[i]; }
  wire[at++] = record->system_type;
  wire[at++] = record->encrypt_method;

  return at;
}

/* Logon Notice Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_logon_notice_message(LogonNoticeMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = wire[at++]; }
  record->system_type = wire[at++];
  record->encrypt_method = wire[at++];

  return at;
}

/* what was read of Logon Notice Message is what was written, byte for byte */
static void equal_logon_notice_message(const LogonNoticeMessage *read, const LogonNoticeMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->append_no[i] == written->append_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_out_bound_num[i] == written->end_out_bound_num[i]); }
  assert(read->system_type == written->system_type);
  assert(read->encrypt_method == written->encrypt_method);
}

/* Logon Notice Message: written and read back, then read and written back */
static void check_logon_notice_message(void) {
  LogonNoticeMessage sent;
  LogonNoticeMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_logon_notice_message(&sent);
  assert(encode_logon_notice_message(&sent, wire, 0) == 9);
  assert(decode_logon_notice_message(&got, wire, 0) == 9);
  equal_logon_notice_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_notice_message(&got, wire, 0) == 9);
  assert(encode_logon_notice_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sub Hdr: 6 bytes -------------------------------------------------------- */

/* Tmp Expanded Message Header, which assigns different functionalities to a MessageType by defining additional subcategories for it */
typedef struct {
  uint8_t msg_type_ext;    /* byte 0 */
  uint8_t preserve;        /* byte 1 */
  uint8_t msg_time_ns[4];  /* bytes 2 to 5 */
} SubHdr;

/* any Sub Hdr at all: every byte one the checker chooses */
static void any_sub_hdr(SubHdr *record) {
  record->msg_type_ext = arbitrary();
  record->preserve = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->msg_time_ns[i] = arbitrary(); }
}

/* Sub Hdr to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sub_hdr(const SubHdr *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_type_ext;
  wire[at++] = record->preserve;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_ns[i]; }

  return at;
}

/* Sub Hdr off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sub_hdr(SubHdr *record, const uint8_t *wire, size_t at) {
  record->msg_type_ext = wire[at++];
  record->preserve = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->msg_time_ns[i] = wire[at++]; }

  return at;
}

/* what was read of Sub Hdr is what was written, byte for byte */
static void equal_sub_hdr(const SubHdr *read, const SubHdr *written) {
  assert(read->msg_type_ext == written->msg_type_ext);
  assert(read->preserve == written->preserve);
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_ns[i] == written->msg_time_ns[i]); }
}

/* Sub Hdr: written and read back, then read and written back */
static void check_sub_hdr(void) {
  SubHdr sent;
  SubHdr got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sub_hdr(&sent);
  assert(encode_sub_hdr(&sent, wire, 0) == 6);
  assert(decode_sub_hdr(&got, wire, 0) == 6);
  equal_sub_hdr(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sub_hdr(&got, wire, 0) == 6);
  assert(encode_sub_hdr(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Final Sequential Number Notification For Group Message: 21 bytes -------- */

/* Final Sequential Number Notification Message for Group, transmitting the group's last report sequence number to the futures commission merchant. */
typedef struct {
  SubHdr sub_hdr;                /* bytes 0 to 5 */
  uint8_t wide_status_code[2];   /* bytes 6 to 7 */
  uint8_t part_id;               /* byte 8 */
  uint8_t end_out_bound_num[4];  /* bytes 9 to 12 */
  uint8_t reserved_8[8];         /* bytes 13 to 20 */
} FinalSequentialNumberNotificationForGroupMessage;

/* any Final Sequential Number Notification For Group Message at all: every byte one the checker chooses */
static void any_final_sequential_number_notification_for_group_message(FinalSequentialNumberNotificationForGroupMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = arbitrary(); }
  record->part_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Final Sequential Number Notification For Group Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_final_sequential_number_notification_for_group_message(const FinalSequentialNumberNotificationForGroupMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->wide_status_code[i]; }
  wire[at++] = record->part_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_out_bound_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Final Sequential Number Notification For Group Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_final_sequential_number_notification_for_group_message(FinalSequentialNumberNotificationForGroupMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = wire[at++]; }
  record->part_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Final Sequential Number Notification For Group Message is what was written, byte for byte */
static void equal_final_sequential_number_notification_for_group_message(const FinalSequentialNumberNotificationForGroupMessage *read, const FinalSequentialNumberNotificationForGroupMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  for (size_t i = 0; i < 2; i++) { assert(read->wide_status_code[i] == written->wide_status_code[i]); }
  assert(read->part_id == written->part_id);
  for (size_t i = 0; i < 4; i++) { assert(read->end_out_bound_num[i] == written->end_out_bound_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Final Sequential Number Notification For Group Message: written and read back, then read and written back */
static void check_final_sequential_number_notification_for_group_message(void) {
  FinalSequentialNumberNotificationForGroupMessage sent;
  FinalSequentialNumberNotificationForGroupMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_final_sequential_number_notification_for_group_message(&sent);
  assert(encode_final_sequential_number_notification_for_group_message(&sent, wire, 0) == 21);
  assert(decode_final_sequential_number_notification_for_group_message(&got, wire, 0) == 21);
  equal_final_sequential_number_notification_for_group_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_final_sequential_number_notification_for_group_message(&got, wire, 0) == 21);
  assert(encode_final_sequential_number_notification_for_group_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request Logon Message: 15 bytes ----------------------------------------- */

/* Request logon, sent by the futures commission merchant to Taifex with the start sequence of the messages it requests Taifex to resend. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t append_no[2];          /* bytes 1 to 2 */
  uint8_t fcm_id[2];             /* bytes 3 to 4 */
  uint8_t session_id[2];         /* bytes 5 to 6 */
  uint8_t system_type;           /* byte 7 */
  uint8_t ap_code;               /* byte 8 */
  uint8_t key_value;             /* byte 9 */
  uint8_t request_start_seq[4];  /* bytes 10 to 13 */
  uint8_t cancel_order_sec;      /* byte 14 */
} RequestLogonMessage;

/* any Request Logon Message at all: every byte one the checker chooses */
static void any_request_logon_message(RequestLogonMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  record->system_type = arbitrary();
  record->ap_code = arbitrary();
  record->key_value = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = arbitrary(); }
  record->cancel_order_sec = arbitrary();
}

/* Request Logon Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_request_logon_message(const RequestLogonMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->append_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->system_type;
  wire[at++] = record->ap_code;
  wire[at++] = record->key_value;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_start_seq[i]; }
  wire[at++] = record->cancel_order_sec;

  return at;
}

/* Request Logon Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_request_logon_message(RequestLogonMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  record->system_type = wire[at++];
  record->ap_code = wire[at++];
  record->key_value = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = wire[at++]; }
  record->cancel_order_sec = wire[at++];

  return at;
}

/* what was read of Request Logon Message is what was written, byte for byte */
static void equal_request_logon_message(const RequestLogonMessage *read, const RequestLogonMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->append_no[i] == written->append_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->system_type == written->system_type);
  assert(read->ap_code == written->ap_code);
  assert(read->key_value == written->key_value);
  for (size_t i = 0; i < 4; i++) { assert(read->request_start_seq[i] == written->request_start_seq[i]); }
  assert(read->cancel_order_sec == written->cancel_order_sec);
}

/* Request Logon Message: written and read back, then read and written back */
static void check_request_logon_message(void) {
  RequestLogonMessage sent;
  RequestLogonMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_request_logon_message(&sent);
  assert(encode_request_logon_message(&sent, wire, 0) == 15);
  assert(decode_request_logon_message(&got, wire, 0) == 15);
  equal_request_logon_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_request_logon_message(&got, wire, 0) == 15);
  assert(encode_request_logon_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Activate Application System Message: 4 bytes ---------------------------- */

/* Activate application system, sent by Taifex to the futures commission merchant. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t heart_bt_int;          /* byte 1 */
  uint8_t max_flow_ctrl_cnt[2];  /* bytes 2 to 3 */
} ActivateApplicationSystemMessage;

/* any Activate Application System Message at all: every byte one the checker chooses */
static void any_activate_application_system_message(ActivateApplicationSystemMessage *record) {
  record->status_code = arbitrary();
  record->heart_bt_int = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->max_flow_ctrl_cnt[i] = arbitrary(); }
}

/* Activate Application System Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_activate_application_system_message(const ActivateApplicationSystemMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  wire[at++] = record->heart_bt_int;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_flow_ctrl_cnt[i]; }

  return at;
}

/* Activate Application System Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_activate_application_system_message(ActivateApplicationSystemMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  record->heart_bt_int = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->max_flow_ctrl_cnt[i] = wire[at++]; }

  return at;
}

/* what was read of Activate Application System Message is what was written, byte for byte */
static void equal_activate_application_system_message(const ActivateApplicationSystemMessage *read, const ActivateApplicationSystemMessage *written) {
  assert(read->status_code == written->status_code);
  assert(read->heart_bt_int == written->heart_bt_int);
  for (size_t i = 0; i < 2; i++) { assert(read->max_flow_ctrl_cnt[i] == written->max_flow_ctrl_cnt[i]); }
}

/* Activate Application System Message: written and read back, then read and written back */
static void check_activate_application_system_message(void) {
  ActivateApplicationSystemMessage sent;
  ActivateApplicationSystemMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_activate_application_system_message(&sent);
  assert(encode_activate_application_system_message(&sent, wire, 0) == 4);
  assert(decode_activate_application_system_message(&got, wire, 0) == 4);
  equal_activate_application_system_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_activate_application_system_message(&got, wire, 0) == 4);
  assert(encode_activate_application_system_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Activate Application System Confirmed Message: 1 byte ------------------- */

/* Activate application system confirmed, from which Taifex calculates the round trip time of the L50 message to determine the maximum peak flow per second. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ActivateApplicationSystemConfirmedMessage;

/* any Activate Application System Confirmed Message at all: every byte one the checker chooses */
static void any_activate_application_system_confirmed_message(ActivateApplicationSystemConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Activate Application System Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_activate_application_system_confirmed_message(const ActivateApplicationSystemConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Activate Application System Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_activate_application_system_confirmed_message(ActivateApplicationSystemConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Activate Application System Confirmed Message is what was written, byte for byte */
static void equal_activate_application_system_confirmed_message(const ActivateApplicationSystemConfirmedMessage *read, const ActivateApplicationSystemConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Activate Application System Confirmed Message: written and read back, then read and written back */
static void check_activate_application_system_confirmed_message(void) {
  ActivateApplicationSystemConfirmedMessage sent;
  ActivateApplicationSystemConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_activate_application_system_confirmed_message(&sent);
  assert(encode_activate_application_system_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_activate_application_system_confirmed_message(&got, wire, 0) == 1);
  equal_activate_application_system_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_activate_application_system_confirmed_message(&got, wire, 0) == 1);
  assert(encode_activate_application_system_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Confirmed Message: 1 byte ---------------------------------------- */

/* Logout confirmed message, sent by Taifex to the futures commission merchant. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} LogoutConfirmedMessage;

/* any Logout Confirmed Message at all: every byte one the checker chooses */
static void any_logout_confirmed_message(LogoutConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Logout Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_logout_confirmed_message(const LogoutConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Logout Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_logout_confirmed_message(LogoutConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Logout Confirmed Message is what was written, byte for byte */
static void equal_logout_confirmed_message(const LogoutConfirmedMessage *read, const LogoutConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Logout Confirmed Message: written and read back, then read and written back */
static void check_logout_confirmed_message(void) {
  LogoutConfirmedMessage sent;
  LogoutConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_logout_confirmed_message(&sent);
  assert(encode_logout_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_logout_confirmed_message(&got, wire, 0) == 1);
  equal_logout_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_confirmed_message(&got, wire, 0) == 1);
  assert(encode_logout_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Confirm Connection Message: 1 byte -------------------------------------- */

/* Confirm connection message, which either party sends when no new message has arrived from the other after the number of seconds set in the HeartBtInt field of L50. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ConfirmConnectionMessage;

/* any Confirm Connection Message at all: every byte one the checker chooses */
static void any_confirm_connection_message(ConfirmConnectionMessage *record) {
  record->status_code = arbitrary();
}

/* Confirm Connection Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_confirm_connection_message(const ConfirmConnectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Confirm Connection Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_confirm_connection_message(ConfirmConnectionMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Confirm Connection Message is what was written, byte for byte */
static void equal_confirm_connection_message(const ConfirmConnectionMessage *read, const ConfirmConnectionMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Confirm Connection Message: written and read back, then read and written back */
static void check_confirm_connection_message(void) {
  ConfirmConnectionMessage sent;
  ConfirmConnectionMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_confirm_connection_message(&sent);
  assert(encode_confirm_connection_message(&sent, wire, 0) == 1);
  assert(decode_confirm_connection_message(&got, wire, 0) == 1);
  equal_confirm_connection_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_confirm_connection_message(&got, wire, 0) == 1);
  assert(encode_confirm_connection_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Connection Confirmed Message: 1 byte ------------------------------------ */

/* Connection confirmed message, with which a party answers the confirm connection message of the other. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ConnectionConfirmedMessage;

/* any Connection Confirmed Message at all: every byte one the checker chooses */
static void any_connection_confirmed_message(ConnectionConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Connection Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_connection_confirmed_message(const ConnectionConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Connection Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_connection_confirmed_message(ConnectionConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Connection Confirmed Message is what was written, byte for byte */
static void equal_connection_confirmed_message(const ConnectionConfirmedMessage *read, const ConnectionConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Connection Confirmed Message: written and read back, then read and written back */
static void check_connection_confirmed_message(void) {
  ConnectionConfirmedMessage sent;
  ConnectionConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_connection_confirmed_message(&sent);
  assert(encode_connection_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_connection_confirmed_message(&got, wire, 0) == 1);
  equal_connection_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_connection_confirmed_message(&got, wire, 0) == 1);
  assert(encode_connection_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Text: 20 bytes --------------------------------------------------- */

/* Text product ID, naming a product by its Ascii character string symbol */
typedef struct {
  uint8_t symbol[20];  /* bytes 0 to 19 */
} SymbolText;

/* any Symbol Text at all: every byte one the checker chooses */
static void any_symbol_text(SymbolText *record) {
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = arbitrary(); }
}

/* Symbol Text to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_symbol_text(const SymbolText *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Symbol Text off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_symbol_text(SymbolText *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Text is what was written, byte for byte */
static void equal_symbol_text(const SymbolText *read, const SymbolText *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Symbol Text: written and read back, then read and written back */
static void check_symbol_text(void) {
  SymbolText sent;
  SymbolText got;
  uint8_t wire[20];
  uint8_t again[20];

  any_symbol_text(&sent);
  assert(encode_symbol_text(&sent, wire, 0) == 20);
  assert(decode_symbol_text(&got, wire, 0) == 20);
  equal_symbol_text(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_text(&got, wire, 0) == 20);
  assert(encode_symbol_text(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Org Trans Time Msg Time: 6 bytes ---------------------------------------- */

/* Tmp time format, the seconds since the epoch and the thousandth of a second */
typedef struct {
  uint8_t msg_time_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t ms[2];                /* bytes 4 to 5 */
} OrgTransTimeMsgTime;

/* any Org Trans Time Msg Time at all: every byte one the checker chooses */
static void any_org_trans_time_msg_time(OrgTransTimeMsgTime *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = arbitrary(); }
}

/* Org Trans Time Msg Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_org_trans_time_msg_time(const OrgTransTimeMsgTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ms[i]; }

  return at;
}

/* Org Trans Time Msg Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_org_trans_time_msg_time(OrgTransTimeMsgTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = wire[at++]; }

  return at;
}

/* what was read of Org Trans Time Msg Time is what was written, byte for byte */
static void equal_org_trans_time_msg_time(const OrgTransTimeMsgTime *read, const OrgTransTimeMsgTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_epoch_s[i] == written->msg_time_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ms[i] == written->ms[i]); }
}

/* Org Trans Time Msg Time: written and read back, then read and written back */
static void check_org_trans_time_msg_time(void) {
  OrgTransTimeMsgTime sent;
  OrgTransTimeMsgTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_org_trans_time_msg_time(&sent);
  assert(encode_org_trans_time_msg_time(&sent, wire, 0) == 6);
  assert(decode_org_trans_time_msg_time(&got, wire, 0) == 6);
  equal_org_trans_time_msg_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_org_trans_time_msg_time(&got, wire, 0) == 6);
  assert(encode_org_trans_time_msg_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transact Time Msg Time: 6 bytes ----------------------------------------- */

/* Tmp time format, the seconds since the epoch and the thousandth of a second */
typedef struct {
  uint8_t msg_time_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t ms[2];                /* bytes 4 to 5 */
} TransactTimeMsgTime;

/* any Transact Time Msg Time at all: every byte one the checker chooses */
static void any_transact_time_msg_time(TransactTimeMsgTime *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = arbitrary(); }
}

/* Transact Time Msg Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_transact_time_msg_time(const TransactTimeMsgTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ms[i]; }

  return at;
}

/* Transact Time Msg Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_transact_time_msg_time(TransactTimeMsgTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time Msg Time is what was written, byte for byte */
static void equal_transact_time_msg_time(const TransactTimeMsgTime *read, const TransactTimeMsgTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_epoch_s[i] == written->msg_time_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ms[i] == written->ms[i]); }
}

/* Transact Time Msg Time: written and read back, then read and written back */
static void check_transact_time_msg_time(void) {
  TransactTimeMsgTime sent;
  TransactTimeMsgTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_transact_time_msg_time(&sent);
  assert(encode_transact_time_msg_time(&sent, wire, 0) == 6);
  assert(decode_transact_time_msg_time(&got, wire, 0) == 6);
  equal_transact_time_msg_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_transact_time_msg_time(&got, wire, 0) == 6);
  assert(encode_transact_time_msg_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Symbol Text: 40 bytes ---------------------------------------------- */

/* Text product ID in the long product format, naming a product by its Ascii character string symbol */
typedef struct {
  uint8_t long_symbol[40];  /* bytes 0 to 39 */
} LongSymbolText;

/* any Long Symbol Text at all: every byte one the checker chooses */
static void any_long_symbol_text(LongSymbolText *record) {
  for (size_t i = 0; i < 40; i++) { record->long_symbol[i] = arbitrary(); }
}

/* Long Symbol Text to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_long_symbol_text(const LongSymbolText *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->long_symbol[i]; }

  return at;
}

/* Long Symbol Text off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_long_symbol_text(LongSymbolText *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { record->long_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Long Symbol Text is what was written, byte for byte */
static void equal_long_symbol_text(const LongSymbolText *read, const LongSymbolText *written) {
  for (size_t i = 0; i < 40; i++) { assert(read->long_symbol[i] == written->long_symbol[i]); }
}

/* Long Symbol Text: written and read back, then read and written back */
static void check_long_symbol_text(void) {
  LongSymbolText sent;
  LongSymbolText got;
  uint8_t wire[40];
  uint8_t again[40];

  any_long_symbol_text(&sent);
  assert(encode_long_symbol_text(&sent, wire, 0) == 40);
  assert(decode_long_symbol_text(&got, wire, 0) == 40);
  equal_long_symbol_text(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_long_symbol_text(&got, wire, 0) == 40);
  assert(encode_long_symbol_text(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Num X: 4 bytes --------------------------------------------------- */

/* FLEX Numeric Single Product Serial number, naming a FLEX product by the serial number of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t pseq[4];  /* bytes 0 to 3 */
} SymbolNumX;

/* any Symbol Num X at all: every byte one the checker chooses */
static void any_symbol_num_x(SymbolNumX *record) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = arbitrary(); }
}

/* Symbol Num X to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_symbol_num_x(const SymbolNumX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pseq[i]; }

  return at;
}

/* Symbol Num X off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_symbol_num_x(SymbolNumX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Num X is what was written, byte for byte */
static void equal_symbol_num_x(const SymbolNumX *read, const SymbolNumX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->pseq[i] == written->pseq[i]); }
}

/* Symbol Num X: written and read back, then read and written back */
static void check_symbol_num_x(void) {
  SymbolNumX sent;
  SymbolNumX got;
  uint8_t wire[4];
  uint8_t again[4];

  any_symbol_num_x(&sent);
  assert(encode_symbol_num_x(&sent, wire, 0) == 4);
  assert(decode_symbol_num_x(&got, wire, 0) == 4);
  equal_symbol_num_x(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_num_x(&got, wire, 0) == 4);
  assert(encode_symbol_num_x(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Txt X: 20 bytes -------------------------------------------------- */

/* FLEX Textual Single Product Symbol, naming a FLEX product by the product symbol of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t prod_id[20];  /* bytes 0 to 19 */
} SymbolTxtX;

/* any Symbol Txt X at all: every byte one the checker chooses */
static void any_symbol_txt_x(SymbolTxtX *record) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = arbitrary(); }
}

/* Symbol Txt X to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_symbol_txt_x(const SymbolTxtX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->prod_id[i]; }

  return at;
}

/* Symbol Txt X off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_symbol_txt_x(SymbolTxtX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Txt X is what was written, byte for byte */
static void equal_symbol_txt_x(const SymbolTxtX *read, const SymbolTxtX *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->prod_id[i] == written->prod_id[i]); }
}

/* Symbol Txt X: written and read back, then read and written back */
static void check_symbol_txt_x(void) {
  SymbolTxtX sent;
  SymbolTxtX got;
  uint8_t wire[20];
  uint8_t again[20];

  any_symbol_txt_x(&sent);
  assert(encode_symbol_txt_x(&sent, wire, 0) == 20);
  assert(decode_symbol_txt_x(&got, wire, 0) == 20);
  equal_symbol_txt_x(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_txt_x(&got, wire, 0) == 20);
  assert(encode_symbol_txt_x(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Sym Symbol Num X: 4 bytes ------------------------------------------- */

/* FLEX Numeric Single Product Serial number, naming a FLEX product by the serial number of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t pseq[4];  /* bytes 0 to 3 */
} LegSymSymbolNumX;

/* any Leg Sym Symbol Num X at all: every byte one the checker chooses */
static void any_leg_sym_symbol_num_x(LegSymSymbolNumX *record) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = arbitrary(); }
}

/* Leg Sym Symbol Num X to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_leg_sym_symbol_num_x(const LegSymSymbolNumX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pseq[i]; }

  return at;
}

/* Leg Sym Symbol Num X off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_leg_sym_symbol_num_x(LegSymSymbolNumX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Sym Symbol Num X is what was written, byte for byte */
static void equal_leg_sym_symbol_num_x(const LegSymSymbolNumX *read, const LegSymSymbolNumX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->pseq[i] == written->pseq[i]); }
}

/* Leg Sym Symbol Num X: written and read back, then read and written back */
static void check_leg_sym_symbol_num_x(void) {
  LegSymSymbolNumX sent;
  LegSymSymbolNumX got;
  uint8_t wire[4];
  uint8_t again[4];

  any_leg_sym_symbol_num_x(&sent);
  assert(encode_leg_sym_symbol_num_x(&sent, wire, 0) == 4);
  assert(decode_leg_sym_symbol_num_x(&got, wire, 0) == 4);
  equal_leg_sym_symbol_num_x(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_sym_symbol_num_x(&got, wire, 0) == 4);
  assert(encode_leg_sym_symbol_num_x(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Sym Symbol Txt X: 20 bytes ------------------------------------------ */

/* FLEX Textual Single Product Symbol, naming a FLEX product by the product symbol of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t prod_id[20];  /* bytes 0 to 19 */
} LegSymSymbolTxtX;

/* any Leg Sym Symbol Txt X at all: every byte one the checker chooses */
static void any_leg_sym_symbol_txt_x(LegSymSymbolTxtX *record) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = arbitrary(); }
}

/* Leg Sym Symbol Txt X to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_leg_sym_symbol_txt_x(const LegSymSymbolTxtX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->prod_id[i]; }

  return at;
}

/* Leg Sym Symbol Txt X off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_leg_sym_symbol_txt_x(LegSymSymbolTxtX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Sym Symbol Txt X is what was written, byte for byte */
static void equal_leg_sym_symbol_txt_x(const LegSymSymbolTxtX *read, const LegSymSymbolTxtX *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->prod_id[i] == written->prod_id[i]); }
}

/* Leg Sym Symbol Txt X: written and read back, then read and written back */
static void check_leg_sym_symbol_txt_x(void) {
  LegSymSymbolTxtX sent;
  LegSymSymbolTxtX got;
  uint8_t wire[20];
  uint8_t again[20];

  any_leg_sym_symbol_txt_x(&sent);
  assert(encode_leg_sym_symbol_txt_x(&sent, wire, 0) == 20);
  assert(decode_leg_sym_symbol_txt_x(&got, wire, 0) == 20);
  equal_leg_sym_symbol_txt_x(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_sym_symbol_txt_x(&got, wire, 0) == 20);
  assert(encode_leg_sym_symbol_txt_x(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Org Trans Time Msg Time X: 8 bytes -------------------------------------- */

/* Tmp Expanded Time Format, the seconds since the epoch and the billionth of a second, which the FLEX reports carry in place of msg_time */
typedef struct {
  uint8_t msg_time_x_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t nanosecond[4];          /* bytes 4 to 7 */
} OrgTransTimeMsgTimeX;

/* any Org Trans Time Msg Time X at all: every byte one the checker chooses */
static void any_org_trans_time_msg_time_x(OrgTransTimeMsgTimeX *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Org Trans Time Msg Time X to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_org_trans_time_msg_time_x(const OrgTransTimeMsgTimeX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_x_epoch_s[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Org Trans Time Msg Time X off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_org_trans_time_msg_time_x(OrgTransTimeMsgTimeX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Org Trans Time Msg Time X is what was written, byte for byte */
static void equal_org_trans_time_msg_time_x(const OrgTransTimeMsgTimeX *read, const OrgTransTimeMsgTimeX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_x_epoch_s[i] == written->msg_time_x_epoch_s[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Org Trans Time Msg Time X: written and read back, then read and written back */
static void check_org_trans_time_msg_time_x(void) {
  OrgTransTimeMsgTimeX sent;
  OrgTransTimeMsgTimeX got;
  uint8_t wire[8];
  uint8_t again[8];

  any_org_trans_time_msg_time_x(&sent);
  assert(encode_org_trans_time_msg_time_x(&sent, wire, 0) == 8);
  assert(decode_org_trans_time_msg_time_x(&got, wire, 0) == 8);
  equal_org_trans_time_msg_time_x(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_org_trans_time_msg_time_x(&got, wire, 0) == 8);
  assert(encode_org_trans_time_msg_time_x(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transact Time Msg Time X: 8 bytes --------------------------------------- */

/* Tmp Expanded Time Format, the seconds since the epoch and the billionth of a second, which the FLEX reports carry in place of msg_time */
typedef struct {
  uint8_t msg_time_x_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t nanosecond[4];          /* bytes 4 to 7 */
} TransactTimeMsgTimeX;

/* any Transact Time Msg Time X at all: every byte one the checker chooses */
static void any_transact_time_msg_time_x(TransactTimeMsgTimeX *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Transact Time Msg Time X to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_transact_time_msg_time_x(const TransactTimeMsgTimeX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_x_epoch_s[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Transact Time Msg Time X off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_transact_time_msg_time_x(TransactTimeMsgTimeX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time Msg Time X is what was written, byte for byte */
static void equal_transact_time_msg_time_x(const TransactTimeMsgTimeX *read, const TransactTimeMsgTimeX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_x_epoch_s[i] == written->msg_time_x_epoch_s[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Transact Time Msg Time X: written and read back, then read and written back */
static void check_transact_time_msg_time_x(void) {
  TransactTimeMsgTimeX sent;
  TransactTimeMsgTimeX got;
  uint8_t wire[8];
  uint8_t again[8];

  any_transact_time_msg_time_x(&sent);
  assert(encode_transact_time_msg_time_x(&sent, wire, 0) == 8);
  assert(decode_transact_time_msg_time_x(&got, wire, 0) == 8);
  equal_transact_time_msg_time_x(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_transact_time_msg_time_x(&got, wire, 0) == 8);
  assert(encode_transact_time_msg_time_x(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Member Initiate Operation Message: 7 bytes --------------------- */

/* Clearing member initiate operation message, with which the clearing member requests the report start sequence of its downline FCM data. */
typedef struct {
  uint8_t member_id[2];   /* bytes 0 to 1 */
  uint8_t target_id;      /* byte 2 */
  uint8_t req_cm_seq[4];  /* bytes 3 to 6 */
} ClearingMemberInitiateOperationMessage;

/* any Clearing Member Initiate Operation Message at all: every byte one the checker chooses */
static void any_clearing_member_initiate_operation_message(ClearingMemberInitiateOperationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = arbitrary(); }
  record->target_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = arbitrary(); }
}

/* Clearing Member Initiate Operation Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_clearing_member_initiate_operation_message(const ClearingMemberInitiateOperationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->member_id[i]; }
  wire[at++] = record->target_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->req_cm_seq[i]; }

  return at;
}

/* Clearing Member Initiate Operation Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_clearing_member_initiate_operation_message(ClearingMemberInitiateOperationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = wire[at++]; }
  record->target_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Member Initiate Operation Message is what was written, byte for byte */
static void equal_clearing_member_initiate_operation_message(const ClearingMemberInitiateOperationMessage *read, const ClearingMemberInitiateOperationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->member_id[i] == written->member_id[i]); }
  assert(read->target_id == written->target_id);
  for (size_t i = 0; i < 4; i++) { assert(read->req_cm_seq[i] == written->req_cm_seq[i]); }
}

/* Clearing Member Initiate Operation Message: written and read back, then read and written back */
static void check_clearing_member_initiate_operation_message(void) {
  ClearingMemberInitiateOperationMessage sent;
  ClearingMemberInitiateOperationMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_clearing_member_initiate_operation_message(&sent);
  assert(encode_clearing_member_initiate_operation_message(&sent, wire, 0) == 7);
  assert(decode_clearing_member_initiate_operation_message(&got, wire, 0) == 7);
  equal_clearing_member_initiate_operation_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_member_initiate_operation_message(&got, wire, 0) == 7);
  assert(encode_clearing_member_initiate_operation_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Member Initiate Operation Confirmed Message: 8 bytes ----------- */

/* Clearing member initiate operation confirmed message, with which Taifex answers the clearing member with a report start notice. */
typedef struct {
  uint8_t status_code;    /* byte 0 */
  uint8_t member_id[2];   /* bytes 1 to 2 */
  uint8_t target_id;      /* byte 3 */
  uint8_t req_cm_seq[4];  /* bytes 4 to 7 */
} ClearingMemberInitiateOperationConfirmedMessage;

/* any Clearing Member Initiate Operation Confirmed Message at all: every byte one the checker chooses */
static void any_clearing_member_initiate_operation_confirmed_message(ClearingMemberInitiateOperationConfirmedMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = arbitrary(); }
  record->target_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = arbitrary(); }
}

/* Clearing Member Initiate Operation Confirmed Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_clearing_member_initiate_operation_confirmed_message(const ClearingMemberInitiateOperationConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->member_id[i]; }
  wire[at++] = record->target_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->req_cm_seq[i]; }

  return at;
}

/* Clearing Member Initiate Operation Confirmed Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_clearing_member_initiate_operation_confirmed_message(ClearingMemberInitiateOperationConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = wire[at++]; }
  record->target_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Member Initiate Operation Confirmed Message is what was written, byte for byte */
static void equal_clearing_member_initiate_operation_confirmed_message(const ClearingMemberInitiateOperationConfirmedMessage *read, const ClearingMemberInitiateOperationConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->member_id[i] == written->member_id[i]); }
  assert(read->target_id == written->target_id);
  for (size_t i = 0; i < 4; i++) { assert(read->req_cm_seq[i] == written->req_cm_seq[i]); }
}

/* Clearing Member Initiate Operation Confirmed Message: written and read back, then read and written back */
static void check_clearing_member_initiate_operation_confirmed_message(void) {
  ClearingMemberInitiateOperationConfirmedMessage sent;
  ClearingMemberInitiateOperationConfirmedMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_clearing_member_initiate_operation_confirmed_message(&sent);
  assert(encode_clearing_member_initiate_operation_confirmed_message(&sent, wire, 0) == 8);
  assert(decode_clearing_member_initiate_operation_confirmed_message(&got, wire, 0) == 8);
  equal_clearing_member_initiate_operation_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_member_initiate_operation_confirmed_message(&got, wire, 0) == 8);
  assert(encode_clearing_member_initiate_operation_confirmed_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Flex Clearing Member Initiate Operation Message: 14 bytes --------------- */

/* Clearing member initiate FLEX operation message, with which the clearing member subscribes to the FLEX order and execution data of a partition. */
typedef struct {
  SubHdr sub_hdr;         /* bytes 0 to 5 */
  uint8_t part_id;        /* byte 6 */
  uint8_t member_id[2];   /* bytes 7 to 8 */
  uint8_t target_id;      /* byte 9 */
  uint8_t req_cm_seq[4];  /* bytes 10 to 13 */
} FlexClearingMemberInitiateOperationMessage;

/* any Flex Clearing Member Initiate Operation Message at all: every byte one the checker chooses */
static void any_flex_clearing_member_initiate_operation_message(FlexClearingMemberInitiateOperationMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->part_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = arbitrary(); }
  record->target_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = arbitrary(); }
}

/* Flex Clearing Member Initiate Operation Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_flex_clearing_member_initiate_operation_message(const FlexClearingMemberInitiateOperationMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->part_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->member_id[i]; }
  wire[at++] = record->target_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->req_cm_seq[i]; }

  return at;
}

/* Flex Clearing Member Initiate Operation Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_flex_clearing_member_initiate_operation_message(FlexClearingMemberInitiateOperationMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->part_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = wire[at++]; }
  record->target_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = wire[at++]; }

  return at;
}

/* what was read of Flex Clearing Member Initiate Operation Message is what was written, byte for byte */
static void equal_flex_clearing_member_initiate_operation_message(const FlexClearingMemberInitiateOperationMessage *read, const FlexClearingMemberInitiateOperationMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->part_id == written->part_id);
  for (size_t i = 0; i < 2; i++) { assert(read->member_id[i] == written->member_id[i]); }
  assert(read->target_id == written->target_id);
  for (size_t i = 0; i < 4; i++) { assert(read->req_cm_seq[i] == written->req_cm_seq[i]); }
}

/* Flex Clearing Member Initiate Operation Message: written and read back, then read and written back */
static void check_flex_clearing_member_initiate_operation_message(void) {
  FlexClearingMemberInitiateOperationMessage sent;
  FlexClearingMemberInitiateOperationMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_flex_clearing_member_initiate_operation_message(&sent);
  assert(encode_flex_clearing_member_initiate_operation_message(&sent, wire, 0) == 14);
  assert(decode_flex_clearing_member_initiate_operation_message(&got, wire, 0) == 14);
  equal_flex_clearing_member_initiate_operation_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_flex_clearing_member_initiate_operation_message(&got, wire, 0) == 14);
  assert(encode_flex_clearing_member_initiate_operation_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Flex Clearing Member Initiate Operation Confirmed Message: 32 bytes ----- */

/* Clearing member initiate FLEX operation confirmed message, with which Taifex confirms the FLEX subscription. */
typedef struct {
  SubHdr sub_hdr;               /* bytes 0 to 5 */
  uint8_t part_id;              /* byte 6 */
  uint8_t wide_status_code[2];  /* bytes 7 to 8 */
  uint8_t member_id[2];         /* bytes 9 to 10 */
  uint8_t target_id;            /* byte 11 */
  uint8_t req_cm_seq[4];        /* bytes 12 to 15 */
  uint8_t reserved_16[16];      /* bytes 16 to 31 */
} FlexClearingMemberInitiateOperationConfirmedMessage;

/* any Flex Clearing Member Initiate Operation Confirmed Message at all: every byte one the checker chooses */
static void any_flex_clearing_member_initiate_operation_confirmed_message(FlexClearingMemberInitiateOperationConfirmedMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->part_id = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = arbitrary(); }
  record->target_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Flex Clearing Member Initiate Operation Confirmed Message to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_flex_clearing_member_initiate_operation_confirmed_message(const FlexClearingMemberInitiateOperationConfirmedMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->part_id;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->wide_status_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->member_id[i]; }
  wire[at++] = record->target_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->req_cm_seq[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Flex Clearing Member Initiate Operation Confirmed Message off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_flex_clearing_member_initiate_operation_confirmed_message(FlexClearingMemberInitiateOperationConfirmedMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->part_id = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->member_id[i] = wire[at++]; }
  record->target_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->req_cm_seq[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Flex Clearing Member Initiate Operation Confirmed Message is what was written, byte for byte */
static void equal_flex_clearing_member_initiate_operation_confirmed_message(const FlexClearingMemberInitiateOperationConfirmedMessage *read, const FlexClearingMemberInitiateOperationConfirmedMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->part_id == written->part_id);
  for (size_t i = 0; i < 2; i++) { assert(read->wide_status_code[i] == written->wide_status_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->member_id[i] == written->member_id[i]); }
  assert(read->target_id == written->target_id);
  for (size_t i = 0; i < 4; i++) { assert(read->req_cm_seq[i] == written->req_cm_seq[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Flex Clearing Member Initiate Operation Confirmed Message: written and read back, then read and written back */
static void check_flex_clearing_member_initiate_operation_confirmed_message(void) {
  FlexClearingMemberInitiateOperationConfirmedMessage sent;
  FlexClearingMemberInitiateOperationConfirmedMessage got;
  uint8_t wire[32];
  uint8_t again[32];

  any_flex_clearing_member_initiate_operation_confirmed_message(&sent);
  assert(encode_flex_clearing_member_initiate_operation_confirmed_message(&sent, wire, 0) == 32);
  assert(decode_flex_clearing_member_initiate_operation_confirmed_message(&got, wire, 0) == 32);
  equal_flex_clearing_member_initiate_operation_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_flex_clearing_member_initiate_operation_confirmed_message(&got, wire, 0) == 32);
  assert(encode_flex_clearing_member_initiate_operation_confirmed_message(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Tail: 1 byte ---------------------------------------------------- */

/* Tmp Message Tail, carrying the check sum of a message */
typedef struct {
  uint8_t check_sum;  /* byte 0 */
} MessageTail;

/* any Message Tail at all: every byte one the checker chooses */
static void any_message_tail(MessageTail *record) {
  record->check_sum = arbitrary();
}

/* Message Tail to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_message_tail(const MessageTail *record, uint8_t *wire, size_t at) {
  wire[at++] = record->check_sum;

  return at;
}

/* Message Tail off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_message_tail(MessageTail *record, const uint8_t *wire, size_t at) {
  record->check_sum = wire[at++];

  return at;
}

/* what was read of Message Tail is what was written, byte for byte */
static void equal_message_tail(const MessageTail *read, const MessageTail *written) {
  assert(read->check_sum == written->check_sum);
}

/* Message Tail: written and read back, then read and written back */
static void check_message_tail(void) {
  MessageTail sent;
  MessageTail got;
  uint8_t wire[1];
  uint8_t again[1];

  any_message_tail(&sent);
  assert(encode_message_tail(&sent, wire, 0) == 1);
  assert(decode_message_tail(&got, wire, 0) == 1);
  equal_message_tail(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_message_tail(&got, wire, 0) == 1);
  assert(encode_message_tail(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_header_time();
  check_hdr();
  check_wake_up_call_message();
  check_wake_up_call_confirmed_message();
  check_logon_notice_message();
  check_sub_hdr();
  check_final_sequential_number_notification_for_group_message();
  check_request_logon_message();
  check_activate_application_system_message();
  check_activate_application_system_confirmed_message();
  check_logout_confirmed_message();
  check_confirm_connection_message();
  check_connection_confirmed_message();
  check_symbol_text();
  check_org_trans_time_msg_time();
  check_transact_time_msg_time();
  check_long_symbol_text();
  check_symbol_num_x();
  check_symbol_txt_x();
  check_leg_sym_symbol_num_x();
  check_leg_sym_symbol_txt_x();
  check_org_trans_time_msg_time_x();
  check_transact_time_msg_time_x();
  check_clearing_member_initiate_operation_message();
  check_clearing_member_initiate_operation_confirmed_message();
  check_flex_clearing_member_initiate_operation_message();
  check_flex_clearing_member_initiate_operation_confirmed_message();
  check_message_tail();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
