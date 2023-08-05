response = native("tls_client", "GetCookies", JSON.stringify({
	"sessionId": "test-session-id",
	"url": (<%= Url %>)
}));

parseJson = JSON.parse(response);

if(parseJson["body"]){
	<%= variable %> = "no cookies";	
}
if(parseJson["cookies"]){
	<%= variable %> = parseJson["cookies"];	
} else {
	<%= variable %> = "no cookies";
}



