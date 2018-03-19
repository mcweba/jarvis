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
