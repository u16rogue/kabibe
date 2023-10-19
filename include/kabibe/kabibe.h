#pragma once

#include <kabibe/types.h>


enum kabibe__F2BReason {
  KABIBE__F2BREASON_INIT,
  KABIBE__F2BREASON_UNINIT,
};

/*
 *  INTERNAL
 *  # Frontend to backend data
 */
struct kabibe__F2BData {
  enum kabibe__F2BReason        reason;
  struct kabibe_Context       * ctx;
  struct kabibe_ContextInitEx * initex;
};

/*
 *  # Architecture backend type
 */
typedef kabibe_bool(*kabibe_ArchBackend)(struct kabibe__F2BData *);

/*
 *  # Extended context initialization
 *  - Provide extra information for the generation
 *  context backend.
 */
struct kabibe_ContextInitEx {
  kabibe_u8 _;
};

/*
 *  # Generation context
 */
struct kabibe_Context {
  kabibe_ArchBackend backend;  // Active backend for this context
  kabibe_vptr        ir_buffer; // Buffer to the IR
  kabibe_u32         ir_buffer_size; // Size of the buffer containing the IR in bytes

  // [19/10/2023] This is for convenience if a backend doesn't
  // need that large of an extend memory atleast it can use
  // the memory that extend itself occupies and making it
  // well defined.
  union {
    kabibe_u64  extended;  // Managed by the backend
    struct {
      kabibe_u32  irb_index; // Current index inside the IR buffer
      kabibe_u32  out_index; // Current index inside the output buffer
    };
  };
};

/*
 *  # Initialize context
 */
kabibe_bool
kabibe_context_init(
  struct kabibe_Context       * ctx,
  struct kabibe_ContextInitEx * initex,
  kabibe_ArchBackend backend,
  kabibe_vptr        ir,
  kabibe_u32         size
);

/*
 *  # Uninitialize context
 */
kabibe_bool
kabibe_context_uninit(
  struct kabibe_Context * ctx
);

/*
 *  # Generator function response
 */
enum kabibe_ResponseGenerate {
  KABIBE_RESP_GENERATE_SUCCESS,
  KABIBE_RESP_GENERATE_FAILURE, // Unspecified error
  KABIBE_RESP_GENERATE_BAD_CONTEXT,
};

/*
 *  # Generate machine code from context
 */
enum kabibe_ResponseGenerate
kabibe_generate(
  const struct kabibe_Context * ctx
);
