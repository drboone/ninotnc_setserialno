#!/usr/bin/make
# Makefile, Boone, 09/13/20
# Build ninotnc_setserialno
#
# Modifications:
# 09/13/20 Boone      Initial coding
# End Modifications

all:	ninotnc_setserialno ninotnc_setlabel

ninotnc_setserialno:	ninotnc_setserialno.c
	cc -g -I/usr/local/include -c ninotnc_setserialno.c
	cc -L/usr/local/lib -o ninotnc_setserialno ninotnc_setserialno.o -lmcp2221 -lhidapi-hidraw -ludev

ninotnc_setlabel:	ninotnc_setlabel.c
	cc -g -I/usr/local/include -c ninotnc_setlabel.c
	cc -L/usr/local/lib -o ninotnc_setlabel ninotnc_setlabel.o -lmcp2221 -lhidapi-hidraw -ludev
