		var FACEBOOK_FUNCTIONS = 
		{
			fnc_auto_auth: function()
			{

			},
			fnc_revoked: function()
			{
				//alert('logged out');
			}
		}

		function logOut()
		{

			$( "#logOUT" ).hide();
			$( "#logIN" ).show();
			// $('#displayContent').html('');
			FACEBOOK.revoke();
			FACEBOOK.logout();
			$('#profilePhotoHolder').empty();			
			$('#coverPhotosHolder').empty();
			$('#personalInfoHolder').empty();
			$('#show').empty();
			//$('img').empty();
		}



		function test()
		{
			
			$( "#logIN" ).hide();
  			$( "#logOUT" ).css("display", "block");
	

	


			/* make the API friends call */
			FACEBOOK.get_app_friends(friends);

			function friends(response)
			{
				// console.log(response);
				// console.log("Display friends on App above");
			}

			/* make the API likes call */
			FACEBOOK.get_likes(likes);

			function likes(response)
			{
				 console.log(response);
				 console.log("Show likes above");
				 var count = 0;

				 for(var t in response.data)
				 {
				 		count++;
						var allLikes = response.data[t].name;

					
						// console.log('is this working?');
						// var likeOne = response.data[0].name;
						// var likeTwo = response.data[1].name;
						// var likeThree = response.data[2].name;
						// var likeFour = response.data[3].name;
						// var likeFive = response.data[4].name;
						callMusic(allLikes);

						//Search LastFM database based on first like

						// $('#personalInfoHolder').append('<p>'+ allLikes +'</p>');
						// $('#personalInfoHolder').append('<p>'+ likeTwo +'</p>');
						// $('#personalInfoHolder').append('<p>'+ likeThree +'</p>');
						// $('#personalInfoHolder').append('<p>'+ likeFour +'</p>');
						// $('#personalInfoHolder').append('<p>'+ likeFive +'</p>');
						// return;

						if(count>25)
						{
							$('#show').prepend('<li><p>Suggested music from Last.FM based on FB likes:</p></li>');
							return;
						}
				 }
			}

			/* make the API photos call */
			// FACEBOOK.get_photos(photos);

			// function photos(response)
			// {
			// 	console.log(response);
			// 	console.log("show tagged photos");
			// }


			FACEBOOK.get_personal_info(personal);

			function personal(response)
			{

				//console.log('personal shit here');
				//console.log(response);
				var profileInfo = response.name;
				console.log(profileInfo);
				$('#personalInfoHolder').append('<p>'+ profileInfo +' likes: </p>');

			}





			FACEBOOK.get_albums(albums);

			function albums(response)
			{

				// console.log(response);
				// console.log("show photos from albums");
				coverPhotosHolder(response);


				for(var t in response.data)
				{
					var allAlbums = response.data[t].name;
				//	console.log(allAlbums);

					if (allAlbums == 'Profile Pictures')
					{

						// var tester = response.data[t].id;
						var profilePhoto = response.data[t].photos.data[0].images[0].source;
				//		console.log(profilePhoto);
						$('#profilePhotoHolder').prepend('<img src = "'+ profilePhoto +'"></img>');
						return;

					}
				}

			}

			function coverPhotosHolder(response)
			{

				//console.log(response)

				for(var t in response.data)
				{
					var allAlbums = response.data[t].name;

					if (allAlbums == 'Cover Photos')
					{
						// console.log('is this working?');
						var photoOne = response.data[t].photos.data[1].images[0].source;
						var photoTwo = response.data[t].photos.data[2].images[0].source;
						var photoThree = response.data[t].photos.data[3].images[0].source;
						var photoFour = response.data[t].photos.data[4].images[0].source;
						var photoFive = response.data[t].photos.data[5].images[0].source;

						$('#coverPhotosHolder').append('<img class = "smallImage" src = "'+ photoOne +'"></img>');
						$('#coverPhotosHolder').append('<img class = "smallImage" src = "'+ photoTwo +'"></img>');
						$('#coverPhotosHolder').append('<img class = "smallImage" src = "'+ photoThree +'"></img>');
						$('#coverPhotosHolder').append('<img class = "smallImage" src = "'+ photoFour +'"></img>');
						return;

					}
				}

			}



			function callMusic(allLikes){


				// var likeOne = response.data[0].name;
				// var likeTwo = response.data[1].name;
				// var likeThree = response.data[2].name;
				// var likeFour = response.data[3].name;
				// var likeFive = response.data[4].name;

				$.ajax({
					type: "get",
					url: 'http://ws.audioscrobbler.com/2.0/?method=artist.getinfo&artist='+ allLikes +'&api_key=2841b5202cade09caf60fcec121752af&format=json',
					dataType: "json",
					async: false,
					//timeout: 20000,
					//processdata: true,
					cache: false,
					global: false,
					contentTypeString: "application/x-www-form-urlencoded",
					//SUCCESS
					success: function(response){
			  			console.log('---------- i just got my music response -----------');
						console.log(response);
						callMusicCallback(allLikes, response);
					},
					//ERROR
					error: function(xhr, status, error){
						alert('Refresh to try again');
						//console.log(xhr);
						//console.log(status);
						//console.log(error);
					}
				});
			}

			//THIS TAKES THE INFORMATION IN THE CONSOLE, DISPLAYS IT IN THE BODY AND THEN CALLS NEXT FUNCTION

			function callMusicCallback(likes, bla){

					console.log(bla.error);
					console.log(bla.message);
					if(typeof(bla.error) == 'undefined')
					{

						console.log
						$('#personalInfoHolder').append('<p>'+ likes +'</p>');
			  			console.log('---------- i just made my music response callback -----------');
				// console.log(bla);

						var url = bla.artist.url;
						var name = bla.artist.name;
						//console.log(name);
						//console.log(url);
						$('#show').append('<li><p><a href ="'+ url +'">' + name + '</a></p></li>');
			  			console.log('---------- i just finished my music list and called get similar artists -----------');
						// getSimilarArtists(bla);
						
					}
					else
					{
						console.log('ERROR HAS HAPPENED');
						return;
					}

			}



			

			/* make the API profile photos call */
			// FACEBOOK.get_profile(picture);

			// function picture(response)
			// {
			// 	console.log(response);
			// 	console.log("what profile picture do you have?");
			// }
			
		}


