CUDA_DIR=/usr/local/cuda
CUDA_BIN_DIR=$(CUDA_DIR)/bin
CUDA_LIB_DIR=$(CUDA_DIR)/lib64
CFLAGS=-Wall
NVCC=$(CUDA_BIN_DIR)/nvcc --compiler-options $(CFLAGS)

OBJECTS=main.o random.o cuda_utils.o
HEADERS=random.h warpspeed.h

.PHONY: all clean

all: random

%.o: %.cu $(HEADERS)
	$(NVCC) -o $@ -c $<

random: $(OBJECTS)
	$(NVCC) $^ -o $@

clean:
	rm -f random *.o
