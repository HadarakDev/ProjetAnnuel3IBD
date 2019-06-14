from flask import Flask, make_response, render_template, request, send_file, flash




app = Flask(__name__)
app.secret_key = 'd66HR8dgjYYic*dhfdsfsdf'

@app.before_request
def before_request():
    if request.url.startswith('http://'):
        url = request.url.replace('http://', 'https://', 1)
        code = 301
        return redirect(url, code=code)


if __name__ == '__main__':

    app.run(host='0.0.0.0', port=80  )
    app.run(debug=True)

