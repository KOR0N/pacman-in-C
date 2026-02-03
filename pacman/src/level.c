#include "headers/level.h"
#include <stdlib.h>
#include <stdio.h>
#include "headers/framework.h"

// pour construire les chemins de fichiers
extern const char* pathSeparator;

Level loadLevel(const int id)
{
    Level level;
    level.id = id;
    level.width = WIDTH;
    level.height = HEIGHT;

    level.grid = (char**)malloc(sizeof(char*) * level.height);
    for (int i = 0; i < level.height; i++)
    {
        level.grid[i] = (char*)malloc(sizeof(char) * (level.width + 1)); // +1 for null terminator if needed, though we read chars
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "resources%slevels%s%d.txt", pathSeparator, pathSeparator, id);

    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Could not open level file %s\n", filename);
        // Fallback or exit? For now, let's return empty/null level or handle error gracefully
        // But the function signature returns Level by value.
        // Let's fill with spaces or walls to avoid crash
        for(int y=0; y<level.height; y++) {
            for(int x=0; x<level.width; x++) {
                level.grid[y][x] = 'H';
            }
            level.grid[y][level.width] = '\0';
        }
        return level;
    }

    char line[256];
    int row = 0;
    while (fgets(line, sizeof(line), file) && row < level.height)
    {
        for (int col = 0; col < level.width; col++)
        {
            // Handle potential newlines if line is shorter or has \n
            if (line[col] == '\n' || line[col] == '\0') break;
            level.grid[row][col] = line[col];
        }
        level.grid[row][level.width] = '\0'; // Null terminate for safety
        row++;
    }

    fclose(file);
    return level;
}
