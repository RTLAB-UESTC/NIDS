
/*  A Bison parser, made from ./grammar.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse sfbpf_parse
#define yylex sfbpf_lex
#define yyerror sfbpf_error
#define yylval sfbpf_lval
#define yychar sfbpf_char
#define yydebug sfbpf_debug
#define yynerrs sfbpf_nerrs
#define	DST	258
#define	SRC	259
#define	HOST	260
#define	GATEWAY	261
#define	NET	262
#define	NETMASK	263
#define	PORT	264
#define	PORTRANGE	265
#define	LESS	266
#define	GREATER	267
#define	PROTO	268
#define	PROTOCHAIN	269
#define	CBYTE	270
#define	ARP	271
#define	RARP	272
#define	IP	273
#define	SCTP	274
#define	TCP	275
#define	UDP	276
#define	ICMP	277
#define	IGMP	278
#define	IGRP	279
#define	PIM	280
#define	VRRP	281
#define	ATALK	282
#define	AARP	283
#define	DECNET	284
#define	LAT	285
#define	SCA	286
#define	MOPRC	287
#define	MOPDL	288
#define	TK_BROADCAST	289
#define	TK_MULTICAST	290
#define	NUM	291
#define	INBOUND	292
#define	OUTBOUND	293
#define	PF_IFNAME	294
#define	PF_RSET	295
#define	PF_RNR	296
#define	PF_SRNR	297
#define	PF_REASON	298
#define	PF_ACTION	299
#define	TYPE	300
#define	SUBTYPE	301
#define	DIR	302
#define	ADDR1	303
#define	ADDR2	304
#define	ADDR3	305
#define	ADDR4	306
#define	LINK	307
#define	GEQ	308
#define	LEQ	309
#define	NEQ	310
#define	ID	311
#define	EID	312
#define	HID	313
#define	HID6	314
#define	AID	315
#define	LSH	316
#define	RSH	317
#define	LEN	318
#define	IPV6	319
#define	ICMPV6	320
#define	AH	321
#define	ESP	322
#define	VLAN	323
#define	MPLS	324
#define	PPPOED	325
#define	PPPOES	326
#define	ISO	327
#define	ESIS	328
#define	CLNP	329
#define	ISIS	330
#define	L1	331
#define	L2	332
#define	IIH	333
#define	LSP	334
#define	SNP	335
#define	CSNP	336
#define	PSNP	337
#define	STP	338
#define	IPX	339
#define	NETBEUI	340
#define	LANE	341
#define	LLC	342
#define	METAC	343
#define	BCC	344
#define	SC	345
#define	ILMIC	346
#define	OAMF4EC	347
#define	OAMF4SC	348
#define	OAM	349
#define	OAMF4	350
#define	CONNECTMSG	351
#define	METACONNECT	352
#define	VPI	353
#define	VCI	354
#define	RADIO	355
#define	FISU	356
#define	LSSU	357
#define	MSU	358
#define	SIO	359
#define	OPC	360
#define	DPC	361
#define	SLS	362
#define	OR	363
#define	AND	364
#define	UMINUS	365

#line 1 "./grammar.y"

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef lint
static const char rcsid[] =
    "@(#) $Header: /usr/cvsroot/sfeng/ims/src/libraries/daq/daq/sfbpf/grammar.y,v 1.1 2010-04-15 19:18:35 maltizer Exp $ (LBL)";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#if __STDC__
struct mbuf;
struct rtentry;
#endif

#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include "sfbpf-int.h"

#include "gencode.h"
#ifdef HAVE_NET_PFVAR_H
#include <net/if.h>
#include <net/pfvar.h>
#include <net/if_pflog.h>
#endif
#include "ieee80211.h"
#include "namedb.h"

#define QSET(q, p, d, a) (q).proto = (p),\
			 (q).dir = (d),\
			 (q).addr = (a)

struct tok {
	int v;			/* value */
	const char *s;		/* string */
};

static const struct tok ieee80211_types[] = {
	{ IEEE80211_FC0_TYPE_DATA, "data" },
	{ IEEE80211_FC0_TYPE_MGT, "mgt" },
	{ IEEE80211_FC0_TYPE_MGT, "management" },
	{ IEEE80211_FC0_TYPE_CTL, "ctl" },
	{ IEEE80211_FC0_TYPE_CTL, "control" },
	{ 0, NULL }
};
static const struct tok ieee80211_mgt_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assocreq" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assoc-req" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assocresp" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassocreq" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassoc-req" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassocresp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probereq" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probe-req" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "proberesp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "probe-resp" },
	{ IEEE80211_FC0_SUBTYPE_BEACON, "beacon" },
	{ IEEE80211_FC0_SUBTYPE_ATIM, "atim" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassoc" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassociation" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "auth" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "authentication" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauth" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauthentication" },
	{ 0, NULL }
};
static const struct tok ieee80211_ctl_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_PS_POLL, "ps-poll" },
	{ IEEE80211_FC0_SUBTYPE_RTS, "rts" },
	{ IEEE80211_FC0_SUBTYPE_CTS, "cts" },
	{ IEEE80211_FC0_SUBTYPE_ACK, "ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_END, "cf-end" },
	{ IEEE80211_FC0_SUBTYPE_CF_END_ACK, "cf-end-ack" },
	{ 0, NULL }
};
static const struct tok ieee80211_data_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_DATA, "data" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACK, "data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_POLL, "data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACPL, "data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_NODATA, "null" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACK, "cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "cf-poll"  },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_DATA, "qos-data" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACK, "qos-data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_POLL, "qos-data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACPL, "qos-data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA, "qos" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "qos-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "qos-cf-ack-poll" },
	{ 0, NULL }
};
struct type2tok {
	int type;
	const struct tok *tok;
};
static const struct type2tok ieee80211_type_subtypes[] = {
	{ IEEE80211_FC0_TYPE_MGT, ieee80211_mgt_subtypes },
	{ IEEE80211_FC0_TYPE_CTL, ieee80211_ctl_subtypes },
	{ IEEE80211_FC0_TYPE_DATA, ieee80211_data_subtypes },
	{ 0, NULL }
};

static int
str2tok(const char *str, const struct tok *toks)
{
	int i;

	for (i = 0; toks[i].s != NULL; i++) {
		if (sfbpf_strcasecmp(toks[i].s, str) == 0)
			return (toks[i].v);
	}
	return (-1);
}

int n_errors = 0;

static struct qual qerr = { Q_UNDEF, Q_UNDEF, Q_UNDEF, Q_UNDEF };

static void
yyerror(const char *msg)
{
	++n_errors;
	bpf_error("%s", msg);
	/* NOTREACHED */
}

#ifndef YYBISON
int yyparse(void);

