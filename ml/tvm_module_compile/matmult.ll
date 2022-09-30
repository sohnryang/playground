; ModuleID = 'TVMMod'
source_filename = "TVMMod"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-darwin21.6.0"

%0 = type { double }
%1 = type { ptr, %2, i32, %3, ptr, ptr, i64 }
%2 = type { i32, i32 }
%3 = type { i8, i8, i16 }

@__TVMAPISetLastError = linkonce dllexport local_unnamed_addr global ptr null, align 8
@.str = private constant [60 x i8] c"Assert fail: (num_args == 3), matmult: num_args should be 3\00", align 1
@.str.1 = private constant [139 x i8] c"Assert fail: ((((arg.A.code == 3) || (arg.A.code == 13)) || (arg.A.code == 7)) || (arg.A.code == 4)), matmult: Expect arg[0] to be pointer\00", align 1
@.str.2 = private constant [139 x i8] c"Assert fail: ((((arg.B.code == 3) || (arg.B.code == 13)) || (arg.B.code == 7)) || (arg.B.code == 4)), matmult: Expect arg[1] to be pointer\00", align 1
@.str.3 = private constant [139 x i8] c"Assert fail: ((((arg.C.code == 3) || (arg.C.code == 13)) || (arg.C.code == 7)) || (arg.C.code == 4)), matmult: Expect arg[2] to be pointer\00", align 1
@.str.4 = private constant [87 x i8] c"Assert fail: (2 == tir.tvm_struct_get(arg.A, 0, 4)), arg.A.ndim is expected to equal 2\00", align 1
@.str.5 = private constant [202 x i8] c"Assert fail: (((tir.tvm_struct_get(arg.A, 0, 5) == (uint8)2) && (tir.tvm_struct_get(arg.A, 0, 6) == (uint8)32)) && (tir.tvm_struct_get(arg.A, 0, 7) == (uint16)1)), arg.A.dtype is expected to be float32\00", align 1
@.str.6 = private constant [166 x i8] c"Assert fail: ((uint64)0 == tir.tvm_struct_get(arg.A, 0, 8)), Argument arg.A.byte_offset has an unsatisfied constraint: ((uint64)0 == tir.tvm_struct_get(arg.A, 0, 8))\00", align 1
@.str.7 = private constant [152 x i8] c"Assert fail: (1 == tir.tvm_struct_get(arg.A, 0, 10)), Argument arg.A.device_type has an unsatisfied constraint: (1 == tir.tvm_struct_get(arg.A, 0, 10))\00", align 1
@.str.8 = private constant [87 x i8] c"Assert fail: (2 == tir.tvm_struct_get(arg.B, 0, 4)), arg.B.ndim is expected to equal 2\00", align 1
@.str.9 = private constant [202 x i8] c"Assert fail: (((tir.tvm_struct_get(arg.B, 0, 5) == (uint8)2) && (tir.tvm_struct_get(arg.B, 0, 6) == (uint8)32)) && (tir.tvm_struct_get(arg.B, 0, 7) == (uint16)1)), arg.B.dtype is expected to be float32\00", align 1
@.str.10 = private constant [127 x i8] c"Assert fail: (m == int32(arg.B.shape[0])), Argument arg.B.shape[0] has an unsatisfied constraint: (m == int32(arg.B.shape[0]))\00", align 1
@.str.11 = private constant [166 x i8] c"Assert fail: ((uint64)0 == tir.tvm_struct_get(arg.B, 0, 8)), Argument arg.B.byte_offset has an unsatisfied constraint: ((uint64)0 == tir.tvm_struct_get(arg.B, 0, 8))\00", align 1
@.str.12 = private constant [152 x i8] c"Assert fail: (1 == tir.tvm_struct_get(arg.B, 0, 10)), Argument arg.B.device_type has an unsatisfied constraint: (1 == tir.tvm_struct_get(arg.B, 0, 10))\00", align 1
@.str.13 = private constant [158 x i8] c"Assert fail: (dev_id == tir.tvm_struct_get(arg.B, 0, 9)), Argument arg.B.device_id has an unsatisfied constraint: (dev_id == tir.tvm_struct_get(arg.B, 0, 9))\00", align 1
@.str.14 = private constant [87 x i8] c"Assert fail: (2 == tir.tvm_struct_get(arg.C, 0, 4)), arg.C.ndim is expected to equal 2\00", align 1
@.str.15 = private constant [202 x i8] c"Assert fail: (((tir.tvm_struct_get(arg.C, 0, 5) == (uint8)2) && (tir.tvm_struct_get(arg.C, 0, 6) == (uint8)32)) && (tir.tvm_struct_get(arg.C, 0, 7) == (uint16)1)), arg.C.dtype is expected to be float32\00", align 1
@.str.16 = private constant [127 x i8] c"Assert fail: (n == int32(arg.C.shape[0])), Argument arg.C.shape[0] has an unsatisfied constraint: (n == int32(arg.C.shape[0]))\00", align 1
@.str.17 = private constant [127 x i8] c"Assert fail: (h == int32(arg.C.shape[1])), Argument arg.C.shape[1] has an unsatisfied constraint: (h == int32(arg.C.shape[1]))\00", align 1
@.str.18 = private constant [166 x i8] c"Assert fail: ((uint64)0 == tir.tvm_struct_get(arg.C, 0, 8)), Argument arg.C.byte_offset has an unsatisfied constraint: ((uint64)0 == tir.tvm_struct_get(arg.C, 0, 8))\00", align 1
@.str.19 = private constant [152 x i8] c"Assert fail: (1 == tir.tvm_struct_get(arg.C, 0, 10)), Argument arg.C.device_type has an unsatisfied constraint: (1 == tir.tvm_struct_get(arg.C, 0, 10))\00", align 1
@.str.20 = private constant [158 x i8] c"Assert fail: (dev_id == tir.tvm_struct_get(arg.C, 0, 9)), Argument arg.C.device_id has an unsatisfied constraint: (dev_id == tir.tvm_struct_get(arg.C, 0, 9))\00", align 1
@__tvm_main__ = weak dllexport local_unnamed_addr constant [8 x i8] c"matmult\00", align 1
@llvm.global_ctors = appending global [0 x { i32, ptr, ptr }] zeroinitializer

