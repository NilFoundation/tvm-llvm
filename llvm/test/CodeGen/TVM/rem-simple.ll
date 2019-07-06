; RUN: llc < %s -march=tvm -asm-verbose=false | FileCheck %s 

target datalayout = "E-S1024-i256:256:256"
target triple = "tvm"

; Function Attrs: norecurse nounwind readnone
define dso_local i64 @rem_func(i64 %a) norecurse nounwind readnone {
; CHECK-LABEL: rem_func:

; CHECK:	PUSHINT	2863667376384852129
; CHECK:	MUL
; CHECK:	RSHIFT	64
; CHECK:	RSHIFT	12
; CHECK:	PUSHINT	18446744073709551615
; CHECK:	AND
; CHECK:	RSHIFT	63
; CHECK:	ADD
; CHECK:	PUSHINT	26385
; CHECK:	MUL
; CHECK:	PUSHINT	18446744073709551615
; CHECK:	AND
; CHECK:	SUB

entry:
  %rem = srem i64 %a, 26385
  ret i64 %rem
}

