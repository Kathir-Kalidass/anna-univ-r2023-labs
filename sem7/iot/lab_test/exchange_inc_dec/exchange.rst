                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.6.0 #16555 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module exchange
                                      6 	
                                      7 	.optsdcc -mmcs51 --model-small
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _CY
                                     13 	.globl _AC
                                     14 	.globl _F0
                                     15 	.globl _RS1
                                     16 	.globl _RS0
                                     17 	.globl _OV
                                     18 	.globl _F1
                                     19 	.globl _P
                                     20 	.globl _PS
                                     21 	.globl _PT1
                                     22 	.globl _PX1
                                     23 	.globl _PT0
                                     24 	.globl _PX0
                                     25 	.globl _RD
                                     26 	.globl _WR
                                     27 	.globl _T1
                                     28 	.globl _T0
                                     29 	.globl _INT1
                                     30 	.globl _INT0
                                     31 	.globl _TXD
                                     32 	.globl _RXD
                                     33 	.globl _P3_7
                                     34 	.globl _P3_6
                                     35 	.globl _P3_5
                                     36 	.globl _P3_4
                                     37 	.globl _P3_3
                                     38 	.globl _P3_2
                                     39 	.globl _P3_1
                                     40 	.globl _P3_0
                                     41 	.globl _EA
                                     42 	.globl _ES
                                     43 	.globl _ET1
                                     44 	.globl _EX1
                                     45 	.globl _ET0
                                     46 	.globl _EX0
                                     47 	.globl _P2_7
                                     48 	.globl _P2_6
                                     49 	.globl _P2_5
                                     50 	.globl _P2_4
                                     51 	.globl _P2_3
                                     52 	.globl _P2_2
                                     53 	.globl _P2_1
                                     54 	.globl _P2_0
                                     55 	.globl _SM0
                                     56 	.globl _SM1
                                     57 	.globl _SM2
                                     58 	.globl _REN
                                     59 	.globl _TB8
                                     60 	.globl _RB8
                                     61 	.globl _TI
                                     62 	.globl _RI
                                     63 	.globl _P1_7
                                     64 	.globl _P1_6
                                     65 	.globl _P1_5
                                     66 	.globl _P1_4
                                     67 	.globl _P1_3
                                     68 	.globl _P1_2
                                     69 	.globl _P1_1
                                     70 	.globl _P1_0
                                     71 	.globl _TF1
                                     72 	.globl _TR1
                                     73 	.globl _TF0
                                     74 	.globl _TR0
                                     75 	.globl _IE1
                                     76 	.globl _IT1
                                     77 	.globl _IE0
                                     78 	.globl _IT0
                                     79 	.globl _P0_7
                                     80 	.globl _P0_6
                                     81 	.globl _P0_5
                                     82 	.globl _P0_4
                                     83 	.globl _P0_3
                                     84 	.globl _P0_2
                                     85 	.globl _P0_1
                                     86 	.globl _P0_0
                                     87 	.globl _B
                                     88 	.globl _ACC
                                     89 	.globl _PSW
                                     90 	.globl _IP
                                     91 	.globl _P3
                                     92 	.globl _IE
                                     93 	.globl _P2
                                     94 	.globl _SBUF
                                     95 	.globl _SCON
                                     96 	.globl _P1
                                     97 	.globl _TH1
                                     98 	.globl _TH0
                                     99 	.globl _TL1
                                    100 	.globl _TL0
                                    101 	.globl _TMOD
                                    102 	.globl _TCON
                                    103 	.globl _PCON
                                    104 	.globl _DPH
                                    105 	.globl _DPL
                                    106 	.globl _SP
                                    107 	.globl _P0
                                    108 	.globl _temp
                                    109 	.globl _b
                                    110 	.globl _a
                                    111 ;--------------------------------------------------------
                                    112 ; special function registers
                                    113 ;--------------------------------------------------------
                                    114 	.area RSEG    (ABS,DATA)
      000000                        115 	.org 0x0000
                           000080   116 G$P0$0_0$0 == 0x0080
                           000080   117 _P0	=	0x0080
                           000081   118 G$SP$0_0$0 == 0x0081
                           000081   119 _SP	=	0x0081
                           000082   120 G$DPL$0_0$0 == 0x0082
                           000082   121 _DPL	=	0x0082
                           000083   122 G$DPH$0_0$0 == 0x0083
                           000083   123 _DPH	=	0x0083
                           000087   124 G$PCON$0_0$0 == 0x0087
                           000087   125 _PCON	=	0x0087
                           000088   126 G$TCON$0_0$0 == 0x0088
                           000088   127 _TCON	=	0x0088
                           000089   128 G$TMOD$0_0$0 == 0x0089
                           000089   129 _TMOD	=	0x0089
                           00008A   130 G$TL0$0_0$0 == 0x008a
                           00008A   131 _TL0	=	0x008a
                           00008B   132 G$TL1$0_0$0 == 0x008b
                           00008B   133 _TL1	=	0x008b
                           00008C   134 G$TH0$0_0$0 == 0x008c
                           00008C   135 _TH0	=	0x008c
                           00008D   136 G$TH1$0_0$0 == 0x008d
                           00008D   137 _TH1	=	0x008d
                           000090   138 G$P1$0_0$0 == 0x0090
                           000090   139 _P1	=	0x0090
                           000098   140 G$SCON$0_0$0 == 0x0098
                           000098   141 _SCON	=	0x0098
                           000099   142 G$SBUF$0_0$0 == 0x0099
                           000099   143 _SBUF	=	0x0099
                           0000A0   144 G$P2$0_0$0 == 0x00a0
                           0000A0   145 _P2	=	0x00a0
                           0000A8   146 G$IE$0_0$0 == 0x00a8
                           0000A8   147 _IE	=	0x00a8
                           0000B0   148 G$P3$0_0$0 == 0x00b0
                           0000B0   149 _P3	=	0x00b0
                           0000B8   150 G$IP$0_0$0 == 0x00b8
                           0000B8   151 _IP	=	0x00b8
                           0000D0   152 G$PSW$0_0$0 == 0x00d0
                           0000D0   153 _PSW	=	0x00d0
                           0000E0   154 G$ACC$0_0$0 == 0x00e0
                           0000E0   155 _ACC	=	0x00e0
                           0000F0   156 G$B$0_0$0 == 0x00f0
                           0000F0   157 _B	=	0x00f0
                                    158 ;--------------------------------------------------------
                                    159 ; special function bits
                                    160 ;--------------------------------------------------------
                                    161 	.area RSEG    (ABS,DATA)
      000000                        162 	.org 0x0000
                           000080   163 G$P0_0$0_0$0 == 0x0080
                           000080   164 _P0_0	=	0x0080
                           000081   165 G$P0_1$0_0$0 == 0x0081
                           000081   166 _P0_1	=	0x0081
                           000082   167 G$P0_2$0_0$0 == 0x0082
                           000082   168 _P0_2	=	0x0082
                           000083   169 G$P0_3$0_0$0 == 0x0083
                           000083   170 _P0_3	=	0x0083
                           000084   171 G$P0_4$0_0$0 == 0x0084
                           000084   172 _P0_4	=	0x0084
                           000085   173 G$P0_5$0_0$0 == 0x0085
                           000085   174 _P0_5	=	0x0085
                           000086   175 G$P0_6$0_0$0 == 0x0086
                           000086   176 _P0_6	=	0x0086
                           000087   177 G$P0_7$0_0$0 == 0x0087
                           000087   178 _P0_7	=	0x0087
                           000088   179 G$IT0$0_0$0 == 0x0088
                           000088   180 _IT0	=	0x0088
                           000089   181 G$IE0$0_0$0 == 0x0089
                           000089   182 _IE0	=	0x0089
                           00008A   183 G$IT1$0_0$0 == 0x008a
                           00008A   184 _IT1	=	0x008a
                           00008B   185 G$IE1$0_0$0 == 0x008b
                           00008B   186 _IE1	=	0x008b
                           00008C   187 G$TR0$0_0$0 == 0x008c
                           00008C   188 _TR0	=	0x008c
                           00008D   189 G$TF0$0_0$0 == 0x008d
                           00008D   190 _TF0	=	0x008d
                           00008E   191 G$TR1$0_0$0 == 0x008e
                           00008E   192 _TR1	=	0x008e
                           00008F   193 G$TF1$0_0$0 == 0x008f
                           00008F   194 _TF1	=	0x008f
                           000090   195 G$P1_0$0_0$0 == 0x0090
                           000090   196 _P1_0	=	0x0090
                           000091   197 G$P1_1$0_0$0 == 0x0091
                           000091   198 _P1_1	=	0x0091
                           000092   199 G$P1_2$0_0$0 == 0x0092
                           000092   200 _P1_2	=	0x0092
                           000093   201 G$P1_3$0_0$0 == 0x0093
                           000093   202 _P1_3	=	0x0093
                           000094   203 G$P1_4$0_0$0 == 0x0094
                           000094   204 _P1_4	=	0x0094
                           000095   205 G$P1_5$0_0$0 == 0x0095
                           000095   206 _P1_5	=	0x0095
                           000096   207 G$P1_6$0_0$0 == 0x0096
                           000096   208 _P1_6	=	0x0096
                           000097   209 G$P1_7$0_0$0 == 0x0097
                           000097   210 _P1_7	=	0x0097
                           000098   211 G$RI$0_0$0 == 0x0098
                           000098   212 _RI	=	0x0098
                           000099   213 G$TI$0_0$0 == 0x0099
                           000099   214 _TI	=	0x0099
                           00009A   215 G$RB8$0_0$0 == 0x009a
                           00009A   216 _RB8	=	0x009a
                           00009B   217 G$TB8$0_0$0 == 0x009b
                           00009B   218 _TB8	=	0x009b
                           00009C   219 G$REN$0_0$0 == 0x009c
                           00009C   220 _REN	=	0x009c
                           00009D   221 G$SM2$0_0$0 == 0x009d
                           00009D   222 _SM2	=	0x009d
                           00009E   223 G$SM1$0_0$0 == 0x009e
                           00009E   224 _SM1	=	0x009e
                           00009F   225 G$SM0$0_0$0 == 0x009f
                           00009F   226 _SM0	=	0x009f
                           0000A0   227 G$P2_0$0_0$0 == 0x00a0
                           0000A0   228 _P2_0	=	0x00a0
                           0000A1   229 G$P2_1$0_0$0 == 0x00a1
                           0000A1   230 _P2_1	=	0x00a1
                           0000A2   231 G$P2_2$0_0$0 == 0x00a2
                           0000A2   232 _P2_2	=	0x00a2
                           0000A3   233 G$P2_3$0_0$0 == 0x00a3
                           0000A3   234 _P2_3	=	0x00a3
                           0000A4   235 G$P2_4$0_0$0 == 0x00a4
                           0000A4   236 _P2_4	=	0x00a4
                           0000A5   237 G$P2_5$0_0$0 == 0x00a5
                           0000A5   238 _P2_5	=	0x00a5
                           0000A6   239 G$P2_6$0_0$0 == 0x00a6
                           0000A6   240 _P2_6	=	0x00a6
                           0000A7   241 G$P2_7$0_0$0 == 0x00a7
                           0000A7   242 _P2_7	=	0x00a7
                           0000A8   243 G$EX0$0_0$0 == 0x00a8
                           0000A8   244 _EX0	=	0x00a8
                           0000A9   245 G$ET0$0_0$0 == 0x00a9
                           0000A9   246 _ET0	=	0x00a9
                           0000AA   247 G$EX1$0_0$0 == 0x00aa
                           0000AA   248 _EX1	=	0x00aa
                           0000AB   249 G$ET1$0_0$0 == 0x00ab
                           0000AB   250 _ET1	=	0x00ab
                           0000AC   251 G$ES$0_0$0 == 0x00ac
                           0000AC   252 _ES	=	0x00ac
                           0000AF   253 G$EA$0_0$0 == 0x00af
                           0000AF   254 _EA	=	0x00af
                           0000B0   255 G$P3_0$0_0$0 == 0x00b0
                           0000B0   256 _P3_0	=	0x00b0
                           0000B1   257 G$P3_1$0_0$0 == 0x00b1
                           0000B1   258 _P3_1	=	0x00b1
                           0000B2   259 G$P3_2$0_0$0 == 0x00b2
                           0000B2   260 _P3_2	=	0x00b2
                           0000B3   261 G$P3_3$0_0$0 == 0x00b3
                           0000B3   262 _P3_3	=	0x00b3
                           0000B4   263 G$P3_4$0_0$0 == 0x00b4
                           0000B4   264 _P3_4	=	0x00b4
                           0000B5   265 G$P3_5$0_0$0 == 0x00b5
                           0000B5   266 _P3_5	=	0x00b5
                           0000B6   267 G$P3_6$0_0$0 == 0x00b6
                           0000B6   268 _P3_6	=	0x00b6
                           0000B7   269 G$P3_7$0_0$0 == 0x00b7
                           0000B7   270 _P3_7	=	0x00b7
                           0000B0   271 G$RXD$0_0$0 == 0x00b0
                           0000B0   272 _RXD	=	0x00b0
                           0000B1   273 G$TXD$0_0$0 == 0x00b1
                           0000B1   274 _TXD	=	0x00b1
                           0000B2   275 G$INT0$0_0$0 == 0x00b2
                           0000B2   276 _INT0	=	0x00b2
                           0000B3   277 G$INT1$0_0$0 == 0x00b3
                           0000B3   278 _INT1	=	0x00b3
                           0000B4   279 G$T0$0_0$0 == 0x00b4
                           0000B4   280 _T0	=	0x00b4
                           0000B5   281 G$T1$0_0$0 == 0x00b5
                           0000B5   282 _T1	=	0x00b5
                           0000B6   283 G$WR$0_0$0 == 0x00b6
                           0000B6   284 _WR	=	0x00b6
                           0000B7   285 G$RD$0_0$0 == 0x00b7
                           0000B7   286 _RD	=	0x00b7
                           0000B8   287 G$PX0$0_0$0 == 0x00b8
                           0000B8   288 _PX0	=	0x00b8
                           0000B9   289 G$PT0$0_0$0 == 0x00b9
                           0000B9   290 _PT0	=	0x00b9
                           0000BA   291 G$PX1$0_0$0 == 0x00ba
                           0000BA   292 _PX1	=	0x00ba
                           0000BB   293 G$PT1$0_0$0 == 0x00bb
                           0000BB   294 _PT1	=	0x00bb
                           0000BC   295 G$PS$0_0$0 == 0x00bc
                           0000BC   296 _PS	=	0x00bc
                           0000D0   297 G$P$0_0$0 == 0x00d0
                           0000D0   298 _P	=	0x00d0
                           0000D1   299 G$F1$0_0$0 == 0x00d1
                           0000D1   300 _F1	=	0x00d1
                           0000D2   301 G$OV$0_0$0 == 0x00d2
                           0000D2   302 _OV	=	0x00d2
                           0000D3   303 G$RS0$0_0$0 == 0x00d3
                           0000D3   304 _RS0	=	0x00d3
                           0000D4   305 G$RS1$0_0$0 == 0x00d4
                           0000D4   306 _RS1	=	0x00d4
                           0000D5   307 G$F0$0_0$0 == 0x00d5
                           0000D5   308 _F0	=	0x00d5
                           0000D6   309 G$AC$0_0$0 == 0x00d6
                           0000D6   310 _AC	=	0x00d6
                           0000D7   311 G$CY$0_0$0 == 0x00d7
                           0000D7   312 _CY	=	0x00d7
                                    313 ;--------------------------------------------------------
                                    314 ; overlayable register banks
                                    315 ;--------------------------------------------------------
                                    316 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        317 	.ds 8
                                    318 ;--------------------------------------------------------
                                    319 ; internal ram data
                                    320 ;--------------------------------------------------------
                                    321 	.area DSEG    (DATA)
                           000030   322 G$a$0_0$0 == 0x0030
                           000030   323 _a	=	0x0030
                           000031   324 G$b$0_0$0 == 0x0031
                           000031   325 _b	=	0x0031
                           000032   326 G$temp$0_0$0 == 0x0032
                           000032   327 _temp	=	0x0032
                                    328 ;--------------------------------------------------------
                                    329 ; overlayable items in internal ram
                                    330 ;--------------------------------------------------------
                                    331 ;--------------------------------------------------------
                                    332 ; Stack segment in internal ram
                                    333 ;--------------------------------------------------------
                                    334 	.area SSEG
      000008                        335 __start__stack:
      000008                        336 	.ds	1
                                    337 
                                    338 ;--------------------------------------------------------
                                    339 ; indirectly addressable internal ram data
                                    340 ;--------------------------------------------------------
                                    341 	.area ISEG    (DATA)
                                    342 ;--------------------------------------------------------
                                    343 ; absolute internal ram data
                                    344 ;--------------------------------------------------------
                                    345 	.area IABS    (ABS,DATA)
                                    346 	.area IABS    (ABS,DATA)
                                    347 ;--------------------------------------------------------
                                    348 ; bit data
                                    349 ;--------------------------------------------------------
                                    350 	.area BSEG    (BIT)
                                    351 ;--------------------------------------------------------
                                    352 ; paged external ram data
                                    353 ;--------------------------------------------------------
                                    354 	.area PSEG    (PAG,XDATA)
                                    355 ;--------------------------------------------------------
                                    356 ; uninitialized external ram data
                                    357 ;--------------------------------------------------------
                                    358 	.area XSEG    (XDATA)
                                    359 ;--------------------------------------------------------
                                    360 ; absolute external ram data
                                    361 ;--------------------------------------------------------
                                    362 	.area XABS    (ABS,XDATA)
                                    363 ;--------------------------------------------------------
                                    364 ; initialized external ram data
                                    365 ;--------------------------------------------------------
                                    366 	.area XISEG   (XDATA)
                                    367 	.area HOME    (CODE)
                                    368 	.area GSINIT0 (CODE)
                                    369 	.area GSINIT1 (CODE)
                                    370 	.area GSINIT2 (CODE)
                                    371 	.area GSINIT3 (CODE)
                                    372 	.area GSINIT4 (CODE)
                                    373 	.area GSINIT5 (CODE)
                                    374 	.area GSINIT  (CODE)
                                    375 	.area GSFINAL (CODE)
                                    376 	.area CSEG    (CODE)
                                    377 ;--------------------------------------------------------
                                    378 ; interrupt vector
                                    379 ;--------------------------------------------------------
                                    380 	.area HOME    (CODE)
      000000                        381 __interrupt_vect:
      000000 02 00 4E         [24]  382 	ljmp	__sdcc_gsinit_startup
                                    383 ; restartable atomic support routines
      000003                        384 	.ds	5
      000008                        385 sdcc_atomic_exchange_rollback_start::
      000008 00               [12]  386 	nop
      000009 00               [12]  387 	nop
      00000A                        388 sdcc_atomic_exchange_pdata_impl:
      00000A E2               [24]  389 	movx	a, @r0
      00000B FB               [12]  390 	mov	r3, a
      00000C EA               [12]  391 	mov	a, r2
      00000D F2               [24]  392 	movx	@r0, a
      00000E 80 2C            [24]  393 	sjmp	sdcc_atomic_exchange_exit
      000010 00               [12]  394 	nop
      000011 00               [12]  395 	nop
      000012                        396 sdcc_atomic_exchange_xdata_impl:
      000012 E0               [24]  397 	movx	a, @dptr
      000013 FB               [12]  398 	mov	r3, a
      000014 EA               [12]  399 	mov	a, r2
      000015 F0               [24]  400 	movx	@dptr, a
      000016 80 24            [24]  401 	sjmp	sdcc_atomic_exchange_exit
      000018                        402 sdcc_atomic_compare_exchange_idata_impl:
      000018 E6               [12]  403 	mov	a, @r0
      000019 B5 02 02         [24]  404 	cjne	a, ar2, .+#5
      00001C EB               [12]  405 	mov	a, r3
      00001D F6               [12]  406 	mov	@r0, a
      00001E 22               [24]  407 	ret
      00001F 00               [12]  408 	nop
      000020                        409 sdcc_atomic_compare_exchange_pdata_impl:
      000020 E2               [24]  410 	movx	a, @r0
      000021 B5 02 02         [24]  411 	cjne	a, ar2, .+#5
      000024 EB               [12]  412 	mov	a, r3
      000025 F2               [24]  413 	movx	@r0, a
      000026 22               [24]  414 	ret
      000027 00               [12]  415 	nop
      000028                        416 sdcc_atomic_compare_exchange_xdata_impl:
      000028 E0               [24]  417 	movx	a, @dptr
      000029 B5 02 02         [24]  418 	cjne	a, ar2, .+#5
      00002C EB               [12]  419 	mov	a, r3
      00002D F0               [24]  420 	movx	@dptr, a
      00002E 22               [24]  421 	ret
      00002F                        422 sdcc_atomic_exchange_rollback_end::
                                    423 
      00002F                        424 sdcc_atomic_exchange_gptr_impl::
      00002F 30 F6 E0         [24]  425 	jnb	b.6, sdcc_atomic_exchange_xdata_impl
      000032 A8 82            [24]  426 	mov	r0, dpl
      000034 20 F5 D3         [24]  427 	jb	b.5, sdcc_atomic_exchange_pdata_impl
      000037                        428 sdcc_atomic_exchange_idata_impl:
      000037 EA               [12]  429 	mov	a, r2
      000038 C6               [12]  430 	xch	a, @r0
      000039 F5 82            [12]  431 	mov	dpl, a
      00003B 22               [24]  432 	ret
      00003C                        433 sdcc_atomic_exchange_exit:
      00003C 8B 82            [24]  434 	mov	dpl, r3
      00003E 22               [24]  435 	ret
      00003F                        436 sdcc_atomic_compare_exchange_gptr_impl::
      00003F 30 F6 E6         [24]  437 	jnb	b.6, sdcc_atomic_compare_exchange_xdata_impl
      000042 A8 82            [24]  438 	mov	r0, dpl
      000044 20 F5 D9         [24]  439 	jb	b.5, sdcc_atomic_compare_exchange_pdata_impl
      000047 80 CF            [24]  440 	sjmp	sdcc_atomic_compare_exchange_idata_impl
                                    441 ;--------------------------------------------------------
                                    442 ; global & static initialisations
                                    443 ;--------------------------------------------------------
                                    444 	.area HOME    (CODE)
                                    445 	.area GSINIT  (CODE)
                                    446 	.area GSFINAL (CODE)
                                    447 	.area GSINIT  (CODE)
                                    448 	.globl __sdcc_gsinit_startup
                                    449 	.globl __sdcc_program_startup
                                    450 	.globl __start__stack
                                    451 	.globl __mcs51_genXINIT
                                    452 	.globl __mcs51_genXRAMCLEAR
                                    453 	.globl __mcs51_genRAMCLEAR
                                    454 	.area GSFINAL (CODE)
      0000A7 02 00 49         [24]  455 	ljmp	__sdcc_program_startup
                                    456 ;--------------------------------------------------------
                                    457 ; Home
                                    458 ;--------------------------------------------------------
                                    459 	.area HOME    (CODE)
                                    460 	.area HOME    (CODE)
      000049                        461 __sdcc_program_startup:
      000049 12 00 AA         [24]  462 	lcall	_main
      00004C                        463 __sdcc_program_exit:
      00004C 80 FE            [24]  464 	sjmp	.
                                    465 ;	return from main will return to caller
                                    466 ;--------------------------------------------------------
                                    467 ; code
                                    468 ;--------------------------------------------------------
                                    469 	.area CSEG    (CODE)
                                    470 ;------------------------------------------------------------
                                    471 ;Allocation info for local variables in function 'main'
                                    472 ;------------------------------------------------------------
                           000000   473 	G$main$0$0 ==.
                           000000   474 	C$exchange.c$7$0_0$2 ==.
                                    475 ;	exchange.c:7: void main(void)
                                    476 ;	-----------------------------------------
                                    477 ;	 function main
                                    478 ;	-----------------------------------------
      0000AA                        479 _main:
                           000007   480 	ar7 = 0x07
                           000006   481 	ar6 = 0x06
                           000005   482 	ar5 = 0x05
                           000004   483 	ar4 = 0x04
                           000003   484 	ar3 = 0x03
                           000002   485 	ar2 = 0x02
                           000001   486 	ar1 = 0x01
                           000000   487 	ar0 = 0x00
                           000000   488 	C$exchange.c$9$1_0$2 ==.
                                    489 ;	exchange.c:9: a = 10;
      0000AA 75 30 0A         [24]  490 	mov	_a,#0x0a
                           000003   491 	C$exchange.c$10$1_0$2 ==.
                                    492 ;	exchange.c:10: b = 20;
      0000AD 75 31 14         [24]  493 	mov	_b,#0x14
                           000006   494 	C$exchange.c$12$1_0$2 ==.
                                    495 ;	exchange.c:12: temp = a;
      0000B0 85 30 32         [24]  496 	mov	_temp,_a
                           000009   497 	C$exchange.c$13$1_0$2 ==.
                                    498 ;	exchange.c:13: a = b;
      0000B3 85 31 30         [24]  499 	mov	_a,_b
                           00000C   500 	C$exchange.c$14$1_0$2 ==.
                                    501 ;	exchange.c:14: b = temp;
      0000B6 85 32 31         [24]  502 	mov	_b,_temp
                           00000F   503 	C$exchange.c$16$1_0$2 ==.
                                    504 ;	exchange.c:16: a++;
      0000B9 E5 30            [12]  505 	mov	a,_a
      0000BB 04               [12]  506 	inc	a
      0000BC F5 30            [12]  507 	mov	_a,a
                           000014   508 	C$exchange.c$17$1_0$2 ==.
                                    509 ;	exchange.c:17: b--;
      0000BE E5 31            [12]  510 	mov	a,_b
      0000C0 14               [12]  511 	dec	a
      0000C1 F5 31            [12]  512 	mov	_b,a
                           000019   513 	C$exchange.c$19$1_0$2 ==.
                                    514 ;	exchange.c:19: while (1);
      0000C3                        515 00102$:
      0000C3 80 FE            [24]  516 	sjmp	00102$
                           00001B   517 	C$exchange.c$20$1_0$2 ==.
                                    518 ;	exchange.c:20: }
                           00001B   519 	C$exchange.c$20$1_0$2 ==.
                           00001B   520 	XG$main$0$0 ==.
      0000C5 22               [24]  521 	ret
                                    522 	.area CSEG    (CODE)
                                    523 	.area CONST   (CODE)
                                    524 	.area XINIT   (CODE)
                                    525 	.area CABS    (ABS,CODE)
