CC=gcc
FLAGS= -fPIC -shared -rdynamic

all:
	$(CC) $(FLAGS) pam_honeypam.c -o pam_honeypam.so

install:
	cp pam_honeypam.so /lib/security/

clean:
	rm pam_honeypam.so
