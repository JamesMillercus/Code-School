

/*
	
	AUTHOR:		Alex Bimpson @ Prrple
	NAME:		Facebook JS SDK Wrapper
	WEBSITE:	http://www.prrple.com
	LICENSE:	Distributed under the MIT License
	VERSION:	3.4
	UPDATED:	2015-01-29
	
*/


/********************************************************************************************************************************/
/****************************************************** FACEBOOK - FRAMEWORK ****************************************************/
/********************************************************************************************************************************/

var FACEBOOK = new Object({
	
	
	/******************** CONFIG ********************/
	app_id:					'1631348210485554',
	namespace:				'',
	user_fields:			'',
	scope:					'user_about_me, user_likes, user_friends, publish_actions, user_photos,', 
	get_stream_privacy:		false,
	channel_file:			'',
	
	
	/******************** DATA STORAGE ********************/
	//GENERAL
	init:					false,
	got_status:				false,
	auth_response:			'',
	//USER DATA
	logged_in:				false,
	got_user:				false,
	user:					'',
	status:					'',
	permissions:			'',
	friends:				'',
	default_stream_privacy:	'',
	//CANVAS DATA
	canvas_info:			'',
	//FRAMEWORK VARS
	clicked:				false,
	
	
	/******************** RESET DATA STORAGE (AFTER LOGOUT) ********************/
	reset: function(){
		FACEBOOK.auth_response = '';
		FACEBOOK.logged_in = false;
		FACEBOOK.got_user = false;
		FACEBOOK.user = '';
		FACEBOOK.status = '';
		FACEBOOK.permissions = '';
		FACEBOOK.friends = '';
		FACEBOOK.default_stream_privacy = '';
		FACEBOOK.canvas_info = '';
		FACEBOOK.clicked = false;
	},
	
	
	/******************** INITIALISE ********************/
	initialise: function(){
		FACEBOOK.init = true;
		FACEBOOK.fb_ready();
	},
	
	
	/******************** STATUS CHANGES ********************/
	status_change: function(response){
		if(response.status == 'connected'){
			//authenticated
			//console.log('--- facebook - authenticated ---');
			FACEBOOK.status = 'connected';
			FACEBOOK.status_authenticated();
		}else if(response.status == 'not_authorized'){
			//logged in but not authenticated
			//console.log('--- facebook - not authenticated ---');
			FACEBOOK.status = 'not_authorized';
			FACEBOOK.status_not_authenticated();
		}else{
			//not logged in to facebook
			//console.log('--- facebook - not logged in ---');
			FACEBOOK.status = 'not_logged_in';
			FACEBOOK.status_not_logged_in();
		};
	},
	status_authenticated: function(){
		FACEBOOK.logged_in = true;
		FACEBOOK.get_user();
		FACEBOOK.fb_auto_auth();
	},
	status_not_authenticated: function(){
		FACEBOOK.reset();
		FACEBOOK.fb_auto_not_auth();
	},
	status_not_logged_in: function(){
		FACEBOOK.reset();
		FACEBOOK.fb_auto_not_logged_in();
	},
	
	
	/******************** FACEBOOK - LOGIN ********************/
	login: function(callback){
		FACEBOOK.fb_login_pre();
		if(FACEBOOK.init == true){
			//console.log("Did it work?");
			FACEBOOK.authenticate(callback);
		}else{
			setTimeout(function(){
				FACEBOOK.login(callback);
			},50);
		};
	},
	//LOGIN FUNCTION
	authenticate: function(callback){
		if(FACEBOOK.logged_in == true){
			FACEBOOK.fb_login_auth(callback);
			
		}else{
			//IF IE THEN DIRECTLY LOGIN - AVOIDS POPUP BLOCKER
			if(typeof(yourBrowser)!=='undefined' && yourBrowser=='IE'){
				FB.login(function(response) {
					if (response.authResponse) {
						//successfully logged in
						FACEBOOK.fb_login_auth(callback);
					}else{
						//User cancelled login or did not fully authorize
						FACEBOOK.fb_cancelled(callback);
					};
				}, {scope: FACEBOOK.scope});
			}else if(navigator.userAgent.match('CriOS')){
				window.open('https://www.facebook.com/dialog/oauth?client_id='+ FACEBOOK.app_id +'&redirect_uri='+document.location.href+'&scope='+FACEBOOK.scope, '', null);
			}else{
				FB.getLoginStatus(function(response) {
					if(response.status == 'connected'){
						//already authenticated
						FACEBOOK.fb_login_auth(callback);
					}else if(response.status == 'not_authorized'){
						//logged in to facebook but not authenticated
						FACEBOOK.authenticate_func(callback);
					}else{
						//not logged in to facebook
						FACEBOOK.authenticate_func(callback);
					};
				});
			};
		};
	},
	//LOGIN FUNCTION FOR NON IE BROWSERS
	authenticate_func: function(callback){
		FB.login(function(response) {
			if (response.authResponse) {
				//successfully logged in
				FACEBOOK.fb_login_auth(callback);
			}else{
				//User cancelled login or did not fully authorize
				FACEBOOK.fb_cancelled(callback);
			};
		}, {scope: FACEBOOK.scope});
	},
	
	
	/******************** GET USER DETAILS ********************/
	get_user: function(){
		if(FACEBOOK.got_user == false){
			//AUTH RESPONSE
			FACEBOOK.auth_response = FB.getAuthResponse();
			//CHECK PERMISSIONS
			var fields = FACEBOOK.user_fields.split(',');
			if(jQuery.inArray('permissions', fields) == -1){
				FACEBOOK.user_fields = FACEBOOK.user_fields+',permissions'
			}
			//GET AND STORE FACEBOOK USER DATA
			FB.api('/me?fields='+FACEBOOK.user_fields, function(response) {
				if(response.permissions){
					FACEBOOK.permissions = response.permissions;
				}
				FACEBOOK.user = response;
				FACEBOOK.got_user = true;
			});
			//GET STREAM PRIVACY
			if(FACEBOOK.get_stream_privacy == true){
				FB.api({
					method: 'fql.query',
					query: "SELECT name, value, description FROM privacy_setting WHERE name = 'default_stream_privacy'"
				}, function(response) {
					FACEBOOK.default_stream_privacy = response.description;
				});
			};
		};
	},
	
	
	/******************** AUTH CALLBACKS ********************/
	//INITIALISED
	fb_ready: function(){
		FACEBOOK.fnc_ready();
	},
	//AUTO - NOT LOGGED IN TO FACEBOOK
	fb_auto_not_logged_in: function(){
		FACEBOOK.fnc_auto_not_logged_in();
	},
	//AUTO - NOT AUTHENTICATED
	fb_auto_not_auth: function(){
		FACEBOOK.fnc_auto_not_auth();
	},
	//AUTO - AUTHENTICATED
	fb_auto_auth: function(){
		//ensure user hasn't already clicked manual login
		if(FACEBOOK.clicked == false){
			if(FACEBOOK.got_user == true){
				FACEBOOK.fnc_auto_auth();
			}else{
				setTimeout(function(){
					FACEBOOK.fb_auto_auth();
				},50);
			};
		};
	},
	//LOGIN - PRE-AUTHENTICATION
	fb_login_pre: function(){
		FACEBOOK.clicked = true;
		FACEBOOK.fnc_login_pre();
	},
	//LOGIN - AUTHENTICATED
	fb_login_auth: function(callback){
		if(FACEBOOK.got_user == true){
			if(typeof(callback) == "function"){
				callback();
			}else{
				//console.log("Yes it did!");
				FACEBOOK.fnc_login_auth();
			};
		}else{
			setTimeout(function(){
				FACEBOOK.fb_login_auth(callback);
			},50);
		};
	},
	//LOGIN CANCELLED
	fb_cancelled: function(){
		FACEBOOK.fnc_cancelled();
	},
	//PERMISSIONS REVOKED
	fb_revoked: function(callback){
		FACEBOOK.reset();
		if(typeof(callback) == "function"){
			callback();
		}else{
			FACEBOOK.fnc_revoked();
		};
	},
	//LOGGED OUT
	fb_loggedout: function(callback){
		FACEBOOK.reset();
		if(typeof(callback) == "function"){
			callback();
		}else{
			FACEBOOK.fnc_loggedout();
		};
	},
	
	
	/******************** CALLBACK FUNCTIONS ********************/
	fnc_ready: function(){},
	fnc_auto_not_logged_in: function(){},
	fnc_auto_not_auth: function(){},
	fnc_auto_auth: function(){},
	fnc_login_pre: function(){},
	fnc_login_auth: function(){},
	fnc_cancelled: function(){},
	fnc_revoked: function(){},
	fnc_loggedout: function(){},
	
	
	/******************** REQUEST ADDITIONAL PERMISSIONS ********************/
	add_perms: function(permissions,callback){
		if(FACEBOOK.got_user == true){
			//SEE IF ALREADY GOT
			var permsExisting = new Array();
			for(var i in FACEBOOK.permissions.data){
				if(FACEBOOK.permissions.data[i].status == 'granted'){
					permsExisting.push(FACEBOOK.permissions.data[i].permission);
				};
			};
			var permsRequested = permissions.split(',');
			var permsNeeded = new Array();
			for(var i in permsRequested){
				if(jQuery.inArray(permsRequested[i], permsExisting) <= -1){
					permsNeeded.push(permsRequested[i]);
				};
			};
			//GET NEW PERMS
			if(permsNeeded.length >= 1){
				permsNeeded = permsNeeded.join(',');
				FB.login(function(response2) {
					//CHECK PERMISSIONS WERE ACCEPTED
					FB.api('/me/permissions', function(response){
						FACEBOOK.permissions = response;
						var permsExisting = new Array();
						for(var i in FACEBOOK.permissions.data){
							if(FACEBOOK.permissions.data[i].status == 'granted'){
								permsExisting.push(FACEBOOK.permissions.data[i].permission);
							};
						};
						var permsRequested = permissions.split(',');
						var permsNeeded = new Array();
						for(var i in permsRequested){
							if(jQuery.inArray(permsRequested[i], permsExisting) <= -1){
								permsNeeded.push(permsRequested[i]);
							};
						};
						if(permsNeeded.length >= 1){
							//not accepted
							if(typeof(callback)=="function"){
								callback(false);
							};
						}else{
							//accepted
							if(typeof(callback)=="function"){
								callback(true);
							};
						};
					});
				},{
					scope: permsNeeded,
					auth_type: 'rerequest'
				});
			}else{
				//CONTINUE
				if(typeof(callback)=="function"){
					callback(true);
				};
			};
		}else{
			setTimeout(function(){
				FACEBOOK.add_perms(permissions,callback);
			},300);
		};
	},
	

	get_personal_info: function(callback)
	{

		FB.api('me/?fields=name', function(response)
		{
			FACEBOOK.personal_info = response.data;
			if(typeof(callback) == "function")
			{
				callback(response);	
			};
			
		});
	},
	
	/******************** GET FRIENDS WHO USE THE APP ********************/
	get_app_friends: function(callback){
		FB.api('/me/friends',function(response){
			FACEBOOK.friends = response.data;
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},

	/******************** GET LIKES FROM USER ********************/
	get_likes: function(callback){
		FB.api('/me/likes?limit=500',function(response){
			FACEBOOK.likes = response.data;
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},
	
	
	/******************** GET PHOTOS ********************/
	get_photos: function(callback){
		FB.api('/me/photos?limit=500', function(response){
			FACEBOOK.photos = response.data;
		}, function(response){
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},


	/********** make the photo albums API call **********/
	get_albums: function(callback)
	{
		FB.api('me/albums?fields=name,photos{name,id,images,link}&limit=500', function(response) 
		{
		   FACEBOOK.albums = response.data;
		}, function(response)
		{
		      if (typeof(callback) == "function"){
		        callback(response)
		      };
		});
	},

	/******************** GET PROFILE PHOTOS ********************/
	// get_profile: function(callback){
	// 	FB.api('/me/picture', function(response){
	// 		FACEBOOK.picture = response.data;
	// 	}, function(response){
	// 		if(typeof(callback) == "function"){
	// 			callback(response);
	// 		};
	// 	});
	// },

	/******************** UPLOAD A PHOTO ********************/
	upload_photo: function(url,description,callback){
		FB.api('/me/photos', 'post', {
			message: (typeof(description)!=='undefined'?description:''),
			url: url
		}, function(response){
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},
	
	
	/******************** FRIEND REQUEST ********************/
	friend_request: function(fbid,callback){
		FB.ui({
			method:			'friends',
			id:				fbid
		}, function(response){
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},
	
	
	/******************** SEND NOTIFICATION ********************/
	//note - this shouldn't be done client side as it requires an app access token
	send_notification: function(fbid,app_token,href,template,callback){
		FB.api('/'+fbid+'/notifications', 'post', {
			access_token: app_token,
			href: href,
			template: template
		}, function(response) {
			if(typeof(callback) == "function"){
				callback(response);
			};
		});
	},
	
	
	/******************** REVOKE PERMISSIONS ********************/
	revoke: function(callback){
		FB.api('/me/permissions', 'delete', function(response) {
			FACEBOOK.fb_revoked(callback);
		});
	},
	
	
	/******************** LOGOUT OF FACEBOOK ********************/
	logout: function(callback){
		FB.logout(function(response) {
			FACEBOOK.fb_loggedout(callback);
		});
	},
	
	
	/******************** CANVAS STUFF ********************/
	//GET CANVAS INFO
	canvas_get_info: function(callback){
		if(FACEBOOK.init == true){
			FB.Canvas.getPageInfo(function(response){
				FACEBOOK.canvas_info = response;
				if(typeof(callback) == "function"){
					callback(response);
				};
			});
		}else{
			setTimeout(function(){
				FACEBOOK.canvas_get_info();
			},200);
		}
	},
	//SCROLL CANVAS TO TOP
	canvas_scroll_top: function(){
		if(FACEBOOK.init == true){
			FB.Canvas.scrollTo(0,0);
		}else{
			setTimeout(function(){
				FACEBOOK.canvas_scroll_top();
			},200);
		}
	},
	//SCROLL CANVAS
	canvas_scroll_to: function(y){
		if(FACEBOOK.init == true){
			FB.Canvas.scrollTo(0,y);
		}else{
			setTimeout(function(){
				FACEBOOK.canvas_scroll_to(y);
			},200);
		}
	},
	//RESIZE CANVAS
	canvas_set_size: function(xheight,xwidth){
		if(FACEBOOK.init == true){
			if(typeof xwidth !== 'undefined' && xwidth != null){
				//height & width
				FB.Canvas.setSize({
					width:xwidth,
					height:xheight
				});
			}else{
				//height only
				FB.Canvas.setSize({
					width: 810,
					height:xheight
				});
			};
		}else{
			setTimeout(function(){
				FACEBOOK.canvas_set_size(xheight,xwidth);
			},200);
		};
	},
	//RESIZE CANVAS REPEATEDLY (for apps of variable height)
	canvas_set_size_repeat_int: '',
	canvas_set_size_repeat: function(){
		if(window.self != window.top){
			FACEBOOK.canvas_set_size_repeat_int = window.setInterval(function(){
				var xheight = $(document).height();
				FACEBOOK.canvas_set_size(xheight,810);
			},500);
		};
	},
	//AUTO RESIZE CANVAS (only grows, won't shrink again)
	canvas_set_autosize: function(){
		if(FACEBOOK.init == true){
			FB.Canvas.setAutoGrow();
		}else{
			setTimeout(function(){
				FACEBOOK.canvas_set_autosize();
			},200);
		}
	}
	
	
});





/********************************************************************************************************************************/
/**************************************************** FACEBOOK - INITIALISE SDK *************************************************/
/********************************************************************************************************************************/


/******************** LOAD FACEBOOK SDK ********************/
$(document).ready(function(){
	//EXTEND CONFIG
	if(typeof FACEBOOK_CONFIG !== 'undefined' && FACEBOOK_CONFIG != null){
		$.extend(FACEBOOK, FACEBOOK_CONFIG);
	};
	if(typeof FACEBOOK_FUNCTIONS !== 'undefined' && FACEBOOK_FUNCTIONS != null){
		$.extend(FACEBOOK, FACEBOOK_FUNCTIONS);
	};
	//LOAD THE FACEBOOK SDK ASYNCHRONOUSLY
	(function(d){
		var js, id = 'facebook-jssdk', ref = d.getElementsByTagName('script')[0];
		if (d.getElementById(id)) {return;};
		js = d.createElement('script'); js.id = id; js.async = true;
		js.src = "//connect.facebook.com/en_US/sdk.js";
		ref.parentNode.insertBefore(js, ref);
	}(document));
});


/******************** FACEBOOK INIT ********************/
window.fbAsyncInit = function() {
	if(FACEBOOK.app_id != ''){
		//INIT THE SDK
		FB.init({
			version:	'v2.1',
			appId:		FACEBOOK.app_id,		// App ID
			channelUrl:	FACEBOOK.channel_file,	// Path to your Channel File
			status:		true,					// check login status
			cookie:		true,					// enable cookies to allow the server to access the session
			xfbml:		true,					// parse XFBML
			oauth:		true
		});
		//GET LOGIN STATUS ON INITIALISE
		FB.getLoginStatus(function(response) {
			FACEBOOK.status_change(response);
			FACEBOOK.got_status = true;
		},true);
		//LISTEN FOR AND HANDLE LOGIN STATUS CHANGES
		FB.Event.subscribe('auth.statusChange', function(response) {
			FACEBOOK.status_change(response);
		});
		//FACEBOOK CONNECTION INITIALISED
		FACEBOOK.initialise();
	};
};




