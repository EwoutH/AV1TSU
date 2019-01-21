#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class options
{
public:
	void enter_options();
	void splicing();
	void keyframe_list();
	void keyframe_counting();
	void creating_core_splices_list();
	void adding_leftover_core_splices();
	void merging_core_splices();
	void delete_unwanted_files();
	void encoding();
	string name;
	string splicing_command;
	string keyframe_list_command = "\"(for %i in (*spliced_*) do @echo file '%i') > keyframes.txt\"";
	int keyframes = 0;
	string keyframe_text;
	int cores = 1;
	int int_keyframe_index = 0;
	int current_core = 1;
	string video_quality;
	string string_keyframe_index;
	string string_current_core;
	string encoding_command;
	string speed;
	string final_merging_command;
	string string_cores;
};

