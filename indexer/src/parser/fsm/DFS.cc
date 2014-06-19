/*
 * DFS.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include "parser/fsm/DFS.h"

DFS::~DFS()
{
	for (int i = 0; i < 256; i++)
	{
		free(delta[i]);
	}
	free(delta);
}

DFS::DFS(int** _delta, const std::set<int>& _accept_states) :
	state(0),
	delta(_delta),
	accept_states(_accept_states)
{

}

bool DFS::accepting() const
{
	return accept_states.find(state) != accept_states.end();
}

void DFS::next(char c)
{
	if (state == STATE_BAD_STATE)
	{
		puts("DFS in bad state.");
		exit(1);
	}
	state = delta[c][state];
}

int** create_delta(const int num_states)
{
	int **ret_val = (int **) malloc (sizeof(*ret_val) * 256);
	for (int i=0;i<256;i++)
	{
		ret_val[i] = (int *) malloc (sizeof(*ret_val[i]) * num_states);
		for (int j=0;j<num_states;j++)
		{
			ret_val[i][j] = STATE_BAD_STATE;
		}
	}
	return ret_val;
}

void something()
{
	int indices[256];

	int id = 0;
	for (int i = 0; i < 256; i++)
	{
		bool is_char = strchr(get_settings().get_delims(), i) != nullptr
				|| ('a' <= i && i <= 'z')
				|| ('A' <= i && i <= 'Z')
				|| ('0' <= i && i <= '9');

		if (is_char)
		{
			indices[i] = id++;
		}
	}
}

int get_index(CHARACTER c)
{
	switch(c)
	{
	// should just have an array of indices.
		case 'a' : return  0;
		case 'b' : return  1;
		case 'c' : return  2;
		case 'd' : return  3;
		case 'e' : return  4;
		case 'f' : return  5;
		case 'g' : return  6;
		case 'h' : return  7;
		case 'i' : return  8;
		case 'j' : return  9;
		case 'k' : return  0;
		case 'l' : return 11;
		case 'm' : return 12;
		case 'n' : return 13;
		case 'o' : return 14;
		case 'p' : return 15;
		case 'q' : return 16;
		case 'r' : return 17;
		case 's' : return 18;
		case 't' : return 19;
		case 'u' : return 20;
		case 'v' : return 21;
		case 'w' : return 22;
		case 'x' : return 23;
		case 'y' : return 24;
		case 'z' : return 25;
		case 'A' : return 26;
		case 'B' : return 27;
		case 'C' : return 28;
		case 'D' : return 29;
		case 'E' : return 30;
		case 'F' : return 31;
		case 'G' : return 32;
		case 'H' : return 33;
		case 'I' : return 34;
		case 'J' : return 35;
		case 'K' : return 36;
		case 'L' : return 37;
		case 'M' : return 38;
		case 'N' : return 39;
		case 'O' : return 40;
		case 'P' : return 41;
		case 'Q' : return 42;
		case 'R' : return 43;
		case 'S' : return 44;
		case 'T' : return 45;
		case 'U' : return 46;
		case 'V' : return 47;
		case 'W' : return 48;
		case 'X' : return 49;
		case 'Y' : return 50;
		case 'Z' : return 51;
		case '0' : return 52;
		case '1' : return 53;
		case '2' : return 54;
		case '3' : return 55;
		case '4' : return 56;
		case '5' : return 57;
		case '6' : return 58;
		case '7' : return 59;
		case '8' : return 60;
		case '9' : return 61;
		case '.' : return 62;
		case '!' : return 63;
		case '@' : return 64;
		case '#' : return 65;
		case '$' : return 66;
		case '%' : return 67;
		case '^' : return 68;
		case '&' : return 69;
		case '*' : return 70;
		case '(' : return 71;
		case ')' : return 72;
		case '+' : return 73;
		case '-' : return 74;
		case '=' : return 75;
		case '{' : return 76;
		case '}' : return 77;
		case '|' : return 78;
		case '[' : return 79;
		case ']' : return 80;
		case ';' : return 81;
		case '\'': return 82;
		case ':' : return 83;
		case '"' : return 84;
		case ',' : return 85;
		case '.' : return 86;
		case '<' : return 87;
		case '>' : return 88;
		case '/' : return 89;
		case '?' : return 90;
		case '\\': return 91;
		case '\t': return 92;
		case '\n': return 93;
		case '\r': return 94;
		case '^' : return 95;
		case '`' : return 96;
		case '~' : return 97;
		case ';' : return 98;
		default:
			return -1;
	}
}
