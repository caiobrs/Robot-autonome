from time import sleep
from lib import marvelmind
import threading
from flask import Flask, render_template, url_for, request, jsonify

app = Flask(__name__)
@app.route('/')
def index() :
    return render_template('index.html')

@app.route('/getBeacons', methods=['POST', 'GET'])
def process_set_motor():
    hedge = marvelmind.MarvelmindHedge(tty = "/dev/ttyACM0", adr=None, debug=False) # create MarvelmindHedge thread
    hedge.start() # start thread
    sleep(1)
    positions = hedge.getPositionXY()
    print(positions)

    results = {'processed': 'true'}
    return jsonify(results)

app.run(debug=True, host='192.168.0.105')
#if __name__ == "__main__":
#    threading.Thread(target=lambda : app.run(debug=True, host='192.168.0.105', use_reloader=False)).start()
