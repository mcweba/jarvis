require('log-timestamp');
const express = require('express')
const requestAPI = require("request");
const app = express()
const config = require('./config');

console.log('*** starting Husqvarna REST API adapter ***');

var urlPrefix = 'http://openhabianpi:8080/rest/items/'

var authURL = 'https://api.authentication.husqvarnagroup.dev/v1/oauth2/token'
var mowerURL = 'https://api.amc.husqvarna.dev/v1/mowers/' + config.mower_id
var access_token = ''

function updateAccessToken() {
    console.log('About to update access token');
    requestAPI.post({
        url: authURL,
        headers: {'Content-Type': 'application/x-www-form-urlencoded'},
        form: {
            'grant_type' : 'refresh_token',
            'client_id' : config.client_id,
            'refresh_token' : config.refresh_token
        }
    }, function (error, resp, body) {
        if (!error && resp.statusCode == 200) {
            console.log('Successfully got new access token')
            const jsonBody = JSON.parse(body);
            access_token = jsonBody.access_token
        } else {
            console.log('Failed to update access token: ' + body)
        }
    });
}

app.get('/husqvarna/status', (request, response) => {
    requestAPI.get({
        url: mowerURL,
        headers: {
            'Authorization' : 'Bearer ' + access_token,
            'Authorization-Provider' : 'husqvarna',
            'X-Api-Key' : config.x_api_key
        }
    }, function (error, resp, body) {
        if (!error && resp.statusCode == 200) {
            console.log('Successfully got status')
            response.set('Content-Type', 'application/json');
            response.send(body)
        }
    });
})

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


updateAccessToken(); // initial get of access token
setInterval(updateAccessToken, 3590 * 1000); // update every hour

app.listen(3001, function () {
  console.log('listening on port 3001');
});
