<div class="container-fluid">
	<%= _.template($('#input_constructor').html())({id:"Url", description:tr("Url"), default_selector: "string", disable_int:true}) %>
	<%= _.template($('#variable_constructor').html())({id:"Save", description:tr("Variable To Save"), default_variable: "SAVED_COOKIES", help: {description: tr("This variable will contain string with json. That json will hold list with all cookies for all domains. Json format is described below.")}}) %>
</div>

<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>