int
sfbpf_parse()
{
	return (yyparse());
}
#endif

#ifdef HAVE_NET_PFVAR_H
static int
pfreason_to_num(const char *reason)
{
	const char *reasons[] = PFRES_NAMES;
	int i;

	for (i = 0; reasons[i]; i++) {
		if (sfbpf_strcasecmp(reason, reasons[i]) == 0)
			return (i);
	}
	bpf_error("unknown PF reason");
	/*NOTREACHED*/
}

static int
pfaction_to_num(const char *action)
{
	if (sfbpf_strcasecmp(action, "pass") == 0 ||
	    sfbpf_strcasecmp(action, "accept") == 0)
		return (PF_PASS);
	else if (sfbpf_strcasecmp(action, "drop") == 0 ||
		sfbpf_strcasecmp(action, "block") == 0)
		return (PF_DROP);
#if HAVE_PF_NAT_THROUGH_PF_NORDR
	else if (sfbpf_strcasecmp(action, "rdr") == 0)
		return (PF_RDR);
	else if (sfbpf_strcasecmp(action, "nat") == 0)
		return (PF_NAT);
	else if (sfbpf_strcasecmp(action, "binat") == 0)
		return (PF_BINAT);
	else if (sfbpf_strcasecmp(action, "nordr") == 0)
		return (PF_NORDR);
#endif
	else {
		bpf_error("unknown PF action");
		/*NOTREACHED*/
	}
}
#else /* !HAVE_NET_PFVAR_H */
static int
pfreason_to_num(const char *reason)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}

static int
pfaction_to_num(const char *action)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}
#endif /* HAVE_NET_PFVAR_H */

#line 231 "./grammar.y"
typedef union {
	int i;
	sfbpf_u_int32 h;
	u_char *e;
	char *s;
	struct stmt *stmt;
	struct arth *a;
	struct {
		struct qual q;
		int atmfieldtype;
		int mtp3fieldtype;
		struct block *b;
	} blk;
	struct block *rblk;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		274
#define	YYFLAG		-32768
#define	YYNTBASE	126

#define YYTRANSLATE(x) ((unsigned)(x) <= 365 ? yytranslate[x] : 171)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   110,     2,     2,     2,     2,   112,     2,   119,
   118,   115,   113,     2,   114,     2,   116,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   125,     2,   122,
   121,   120,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   123,     2,   124,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,   111,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   117
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     5,     6,     8,    12,    16,    20,    24,    26,
    28,    30,    32,    36,    38,    42,    46,    48,    52,    54,
    56,    58,    61,    63,    65,    67,    71,    75,    77,    79,
    81,    84,    88,    91,    94,    97,   100,   103,   106,   110,
   112,   116,   120,   122,   124,   126,   129,   131,   134,   136,
   137,   139,   141,   145,   149,   153,   157,   159,   161,   163,
   165,   167,   169,   171,   173,   175,   177,   179,   181,   183,
   185,   187,   189,   191,   193,   195,   197,   199,   201,   203,
   205,   207,   209,   211,   213,   215,   217,   219,   221,   223,
   225,   227,   229,   231,   233,   235,   237,   239,   241,   243,
   245,   247,   249,   251,   254,   257,   260,   263,   268,   270,
   272,   275,   277,   280,   282,   284,   286,   288,   291,   294,
   297,   300,   303,   306,   309,   314,   317,   320,   323,   325,
   327,   329,   331,   333,   335,   337,   339,   341,   343,   345,
   347,   349,   351,   353,   355,   357,   359,   364,   371,   375,
   379,   383,   387,   391,   395,   399,   403,   406,   410,   412,
   414,   416,   418,   420,   422,   424,   428,   430,   432,   434,
   436,   438,   440,   442,   444,   446,   448,   450,   452,   454,
   456,   458,   461,   464,   468,   470,   472,   476,   478,   480,
   482,   484,   486,   488,   490,   492,   495,   498,   502,   504,
   506
};

