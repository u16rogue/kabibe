#include <kabibe/kabibe.h>

kabibe_bool kabibe_context_init(
  struct kabibe_Context * ctx,
  struct kabibe_ContextInitEx * initex,
  kabibe_ArchBackend backend,
  kabibe_vptr ir,
  kabibe_u32  size
) {

  if (backend == kabibe_nilptr) {
    return kabibe_false;
  }
   
  ctx->backend        = backend;
  ctx->ir_buffer      = ir;
  ctx->ir_buffer_size = size;
  //
  ctx->irb_index      = 0;
  ctx->out_index      = 0;
  ctx->extended       = 0;

  struct kabibe__F2BData backend_f2bd;
  backend_f2bd.reason = KABIBE__F2BREASON_INIT;
  backend_f2bd.ctx    = ctx;
  backend_f2bd.initex = initex;
  if (!backend(&backend_f2bd)) {
    return kabibe_false;
  }

  return kabibe_true;
}

kabibe_bool
kabibe_context_uninit(
  struct kabibe_Context * ctx
) {

  struct kabibe__F2BData backend_f2bd;
  backend_f2bd.reason = KABIBE__F2BREASON_UNINIT;
  backend_f2bd.ctx    = ctx;
  backend_f2bd.initex = kabibe_nilptr;
  if (!ctx->backend(&backend_f2bd)) {
    return kabibe_false;
  }

  ctx->backend        = kabibe_nilptr;
  ctx->ir_buffer      = kabibe_nilptr;
  ctx->ir_buffer_size = 0;
  //
  ctx->irb_index      = 0;
  ctx->out_index      = 0;
  ctx->extended       = 0;

  return kabibe_true;
}

enum kabibe_ResponseGenerate kabibe_generate(const struct kabibe_Context * ctx) {
  (void)ctx;
  return KABIBE_RESP_GENERATE_FAILURE;
}
