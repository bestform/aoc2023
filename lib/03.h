//
// Created by bestf on 1/3/2024.
//

#ifndef AOC2023_03_H
#define AOC2023_03_H

typedef struct Schematic Schematic;

Schematic *schematic_create();
void schematic_add_line(Schematic *schematic, const char* line);
int schematic_sum(Schematic *schematic);
int schematic_gear_ratio_sum(Schematic *schematic);
void schematic_free(Schematic *s);

#endif //AOC2023_03_H