static const short yyrhs[] = {   127,
   128,     0,   127,     0,     0,   137,     0,   128,   129,   137,
     0,   128,   129,   131,     0,   128,   130,   137,     0,   128,
   130,   131,     0,   109,     0,   108,     0,   132,     0,   159,
     0,   134,   135,   118,     0,    56,     0,    58,   116,    36,
     0,    58,     8,    58,     0,    58,     0,    59,   116,    36,
     0,    59,     0,    57,     0,    60,     0,   133,   131,     0,
   110,     0,   119,     0,   132,     0,   136,   129,   131,     0,
   136,   130,   131,     0,   159,     0,   135,     0,   139,     0,
   133,   137,     0,   140,   141,   142,     0,   140,   141,     0,
   140,   142,     0,   140,    13,     0,   140,    14,     0,   140,
   143,     0,   138,   131,     0,   134,   128,   118,     0,   144,
     0,   156,   154,   156,     0,   156,   155,   156,     0,   145,
     0,   160,     0,   161,     0,   162,   163,     0,   166,     0,
   167,   168,     0,   144,     0,     0,     4,     0,     3,     0,
     4,   108,     3,     0,     3,   108,     4,     0,     4,   109,
     3,     0,     3,   109,     4,     0,    48,     0,    49,     0,
    50,     0,    51,     0,     5,     0,     7,     0,     9,     0,
    10,     0,     6,     0,    52,     0,    18,     0,    16,     0,
    17,     0,    19,     0,    20,     0,    21,     0,    22,     0,
    23,     0,    24,     0,    25,     0,    26,     0,    27,     0,
    28,     0,    29,     0,    30,     0,    31,     0,    33,     0,
    32,     0,    64,     0,    65,     0,    66,     0,    67,     0,
    72,     0,    73,     0,    75,     0,    76,     0,    77,     0,
    78,     0,    79,     0,    80,     0,    82,     0,    81,     0,
    74,     0,    83,     0,    84,     0,    85,     0,   100,     0,
   140,    34,     0,   140,    35,     0,    11,    36,     0,    12,
    36,     0,    15,    36,   158,    36,     0,    37,     0,    38,
     0,    68,   159,     0,    68,     0,    69,   159,     0,    69,
     0,    70,     0,    71,     0,   146,     0,   140,   147,     0,
    39,    56,     0,    40,    56,     0,    41,    36,     0,    42,
    36,     0,    43,   152,     0,    44,   153,     0,    45,   148,
    46,   149,     0,    45,   148,     0,    46,   150,     0,    47,
   151,     0,    36,     0,    56,     0,    36,     0,    56,     0,
    56,     0,    36,     0,    56,     0,    36,     0,    56,     0,
    56,     0,   120,     0,    53,     0,   121,     0,    54,     0,
   122,     0,    55,     0,   159,     0,   157,     0,   144,   123,
   156,   124,     0,   144,   123,   156,   125,    36,   124,     0,
   156,   113,   156,     0,   156,   114,   156,     0,   156,   115,
   156,     0,   156,   116,   156,     0,   156,   112,   156,     0,
   156,   111,   156,     0,   156,    61,   156,     0,   156,    62,
   156,     0,   114,   156,     0,   134,   157,   118,     0,    63,
     0,   112,     0,   111,     0,   122,     0,   120,     0,   121,
     0,    36,     0,   134,   159,   118,     0,    86,     0,    87,
     0,    88,     0,    89,     0,    92,     0,    93,     0,    90,
     0,    91,     0,    94,     0,    95,     0,    96,     0,    97,
     0,    98,     0,    99,     0,   164,     0,   154,    36,     0,
   155,    36,     0,   134,   165,   118,     0,    36,     0,   164,
     0,   165,   130,   164,     0,   101,     0,   102,     0,   103,
     0,   104,     0,   105,     0,   106,     0,   107,     0,   169,
     0,   154,    36,     0,   155,    36,     0,   134,   170,   118,
     0,    36,     0,   169,     0,   170,   130,   169,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   304,   308,   310,   312,   313,   314,   315,   316,   318,   320,
   322,   323,   325,   327,   328,   330,   332,   345,   354,   363,
   372,   381,   383,   385,   387,   388,   389,   391,   393,   395,
   396,   398,   399,   400,   401,   402,   403,   405,   406,   407,
   408,   410,   412,   413,   414,   415,   416,   417,   420,   421,
   424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
   436,   437,   438,   439,   442,   444,   445,   446,   447,   448,
   449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
   459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
   469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
   479,   480,   481,   483,   484,   485,   486,   487,   488,   489,
   490,   491,   492,   493,   494,   495,   496,   497,   500,   501,
   502,   503,   504,   505,   508,   513,   516,   520,   523,   524,
   530,   531,   551,   567,   568,   581,   582,   585,   588,   589,
   590,   592,   593,   594,   596,   597,   599,   600,   601,   602,
   603,   604,   605,   606,   607,   608,   609,   610,   611,   613,
   614,   615,   616,   617,   619,   620,   622,   623,   624,   625,
   626,   627,   628,   629,   631,   632,   633,   634,   637,   638,
   640,   641,   642,   643,   645,   652,   653,   656,   657,   658,
   661,   662,   663,   664,   666,   667,   668,   669,   671,   680,
   681
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DST","SRC",
"HOST","GATEWAY","NET","NETMASK","PORT","PORTRANGE","LESS","GREATER","PROTO",
"PROTOCHAIN","CBYTE","ARP","RARP","IP","SCTP","TCP","UDP","ICMP","IGMP","IGRP",
"PIM","VRRP","ATALK","AARP","DECNET","LAT","SCA","MOPRC","MOPDL","TK_BROADCAST",
"TK_MULTICAST","NUM","INBOUND","OUTBOUND","PF_IFNAME","PF_RSET","PF_RNR","PF_SRNR",
"PF_REASON","PF_ACTION","TYPE","SUBTYPE","DIR","ADDR1","ADDR2","ADDR3","ADDR4",
"LINK","GEQ","LEQ","NEQ","ID","EID","HID","HID6","AID","LSH","RSH","LEN","IPV6",
"ICMPV6","AH","ESP","VLAN","MPLS","PPPOED","PPPOES","ISO","ESIS","CLNP","ISIS",
"L1","L2","IIH","LSP","SNP","CSNP","PSNP","STP","IPX","NETBEUI","LANE","LLC",
"METAC","BCC","SC","ILMIC","OAMF4EC","OAMF4SC","OAM","OAMF4","CONNECTMSG","METACONNECT",
"VPI","VCI","RADIO","FISU","LSSU","MSU","SIO","OPC","DPC","SLS","OR","AND","'!'",
"'|'","'&'","'+'","'-'","'*'","'/'","UMINUS","')'","'('","'>'","'='","'<'","'['",
"']'","':'","prog","null","expr","and","or","id","nid","not","paren","pid","qid",
"term","head","rterm","pqual","dqual","aqual","ndaqual","pname","other","pfvar",
"p80211","type","subtype","type_subtype","dir","reason","action","relop","irelop",
"arth","narth","byteop","pnum","atmtype","atmmultitype","atmfield","atmvalue",
"atmfieldvalue","atmlistvalue","mtp2type","mtp3field","mtp3value","mtp3fieldvalue",
"mtp3listvalue", NULL
};
#endif

static const short yyr1[] = {     0,
   126,   126,   127,   128,   128,   128,   128,   128,   129,   130,
   131,   131,   131,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   133,   134,   135,   135,   135,   136,   136,   137,
   137,   138,   138,   138,   138,   138,   138,   139,   139,   139,
   139,   139,   139,   139,   139,   139,   139,   139,   140,   140,
   141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
   142,   142,   142,   142,   143,   144,   144,   144,   144,   144,
   144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
   144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
   144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
   144,   144,   144,   145,   145,   145,   145,   145,   145,   145,
   145,   145,   145,   145,   145,   145,   145,   145,   146,   146,
   146,   146,   146,   146,   147,   147,   147,   147,   148,   148,
   149,   149,   150,   151,   151,   152,   152,   153,   154,   154,
   154,   155,   155,   155,   156,   156,   157,   157,   157,   157,
   157,   157,   157,   157,   157,   157,   157,   157,   157,   158,
   158,   158,   158,   158,   159,   159,   160,   160,   160,   160,
   160,   160,   160,   160,   161,   161,   161,   161,   162,   162,
   163,   163,   163,   163,   164,   165,   165,   166,   166,   166,
   167,   167,   167,   167,   168,   168,   168,   168,   169,   170,
   170
};

static const short yyr2[] = {     0,
     2,     1,     0,     1,     3,     3,     3,     3,     1,     1,
     1,     1,     3,     1,     3,     3,     1,     3,     1,     1,
     1,     2,     1,     1,     1,     3,     3,     1,     1,     1,
     2,     3,     2,     2,     2,     2,     2,     2,     3,     1,
     3,     3,     1,     1,     1,     2,     1,     2,     1,     0,
     1,     1,     3,     3,     3,     3,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     2,     2,     2,     2,     4,     1,     1,
     2,     1,     2,     1,     1,     1,     1,     2,     2,     2,
     2,     2,     2,     2,     4,     2,     2,     2,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     4,     6,     3,     3,
     3,     3,     3,     3,     3,     3,     2,     3,     1,     1,
     1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     2,     2,     3,     1,     1,     3,     1,     1,     1,
     1,     1,     1,     1,     1,     2,     2,     3,     1,     1,
     3
};

