                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.6.0 #16555 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module toggle_led_switch
                                      6 	
                                      7 	.optsdcc -mmcs51 --model-small
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _LED
                                     13 	.globl _SW
                                     14 	.globl _CY
                                     15 	.globl _AC
                                     16 	.globl _F0
                                     17 	.globl _RS1
                                     18 	.globl _RS0
                                     19 	.globl _OV
                                     20 	.globl _F1
                                     21 	.globl _P
                                     22 	.globl _PS
                                     23 	.globl _PT1
                                     24 	.globl _PX1
                                     25 	.globl _PT0
                                     26 	.globl _PX0
                                     27 	.globl _RD
                                     28 	.globl _WR
                                     29 	.globl _T1
                                     30 	.globl _T0
                                     31 	.globl _INT1
                                     32 	.globl _INT0
                                     33 	.globl _TXD
                                     34 	.globl _RXD
                                     35 	.globl _P3_7
                                     36 	.globl _P3_6
                                     37 	.globl _P3_5
                                     38 	.globl _P3_4
                                     39 	.globl _P3_3
                                     40 	.globl _P3_2
                                     41 	.globl _P3_1
                                     42 	.globl _P3_0
                                     43 	.globl _EA
                                     44 	.globl _ES
                                     45 	.globl _ET1
                                     46 	.globl _EX1
                                     47 	.globl _ET0
                                     48 	.globl _EX0
                                     49 	.globl _P2_7
                                     50 	.globl _P2_6
                                     51 	.globl _P2_5
                                     52 	.globl _P2_4
                                     53 	.globl _P2_3
                                     54 	.globl _P2_2
                                     55 	.globl _P2_1
                                     56 	.globl _P2_0
                                     57 	.globl _SM0
                                     58 	.globl _SM1
                                     59 	.globl _SM2
                                     60 	.globl _REN
                                     61 	.globl _TB8
                                     62 	.globl _RB8
                                     63 	.globl _TI
                                     64 	.globl _RI
                                     65 	.globl _P1_7
                                     66 	.globl _P1_6
                                     67 	.globl _P1_5
                                     68 	.globl _P1_4
                                     69 	.globl _P1_3
                                     70 	.globl _P1_2
                                     71 	.globl _P1_1
                                     72 	.globl _P1_0
                                     73 	.globl _TF1
                                     74 	.globl _TR1
                                     75 	.globl _TF0
                                     76 	.globl _TR0
                                     77 	.globl _IE1
                                     78 	.globl _IT1
                                     79 	.globl _IE0
                                     80 	.globl _IT0
                                     81 	.globl _P0_7
                                     82 	.globl _P0_6
                                     83 	.globl _P0_5
                                     84 	.globl _P0_4
                                     85 	.globl _P0_3
                                     86 	.globl _P0_2
                                     87 	.globl _P0_1
                                     88 	.globl _P0_0
                                     89 	.globl _B
                                     90 	.globl _ACC
                                     91 	.globl _PSW
                                     92 	.globl _IP
                                     93 	.globl _P3
                                     94 	.globl _IE
                                     95 	.globl _P2
                                     96 	.globl _SBUF
                                     97 	.globl _SCON
                                     98 	.globl _P1
                                     99 	.globl _TH1
                                    100 	.globl _TH0
                                    101 	.globl _TL1
                                    102 	.globl _TL0
                                    103 	.globl _TMOD
                                    104 	.globl _TCON
                                    105 	.globl _PCON
                                    106 	.globl _DPH
                                    107 	.globl _DPL
                                    108 	.globl _SP
                                    109 	.globl _P0
                                    110 ;--------------------------------------------------------
                                    111 ; special function registers
                                    112 ;--------------------------------------------------------
                                    113 	.area RSEG    (ABS,DATA)
      000000                        114 	.org 0x0000
                           000080   115 G$P0$0_0$0 == 0x0080
                           000080   116 _P0	=	0x0080
                           000081   117 G$SP$0_0$0 == 0x0081
                           000081   118 _SP	=	0x0081
                           000082   119 G$DPL$0_0$0 == 0x0082
                           000082   120 _DPL	=	0x0082
                           000083   121 G$DPH$0_0$0 == 0x0083
                           000083   122 _DPH	=	0x0083
                           000087   123 G$PCON$0_0$0 == 0x0087
                           000087   124 _PCON	=	0x0087
                           000088   125 G$TCON$0_0$0 == 0x0088
                           000088   126 _TCON	=	0x0088
                           000089   127 G$TMOD$0_0$0 == 0x0089
                           000089   128 _TMOD	=	0x0089
                           00008A   129 G$TL0$0_0$0 == 0x008a
                           00008A   130 _TL0	=	0x008a
                           00008B   131 G$TL1$0_0$0 == 0x008b
                           00008B   132 _TL1	=	0x008b
                           00008C   133 G$TH0$0_0$0 == 0x008c
                           00008C   134 _TH0	=	0x008c
                           00008D   135 G$TH1$0_0$0 == 0x008d
                           00008D   136 _TH1	=	0x008d
                           000090   137 G$P1$0_0$0 == 0x0090
                           000090   138 _P1	=	0x0090
                           000098   139 G$SCON$0_0$0 == 0x0098
                           000098   140 _SCON	=	0x0098
                           000099   141 G$SBUF$0_0$0 == 0x0099
                           000099   142 _SBUF	=	0x0099
                           0000A0   143 G$P2$0_0$0 == 0x00a0
                           0000A0   144 _P2	=	0x00a0
                           0000A8   145 G$IE$0_0$0 == 0x00a8
                           0000A8   146 _IE	=	0x00a8
                           0000B0   147 G$P3$0_0$0 == 0x00b0
                           0000B0   148 _P3	=	0x00b0
                           0000B8   149 G$IP$0_0$0 == 0x00b8
                           0000B8   150 _IP	=	0x00b8
                           0000D0   151 G$PSW$0_0$0 == 0x00d0
                           0000D0   152 _PSW	=	0x00d0
                           0000E0   153 G$ACC$0_0$0 == 0x00e0
                           0000E0   154 _ACC	=	0x00e0
                           0000F0   155 G$B$0_0$0 == 0x00f0
                           0000F0   156 _B	=	0x00f0
                                    157 ;--------------------------------------------------------
                                    158 ; special function bits
                                    159 ;--------------------------------------------------------
                                    160 	.area RSEG    (ABS,DATA)
      000000                        161 	.org 0x0000
                           000080   162 G$P0_0$0_0$0 == 0x0080
                           000080   163 _P0_0	=	0x0080
                           000081   164 G$P0_1$0_0$0 == 0x0081
                           000081   165 _P0_1	=	0x0081
                           000082   166 G$P0_2$0_0$0 == 0x0082
                           000082   167 _P0_2	=	0x0082
                           000083   168 G$P0_3$0_0$0 == 0x0083
                           000083   169 _P0_3	=	0x0083
                           000084   170 G$P0_4$0_0$0 == 0x0084
                           000084   171 _P0_4	=	0x0084
                           000085   172 G$P0_5$0_0$0 == 0x0085
                           000085   173 _P0_5	=	0x0085
                           000086   174 G$P0_6$0_0$0 == 0x0086
                           000086   175 _P0_6	=	0x0086
                           000087   176 G$P0_7$0_0$0 == 0x0087
                           000087   177 _P0_7	=	0x0087
                           000088   178 G$IT0$0_0$0 == 0x0088
                           000088   179 _IT0	=	0x0088
                           000089   180 G$IE0$0_0$0 == 0x0089
                           000089   181 _IE0	=	0x0089
                           00008A   182 G$IT1$0_0$0 == 0x008a
                           00008A   183 _IT1	=	0x008a
                           00008B   184 G$IE1$0_0$0 == 0x008b
                           00008B   185 _IE1	=	0x008b
                           00008C   186 G$TR0$0_0$0 == 0x008c
                           00008C   187 _TR0	=	0x008c
                           00008D   188 G$TF0$0_0$0 == 0x008d
                           00008D   189 _TF0	=	0x008d
                           00008E   190 G$TR1$0_0$0 == 0x008e
                           00008E   191 _TR1	=	0x008e
                           00008F   192 G$TF1$0_0$0 == 0x008f
                           00008F   193 _TF1	=	0x008f
                           000090   194 G$P1_0$0_0$0 == 0x0090
                           000090   195 _P1_0	=	0x0090
                           000091   196 G$P1_1$0_0$0 == 0x0091
                           000091   197 _P1_1	=	0x0091
                           000092   198 G$P1_2$0_0$0 == 0x0092
                           000092   199 _P1_2	=	0x0092
                           000093   200 G$P1_3$0_0$0 == 0x0093
                           000093   201 _P1_3	=	0x0093
                           000094   202 G$P1_4$0_0$0 == 0x0094
                           000094   203 _P1_4	=	0x0094
                           000095   204 G$P1_5$0_0$0 == 0x0095
                           000095   205 _P1_5	=	0x0095
                           000096   206 G$P1_6$0_0$0 == 0x0096
                           000096   207 _P1_6	=	0x0096
                           000097   208 G$P1_7$0_0$0 == 0x0097
                           000097   209 _P1_7	=	0x0097
                           000098   210 G$RI$0_0$0 == 0x0098
                           000098   211 _RI	=	0x0098
                           000099   212 G$TI$0_0$0 == 0x0099
                           000099   213 _TI	=	0x0099
                           00009A   214 G$RB8$0_0$0 == 0x009a
                           00009A   215 _RB8	=	0x009a
                           00009B   216 G$TB8$0_0$0 == 0x009b
                           00009B   217 _TB8	=	0x009b
                           00009C   218 G$REN$0_0$0 == 0x009c
                           00009C   219 _REN	=	0x009c
                           00009D   220 G$SM2$0_0$0 == 0x009d
                           00009D   221 _SM2	=	0x009d
                           00009E   222 G$SM1$0_0$0 == 0x009e
                           00009E   223 _SM1	=	0x009e
                           00009F   224 G$SM0$0_0$0 == 0x009f
                           00009F   225 _SM0	=	0x009f
                           0000A0   226 G$P2_0$0_0$0 == 0x00a0
                           0000A0   227 _P2_0	=	0x00a0
                           0000A1   228 G$P2_1$0_0$0 == 0x00a1
                           0000A1   229 _P2_1	=	0x00a1
                           0000A2   230 G$P2_2$0_0$0 == 0x00a2
                           0000A2   231 _P2_2	=	0x00a2
                           0000A3   232 G$P2_3$0_0$0 == 0x00a3
                           0000A3   233 _P2_3	=	0x00a3
                           0000A4   234 G$P2_4$0_0$0 == 0x00a4
                           0000A4   235 _P2_4	=	0x00a4
                           0000A5   236 G$P2_5$0_0$0 == 0x00a5
                           0000A5   237 _P2_5	=	0x00a5
                           0000A6   238 G$P2_6$0_0$0 == 0x00a6
                           0000A6   239 _P2_6	=	0x00a6
                           0000A7   240 G$P2_7$0_0$0 == 0x00a7
                           0000A7   241 _P2_7	=	0x00a7
                           0000A8   242 G$EX0$0_0$0 == 0x00a8
                           0000A8   243 _EX0	=	0x00a8
                           0000A9   244 G$ET0$0_0$0 == 0x00a9
                           0000A9   245 _ET0	=	0x00a9
                           0000AA   246 G$EX1$0_0$0 == 0x00aa
                           0000AA   247 _EX1	=	0x00aa
                           0000AB   248 G$ET1$0_0$0 == 0x00ab
                           0000AB   249 _ET1	=	0x00ab
                           0000AC   250 G$ES$0_0$0 == 0x00ac
                           0000AC   251 _ES	=	0x00ac
                           0000AF   252 G$EA$0_0$0 == 0x00af
                           0000AF   253 _EA	=	0x00af
                           0000B0   254 G$P3_0$0_0$0 == 0x00b0
                           0000B0   255 _P3_0	=	0x00b0
                           0000B1   256 G$P3_1$0_0$0 == 0x00b1
                           0000B1   257 _P3_1	=	0x00b1
                           0000B2   258 G$P3_2$0_0$0 == 0x00b2
                           0000B2   259 _P3_2	=	0x00b2
                           0000B3   260 G$P3_3$0_0$0 == 0x00b3
                           0000B3   261 _P3_3	=	0x00b3
                           0000B4   262 G$P3_4$0_0$0 == 0x00b4
                           0000B4   263 _P3_4	=	0x00b4
                           0000B5   264 G$P3_5$0_0$0 == 0x00b5
                           0000B5   265 _P3_5	=	0x00b5
                           0000B6   266 G$P3_6$0_0$0 == 0x00b6
                           0000B6   267 _P3_6	=	0x00b6
                           0000B7   268 G$P3_7$0_0$0 == 0x00b7
                           0000B7   269 _P3_7	=	0x00b7
                           0000B0   270 G$RXD$0_0$0 == 0x00b0
                           0000B0   271 _RXD	=	0x00b0
                           0000B1   272 G$TXD$0_0$0 == 0x00b1
                           0000B1   273 _TXD	=	0x00b1
                           0000B2   274 G$INT0$0_0$0 == 0x00b2
                           0000B2   275 _INT0	=	0x00b2
                           0000B3   276 G$INT1$0_0$0 == 0x00b3
                           0000B3   277 _INT1	=	0x00b3
                           0000B4   278 G$T0$0_0$0 == 0x00b4
                           0000B4   279 _T0	=	0x00b4
                           0000B5   280 G$T1$0_0$0 == 0x00b5
                           0000B5   281 _T1	=	0x00b5
                           0000B6   282 G$WR$0_0$0 == 0x00b6
                           0000B6   283 _WR	=	0x00b6
                           0000B7   284 G$RD$0_0$0 == 0x00b7
                           0000B7   285 _RD	=	0x00b7
                           0000B8   286 G$PX0$0_0$0 == 0x00b8
                           0000B8   287 _PX0	=	0x00b8
                           0000B9   288 G$PT0$0_0$0 == 0x00b9
                           0000B9   289 _PT0	=	0x00b9
                           0000BA   290 G$PX1$0_0$0 == 0x00ba
                           0000BA   291 _PX1	=	0x00ba
                           0000BB   292 G$PT1$0_0$0 == 0x00bb
                           0000BB   293 _PT1	=	0x00bb
                           0000BC   294 G$PS$0_0$0 == 0x00bc
                           0000BC   295 _PS	=	0x00bc
                           0000D0   296 G$P$0_0$0 == 0x00d0
                           0000D0   297 _P	=	0x00d0
                           0000D1   298 G$F1$0_0$0 == 0x00d1
                           0000D1   299 _F1	=	0x00d1
                           0000D2   300 G$OV$0_0$0 == 0x00d2
                           0000D2   301 _OV	=	0x00d2
                           0000D3   302 G$RS0$0_0$0 == 0x00d3
                           0000D3   303 _RS0	=	0x00d3
                           0000D4   304 G$RS1$0_0$0 == 0x00d4
                           0000D4   305 _RS1	=	0x00d4
                           0000D5   306 G$F0$0_0$0 == 0x00d5
                           0000D5   307 _F0	=	0x00d5
                           0000D6   308 G$AC$0_0$0 == 0x00d6
                           0000D6   309 _AC	=	0x00d6
                           0000D7   310 G$CY$0_0$0 == 0x00d7
                           0000D7   311 _CY	=	0x00d7
                           000090   312 G$SW$0_0$0 == 0x0090
                           000090   313 _SW	=	0x0090
                           0000A7   314 G$LED$0_0$0 == 0x00a7
                           0000A7   315 _LED	=	0x00a7
                                    316 ;--------------------------------------------------------
                                    317 ; overlayable register banks
                                    318 ;--------------------------------------------------------
                                    319 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        320 	.ds 8
                                    321 ;--------------------------------------------------------
                                    322 ; internal ram data
                                    323 ;--------------------------------------------------------
                                    324 	.area DSEG    (DATA)
                                    325 ;--------------------------------------------------------
                                    326 ; overlayable items in internal ram
                                    327 ;--------------------------------------------------------
                                    328 ;--------------------------------------------------------
                                    329 ; Stack segment in internal ram
                                    330 ;--------------------------------------------------------
                                    331 	.area SSEG
      000008                        332 __start__stack:
      000008                        333 	.ds	1
                                    334 
                                    335 ;--------------------------------------------------------
                                    336 ; indirectly addressable internal ram data
                                    337 ;--------------------------------------------------------
                                    338 	.area ISEG    (DATA)
                                    339 ;--------------------------------------------------------
                                    340 ; absolute internal ram data
                                    341 ;--------------------------------------------------------
                                    342 	.area IABS    (ABS,DATA)
                                    343 	.area IABS    (ABS,DATA)
                                    344 ;--------------------------------------------------------
                                    345 ; bit data
                                    346 ;--------------------------------------------------------
                                    347 	.area BSEG    (BIT)
                                    348 ;--------------------------------------------------------
                                    349 ; paged external ram data
                                    350 ;--------------------------------------------------------
                                    351 	.area PSEG    (PAG,XDATA)
                                    352 ;--------------------------------------------------------
                                    353 ; uninitialized external ram data
                                    354 ;--------------------------------------------------------
                                    355 	.area XSEG    (XDATA)
                                    356 ;--------------------------------------------------------
                                    357 ; absolute external ram data
                                    358 ;--------------------------------------------------------
                                    359 	.area XABS    (ABS,XDATA)
                                    360 ;--------------------------------------------------------
                                    361 ; initialized external ram data
                                    362 ;--------------------------------------------------------
                                    363 	.area XISEG   (XDATA)
                                    364 	.area HOME    (CODE)
                                    365 	.area GSINIT0 (CODE)
                                    366 	.area GSINIT1 (CODE)
                                    367 	.area GSINIT2 (CODE)
                                    368 	.area GSINIT3 (CODE)
                                    369 	.area GSINIT4 (CODE)
                                    370 	.area GSINIT5 (CODE)
                                    371 	.area GSINIT  (CODE)
                                    372 	.area GSFINAL (CODE)
                                    373 	.area CSEG    (CODE)
                                    374 ;--------------------------------------------------------
                                    375 ; interrupt vector
                                    376 ;--------------------------------------------------------
                                    377 	.area HOME    (CODE)
      000000                        378 __interrupt_vect:
      000000 02 00 4E         [24]  379 	ljmp	__sdcc_gsinit_startup
                                    380 ; restartable atomic support routines
      000003                        381 	.ds	5
      000008                        382 sdcc_atomic_exchange_rollback_start::
      000008 00               [12]  383 	nop
      000009 00               [12]  384 	nop
      00000A                        385 sdcc_atomic_exchange_pdata_impl:
      00000A E2               [24]  386 	movx	a, @r0
      00000B FB               [12]  387 	mov	r3, a
      00000C EA               [12]  388 	mov	a, r2
      00000D F2               [24]  389 	movx	@r0, a
      00000E 80 2C            [24]  390 	sjmp	sdcc_atomic_exchange_exit
      000010 00               [12]  391 	nop
      000011 00               [12]  392 	nop
      000012                        393 sdcc_atomic_exchange_xdata_impl:
      000012 E0               [24]  394 	movx	a, @dptr
      000013 FB               [12]  395 	mov	r3, a
      000014 EA               [12]  396 	mov	a, r2
      000015 F0               [24]  397 	movx	@dptr, a
      000016 80 24            [24]  398 	sjmp	sdcc_atomic_exchange_exit
      000018                        399 sdcc_atomic_compare_exchange_idata_impl:
      000018 E6               [12]  400 	mov	a, @r0
      000019 B5 02 02         [24]  401 	cjne	a, ar2, .+#5
      00001C EB               [12]  402 	mov	a, r3
      00001D F6               [12]  403 	mov	@r0, a
      00001E 22               [24]  404 	ret
      00001F 00               [12]  405 	nop
      000020                        406 sdcc_atomic_compare_exchange_pdata_impl:
      000020 E2               [24]  407 	movx	a, @r0
      000021 B5 02 02         [24]  408 	cjne	a, ar2, .+#5
      000024 EB               [12]  409 	mov	a, r3
      000025 F2               [24]  410 	movx	@r0, a
      000026 22               [24]  411 	ret
      000027 00               [12]  412 	nop
      000028                        413 sdcc_atomic_compare_exchange_xdata_impl:
      000028 E0               [24]  414 	movx	a, @dptr
      000029 B5 02 02         [24]  415 	cjne	a, ar2, .+#5
      00002C EB               [12]  416 	mov	a, r3
      00002D F0               [24]  417 	movx	@dptr, a
      00002E 22               [24]  418 	ret
      00002F                        419 sdcc_atomic_exchange_rollback_end::
                                    420 
      00002F                        421 sdcc_atomic_exchange_gptr_impl::
      00002F 30 F6 E0         [24]  422 	jnb	b.6, sdcc_atomic_exchange_xdata_impl
      000032 A8 82            [24]  423 	mov	r0, dpl
      000034 20 F5 D3         [24]  424 	jb	b.5, sdcc_atomic_exchange_pdata_impl
      000037                        425 sdcc_atomic_exchange_idata_impl:
      000037 EA               [12]  426 	mov	a, r2
      000038 C6               [12]  427 	xch	a, @r0
      000039 F5 82            [12]  428 	mov	dpl, a
      00003B 22               [24]  429 	ret
      00003C                        430 sdcc_atomic_exchange_exit:
      00003C 8B 82            [24]  431 	mov	dpl, r3
      00003E 22               [24]  432 	ret
      00003F                        433 sdcc_atomic_compare_exchange_gptr_impl::
      00003F 30 F6 E6         [24]  434 	jnb	b.6, sdcc_atomic_compare_exchange_xdata_impl
      000042 A8 82            [24]  435 	mov	r0, dpl
      000044 20 F5 D9         [24]  436 	jb	b.5, sdcc_atomic_compare_exchange_pdata_impl
      000047 80 CF            [24]  437 	sjmp	sdcc_atomic_compare_exchange_idata_impl
                                    438 ;--------------------------------------------------------
                                    439 ; global & static initialisations
                                    440 ;--------------------------------------------------------
                                    441 	.area HOME    (CODE)
                                    442 	.area GSINIT  (CODE)
                                    443 	.area GSFINAL (CODE)
                                    444 	.area GSINIT  (CODE)
                                    445 	.globl __sdcc_gsinit_startup
                                    446 	.globl __sdcc_program_startup
                                    447 	.globl __start__stack
                                    448 	.globl __mcs51_genXINIT
                                    449 	.globl __mcs51_genXRAMCLEAR
                                    450 	.globl __mcs51_genRAMCLEAR
                                    451 	.area GSFINAL (CODE)
      0000A7 02 00 49         [24]  452 	ljmp	__sdcc_program_startup
                                    453 ;--------------------------------------------------------
                                    454 ; Home
                                    455 ;--------------------------------------------------------
                                    456 	.area HOME    (CODE)
                                    457 	.area HOME    (CODE)
      000049                        458 __sdcc_program_startup:
      000049 12 00 AA         [24]  459 	lcall	_main
      00004C                        460 __sdcc_program_exit:
      00004C 80 FE            [24]  461 	sjmp	.
                                    462 ;	return from main will return to caller
                                    463 ;--------------------------------------------------------
                                    464 ; code
                                    465 ;--------------------------------------------------------
                                    466 	.area CSEG    (CODE)
                                    467 ;------------------------------------------------------------
                                    468 ;Allocation info for local variables in function 'main'
                                    469 ;------------------------------------------------------------
                           000000   470 	G$main$0$0 ==.
                           000000   471 	C$toggle_led_switch.c$6$0_0$2 ==.
                                    472 ;	toggle_led_switch.c:6: void main(void)
                                    473 ;	-----------------------------------------
                                    474 ;	 function main
                                    475 ;	-----------------------------------------
      0000AA                        476 _main:
                           000007   477 	ar7 = 0x07
                           000006   478 	ar6 = 0x06
                           000005   479 	ar5 = 0x05
                           000004   480 	ar4 = 0x04
                           000003   481 	ar3 = 0x03
                           000002   482 	ar2 = 0x02
                           000001   483 	ar1 = 0x01
                           000000   484 	ar0 = 0x00
                           000000   485 	C$toggle_led_switch.c$8$1_0$2 ==.
                                    486 ;	toggle_led_switch.c:8: P1 = 0xFF;
      0000AA 75 90 FF         [24]  487 	mov	_P1,#0xff
                           000003   488 	C$toggle_led_switch.c$9$1_0$2 ==.
                                    489 ;	toggle_led_switch.c:9: LED = 0;
                                    490 ;	assignBit
      0000AD C2 A7            [12]  491 	clr	_LED
                           000005   492 	C$toggle_led_switch.c$11$1_0$2 ==.
                                    493 ;	toggle_led_switch.c:11: while (1)
      0000AF                        494 00107$:
                           000005   495 	C$toggle_led_switch.c$13$3_0$4 ==.
                                    496 ;	toggle_led_switch.c:13: if (SW == 0)
      0000AF 20 90 FD         [24]  497 	jb	_SW,00107$
                           000008   498 	C$toggle_led_switch.c$15$4_0$5 ==.
                                    499 ;	toggle_led_switch.c:15: LED = !LED;
      0000B2 B2 A7            [12]  500 	cpl	_LED
                           00000A   501 	C$toggle_led_switch.c$16$4_0$5 ==.
                                    502 ;	toggle_led_switch.c:16: while (SW == 0);
      0000B4                        503 00101$:
      0000B4 30 90 FD         [24]  504 	jnb	_SW,00101$
      0000B7 80 F6            [24]  505 	sjmp	00107$
                           00000F   506 	C$toggle_led_switch.c$19$1_0$2 ==.
                                    507 ;	toggle_led_switch.c:19: }
                           00000F   508 	C$toggle_led_switch.c$19$1_0$2 ==.
                           00000F   509 	XG$main$0$0 ==.
      0000B9 22               [24]  510 	ret
                                    511 	.area CSEG    (CODE)
                                    512 	.area CONST   (CODE)
                                    513 	.area XINIT   (CODE)
                                    514 	.area CABS    (ABS,CODE)
