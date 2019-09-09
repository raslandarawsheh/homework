              
# import pygame module in this program 
import cv2
import numpy as np
import socket,os,struct, glob, sys

            
img = cv2.imread('img.jpg')
def receive_data():
    img = []
    recv_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    try:
        os.remove("/tmp/tmp")
    except OSError:
        pass
    recv_socket.bind("/tmp/tmp")
    recv_socket.listen(10)
    conn, addr = recv_socket.accept()
    size = conn.recv(4)
    size = struct.unpack('i', size)[0]
    while size > 0:
        data = conn.recv(4)
        try:
            p = struct.unpack('f', data)[0]
        except struct.error:
            p = 0
        size -= 1
        img.append(p)

    img = np.array(img)
    cv2.imwrite('color_img.jpg', img)
    cv2.imshow("img", img)
    #flip_imgs_and_show(img)


def flip_imgs_and_show(img):
    cv2.imshow("img", img)
    return
    horizontal_img = img.copy()
    vertical_img = img.copy()
    both_img = img.copy()
 
    # flip img horizontally, vertically,
    # and both axes with flip()
    cv2.flip( horizontal_img, 0, horizontal_img)
    cv2.flip( vertical_img , 1, vertical_img)
    cv2.flip(both_img , -1 , both_img)
    cv2.flip(both_img , 0 , both_img)
    # display the images on screen with imshow()
    up = cv2.hconcat(img, horizontal_img)
    down = cv2.hconcat(vertical_img, both_img)
    img_to_disblay = cv2.vconcat(up, down)
    cv2.imshow("img", img_to_disblay)


receive_data()
while 1:
    receive_data()