static const short yydefact[] = {     3,
    50,     0,     0,     0,    68,    69,    67,    70,    71,    72,
    73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
    84,    83,   165,   109,   110,     0,     0,     0,     0,     0,
     0,    66,   159,    85,    86,    87,    88,   112,   114,   115,
   116,    89,    90,    99,    91,    92,    93,    94,    95,    96,
    98,    97,   100,   101,   102,   167,   168,   169,   170,   173,
   174,   171,   172,   175,   176,   177,   178,   179,   180,   103,
   188,   189,   190,   191,   192,   193,   194,    23,     0,    24,
     1,    50,    50,     4,     0,    30,     0,    49,    43,   117,
     0,   146,   145,    44,    45,     0,    47,     0,   106,   107,
     0,   119,   120,   121,   122,   136,   137,   123,   138,   124,
     0,   111,   113,     0,     0,   157,    10,     9,    50,    50,
    31,     0,   146,   145,    14,    20,    17,    19,    21,    38,
    11,     0,     0,    12,    52,    51,    61,    65,    62,    63,
    64,    35,    36,   104,   105,     0,     0,     0,    57,    58,
    59,    60,    33,    34,    37,   118,     0,   140,   142,   144,
     0,     0,     0,     0,     0,     0,     0,     0,   139,   141,
   143,     0,     0,   185,     0,     0,     0,    46,   181,   199,
     0,     0,     0,    48,   195,   161,   160,   163,   164,   162,
     0,     0,     0,     6,    50,    50,     5,   145,     8,     7,
    39,   158,   166,     0,     0,     0,    22,    25,    29,     0,
    28,     0,     0,     0,     0,   129,   130,   126,   133,   127,
   134,   135,   128,    32,     0,   155,   156,   154,   153,   149,
   150,   151,   152,    41,    42,   186,     0,   182,   183,   200,
     0,   196,   197,   108,   145,    16,    15,    18,    13,     0,
     0,    54,    56,    53,    55,     0,   147,     0,   184,     0,
   198,     0,    26,    27,   131,   132,   125,     0,   187,   201,
   148,     0,     0,     0
};

static const short yydefgoto[] = {   272,
     1,   122,   119,   120,   207,   131,   132,   114,   209,   210,
    84,    85,    86,    87,   153,   154,   155,   115,    89,    90,
   156,   218,   267,   220,   223,   108,   110,   172,   173,    91,
    92,   191,    93,    94,    95,    96,   178,   179,   237,    97,
    98,   184,   185,   241
};

static const short yypact[] = {-32768,
   215,   -19,   -13,   -11,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   -24,    -3,    38,    47,   -23,
    46,-32768,-32768,-32768,-32768,-32768,-32768,   -25,   -25,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   529,-32768,
   -52,   425,   425,-32768,   -14,-32768,   617,    12,-32768,-32768,
   524,-32768,-32768,-32768,-32768,   101,-32768,   143,-32768,-32768,
    -8,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   -25,-32768,-32768,   529,    16,-32768,-32768,-32768,   320,   320,
-32768,   -47,     4,    30,-32768,-32768,    -5,    33,-32768,-32768,
-32768,   -14,   -14,-32768,   -49,   -33,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   -22,    94,    -9,-32768,-32768,
-32768,-32768,   163,-32768,-32768,-32768,   529,-32768,-32768,-32768,
   529,   529,   529,   529,   529,   529,   529,   529,-32768,-32768,
-32768,   529,   529,-32768,   117,   123,   124,-32768,-32768,-32768,
   127,   128,   129,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   133,    30,    72,-32768,   320,   320,-32768,    20,-32768,-32768,
-32768,-32768,-32768,   113,   142,   144,-32768,-32768,    63,   -52,
    30,   178,   185,   187,   188,-32768,-32768,   146,-32768,-32768,
-32768,-32768,-32768,-32768,   -46,    61,    61,    96,    -7,     1,
     1,-32768,-32768,    72,    72,-32768,   -90,-32768,-32768,-32768,
   -17,-32768,-32768,-32768,   -45,-32768,-32768,-32768,-32768,   -14,
   -14,-32768,-32768,-32768,-32768,    -6,-32768,   157,-32768,   117,
-32768,   127,-32768,-32768,-32768,-32768,-32768,    75,-32768,-32768,
-32768,   204,   205,-32768
};

static const short yypgoto[] = {-32768,
-32768,   206,    -4,  -189,   -84,  -124,     5,    -1,-32768,-32768,
   -80,-32768,-32768,-32768,-32768,    60,-32768,     7,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -72,   -67,   -21,
   -73,-32768,   -34,-32768,-32768,-32768,-32768,  -168,-32768,-32768,
-32768,-32768,  -162,-32768
};


#define	YYLAST		668


static const short yytable[] = {    83,
   130,   121,   204,   112,   113,    82,   236,    88,   208,   123,
    23,   -40,   106,   216,   161,   162,    99,   117,   240,   -12,
   251,    23,   100,   176,   101,   182,   221,   259,   177,   265,
   183,   102,   107,   217,   194,   199,   111,   111,   197,   200,
   123,   125,   126,   127,   128,   129,   222,   260,   124,   266,
   134,   262,   103,   161,   162,   117,   118,   116,   212,   213,
   117,   118,   -28,   -28,   163,   164,   165,   166,   167,   168,
   201,   208,   203,   104,   214,   215,   192,   257,   258,   124,
    83,    83,   105,   133,   198,   198,    82,    82,    88,    88,
   117,   269,   193,    80,   175,    78,   181,   134,   211,   270,
   261,   109,   186,   187,    80,   165,   166,   167,   168,   111,
   205,   188,   189,   190,   121,   167,   168,   196,   196,   -40,
   -40,   202,   123,   195,   195,    88,    88,   -12,   -12,   -40,
   133,   111,   161,   162,   157,   225,   174,   -12,   157,   226,
   227,   228,   229,   230,   231,   232,   233,   203,   206,   219,
   234,   235,   174,   158,   159,   160,   161,   162,   238,   239,
   198,   245,   180,   242,   243,   263,   264,   137,   244,   139,
   246,   140,   141,   165,   166,   167,   168,   247,   180,   248,
   249,   252,   163,   164,   165,   166,   167,   168,   253,   254,
   255,   256,   268,   196,    83,   158,   159,   160,   271,   195,
   195,    88,    88,   273,   274,   250,    81,   164,   165,   166,
   167,   168,   224,     0,    -2,   134,   134,     0,     0,    80,
   169,   170,   171,     0,     0,     2,     3,     0,     0,     4,
     5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,   133,   133,
    23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
     0,    80,   169,   170,   171,     0,    32,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,     0,     0,    78,     0,     0,     0,    79,     0,
     2,     3,     0,    80,     4,     5,     6,     7,     8,     9,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,    21,    22,     0,     0,    23,    24,    25,    26,    27,
    28,    29,    30,    31,     0,     0,     0,     0,     0,     0,
     0,    32,     0,     0,     0,   125,   126,   127,   128,   129,
     0,     0,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
     0,     0,     0,    79,     0,     2,     3,     0,    80,     4,
     5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,     0,     0,
    23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
     0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,     0,     0,    78,     0,     0,     0,    79,     0,
     0,     0,     0,    80,     5,     6,     7,     8,     9,    10,
    11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
    21,    22,     0,     0,    23,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   158,   159,   160,     0,
    32,     0,     0,     0,   161,   162,     0,     0,     0,     0,
     0,    33,    34,    35,    36,    37,     0,     0,     0,     0,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,     0,     0,     0,     0,     0,   135,
   136,   137,   138,   139,     0,   140,   141,     0,    70,   142,
   143,     0,     0,     0,   163,   164,   165,   166,   167,   168,
     0,     0,    79,   169,   170,   171,     0,    80,     0,     0,
   144,   145,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   146,   147,   148,   149,   150,   151,   152
};

