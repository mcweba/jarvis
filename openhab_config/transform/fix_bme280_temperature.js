(function(jsonString) {
	var data = JSON.parse(jsonString);
	var value = data.BME280.Temperature;
	return value - 3.2;
})(input)