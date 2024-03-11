#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include <memory>
#include <string>

#include "TextEditor.h"
#include "addons/imguifilesystem/imguifilesystem.h"

#include "window.h"
#include "song_manager.h"

class Dmf_Importer;

class Editor_Window : public Window
{
	public:
		Editor_Window();

		void resize();

		void display() override;
		void fontResize();
		void close_request() override;
		std::string dump_state() override;

		void play_song(uint32_t position = 0);
		void stop_song();

		void play_from_cursor();
		void play_from_line();

	private:
		const char* default_filename = "Untitled.mml";
		const char* default_filter = ".mml;.muc;.txt";

		void show_player_error();
		void show_close_warning();
		void show_warning();
		void handle_file_io();

		int load_file(const char* fn);
		int save_file(const char* fn);
		void export_file(const char* fn);
		int prepare_import_file(const char* fn);
		int import_file();

		std::string get_display_filename() const;
		std::string get_export_filename() const;
		void show_player_controls();
		void get_compile_result();
		void show_track_positions();

		void show_import_settings();
		void show_export_menu();

		inline void set_flag(uint32_t data) { flag |= data; };
		inline void clear_flag(uint32_t data) { flag &= ~data; };
		inline bool test_flag(uint32_t data) { return flag & data; };

		// Text editor state
		TextEditor editor;

		// File selection state
		ImGuiFs::Dialog fs;
		std::string filename;
		uint32_t flag;

		// Import state
		std::shared_ptr<Dmf_Importer> dmf_importer;
		bool import_patches;
		bool import_patterns;
		bool save_samples;

		// Export state
		std::string export_filter;
		unsigned int export_format;

		// Song manager state
		std::shared_ptr<Song_Manager> song_manager;

		// Playback error string
		std::string player_error;

		// Song position
		uint32_t line_pos;
		uint32_t cursor_pos;

		// test code
		double scale_log;
		double scale_log_old;

};

#endif
