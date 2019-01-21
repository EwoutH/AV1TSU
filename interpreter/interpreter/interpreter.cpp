#include <iostream>
#include <fstream>
#include <string>
#include "options.h"
using namespace std;
int main()
{
	options commands;
	commands.enter_options();
	commands.splicing();
	commands.keyframe_list();
	commands.keyframe_counting();
	for (commands.current_core; commands.current_core <= commands.cores; commands.current_core++)
	{
		ofstream out("merge.txt");
		commands.creating_core_splices_list();
		commands.adding_leftover_core_splices();
		commands.merging_core_splices();
		commands.encoding();
	}
	commands.delete_unwanted_files();
	cin.ignore();
}