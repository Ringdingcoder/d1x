/*
 * arch_ip.cpp - arch specific udp/ip code.  (dos ver)
 * added 2000/02/07 Matt Mueller
 * edited for winconsole 2000/02/28 Victor Rachels
 */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#include "winsock.h"

extern "C" {
#include "ipx_drv.h"
#include "types.h"
#include "mono.h"
//#include "multi.h"
}


#include "ip_base.h"
#include "ipclient.h"

#if 1

#include "bootp.h"

Socket *socket;

//dos stub file.  needs to be filled in. (see the win32 or linux ver for examples)

/* Do hostname resolve on name "buf"
 */
int arch_ip_queryhost(ip_addr *addr,char *buf,ushort baseport)
{
 char *s;
 ushort p;
 long intaddr;
 int i,addrlist[4];

   if ((s=strrchr(buf,':')))
    {
      *s='\0';
      p=ip_portshift(baseport,s+1);
    }
   else p=ip_portshift(baseport,NULL);

  intaddr=Resolve(buf);

   for(i=0;i<4;i++)
    {
     addrlist[i] = intaddr & 0xff;
     intaddr = intaddr >> 0x08;
    }

  addr->set(4,(u_char *)addrlist,p);

  return 0;
}

int ip_sendtoca(ip_addr addr,const void *buf,int len)
{
   if (addr.addrlen()!=4)
    return 0;//not handled yet

#ifdef UDPDEBUG
  printf(MSGHDR "sendtoca((%d) ",len);
  addr.dump();
  puts(").");
#endif

 InetAddress sto;

  sto.family = AF_INET;
  sto.port   = *(unsigned short *)(addr.addr+4);
  memcpy(&sto.address,addr.addr,4);

  return (socket->Send((char *)buf,len,0,&sto,sizeof(sto)) > 0);
}

int arch_ip_get_my_addr(ushort myport)
{
  /* no way to do this in this API that I could find */
  return -1;
}

int arch_ip_open_socket(int port)
{
   if(socket)
    FAIL("socket already open");

  SocketInit();

  socket = new Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef UDPDEBUG
  socket->_ErrorDisplay = 1;
#endif

 int val_one;

  val_one = 1; // wtf is val_one used as?
  socket->SetOption(&val_one,SOL_SOCKET,SO_BROADCAST,sizeof(val_one));

 InetAddress sin;

  sin.family =AF_INET;
  sin.port   =port;
  if (ip_bind_addr.ok())
    memcpy(&sin.address,ip_bind_addr.addr,4);
  else
    sin.address=0; // any

  socket->Bind(&sin,sizeof(InetAddress));

  return 0;
}

void arch_ip_close_socket(void)
{
   if(socket)
    delete(socket);
   else
    msg("close socket without open");

  socket = NULL;
  return;
}

int arch_ip_recvfrom(char *outbuf, int outbufsize, struct ipx_recv_data *rd)
{

 InetAddress sfrm;
 int size, frmlen;

  size = socket->Recv((void *)outbuf,(int)outbufsize,0,(void *)&sfrm,(int &)frmlen); //wtf??

   if(size < 0)
    return -1;
   if(sfrm.family != AF_INET)
    return -1;

  ip_addr tmpip;

  tmpip.set(4, (u_char*)&sfrm.address, sfrm.port);

#ifdef UDPDEBUG
  printf(MSGHDR "recvfrom((%d-2=%d),",size,size-2);
  tmpip.dump();
  puts(").");
#endif


  memcpy(rd->src_node,&tmpip,sizeof(ip_addr*)); //eeennhhh?
     /* src_node is ubyte[6] ip_addr is class prot: int pub: ubyte[6] */

  return size;
}

int arch_ip_PacketReady(void)
{
  return socket->Select(FD_READ);
}

#else

int arch_ip_queryhost(ip_addr *addr,char *buf,ushort baseport)
{
  return -1;
}

int ip_sendtoca(ip_addr addr,const void *buf,int len)
{
  return -1;
}

int arch_ip_get_my_addr(ushort myport)
{
  return -1;
}

int arch_ip_open_socket(int port)
{
  return -1;
}

void arch_ip_close_socket(void)
{
  return;
}

int arch_ip_recvfrom(char *outbuf, int outbufsize, struct ipx_recv_data *rd)
{
  return -1;
}

int arch_ip_PacketReady(void)
{
  return -1;
}

#endif
