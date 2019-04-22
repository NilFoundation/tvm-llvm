; RUN: llc < %s -march=tvm | FileCheck %s
target datalayout = "E-S1024-i256:256:256"
target triple = "tvm"

; CHECK-LABEL: newdict
define i64 @newdict() nounwind {
; CHECK: NEWDICT
  %1 = call i64 @llvm.tvm.newdict()
  ret i64 %1
}

; CHECK-LABEL: persistent_root
define i64 @persistent_root() nounwind {
; CHECK: PUSHROOT
; CHECK-NEXT: CTOS
  %1 = call i64 @llvm.tvm.get.persistent.data()
  ret i64 %1
}

; CHECK-LABEL: itos
define i64 @itos(i64 %arg) nounwind {
; CHECK: NEWC
; CHECK-NEXT: STU 256
; CHECK-NEXT: ENDC
; CHECK-NEXT: CTOS
  %1 = call i64 @llvm.tvm.inttoslice(i64 %arg)
  ret i64 %1
}

; CHECK-LABEL: stslice
define i64 @stslice(i64 %slice, i64 %builder) nounwind {
; CHECK: STSLICE
  %1 = call i64 @llvm.tvm.stslice(i64 %slice, i64 %builder)
  ret i64 %1
}

; CHECK-LABEL: throws
define void @throws(i64 %cond) {
; CHEC: THROWIF 42
  call void @llvm.tvm.throwif(i64 %cond, i64 42)
  ret void
}

; CHECK-LABEL: throws_neg
define void @throws_neg(i64 %cond) {
; CHEC: THROWIFNOT 42
  %1 = xor i64 %cond, -1
  call void @llvm.tvm.throwif(i64 %1, i64 42)
  ret void
}

declare i64 @llvm.tvm.newdict() nounwind
declare i64 @llvm.tvm.get.persistent.data() nounwind
declare i64 @llvm.tvm.inttoslice(i64 %val) nounwind
declare i64 @llvm.tvm.stslice(i64 %slice, i64 %builder) nounwind
declare void @llvm.tvm.throwif(i64 %cond, i64 %exception)
