#ifndef DMF_IMPORTER_H
#define DMF_IMPORTER_H

#include <vector>
#include <string>
#include <cstdint>
#include <utility>
#include <map>

class Pattern_Mml_Writer;
class Dmf_Importer
{
	public:
		Dmf_Importer(const char* filename);

		std::string get_error();
		std::string get_mml();

	private:
		void parse();
		uint8_t* parse_fm_instrument(uint8_t* ptr, int id, std::string str);
		uint8_t* parse_psg_instrument(uint8_t* ptr, int id, std::string str);
		void parse_patterns(Pattern_Mml_Writer& writer);

		std::string error_output;
		std::string mml_output;
		std::vector<uint8_t> data;

		uint8_t channel_count;
		uint8_t pattern_rows;
		uint8_t matrix_rows;
		uint8_t instrument_count;

		uint8_t speed;
		uint8_t highlight_b;

		struct Channel_Row {
			int16_t note = 0;
			int16_t octave = 0;
			int16_t volume;
			std::vector<std::pair<int16_t,int16_t>> effects;
			int16_t instrument;
		};

		std::vector<std::vector<std::vector<Channel_Row>>> channel_pattern_rows;
};


class Pattern_Mml_Writer
{
	public:
		struct Row
		{
			enum Type {
				TIE,
				NOTE,
				SLUR,
				REST,
			} type;
			int16_t note;
			int16_t octave;
			std::string mml;
		};
		struct Channel
		{
			bool optimizable; // Optimizable if no unknown effects were used.
			std::map<int, Row> rows;
		};
		struct Pattern
		{
			int length = 64*6;
			std::vector<Channel> channels;
		};

		Pattern_Mml_Writer(int initial_whole_len = 96, int number_of_patterns = 1);
		std::string output_all();
		std::string output_line(int pattern, int channel, int default_length);
		std::string convert_length(int length, int starting_time, int default_length, char tie_char);

		int whole_len;
		int smallest_len;
		std::vector<Pattern> patterns;
};

#endif
