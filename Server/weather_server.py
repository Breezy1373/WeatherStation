import eventlet
import json
import sqlite3
from time import gmtime, strftime
from flask import Flask, render_template
from flask_mqtt import Mqtt
from flask_socketio import SocketIO
from flask_bootstrap import Bootstrap

eventlet.monkey_patch()

app = Flask(__name__)
app.config['SECRET'] = 'my secret key'
app.config['TEMPLATES_AUTO_RELOAD'] = True
app.config['MQTT_BROKER_URL'] = '192.168.8.32'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_KEEPALIVE'] = 5
app.config['MQTT_TLS_ENABLED'] = False

# Parameters for SSL enabled
# app.config['MQTT_BROKER_PORT'] = 8883
# app.config['MQTT_TLS_ENABLED'] = True
# app.config['MQTT_TLS_INSECURE'] = True
# app.config['MQTT_TLS_CA_CERTS'] = 'ca.crt'

mqtt = Mqtt(app)
socketio = SocketIO(app)
bootstrap = Bootstrap(app)


@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('subscribe')
def handle_subscribe(json_str):
    data = json.loads(json_str)
    mqtt.subscribe(data['topic'])

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
    )
    print("Data: %s" % data)
    socketio.emit('mqtt_message', data=data)
    theTime = strftime("%Y-%m-%d %H:%M:%S", gmtime())
    # enter data into database
    conn = sqlite3.connect('sensordata.db')
    c = conn.cursor()



@mqtt.on_log()
def handle_logging(client, userdata, level, buf):
    pass
    # print("userdata: %s" % userdata)


if __name__ == '__main__':
    mqtt.subscribe('weather/#')
    socketio.run(app, host='0.0.0.0', port=5000, use_reloader=False, debug=True)