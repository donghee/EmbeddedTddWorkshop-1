#!/usr/bin/python2.6
# -*- coding: utf-8 -*-


from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler
import os,glob, time, random, pdb
import serial, struct

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        print "GET"
        s=serial.Serial("Com1")
        s.open()
        fpath = os.path.join(os.getcwd(),self.path[1:])
        response = ""
        self.send_response(200)
        self.send_header("Content-type","text/html")
        self.end_headers()
        self.wfile.write("""<html><head>
<style type="text/css">
td
{
font-size:5px;
}
</style>
<script language="javascript">
        function addColumn(id, value, color){
        var table = document.getElementById(id);
        var rows = table.getElementsByTagName('tr');
        var lastrow = rows[rows.length - 1];
        var td = document.createElement('td');
        td.setAttribute("bgcolor",color);
        td.appendChild(document.createTextNode(value));
        lastrow.appendChild(td);
        }

        function addRow(id,html) {

            var table = document.getElementById(id);
            table.lastChild.innerHTML=html;
        }
        </script></head>
        """)

        self.wfile.write(str('<body>TestPoint<table id="testtable" border="1"><tr></tr></table>'))


        width=120
        cpos=0
        trInnerHtml ="<tr>"
        for i in xrange(10000):
            #v=random.randrange(0,1024)
            readbytes=struct.unpack('2B', s.read(2))
            v = readbytes[0] + (readbytes[1] <<8)
            
            if v > 300 :
                color = "red"
            else:
                color = "blue"
            trInnerHtml += '<td bgcolor="%s">%d</td>'%(color,v)

            cpos+=1
            if cpos%width==0:
                trInnerHtml += "</tr>"
                self.wfile.write("""
                <script type="text/javascript">
                    addRow('testtable', '%s');
                    scrollTo(0,99999999999);   
                </script>
                """%trInnerHtml)               
                cpos=0
                trInnerHtml = "<tr>"
            self.wfile.flush()
        self.wfile.write("</body></html>")
        s.close()

        
httpd = HTTPServer(('',8085),RequestHandler)
httpd.serve_forever()