define dllexport i32 @matmult(ptr noalias nocapture readonly %args, ptr noalias nocapture readonly %arg_type_ids, i32 %num_args, ptr noalias nocapture readnone %out_ret_value, ptr noalias nocapture readnone %out_ret_tcode, ptr noalias nocapture readnone %resource_handle) local_unnamed_addr #0 {
entry:
  %0 = icmp eq i32 %num_args, 3
  br i1 %0, label %assert_end, label %assert_fail, !prof !5

common.ret:                                       ; preds = %assert_end84, %assert_fail83, %assert_fail81, %assert_fail79, %assert_fail77, %assert_fail75, %assert_fail73, %assert_fail69, %assert_fail67, %assert_fail65, %assert_fail63, %assert_fail61, %assert_fail59, %assert_fail55, %assert_fail53, %assert_fail51, %assert_fail49, %assert_fail45, %assert_fail43, %assert_fail41, %assert_fail39, %assert_fail
  %common.ret.op = phi i32 [ -1, %assert_fail ], [ -1, %assert_fail39 ], [ -1, %assert_fail41 ], [ -1, %assert_fail43 ], [ -1, %assert_fail45 ], [ -1, %assert_fail49 ], [ -1, %assert_fail51 ], [ -1, %assert_fail53 ], [ -1, %assert_fail55 ], [ -1, %assert_fail59 ], [ -1, %assert_fail61 ], [ -1, %assert_fail63 ], [ -1, %assert_fail65 ], [ -1, %assert_fail67 ], [ -1, %assert_fail69 ], [ -1, %assert_fail73 ], [ -1, %assert_fail75 ], [ -1, %assert_fail77 ], [ -1, %assert_fail79 ], [ -1, %assert_fail81 ], [ -1, %assert_fail83 ], [ 0, %assert_end84 ]
  ret i32 %common.ret.op

assert_fail:                                      ; preds = %entry
  %1 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %1(ptr nonnull @.str)
  br label %common.ret

assert_end:                                       ; preds = %entry
  %arg.A = load ptr, ptr %args, align 8
  %arg.A.code = load i32, ptr %arg_type_ids, align 4, !tbaa !9
  %2 = getelementptr inbounds %0, ptr %args, i64 1
  %arg.B = load ptr, ptr %2, align 8
  %3 = getelementptr inbounds i32, ptr %arg_type_ids, i64 1
  %arg.B.code = load i32, ptr %3, align 4, !tbaa !20
  %4 = getelementptr inbounds %0, ptr %args, i64 2
  %arg.C = load ptr, ptr %4, align 8
  %5 = getelementptr inbounds i32, ptr %arg_type_ids, i64 2
  %arg.C.code = load i32, ptr %5, align 4, !tbaa !22
  %A = load ptr, ptr %arg.A, align 8
  %6 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 4
  %arg.A.shape = load ptr, ptr %6, align 8
  %7 = load i64, ptr %arg.A.shape, align 8, !tbaa !25
  %n = trunc i64 %7 to i32
  %8 = getelementptr inbounds i64, ptr %arg.A.shape, i64 1
  %9 = load i64, ptr %8, align 8, !tbaa !35
  %m = trunc i64 %9 to i32
  %10 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 5
  %arg.A.strides = load ptr, ptr %10, align 8
  %11 = icmp eq i32 %m, 1
  br i1 %11, label %if_end, label %if_else

if_else:                                          ; preds = %assert_end
  %12 = icmp eq ptr %arg.A.strides, null
  br i1 %12, label %if_end.thread, label %if_else2

if_end:                                           ; preds = %if_else2, %assert_end
  %stride = phi i32 [ 0, %assert_end ], [ %17, %if_else2 ]
  %13 = icmp eq i32 %n, 1
  br i1 %13, label %if_end6, label %if_else5

if_end.thread:                                    ; preds = %if_else
  %14 = icmp eq i32 %n, 1
  %spec.select113 = select i1 %14, i32 0, i32 %m
  br label %if_end6

if_else2:                                         ; preds = %if_else
  %15 = getelementptr inbounds i64, ptr %arg.A.strides, i64 1
  %16 = load i64, ptr %15, align 8, !tbaa !37
  %17 = trunc i64 %16 to i32
  br label %if_end

if_else5:                                         ; preds = %if_end
  %18 = icmp eq ptr %arg.A.strides, null
  br i1 %18, label %if_end6, label %if_else8

if_end6:                                          ; preds = %if_end.thread, %if_else8, %if_else5, %if_end
  %19 = phi i1 [ true, %if_end ], [ false, %if_else8 ], [ false, %if_else5 ], [ %14, %if_end.thread ]
  %stride92 = phi i32 [ %stride, %if_end ], [ %stride, %if_else8 ], [ %stride, %if_else5 ], [ 1, %if_end.thread ]
  %stride87 = phi i32 [ 0, %if_end ], [ %27, %if_else8 ], [ %m, %if_else5 ], [ %spec.select113, %if_end.thread ]
  %20 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 1, i32 1
  %dev_id = load i32, ptr %20, align 4
  %B = load ptr, ptr %arg.B, align 8
  %21 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 4
  %arg.B.shape = load ptr, ptr %21, align 8
  %22 = getelementptr inbounds i64, ptr %arg.B.shape, i64 1
  %23 = load i64, ptr %22, align 8, !tbaa !47
  %h = trunc i64 %23 to i32
  %24 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 5
  %arg.B.strides = load ptr, ptr %24, align 8
  %25 = icmp eq i32 %h, 1
  br i1 %25, label %if_end13, label %if_else12

if_else8:                                         ; preds = %if_else5
  %26 = load i64, ptr %arg.A.strides, align 8, !tbaa !57
  %27 = trunc i64 %26 to i32
  br label %if_end6

if_else12:                                        ; preds = %if_end6
  %28 = icmp eq ptr %arg.B.strides, null
  br i1 %28, label %if_end13.thread, label %if_else15

if_end13:                                         ; preds = %if_else15, %if_end6
  %stride89 = phi i32 [ 0, %if_end6 ], [ %35, %if_else15 ]
  %29 = icmp eq i32 %m, 1
  br i1 %29, label %if_end20, label %if_else19

if_end13.thread:                                  ; preds = %if_else12
  %30 = icmp eq i32 %m, 1
  %spec.select114 = select i1 %30, i32 0, i32 %h
  %C100 = load ptr, ptr %arg.C, align 8
  %31 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 4
  %arg.C.shape101 = load ptr, ptr %31, align 8
  %32 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 5
  %arg.C.strides102 = load ptr, ptr %32, align 8
  br label %if_else26

