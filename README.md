# jarvis
Home Automation based on OpenHAB2

## MyStrom Button Adapter
Since the REST API of the MyStrom Button does not allow to make _POST_ requests with a _text/plain_ content-type and the (items) REST API of _openHAB2_ only accepts _text/plain_ content-type requests, a simple adapter server is used.

This server is based on _Node.js_ and _Express.js_

### Installation
Copy the _adapter.js_ script to the following folder on the raspberry pi:

```
/home/openhabian/MyStromButtonAdapter
```
Navigate into this directory and call

```
sudo npm i express
sudo npm i request
```
You should no be able to start the adapter (for testing) with
```
node adapter.js
```

### Start adapter after Raspberry reboot
To start the adapter automatically after a reboot you have to copy the init script _mystrombuttonadapter_ to
```
/etc/init.d/
```
Change permissions of init script to
```
sudo chmod 755 mystrombuttonadapter
```
activate the service by calling
```
sudo update-rc.d mystrombuttonadapter defaults
```
The init script should now be started on next reboot. To manually start the script use
```
sudo /etc/init.d/mystrombuttonadapter start
```
to stop the script use
```
sudo /etc/init.d/mystrombuttonadapter stop
```
to get the status of the script use
```
sudo /etc/init.d/mystrombuttonadapter status
```
the corresponding log files can be viewed with
```
tail -f /var/log/mystrombuttonadapter.log
tail -f /var/log/mystrombuttonadapter.err
```
## MyStrom Button Configuration
To configure the MyStrom Button REST API (https://mystrom.ch/wp-content/uploads/REST_API_WBP.txt) make the following request
```
POST http://[IP]/api/v1/device/[MAC]
Body: single=post://openhabianpi:3000/button1/single&double=post://openhabianpi:3000/button1/double&long=post://openhabianpi:3000/button1/long&touch=post://openhabianpi:3000/button1/touch
```
The values
* single=post://openhabianpi:3000/button1/single
* double=post://openhabianpi:3000/button1/double
* long=post://openhabianpi:3000/button1/long
* touch=post://openhabianpi:3000/button1/touch

point to the _MyStrom Button adapter_

## Zigbee2mqtt
### Installation
See documentation about installation on [www.zigbee2mqtt.io](https://www.zigbee2mqtt.io)

### Configuration
The config file is
```
/opt/zigbee2mqtt/data/configuration.yaml
```

### Running as service
Starting zigbee2mqtt
```
sudo systemctl start zigbee2mqtt
```

Stopping zigbee2mqtt
```
sudo systemctl stop zigbee2mqtt
```
View the log of zigbee2mqtt
```
sudo journalctl -u zigbee2mqtt.service -f
```

### MQTT topics and message structure
See [documentation](https://www.zigbee2mqtt.io/information/mqtt_topics_and_message_structure.html)
