if(!(<%= UseConstructor %>)){
	log(JSON.stringify(
	{"Value": (<%= Value %>), "Params": <%= PostDataRaw %>, "ContentType":(<%= ContentTypeRaw %>), "Method": (<%= Method %>), "Headers": (<%= Headers %>), "Redirect": (<%= Redirect %>)}
));
}else{
	log(JSON.stringify(
	{"Value": (<%= Value %>), "Params": (<%= Params %>), "ContentType": (<%= ContentType %>), "Method": (<%= Method %>), "Headers": (<%= Headers %>),"Redirect": (<%= Redirect %>)}
));

}
