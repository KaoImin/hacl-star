/* This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
 * KreMLin invocation: /Users/bhargava/Desktop/repositories/kremlin/krml -I /Users/bhargava/Desktop/repositories/hacl-star/code/lib/kremlin -I /Users/bhargava/Desktop/repositories/kremlin/kremlib/compat -I /Users/bhargava/Desktop/repositories/hacl-star/specs -I . -ccopt -march=native -verbose -ldopt -flto -tmpdir mpfr-c mpfr-c/out.krml -skip-compilation -minimal -add-include "kremlib.h" -bundle MPFR=*
 * F* version: 2441c5c2
 * KreMLin version: c65d4779
 */

#include "MPFR.h"

static bool MPFR_RoundingMode_uu___is_MPFR_RNDN(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDN:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDZ(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDZ:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDU(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDU:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDD(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDD:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(MPFR_RoundingMode_mpfr_rnd_t rnd, bool neg)
{
  return
    MPFR_RoundingMode_uu___is_MPFR_RNDZ(rnd)
    || MPFR_RoundingMode_uu___is_MPFR_RNDU(rnd) && neg
    || MPFR_RoundingMode_uu___is_MPFR_RNDD(rnd) && !neg;
}

static uint32_t MPFR_Lib_mpfr_GET_PREC(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_struct f = x[0U];
  return f.mpfr_prec;
}

static void MPFR_Lib_mpfr_SET_EXP(MPFR_Lib_mpfr_struct *x, int32_t e)
{
  MPFR_Lib_mpfr_struct f = x[0U];
  MPFR_Lib_mpfr_struct uu___54_3309 = f;
  x[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___54_3309.mpfr_prec,
        .mpfr_sign = uu___54_3309.mpfr_sign,
        .mpfr_exp = e,
        .mpfr_d = uu___54_3309.mpfr_d
      }
    );
}

static void MPFR_Lib_mpfr_SET_INF(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_SET_EXP(x, (int32_t)-0x80000000 + (int32_t)3);
}

static int32_t MPFR_Lib_mpfr_SIGN(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_struct f = x[0U];
  return f.mpfr_sign;
}

static void MPFR_Lib_mpfr_SET_SIGN(MPFR_Lib_mpfr_struct *x, int32_t s)
{
  MPFR_Lib_mpfr_struct f = x[0U];
  MPFR_Lib_mpfr_struct uu___55_3868 = f;
  x[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___55_3868.mpfr_prec,
        .mpfr_sign = s,
        .mpfr_exp = uu___55_3868.mpfr_exp,
        .mpfr_d = uu___55_3868.mpfr_d
      }
    );
}

static int32_t MPFR_Lib_mpfr_NEG_SIGN(int32_t s)
{
  if (s == (int32_t)1)
    return (int32_t)-1;
  else
    return (int32_t)1;
}

static bool MPFR_Lib_mpfr_IS_NEG(MPFR_Lib_mpfr_struct *x)
{
  return MPFR_Lib_mpfr_SIGN(x) < (int32_t)0;
}

static bool MPFR_Lib_mpfr_IS_NEG_SIGN(int32_t s)
{
  return s < (int32_t)0;
}

static uint64_t *MPFR_Lib_mpfr_MANT(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_struct f = x[0U];
  return f.mpfr_d;
}

static uint32_t MPFR_Lib_mpfr_LAST_LIMB(MPFR_Lib_mpfr_struct *x)
{
  return (MPFR_Lib_mpfr_GET_PREC(x) - (uint32_t)1U) / (uint32_t)64U;
}

static uint32_t MPFR_Lib_mpfr_LIMB_SIZE(MPFR_Lib_mpfr_struct *x)
{
  return MPFR_Lib_mpfr_LAST_LIMB(x) + (uint32_t)1U;
}

static uint64_t MPFR_Lib_mpfr_LIMB_ONE = (uint64_t)1U;

static uint64_t MPFR_Lib_mpfr_LIMB_MASK(uint32_t s)
{
  uint64_t lsh = (uint64_t)1U << s;
  return lsh - (uint64_t)1U;
}

static uint64_t MPFR_Lib_mpfr_LIMB_HIGHBIT = (uint64_t)0x8000000000000000U;

static uint64_t MPFR_Lib_mpfr_LIMB_MAX = (uint64_t)0xffffffffffffffffU;

static void MPFR_Lib_mpfr_setmax_rec(MPFR_Lib_mpfr_struct *x, uint32_t i)
{
  uint64_t *mant = MPFR_Lib_mpfr_MANT(x);
  if (i == (uint32_t)0U)
  {
    uint32_t p = MPFR_Lib_mpfr_GET_PREC(x);
    uint32_t l = MPFR_Lib_mpfr_LIMB_SIZE(x);
    mant[i] = MPFR_Lib_mpfr_LIMB_MAX << l * (uint32_t)64U - p;
    uint64_t *uu____0 = MPFR_Lib_mpfr_MANT(x);
    uint64_t *uu____1 = MPFR_Lib_mpfr_MANT(x);
  }
  else
  {
    MPFR_Lib_mpfr_setmax_rec(x, i - (uint32_t)1U);
    mant[i] = MPFR_Lib_mpfr_LIMB_MAX;
  }
}

static void MPFR_Lib_mpfr_setmax(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_SET_EXP(x, (int32_t)0x40000000 - (int32_t)1);
  MPFR_Lib_mpfr_setmax_rec(x, MPFR_Lib_mpfr_LAST_LIMB(x));
  uint32_t p = MPFR_Lib_mpfr_GET_PREC(x);
  uint32_t l = MPFR_Lib_mpfr_LIMB_SIZE(x);
}

static int32_t
MPFR_Exceptions_mpfr_overflow(
  MPFR_Lib_mpfr_struct *x,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  int32_t sign
)
{
  MPFR_Lib_mpfr_SET_SIGN(x, sign);
  if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, MPFR_Lib_mpfr_IS_NEG_SIGN(sign)))
  {
    MPFR_Lib_mpfr_setmax(x);
    return MPFR_Lib_mpfr_NEG_SIGN(sign);
  }
  else
  {
    MPFR_Lib_mpfr_SET_INF(x);
    return sign;
  }
}

