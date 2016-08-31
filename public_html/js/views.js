var OverviewPageView = Backbone.View.extend({
	el: "#overview",

	initialize: function() {
		this.listenTo(this.model, "change:gear", this.renderGear);
		this.listenTo(this.model, "change:engine_rpm", this.renderRevs);
		this.listenTo(this.model, "change:max_engine_rpm", this.updateMaxRevs);
		this.listenTo(this.model, "change:engine_oil_pressure", this.renderEngineOilPressure);
		this.listenTo(this.model, "change:car_speed", this.renderSpeed);
		this.listenTo(this.model, "change:throttle_pedal", this.renderPedals);
		this.listenTo(this.model, "change:brake_pedal", this.renderPedals);
		this.listenTo(this.model, "change:clutch_pedal", this.renderPedals);
		this.listenTo(this.model, "change:time", this.renderTimes);
		this.listenTo(this.model, "change:lap_time_best_self", this.renderTimes);
		this.listenTo(this.model, "change:lap_time_current_self", this.renderTimes);
	},

	renderGear: function() {
		var gear = this.model.get("gear");

		var text;
		switch (gear) {
			case -1: text = "R"; break;
			case 0: text = "N"; break;
			default: text = gear; break;
		}

		this.$("#gear .value").text(text);
	},

	updateMaxRevs: function() {
		$("#rpm-slider").attr("max", this.model.get("max_engine_rpm"));
		this.renderRevs();
	},

	renderRevs: function() {
		var rpm = Math.round(this.model.get("engine_rpm"));
		var max_rpm = this.model.get("max_engine_rpm");

		$("#rpm-slider").slider("option", "theme", rpm > max_rpm * 0.9 ? "b" : "a");
		$("#rpm-slider").val(rpm).slider("refresh");
	},

	renderEngineOilPressure: function() {
		var pressure = this.model.get("engine_oil_pressure");
		$("#rpm-slider").slider(pressure > 0 ? "enable" : "disable");
	},

	renderSpeed: function() {
		var text = Math.round(this.model.get("car_speed"));
		this.$("#speed .value").text(text);
	},

	renderPedals: function() {
		var throttle = this.model.get("throttle_pedal") * 100;
		var brake = this.model.get("brake_pedal") * 100;
		var clutch = this.model.get("clutch_pedal") * 100;

		this.$("#throttle-pedal-slider").val(throttle).slider("refresh");
		this.$("#brake-pedal-slider").val(brake).slider("refresh");
		this.$("#clutch-pedal-slider").val(clutch).slider("refresh");
	},

	renderTimes: function() {
		var best_time = this.model.formatTime("lap_time_best_self");
		var current_time = this.model.formatTime("lap_time_current_self");

		this.$("#current-time").val(current_time);
		this.$("#best-time").val(best_time);
	}
});

var ChartsPageView = Backbone.View.extend({
	el: "#charts",

	initialize: function() {
		this.views = [];
		this.views.push(new GraphView({ el: "#engine_rpm-block", attrName: "engine_rpm", model: this.model }));
		this.views.push(new GraphView({ el: "#car_speed-block", attrName: "car_speed", model: this.model }));
		this.views.push(new GraphView({ el: "#gear-block", attrName: "gear", model: this.model }));
	}
});

var GraphView = Backbone.View.extend({
	initialize: function(blubb) {
		this.attrName = blubb["attrName"];
		this.counter = 0;
		this.dps = [];
		this.renderGraph();
		this.listenTo(this.model, "change:ticks", this.updateGraph);
	},

	renderGraph: function() {
		this.$(".graph").CanvasJSChart({
			interactivityEnabled: false,
			animationEnabled: false,
			theme: "theme1",
			axisY: {
				gridThickness: 0
			},
			axisX: {
				valueFormatString: " ",
				tickLength: 0
			},
			data: [{
				type: "line", // line/spline
				markerType: "none",
				dataPoints: this.dps
			}]
		});

		this.chart = this.$(".graph").CanvasJSChart();
	},

	updateGraph: function() {
		if (this.dps.length > 30)
			this.dps.shift();

		this.dps.push(
			{
				x: this.counter++,
				y: this.model.get(this.attrName)
			}
		);

		this.chart.render();

		this.$(".value").text(this.model.get(this.attrName));
	}
});