static const short yycheck[] = {     1,
    85,    82,     8,    38,    39,     1,   175,     1,   133,    83,
    36,     0,    36,    36,    61,    62,    36,   108,   181,     0,
   210,    36,    36,    96,    36,    98,    36,   118,    96,    36,
    98,    56,    56,    56,   119,   120,    38,    39,   119,   120,
   114,    56,    57,    58,    59,    60,    56,   237,    83,    56,
    85,   241,    56,    61,    62,   108,   109,    79,   108,   109,
   108,   109,   108,   109,   111,   112,   113,   114,   115,   116,
   118,   196,   118,    36,   108,   109,   111,   124,   125,   114,
    82,    83,    36,    85,   119,   120,    82,    83,    82,    83,
   108,   260,   114,   119,    96,   110,    98,   132,   133,   262,
   118,    56,   111,   112,   119,   113,   114,   115,   116,   111,
   116,   120,   121,   122,   195,   115,   116,   119,   120,   108,
   109,   118,   196,   119,   120,   119,   120,   108,   109,   118,
   132,   133,    61,    62,   123,   157,    36,   118,   123,   161,
   162,   163,   164,   165,   166,   167,   168,   118,   116,    56,
   172,   173,    36,    53,    54,    55,    61,    62,    36,    36,
   195,   196,    36,    36,    36,   250,   251,     5,    36,     7,
    58,     9,    10,   113,   114,   115,   116,    36,    36,    36,
   118,     4,   111,   112,   113,   114,   115,   116,     4,     3,
     3,    46,    36,   195,   196,    53,    54,    55,   124,   195,
   196,   195,   196,     0,     0,   210,     1,   112,   113,   114,
   115,   116,   153,    -1,     0,   250,   251,    -1,    -1,   119,
   120,   121,   122,    -1,    -1,    11,    12,    -1,    -1,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,   250,   251,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
    -1,   119,   120,   121,   122,    -1,    52,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,
    11,    12,    -1,   119,    15,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
    31,    32,    33,    -1,    -1,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    52,    -1,    -1,    -1,    56,    57,    58,    59,    60,
    -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
   101,   102,   103,   104,   105,   106,   107,    -1,    -1,   110,
    -1,    -1,    -1,   114,    -1,    11,    12,    -1,   119,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,    -1,    -1,   110,    -1,    -1,    -1,   114,    -1,
    -1,    -1,    -1,   119,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
    32,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,
    52,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
    72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,     3,
     4,     5,     6,     7,    -1,     9,    10,    -1,   100,    13,
    14,    -1,    -1,    -1,   111,   112,   113,   114,   115,   116,
    -1,    -1,   114,   120,   121,   122,    -1,   119,    -1,    -1,
    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    45,    46,    47,    48,    49,    50,    51
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 305 "./grammar.y"
{
	finish_parse(yyvsp[0].blk.b);
;
    break;}
case 3:
#line 310 "./grammar.y"
{ yyval.blk.q = qerr; ;
    break;}
case 5:
#line 313 "./grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 6:
#line 314 "./grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 7:
#line 315 "./grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 8:
#line 316 "./grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 9:
#line 318 "./grammar.y"
{ yyval.blk = yyvsp[-1].blk; ;
    break;}
case 10:
#line 320 "./grammar.y"
{ yyval.blk = yyvsp[-1].blk; ;
    break;}
case 12:
#line 323 "./grammar.y"
{ yyval.blk.b = gen_ncode(NULL, (sfbpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); ;
    break;}
case 13:
#line 325 "./grammar.y"
{ yyval.blk = yyvsp[-1].blk; ;
    break;}
case 14:
#line 327 "./grammar.y"
{ yyval.blk.b = gen_scode(yyvsp[0].s, yyval.blk.q = yyvsp[-1].blk.q); ;
    break;}
case 15:
#line 328 "./grammar.y"
{ yyval.blk.b = gen_mcode(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q); ;
    break;}
case 16:
#line 330 "./grammar.y"
{ yyval.blk.b = gen_mcode(yyvsp[-2].s, yyvsp[0].s, 0,
				    yyval.blk.q = yyvsp[-3].blk.q); ;
    break;}
case 17:
#line 332 "./grammar.y"
{
				  /* Decide how to parse HID based on proto */
				  yyval.blk.q = yyvsp[-1].blk.q;
				  if (yyval.blk.q.addr == Q_PORT)
				  	bpf_error("'port' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PORTRANGE)
				  	bpf_error("'portrange' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PROTO)
				  	bpf_error("'proto' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PROTOCHAIN)
				  	bpf_error("'protochain' modifier applied to ip host");
				  yyval.blk.b = gen_ncode(yyvsp[0].s, 0, yyval.blk.q);
				;
    break;}
case 18:
#line 345 "./grammar.y"
{
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q);
#else
				  bpf_error("'ip6addr/prefixlen' not supported "
					"in this configuration");
#endif /*INET6*/
				;
    break;}
case 19:
#line 354 "./grammar.y"
{
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[0].s, 0, 128,
				    yyval.blk.q = yyvsp[-1].blk.q);
#else
				  bpf_error("'ip6addr' not supported "
					"in this configuration");
#endif /*INET6*/
				;
    break;}
case 20:
#line 363 "./grammar.y"
{ 
				  yyval.blk.b = gen_ecode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				;
    break;}
case 21:
#line 372 "./grammar.y"
{
				  yyval.blk.b = gen_acode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				;
    break;}
case 22:
#line 381 "./grammar.y"
{ gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 23:
#line 383 "./grammar.y"
{ yyval.blk = yyvsp[-1].blk; ;
    break;}
case 24:
#line 385 "./grammar.y"
{ yyval.blk = yyvsp[-1].blk; ;
    break;}
case 26:
#line 388 "./grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 27:
#line 389 "./grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 28:
#line 391 "./grammar.y"
{ yyval.blk.b = gen_ncode(NULL, (sfbpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); ;
    break;}
case 31:
#line 396 "./grammar.y"
{ gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 32:
#line 398 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i); ;
    break;}
case 33:
#line 399 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, yyvsp[0].i, Q_DEFAULT); ;
    break;}
case 34:
#line 400 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); ;
    break;}
case 35:
#line 401 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTO); ;
    break;}
case 36:
#line 402 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTOCHAIN); ;
    break;}
case 37:
#line 403 "./grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); ;
    break;}
