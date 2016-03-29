CUDA_DIR=/usr/local/cuda-7.5
CUDA_BIN_DIR=$(CUDA_DIR)/bin
CUDA_LIB_DIR=$(CUDA_DIR)/lib64
NVCC=$(CUDA_BIN_DIR)/nvcc

.PHONY: all clean

all: random

%.o: %.cu random.h
	$(NVCC) -c $<

random: random.o main.o
	$(NVCC) $^ -o $@

clean:
	rm -f random *.o
