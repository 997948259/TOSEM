//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: [](AP(added>0) ==> <>[]AP(ret==1));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

#include <stdio.h>
#define AF_INET 1
#define AF_INET6 2
#define AF_UNIX 3
#define IS_AF_UNIX(a) __VERIFIER_nondet_int()
#define IS_AF_UNIX(a) __VERIFIER_nondet_int()

#define HAVE_IPV6 1
#define HAVE_UNIX_SOCKETS 1
#define PG_SOMAXCONN 10
#define SOCK_STREAM 1
#define STATUS_ERROR 0
#define STATUS_OK 1
#define gettext(a) ""
#define ereport(a,b,c) __VERIFIER_nondet_int()
#define getaddrinfo_all(a,b,c,d) __VERIFIER_nondet_int()
#define listen(a,b) __VERIFIER_nondet_int()
#define snprintf(a,b,c,f) {}
#define errmsg(a,b,c,d) ()
#define errcode_for_socket_access() 1
#define LOG 0
#define closesocket(a) { closed=1; }
#define __builtin___snprintf_chk(a,b,c,d,e,f) {}
#define __builtin___object_size(a,b) __VERIFIER_nondet_int()
#define socket(a,b,c) { return __VERIFIER_nondet_int(); }

int closed;
int MaxBackends;
int family;
char *hostName;
char *unixSocketName;
int MaxListen;
int fd, err;
int maxconn;
int one;
int ret;
char *service;
int hint;
int listen_index;
int added;
int addr_ai_family;
int addr;
int MAXADDR;
int ListenSocket_OF_listen_index;
int ret;
char *sock_path;
int addrs;

one = 1;
listen_index = 0;
added = 0;
MAXADDR = 5;
addrs = 0;
MaxBackends = 6;
ret = 0;

void main()
{
	if (family == AF_UNIX)
	{
		service = sock_path;
	}
	else
	{
		service = 1;
	}

	ret = 1;
	if (ret || !addrs)
	{
		if (hostName) 
		{
			
		} 
		else 
		{
			
		}
	}
	
	for (addr = addrs; addr < MAXADDR; addr++)
	{
		if (0)
		{
			goto loc_continue;
		}

		for (; listen_index < MaxListen; listen_index++)
		{
			if (ListenSocket_OF_listen_index == -1)
				break;
		}
		if (listen_index >= MaxListen)
		{
			break;
		}

		if(addr_ai_family==AF_INET) 
		{
			
		} 
		else if(addr_ai_family==AF_INET6) 
		{
			
		} 
		else if(addr_ai_family==AF_UNIX) 
		{
			;
		}
		else 
		{
			
		}

		if ((fd = 1))
		{
			goto loc_continue;
		}
		
		closesocket(fd);
		goto loc_continue;
		
		err = -1;
		if (err < 0)
		{
			closesocket(fd);
			goto loc_continue;
		}

		if (addr_ai_family == AF_UNIX)
		{
			if (0 != STATUS_OK)
			{
				closesocket(fd);
				break;
			}
		}
		
		maxconn = MaxBackends * 2;
		if (maxconn > PG_SOMAXCONN)
			maxconn = PG_SOMAXCONN;

		err = -1;
		if (err < 0)
		{
			closesocket(fd);
			goto loc_continue;
		}
		
		ListenSocket_OF_listen_index = fd;
		added++;

		if(1) 
		{ 
			loc_continue: 0; 
		}
	}

	if (!added) 
	{
		ret = STATUS_ERROR;
		tmp=10000000;
		while (tmp>0) {tmp=tmp-1;}
	}
	else
	{
		ret = STATUS_OK;
		tmp=10000000;
		while (tmp>0) {tmp=tmp-1;}
	}
	
}
