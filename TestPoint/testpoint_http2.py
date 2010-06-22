#!/usr/bin/python2.6
# -*- coding: utf-8 -*-


from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
import os,glob, time, random, pdb
import serial, struct

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
	s=serial.Serial("Com3")
        fpath = os.path.join(os.getcwd(),self.path[1:])
        response = ""
        self.send_response(200)
        self.send_header("Content-type","text/html")
        self.end_headers()
        self.wfile.write("""<html>""")
        self.wfile.write(str('<script language="javascript">'))
        self.wfile.write("""
        function addColumn(id, value, color){
        var table = document.getElementById(id);
        var rows = table.getElementsByTagName('tr');
        var lastrow = rows[rows.length - 1];
        var td = document.createElement('td');
        td.setAttribute("bgcolor",color);
        td.appendChild(document.createTextNode(value));
        lastrow.appendChild(td);
        }

        function addRow(id) {
        var table = document.getElementById(id);
        var tr=document.createElement('tr');
        table.appendChild(tr);
        }
        """)
       
        self.wfile.write(str('</script>'))

        self.wfile.write(str('<body>TestPoint<table id="testtable" border="1"><tr></tr></table>'))


        width=30
        cpos=0
       
        for i in xrange(10000):
	    readbytes=struct.unpack('1B', s.read(1))
            v = readbytes[0]
	    if v > 0 :
                color = "\'red\'"
            else:
                color = "\'blue\'"
            self.wfile.write("""
            <script type="text/javascript">
            addColumn('testtable',"""+str(v)+""" ,"""+color+""");
            scrollTo(0,99999999999);
            </script>""")

            cpos+=1
            if cpos%width==0:
                self.wfile.write("""
                <script type="text/javascript">
                addRow('testtable')
                </script>
                """)               
                cpos=0
            self.wfile.flush()
            time.sleep(0.01)
        self.wfile.write("</body></html>")
	s.close()

        
httpd = HTTPServer(('',7676),RequestHandler)
httpd.serve_forever()