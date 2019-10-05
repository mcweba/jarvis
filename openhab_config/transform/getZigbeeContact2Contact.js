(function(x){
    var result = "";
    var json = JSON.parse(x);
    if (json.contact)
    {
        result="CLOSED";
    }
    else
    {
        result="OPEN";
    }
    return result;
})(input)