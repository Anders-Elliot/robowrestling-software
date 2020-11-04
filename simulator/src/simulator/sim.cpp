#include <simulator/sim.h>
#include <iostream>

void draw_field() {
    
    sf::CircleShape dohyo(150.f); //create the circle that represents the dohyo. Input is radius
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(10.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((WINDOW_WIDTH/2)-150, (WINDOW_HEIGHT/2)-150);
    window_->draw(dohyo);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::RectangleShape rectangle(sf::Vector2f(robot->width_, robot->length_));
    rectangle.setFillColor(sf::Color(50, 50, 50));
    double shift_magnitude = sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = robot->x_pos_ + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = robot->y_pos_ + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
    rectangle.setPosition(homogenous_x, homogenous_y);
    rectangle.setRotation(robot->angle_*180/M_PI + 90);
    window_->draw(rectangle);
}	

void update() {
	sf::Event event;
    window_->clear(sf::Color::White); // clear the window with white color
    while (window_->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window_->close();
        } 
    }
    // window->clear();

    // need to redraw things
    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    window_->display();
}

int main() {
	/* code */
	robot1_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)-65, WINDOW_HEIGHT/2, 0);
	robot2_ = std::make_shared<BasicRobot>((WINDOW_WIDTH/2)+65, WINDOW_HEIGHT/2, M_PI);
    physics_updater_ = std::make_shared<RobotPhysicsUpdater>();
    
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");
    window_->clear(sf::Color::White); // clear the window with white color


    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    int i = 0;
	while (window_->isOpen()) {
        if (i < 5) {
            auto dummy_vector = std::vector<double>();
            std::vector<int> r1_drive = robot1_->strat_->next_action(dummy_vector);
            physics_updater_->move_robot(robot1_, r1_drive[0], r1_drive[1], 1);
            physics_updater_->move_robot(robot2_, 100, 50, 2);
            // std::cout << robot1->x_pos << ", " << robot1->y_pos << std::endl;
            // std::cout << robot2->x_pos << ", " << robot2->y_pos << std::endl;
            // i++;
        }
		update();
	}
	return 0;
}