case 38:
#line 405 "./grammar.y"
{ yyval.blk = yyvsp[0].blk; ;
    break;}
case 39:
#line 406 "./grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = yyvsp[-2].blk.q; ;
    break;}
case 40:
#line 407 "./grammar.y"
{ yyval.blk.b = gen_proto_abbrev(yyvsp[0].i); yyval.blk.q = qerr; ;
    break;}
case 41:
#line 408 "./grammar.y"
{ yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 0);
				  yyval.blk.q = qerr; ;
    break;}
case 42:
#line 410 "./grammar.y"
{ yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 1);
				  yyval.blk.q = qerr; ;
    break;}
case 43:
#line 412 "./grammar.y"
{ yyval.blk.b = yyvsp[0].rblk; yyval.blk.q = qerr; ;
    break;}
case 44:
#line 413 "./grammar.y"
{ yyval.blk.b = gen_atmtype_abbrev(yyvsp[0].i); yyval.blk.q = qerr; ;
    break;}
case 45:
#line 414 "./grammar.y"
{ yyval.blk.b = gen_atmmulti_abbrev(yyvsp[0].i); yyval.blk.q = qerr; ;
    break;}
case 46:
#line 415 "./grammar.y"
{ yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; ;
    break;}
case 47:
#line 416 "./grammar.y"
{ yyval.blk.b = gen_mtp2type_abbrev(yyvsp[0].i); yyval.blk.q = qerr; ;
    break;}
case 48:
#line 417 "./grammar.y"
{ yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; ;
    break;}
case 50:
#line 421 "./grammar.y"
{ yyval.i = Q_DEFAULT; ;
    break;}
case 51:
#line 424 "./grammar.y"
{ yyval.i = Q_SRC; ;
    break;}
case 52:
#line 425 "./grammar.y"
{ yyval.i = Q_DST; ;
    break;}
case 53:
#line 426 "./grammar.y"
{ yyval.i = Q_OR; ;
    break;}
case 54:
#line 427 "./grammar.y"
{ yyval.i = Q_OR; ;
    break;}
case 55:
#line 428 "./grammar.y"
{ yyval.i = Q_AND; ;
    break;}
case 56:
#line 429 "./grammar.y"
{ yyval.i = Q_AND; ;
    break;}
case 57:
#line 430 "./grammar.y"
{ yyval.i = Q_ADDR1; ;
    break;}
case 58:
#line 431 "./grammar.y"
{ yyval.i = Q_ADDR2; ;
    break;}
case 59:
#line 432 "./grammar.y"
{ yyval.i = Q_ADDR3; ;
    break;}
case 60:
#line 433 "./grammar.y"
{ yyval.i = Q_ADDR4; ;
    break;}
case 61:
#line 436 "./grammar.y"
{ yyval.i = Q_HOST; ;
    break;}
case 62:
#line 437 "./grammar.y"
{ yyval.i = Q_NET; ;
    break;}
case 63:
#line 438 "./grammar.y"
{ yyval.i = Q_PORT; ;
    break;}
case 64:
#line 439 "./grammar.y"
{ yyval.i = Q_PORTRANGE; ;
    break;}
case 65:
#line 442 "./grammar.y"
{ yyval.i = Q_GATEWAY; ;
    break;}
case 66:
#line 444 "./grammar.y"
{ yyval.i = Q_LINK; ;
    break;}
case 67:
#line 445 "./grammar.y"
{ yyval.i = Q_IP; ;
    break;}
case 68:
#line 446 "./grammar.y"
{ yyval.i = Q_ARP; ;
    break;}
case 69:
#line 447 "./grammar.y"
{ yyval.i = Q_RARP; ;
    break;}
case 70:
#line 448 "./grammar.y"
{ yyval.i = Q_SCTP; ;
    break;}
case 71:
#line 449 "./grammar.y"
{ yyval.i = Q_TCP; ;
    break;}
case 72:
#line 450 "./grammar.y"
{ yyval.i = Q_UDP; ;
    break;}
case 73:
#line 451 "./grammar.y"
{ yyval.i = Q_ICMP; ;
    break;}
case 74:
#line 452 "./grammar.y"
{ yyval.i = Q_IGMP; ;
    break;}
case 75:
#line 453 "./grammar.y"
{ yyval.i = Q_IGRP; ;
    break;}
case 76:
#line 454 "./grammar.y"
{ yyval.i = Q_PIM; ;
    break;}
case 77:
#line 455 "./grammar.y"
{ yyval.i = Q_VRRP; ;
    break;}
case 78:
#line 456 "./grammar.y"
{ yyval.i = Q_ATALK; ;
    break;}
case 79:
#line 457 "./grammar.y"
{ yyval.i = Q_AARP; ;
    break;}
case 80:
#line 458 "./grammar.y"
{ yyval.i = Q_DECNET; ;
    break;}
case 81:
#line 459 "./grammar.y"
{ yyval.i = Q_LAT; ;
    break;}
case 82:
#line 460 "./grammar.y"
{ yyval.i = Q_SCA; ;
    break;}
case 83:
#line 461 "./grammar.y"
{ yyval.i = Q_MOPDL; ;
    break;}
case 84:
#line 462 "./grammar.y"
{ yyval.i = Q_MOPRC; ;
    break;}
case 85:
#line 463 "./grammar.y"
{ yyval.i = Q_IPV6; ;
    break;}
case 86:
#line 464 "./grammar.y"
{ yyval.i = Q_ICMPV6; ;
    break;}
case 87:
#line 465 "./grammar.y"
{ yyval.i = Q_AH; ;
    break;}
case 88:
#line 466 "./grammar.y"
{ yyval.i = Q_ESP; ;
    break;}
case 89:
#line 467 "./grammar.y"
{ yyval.i = Q_ISO; ;
    break;}
case 90:
#line 468 "./grammar.y"
{ yyval.i = Q_ESIS; ;
    break;}
case 91:
#line 469 "./grammar.y"
{ yyval.i = Q_ISIS; ;
    break;}