typedef struct MPFR_Add1sp1_state_s
{
  uint32_t sh;
  int32_t bx;
  uint64_t rb;
  uint64_t sb;
}
MPFR_Add1sp1_state;

static MPFR_Add1sp1_state
MPFR_Add1sp1_mk_state(uint32_t sh, int32_t bx, uint64_t rb, uint64_t sb)
{
  return ((MPFR_Add1sp1_state){ .sh = sh, .bx = bx, .rb = rb, .sb = sb });
}

typedef struct K___uint64_t_int32_t_s
{
  uint64_t fst;
  int32_t snd;
}
K___uint64_t_int32_t;

typedef struct K___uint64_t_uint64_t_int32_t_s
{
  uint64_t fst;
  uint64_t snd;
  int32_t thd;
}
K___uint64_t_uint64_t_int32_t;

static int32_t
MPFR_Add1sp1_mpfr_add1sp1(
  MPFR_Lib_mpfr_struct *a,
  MPFR_Lib_mpfr_struct *b,
  MPFR_Lib_mpfr_struct *c,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  uint32_t p
)
{
  MPFR_Lib_mpfr_struct uu____0 = a[0U];
  MPFR_Lib_mpfr_struct uu____1 = b[0U];
  MPFR_Lib_mpfr_struct uu____2 = c[0U];
  int32_t bx = uu____1.mpfr_exp;
  int32_t cx = uu____2.mpfr_exp;
  uint32_t sh = (uint32_t)64U - p;
  MPFR_Add1sp1_state st;
  if (bx == cx)
  {
    uint64_t *ap = uu____0.mpfr_d;
    uint64_t *bp = uu____1.mpfr_d;
    uint64_t *cp = uu____2.mpfr_d;
    uint64_t a0 = (bp[0U] >> (uint32_t)1U) + (cp[0U] >> (uint32_t)1U);
    int32_t bx1 = uu____1.mpfr_exp + (int32_t)1;
    uint64_t rb = a0 & MPFR_Lib_mpfr_LIMB_ONE << sh - (uint32_t)1U;
    ap[0U] = a0 ^ rb;
    uint64_t sb = (uint64_t)0U;
    st = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb);
  }
  else
  {
    MPFR_Add1sp1_state ite0;
    if (bx > cx)
    {
      int32_t bx1 = uu____1.mpfr_exp;
      int32_t cx1 = uu____2.mpfr_exp;
      uint32_t d = (uint32_t)(bx1 - cx1);
      uint64_t mask = MPFR_Lib_mpfr_LIMB_MASK(sh);
      MPFR_Add1sp1_state ite1;
      if (d < sh)
      {
        uint64_t *ap = uu____0.mpfr_d;
        uint64_t *bp = uu____1.mpfr_d;
        uint64_t *cp = uu____2.mpfr_d;
        int32_t bx2 = uu____1.mpfr_exp;
        uint64_t a0 = bp[0U] + (cp[0U] >> d);
        K___uint64_t_int32_t scrut;
        if (a0 < bp[0U])
          scrut =
            (
              (K___uint64_t_int32_t){
                .fst = MPFR_Lib_mpfr_LIMB_HIGHBIT | a0 >> (uint32_t)1U,
                .snd = bx2 + (int32_t)1
              }
            );
        else
          scrut = ((K___uint64_t_int32_t){ .fst = a0, .snd = bx2 });
        uint64_t a01 = scrut.fst;
        int32_t bx3 = scrut.snd;
        uint64_t rb = a01 & MPFR_Lib_mpfr_LIMB_ONE << sh - (uint32_t)1U;
        uint64_t sb = a01 & mask ^ rb;
        ap[0U] = a01 & ~mask;
        ite1 = MPFR_Add1sp1_mk_state(sh, bx3, rb, sb);
      }
      else
      {
        MPFR_Add1sp1_state ite;
        if (d < (uint32_t)64U)
        {
          uint64_t *ap = uu____0.mpfr_d;
          uint64_t *bp = uu____1.mpfr_d;
          uint64_t *cp = uu____2.mpfr_d;
          int32_t bx2 = uu____1.mpfr_exp;
          uint64_t sb = cp[0U] << (uint32_t)64U - d;
          uint64_t a0 = bp[0U] + (cp[0U] >> d);
          K___uint64_t_uint64_t_int32_t scrut;
          if (a0 < bp[0U])
            scrut =
              (
                (K___uint64_t_uint64_t_int32_t){
                  .fst = sb | a0 & (uint64_t)1U,
                  .snd = MPFR_Lib_mpfr_LIMB_HIGHBIT | a0 >> (uint32_t)1U,
                  .thd = bx2 + (int32_t)1
                }
              );
          else
            scrut = ((K___uint64_t_uint64_t_int32_t){ .fst = sb, .snd = a0, .thd = bx2 });
          uint64_t sb1 = scrut.fst;
          uint64_t a01 = scrut.snd;
          int32_t bx3 = scrut.thd;
          uint64_t rb = a01 & MPFR_Lib_mpfr_LIMB_ONE << sh - (uint32_t)1U;
          uint64_t sb2 = sb1 | a01 & mask ^ rb;
          ap[0U] = a01 & ~mask;
          ite = MPFR_Add1sp1_mk_state(sh, bx3, rb, sb2);
        }
        else
        {
          uint64_t *ap = uu____0.mpfr_d;
          uint64_t *bp = uu____1.mpfr_d;
          int32_t bx2 = uu____1.mpfr_exp;
          ap[0U] = bp[0U];
          uint64_t rb = (uint64_t)0U;
          uint64_t sb = (uint64_t)1U;
          ite = MPFR_Add1sp1_mk_state(sh, bx2, rb, sb);
        }
        ite1 = ite;
      }
      ite0 = ite1;
    }
    else
    {
      int32_t bx1 = uu____2.mpfr_exp;
      int32_t cx1 = uu____1.mpfr_exp;
      uint32_t d = (uint32_t)(bx1 - cx1);
      uint64_t mask = MPFR_Lib_mpfr_LIMB_MASK(sh);
      MPFR_Add1sp1_state ite1;
      if (d < sh)
      {
        uint64_t *ap = uu____0.mpfr_d;
        uint64_t *bp = uu____2.mpfr_d;
        uint64_t *cp = uu____1.mpfr_d;
        int32_t bx2 = uu____2.mpfr_exp;
        uint64_t a0 = bp[0U] + (cp[0U] >> d);
        K___uint64_t_int32_t scrut;
        if (a0 < bp[0U])
          scrut =
            (
              (K___uint64_t_int32_t){
                .fst = MPFR_Lib_mpfr_LIMB_HIGHBIT | a0 >> (uint32_t)1U,
                .snd = bx2 + (int32_t)1
              }
            );
        else
          scrut = ((K___uint64_t_int32_t){ .fst = a0, .snd = bx2 });
        uint64_t a01 = scrut.fst;
        int32_t bx3 = scrut.snd;
        uint64_t rb = a01 & MPFR_Lib_mpfr_LIMB_ONE << sh - (uint32_t)1U;
        uint64_t sb = a01 & mask ^ rb;
        ap[0U] = a01 & ~mask;
        ite1 = MPFR_Add1sp1_mk_state(sh, bx3, rb, sb);
      }
      else
      {
        MPFR_Add1sp1_state ite;
        if (d < (uint32_t)64U)
        {
          uint64_t *ap = uu____0.mpfr_d;
          uint64_t *bp = uu____2.mpfr_d;
          uint64_t *cp = uu____1.mpfr_d;
          int32_t bx2 = uu____2.mpfr_exp;
          uint64_t sb = cp[0U] << (uint32_t)64U - d;
          uint64_t a0 = bp[0U] + (cp[0U] >> d);
          K___uint64_t_uint64_t_int32_t scrut;
          if (a0 < bp[0U])
            scrut =
              (
                (K___uint64_t_uint64_t_int32_t){
                  .fst = sb | a0 & (uint64_t)1U,
                  .snd = MPFR_Lib_mpfr_LIMB_HIGHBIT | a0 >> (uint32_t)1U,
                  .thd = bx2 + (int32_t)1
                }
              );
          else
            scrut = ((K___uint64_t_uint64_t_int32_t){ .fst = sb, .snd = a0, .thd = bx2 });
          uint64_t sb1 = scrut.fst;
          uint64_t a01 = scrut.snd;
          int32_t bx3 = scrut.thd;
          uint64_t rb = a01 & MPFR_Lib_mpfr_LIMB_ONE << sh - (uint32_t)1U;
          uint64_t sb2 = sb1 | a01 & mask ^ rb;
          ap[0U] = a01 & ~mask;
          ite = MPFR_Add1sp1_mk_state(sh, bx3, rb, sb2);
        }
        else
        {
          uint64_t *ap = uu____0.mpfr_d;
          uint64_t *bp = uu____2.mpfr_d;
          int32_t bx2 = uu____2.mpfr_exp;
          ap[0U] = bp[0U];
          uint64_t rb = (uint64_t)0U;
          uint64_t sb = (uint64_t)1U;
          ite = MPFR_Add1sp1_mk_state(sh, bx2, rb, sb);
        }
        ite1 = ite;
      }
      ite0 = ite1;
    }
    st = ite0;
  }
  uint64_t *uu____3 = MPFR_Lib_mpfr_MANT(a);
  uint64_t *uu____4 = MPFR_Lib_mpfr_MANT(a);
  if (st.bx > (int32_t)0x40000000 - (int32_t)1)
  {
    int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, MPFR_Lib_mpfr_SIGN(a));
    return t;
  }
  else
  {
    uint64_t *ap = MPFR_Lib_mpfr_MANT(a);
    uint64_t a0 = ap[0U];
    MPFR_Lib_mpfr_SET_EXP(a, st.bx);
    if (st.rb == (uint64_t)0U && st.sb == (uint64_t)0U)
      return (int32_t)0;
    else if (MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode))
      if
      (
        st.rb
        == (uint64_t)0U
        || st.sb == (uint64_t)0U && (a0 & MPFR_Lib_mpfr_LIMB_ONE << st.sh) == (uint64_t)0U
      )
        return MPFR_Lib_mpfr_NEG_SIGN(MPFR_Lib_mpfr_SIGN(a));
      else
      {
        uint64_t *ap1 = MPFR_Lib_mpfr_MANT(a);
        ap1[0U] = ap1[0U] + (MPFR_Lib_mpfr_LIMB_ONE << st.sh);
        if (ap1[0U] == (uint64_t)0U)
        {
          ap1[0U] = MPFR_Lib_mpfr_LIMB_HIGHBIT;
          if (st.bx + (int32_t)1 <= (int32_t)0x40000000 - (int32_t)1)
          {
            MPFR_Lib_mpfr_SET_EXP(a, st.bx + (int32_t)1);
            return MPFR_Lib_mpfr_SIGN(a);
          }
          else
          {
            int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, MPFR_Lib_mpfr_SIGN(a));
            return t;
          }
        }
        else
          return MPFR_Lib_mpfr_SIGN(a);
      }
    else if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, MPFR_Lib_mpfr_IS_NEG(a)))
      return MPFR_Lib_mpfr_NEG_SIGN(MPFR_Lib_mpfr_SIGN(a));
    else
    {
      uint64_t *ap1 = MPFR_Lib_mpfr_MANT(a);
      ap1[0U] = ap1[0U] + (MPFR_Lib_mpfr_LIMB_ONE << st.sh);
      if (ap1[0U] == (uint64_t)0U)
      {
        ap1[0U] = MPFR_Lib_mpfr_LIMB_HIGHBIT;
        if (st.bx + (int32_t)1 <= (int32_t)0x40000000 - (int32_t)1)
        {
          MPFR_Lib_mpfr_SET_EXP(a, st.bx + (int32_t)1);
          return MPFR_Lib_mpfr_SIGN(a);
        }
        else
        {
          int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, MPFR_Lib_mpfr_SIGN(a));
          return t;
        }
      }
      else
        return MPFR_Lib_mpfr_SIGN(a);
    }
  }
}

int32_t
(*MPFR_mpfr_add1sp1)(
  MPFR_Lib_mpfr_struct *x0,
  MPFR_Lib_mpfr_struct *x1,
  MPFR_Lib_mpfr_struct *x2,
  MPFR_RoundingMode_mpfr_rnd_t x3,
  uint32_t x4
) = MPFR_Add1sp1_mpfr_add1sp1;

