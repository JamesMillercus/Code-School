var express = require('express');
var bodyParser = require('body-parser');
var methodOverride = require('method-override');
var twilio = require('twilio');
var  path = require('path');
var io = require('socket.io')(server);
 io.on('connection', function(socket)
 	{
 		console.log('user is connected');
 	});
// io.listen(8080);

var app = express();
app.set('views', path.join(process.cwd(), 'views'));
app.set('view engine', 'ejs');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true  }));
app.use(express.static(__dirname + '/public'));

var port = process.env.PORT || 8080; // set our port

var client = twilio('AC3926c3fb55db04963a0bbbd589a51844', 'be8c7c3f66527005eadf454ebbcbf4f4');
var twilio_number = '+447960644904';
//441400414031
var api_key = "58f46927-34b3-40f8-bd7f-d3c6099f0d8f";
var appname = "test";
var collection = "smscontact";
var messagesRef = require('datamcfly').init(appname, collection, api_key);

var server = app.listen(port, function() {
    console.log('Listening on port %d', server.address().port);
});

// backend routes =========================

app.post('/message', function (request, response) {
    var d = new Date();
    var date = d.toLocaleString();

    messagesRef.push({
        sid: request.param('MessageSid'),
        type:'text',
        direction: "inbound",
        tstamp: date,
        fromNumber:request.param('From'),
        textMessage:request.param('Body'),
        fromCity:request.param('FromCity'),
        fromState:request.param('FromState'),
        fromCountry:request.param('FromCountry')
    });

    var resp = new twilio.TwimlResponse();
    resp.message('Thanks for the message, an agent will get back to you shortly.');
    response.writeHead(200, {
        'Content-Type':'text/xml'
    });
    response.end(resp.toString());
});

	app.post('/reply', function (request, response) {
	    var d = new Date();
	    var date = d.toLocaleString();

	    messagesRef.push({
	        type:'text',
	        direction: "outbound",
	        tstamp: date,
	        fromNumber:request.param('From'),
	        textMessage:request.param('Body'),
	        fromCity:'',
	        fromState:'',
	        fromCountry:''
	    });

	    client.sendMessage( {
	        to:request.param('To'), 
	        from:twilio_number,
	        body:request.param('Body')
	    }, function( err, data ) {
	       // console.log( data.body );
	    });
	});

// frontend routes =========================

// route to handle all angular requests
app.get('*', function(req, res) {
    res.render('home', {
        apikey:api_key,
        appname:appname,
        collection:collection
    });
});


