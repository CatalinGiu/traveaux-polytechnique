/*
-- File : flx.h
--
-- Contents : Processor header-file for the DLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/




#ifndef _flx_h
#define _flx_h

namespace flx_primitive {
    
 // declaration of primitive data types 

    // main data types
    class w08     property( 8 bit signed);
    class w16     property(16 bit signed);
    class w32     property(32 bit signed);

    class addr    property(32 bit unsigned);
    class iword   property(32 bit unsigned);

    // types for immediates
    class uint1   property( 1 bit unsigned);
    class uint4   property( 4 bit unsigned);
    class uint5   property( 5 bit unsigned);
    class uint16  property(16 bit unsigned);

    class int5    property( 5 bit signed);
    class int16   property(16 bit signed);
    class int16p  property(16 bit signed /*padded*/);
    class int26   property(26 bit signed);

    class uint2   property( 2 bit unsigned);
    class uint10  property(10 bit unsigned);

 // integer primitives 

    w32 add(w32,w32,uint1&)              property(commutative);
    w32 add(w32,w32)                     property(commutative);
    w32 sub(w32,w32,uint1&); 

    w32 addx(w32,w32,uint1,uint1&)       property(commutative);
    w32 subx(w32,w32,uint1,uint1&);

    w32 band(w32,w32)                    property(commutative);
    w32 bor (w32,w32)                    property(commutative);
    w32 bxor(w32,w32)                    property(commutative);
    w32 xtd (w32,w32);

    w32 mul(w32,w32)                     property(commutative);

    void lmulss(w32,w32,w32& l, w32& h)  property(commutative);
    void lmulsu(w32,w32,w32& l, w32& h);
    void lmuluu(w32,w32,w32& l, w32& h)  property(commutative);

    w32 sll(w32,w32);
    w32 srl(w32,w32);
    w32 sra(w32,w32);
    w32 clb(w32);

    w32 sge (w32,w32);
    w32 sgt (w32,w32);
    w32 sle (w32,w32);
    w32 slt (w32,w32);
    w32 sgeu(w32,w32);
    w32 sgtu(w32,w32);
    w32 sleu(w32,w32);
    w32 sltu(w32,w32);
    w32 seq (w32,w32)  property(commutative);
    w32 sne (w32,w32)  property(commutative);

    w32 lhi(int16p) property(right_padding_16 promotion_conversion_alternate);

    w32 extend_sign(w08)  property(promotion_conversion_alternate); 
    w32 extend_zero(w08)  property(promotion_conversion_alternate);
    w32 extend_sign(w16)  property(promotion_conversion_alternate); 
    w32 extend_zero(w16)  property(promotion_conversion_alternate);
    w08 extract_w08(w32)  property(promotion_conversion_alternate); 
    w16 extract_w16(w32)  property(promotion_conversion_alternate);  

 // custom instruction
    w32 ma(w32, w32);
    


 // iterative division primitive

    void divide(w32 a, w32 b, w32& l, w32& h) property(multicycle_32);
    // void divide27(w32 a, w32 b, w32& l, w32& h) property(multicycle_27);
    void fdivide(w32 a, w32 b, w32& l) property(multicycle_29);
    void fsqrt(w32 a, w32& l) property(multicycle_26);

 // floating point primitives

    w32 faddsub(uint1 op, w32,w32); // op=0: add; op=1: sub
    w32 fmul(w32,w32);

    /*
    void fdiv_pre(w32 opa, w32 opb, w32& dvdnd, w32& dvsor, w32& other);
    void fdiv_step(w32,w32,w32&,w32&,w32);
    w32  fdiv_post(w32 qutnt, w32 rmndr, w32 other);

    void fsqrt_pre(w32 opa, w32& remainder, w32& other);
    void fsqrt_step(w32 s_in,w32 q_in,w32& s_out,w32& q_out);
    w32  fsqrt_post(w32 q_in, w32 other);
*/
    w32 sfle(w32,w32);
    w32 sflt(w32,w32);
    w32 sfeq(w32,w32);

    w32 i2f(w32); // int to float
    w32 f2i(w32); // float to int
    w32 frnd(w32); // roundf

    w32 fadd(w32,w32) property(programmers_view);
    w32 fsub(w32,w32) property(programmers_view);
 
 
 
 
 // control primitives 

    bool eqz(w32);
    bool nez(w32) property(copy_jump);
    w32 seq0(w32) property(chess_view);
    w32 sne0(w32) property(chess_view);
      
    void br(bool,int16)   property(relative jump);
    void j(int26)         property(relative jump);
    void jr(w32)	  property(absolute jump ret);
    void nop()            property(nop);

#if defined(__programmers_view__)
    w32 jal(int26)        property(relative call);
    w32 jalr(w32)         property(absolute call);
#else
    void jal(int26)       property(relative call);
    void jalr(w32)        property(absolute call);
    w32 pcadd(w32,w32);
#endif

    void  hwdo(w32,int16)  property(relative doloop);
    #if !defined(__programmers_view__)
    uint2 incr(uint2);     // increment doloop level
    #endif

    w32 sign_extend_08(w32)  property(chess_view); 
    w32 zero_extend_08(w32)  property(chess_view);
    w32 sign_extend_16(w32)  property(chess_view);
    w32 zero_extend_16(w32)  property(chess_view); 

#if defined(__go__)
    addr incr1(addr); // OCD addr + 1 
    addr incr4(addr); // OCD addr + 4
#endif

 // definition of primitive data types 

    class w32 {
        w32(int16);          // for immediates
        w32(uint16);         // for immediates
        w32(int5);   
        w32(uint10);
        w32(int);            // for hw loop count
    };

    class addr {
        addr(w32);
    };
 
}

#endif // _flx_h
