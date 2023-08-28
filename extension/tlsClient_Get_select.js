var Value = GetInputConstructorValue("Value", loader);
if(Value["original"].length <= 0){
	Invalid(tr("Url") + " " + tr("is empty"));
    return;
};
var Headers = GetInputConstructorValue("Headers", loader);
var Method = GetInputConstructorValue("Method", loader);
if(Method["original"].length <= 0){
	Invalid(tr("Method") + " " + tr("is empty"));
    return;
};

var Redirect = $("#Check").is(':checked');
var isByteResponse = $("#isByteResponse").is(":checked");

var Timeout = GetInputConstructorValue("Timeout", loader);
if(Timeout["original"].length == 0){
	Invalid(tr("Timeout") + " " + tr("is empty"));
    return;
};
var MaximumFailes = GetInputConstructorValue("MaximumFailes", loader);
if(MaximumFailes["original"].length == 0){
	Invalid(tr("Maximum failures") + " " + tr("is empty"));
    return;
};
var ClientIdentifier = GetInputConstructorValue("ClientIdentifier", loader);

try {
    var code = loader.GetAdditionalData() + _.template($("#tlsClient_Get_code").html())({
        Value: Value["updated"],
		Headers: Headers["updated"],
		Method: Method["updated"],
		Redirect: Redirect,
		isByteResponse: isByteResponse,
		Timeout: Timeout["updated"],
		MaximumFailes: MaximumFailes["updated"],
		ClientIdentifier: ClientIdentifier["updated"],
    })
	code = Normalize(code, 0);
	BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e){Invalid(e);}