case 92:
#line 470 "./grammar.y"
{ yyval.i = Q_ISIS_L1; ;
    break;}
case 93:
#line 471 "./grammar.y"
{ yyval.i = Q_ISIS_L2; ;
    break;}
case 94:
#line 472 "./grammar.y"
{ yyval.i = Q_ISIS_IIH; ;
    break;}
case 95:
#line 473 "./grammar.y"
{ yyval.i = Q_ISIS_LSP; ;
    break;}
case 96:
#line 474 "./grammar.y"
{ yyval.i = Q_ISIS_SNP; ;
    break;}
case 97:
#line 475 "./grammar.y"
{ yyval.i = Q_ISIS_PSNP; ;
    break;}
case 98:
#line 476 "./grammar.y"
{ yyval.i = Q_ISIS_CSNP; ;
    break;}
case 99:
#line 477 "./grammar.y"
{ yyval.i = Q_CLNP; ;
    break;}
case 100:
#line 478 "./grammar.y"
{ yyval.i = Q_STP; ;
    break;}
case 101:
#line 479 "./grammar.y"
{ yyval.i = Q_IPX; ;
    break;}
case 102:
#line 480 "./grammar.y"
{ yyval.i = Q_NETBEUI; ;
    break;}
case 103:
#line 481 "./grammar.y"
{ yyval.i = Q_RADIO; ;
    break;}
case 104:
#line 483 "./grammar.y"
{ yyval.rblk = gen_broadcast(yyvsp[-1].i); ;
    break;}
case 105:
#line 484 "./grammar.y"
{ yyval.rblk = gen_multicast(yyvsp[-1].i); ;
    break;}
case 106:
#line 485 "./grammar.y"
{ yyval.rblk = gen_less(yyvsp[0].i); ;
    break;}
case 107:
#line 486 "./grammar.y"
{ yyval.rblk = gen_greater(yyvsp[0].i); ;
    break;}
case 108:
#line 487 "./grammar.y"
{ yyval.rblk = gen_byteop(yyvsp[-1].i, yyvsp[-2].i, yyvsp[0].i); ;
    break;}
case 109:
#line 488 "./grammar.y"
{ yyval.rblk = gen_inbound(0); ;
    break;}
case 110:
#line 489 "./grammar.y"
{ yyval.rblk = gen_inbound(1); ;
    break;}
case 111:
#line 490 "./grammar.y"
{ yyval.rblk = gen_vlan(yyvsp[0].i); ;
    break;}
case 112:
#line 491 "./grammar.y"
{ yyval.rblk = gen_vlan(-1); ;
    break;}
case 113:
#line 492 "./grammar.y"
{ yyval.rblk = gen_mpls(yyvsp[0].i); ;
    break;}
case 114:
#line 493 "./grammar.y"
{ yyval.rblk = gen_mpls(-1); ;
    break;}
case 115:
#line 494 "./grammar.y"
{ yyval.rblk = gen_pppoed(); ;
    break;}
case 116:
#line 495 "./grammar.y"
{ yyval.rblk = gen_pppoes(); ;
    break;}
case 117:
#line 496 "./grammar.y"
{ yyval.rblk = yyvsp[0].rblk; ;
    break;}
case 118:
#line 497 "./grammar.y"
{ yyval.rblk = yyvsp[0].rblk; ;
    break;}
case 119:
#line 500 "./grammar.y"
{ yyval.rblk = gen_pf_ifname(yyvsp[0].s); ;
    break;}
case 120:
#line 501 "./grammar.y"
{ yyval.rblk = gen_pf_ruleset(yyvsp[0].s); ;
    break;}
case 121:
#line 502 "./grammar.y"
{ yyval.rblk = gen_pf_rnr(yyvsp[0].i); ;
    break;}
case 122:
#line 503 "./grammar.y"
{ yyval.rblk = gen_pf_srnr(yyvsp[0].i); ;
    break;}
case 123:
#line 504 "./grammar.y"
{ yyval.rblk = gen_pf_reason(yyvsp[0].i); ;
    break;}
case 124:
#line 505 "./grammar.y"
{ yyval.rblk = gen_pf_action(yyvsp[0].i); ;
    break;}
case 125:
#line 509 "./grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[-2].i | yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				;
    break;}
case 126:
#line 513 "./grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK);
				;
    break;}
case 127:
#line 516 "./grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				;
    break;}
case 128:
#line 520 "./grammar.y"
{ yyval.rblk = gen_p80211_fcdir(yyvsp[0].i); ;
    break;}
case 130:
#line 524 "./grammar.y"
{ yyval.i = str2tok(yyvsp[0].s, ieee80211_types);
				  if (yyval.i == -1)
				  	bpf_error("unknown 802.11 type name");
				;
    break;}
case 132:
#line 531 "./grammar.y"
{ const struct tok *types = NULL;
				  int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type");
						break;
					}
					if (yyvsp[-2].i == ieee80211_type_subtypes[i].type) {
						types = ieee80211_type_subtypes[i].tok;
						break;
					}
				  }

				  yyval.i = str2tok(yyvsp[0].s, types);
				  if (yyval.i == -1)
					bpf_error("unknown 802.11 subtype name");
				;
    break;}
case 133:
#line 551 "./grammar.y"
{ int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type name");
						break;
					}
					yyval.i = str2tok(yyvsp[0].s, ieee80211_type_subtypes[i].tok);
					if (yyval.i != -1) {
						yyval.i |= ieee80211_type_subtypes[i].type;
						break;
					}
				  }
				;
    break;}
case 135:
#line 568 "./grammar.y"
{ if (sfbpf_strcasecmp(yyvsp[0].s, "nods") == 0)
					yyval.i = IEEE80211_FC1_DIR_NODS;
				  else if (sfbpf_strcasecmp(yyvsp[0].s, "tods") == 0)
					yyval.i = IEEE80211_FC1_DIR_TODS;
				  else if (sfbpf_strcasecmp(yyvsp[0].s, "fromds") == 0)
					yyval.i = IEEE80211_FC1_DIR_FROMDS;
				  else if (sfbpf_strcasecmp(yyvsp[0].s, "dstods") == 0)
					yyval.i = IEEE80211_FC1_DIR_DSTODS;
				  else
					bpf_error("unknown 802.11 direction");
				;
    break;}
case 136:
#line 581 "./grammar.y"
{ yyval.i = yyvsp[0].i; ;
    break;}
case 137:
#line 582 "./grammar.y"
{ yyval.i = pfreason_to_num(yyvsp[0].s); ;
    break;}
case 138:
#line 585 "./grammar.y"
{ yyval.i = pfaction_to_num(yyvsp[0].s); ;
    break;}
