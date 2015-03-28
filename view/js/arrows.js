	$("#up").click(function () {
		ajaxSend('forward');
	});
	
	$("#down").click(function () {
		ajaxSend('reverse');
	});
	
	$("#left").click(function () {
		ajaxSend('left');
	});
	
	$("#right").click(function () {
		ajaxSend('right');
	});
	
	$("#release").click(function () {
		ajaxSend('stop');
		ajaxSend('release');
	});