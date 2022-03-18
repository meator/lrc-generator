// header file for the generator class
#include "../headers/lrc-generator.h"
// curses library
#include <ncurses.h>

void Lrc_generator::interface_setup(void)
{
	// splits the terminal: a left section with a menu and a right one with the lyrics
	getmaxyx(stdscr, this->height, this->width);
	this->menu = newwin(this->height, this->width / 2, 0, 0);
	this->lyrics_win = newwin(this->height, this->width / 2, 0, this->width / 2);
}

void Lrc_generator::draw_menu(void)
{

	// menu options
	const int opts = 6;
	std::string menu_items[opts] = {
		"start syncing",
		"set title",
		"set artist",
		"set album",
		"set creator",
		"quit program"};
	const int hoff = 1;
	const int woff = 1;
	// draw options on the menu window
	wclear(this->menu);
	wstandout(this->menu);
	mvwaddstr(this->menu, hoff, woff, "Menu");
	wstandend(this->menu);
	int i;
	for (i = 1; i <= opts; i++)
	{
		mvwprintw(this->menu, i + hoff, woff, "%d: %s\n", i - 1, menu_items[i - 1].c_str());
	}
	wmove(this->menu, hoff + i, woff);
	waddstr(this->menu, ">> ");
	box(this->menu, 0, 0);
	wrefresh(this->menu);
}

void Lrc_generator::set_attr_dialog(std::string attr)
{
	WINDOW *dialog = newwin(4, 50, 20, 50);
	bool not_ok = true;
	char value[20] = {0};
	char ans;
	char c;
	int i = 0;
	const int hoff = 1;
	const int woff = 1;
	do
	{
		wclear(dialog);
		box(dialog, 0, 0);
		mvwprintw(dialog, hoff, woff, "Song %s: ", attr.c_str());
		i = 0;
		do
		{
			c = wgetch(dialog);
			value[i] = c;
			waddch(dialog, c);
			wrefresh(dialog);
			i++;
		} while (c != '\n');
		value[i - 1] = '\0';

		mvwprintw(dialog, hoff + 1, woff, "Is %s ok? [y/n]", value);
		box(dialog, 0, 0);
		ans = wgetch(dialog);
		if (ans == 'y')
		{
			not_ok = false;
		}
		wrefresh(dialog);
	} while (not_ok);

	// now write it to the file
	if (attr.compare("cr") == 0)
	{
		attr.assign("by"); // the creator attribute has another abbreviation
	}
	// push this metadata (updates if it was already set)
	/// TODO: improve this
	size_t j = 0;
	for(;j < this->metadata.size(); j++) {
		if(this->metadata[j].find("[" + attr.substr(0, 2) + ": ") != std::string::npos) {
			this->metadata[j].erase();
			this->metadata[j] = "[" + attr.substr(0, 2) + ": " + value + "]";
			break;
		}
	}
	if(j == this->metadata.size()) {
		this->metadata.push_back("[" + attr.substr(0, 2) + ": " + value + "]");
	}
	// deletes this window
	delwin(dialog);
}
