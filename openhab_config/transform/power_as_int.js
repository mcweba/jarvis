(function(jsonString) {
	var data = JSON.parse(jsonString);
    var valueAsInt = parseInt(data.power, 10);
	return valueAsInt;
})(input)