case 139:
#line 588 "./grammar.y"
{ yyval.i = SFBPF_JGT; ;
    break;}
case 140:
#line 589 "./grammar.y"
{ yyval.i = SFBPF_JGE; ;
    break;}
case 141:
#line 590 "./grammar.y"
{ yyval.i = SFBPF_JEQ; ;
    break;}
case 142:
#line 592 "./grammar.y"
{ yyval.i = SFBPF_JGT; ;
    break;}
case 143:
#line 593 "./grammar.y"
{ yyval.i = SFBPF_JGE; ;
    break;}
case 144:
#line 594 "./grammar.y"
{ yyval.i = SFBPF_JEQ; ;
    break;}
case 145:
#line 596 "./grammar.y"
{ yyval.a = gen_loadi(yyvsp[0].i); ;
    break;}
case 147:
#line 599 "./grammar.y"
{ yyval.a = gen_load(yyvsp[-3].i, yyvsp[-1].a, 1); ;
    break;}
case 148:
#line 600 "./grammar.y"
{ yyval.a = gen_load(yyvsp[-5].i, yyvsp[-3].a, yyvsp[-1].i); ;
    break;}
case 149:
#line 601 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_ADD, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 150:
#line 602 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_SUB, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 151:
#line 603 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_MUL, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 152:
#line 604 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_DIV, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 153:
#line 605 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_AND, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 154:
#line 606 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_OR, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 155:
#line 607 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_LSH, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 156:
#line 608 "./grammar.y"
{ yyval.a = gen_arth(SFBPF_RSH, yyvsp[-2].a, yyvsp[0].a); ;
    break;}
case 157:
#line 609 "./grammar.y"
{ yyval.a = gen_neg(yyvsp[0].a); ;
    break;}
case 158:
#line 610 "./grammar.y"
{ yyval.a = yyvsp[-1].a; ;
    break;}
case 159:
#line 611 "./grammar.y"
{ yyval.a = gen_loadlen(); ;
    break;}
case 160:
#line 613 "./grammar.y"
{ yyval.i = '&'; ;
    break;}
case 161:
#line 614 "./grammar.y"
{ yyval.i = '|'; ;
    break;}
case 162:
#line 615 "./grammar.y"
{ yyval.i = '<'; ;
    break;}
case 163:
#line 616 "./grammar.y"
{ yyval.i = '>'; ;
    break;}
case 164:
#line 617 "./grammar.y"
{ yyval.i = '='; ;
    break;}
case 166:
#line 620 "./grammar.y"
{ yyval.i = yyvsp[-1].i; ;
    break;}
case 167:
#line 622 "./grammar.y"
{ yyval.i = A_LANE; ;
    break;}
case 168:
#line 623 "./grammar.y"
{ yyval.i = A_LLC; ;
    break;}
case 169:
#line 624 "./grammar.y"
{ yyval.i = A_METAC;	;
    break;}
case 170:
#line 625 "./grammar.y"
{ yyval.i = A_BCC; ;
    break;}
case 171:
#line 626 "./grammar.y"
{ yyval.i = A_OAMF4EC; ;
    break;}
case 172:
#line 627 "./grammar.y"
{ yyval.i = A_OAMF4SC; ;
    break;}
case 173:
#line 628 "./grammar.y"
{ yyval.i = A_SC; ;
    break;}
case 174:
#line 629 "./grammar.y"
{ yyval.i = A_ILMIC; ;
    break;}
case 175:
#line 631 "./grammar.y"
{ yyval.i = A_OAM; ;
    break;}
case 176:
#line 632 "./grammar.y"
{ yyval.i = A_OAMF4; ;
    break;}
case 177:
#line 633 "./grammar.y"
{ yyval.i = A_CONNECTMSG; ;
    break;}
case 178:
#line 634 "./grammar.y"
{ yyval.i = A_METACONNECT; ;
    break;}
case 179:
#line 637 "./grammar.y"
{ yyval.blk.atmfieldtype = A_VPI; ;
    break;}
case 180:
#line 638 "./grammar.y"
{ yyval.blk.atmfieldtype = A_VCI; ;
    break;}
case 182:
#line 641 "./grammar.y"
{ yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (sfbpf_int32)yyvsp[0].i, (sfbpf_u_int32)yyvsp[-1].i, 0); ;
    break;}
case 183:
#line 642 "./grammar.y"
{ yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (sfbpf_int32)yyvsp[0].i, (sfbpf_u_int32)yyvsp[-1].i, 1); ;
    break;}
case 184:
#line 643 "./grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; ;
    break;}
case 185:
#line 645 "./grammar.y"
{
	yyval.blk.atmfieldtype = yyvsp[-1].blk.atmfieldtype;
	if (yyval.blk.atmfieldtype == A_VPI ||
	    yyval.blk.atmfieldtype == A_VCI)
		yyval.blk.b = gen_atmfield_code(yyval.blk.atmfieldtype, (sfbpf_int32) yyvsp[0].i, SFBPF_JEQ, 0);
	;
    break;}
case 187:
#line 653 "./grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
case 188:
#line 656 "./grammar.y"
{ yyval.i = M_FISU; ;
    break;}
case 189:
#line 657 "./grammar.y"
{ yyval.i = M_LSSU; ;
    break;}
case 190:
#line 658 "./grammar.y"
{ yyval.i = M_MSU; ;
    break;}
case 191:
#line 661 "./grammar.y"
{ yyval.blk.mtp3fieldtype = M_SIO; ;
    break;}
case 192:
#line 662 "./grammar.y"
{ yyval.blk.mtp3fieldtype = M_OPC; ;
    break;}
case 193:
#line 663 "./grammar.y"
{ yyval.blk.mtp3fieldtype = M_DPC; ;
    break;}
case 194:
#line 664 "./grammar.y"
{ yyval.blk.mtp3fieldtype = M_SLS; ;
    break;}
case 196:
#line 667 "./grammar.y"
{ yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 0); ;
    break;}
case 197:
#line 668 "./grammar.y"
{ yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 1); ;
    break;}
case 198:
#line 669 "./grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; ;
    break;}
case 199:
#line 671 "./grammar.y"
{
	yyval.blk.mtp3fieldtype = yyvsp[-1].blk.mtp3fieldtype;
	if (yyval.blk.mtp3fieldtype == M_SIO ||
	    yyval.blk.mtp3fieldtype == M_OPC ||
	    yyval.blk.mtp3fieldtype == M_DPC ||
	    yyval.blk.mtp3fieldtype == M_SLS )
		yyval.blk.b = gen_mtp3field_code(yyval.blk.mtp3fieldtype, (u_int) yyvsp[0].i, SFBPF_JEQ, 0);
	;
    break;}
case 201:
#line 681 "./grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 683 "./grammar.y"

