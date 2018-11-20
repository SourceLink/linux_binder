APPS = service_manager test_client led_control_server

all : $(APPS)

service_manager : service_manager.o binder.o
	arm-linux-gcc -o $@ $^ -lpthread

test_client : test_client.o binder.o
	arm-linux-gcc -o $@ $^ -lpthread

led_control_server: led_control_server.o binder.o
	arm-linux-gcc -o $@ $^ -L ./ -lpthread -lslhl

%.o : %.c 
	arm-linux-gcc -DBINDER_IPC_32BIT=1 -I include -c -o $@ $< -Wall
			
clean:
	rm $(APPS) *.o -f;