if_else15:                                        ; preds = %if_else12
  %33 = getelementptr inbounds i64, ptr %arg.B.strides, i64 1
  %34 = load i64, ptr %33, align 8, !tbaa !59
  %35 = trunc i64 %34 to i32
  br label %if_end13

if_else19:                                        ; preds = %if_end13
  %36 = icmp eq ptr %arg.B.strides, null
  br i1 %36, label %if_end20, label %if_else22

if_end20:                                         ; preds = %if_else22, %if_else19, %if_end13
  %stride88 = phi i32 [ 0, %if_end13 ], [ %41, %if_else22 ], [ %h, %if_else19 ]
  %37 = icmp eq i32 %h, 1
  %C = load ptr, ptr %arg.C, align 8
  %38 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 4
  %arg.C.shape = load ptr, ptr %38, align 8
  %39 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 5
  %arg.C.strides = load ptr, ptr %39, align 8
  br i1 %37, label %if_end27, label %if_else26

if_else22:                                        ; preds = %if_else19
  %40 = load i64, ptr %arg.B.strides, align 8, !tbaa !69
  %41 = trunc i64 %40 to i32
  br label %if_end20

if_else26:                                        ; preds = %if_end13.thread, %if_end20
  %arg.C.strides111 = phi ptr [ %arg.C.strides102, %if_end13.thread ], [ %arg.C.strides, %if_end20 ]
  %arg.C.shape109 = phi ptr [ %arg.C.shape101, %if_end13.thread ], [ %arg.C.shape, %if_end20 ]
  %C107 = phi ptr [ %C100, %if_end13.thread ], [ %C, %if_end20 ]
  %stride88105 = phi i32 [ %spec.select114, %if_end13.thread ], [ %stride88, %if_end20 ]
  %stride8996103 = phi i32 [ 1, %if_end13.thread ], [ %stride89, %if_end20 ]
  %42 = icmp eq ptr %arg.C.strides111, null
  br i1 %42, label %if_end27.thread, label %if_else29

if_end27:                                         ; preds = %if_else29, %if_end20
  %arg.C.strides112 = phi ptr [ %arg.C.strides, %if_end20 ], [ %arg.C.strides111, %if_else29 ]
  %arg.C.shape110 = phi ptr [ %arg.C.shape, %if_end20 ], [ %arg.C.shape109, %if_else29 ]
  %C108 = phi ptr [ %C, %if_end20 ], [ %C107, %if_else29 ]
  %stride88106 = phi i32 [ %stride88, %if_end20 ], [ %stride88105, %if_else29 ]
  %stride8996104 = phi i32 [ %stride89, %if_end20 ], [ %stride8996103, %if_else29 ]
  %stride86 = phi i32 [ 0, %if_end20 ], [ %45, %if_else29 ]
  br i1 %19, label %if_end34, label %if_else33

if_end27.thread:                                  ; preds = %if_else26
  %spec.select = select i1 %19, i32 0, i32 %h
  br label %if_end34

if_else29:                                        ; preds = %if_else26
  %43 = getelementptr inbounds i64, ptr %arg.C.strides111, i64 1
  %44 = load i64, ptr %43, align 8, !tbaa !71
  %45 = trunc i64 %44 to i32
  br label %if_end27

if_else33:                                        ; preds = %if_end27
  %46 = icmp eq ptr %arg.C.strides112, null
  br i1 %46, label %if_end34, label %if_else36

if_end34:                                         ; preds = %if_end27.thread, %if_else36, %if_else33, %if_end27
  %stride86131 = phi i32 [ %stride86, %if_end27 ], [ %stride86, %if_else36 ], [ %stride86, %if_else33 ], [ 1, %if_end27.thread ]
  %stride8996104129 = phi i32 [ %stride8996104, %if_end27 ], [ %stride8996104, %if_else36 ], [ %stride8996104, %if_else33 ], [ %stride8996103, %if_end27.thread ]
  %stride88106127 = phi i32 [ %stride88106, %if_end27 ], [ %stride88106, %if_else36 ], [ %stride88106, %if_else33 ], [ %stride88105, %if_end27.thread ]
  %C108125 = phi ptr [ %C108, %if_end27 ], [ %C108, %if_else36 ], [ %C108, %if_else33 ], [ %C107, %if_end27.thread ]
  %arg.C.shape110123 = phi ptr [ %arg.C.shape110, %if_end27 ], [ %arg.C.shape110, %if_else36 ], [ %arg.C.shape110, %if_else33 ], [ %arg.C.shape109, %if_end27.thread ]
  %stride85 = phi i32 [ 0, %if_end27 ], [ %48, %if_else36 ], [ %h, %if_else33 ], [ %spec.select, %if_end27.thread ]
  switch i32 %arg.A.code, label %assert_fail39 [
    i32 13, label %assert_end40
    i32 7, label %assert_end40
    i32 4, label %assert_end40
    i32 3, label %assert_end40
  ]

if_else36:                                        ; preds = %if_else33
  %47 = load i64, ptr %arg.C.strides112, align 8, !tbaa !81
  %48 = trunc i64 %47 to i32
  br label %if_end34

assert_fail39:                                    ; preds = %if_end34
  %49 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %49(ptr nonnull @.str.1)
  br label %common.ret

assert_end40:                                     ; preds = %if_end34, %if_end34, %if_end34, %if_end34
  switch i32 %arg.B.code, label %assert_fail41 [
    i32 13, label %assert_end42
    i32 7, label %assert_end42
    i32 4, label %assert_end42
    i32 3, label %assert_end42
  ]

assert_fail41:                                    ; preds = %assert_end40
  %50 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %50(ptr nonnull @.str.2)
  br label %common.ret

assert_end42:                                     ; preds = %assert_end40, %assert_end40, %assert_end40, %assert_end40
  switch i32 %arg.C.code, label %assert_fail43 [
    i32 13, label %assert_end44
    i32 7, label %assert_end44
    i32 4, label %assert_end44
    i32 3, label %assert_end44
  ]

assert_fail43:                                    ; preds = %assert_end42
  %51 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %51(ptr nonnull @.str.3)
  br label %common.ret

assert_end44:                                     ; preds = %assert_end42, %assert_end42, %assert_end42, %assert_end42
  %52 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 2
  %53 = load i32, ptr %52, align 4
  %54 = icmp eq i32 %53, 2
  br i1 %54, label %assert_end48, label %assert_fail45, !prof !5

assert_fail45:                                    ; preds = %assert_end44
  %55 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %55(ptr nonnull @.str.4)
  br label %common.ret

