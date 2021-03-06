#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include "Help.h"
#include "Tetromino.h"
#include "Kick.h"
#include "GetFigures.h"


int main()
{
	unsigned char fall_timer = 0;
	unsigned char move_timer = 0;
	unsigned char next_figure;
	unsigned char drop_timer = 0;



	bool game_over = false;
	bool hard_drop_pressed = false;
	bool rotate_pressed = false;
	unsigned delay = 0;
	unsigned lines_cleared = 0;
	unsigned char clear_timer = 0;
	unsigned char current_fall_speed = START_FALL_SPEED;
	


	std::chrono::time_point<std::chrono::steady_clock> previous_time;
	std::random_device random_device;
	std::default_random_engine random_engine(random_device());
	std::uniform_int_distribution<unsigned short> shape_distribution(0, 6);
	std::vector<bool> clear_lines(ROWS, 0);



	std::vector<sf::Color> cell_colors = {
		sf::Color(36, 36, 85),
		sf::Color(0, 219, 255),
		sf::Color(0, 36, 255),
		sf::Color(255, 146, 0),
		sf::Color(255, 219, 0),
		sf::Color(0, 219, 0),
		sf::Color(146, 0, 255),
		sf::Color(219, 0, 0),
		sf::Color(73, 73, 85)
	};

	
	std::vector<std::vector<unsigned char>> matrix_tetris(COLUMNS, std::vector<unsigned char>(ROWS));
	sf::Event event;


	sf::RenderWindow window(sf::VideoMode(2 * CELL_SIZE * COLUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "TETRIS_LAB3", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));


	Tetromino figures(static_cast<unsigned char>(shape_distribution(random_engine)), matrix_tetris);
	next_figure = static_cast<unsigned char>(shape_distribution(random_engine));
	previous_time = std::chrono::steady_clock::now();

	
	while (window.isOpen())
	{
		
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
		delay += delta_time;		
		previous_time += std::chrono::microseconds(delta_time);

		
		while (FRAME_DURATION <= delay)
		{			
			delay -= FRAME_DURATION;
			
			while (window.pollEvent(event))
			{
				
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();

					break;
				}
				
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{
						
					case sf::Keyboard::C:
					case sf::Keyboard::Z:
					{
						rotate_pressed = 0;
						break;
					}
					
					case sf::Keyboard::Down:
					{
						drop_timer = 0;
						break;
					} 
					case sf::Keyboard::Left:
					case sf::Keyboard::Right:
					{
						move_timer = 0;
						break;
					}
					case sf::Keyboard::Space:
					{
						hard_drop_pressed = 0;
					}
					}
				}
				}
			}

			
			if (clear_timer==0)
			{
				if (game_over==0)
				{
					
					if (rotate_pressed==0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
						{
							rotate_pressed = 1;

							figures.rotate(1, matrix_tetris);
						} 
						else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
						{
							
							rotate_pressed = 1;

							figures.rotate(0, matrix_tetris);
						}
					}

					
					if (move_timer==0)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						{
							move_timer = 1;
							figures.move_left(matrix_tetris);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						{
							move_timer = 1;
							figures.move_right(matrix_tetris);
						}
					}
					else
					{
						move_timer = (1 + move_timer) % MOVE_SPEED;
					}
					
					if (hard_drop_pressed)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							hard_drop_pressed = 1;
							fall_timer = current_fall_speed;
							figures.hard_drop(matrix_tetris);
						}
					}

					if (drop_timer)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							if (figures.move_down(matrix_tetris))
							{
								fall_timer = 0;
								drop_timer = 1;
							}
						}
					}
					else
					{
						drop_timer = (1 + drop_timer) % SOFT_DROP_SPEED;
					}
					
					if (current_fall_speed == fall_timer)
					{
						if (figures.move_down(matrix_tetris)==0)
						{
							figures.update_matrix(matrix_tetris);
							for (unsigned char a = 0; a < ROWS; a++)
							{
								bool clear_line = 1;
								for (unsigned char b = 0; b < COLUMNS; b++)
								{
									if (matrix_tetris[b][a]==0)
									{
										clear_line = 0;

										break;
									}
								}
								if (clear_line)
								{
									lines_cleared++;
									clear_timer = CLEAR_EFFECT_DURATION;									
									clear_lines[a] = 1;

									if (0 == lines_cleared % LINES_TO_INCREASE_SPEED)
									{
										current_fall_speed = std::max<unsigned char>(SOFT_DROP_SPEED, current_fall_speed - 1);
									}
								}
							}
							if (0 == clear_timer)
							{
								game_over = 0 == figures.reset(next_figure, matrix_tetris);

								next_figure = static_cast<unsigned char>(shape_distribution(random_engine));
							}
						}

						fall_timer = 0;
					}
					else
					{
						fall_timer++;
					}
				} 
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					game_over = 0;
					hard_drop_pressed = 0;
					rotate_pressed = 0;

					lines_cleared = 0;

					current_fall_speed = START_FALL_SPEED;
					fall_timer = 0;
					move_timer = 0;
					drop_timer = 0;

					for (std::vector<unsigned char>& a : matrix_tetris)
					{
						std::fill(a.begin(), a.end(), 0);
					}
				}
			}
			else
			{
				clear_timer--;

				
				if (0 == clear_timer)
				{				
					for (unsigned char a = 0; a < ROWS; a++)
					{						
						if (1 == clear_lines[a])
						{
							for (unsigned char b = 0; b < COLUMNS; b++)
							{
								matrix_tetris[b][a] = 0;								
								for (unsigned char c = a; 0 < c; c--)
								{
									matrix_tetris[b][c] = matrix_tetris[b][c - 1];
									matrix_tetris[b][c - 1] = 0;
								}
							}
						}
					}

					game_over = 0 == figures.reset(next_figure, matrix_tetris);

					next_figure = static_cast<unsigned char>(shape_distribution(random_engine));

					std::fill(clear_lines.begin(), clear_lines.end(), 0);
				}
			}

			if (FRAME_DURATION > delay)
			{
				unsigned char clear_cell_size = static_cast<unsigned char>(2 * round(0.5f * CELL_SIZE * (clear_timer / static_cast<float>(CLEAR_EFFECT_DURATION))));

				sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
				sf::RectangleShape preview_border(sf::Vector2f(5 * CELL_SIZE, 5 * CELL_SIZE));
				preview_border.setFillColor(sf::Color(0, 0, 0));
				preview_border.setOutlineThickness(-1);
				preview_border.setPosition(CELL_SIZE * (1.5f * COLUMNS - 2.5f), CELL_SIZE * (0.25f * ROWS - 2.5f));
				
				window.clear();

				for (unsigned char a = 0; a < COLUMNS; a++)
				{
					for (unsigned char b = 0; b < ROWS; b++)
					{
						if (clear_lines[b]==0)
						{
							cell.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));

							if (1 == game_over && 0 < matrix_tetris[a][b])
							{
								cell.setFillColor(cell_colors[8]);
							}
							else
							{
								cell.setFillColor(cell_colors[matrix_tetris[a][b]]);
							}

							window.draw(cell);
						}
					}
				}

				cell.setFillColor(cell_colors[8]);

				if (game_over==0)
				{
					for (Position& mino : figures.position_in_matrix(matrix_tetris))
					{
						cell.setPosition(static_cast<float>(CELL_SIZE * mino.x), static_cast<float>(CELL_SIZE * mino.y));

						window.draw(cell);
					}

					cell.setFillColor(cell_colors[1 + figures.get_shape()]);
				}

				for (Position& mino : figures.get_tetr())
				{
					cell.setPosition(static_cast<float>(CELL_SIZE * mino.x), static_cast<float>(CELL_SIZE * mino.y));

					window.draw(cell);
				}

				for (unsigned char a = 0; a < COLUMNS; a++)
				{
					for (unsigned char b = 0; b < ROWS; b++)
					{
						if (clear_lines[b])
						{
							cell.setFillColor(cell_colors[0]);
							cell.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
							cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

							window.draw(cell);

							cell.setFillColor(sf::Color(255, 255, 255));
							cell.setPosition(floor(CELL_SIZE * (0.5f + a) - 0.5f * clear_cell_size), floor(CELL_SIZE * (0.5f + b) - 0.5f * clear_cell_size));
							cell.setSize(sf::Vector2f(clear_cell_size, clear_cell_size));

							window.draw(cell);
						}
					}
				}

				cell.setFillColor(cell_colors[1 + next_figure]);
				cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

				window.draw(preview_border);

				for (Position& mino : get_tetromino(next_figure, static_cast<unsigned char>(1.5f * COLUMNS), static_cast<unsigned char>(0.25f * ROWS)))
				{
					unsigned short next_tetromino_x = CELL_SIZE * mino.x;
					unsigned short next_tetromino_y = CELL_SIZE * mino.y;

					if (0 == next_figure)
					{
						next_tetromino_y += static_cast<unsigned char>(round(0.5f * CELL_SIZE));
					}
					else if (3 != next_figure)
					{
						next_tetromino_x -= static_cast<unsigned char>(round(0.5f * CELL_SIZE));
					}

					cell.setPosition(next_tetromino_x, next_tetromino_y);

					window.draw(cell);
				}

				window.display();

				
			}
		}
	}
}