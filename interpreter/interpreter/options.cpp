#include "options.h"
#include <iostream>
#include <fstream>
#include <string>
#include "options.h"
#include <windows.h>
using namespace std;
ofstream out("merge.txt");
ofstream something("something.txt");

void options::enter_options()
{
	cout << "Enter full name (example: test.mp4) of the file: ";
	cin >> name;
	cout << "Enter video quality: ";
	cin >> video_quality;
	cout << "How many cores can encoder use?: ";
	cin >> cores;
	cout << "What speed setting should encoder use?: ";
	cin >> speed;

}
void options::splicing()
{
	splicing_command = "\"ffmpeg -i ";
	splicing_command += name;
	splicing_command += " -acodec copy -f segment -vcodec copy spliced_%d.mp4\"";
	system((splicing_command).c_str());
}
void options::keyframe_list()
{
	system((keyframe_list_command).c_str());
}
void options::keyframe_counting()
{
	ifstream in("keyframes.txt");
	while (getline(in, keyframe_text))
	{
		keyframes++;
	}
}
void options::creating_core_splices_list()
{
	for (int i = 0; i < (keyframes / cores); i++)
	{
		string_keyframe_index = to_string(int_keyframe_index);
		out << "file 'spliced_" << string_keyframe_index << ".mp4'" << endl;
		int_keyframe_index++;
	}
}
void options::adding_leftover_core_splices()
{
	if (current_core == cores)
	{
		for (int j = 0; j < keyframes%cores; j++)
		{
			string_keyframe_index = to_string(int_keyframe_index);
			out << "file 'spliced_" << string_keyframe_index << ".mp4'" << endl;
			int_keyframe_index++;
		}
	}
}
void options::merging_core_splices()
{
	string_current_core = to_string(current_core);
	system(("ffmpeg -f concat -i merge.txt -c copy merged_" + string_current_core + ".mkv").c_str());
}
void options::encoding()
{
	encoding_command = "start ffmpeg -i merged_";
	encoding_command += string_current_core;
	encoding_command += ".mkv ";
	//encoding_command += "-c:v libx264 ";
	encoding_command += " -c:v libaom-av1 -strict experimental ";
	encoding_command += "-crf ";
	encoding_command += video_quality;
	encoding_command += " -b:v 0";
	encoding_command += " -cpu-used ";
	encoding_command += speed;
	encoding_command += " -row-mt 1 -tiles 2x2 -pix_fmt yuv420p10le";
	encoding_command += " -c:a libopus -ac 2 -b:a 64k -vbr on -compression_level 10";
	encoding_command += " encoded_";
	encoding_command += string_current_core;
	encoding_command += ".mkv";
	system((encoding_command).c_str());
}
void options::delete_unwanted_files()
{
	cout << "AFTER encoding screens close, press ENTER to merge files" << endl;

	system("pause");
	system("break>merge.txt");
	for (int i = 1; i <= cores; i++)
	{
		something << "file 'encoded_" << i << ".mkv'" << endl;
	}
	system("ffmpeg -f concat -i something.txt -c copy output.mkv");
	cout << "After merging , to delete everything ";
	system("pause");
	out.close();
	something.close();
	system("del *encoded_*");
	system("del *spliced_*");
	system("del *merged_*");
	system("del keyframes.txt");
	system("del merge.txt");
	system("del something.txt");
}