assert_end48:                                     ; preds = %assert_end44
  %56 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 3, i32 0
  %57 = load i8, ptr %56, align 1
  %58 = icmp eq i8 %57, 2
  %59 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 3, i32 1
  %60 = load i8, ptr %59, align 1
  %61 = icmp eq i8 %60, 32
  %62 = and i1 %58, %61
  %63 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 3, i32 2
  %64 = load i16, ptr %63, align 2
  %65 = icmp eq i16 %64, 1
  %66 = and i1 %62, %65
  br i1 %66, label %assert_end50, label %assert_fail49, !prof !5

assert_fail49:                                    ; preds = %assert_end48
  %67 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %67(ptr nonnull @.str.5)
  br label %common.ret

assert_end50:                                     ; preds = %assert_end48
  %68 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 6
  %69 = load i64, ptr %68, align 8
  %70 = icmp eq i64 %69, 0
  br i1 %70, label %assert_end52, label %assert_fail51, !prof !5

assert_fail51:                                    ; preds = %assert_end50
  %71 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %71(ptr nonnull @.str.6)
  br label %common.ret

assert_end52:                                     ; preds = %assert_end50
  %72 = getelementptr inbounds %1, ptr %arg.A, i64 0, i32 1, i32 0
  %73 = load i32, ptr %72, align 4
  %74 = icmp eq i32 %73, 1
  br i1 %74, label %assert_end54, label %assert_fail53, !prof !5

assert_fail53:                                    ; preds = %assert_end52
  %75 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %75(ptr nonnull @.str.7)
  br label %common.ret

assert_end54:                                     ; preds = %assert_end52
  %76 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 2
  %77 = load i32, ptr %76, align 4
  %78 = icmp eq i32 %77, 2
  br i1 %78, label %assert_end58, label %assert_fail55, !prof !5

assert_fail55:                                    ; preds = %assert_end54
  %79 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %79(ptr nonnull @.str.8)
  br label %common.ret

assert_end58:                                     ; preds = %assert_end54
  %80 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 3, i32 0
  %81 = load i8, ptr %80, align 1
  %82 = icmp eq i8 %81, 2
  %83 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 3, i32 1
  %84 = load i8, ptr %83, align 1
  %85 = icmp eq i8 %84, 32
  %86 = and i1 %82, %85
  %87 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 3, i32 2
  %88 = load i16, ptr %87, align 2
  %89 = icmp eq i16 %88, 1
  %90 = and i1 %86, %89
  br i1 %90, label %assert_end60, label %assert_fail59, !prof !5

assert_fail59:                                    ; preds = %assert_end58
  %91 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %91(ptr nonnull @.str.9)
  br label %common.ret

assert_end60:                                     ; preds = %assert_end58
  %92 = load i64, ptr %arg.B.shape, align 8, !tbaa !83
  %93 = trunc i64 %92 to i32
  %94 = icmp eq i32 %m, %93
  br i1 %94, label %assert_end62, label %assert_fail61, !prof !5

assert_fail61:                                    ; preds = %assert_end60
  %95 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %95(ptr nonnull @.str.10)
  br label %common.ret

assert_end62:                                     ; preds = %assert_end60
  %96 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 6
  %97 = load i64, ptr %96, align 8
  %98 = icmp eq i64 %97, 0
  br i1 %98, label %assert_end64, label %assert_fail63, !prof !5

assert_fail63:                                    ; preds = %assert_end62
  %99 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %99(ptr nonnull @.str.11)
  br label %common.ret

assert_end64:                                     ; preds = %assert_end62
  %100 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 1, i32 0
  %101 = load i32, ptr %100, align 4
  %102 = icmp eq i32 %101, 1
  br i1 %102, label %assert_end66, label %assert_fail65, !prof !5

assert_fail65:                                    ; preds = %assert_end64
  %103 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %103(ptr nonnull @.str.12)
  br label %common.ret

assert_end66:                                     ; preds = %assert_end64
  %104 = getelementptr inbounds %1, ptr %arg.B, i64 0, i32 1, i32 1
  %105 = load i32, ptr %104, align 4
  %106 = icmp eq i32 %dev_id, %105
  br i1 %106, label %assert_end68, label %assert_fail67, !prof !5

assert_fail67:                                    ; preds = %assert_end66
  %107 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %107(ptr nonnull @.str.13)
  br label %common.ret

assert_end68:                                     ; preds = %assert_end66
  %108 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 2
  %109 = load i32, ptr %108, align 4
  %110 = icmp eq i32 %109, 2
  br i1 %110, label %assert_end72, label %assert_fail69, !prof !5

assert_fail69:                                    ; preds = %assert_end68
  %111 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %111(ptr nonnull @.str.14)
  br label %common.ret

assert_end72:                                     ; preds = %assert_end68
  %112 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 3, i32 0
  %113 = load i8, ptr %112, align 1
  %114 = icmp eq i8 %113, 2
  %115 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 3, i32 1
  %116 = load i8, ptr %115, align 1
  %117 = icmp eq i8 %116, 32
  %118 = and i1 %114, %117
  %119 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 3, i32 2
  %120 = load i16, ptr %119, align 2
  %121 = icmp eq i16 %120, 1
  %122 = and i1 %118, %121
  br i1 %122, label %assert_end74, label %assert_fail73, !prof !5

assert_fail73:                                    ; preds = %assert_end72
  %123 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %123(ptr nonnull @.str.15)
  br label %common.ret

assert_end74:                                     ; preds = %assert_end72
  %124 = load i64, ptr %arg.C.shape110123, align 8, !tbaa !85
  %125 = trunc i64 %124 to i32
  %126 = icmp eq i32 %n, %125
  br i1 %126, label %assert_end76, label %assert_fail75, !prof !5

assert_fail75:                                    ; preds = %assert_end74
  %127 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %127(ptr nonnull @.str.16)
  br label %common.ret

assert_end76:                                     ; preds = %assert_end74
  %128 = getelementptr inbounds i64, ptr %arg.C.shape110123, i64 1
  %129 = load i64, ptr %128, align 8, !tbaa !95
  %130 = trunc i64 %129 to i32
  %131 = icmp eq i32 %h, %130
  br i1 %131, label %assert_end78, label %assert_fail77, !prof !5

assert_fail77:                                    ; preds = %assert_end76
  %132 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %132(ptr nonnull @.str.17)
  br label %common.ret

