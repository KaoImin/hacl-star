/* MIT License
 *
 * Copyright (c) 2016-2018 INRIA and Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __Vec_H
#define __Vec_H


#ifdef __MSVC__
#define forceinline __forceinline inline
#elif (defined(__GNUC__) || defined(__clang__))
#define forceinline __attribute__((always_inline)) inline
#else
#define forceinline inline
#endif

#if defined(__SSSE3__) || defined(__AVX2__) || defined(__AVX__)

#include <emmintrin.h>
#include <tmmintrin.h>

#define Hacl_UInt32x4_vec128
#define Hacl_UInt32x4_vec_size 4

typedef __m128i Hacl_UInt32x4_vec;

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_left_8(Hacl_UInt32x4_vec v) {
  __m128i x = _mm_set_epi8(14, 13, 12, 15, 10, 9, 8, 11, 6, 5, 4, 7, 2, 1, 0, 3);
  return _mm_shuffle_epi8(v,x);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_left_16(Hacl_UInt32x4_vec v) {
  __m128i x = _mm_set_epi8(13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);
  return _mm_shuffle_epi8(v,x);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_left(Hacl_UInt32x4_vec v, unsigned int n) {
  if (n == 8) return Hacl_UInt32x4_vec_rotate_left_8(v);
  if (n == 16) return Hacl_UInt32x4_vec_rotate_left_16(v);
  return _mm_xor_si128(_mm_slli_epi32(v,n),
		       _mm_srli_epi32(v,32-n));
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_right(Hacl_UInt32x4_vec v, unsigned int n) {
  return (Hacl_UInt32x4_vec_rotate_left(v,32-n));
}

#define Hacl_UInt32x4_vec_shuffle_right(x,n) \
  _mm_shuffle_epi32(x,_MM_SHUFFLE((3+(n))%4,(2+(n))%4,(1+(n))%4,(n)%4))

#define Hacl_UInt32x4_vec_shuffle_left(x,n) Hacl_UInt32x4_vec_shuffle_right((x),4-(n))

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32x4(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4){
  return _mm_set_epi32(x4,x3,x2,x1);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32x8(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5, uint32_t x6, uint32_t x7, uint32_t x8){
  return _mm_set_epi32(x4,x3,x2,x1);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_le(const unsigned char* in) {
  return _mm_loadu_si128((__m128i*)(in));
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load128_le(const unsigned char* in) {
  return Hacl_UInt32x4_vec_load_le(in);
}

static forceinline void Hacl_UInt32x4_vec_store_le(unsigned char* out, Hacl_UInt32x4_vec v) {
  _mm_storeu_si128((__m128i*)(out), v);
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  return _mm_add_epi32(v1, v2);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add_u32(Hacl_UInt32x4_vec v1, uint32_t x) {
  Hacl_UInt32x4_vec v2 = Hacl_UInt32x4_vec_load_32x4(x,0,0,0);
  return _mm_add_epi32(v1, v2);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_increment(Hacl_UInt32x4_vec v1) {
  Hacl_UInt32x4_vec one = Hacl_UInt32x4_vec_load_32x4(1,0,0,0);
  return _mm_add_epi32(v1, one);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_xor(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  return _mm_xor_si128(v1,v2);
}

#define Hacl_UInt32x4_vec_zero() _mm_set_epi32(0,0,0,0)

#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>

typedef uint32x4_t Hacl_UInt32x4_vec;

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_xor(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  return veorq_u32(v1,v2);
}

#define Hacl_UInt32x4_vec_rotate_left(x,n) \
  vsriq_n_u32(vshlq_n_u32((x),(n)),(x),32-(n))

#define Hacl_UInt32x4_vec_rotate_right(a, b) \
    Hacl_UInt32x4_vec_rotate_left((b), 32 - (b))

#define Hacl_UInt32x4_vec_shuffle_right(x,n) \
  vextq_u32((x),(x),(n))

#define Hacl_UInt32x4_vec_shuffle_left(a, b) \
    Hacl_UInt32x4_vec_shuffle_right((a), 4 - (b))

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32x4(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4){
  uint32_t a[4] = {x1,x2,x3,x4};
  return vld1q_u32(a);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32(uint32_t x1) {
  uint32_t a[4] = {x1,x1,x1,x1};
  return vld1q_u32(a);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32x8(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4,uint32_t x5, uint32_t x6, uint32_t x7, uint32_t x8) {
  return Hacl_UInt32x4_vec_load_32x4(x1,x2,x3,x4);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_le(const unsigned char* in) {
  return vld1q_u32((uint32_t*) in);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load128_le(const unsigned char* in) {
  return Hacl_UInt32x4_vec_load_le(in);
}

static forceinline void Hacl_UInt32x4_vec_store_le(unsigned char* out, Hacl_UInt32x4_vec v) {
  vst1q_u32((uint32_t*)out,v);
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  return vaddq_u32(v1,v2);
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add_u32(Hacl_UInt32x4_vec v1, uint32_t x) {
  Hacl_UInt32x4_vec v2 = Hacl_UInt32x4_vec_load_32x4(x,0,0,0);
  return Hacl_UInt32x4_vec_add(v1, v2);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_increment(Hacl_UInt32x4_vec v1) {
  Hacl_UInt32x4_vec one = Hacl_UInt32x4_vec_load_32x4(1,0,0,0);
  return Hacl_UInt32x4_vec_add(v1, one);
}

#define Hacl_UInt32x4_vec_zero() Hacl_UInt32x4_vec_load_32x4(0,0,0,0)

#else

#define Hacl_UInt32x4_vec128
#define Hacl_UInt32x4_vec_size 4

typedef struct {
  uint32_t v[4];
} Hacl_UInt32x4_vec;

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_xor(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  Hacl_UInt32x4_vec r;
  r.v[0] = v1.v[0] ^ v2.v[0];
  r.v[1] = v1.v[1] ^ v2.v[1];
  r.v[2] = v1.v[2] ^ v2.v[2];
  r.v[3] = v1.v[3] ^ v2.v[3];
  return r;
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_left(Hacl_UInt32x4_vec v, unsigned int n) {
  Hacl_UInt32x4_vec r;
  r.v[0] = (v.v[0] << n) ^ (v.v[0] >> (32-n));
  r.v[1] = (v.v[1] << n) ^ (v.v[1] >> (32-n));
  r.v[2] = (v.v[2] << n) ^ (v.v[2] >> (32-n));
  r.v[3] = (v.v[3] << n) ^ (v.v[3] >> (32-n));
  return r;
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_rotate_right(Hacl_UInt32x4_vec v, unsigned int n) {
  return (Hacl_UInt32x4_vec_rotate_left(v,32-n));
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_shuffle_right(Hacl_UInt32x4_vec v, unsigned int n) {
  Hacl_UInt32x4_vec r;
  r.v[0] = v.v[n%4];
  r.v[1] = v.v[(n+1)%4];
  r.v[2] = v.v[(n+2)%4];
  r.v[3] = v.v[(n+3)%4];
  return r;
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_shuffle_left(Hacl_UInt32x4_vec x, unsigned int n) {
  return Hacl_UInt32x4_vec_shuffle_right(x,4-n);
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32x4(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3){
  Hacl_UInt32x4_vec v;
  v.v[0] = x0;
  v.v[1] = x1;
  v.v[2] = x2;
  v.v[3] = x3;
  return v;
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_32(uint32_t x0){
  Hacl_UInt32x4_vec v;
  v.v[0] = x0;
  v.v[1] = x0;
  v.v[2] = x0;
  v.v[3] = x0;
  return v;
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load_le(const uint8_t* in) {
  Hacl_UInt32x4_vec r;
  r.v[0] = load32_le((uint8_t*)in);
  r.v[1] = load32_le((uint8_t*)in+4);
  r.v[2] = load32_le((uint8_t*)in+8);
  r.v[3] = load32_le((uint8_t*)in+12);
  return r;
}

static forceinline void Hacl_UInt32x4_vec_store_le(unsigned char* out, Hacl_UInt32x4_vec r) {
  store32_le(out,r.v[0]);
  store32_le(out+4,r.v[1]);
  store32_le(out+8,r.v[2]);
  store32_le(out+12,r.v[3]);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_load128_le(const unsigned char* in) {
  return Hacl_UInt32x4_vec_load_le(in);
}


static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add(Hacl_UInt32x4_vec v1, Hacl_UInt32x4_vec v2) {
  Hacl_UInt32x4_vec r;
  r.v[0] = v1.v[0] + v2.v[0];
  r.v[1] = v1.v[1] + v2.v[1];
  r.v[2] = v1.v[2] + v2.v[2];
  r.v[3] = v1.v[3] + v2.v[3];
  return r;
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_add_u32(Hacl_UInt32x4_vec v1, uint32_t x) {
  Hacl_UInt32x4_vec v2 = Hacl_UInt32x4_vec_load_32x4(x,0,0,0);
  return Hacl_UInt32x4_vec_add(v1, v2);
}

static forceinline Hacl_UInt32x4_vec Hacl_UInt32x4_vec_increment(Hacl_UInt32x4_vec v1) {
  Hacl_UInt32x4_vec one = Hacl_UInt32x4_vec_load_32x4(1,0,0,0);
  return Hacl_UInt32x4_vec_add(v1, one);
}

#define Hacl_UInt32x4_vec_zero() Hacl_UInt32x4_vec_load_32x4(0,0,0,0)

#endif

#endif
