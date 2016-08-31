var ws;
var car;
var view;

var connect = function() {
	$.mobile.loading("show", {
		text: "Establishing connection...",
		textVisible: true,
		theme: "b"
	});

	ws = new WebSocket("ws://localhost:8080/ws");
	ws.onopen = onOpen;
	ws.onerror = onError;
	ws.onmessage = onMessage;
};

var onOpen = function() {
	$.mobile.loading("hide");

	return;

	$.mobile.loading("show", {
		text: "Waiting for R3E to start...",
		textVisible: true,
		theme: "b"
	});
};

var onMessage = function(event) {
	var data = JSON.parse(event.data);
	car.add(data);
};

var onError = function(e) {
	console.log("Error occurred.", e);
	console.log("Reconnecting in 3s");

	this.close(); // TODO: needed?
	setTimeout(connect, 3000);
};

$(document).on("ready", function() {
	$("[data-role='header'], [data-role='footer']").toolbar();
	$("[data-role='navbar']").navbar();
	$("[data-role='panel']").panel().enhanceWithin();

	car = new CarModel();
	view = new OverviewPageView({ model: car });
	view2 = new ChartsPageView({ model: car });
	connect();
});