assert_end78:                                     ; preds = %assert_end76
  %133 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 6
  %134 = load i64, ptr %133, align 8
  %135 = icmp eq i64 %134, 0
  br i1 %135, label %assert_end80, label %assert_fail79, !prof !5

assert_fail79:                                    ; preds = %assert_end78
  %136 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %136(ptr nonnull @.str.18)
  br label %common.ret

assert_end80:                                     ; preds = %assert_end78
  %137 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 1, i32 0
  %138 = load i32, ptr %137, align 4
  %139 = icmp eq i32 %138, 1
  br i1 %139, label %assert_end82, label %assert_fail81, !prof !5

assert_fail81:                                    ; preds = %assert_end80
  %140 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %140(ptr nonnull @.str.19)
  br label %common.ret

assert_end82:                                     ; preds = %assert_end80
  %141 = getelementptr inbounds %1, ptr %arg.C, i64 0, i32 1, i32 1
  %142 = load i32, ptr %141, align 4
  %143 = icmp eq i32 %dev_id, %142
  br i1 %143, label %assert_end84, label %assert_fail83, !prof !5

assert_fail83:                                    ; preds = %assert_end82
  %144 = load ptr, ptr @__TVMAPISetLastError, align 8, !tbaa !6
  tail call void %144(ptr nonnull @.str.20)
  br label %common.ret

assert_end84:                                     ; preds = %assert_end82
  tail call fastcc void @matmult_compute_(i32 %n, i32 %h, ptr %C108125, i32 %stride85, i32 %stride86131, i32 %m, ptr %A, i32 %stride87, i32 %stride92, ptr %B, i32 %stride88106127, i32 %stride8996104129)
  br label %common.ret
}

; Function Attrs: inaccessiblememonly mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.assume(i1 noundef) #1

; Function Attrs: argmemonly nofree noinline nosync nounwind
define internal fastcc void @matmult_compute_(i32 %0, i32 %1, ptr noalias nocapture align 128 %2, i32 %3, i32 %4, i32 %5, ptr noalias nocapture readonly align 128 %6, i32 %7, i32 %8, ptr noalias nocapture readonly align 128 %9, i32 %10, i32 %11) unnamed_addr #2 {
entry:
  %12 = icmp sgt i32 %0, 0
  %13 = icmp sgt i32 %1, 0
  %or.cond = select i1 %12, i1 %13, i1 false
  br i1 %or.cond, label %for_begin_x.preheader.lr.ph.split.us, label %for_end_y, !prof !97

for_begin_x.preheader.lr.ph.split.us:             ; preds = %entry
  %14 = icmp sgt i32 %5, 0
  br i1 %14, label %for_begin_x.preheader.us.us.preheader, label %for_begin_x.preheader.us.preheader, !prof !5

for_begin_x.preheader.us.preheader:               ; preds = %for_begin_x.preheader.lr.ph.split.us
  %15 = sext i32 %4 to i64
  %16 = sext i32 %3 to i64
  %wide.trip.count30 = zext i32 %0 to i64
  %wide.trip.count25 = zext i32 %1 to i64
  %n.vec = and i64 %wide.trip.count25, 4294967294
  %17 = shl nsw i64 %16, 2
  %18 = shl nsw i64 %15, 3
  %19 = shl i64 %15, 2
  %20 = shl nsw i64 %15, 2
  br label %for_begin_x.preheader.us

for_begin_x.preheader.us.us.preheader:            ; preds = %for_begin_x.preheader.lr.ph.split.us
  %21 = sext i32 %8 to i64
  %22 = sext i32 %10 to i64
  %23 = sext i32 %4 to i64
  %24 = sext i32 %11 to i64
  %25 = sext i32 %3 to i64
  %26 = sext i32 %7 to i64
  %wide.trip.count20 = zext i32 %0 to i64
  %wide.trip.count15 = zext i32 %1 to i64
  %wide.trip.count = zext i32 %5 to i64
  %min.iters.check38 = icmp ult i32 %5, 8
  %ident.check = icmp ne i32 %8, 1
  %ident.check35 = icmp ne i32 %10, 1
  %27 = or i1 %ident.check, %ident.check35
  %n.vec41 = and i64 %wide.trip.count, 4294967288
  %brmerge = select i1 %min.iters.check38, i1 true, i1 %27
  %uglygep = getelementptr i8, ptr %6, i64 16
  %28 = shl nsw i64 %26, 2
  %29 = shl nsw i64 %21, 5
  %uglygep62 = getelementptr i8, ptr %9, i64 16
  %30 = shl nsw i64 %24, 2
  %31 = shl nsw i64 %22, 5
  %32 = shl nsw i64 %22, 2
  %33 = shl nsw i64 %21, 2
  br label %for_begin_x.preheader.us.us

for_begin_x.preheader.us.us:                      ; preds = %for_begin_x.preheader.us.us.preheader, %for_begin_x.for_end_x_crit_edge.split.us.us.us
  %lsr.iv74 = phi i64 [ 0, %for_begin_x.preheader.us.us.preheader ], [ %lsr.iv.next75, %for_begin_x.for_end_x_crit_edge.split.us.us.us ]
  %lsr.iv = phi ptr [ %uglygep, %for_begin_x.preheader.us.us.preheader ], [ %uglygep58, %for_begin_x.for_end_x_crit_edge.split.us.us.us ]
  %indvars.iv17 = phi i64 [ 0, %for_begin_x.preheader.us.us.preheader ], [ %indvars.iv.next18, %for_begin_x.for_end_x_crit_edge.split.us.us.us ]
  %34 = mul nsw i64 %indvars.iv17, %25
  br label %for_body_x.us.us.us

for_body_x.us.us.us:                              ; preds = %for_begin_k.for_end_k_crit_edge.us.us.us, %for_begin_x.preheader.us.us
  %lsr.iv69 = phi i64 [ %lsr.iv.next70, %for_begin_k.for_end_k_crit_edge.us.us.us ], [ 0, %for_begin_x.preheader.us.us ]
  %lsr.iv63 = phi ptr [ %uglygep64, %for_begin_k.for_end_k_crit_edge.us.us.us ], [ %uglygep62, %for_begin_x.preheader.us.us ]
  %indvars.iv12 = phi i64 [ %indvars.iv.next13, %for_begin_k.for_end_k_crit_edge.us.us.us ], [ 0, %for_begin_x.preheader.us.us ]
  %35 = mul nsw i64 %indvars.iv12, %23
  %36 = add nsw i64 %35, %34
  br i1 %brmerge, label %for_body_k.us.us.us.preheader, label %vector.body44.preheader

