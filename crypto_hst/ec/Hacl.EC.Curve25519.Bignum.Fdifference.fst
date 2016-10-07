module Hacl.EC.Curve25519.Bignum.Fdifference

open FStar.Mul
open FStar.HST
open FStar.HyperStack
open FStar.Ghost
open FStar.Buffer
open FStar.Math.Lib

open Hacl.UInt64

open Hacl.EC.Curve25519.Parameters
open Hacl.EC.Curve25519.Bigint
open Hacl.EC.Curve25519.Utils
open Hacl.EC.Curve25519.Bignum.Fdifference.Lemmas

#reset-options "--initial_fuel 0 --max_fuel 0"

(* Module abbreviations *)
module HH = FStar.HyperHeap
module HS = FStar.HyperStack

module U8  = FStar.UInt8
module U32 = FStar.UInt32
module H8  = Hacl.UInt8
module H32  = Hacl.UInt32
module H64  = Hacl.UInt64


val add_big_zero_core:
  b:bigint ->
  Stack unit
    (requires (fun h -> norm h b))
    (ensures (fun h0 _ h1 -> addedZero h0 h1 b /\ modifies_1 b h0 h1))
let add_big_zero_core b =
  let two52m38 = (Hacl.Cast.uint64_to_sint64 0xfffffffffffdauL) in // pow2 52 - 38
  let two52m2 =  (Hacl.Cast.uint64_to_sint64 0xffffffffffffeuL) in // pow2 52 - 2
  lemma_pow2_52m38 ();
  lemma_pow2_52m2 ();
  cut(v two52m38 = pow2 52 - 38 /\ v two52m2 = pow2 52 - 2);
  let b0 = b.(0ul) in
  let b1 = b.(1ul) in
  let b2 = b.(2ul) in
  let b3 = b.(3ul) in
  let b4 = b.(4ul) in
  lemma_add_big_zero_core b0 b1 b2 b3 b4;
  let c0 = b0 +^ two52m38 in
  let c1 = b1 +^ two52m2  in
  let c2 = b2 +^ two52m2  in
  let c3 = b3 +^ two52m2  in
  let c4 = b4 +^ two52m2  in
  update_5 b c0 c1 c2 c3 c4


