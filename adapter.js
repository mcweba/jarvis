const express = require('express')
const requestAPI = require("request");
const app = express()
const port = 3000

console.log('*** starting MyStrom button REST API adapter ***');

var urlPrefix = 'http://openhabianpi:8080/rest/items/'

app.post('/button1/touch', (request, response) => {
	requestAPI.post(
	    {url: urlPrefix + 'MyStrom_Button1_Touch',
	    headers: {'Content-Type': 'text/plain'}
	    },
	    function (error, resp, body) {        
	        if (!error && resp.statusCode == 200) {
	            console.log(body)
	        }
	        response.send('forwarded touch event')
	    }
	);
})

app.post('/button1/single', (request, response) => {
	requestAPI.post(
	    {url: urlPrefix + 'MyStrom_Button1_Single',
	    headers: {'Content-Type': 'text/plain'}
	    },
	    function (error, resp, body) {        
	        if (!error && resp.statusCode == 200) {
	            console.log(body)
	        }
	        response.send('forwarded single click event')
	    }
	);
})

app.post('/button1/double', (request, response) => {
	requestAPI.post(
	    {url: urlPrefix + 'MyStrom_Button1_Double',
	    headers: {'Content-Type': 'text/plain'}
	    },
	    function (error, resp, body) {        
	        if (!error && resp.statusCode == 200) {
	            console.log(body)
	        }
	        response.send('forwarded double click event')
	    }
	);
})

app.post('/button1/long', (request, response) => {
	requestAPI.post(
	    {url: urlPrefix + 'MyStrom_Button1_Long',
	    headers: {'Content-Type': 'text/plain'}
	    },
	    function (error, resp, body) {        
	        if (!error && resp.statusCode == 200) {
	            console.log(body)
	        }
	        response.send('forwarded long click event')
	    }
	);
})

app.listen(3000, function () {
  console.log('listening on port 3000');
});