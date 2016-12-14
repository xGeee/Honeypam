# Honeypam

Honeypam is a small PAM module which denies password authentication attempts and log the credentials used (the module always return PAM_AUTH_ERR).

It can be used with services which rely on PAM authentication to create honeypots.

## Build

see Makefile

```
make && sudo make install
```

## Install (ssh)

you need the following at the top of /etc/pam.d/sshd :

	auth required pam_honeypam.so /path/to/log/file

You can keep "PasswordAuthentiction no" in your /etc/sshd_config file and add this for each user you want to deny and log passwords from:

```
Match user root
	PasswordAuthentication yes
```

## Limits

the PAM module will only log passwords if the given username exists on the system.
