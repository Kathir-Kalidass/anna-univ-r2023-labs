                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.6.0 #16555 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module ex2_read_switches_leds
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
                                    108 ;--------------------------------------------------------
                                    109 ; special function registers
                                    110 ;--------------------------------------------------------
                                    111 	.area RSEG    (ABS,DATA)
      000000                        112 	.org 0x0000
                           000080   113 G$P0$0_0$0 == 0x0080
                           000080   114 _P0	=	0x0080
                           000081   115 G$SP$0_0$0 == 0x0081
                           000081   116 _SP	=	0x0081
                           000082   117 G$DPL$0_0$0 == 0x0082
                           000082   118 _DPL	=	0x0082
                           000083   119 G$DPH$0_0$0 == 0x0083
                           000083   120 _DPH	=	0x0083
                           000087   121 G$PCON$0_0$0 == 0x0087
                           000087   122 _PCON	=	0x0087
                           000088   123 G$TCON$0_0$0 == 0x0088
                           000088   124 _TCON	=	0x0088
                           000089   125 G$TMOD$0_0$0 == 0x0089
                           000089   126 _TMOD	=	0x0089
                           00008A   127 G$TL0$0_0$0 == 0x008a
                           00008A   128 _TL0	=	0x008a
                           00008B   129 G$TL1$0_0$0 == 0x008b
                           00008B   130 _TL1	=	0x008b
                           00008C   131 G$TH0$0_0$0 == 0x008c
                           00008C   132 _TH0	=	0x008c
                           00008D   133 G$TH1$0_0$0 == 0x008d
                           00008D   134 _TH1	=	0x008d
                           000090   135 G$P1$0_0$0 == 0x0090
                           000090   136 _P1	=	0x0090
                           000098   137 G$SCON$0_0$0 == 0x0098
                           000098   138 _SCON	=	0x0098
                           000099   139 G$SBUF$0_0$0 == 0x0099
                           000099   140 _SBUF	=	0x0099
                           0000A0   141 G$P2$0_0$0 == 0x00a0
                           0000A0   142 _P2	=	0x00a0
                           0000A8   143 G$IE$0_0$0 == 0x00a8
                           0000A8   144 _IE	=	0x00a8
                           0000B0   145 G$P3$0_0$0 == 0x00b0
                           0000B0   146 _P3	=	0x00b0
                           0000B8   147 G$IP$0_0$0 == 0x00b8
                           0000B8   148 _IP	=	0x00b8
                           0000D0   149 G$PSW$0_0$0 == 0x00d0
                           0000D0   150 _PSW	=	0x00d0
                           0000E0   151 G$ACC$0_0$0 == 0x00e0
                           0000E0   152 _ACC	=	0x00e0
                           0000F0   153 G$B$0_0$0 == 0x00f0
                           0000F0   154 _B	=	0x00f0
                                    155 ;--------------------------------------------------------
                                    156 ; special function bits
                                    157 ;--------------------------------------------------------
                                    158 	.area RSEG    (ABS,DATA)
      000000                        159 	.org 0x0000
                           000080   160 G$P0_0$0_0$0 == 0x0080
                           000080   161 _P0_0	=	0x0080
                           000081   162 G$P0_1$0_0$0 == 0x0081
                           000081   163 _P0_1	=	0x0081
                           000082   164 G$P0_2$0_0$0 == 0x0082
                           000082   165 _P0_2	=	0x0082
                           000083   166 G$P0_3$0_0$0 == 0x0083
                           000083   167 _P0_3	=	0x0083
                           000084   168 G$P0_4$0_0$0 == 0x0084
                           000084   169 _P0_4	=	0x0084
                           000085   170 G$P0_5$0_0$0 == 0x0085
                           000085   171 _P0_5	=	0x0085
                           000086   172 G$P0_6$0_0$0 == 0x0086
                           000086   173 _P0_6	=	0x0086
                           000087   174 G$P0_7$0_0$0 == 0x0087
                           000087   175 _P0_7	=	0x0087
                           000088   176 G$IT0$0_0$0 == 0x0088
                           000088   177 _IT0	=	0x0088
                           000089   178 G$IE0$0_0$0 == 0x0089
                           000089   179 _IE0	=	0x0089
                           00008A   180 G$IT1$0_0$0 == 0x008a
                           00008A   181 _IT1	=	0x008a
                           00008B   182 G$IE1$0_0$0 == 0x008b
                           00008B   183 _IE1	=	0x008b
                           00008C   184 G$TR0$0_0$0 == 0x008c
                           00008C   185 _TR0	=	0x008c
                           00008D   186 G$TF0$0_0$0 == 0x008d
                           00008D   187 _TF0	=	0x008d
                           00008E   188 G$TR1$0_0$0 == 0x008e
                           00008E   189 _TR1	=	0x008e
                           00008F   190 G$TF1$0_0$0 == 0x008f
                           00008F   191 _TF1	=	0x008f
                           000090   192 G$P1_0$0_0$0 == 0x0090
                           000090   193 _P1_0	=	0x0090
                           000091   194 G$P1_1$0_0$0 == 0x0091
                           000091   195 _P1_1	=	0x0091
                           000092   196 G$P1_2$0_0$0 == 0x0092
                           000092   197 _P1_2	=	0x0092
                           000093   198 G$P1_3$0_0$0 == 0x0093
                           000093   199 _P1_3	=	0x0093
                           000094   200 G$P1_4$0_0$0 == 0x0094
                           000094   201 _P1_4	=	0x0094
                           000095   202 G$P1_5$0_0$0 == 0x0095
                           000095   203 _P1_5	=	0x0095
                           000096   204 G$P1_6$0_0$0 == 0x0096
                           000096   205 _P1_6	=	0x0096
                           000097   206 G$P1_7$0_0$0 == 0x0097
                           000097   207 _P1_7	=	0x0097
                           000098   208 G$RI$0_0$0 == 0x0098
                           000098   209 _RI	=	0x0098
                           000099   210 G$TI$0_0$0 == 0x0099
                           000099   211 _TI	=	0x0099
                           00009A   212 G$RB8$0_0$0 == 0x009a
                           00009A   213 _RB8	=	0x009a
                           00009B   214 G$TB8$0_0$0 == 0x009b
                           00009B   215 _TB8	=	0x009b
                           00009C   216 G$REN$0_0$0 == 0x009c
                           00009C   217 _REN	=	0x009c
                           00009D   218 G$SM2$0_0$0 == 0x009d
                           00009D   219 _SM2	=	0x009d
                           00009E   220 G$SM1$0_0$0 == 0x009e
                           00009E   221 _SM1	=	0x009e
                           00009F   222 G$SM0$0_0$0 == 0x009f
                           00009F   223 _SM0	=	0x009f
                           0000A0   224 G$P2_0$0_0$0 == 0x00a0
                           0000A0   225 _P2_0	=	0x00a0
                           0000A1   226 G$P2_1$0_0$0 == 0x00a1
                           0000A1   227 _P2_1	=	0x00a1
                           0000A2   228 G$P2_2$0_0$0 == 0x00a2
                           0000A2   229 _P2_2	=	0x00a2
                           0000A3   230 G$P2_3$0_0$0 == 0x00a3
                           0000A3   231 _P2_3	=	0x00a3
                           0000A4   232 G$P2_4$0_0$0 == 0x00a4
                           0000A4   233 _P2_4	=	0x00a4
                           0000A5   234 G$P2_5$0_0$0 == 0x00a5
                           0000A5   235 _P2_5	=	0x00a5
                           0000A6   236 G$P2_6$0_0$0 == 0x00a6
                           0000A6   237 _P2_6	=	0x00a6
                           0000A7   238 G$P2_7$0_0$0 == 0x00a7
                           0000A7   239 _P2_7	=	0x00a7
                           0000A8   240 G$EX0$0_0$0 == 0x00a8
                           0000A8   241 _EX0	=	0x00a8
                           0000A9   242 G$ET0$0_0$0 == 0x00a9
                           0000A9   243 _ET0	=	0x00a9
                           0000AA   244 G$EX1$0_0$0 == 0x00aa
                           0000AA   245 _EX1	=	0x00aa
                           0000AB   246 G$ET1$0_0$0 == 0x00ab
                           0000AB   247 _ET1	=	0x00ab
                           0000AC   248 G$ES$0_0$0 == 0x00ac
                           0000AC   249 _ES	=	0x00ac
                           0000AF   250 G$EA$0_0$0 == 0x00af
                           0000AF   251 _EA	=	0x00af
                           0000B0   252 G$P3_0$0_0$0 == 0x00b0
                           0000B0   253 _P3_0	=	0x00b0
                           0000B1   254 G$P3_1$0_0$0 == 0x00b1
                           0000B1   255 _P3_1	=	0x00b1
                           0000B2   256 G$P3_2$0_0$0 == 0x00b2
                           0000B2   257 _P3_2	=	0x00b2
                           0000B3   258 G$P3_3$0_0$0 == 0x00b3
                           0000B3   259 _P3_3	=	0x00b3
                           0000B4   260 G$P3_4$0_0$0 == 0x00b4
                           0000B4   261 _P3_4	=	0x00b4
                           0000B5   262 G$P3_5$0_0$0 == 0x00b5
                           0000B5   263 _P3_5	=	0x00b5
                           0000B6   264 G$P3_6$0_0$0 == 0x00b6
                           0000B6   265 _P3_6	=	0x00b6
                           0000B7   266 G$P3_7$0_0$0 == 0x00b7
                           0000B7   267 _P3_7	=	0x00b7
                           0000B0   268 G$RXD$0_0$0 == 0x00b0
                           0000B0   269 _RXD	=	0x00b0
                           0000B1   270 G$TXD$0_0$0 == 0x00b1
                           0000B1   271 _TXD	=	0x00b1
                           0000B2   272 G$INT0$0_0$0 == 0x00b2
                           0000B2   273 _INT0	=	0x00b2
                           0000B3   274 G$INT1$0_0$0 == 0x00b3
                           0000B3   275 _INT1	=	0x00b3
                           0000B4   276 G$T0$0_0$0 == 0x00b4
                           0000B4   277 _T0	=	0x00b4
                           0000B5   278 G$T1$0_0$0 == 0x00b5
                           0000B5   279 _T1	=	0x00b5
                           0000B6   280 G$WR$0_0$0 == 0x00b6
                           0000B6   281 _WR	=	0x00b6
                           0000B7   282 G$RD$0_0$0 == 0x00b7
                           0000B7   283 _RD	=	0x00b7
                           0000B8   284 G$PX0$0_0$0 == 0x00b8
                           0000B8   285 _PX0	=	0x00b8
                           0000B9   286 G$PT0$0_0$0 == 0x00b9
                           0000B9   287 _PT0	=	0x00b9
                           0000BA   288 G$PX1$0_0$0 == 0x00ba
                           0000BA   289 _PX1	=	0x00ba
                           0000BB   290 G$PT1$0_0$0 == 0x00bb
                           0000BB   291 _PT1	=	0x00bb
                           0000BC   292 G$PS$0_0$0 == 0x00bc
                           0000BC   293 _PS	=	0x00bc
                           0000D0   294 G$P$0_0$0 == 0x00d0
                           0000D0   295 _P	=	0x00d0
                           0000D1   296 G$F1$0_0$0 == 0x00d1
                           0000D1   297 _F1	=	0x00d1
                           0000D2   298 G$OV$0_0$0 == 0x00d2
                           0000D2   299 _OV	=	0x00d2
                           0000D3   300 G$RS0$0_0$0 == 0x00d3
                           0000D3   301 _RS0	=	0x00d3
                           0000D4   302 G$RS1$0_0$0 == 0x00d4
                           0000D4   303 _RS1	=	0x00d4
                           0000D5   304 G$F0$0_0$0 == 0x00d5
                           0000D5   305 _F0	=	0x00d5
                           0000D6   306 G$AC$0_0$0 == 0x00d6
                           0000D6   307 _AC	=	0x00d6
                           0000D7   308 G$CY$0_0$0 == 0x00d7
                           0000D7   309 _CY	=	0x00d7
                                    310 ;--------------------------------------------------------
                                    311 ; overlayable register banks
                                    312 ;--------------------------------------------------------
                                    313 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        314 	.ds 8
                                    315 ;--------------------------------------------------------
                                    316 ; internal ram data
                                    317 ;--------------------------------------------------------
                                    318 	.area DSEG    (DATA)
                                    319 ;--------------------------------------------------------
                                    320 ; overlayable items in internal ram
                                    321 ;--------------------------------------------------------
                                    322 ;--------------------------------------------------------
                                    323 ; Stack segment in internal ram
                                    324 ;--------------------------------------------------------
                                    325 	.area SSEG
      000008                        326 __start__stack:
      000008                        327 	.ds	1
                                    328 
                                    329 ;--------------------------------------------------------
                                    330 ; indirectly addressable internal ram data
                                    331 ;--------------------------------------------------------
                                    332 	.area ISEG    (DATA)
                                    333 ;--------------------------------------------------------
                                    334 ; absolute internal ram data
                                    335 ;--------------------------------------------------------
                                    336 	.area IABS    (ABS,DATA)
                                    337 	.area IABS    (ABS,DATA)
                                    338 ;--------------------------------------------------------
                                    339 ; bit data
                                    340 ;--------------------------------------------------------
                                    341 	.area BSEG    (BIT)
                                    342 ;--------------------------------------------------------
                                    343 ; paged external ram data
                                    344 ;--------------------------------------------------------
                                    345 	.area PSEG    (PAG,XDATA)
                                    346 ;--------------------------------------------------------
                                    347 ; uninitialized external ram data
                                    348 ;--------------------------------------------------------
                                    349 	.area XSEG    (XDATA)
                                    350 ;--------------------------------------------------------
                                    351 ; absolute external ram data
                                    352 ;--------------------------------------------------------
                                    353 	.area XABS    (ABS,XDATA)
                                    354 ;--------------------------------------------------------
                                    355 ; initialized external ram data
                                    356 ;--------------------------------------------------------
                                    357 	.area XISEG   (XDATA)
                                    358 	.area HOME    (CODE)
                                    359 	.area GSINIT0 (CODE)
                                    360 	.area GSINIT1 (CODE)
                                    361 	.area GSINIT2 (CODE)
                                    362 	.area GSINIT3 (CODE)
                                    363 	.area GSINIT4 (CODE)
                                    364 	.area GSINIT5 (CODE)
                                    365 	.area GSINIT  (CODE)
                                    366 	.area GSFINAL (CODE)
                                    367 	.area CSEG    (CODE)
                                    368 ;--------------------------------------------------------
                                    369 ; interrupt vector
                                    370 ;--------------------------------------------------------
                                    371 	.area HOME    (CODE)
      000000                        372 __interrupt_vect:
      000000 02 00 4E         [24]  373 	ljmp	__sdcc_gsinit_startup
                                    374 ; restartable atomic support routines
      000003                        375 	.ds	5
      000008                        376 sdcc_atomic_exchange_rollback_start::
      000008 00               [12]  377 	nop
      000009 00               [12]  378 	nop
      00000A                        379 sdcc_atomic_exchange_pdata_impl:
      00000A E2               [24]  380 	movx	a, @r0
      00000B FB               [12]  381 	mov	r3, a
      00000C EA               [12]  382 	mov	a, r2
      00000D F2               [24]  383 	movx	@r0, a
      00000E 80 2C            [24]  384 	sjmp	sdcc_atomic_exchange_exit
      000010 00               [12]  385 	nop
      000011 00               [12]  386 	nop
      000012                        387 sdcc_atomic_exchange_xdata_impl:
      000012 E0               [24]  388 	movx	a, @dptr
      000013 FB               [12]  389 	mov	r3, a
      000014 EA               [12]  390 	mov	a, r2
      000015 F0               [24]  391 	movx	@dptr, a
      000016 80 24            [24]  392 	sjmp	sdcc_atomic_exchange_exit
      000018                        393 sdcc_atomic_compare_exchange_idata_impl:
      000018 E6               [12]  394 	mov	a, @r0
      000019 B5 02 02         [24]  395 	cjne	a, ar2, .+#5
      00001C EB               [12]  396 	mov	a, r3
      00001D F6               [12]  397 	mov	@r0, a
      00001E 22               [24]  398 	ret
      00001F 00               [12]  399 	nop
      000020                        400 sdcc_atomic_compare_exchange_pdata_impl:
      000020 E2               [24]  401 	movx	a, @r0
      000021 B5 02 02         [24]  402 	cjne	a, ar2, .+#5
      000024 EB               [12]  403 	mov	a, r3
      000025 F2               [24]  404 	movx	@r0, a
      000026 22               [24]  405 	ret
      000027 00               [12]  406 	nop
      000028                        407 sdcc_atomic_compare_exchange_xdata_impl:
      000028 E0               [24]  408 	movx	a, @dptr
      000029 B5 02 02         [24]  409 	cjne	a, ar2, .+#5
      00002C EB               [12]  410 	mov	a, r3
      00002D F0               [24]  411 	movx	@dptr, a
      00002E 22               [24]  412 	ret
      00002F                        413 sdcc_atomic_exchange_rollback_end::
                                    414 
      00002F                        415 sdcc_atomic_exchange_gptr_impl::
      00002F 30 F6 E0         [24]  416 	jnb	b.6, sdcc_atomic_exchange_xdata_impl
      000032 A8 82            [24]  417 	mov	r0, dpl
      000034 20 F5 D3         [24]  418 	jb	b.5, sdcc_atomic_exchange_pdata_impl
      000037                        419 sdcc_atomic_exchange_idata_impl:
      000037 EA               [12]  420 	mov	a, r2
      000038 C6               [12]  421 	xch	a, @r0
      000039 F5 82            [12]  422 	mov	dpl, a
      00003B 22               [24]  423 	ret
      00003C                        424 sdcc_atomic_exchange_exit:
      00003C 8B 82            [24]  425 	mov	dpl, r3
      00003E 22               [24]  426 	ret
      00003F                        427 sdcc_atomic_compare_exchange_gptr_impl::
      00003F 30 F6 E6         [24]  428 	jnb	b.6, sdcc_atomic_compare_exchange_xdata_impl
      000042 A8 82            [24]  429 	mov	r0, dpl
      000044 20 F5 D9         [24]  430 	jb	b.5, sdcc_atomic_compare_exchange_pdata_impl
      000047 80 CF            [24]  431 	sjmp	sdcc_atomic_compare_exchange_idata_impl
                                    432 ;--------------------------------------------------------
                                    433 ; global & static initialisations
                                    434 ;--------------------------------------------------------
                                    435 	.area HOME    (CODE)
                                    436 	.area GSINIT  (CODE)
                                    437 	.area GSFINAL (CODE)
                                    438 	.area GSINIT  (CODE)
                                    439 	.globl __sdcc_gsinit_startup
                                    440 	.globl __sdcc_program_startup
                                    441 	.globl __start__stack
                                    442 	.globl __mcs51_genXINIT
                                    443 	.globl __mcs51_genXRAMCLEAR
                                    444 	.globl __mcs51_genRAMCLEAR
                                    445 	.area GSFINAL (CODE)
      0000A7 02 00 49         [24]  446 	ljmp	__sdcc_program_startup
                                    447 ;--------------------------------------------------------
                                    448 ; Home
                                    449 ;--------------------------------------------------------
                                    450 	.area HOME    (CODE)
                                    451 	.area HOME    (CODE)
      000049                        452 __sdcc_program_startup:
      000049 12 00 AA         [24]  453 	lcall	_main
      00004C                        454 __sdcc_program_exit:
      00004C 80 FE            [24]  455 	sjmp	.
                                    456 ;	return from main will return to caller
                                    457 ;--------------------------------------------------------
                                    458 ; code
                                    459 ;--------------------------------------------------------
                                    460 	.area CSEG    (CODE)
                                    461 ;------------------------------------------------------------
                                    462 ;Allocation info for local variables in function 'main'
                                    463 ;------------------------------------------------------------
                           000000   464 	G$main$0$0 ==.
                           000000   465 	C$ex2_read_switches_leds.c$8$0_0$2 ==.
                                    466 ;	ex2_read_switches_leds.c:8: void main(void) {
                                    467 ;	-----------------------------------------
                                    468 ;	 function main
                                    469 ;	-----------------------------------------
      0000AA                        470 _main:
                           000007   471 	ar7 = 0x07
                           000006   472 	ar6 = 0x06
                           000005   473 	ar5 = 0x05
                           000004   474 	ar4 = 0x04
                           000003   475 	ar3 = 0x03
                           000002   476 	ar2 = 0x02
                           000001   477 	ar1 = 0x01
                           000000   478 	ar0 = 0x00
                           000000   479 	C$ex2_read_switches_leds.c$9$1_0$2 ==.
                                    480 ;	ex2_read_switches_leds.c:9: P0 = 0xFF;     /* Configure P0 as input */
      0000AA 75 80 FF         [24]  481 	mov	_P0,#0xff
                           000003   482 	C$ex2_read_switches_leds.c$11$1_0$2 ==.
                                    483 ;	ex2_read_switches_leds.c:11: while (1) {
      0000AD                        484 00102$:
                           000003   485 	C$ex2_read_switches_leds.c$12$2_0$3 ==.
                                    486 ;	ex2_read_switches_leds.c:12: P1 = P0;   /* Mirror switches to LEDs */
      0000AD 85 80 90         [24]  487 	mov	_P1,_P0
      0000B0 80 FB            [24]  488 	sjmp	00102$
                           000008   489 	C$ex2_read_switches_leds.c$14$1_0$2 ==.
                                    490 ;	ex2_read_switches_leds.c:14: }
                           000008   491 	C$ex2_read_switches_leds.c$14$1_0$2 ==.
                           000008   492 	XG$main$0$0 ==.
      0000B2 22               [24]  493 	ret
                                    494 	.area CSEG    (CODE)
                                    495 	.area CONST   (CODE)
                                    496 	.area XINIT   (CODE)
                                    497 	.area CABS    (ABS,CODE)
