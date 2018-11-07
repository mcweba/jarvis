(function(jsonString) {
	var data = JSON.parse(jsonString);
	var value = data.BME280.Temperature;
	return value + 0.0;
})(input)