vector.body44.preheader:                          ; preds = %for_body_x.us.us.us
  br label %vector.body44

vector.body44:                                    ; preds = %vector.body44.preheader, %vector.body44
  %lsr.iv68 = phi i64 [ %n.vec41, %vector.body44.preheader ], [ %lsr.iv.next, %vector.body44 ]
  %lsr.iv65 = phi ptr [ %lsr.iv63, %vector.body44.preheader ], [ %uglygep66, %vector.body44 ]
  %lsr.iv59 = phi ptr [ %lsr.iv, %vector.body44.preheader ], [ %uglygep60, %vector.body44 ]
  %vec.phi = phi float [ %40, %vector.body44 ], [ 0.000000e+00, %vector.body44.preheader ]
  %uglygep61 = getelementptr i8, ptr %lsr.iv59, i64 -16
  %wide.load = load <4 x float>, ptr %uglygep61, align 4, !tbaa !98
  %wide.load46 = load <4 x float>, ptr %lsr.iv59, align 4, !tbaa !98
  %uglygep67 = getelementptr i8, ptr %lsr.iv65, i64 -16
  %wide.load47 = load <4 x float>, ptr %uglygep67, align 4, !tbaa !100
  %wide.load48 = load <4 x float>, ptr %lsr.iv65, align 4, !tbaa !100
  %37 = fmul <4 x float> %wide.load, %wide.load47
  %38 = fmul <4 x float> %wide.load46, %wide.load48
  %39 = call float @llvm.vector.reduce.fadd.v4f32(float %vec.phi, <4 x float> %37)
  %40 = call float @llvm.vector.reduce.fadd.v4f32(float %39, <4 x float> %38)
  %uglygep60 = getelementptr i8, ptr %lsr.iv59, i64 %29
  %uglygep66 = getelementptr i8, ptr %lsr.iv65, i64 %31
  %lsr.iv.next = add nsw i64 %lsr.iv68, -8
  %41 = icmp eq i64 %lsr.iv.next, 0
  br i1 %41, label %middle.block36, label %vector.body44, !prof !102, !llvm.loop !103

middle.block36:                                   ; preds = %vector.body44
  %42 = icmp eq i64 %n.vec41, %wide.trip.count
  br i1 %42, label %for_begin_k.for_end_k_crit_edge.us.us.us, label %for_body_k.us.us.us.preheader

for_body_k.us.us.us.preheader:                    ; preds = %for_body_x.us.us.us, %middle.block36
  %indvars.iv.ph = phi i64 [ %n.vec41, %middle.block36 ], [ 0, %for_body_x.us.us.us ]
  %.ph = phi float [ %40, %middle.block36 ], [ 0.000000e+00, %for_body_x.us.us.us ]
  %43 = mul i64 %22, %indvars.iv.ph
  %44 = add nsw i64 %lsr.iv69, %43
  %45 = shl i64 %44, 2
  %uglygep71 = getelementptr i8, ptr %9, i64 %45
  %46 = mul i64 %21, %indvars.iv.ph
  %47 = add nsw i64 %lsr.iv74, %46
  %48 = shl i64 %47, 2
  %uglygep76 = getelementptr i8, ptr %6, i64 %48
  %49 = sub i64 %wide.trip.count, %indvars.iv.ph
  br label %for_body_k.us.us.us

for_body_k.us.us.us:                              ; preds = %for_body_k.us.us.us.preheader, %for_body_k.us.us.us
  %lsr.iv79 = phi i64 [ %49, %for_body_k.us.us.us.preheader ], [ %lsr.iv.next80, %for_body_k.us.us.us ]
  %lsr.iv77 = phi ptr [ %uglygep76, %for_body_k.us.us.us.preheader ], [ %uglygep78, %for_body_k.us.us.us ]
  %lsr.iv72 = phi ptr [ %uglygep71, %for_body_k.us.us.us.preheader ], [ %uglygep73, %for_body_k.us.us.us ]
  %50 = phi float [ %53, %for_body_k.us.us.us ], [ %.ph, %for_body_k.us.us.us.preheader ]
  %51 = load float, ptr %lsr.iv77, align 4, !tbaa !98
  %52 = load float, ptr %lsr.iv72, align 4, !tbaa !100
  %53 = tail call float @llvm.fmuladd.f32(float %51, float %52, float %50)
  %uglygep73 = getelementptr i8, ptr %lsr.iv72, i64 %32
  %uglygep78 = getelementptr i8, ptr %lsr.iv77, i64 %33
  %lsr.iv.next80 = add i64 %lsr.iv79, -1
  %exitcond.not = icmp eq i64 %lsr.iv.next80, 0
  br i1 %exitcond.not, label %for_begin_k.for_end_k_crit_edge.us.us.us, label %for_body_k.us.us.us, !prof !105, !llvm.loop !106

for_begin_k.for_end_k_crit_edge.us.us.us:         ; preds = %for_body_k.us.us.us, %middle.block36
  %.lcssa = phi float [ %40, %middle.block36 ], [ %53, %for_body_k.us.us.us ]
  %sunkaddr = mul i64 %36, 4
  %sunkaddr93 = getelementptr inbounds i8, ptr %2, i64 %sunkaddr
  store float %.lcssa, ptr %sunkaddr93, align 4, !tbaa !107
  %indvars.iv.next13 = add nuw nsw i64 %indvars.iv12, 1
  %uglygep64 = getelementptr i8, ptr %lsr.iv63, i64 %30
  %lsr.iv.next70 = add nsw i64 %lsr.iv69, %24
  %exitcond16.not = icmp eq i64 %indvars.iv.next13, %wide.trip.count15
  br i1 %exitcond16.not, label %for_begin_x.for_end_x_crit_edge.split.us.us.us, label %for_body_x.us.us.us, !prof !109

for_begin_x.for_end_x_crit_edge.split.us.us.us:   ; preds = %for_begin_k.for_end_k_crit_edge.us.us.us
  %indvars.iv.next18 = add nuw nsw i64 %indvars.iv17, 1
  %uglygep58 = getelementptr i8, ptr %lsr.iv, i64 %28
  %lsr.iv.next75 = add nsw i64 %lsr.iv74, %26
  %exitcond21.not = icmp eq i64 %indvars.iv.next18, %wide.trip.count20
  br i1 %exitcond21.not, label %for_end_y, label %for_begin_x.preheader.us.us, !prof !109

