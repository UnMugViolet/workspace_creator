#include "../program/workspaces.h"
#include "../settings/settings.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


void clear_input_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int count_workspaces()
{
	FILE *file = fopen("workspaces.dat", "rb");
	if (file == NULL)
	{
		return 0;
	}
	struct workspaces workspace;
	int count = 0;
	while (fread(&workspace, sizeof(struct workspaces), 1, file))
	{
		count++;
	}
	fclose(file);
	return count;
}

int	get_workspace_id()
{
	FILE *file = fopen("workspaces.dat", "rb");
	if (file == NULL)
	{
		return 1;
	}

	struct workspaces workspace;
	int max_id = 0;

	while (fread(&workspace, sizeof(struct workspaces), 1, file))
	{
		if ( workspace.id > max_id)
		{
			max_id = workspace.id;
		}
	}
	fclose(file);
	return max_id + 1;
}

int find_workspace_by_id(int *project_id)
{
	FILE *file = fopen("workspaces.dat", "rb");
	if (file == NULL)
	{
		perror("Failed to open file for reading");
		exit(EXIT_FAILURE);
	}
	struct workspaces workspace;
	while (fread(&workspace, sizeof(struct workspaces), 1, file))
	{
		if (workspace.id == *project_id)
		{
			fclose(file);
			return workspace.id;
		}
	}
	fclose(file);
	fprintf(stderr, "Workspace %ls not found\n", project_id);
	return -1;
}

int find_workspace(char *project)
{
	FILE *file = fopen("workspaces.dat", "rb");
	if (file == NULL)
	{
		perror("Failed to open file for reading");
		exit(EXIT_FAILURE);
	}
	struct workspaces workspace;
	while (fread(&workspace, sizeof(struct workspaces), 1, file))
	{
		if (strcmp(workspace.name, project) == 0)
		{
			fclose(file);
			return workspace.id;
		}
	}
	fclose(file);
	return -1;
}

void list_workspaces()
{
	FILE *file = fopen("workspaces.dat", "rb");
	if (file == NULL)
	{
		printf("No workspaces found.\nworkspace add [name] to add a workspace.\n");
		exit(EXIT_FAILURE);
	}
	struct workspaces workspace;
	while (fread(&workspace, sizeof(struct workspaces), 1, file))
	{
		printf("Workspace id: %i\n", workspace.id);
		printf("Workspace name: %s\n", workspace.name);
		printf("Workspace path: %s\n", workspace.path);
		printf("URLs: ");
		if (workspace.urls == NULL)
		{
			printf("None\n");
		}
		else
		{
			for (int i = 0; workspace.urls[i]; i++)
			{
				printf("%s ", workspace.urls[i]);
				printf("\n");
			}
		}
		printf("Start commands: ");
		if (workspace.start_command == NULL)
		{
			printf("None\n");
		}
		else
		{
			for (int i = 0; workspace.start_command[i]; i++)
			{
				printf("%s ", workspace.start_command[i]);
				printf("\n");
			}
		}
		printf("Stop commands: ");
		if (workspace.stop_command == NULL)
		{
			printf("None\n");
		} else {
			for (int i = 0; workspace.stop_command[i]; i++)
			{
				printf("%s ", workspace.stop_command[i]);
				printf("\n");
			}
		}
		printf("Need sudoer: %d\n", workspace.need_sudoer);
		printf("\n");
	}
	fclose(file);
}