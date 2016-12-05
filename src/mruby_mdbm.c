#include <string.h>

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/variable.h"

#include "mdbm.h"

#define E_MDBM_ERROR (mrb_class_get_under(mrb, mrb_class_get(mrb, "MDBM"), "MdbmHandlerError"))

static void
_mdbm_close(mrb_state *mrb, void *p)
{
  mdbm_close((MDBM*)p);
}

static const
struct mrb_data_type MDBM_type = {
  "MDBM", _mdbm_close,
};

static mrb_value
mrb_mdbm_open(mrb_state *mrb, mrb_value self)
{
  char* filename;
  mrb_int flags, mode, psize, presize;

  mrb_get_args(mrb, "ziiii", &filename, &flags, &mode, &psize, &presize);

  MDBM *mdbm = mdbm_open(filename, flags, mode, psize, presize);
  if (!mdbm) {
    mrb_raise(mrb, E_MDBM_ERROR, "mdbm_open failed");
  }

  DATA_TYPE(self) = &MDBM_type;
  DATA_PTR(self) = mdbm;

  return self;
}

static mrb_value
mrb_mdbm_fetch(mrb_state *mrb, mrb_value self)
{
  char* key;
  mrb_get_args(mrb, "z", &key);

  MDBM *mdbm = (MDBM*)DATA_PTR(self);
  if (!mdbm) {
    mrb_raise(mrb, E_MDBM_ERROR, "mdbm is closed");
  }

  datum k, v;
  k.dptr = key;
  k.dsize = strlen(key);
  mdbm_lock(mdbm);
  v = mdbm_fetch(mdbm, k);
  mdbm_unlock(mdbm);

  if (v.dptr) {
    return mrb_str_new(mrb, v.dptr, v.dsize);
  } else {
    return mrb_nil_value();
  }
}

static mrb_value
mrb_mdbm_store(mrb_state *mrb, mrb_value self)
{
  char *key, *value;
  mrb_int mode;
  mrb_get_args(mrb, "zzi", &key, &value, &mode);

  MDBM *mdbm = (MDBM*)DATA_PTR(self);
  if (!mdbm) {
    mrb_raise(mrb, E_MDBM_ERROR, "mdbm is closed");
  }

  datum k, v;
  k.dptr = key;
  k.dsize = strlen(key);
  v.dptr = value;
  v.dsize = strlen(value);
  mdbm_lock(mdbm);
  int rv = mdbm_store(mdbm, k, v, mode);
  mdbm_unlock(mdbm);

  if (rv) {
    mrb_raise(mrb, E_MDBM_ERROR, "mdbm_store is failed");
  } else {
    return mrb_nil_value();
  }
}

static mrb_value
mrb_mdbm_close(mrb_state *mrb, mrb_value self)
{
  MDBM *mdbm = (MDBM*)DATA_PTR(self);
  if (!mdbm) {
    mrb_raise(mrb, E_MDBM_ERROR, "mdbm is closed");
  }

  mdbm_close(mdbm);
  DATA_PTR(self) = NULL;

  return mrb_nil_value();
}

void
mrb_mruby_mdbm_gem_init(mrb_state* mrb)
{
  struct RClass *rclass;

  rclass = mrb_define_class(mrb, "MDBM", mrb->object_class);

  mrb_define_method(mrb, rclass, "initialize", mrb_mdbm_open, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, rclass, "fetch", mrb_mdbm_fetch, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "store", mrb_mdbm_store, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, rclass, "close", mrb_mdbm_close, MRB_ARGS_NONE());

  // modes
  mrb_define_const(mrb, rclass, "MDBM_O_RDONLY", mrb_fixnum_value(MDBM_O_RDONLY));
  mrb_define_const(mrb, rclass, "MDBM_O_RDWR", mrb_fixnum_value(MDBM_O_RDWR));
  mrb_define_const(mrb, rclass, "MDBM_O_WRONLY", mrb_fixnum_value(MDBM_O_WRONLY));
  mrb_define_const(mrb, rclass, "MDBM_O_CREAT", mrb_fixnum_value(MDBM_O_CREAT));
  mrb_define_const(mrb, rclass, "MDBM_O_TRUNC", mrb_fixnum_value(MDBM_O_TRUNC));
  mrb_define_const(mrb, rclass, "MDBM_O_ASYNC", mrb_fixnum_value(MDBM_O_ASYNC));
  mrb_define_const(mrb, rclass, "MDBM_O_FSYNC", mrb_fixnum_value(MDBM_O_FSYNC));
  mrb_define_const(mrb, rclass, "MDBM_O_DIRECT", mrb_fixnum_value(MDBM_O_DIRECT));
  mrb_define_const(mrb, rclass, "MDBM_NO_DIRTY", mrb_fixnum_value(MDBM_NO_DIRTY));
  mrb_define_const(mrb, rclass, "MDBM_OPEN_WINDOWED", mrb_fixnum_value(MDBM_OPEN_WINDOWED));
  mrb_define_const(mrb, rclass, "MDBM_PROTECT", mrb_fixnum_value(MDBM_PROTECT));
  mrb_define_const(mrb, rclass, "MDBM_DBSIZE_MB", mrb_fixnum_value(MDBM_DBSIZE_MB));
  mrb_define_const(mrb, rclass, "MDBM_LARGE_OBJECTS", mrb_fixnum_value(MDBM_LARGE_OBJECTS));
  mrb_define_const(mrb, rclass, "MDBM_PARTITIONED_LOCKS", mrb_fixnum_value(MDBM_PARTITIONED_LOCKS));
  mrb_define_const(mrb, rclass, "MDBM_RW_LOCKS", mrb_fixnum_value(MDBM_RW_LOCKS));
  mrb_define_const(mrb, rclass, "MDBM_CREATE_V3", mrb_fixnum_value(MDBM_CREATE_V3));
  mrb_define_const(mrb, rclass, "MDBM_OPEN_NOLOCK", mrb_fixnum_value(MDBM_OPEN_NOLOCK));
  mrb_define_const(mrb, rclass, "MDBM_ANY_LOCKS", mrb_fixnum_value(MDBM_ANY_LOCKS));
  mrb_define_const(mrb, rclass, "MDBM_SINGLE_ARCH", mrb_fixnum_value(MDBM_SINGLE_ARCH));

  mrb_define_const(mrb, rclass, "MDBM_INSERT", mrb_fixnum_value(MDBM_INSERT));
  mrb_define_const(mrb, rclass, "MDBM_REPLACE", mrb_fixnum_value(MDBM_REPLACE));
  mrb_define_const(mrb, rclass, "MDBM_INSERT_DUP", mrb_fixnum_value(MDBM_INSERT_DUP));
  mrb_define_const(mrb, rclass, "MDBM_MODIFY", mrb_fixnum_value(MDBM_MODIFY));
  mrb_define_const(mrb, rclass, "MDBM_RESERVE", mrb_fixnum_value(MDBM_RESERVE));
  mrb_define_const(mrb, rclass, "MDBM_CACHE_ONLY", mrb_fixnum_value(MDBM_CACHE_ONLY));
  mrb_define_const(mrb, rclass, "MDBM_CACHE_MODIFY", mrb_fixnum_value(MDBM_CACHE_MODIFY));
}

void
mrb_mruby_mdbm_gem_final(mrb_state* mrb)
{
}

