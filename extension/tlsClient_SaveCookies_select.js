var Url = GetInputConstructorValue("Url", loader);
if(Url["original"].length <= 0){
	Invalid(tr("Url") + " " + tr("is empty"));
    return;
};
var Save = this.$el.find("#Save").val().toUpperCase();
if(Save.length == 0){
	Invalid(tr("The variable to which the result is saved is missing"));
	return;
};

try{
    var code = loader.GetAdditionalData() + _.template($("#tlsClient_SaveCookies_code").html())({
		Url: Url["updated"],
        variable: "VAR_" + Save
    });
    code = Normalize(code, 0);
    BrowserAutomationStudio_Append("", BrowserAutomationStudio_SaveControls() + code, action, DisableIfAdd);
}catch(e){}