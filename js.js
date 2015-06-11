$(document).ready(function()
{


		$( "#get" ).click(function() {
	  		console.log('i just clicked something');
			callMusic();
		});

		$('#myText').keypress(function(event)
		{
		  if(event.keyCode == 13){
		    $('#startSearch').click();
		  }
		});

		$( "#startSearch" ).click(function() {
			   var searchedArtist = document.getElementById("myText").value;
    			callMusic(searchedArtist);
    			
    			
		});


	//THIS CALLS THE MUSIC WITH AJAX TO OUR HTML PAGE + DISPLAYS IT IN CONSOLE

	function callMusic(searchedArtist){
		$.ajax({
			type: "get",
			url: 'http://ws.audioscrobbler.com/2.0/?method=artist.getinfo&artist='+ searchedArtist +'&api_key=2841b5202cade09caf60fcec121752af&format=json',
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
				callMusicCallback(response);
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

	function callMusicCallback(bla){
	  			console.log('---------- i just made my music response callback -----------');


				var url = bla.artist.url;
				var name = bla.artist.name;
				//console.log(name);
				//console.log(url);
				$('#show').empty();
				$('#show').append('<li><p> Artist name is: <a href ="'+ url +'">' + name + '</a></p></li>');
	  			console.log('---------- i just finished my music list and called get similar artists -----------');
				getSimilarArtists(bla);
	}

	//DISPLAYS SIMILAR ARTISTS and gets their top albums in the console log

	function getSimilarArtists(response){

		for(var i in response.artist.similar.artist)
		{
			var findSimilarArtists = response.artist.similar.artist[i]
			console.log(findSimilarArtists);

	

			$('#show').append('<li class = artist'+ i +'><span class=title>'+ findSimilarArtists.name +' top albums</span></li>');

		
			//console.log("please work");		
			var urls = ['http://ws.audioscrobbler.com/2.0/?method=artist.gettopalbums&artist='+ findSimilarArtists.name +'&api_key=2841b5202cade09caf60fcec121752af&format=json'];
			console.log(urls +' ' + i);

			console.log('---------- NEW ARTIST -----------');


			
			     $.ajax( 
				 { 
				 	type: "get",
					url: urls,
					dataType: "json",
					async: false,
					//timeout: 20000,
					//processdata: true,
					cache: false,
					global: false,
					contentTypeString: "application/x-www-form-urlencoded",
					//SUCCESS
						success: function(response){
				  			console.log('---------- I just got the top albums from ' + findSimilarArtists.name + ' and am now displaying in console.log-----------');
							//console.log(response);
							getMultipleTopAlbums(response, i);
						},
						//ERROR
						error: function(xhr, status, error){
							alert('Refresh to try again');
							//console.log(xhr);
							//console.log(status);
							//console.log(error);
						}

			       }
			     );
				console.log(i);
		

	    }

	
	}

	//TAKE THE TOP ALBUMS AND DISPLAY THEM AGAINST THE ARTIST THAT MADE THEM

	function getMultipleTopAlbums(pleasework, i)
	{
				console.log('---------- top albums received -----------');
				console.log(pleasework);


				
			for(var t in pleasework.topalbums.album)
			{
				var allTopAlbums = pleasework.topalbums.album[t]
				console.log(allTopAlbums);



				$('.artist'+ i +'').append('<li>'+ allTopAlbums.name +'</li>');
			}



	}



	
});
