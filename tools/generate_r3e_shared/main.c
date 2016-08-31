#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "r3e.h"

r3e_shared data;

void print_binary_data()
{
	printf("  \"binary\": \"");
	for (int i = 0; i < sizeof(r3e_shared); i++)
		printf("%02x", ((unsigned char*)&data)[i]);

	printf("\"");
}

void print_struct()
{
	printf("  \"struct\": {\n");
	printf("    \"user_input\": [%f, %f, %f, %f, %f, %f],\n",
		data.user_input[0], data.user_input[1], data.user_input[2],
		data.user_input[3], data.user_input[4], data.user_input[5]);
	printf("    \"engine_rps\": %f,\n", data.engine_rps);
	printf("    \"max_engine_rps\": %f,\n", data.max_engine_rps);
	printf("    \"fuel_pressure\": %f,\n", data.fuel_pressure);
	printf("    \"fuel_left\": %f,\n", data.fuel_left);
	printf("    \"fuel_capacity\": %f,\n", data.fuel_capacity);
	printf("    \"engine_water_temp\": %f,\n", data.engine_water_temp);
	printf("    \"engine_oil_temp\": %f,\n", data.engine_oil_temp);
	printf("    \"engine_oil_pressure\": %f,\n", data.engine_oil_pressure);
	printf("    \"car_speed\": %f,\n", data.car_speed);
	printf("    \"number_of_laps\": %d,\n", data.number_of_laps);
	printf("    \"completed_laps\": %d,\n", data.completed_laps);
	printf("    \"lap_time_best_self\": %f,\n", data.lap_time_best_self);
	printf("    \"lap_time_previous_self\": %f,\n", data.lap_time_previous_self);
	printf("    \"lap_time_current_self\": %f,\n", data.lap_time_current_self);
	printf("    \"position\": %d,\n", data.position);
	printf("    \"num_cars\": %d,\n", data.num_cars);
	printf("    \"gear\": %d,\n", data.gear);
	printf("    \"tire_temps\": {\n");
	printf("      \"frontleft_left\": %f,\n", data.tire_temps.frontleft_left);
	printf("      \"frontleft_center\": %f,\n", data.tire_temps.frontleft_center);
	printf("      \"frontleft_right\": %f,\n", data.tire_temps.frontleft_right);
	printf("      \"frontright_left\": %f,\n", data.tire_temps.frontright_left);
	printf("      \"frontright_center\": %f,\n", data.tire_temps.frontright_center);
	printf("      \"frontright_right\": %f,\n", data.tire_temps.frontright_right);
	printf("      \"rearleft_left\": %f,\n", data.tire_temps.rearleft_left);
	printf("      \"rearleft_center\": %f,\n", data.tire_temps.rearleft_center);
	printf("      \"rearleft_right\": %f,\n", data.tire_temps.rearleft_right);
	printf("      \"rearright_left\": %f,\n", data.tire_temps.rearright_left);
	printf("      \"rearright_center\": %f,\n", data.tire_temps.rearright_center);
	printf("      \"rearright_right\": %f\n", data.tire_temps.rearright_right);
	printf("    },\n");
	printf("    \"num_penalties\": %d,\n", data.num_penalties);
	printf("    \"car_cg_location\": {\n");
	printf("      \"x\": %f,\n", data.car_cg_location.x);
	printf("      \"y\": %f,\n", data.car_cg_location.y);
	printf("      \"z\": %f\n", data.car_cg_location.z);
	printf("    },\n");
	printf("    \"car_orientation\": {\n");
	printf("      \"pitch\": %f,\n", data.car_orientation.pitch);
	printf("      \"yaw\": %f,\n", data.car_orientation.yaw);
	printf("      \"roll\": %f\n", data.car_orientation.roll);
	printf("    },\n");
	printf("    \"local_acceleration\": {\n");
	printf("      \"x\": %f,\n", data.local_acceleration.x);
	printf("      \"y\": %f,\n", data.local_acceleration.y);
	printf("      \"z\": %f\n", data.local_acceleration.z);
	printf("    },\n");
	printf("    \"drs_available\": %d,\n", data.drs_available);
	printf("    \"drs_engaged\": %d,\n", data.drs_engaged);
	printf("    \"_padding1\": %d,\n", data._padding1);
	printf("    \"player\": {\n");
	printf("      \"game_simulation_ticks\": %d,\n", data.player.game_simulation_ticks);
	printf("      \"_padding1\": %d,\n", data.player._padding1);
	printf("      \"game_simulation_time\": %f,\n", data.player.game_simulation_time);
	printf("      \"position\": {\n");
	printf("        \"x\": %f,\n", data.player.position.x);
	printf("        \"y\": %f,\n", data.player.position.y);
	printf("        \"z\": %f\n", data.player.position.z);
	printf("      },\n");
	printf("      \"velocity\": {\n");
	printf("        \"x\": %f,\n", data.player.velocity.x);
	printf("        \"y\": %f,\n", data.player.velocity.y);
	printf("        \"z\": %f\n", data.player.velocity.z);
	printf("      },\n");
	printf("      \"acceleration\": {\n");
	printf("        \"x\": %f,\n", data.player.acceleration.x);
	printf("        \"y\": %f,\n", data.player.acceleration.y);
	printf("        \"z\": %f\n", data.player.acceleration.z);
	printf("      },\n");
	printf("      \"local_acceleration\": {\n");
	printf("        \"x\": %f,\n", data.player.local_acceleration.x);
	printf("        \"y\": %f,\n", data.player.local_acceleration.y);
	printf("        \"z\": %f\n", data.player.local_acceleration.z);
	printf("      },\n");
	printf("      \"orientation\": {\n");
	printf("        \"x\": %f,\n", data.player.orientation.x);
	printf("        \"y\": %f,\n", data.player.orientation.y);
	printf("        \"z\": %f\n", data.player.orientation.z);
	printf("      },\n");
	printf("      \"rotation\": {\n");
	printf("        \"x\": %f,\n", data.player.rotation.x);
	printf("        \"y\": %f,\n", data.player.rotation.y);
	printf("        \"z\": %f\n", data.player.rotation.z);
	printf("      },\n");
	printf("      \"angular_acceleration\": {\n");
	printf("        \"x\": %f,\n", data.player.angular_acceleration.x);
	printf("        \"y\": %f,\n", data.player.angular_acceleration.y);
	printf("        \"z\": %f\n", data.player.angular_acceleration.z);
	printf("      },\n");
	printf("      \"reserved1\": {\n");
	printf("        \"x\": %f,\n", data.player.reserved1.x);
	printf("        \"y\": %f,\n", data.player.reserved1.y);
	printf("        \"z\": %f\n", data.player.reserved1.z);
	printf("      }\n");
	printf("    },\n");
	printf("    \"event_index\": %d,\n", data.event_index);
	printf("    \"session_type\": %d,\n", data.session_type);
	printf("    \"session_phase\": %d,\n", data.session_phase);
	printf("    \"session_iteration\": %d,\n", data.session_iteration);
	printf("    \"control_type\": %d,\n", data.control_type);
	printf("    \"throttle_pedal\": %f,\n", data.throttle_pedal);
	printf("    \"brake_pedal\": %f,\n", data.brake_pedal);
	printf("    \"clutch_pedal\": %f,\n", data.clutch_pedal);
	printf("    \"brake_bias\": %f,\n", data.brake_bias);
	printf("    \"tire_pressure\": {\n");
	printf("      \"front_left\": %f,\n", data.tire_pressure.front_left);
	printf("      \"front_right\": %f,\n", data.tire_pressure.front_right);
	printf("      \"rear_left\": %f,\n", data.tire_pressure.rear_left);
	printf("      \"rear_right\": %f\n", data.tire_pressure.rear_right);
	printf("    },\n");
	printf("    \"tire_wear_active\": %d,\n", data.tire_wear_active);
	printf("    \"tire_type\": %d,\n", data.tire_type);
	printf("    \"brake_temps\": {\n");
	printf("      \"front_left\": %f,\n", data.brake_temps.front_left);
	printf("      \"front_right\": %f,\n", data.brake_temps.front_right);
	printf("      \"rear_left\": %f,\n", data.brake_temps.rear_left);
	printf("      \"rear_right\": %f\n", data.brake_temps.rear_right);
	printf("    },\n");
	printf("    \"fuel_use_active\": %d,\n", data.fuel_use_active);
	printf("    \"session_time_remaining\": %f,\n", data.session_time_remaining);
	printf("    \"lap_time_best_leader\": %f,\n", data.lap_time_best_leader);
	printf("    \"lap_time_best_leader_class\": %f,\n", data.lap_time_best_leader_class);
	printf("    \"reserved1\": %f,\n", data.reserved1);
	printf("    \"lap_time_delta_leader\": %f,\n", data.lap_time_delta_leader);
	printf("    \"lap_time_delta_leader_class\": %f,\n", data.lap_time_delta_leader_class);
	printf("    \"reserved2\": [%f, %f, %f],\n", data.reserved2[0], data.reserved2[1], data.reserved2[2]);
	printf("    \"reserved3\": [%f, %f, %f],\n", data.reserved3[0], data.reserved3[1], data.reserved3[2]);
	printf("    \"reserved4\": [%f, %f, %f],\n", data.reserved4[0], data.reserved4[1], data.reserved4[2]);
	printf("    \"time_delta_front\": %f,\n", data.time_delta_front);
	printf("    \"time_delta_behind\": %f,\n", data.time_delta_behind);
	printf("    \"pit_window_status\": %d,\n", data.pit_window_status);
	printf("    \"pit_window_start\": %d,\n", data.pit_window_start);
	printf("    \"pit_window_end\": %d,\n", data.pit_window_end);
	printf("    \"cut_track_warnings\": %d,\n", data.cut_track_warnings);
	printf("    \"penalties\": {\n");
	printf("      \"drive_through\": %d,\n", data.penalties.drive_through);
	printf("      \"stop_and_go\": %d,\n", data.penalties.stop_and_go);
	printf("      \"pit_stop\": %d,\n", data.penalties.pit_stop);
	printf("      \"time_deduction\": %d,\n", data.penalties.time_deduction);
	printf("      \"slow_down\": %d\n", data.penalties.slow_down);
	printf("    },\n");
	printf("    \"flags\": {\n");
	printf("      \"yellow\": %d,\n", data.flags.yellow);
	printf("      \"blue\": %d,\n", data.flags.blue);
	printf("      \"black\": %d\n", data.flags.black);
	printf("    },\n");
	printf("    \"car_damage\": {\n");
	printf("      \"engine\": %f,\n", data.car_damage.engine);
	printf("      \"transmission\": %f,\n", data.car_damage.transmission);
	printf("      \"aerodynamics\": %f,\n", data.car_damage.aerodynamics);
	printf("      \"tire_front_left\": %f,\n", data.car_damage.tire_front_left);
	printf("      \"tire_front_right\": %f,\n", data.car_damage.tire_front_right);
	printf("      \"tire_rear_left\": %f,\n", data.car_damage.tire_rear_left);
	printf("      \"tire_rear_right\": %f\n", data.car_damage.tire_rear_right);
	printf("    }\n");
	printf("  }");
}

// not used, could randomly fill the structure given a seed
void generate_struct(unsigned int seed)
{
	memset(&data, 0x0, sizeof(r3e_shared));
	
	srand(seed);
	for (int i = 0; i < sizeof(r3e_shared); i++)
		((unsigned char*)&data)[i] = rand() % 255;
}

int main(int argc, char *argv[])
{
	read(STDIN_FILENO, &data, sizeof(r3e_shared));

	printf("{\n");
	print_binary_data();
	printf(",\n");
	print_struct();
	printf("\n}\n");

	return 0;
}