for_begin_x.preheader.us:                         ; preds = %for_begin_x.preheader.us.preheader, %for_begin_x.for_end_x_crit_edge.us
  %lsr.iv81 = phi ptr [ %2, %for_begin_x.preheader.us.preheader ], [ %uglygep82, %for_begin_x.for_end_x_crit_edge.us ]
  %indvars.iv27 = phi i64 [ 0, %for_begin_x.preheader.us.preheader ], [ %indvars.iv.next28, %for_begin_x.for_end_x_crit_edge.us ]
  %54 = icmp ult i32 %1, 2
  br i1 %54, label %for_body_x.us4.preheader, label %vector.body.preheader

vector.body.preheader:                            ; preds = %for_begin_x.preheader.us
  br label %vector.body

vector.body:                                      ; preds = %vector.body.preheader, %vector.body
  %lsr.iv86 = phi i64 [ %n.vec, %vector.body.preheader ], [ %lsr.iv.next87, %vector.body ]
  %lsr.iv83 = phi ptr [ %lsr.iv81, %vector.body.preheader ], [ %uglygep84, %vector.body ]
  store float 0.000000e+00, ptr %lsr.iv83, align 4, !tbaa !107
  %sunkaddr94 = mul i64 %15, 4
  %sunkaddr95 = getelementptr i8, ptr %lsr.iv83, i64 %sunkaddr94
  store float 0.000000e+00, ptr %sunkaddr95, align 4, !tbaa !107
  %uglygep84 = getelementptr i8, ptr %lsr.iv83, i64 %18
  %lsr.iv.next87 = add nsw i64 %lsr.iv86, -2
  %55 = icmp eq i64 %lsr.iv.next87, 0
  br i1 %55, label %middle.block, label %vector.body, !prof !110, !llvm.loop !111

middle.block:                                     ; preds = %vector.body
  %56 = icmp eq i64 %n.vec, %wide.trip.count25
  br i1 %56, label %for_begin_x.for_end_x_crit_edge.us, label %for_body_x.us4.preheader

for_body_x.us4.preheader:                         ; preds = %for_begin_x.preheader.us, %middle.block
  %indvars.iv22.ph = phi i64 [ %n.vec, %middle.block ], [ 0, %for_begin_x.preheader.us ]
  %57 = mul i64 %19, %indvars.iv22.ph
  %58 = sub i64 %wide.trip.count25, %indvars.iv22.ph
  br label %for_body_x.us4

for_body_x.us4:                                   ; preds = %for_body_x.us4.preheader, %for_body_x.us4
  %lsr.iv91 = phi i64 [ %58, %for_body_x.us4.preheader ], [ %lsr.iv.next92, %for_body_x.us4 ]
  %lsr.iv88 = phi i64 [ %57, %for_body_x.us4.preheader ], [ %lsr.iv.next89, %for_body_x.us4 ]
  %uglygep90 = getelementptr i8, ptr %lsr.iv81, i64 %lsr.iv88
  store float 0.000000e+00, ptr %uglygep90, align 4, !tbaa !107
  %lsr.iv.next89 = add i64 %lsr.iv88, %20
  %lsr.iv.next92 = add i64 %lsr.iv91, -1
  %exitcond26.not = icmp eq i64 %lsr.iv.next92, 0
  br i1 %exitcond26.not, label %for_begin_x.for_end_x_crit_edge.us, label %for_body_x.us4, !prof !105, !llvm.loop !112

for_begin_x.for_end_x_crit_edge.us:               ; preds = %for_body_x.us4, %middle.block
  %indvars.iv.next28 = add nuw nsw i64 %indvars.iv27, 1
  %uglygep82 = getelementptr i8, ptr %lsr.iv81, i64 %17
  %exitcond31.not = icmp eq i64 %indvars.iv.next28, %wide.trip.count30
  br i1 %exitcond31.not, label %for_end_y, label %for_begin_x.preheader.us, !prof !109

for_end_y:                                        ; preds = %for_begin_x.for_end_x_crit_edge.us, %for_begin_x.for_end_x_crit_edge.split.us.us.us, %entry
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind readnone speculatable willreturn
declare float @llvm.fmuladd.f32(float, float, float) #3

; Function Attrs: nocallback nofree nosync nounwind readnone willreturn
declare float @llvm.vector.reduce.fadd.v4f32(float, <4 x float>) #4

