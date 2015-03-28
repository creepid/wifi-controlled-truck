var keys = [];
var ar=new Array(33,34,35,36,37,38,39,40);
var xTriggered = 0;

$(document).keydown(function(event) {
 var startParam;
 var key = event.which;
      if($.inArray(key,ar) > -1) {
		  if (!($.inArray(key,keys) > -1)){
				keys.push(key);
				switch (key){
					case 38: startParam = 'forward'; break;
					case 40: startParam = 'reverse'; break; 
					case 39: startParam = 'right'; break; 
					case 37: startParam = 'left'; break; 
					default:;
				}
				ajaxSend(startParam);
				xTriggered++;
				$.print("Command start->"+ startParam +": "+xTriggered+' times', 'html');
		  };
          
          event.preventDefault();
          return false;
      }
      return true;
});

$(document).keyup(function(event) {
	xTriggered = 0;
	var stopParam;
	var key = event.which;
	if($.inArray(key,ar) > -1) {
		keys.splice( $.inArray(key,keys) ,1 );
		switch (key){
					case 38: 
					case 40: stopParam = 'stop'; break;
					case 39:
					case 37: stopParam = 'release'; break;
					default:;	
		}
		ajaxSend(stopParam);		
		$.print("Command stop->"+ stopParam +" "+xTriggered+" times", 'html');
	}
});

function printKeys() {
    var html = '';
    for (var i in keys) {
        if (!keys.hasOwnProperty(i)) continue;
        html += '<p>' + i + '</p>';
    }
    $('#out').html(html);
};

$('#other').click(function() {
$('#target').keydown();
});