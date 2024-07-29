#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct code_editor
{
	unsigned int id;
	char name[50];
	char command[65];
} *code_editors;

void initialize_code_editor()
{
	code_editors = malloc(sizeof(struct code_editor) * 7);
	if (code_editors == NULL)
	{
		perror("Failed to allocate memory for code_editors");
		exit(EXIT_FAILURE);
	}

	code_editors[1].id = 2;
	strcpy(code_editors[1].name, "Visual Studio Code");
	strcpy(code_editors[1].command, "code .");

	code_editors[0].id = 1;
	strcpy(code_editors[0].name, "Vim");
	strcpy(code_editors[0].command, "gnome-terminal");

	code_editors[2].id = 3;
	strcpy(code_editors[2].name, "Sublime Text");
	strcpy(code_editors[2].command, "subl .");

	code_editors[3].id = 4;
	strcpy(code_editors[3].name, "IntelliJ WebStorm");
	strcpy(code_editors[3].command, "webstorm .");

	code_editors[4].id = 5;
	strcpy(code_editors[4].name, "IntelliJ IDEA");
	strcpy(code_editors[4].command, "idea .");

	code_editors[5].id = 6;
	strcpy(code_editors[5].name, "IntelliJ PyCharm");
	strcpy(code_editors[5].command, "pycharm .");

	code_editors[6].id = 7;
	strcpy(code_editors[6].name, "Atom");
	strcpy(code_editors[6].command, "atom .");
}

void save_selected_code_editor(struct code_editor *editor)
{
	FILE *file = fopen("selected_code_editor.dat", "wb");
	if (file == NULL)
	{
		perror("Failed to open file for writing");
		exit(EXIT_FAILURE);
	}
	if(fwrite(editor, sizeof(struct code_editor), 1, file) != 1)
	{
		perror("Failed to write code editor data to file");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
}

struct code_editor *load_selected_code_editor()
{
	FILE *file = fopen("selected_code_editor.dat", "rb");
	if (file == NULL)
	{
		return NULL;
	}
	struct code_editor *editor = malloc(sizeof(struct code_editor));
	if (editor == NULL)
	{
		perror("Failed to allocate memory for code editor");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	if(fread(editor, sizeof(struct code_editor), 1, file) != 1)
	{
		perror("Failed to read code editor data from file");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return editor;
}

void list_code_editors()
{
	struct code_editor *selected_editor = load_selected_code_editor();
	if (selected_editor != NULL)
	{
		printf("Selected code editor: %s\n", selected_editor->name);
		free(selected_editor);
	}
	else
	{
		printf("No code editor selected.\n");
	}
	printf("Available code editors:\n");
	for (int i = 0; i < 7; i++)
	{
		printf("%d. %s\n", code_editors[i].id, code_editors[i].name);
	}
}

struct code_editor *choose_code_editor()
{
	list_code_editors();
	printf("Enter the ID of the code editor you want to use: ");
	unsigned int choice;
	scanf("%u", &choice);

	if (choice < 1 || choice > 7)
	{
		printf("Invalid choice\n");
		return NULL;
	}

	struct code_editor *selected_editor = malloc(sizeof(struct code_editor));
	if (selected_editor == NULL)
	{
		perror("Failed to find the code editor\n");
		return NULL;
	}

	for (int i = 0; i < 7; i++)
	{
		if (code_editors[i].id == choice)
		{
			*selected_editor = code_editors[i];
			free(code_editors);
			return &code_editors[i];
		}
	}
	printf("Failed to find the code editor\n");
	free(selected_editor);
	return NULL;
}