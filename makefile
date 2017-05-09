# LIB = -L/opt/vc/lib 
# INC=-I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux
# LIBSO =-lbcm_host -lvcos -lmmal -lmmal_core -lmmal_util -lrt -lpigpio

# libe101: start.o camera.o cameracontrol.o
# 	g++ -shared -o libe101.so start.o camera.o cameracontrol.o $(LIB) $(LIBSO)
# 
output:main.cpp
	g++ -Wall -o output "main.cpp" -leE101
