#pragma once

#include <kabibe/types.h>

enum kabibe_ArchType {
  KABIBE_ARCHTYPE_NONE = 0,
  KABIBE_ARCHTYPE_X86_64,
};

struct kabibe_Context {
  enum kabibe_ArchType arch_type;
  kabibe_vptr          extended;
  kabibe_vptr          ir_buffer;
  kabibe_u32           ir_buffer_size;
};

enum kabibe_ResponseGenerate {
  KABIBE_STATUS_GENERATE_SUCCESS,
  KABIBE_STATUS_GENERATE_FAILURE, // Unspecified error
  KABIBE_STATUS_GENERATE_BAD_CONTEXT,
};

enum kabibe_ResponseGenerate kabibe_generate(const struct kabibe_Context * ctx);