attributes #0 = { "target-cpu"="apple-m1" }
attributes #1 = { inaccessiblememonly mustprogress nocallback nofree nosync nounwind willreturn }
attributes #2 = { argmemonly nofree noinline nosync nounwind "target-cpu"="apple-m1" }
attributes #3 = { mustprogress nocallback nofree nosync nounwind readnone speculatable willreturn }
attributes #4 = { nocallback nofree nosync nounwind readnone willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "TVM", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, dwoId: 1)
!1 = !DIFile(filename: "model.tvm", directory: "/tmp/")
!2 = !{i32 2, !"tvm_target", !"llvm -mcpu=apple-m1"}
!3 = !{i32 4, !"Debug Info Version", i32 3}
!4 = !{i32 4, !"Dwarf Version", i32 2}
!5 = !{!"branch_weights", i32 1048576, i32 1}
!6 = !{!7, !7, i64 0}
!7 = !{!"ctx_ptr", !8, i64 0}
!8 = !{!"tvm-tbaa"}
!9 = !{!10, !10, i64 0}
!10 = !{!"0x6000017c2be0.w4.b0", !11, i64 0}
!11 = !{!"0x6000017c2be0.w8.b0", !12, i64 0}
!12 = !{!"0x6000017c2be0.w16.b0", !13, i64 0}
!13 = !{!"0x6000017c2be0.w32.b0", !14, i64 0}
!14 = !{!"0x6000017c2be0.w64.b0", !15, i64 0}
!15 = !{!"0x6000017c2be0.w128.b0", !16, i64 0}
!16 = !{!"0x6000017c2be0.w256.b0", !17, i64 0}
!17 = !{!"0x6000017c2be0.w512.b0", !18, i64 0}
!18 = !{!"0x6000017c2be0.w1024.b0", !19, i64 0}
!19 = !{!"0x6000017c2be0", !8, i64 0}
!20 = !{!21, !21, i64 0}
!21 = !{!"0x6000017c2be0.w4.b4", !11, i64 0}
!22 = !{!23, !23, i64 0}
!23 = !{!"0x6000017c2be0.w4.b8", !24, i64 0}
!24 = !{!"0x6000017c2be0.w8.b8", !12, i64 0}
!25 = !{!26, !26, i64 0}
!26 = !{!"0x6000017c4210.w8.b0", !27, i64 0}
!27 = !{!"0x6000017c4210.w16.b0", !28, i64 0}
!28 = !{!"0x6000017c4210.w32.b0", !29, i64 0}
!29 = !{!"0x6000017c4210.w64.b0", !30, i64 0}
!30 = !{!"0x6000017c4210.w128.b0", !31, i64 0}
!31 = !{!"0x6000017c4210.w256.b0", !32, i64 0}
!32 = !{!"0x6000017c4210.w512.b0", !33, i64 0}
!33 = !{!"0x6000017c4210.w1024.b0", !34, i64 0}
!34 = !{!"0x6000017c4210", !8, i64 0}
!35 = !{!36, !36, i64 0}
!36 = !{!"0x6000017c4210.w8.b8", !27, i64 0}
!37 = !{!38, !38, i64 0}
!38 = !{!"0x6000017c4600.w8.b8", !39, i64 0}
!39 = !{!"0x6000017c4600.w16.b0", !40, i64 0}
!40 = !{!"0x6000017c4600.w32.b0", !41, i64 0}
!41 = !{!"0x6000017c4600.w64.b0", !42, i64 0}
!42 = !{!"0x6000017c4600.w128.b0", !43, i64 0}
!43 = !{!"0x6000017c4600.w256.b0", !44, i64 0}
!44 = !{!"0x6000017c4600.w512.b0", !45, i64 0}
!45 = !{!"0x6000017c4600.w1024.b0", !46, i64 0}
!46 = !{!"0x6000017c4600", !8, i64 0}
!47 = !{!48, !48, i64 0}
!48 = !{!"0x6000017c56e0.w8.b8", !49, i64 0}
!49 = !{!"0x6000017c56e0.w16.b0", !50, i64 0}
!50 = !{!"0x6000017c56e0.w32.b0", !51, i64 0}
!51 = !{!"0x6000017c56e0.w64.b0", !52, i64 0}
!52 = !{!"0x6000017c56e0.w128.b0", !53, i64 0}
!53 = !{!"0x6000017c56e0.w256.b0", !54, i64 0}
!54 = !{!"0x6000017c56e0.w512.b0", !55, i64 0}
!55 = !{!"0x6000017c56e0.w1024.b0", !56, i64 0}
!56 = !{!"0x6000017c56e0", !8, i64 0}
!57 = !{!58, !58, i64 0}
!58 = !{!"0x6000017c4600.w8.b0", !39, i64 0}
!59 = !{!60, !60, i64 0}
!60 = !{!"0x6000017c5b30.w8.b8", !61, i64 0}
!61 = !{!"0x6000017c5b30.w16.b0", !62, i64 0}
!62 = !{!"0x6000017c5b30.w32.b0", !63, i64 0}
!63 = !{!"0x6000017c5b30.w64.b0", !64, i64 0}
!64 = !{!"0x6000017c5b30.w128.b0", !65, i64 0}
!65 = !{!"0x6000017c5b30.w256.b0", !66, i64 0}
!66 = !{!"0x6000017c5b30.w512.b0", !67, i64 0}
!67 = !{!"0x6000017c5b30.w1024.b0", !68, i64 0}
!68 = !{!"0x6000017c5b30", !8, i64 0}
!69 = !{!70, !70, i64 0}
!70 = !{!"0x6000017c5b30.w8.b0", !61, i64 0}
!71 = !{!72, !72, i64 0}
!72 = !{!"0x6000017cd0e0.w8.b8", !73, i64 0}
!73 = !{!"0x6000017cd0e0.w16.b0", !74, i64 0}
!74 = !{!"0x6000017cd0e0.w32.b0", !75, i64 0}
!75 = !{!"0x6000017cd0e0.w64.b0", !76, i64 0}
!76 = !{!"0x6000017cd0e0.w128.b0", !77, i64 0}
!77 = !{!"0x6000017cd0e0.w256.b0", !78, i64 0}
!78 = !{!"0x6000017cd0e0.w512.b0", !79, i64 0}
!79 = !{!"0x6000017cd0e0.w1024.b0", !80, i64 0}
!80 = !{!"0x6000017cd0e0", !8, i64 0}
!81 = !{!82, !82, i64 0}
!82 = !{!"0x6000017cd0e0.w8.b0", !73, i64 0}
!83 = !{!84, !84, i64 0}
!84 = !{!"0x6000017c56e0.w8.b0", !49, i64 0}
!85 = !{!86, !86, i64 0}
!86 = !{!"0x6000017ccc30.w8.b0", !87, i64 0}
!87 = !{!"0x6000017ccc30.w16.b0", !88, i64 0}
!88 = !{!"0x6000017ccc30.w32.b0", !89, i64 0}
!89 = !{!"0x6000017ccc30.w64.b0", !90, i64 0}
!90 = !{!"0x6000017ccc30.w128.b0", !91, i64 0}
!91 = !{!"0x6000017ccc30.w256.b0", !92, i64 0}
!92 = !{!"0x6000017ccc30.w512.b0", !93, i64 0}
!93 = !{!"0x6000017ccc30.w1024.b0", !94, i64 0}
!94 = !{!"0x6000017ccc30", !8, i64 0}
!95 = !{!96, !96, i64 0}
!96 = !{!"0x6000017ccc30.w8.b8", !87, i64 0}
!97 = !{!"branch_weights", i32 -2147483648, i32 4096}
!98 = !{!99, !99, i64 0}
!99 = !{!"0x6000017c1aa0", !8, i64 0}
!100 = !{!101, !101, i64 0}
!101 = !{!"0x6000017c1c80", !8, i64 0}
!102 = !{!"branch_weights", i32 1, i32 131071}
!103 = distinct !{!103, !104}
!104 = !{!"llvm.loop.isvectorized", i32 1}
!105 = !{!"branch_weights", i32 1, i32 0}
!106 = distinct !{!106, !104}
!107 = !{!108, !108, i64 0}
!108 = !{!"0x6000017c1d70", !8, i64 0}
!109 = !{!"branch_weights", i32 1, i32 1048576}
!110 = !{!"branch_weights", i32 1, i32 524287}
!111 = distinct !{!111, !104}
!112 = distinct !{!112, !104}
