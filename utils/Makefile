CC = icc
AR = xiar
LD = icc

CFLAGS = -std=c++11 -ipo -O3 -no-prec-div -xHost
GSLLIB = -L$(TACC_GSL_LIB) -lgsl -lgslcblas
GSLINC = -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/inc
INC = -I../src

all: gridcalc galcatbingen
gridcalc: gridcalc.cpp
	$(CC) $(CFLAGS) $(INC) $(GSLINC) $(GSLLIB) gridcalc.cpp ../src/standalone/triaxUTD.a -o gridcalc
galcatbingen:
	$(CC) $(CFLAGS) $(INC) galcatbingen.cpp -o galcatbingen
clean:
	rm -rf gridcalc galcatbingen

.PHONY: all clean
