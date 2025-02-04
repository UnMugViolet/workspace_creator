#ifndef SETTINGS_H
#define SETTINGS_H
struct web_browser
{
	unsigned int id;
	char name[50];
	char command[65];
};

struct code_editor
{
  unsigned int id;
  char name[50];
  char command[65];
};

// code_editors.c
void  initialize_code_editor();
void  list_code_editors();
struct code_editor *choose_code_editor();

// web_browsers.c
void  initialize_browsers();
void  list_browsers();
struct web_browser *choose_browser();
struct web_browser *load_selected_browser();
void save_selected_browser(struct web_browser *selected_browser);

// settings.c
void  settings_menu();
void	add_workspace(char *workspace_name);
void	remove_workspace();
void	help(void);
void	usage(void);

#endif // SETTINGS_H