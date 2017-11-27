#!/usr/bin/env python
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer

class S(BaseHTTPRequestHandler):
    log_file = open('logfile.txt', 'w')
    def log_message(self, format, *args):
        self.log_file.write("%s - - [%s] %s\n" %
                            (self.client_address[0],
                            self.log_date_time_string(),
                            format%args))

    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        self.wfile.write("get_success")

    def do_PATCH(self):
        self._set_headers()
        self.wfile.write("patch_success")

    def do_PUT(self):
        self._set_headers()
        self.wfile.write("put_success")

    def do_DELETE(self):
        self._set_headers()
        self.wfile.write("delete_success")

    def do_POST(self):
        self._set_headers()
        self.wfile.write("post_success")

    def do_HEAD(self):
        self._set_headers()


def run(server_class=HTTPServer, handler_class=S, port=80, max=-1, count=0):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    while max == -1 or count < max:
        httpd.handle_request()
        count += 1

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    elif len(argv) == 3:
        run(port=int(argv[1]), max=int(argv[2]))
    else:
        run()
