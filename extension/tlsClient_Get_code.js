native_async("tls_client", "RequestBas", JSON.stringify({
        "tlsClientIdentifier": "chrome_103",
        "followRedirects": (<%= Redirect %>),
        "insecureSkipVerify": false,
        "withoutCookieJar": false,
        "withDefaultCookieJar": false,
        "forceHttp1": false,
        "withDebug": false,
        "withRandomTLSExtensionOrder": false,
        "isByteResponse": (<%= isByteResponse %>),
        "isByteRequest": false,
        "catchPanics": false,
        "timeoutSeconds": 30,
        "timeoutMilliseconds": 0,
        "proxyUrl": "",
        "isRotatingProxy": false,
        "certificatePinningHosts": {},
        "headers": {
            "accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
            "user-agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36",
            "accept-encoding": "gzip, deflate, br",
            "content-type": "application/x-www-form-urlencoded",
            "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7"
        },
        "headerOrder": [
            "accept",
            "user-agent",
            "content-type",
            "accept-encoding",
            "accept-language"
        ],
        "requestUrl": (<%= Value %>),
        "requestMethod": "GET",
}))!

parsedResponse = JSON.parse(_result());

if(parsedResponse["status"] < 200){
	fail("[TLS Client] Error: " + parsedResponse["body"]);
}
