#!/usr/bin/env python3
import os
import subprocess
from pathlib import Path
from flask import Flask, escape, request, send_from_directory
app=Flask(__name__)

safeChroot='/usr/local/bin/s4g_chroot'
commentary=open("commentary.txt",'a')

@app.route('/overflowity/<problem>', methods=['GET','POST'])
def get_problem(problem):
    if not problem.isalnum():
        return send_from_directory("ui","nope.html")
    problemPath='problems/'+problem
    if os.path.exists(problemPath):
        page=Path("ui/template0.html").read_text('utf-8')

        user=request.args.get('user') or 'mystery'
        if not user.isalnum():
           user="BADCHARS"
        page += user

        page += Path("ui/template1.html").read_text('utf-8')

        input=request.args.get('input') or ''
        page += format(escape(input))

        page += Path("ui/template2.html").read_text('utf-8')

        page+='<p>Attempting problem '
        page+=problem

        src=Path("src/"+problem+".cpp").read_text('utf-8')
        page+='<p>Problem source code: <pre>'+format(escape(src))+'</pre>'

        page+='<p>Running with input data: <pre>'+format(escape(input))+'</pre>'
        page+='<p>Running '+problem+' now:'
        
        p = subprocess.Popen([safeChroot,problemPath],stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        stdout, stderr = p.communicate(input=input.encode('utf-8'))
        stdout = stdout.decode('utf-8')
        if stderr:
            stderr = stderr.decode('utf-8')
        else:
            stderr=''
        page+='<pre>'+stdout+stderr+'</pre>'
        code=p.returncode
        if code==0:
           page+='<p>OK!'
           Path("users/"+user).mkdir(parents=True,exist_ok=True)
           Path("users/"+user+"/"+problem).write_text("OK "+input)
           commentary.write(user+" just solved "+problem+"!\n")
           commentary.flush()
           page+='<script>document.body.style.backgroundColor="#88ffff";</script>'

        page += Path("ui/template99.html").read_text('utf-8')

        page+='</body></html>'
        
        return page
    else:
        return send_from_directory("ui","index.html")

if __name__ == '__main__':
    app.run()

