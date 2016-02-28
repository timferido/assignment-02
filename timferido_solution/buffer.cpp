/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 YOUR_NAME <YOUR_EMAIL>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Implements `buffer.h`.
 */

#include <string>
#include <iostream>
using namespace std;
#include "constants.h"
#include "buffer.h"


// ----------------------------------------------------------------------------

Buffer::Buffer(unsigned int size_x, unsigned int size_y)
    : size_x(size_x), size_y(size_y)
{
    data_ = new char[size_x*size_y];
    for (unsigned int i = 0; i < size_x * size_y; i++)
        data_[i] = ' ';
}


Buffer::~Buffer()
{
    delete[] data_;
}


char Buffer::get(unsigned int x, unsigned int y) const
{
	if (x > TERM_SIZE_X && y > TERM_SIZE_Y) 
	{
		std::cerr << "ERROR: " << __FUNCTION__ << "index out of bounds" << endl;
		exit(1);
	}
    
	return data_[ y* size_x +x];
}


void Buffer::set(unsigned int x, unsigned int y, char c)
{
	if (x > TERM_SIZE_X && y > TERM_SIZE_Y)
	{
		std::cerr << "ERROR: " << __FUNCTION__ << "index out of bounds" << endl;
		exit(1);
	}

	data_[y*size_x + x] = c;
}


void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s)
{
	if (pos_x > TERM_SIZE_X && pos_y > TERM_SIZE_Y)
	{
		std::cerr << "ERROR: " << __FUNCTION__ << "index out of bounds" << endl;
		exit(1);
	}

	std::string shape = s; //save a copy
	string::size_type pos = shape.find('\n');
	string::size_type idx = 0;

	while (pos != string::npos) {
		string next_line = shape.substr(0, pos);
		for (int row_idx = pos_x; idx < next_line.size(); idx++, row_idx++)
		{
			set(row_idx, pos_y, next_line[idx]);
		}
		shape = shape.substr(pos + 1);
		pos = shape.find('\n');
		pos_y++;
	}

}


void Buffer::draw() const
{
    for(int y = 0; y<size_y; y++)
        for(int x = 0; x<size_x; x++){
            std::cout << data_[y*size_x+x];
        }
    std::cout << std::endl;
}


void Buffer::clear()
{
    for (int i = 0;i<size_x*size_y;i++){
        data_[i]=' ';
    }
}

