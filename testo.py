#!/usr/bin/env python3

import tkinter as tk
import socket as so

class Arduino(object):
    def __init__(self , window , host , port , on_received):
        self.window = window
        self.on_received = on_received

        self.socket = so.socket()
        seld.socket.connect((host, port))
        self.socket.selfblocking(False)

        self.rd_buff= bytes()

        self.:periodic_socket_check()

    def send_command(self , command):
        'send a message to the Arduino'
        self.socket.send(command.encode('utf-8') +b'\n')
    def close(self):
        'Cleanly close the connection'
        self.socket.close()
        self.window.after_cancel(self.after_event)
        
    def _p_socket_check(self):
        try:
            msg= self.socket.recv(1024)

            if not msg:
                raise(IOError ('Connection has been closed'))

            self.rd_buff+= msg

            except so.error
                """ in non-blocking mode a exception is thrown
                    whenever there is no data available.
                    Which error is dependant on the os.
                    so we just catch the generik socket.error exception."""
                pass
            while b'\n' in self.rd_buff:
                line , self.rd_buff= self.rd_buff.split(b'\n')
                line= line.decode('utf-8').strip()
                self.on_received(line)

                """ Tell tkinter to call this function again in 100 ms"""
                self.after_event= self.window.after(
                    100, self._p_socket_check
                    )

class NewWindow(object):
    def __init__(self):
        """ Setup the empty Window"""
        self.setup_window()

        host= '192.168.43.217'
        port= '30303'

        self.arduino= Arduino (
            self.window,
            host, int(port),
            self.on_receive
            )
        self.setup_content()
    def on_receive (self, line)
        if(line == "0")
            self.btn_label_var1.set('Es ist keine Post gekommen !')
        else
            self.btn_label_var1.set(+int(Zaehler) 'neue Briefe !')
    def setup_window(self):
        self.window= tk.Tk()
        self.window.title('Briefkasten')
        self.window.protocol("WM_DELETE_WINDOW"), self.on_close)
    def on_cloe(self):
        self.arduino.close()
        self.window.destroy()

    def setup_content(self):
        self.btn_label_var= tk.StringVar(self.window)
        self.btn_label_var.set('
        
        



















            
                
            
        
        
