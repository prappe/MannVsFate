#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

#include "tfbot.h"
#include "wavespawn.h"
#include <string>
#include <fstream>

class wave_generator
{
	const std::string version = "0.1.11";

public:
	// Accessors.
	void set_map_name(const std::string& in);
	void set_mission_name(const std::string& in);
	void set_starting_currency(int in);
	void set_waves(int in);
	void set_respawn_wave_time(int in);
	void set_event_popfile(int in);
	void set_fixed_respawn_wave_time(bool in);
	void set_add_sentry_buster_when_damage_dealt_exceeds(int in);
	void set_add_sentry_buster_when_kill_count_exceeds(int in);
	void set_can_bots_attack_while_in_spawn_room(int in);
	void set_sentry_buster_cooldown(float in);
	void set_players(int in);
	void set_currency_per_wave(int in);
	void set_max_time(int in);
	void set_tank_chance(float in);
	void set_max_icons(int in);
	void set_max_wavespawns(int in);
	void set_possible_classes(const std::vector<player_class>& classes);
	// Generate the mission. argc and argv are taken only to be printed in the mission file as debug info.
	void generate_mission(int argc = 1, char** argv = nullptr);

private:
	// The popfile being written to.
	std::ofstream popfile;
	// Filename prefix.
	std::string map_name = "mvm_bigrock";
	// Filename suffix.
	std::string mission_name = "gen";
	// Indentation level.
	int indent = 0;
	// The current wave being generated.
	int current_wave = 0;

	// A bunch of settings that end up at the top of the mission file.

	int starting_currency = 2000;
	int respawn_wave_time = 2;
	int event_popfile = 0;
	bool fixed_respawn_wave_time = false;
	int add_sentry_buster_when_damage_dealt_exceeds = 3000;
	int add_sentry_buster_when_kill_count_exceeds = 15;
	int can_bots_attack_while_in_spawn_room = 0;
	float sentry_buster_cooldown = 35.0f;

	// The total number of waves.
	int waves = 7;
	// How many players the mission is intended for.
	int players = 4;
	// The base pressure decay rate, measured per player.
	int base_pressure_decay_rate = 50;
	// The pressure decay rate multiplier.
	float pressure_decay_rate_multiplier = 0.03f;
	// The maximum number of wavespawns per wave.
	unsigned int max_wavespawns = 30;
	// The maximum amount of time that a wave can last.
	int max_time = 300;
	// The maximum number of unique icons per wave. There can be 23 icons before the HUD starts to look stupid.
	unsigned int max_icons = 23;
	// How much currency the players earn per wave.
	int currency_per_wave = 1500;
	// The amount by which currency is multiplied when used to increase pressure.
	float currency_pressure_multiplier = 0.8f;
	// The chance that a tank will exist in the wave.
	float tank_chance = 0.4f;
	// The possible classes that the wave generator can choose from.
	std::vector<player_class> possible_classes = {
		player_class::scout,
		player_class::soldier,
		player_class::pyro,
		player_class::demoman,
		player_class::heavyweapons,
		player_class::engineer,
		player_class::medic,
		player_class::sniper,
		player_class::spy
	};

	// Write a number of indents based on the indentation level.
	void write_indents();
	// Writes a line to the popfile, taking the indentation level into account.
	void write(const std::string& str);
	// Write a string followed by a space followed by an integer.
	void write(const std::string& str, int number);
	// Write a string followed by a space followed by a float.
	void write(const std::string& str, float number);
	// Write a string followed by a space followed by another string.
	void write(const std::string& str1, const std::string& str2);
	// Writes an empty line. It just writes the newline character.
	void write_blank();
	// Starts a block with { and indents. Prior to the {, str is on its own line.
	void block_start(const std::string& str);
	// Ends a block with } and unindents.
	void block_end();
	// Make a bot into a giant.
	void make_bot_into_giant(tfbot& bot, bool& isGiant, float& move_speed_bonus, float& chanceMult, float& bot_pressure, bool& isBoss, bool& isAlwaysCrit);
	// Calculate the effective pressure decay rate.
	void wave_generator::calculate_effective_pressure_decay_rate
	(const float& pressure_decay_rate, float& effective_pressure_decay_rate, const std::vector<wavespawn>& wavespawns, const int& t);
};

#endif