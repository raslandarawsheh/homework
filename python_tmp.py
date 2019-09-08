import socket,os,struct, glob, sys
import random

send_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
recv_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
try:
    os.remove("/tmp/tmp")
except OSError:
    pass

recv_socket.bind("/tmp/tmp")



recv_socket.listen(10)
while 1:
   print ("listening ...")
   conn, addr = recv_socket.accept()
   data = conn.recv(4)
   p = ''
   if data:
       p = struct.unpack('i',data)
       print ('received ', p)

   if p is '9':
      break


   l = int(input(">"))
   a = struct.pack('i', l) 
   send_socket.connect("tmp/tmp1")
   send_socket.sendall(a)
   print ('sent ', l)

send_socket.close()
conn.close()
recv_socket.close()
