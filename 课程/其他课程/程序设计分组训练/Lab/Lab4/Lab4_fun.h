/* run函数的子函数的声明 */
#pragma once

bool init_conf();

bool illegal_number(const char number[]);
bool illegal_filepath(const char filepath[]);
void separate_filepath(const char filepath[]);
void process_dir();

void write();

int rand_num(int minvalue, int maxvalue);

