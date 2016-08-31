var CarModel = Backbone.Model.extend({
	initialize: function() {

	},

	add: function(data) {
		for (var key in data)
			this.set(key, data[key]);
	},

	formatTime: function(key) {
		var result = this.get(key);

		if (result == -1)
			result = "N/A";
		else
			result = parseFloat(result).toFixed(3) + "s";

		return result;
	}
});