(*
val add_big_zero: b:bigint -> Stack unit
  (requires (fun h -> live h b))
  (ensures (fun h0 _ h1 -> live h1 b /\ modifies_1 b h0 h1))
let add_big_zero b =
  (* let h0 = HST.get() in *)
  add_big_zero_core b(* ; *)
  (* let h1 = HST.get() in *)
  (* add_big_zero_lemma h0 h1 b *)


(* #reset-options *)
val fdifference_aux_1:
  a:bigint ->
  b:bigint{disjoint a b} -> ctr:u32{U32.v ctr < norm_length} -> Stack unit
    (requires (fun h -> live h a /\ live h b
      (* /\ norm_length <= length a /\ norm_length <= length b *)
      (*         /\ (forall (i:nat{ i >= U32.v ctr /\ i < norm_length}). v (get h b i) >= v (get h a i)) *)
    ))
    (ensures (fun h0 _ h1 -> live h1 a /\ modifies_1 a h0 h1
      (* live h0 a /\ live h1 a /\ live h0 b /\ live h1 b *)
      (* /\ length a = length a /\ length b = length b *)
      (* /\ norm_length <= length a /\ norm_length <= length b /\ modifies_1 a h0 h1 *)
      (* /\ (forall (i:nat). *)
      (* 	((i >= U32.v ctr+1 /\ i < norm_length) ==>  (v (get h1 b i) >= v (get h1 a i) *)
      (* 						/\ get h1 a i == get h0 a i)) *)
      (* 	/\ (((i<U32.v ctr \/ i>=norm_length) /\ i<length a) ==> get h1 a i == get h0 a i)) *)
      (* /\ v (get h1 a (U32.v ctr)) = v (get h0 b (U32.v ctr)) - v (get h0 a (U32.v ctr)) *)
    ))
let fdifference_aux_1 a b ctr =
  (* let h0 = HST.get() in *)
  let i = ctr in
  (* FdifferenceLemmas.helper_lemma_3 i norm_length;  *)
  (* helper_lemma_1 (U32.v i) norm_length (length a); *)
  (* helper_lemma_1 (U32.v i) norm_length (length b); *)
  let ai = a.(i) in
  let bi = b.(i) in
  (* assert(U32.v i >= U32.v ctr /\ U32.v i < norm_length);  *)
  (* cut(b2t(v (get h0 b (U32.v i)) >= v (get h0 a (U32.v i))));  *)
  (* let z = bi -^ ai in  *)
  upd a i (bi -%^ ai)
  (* let h1 = HST.get() in *)
  (* (\* upd_lemma h0 h1 a i z; *\) *)
  (* (\* no_upd_lemma h0 h1 b ((only a)) *\) *)
  (* () *)

val fdifference_aux:
  a:bigint -> b:bigint{disjoint a b} -> ctr:u32{U32.v ctr <= norm_length } -> Stack unit
    (requires (fun h -> live h a /\ live h b
      (* /\ (forall (i:nat). (i >= U32.v ctr /\ i < norm_length) ==> (v (get h b i) >= v (get h a i))) *)
    ))
    (ensures (fun h0 _ h1 -> live h1 a /\ modifies_1 a h0 h1
      (* (live h0 a) /\ (live h0 b) /\ (live h1 a) /\ (live h1 b) *)
      (* /\ (norm_length <= length a /\ norm_length <= length b) *)
      (* /\ (modifies_1 a h0 h1) *)
      (* /\ (length a = length a) *)
      (* /\ (forall (i:nat).  *)
      (* 	  ((i>= U32.v ctr /\ i<norm_length) ==>   *)
      (* 	    (v (get h1 a i) = v (get h0 b i) - v (get h0 a i))) *)
      (* 	  /\ (((i<U32.v ctr \/ i >= norm_length) /\ i<length a) ==> (get h1 a i == get h0 a i))) *)
    ))
let rec fdifference_aux a b ctr =
  (* //@@ *)
  (* let h0 = HST.get() in *)
  if U32 (ctr =^ nlength) then ()
  else begin
      fdifference_aux_1 a b ctr;
      (* let h1 = HST.get() in *)
      (* no_upd_lemma h0 h1 b ((only a)); *)
      fdifference_aux a b (U32 (ctr +^ 1ul))(* ;  *)
      (* let h2 = HST.get() in *)
      (* fdifference_aux_2 h0 h1 h2 a b (U32.v ctr) *)
  end

val fdifference': a:bigint -> b:bigint{disjoint a b} -> Stack unit
    (requires (fun h -> live h a /\ live h b
      (* /\norm h a /\ filled h b *)
    ))
    (ensures (fun h0 u h1 -> live h1 a /\ modifies_1 a h0 h1
      (* /\norm h0 a /\ filled h0 b /\ filled h1 b /\ live h1 a  *)
      (* /\ modifies_1 a h0 h1 *)
      (* /\ eval h1 a norm_length = eval h0 b norm_length - eval h0 a norm_length *)
      (* /\ (forall (i:nat). i < norm_length ==> v (get h1 a i) = v (get h0 b i) - v (get h0 a i)) *)
    ))
let fdifference' a b =
  (* //@@ *)
  (* let h0 = HST.get() in *)
  (* auxiliary_lemma_0 h0 a h0 b;  *)
  fdifference_aux a b 0ul(* ;  *)
  (* let h1 = HST.get() in *)
  (* (\* auxiliary_lemma_1 h0 h1 ((only a)) min max b ;  *\) *)
  (* subtraction_lemma h0 h1 a b norm_length *)
