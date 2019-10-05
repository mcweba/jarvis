(function(x){
    var result = "";
    var json = JSON.parse(x);
    if (json.water_leak)
    {
        result="OPEN";
    }
    else
    {
        result="CLOSED";
    }
    return result;
})(input)