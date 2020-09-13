#!/usr/bin/make
# Makefile, Boone, 09/13/20
# Build ninotnc_setserialno
#
# Modifications:
# 09/13/20 Boone      Initial coding
# End Modifications

ninotnc_setserialno:	ninotnc_setserialno.c
	cc -g -I/usr/local/include -c ninotnc_setserialno.c
	cc -L/usr/local/lib -o ninotnc_setserialno ninotnc_setserialno.o -lmcp2221 -lhidapi-hidraw -ludev
