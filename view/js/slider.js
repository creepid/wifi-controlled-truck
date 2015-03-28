$(function() {
$( "#slider-range-max" ).slider({
range: "max",
min: 0,
max: 180,
value: 0,
slide: function( event, ui ) {
$( "#amount" ).val( ui.value );
}
});
$( "#amount" ).val( $( "#slider-range-max" ).slider( "value" ) );
});