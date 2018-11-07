(function(jsonString) {
	var data = JSON.parse(jsonString);
	var value = data.BME280.Humidity;
	return value + 6.3;
})(input)