/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 YOUR_NAME <YOUR_EMAIL>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Implements of `neighborhood.h`.
 */

#include <random>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
#include "constants.h"
#include "buffer.h"
#include "shape.h"
#include "neighborhood.h"

// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------

namespace {
    unsigned int mtrand(unsigned int low, unsigned int high) {
        static std::random_device rd;
        static std::mt19937 mt(rd());  // engine (mersenne twister)

        return std::uniform_int_distribution<unsigned int>(low, high)(mt);
    }

}


Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y) : size_x(size_x), size_y(size_y)
{
	unsigned int padding = 5 * 3; //inter size of object;

	for (int idx = 0; idx < (size_y * size_x * padding); idx++)
	{
		Shape p_next_shape;
		p_next_shape.setType("empty");
		neighborhood_[idx] = p_next_shape;
	}
}


Neighborhood::~Neighborhood()
{
	neighborhood_.erase(neighborhood_.begin(), neighborhood_.end());
}


Shape Neighborhood::get(unsigned int x, unsigned int y) const
{
	return ((neighborhood_[y * size_x + x]));
}


void  Neighborhood::set(unsigned int x, unsigned int y, const Shape & s)
{
	neighborhood_[y * size_x + x] = s;

}


void Neighborhood::move(unsigned int old_x, unsigned int old_y)
{
	unsigned int x_random_position = mtrand(0,TERM_SIZE_X);
	unsigned int y_random_position = mtrand(0,TERM_SIZE_Y);
	Shape empty_shape;
    get(old_x,old_y);
	Shape shape_to_move = neighborhood_[old_y * size_x + old_x];
    set(old_x,old_y,empty_shape);
	neighborhood_[old_y * size_x + old_x] = empty_shape;
    set(x_random_position,y_random_position,shape_to_move);
	neighborhood_[y_random_position * size_x + x_random_position] = empty_shape;
}


void Neighborhood::animate(unsigned int frames)
{
    {
        Buffer b(size_x * Shape::size_x, size_y * Shape::size_y);
        for (int k = 0; k < frames; k++)
        {
            for (int y = 0; y < size_y; y++)
            {
                for (int x = 0; x < size_x; x++)
                {
                    neighborhood_[y*size_x + x].drawToBuffer(b, x*Shape::size_x, y*Shape::size_y);
                }
            }
            
            b.draw();
            for (int y = 0; y < size_y; y++)
            {
                for (int x = 0; x < size_x; x++)
                {
                    if (!neighborhood_[y*size_x + x].isHappy(*this, x, y))
                        
                        move(x, y);
                    
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
}
