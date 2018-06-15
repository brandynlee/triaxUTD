CC = icc
AR = xiar
TARGET = triaxUTD.a

CFLAGS = -std=c++11 -ipo -O3 -no-prec-div -xHost -DWITH_MPI=0
FFLAGS =
INC = -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/inc
C_SRCS = common.cpp constants.cpp LensModel.cpp sphNFW.cpp triaxNFW.cpp
OBJS = $(patsubst %.cpp,%.o,$(C_SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(AR) rc $@ $^
%.o: ../%.cpp
	$(CC) $(CFLAGS) $(INC) -c $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean
