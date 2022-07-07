from ctypes import cdll
lib = cdll.LoadLibrary('./libtestfunctions.so')

lib.fake_sum(3, 4);
